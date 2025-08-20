

#include "DimmView.h"
#include "Spd.h"
#include "I3cAccess.h"
#include "I3C0.h"
#include "Ddr5Spd.h"
#include "MemRegs.h"
#include "RACU.h"


BOOLEAN InitI3cDone;

UINT32  PciExpressBaseAddress;
UINT32  ScfBaseAddress;
//UINT32  I3cSpdBus0BaseAddress;  //ABC IMC0~2
//UINT32  I3cSpdBus1BaseAddress;  //GHI IMC6~8
//UINT32  I3cSpdBus2BaseAddress;  //DEF IMC3~5
//UINT32  I3cSpdBus3BaseAddress;  //JKL IMC8~11
UINT32  I3cSpdBusBaseAddress[4];
UINT8   I3cDevStatus;
UINT16  PpCmdEnblReg[4];
UINT8   StrapAddress[3] = { 0, 2, 4 };
SMB_DEVICE_STRUCT Spd;

VOID
SelectI3cPpFreq(
  UINT32 clk
)
{
  Print(L"I3C Push Pull: ");
  switch (clk) {
  case SMB_4M_CLK_PERIOD:
    Print(L"Clock period to be programmed for 4 MHz\n");
    break;

  case SMB_6M_CLK_PERIOD:
    Print(L"Clock period to be programmed for 6 MHz ~ 6.25\n");
    break;

  case SMB_8M_CLK_PERIOD:
    Print(L"Clock period to be programmed for 8 MHz ~ 8.3\n");
    break;

  case SMB_9M_CLK_PERIOD:
    Print(L"Clock period to be programmed for 9 MHz ~ 9.09\n");
    break;

  case SMB_10M_CLK_PERIOD:
    Print(L"Clock period to be programmed for 10 MHz");
    break;

  default:
    Print(L"Unknow Clock Speed\n");
  }

}

VOID
SelectI3cOdFreq(
  UINT32 clk
)
{
  Print(L"I3C Open Drain: ");
  switch (clk) {
  case SMB_100K_CLK_PERIOD:
    Print(L"Clock period to be programmed for 100 kHz\n");
    break;

  case SMB_400K_CLK_PERIOD:
    Print(L"Clock period to be programmed for 400 kHz\n");
    break;

  case SMB_700K_CLK_PERIOD:
    Print(L"Clock period to be programmed for 700 kHz\n");
    break;

  case SMB_1M_CLK_PERIOD:
    Print(L"Clock period to be programmed for 1 MHz\n");
    break;

  default:
    Print(L"Unknow Clock Speed\n");
  }
}

VOID
SelectI2cFmFreq(
  UINT32 clk
)
{
  Print(L"I2C Fast Mode: ");
  switch (clk) {
  case SMB_100K_CLK_PERIOD:
    Print(L"Clock period to be programmed for 100 kHz\n");
    break;

  case SMB_400K_CLK_PERIOD:
    Print(L"Clock period to be programmed for 400 kHz\n");
    break;

  case SMB_700K_CLK_PERIOD:
    Print(L"Clock period to be programmed for 700 kHz\n");
    break;

  case SMB_1M_CLK_PERIOD:
    Print(L"Clock period to be programmed for 1 MHz\n");
    break;

  default:
    Print(L"Unknow Clock Speed\n");
  }
}

EFI_STATUS
CheckI3cFreq(
  UINT32 I3cBaseAddress
)
{
  UINT32  ClockPeriod;

  SCL_I3C_OD_TIMING_I3C0_STRUCT I3cOd;
  SCL_I3C_PP_TIMING_I3C0_STRUCT I3cPp;
  SCL_I2C_FM_TIMING_I3C0_STRUCT I2cFm;

  I3cPp.Data = MmioRead32(I3cBaseAddress + SCL_I3C_PP_TIMING_I3C0_REG);
  I3cOd.Data = MmioRead32(I3cBaseAddress + SCL_I3C_OD_TIMING_I3C0_REG);
  I2cFm.Data = MmioRead32(I3cBaseAddress + SCL_I2C_FM_TIMING_I3C0_REG);

  ClockPeriod = (I3cPp.Bits.i3c_pp_hcnt * 100) / I3C_DUTY_CYCLE_PUSH_PULL;
  //Print(L"Pull Push High counter = %d\n", I3cPp.Bits.i3c_pp_hcnt);
  //Print(L"Pull Push ClkFreq = %d\n", ClockPeriod);
  SelectI3cPpFreq(ClockPeriod);

  ClockPeriod = (I3cOd.Bits.i3c_od_hcnt * 100) / I3C_DUTY_CYCLE_OPEN_DRAIN;
  //Print(L"Open Drain High counter = %d\n", I3cOd.Bits.i3c_od_hcnt);
  //Print(L"Open Drain ClkFreq = %d\n", ClockPeriod);
  SelectI3cOdFreq(ClockPeriod);

  ClockPeriod = (I2cFm.Bits.i2c_fm_hcnt * 100) / I3C_DUTY_CYCLE_OPEN_DRAIN;
  SelectI2cFmFreq(ClockPeriod);
 
  return EFI_SUCCESS;
}

EFI_STATUS
CheckI3cConfig(
  VOID
)
{
  DEVICE_CONTROL_I3C0_STRUCT I3cDevCtrl;

  for (UINT8 i=0; i< BHS_MAX_SMB_INSTANCE; i++) {
    if (I3cSpdBusBaseAddress[i] != 0) {
      I3cDevCtrl.Data = MmioRead32(I3cSpdBusBaseAddress[i] + DEVICE_CONTROL_I3C0_REG);
      if (I3cDevCtrl.Bits.iba_include == 1 &&
          I3cDevCtrl.Bits.i2c_slave_present == 0 &&
          I3cDevCtrl.Bits.enable == 1) {
          //Print(L"I3C Instance %d has I3C Devices\n", i);
          CheckI3cFreq(I3cSpdBusBaseAddress[i]);
          I3cDevStatus |= ((UINT8)BIT0 << i);
      }
    }
    else {
      //Print(L"I3C Instance %d is unsupported\n", i);
      return EFI_UNSUPPORTED;
    }
  }
  //Print(L"I3cDevStatus %x\n", I3cDevStatus);
  return EFI_SUCCESS;
}

EFI_STATUS
CheckResponseStatus(
  UINT32 I3cInstanceAddress,
  UINT8 TransactionID
)
{
  UINT32                                  Timeout;
  RESPONSE_QUEUE_PORT_I3C0_STRUCT         I3cResp;
  EFI_STATUS                              Status = EFI_SUCCESS;

  Timeout = 100;
  //
  // Wait for there is space in the command queue
  //
  //Print(L"TransactionID  %x\n", TransactionID);
  do {
    I3cResp.Data = MmioRead32(I3cInstanceAddress + RESPONSE_QUEUE_PORT_I3C0_REG);

    //MicroSecondDelay(1);
    gBS->Stall(1);
    Timeout--;

    if (Timeout <= 0) {
      Status = EFI_TIMEOUT;
      Print(L"CheckResponseStatus%r\n", Status);
      break;
    }
    // Wait for timeout
  } while ((I3cResp.Bits.tid != TransactionID) || I3cResp.Bits.err_status);

  //Print(L"Respone tid:%x Err:%x\n", I3cResp.Bits.tid, I3cResp.Bits.err_status); 

  return Status;
}

EFI_STATUS
CheckTxFiFoSpace(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS                              Status = EFI_DEVICE_ERROR;
  UINT32                                  Timeout;
  INTR_STATUS_I3C0_STRUCT                 I3cStatus;
  

  //
  // Wait for there is space in the command queue
  //
  Timeout = 100;

  do {
    I3cStatus.Data = MmioRead32(I3cInstanceAddress + INTR_STATUS_I3C0_REG);
    //MicroSecondDelay(1);
    gBS->Stall(1);
    Timeout--;

    if (Timeout <= 0) {
      Status = EFI_TIMEOUT;
      Print(L"CheckTxFiFoSpace: %r\n", Status);
      break;
    }
    // Wait for timeout
  } while ((I3cStatus.Bits.tx_thld_stat == 0) && (I3cStatus.Bits.transfer_err_stat == 0));


  return Status;
}

EFI_STATUS
WaitForWriteToCompleteTarget(
  UINT32 I3cInstanceAddress
)
{
  UINT32                      Timeout;
  INTR_STATUS_I3C0_STRUCT     I3cStatus;
  EFI_STATUS                  Status = EFI_DEVICE_ERROR;

  Timeout = 100;

  //
  // Wait for there is space in the command queue
  //
  do {
    I3cStatus.Data = MmioRead32(I3cInstanceAddress + INTR_STATUS_I3C0_REG);

    if (I3cStatus.Bits.resp_ready_stat == 1) {
      Status = EFI_SUCCESS;
      //Print(L"Response Status Ready\n");
      break;
    }

    //MicroSecondDelay(1);
    gBS->Stall(1);
    Timeout--;

    if (Timeout <= 0) {
      Status = EFI_TIMEOUT;
      Print(L"WaitForWriteToCompleteTarget: %r\n", Status);
      break;
    }

    // Wait for timeout
  } while (Timeout > 0);

 
    
  return Status;
}

EFI_STATUS
WaitForHostNotBusyTarget (
  UINT32 I3cInstanceAddress
)
{
  UINT32                      Timeout;
  INTR_STATUS_I3C0_STRUCT     I3cStatus;
  EFI_STATUS                  Status = EFI_DEVICE_ERROR;

  Timeout = 100;
  //
  // Wait for there is space in the command queue
  //
  do {
    I3cStatus.Data = MmioRead32(I3cInstanceAddress + INTR_STATUS_I3C0_REG);

    if (I3cStatus.Bits.cmd_queue_ready_stat == 1) {
      Status = EFI_SUCCESS;
      //Print(L"CMD Queue Status Ready\n");
      break;
    }
    
    //MicroSecondDelay(1);
    gBS->Stall(1);
    Timeout--;

    if (Timeout <= 0) {
      Status = EFI_TIMEOUT;
      Print(L"WaitForHostNotBusyTarget: %r\n", Status);
      break;
    }
    // Wait for timeout
  } while (Timeout > 0);

  return Status;

}

EFI_STATUS
WaitForDataReadyRead(
  UINT32 I3cInstanceAddress
)
{
  UINT32                      Timeout;
  INTR_STATUS_I3C0_STRUCT     I3cStatus;
  EFI_STATUS                  Status = EFI_SUCCESS;

  Timeout = 100;
  do {
    I3cStatus.Data = MmioRead32(I3cInstanceAddress + INTR_STATUS_I3C0_REG);

    //MicroSecondDelay(1);
    gBS->Stall(1);
    Timeout--;

    if (Timeout <= 0) {
      Status = EFI_TIMEOUT;
      Print(L"WaitForDataReadyRead Error: %r\n", Status);
      break;
    }

  } while ((I3cStatus.Bits.rx_thld_stat == 0) && (I3cStatus.Bits.transfer_err_stat == 0));

  return Status;
}

EFI_STATUS
SendCccCmd(
  UINT32  I3cInstanceAddress,
  UINT8   CccCommand,
  SMB_ATTR_FLAG Attribute,
  UINT8   *Data,
  UINT8   *DataLength
)
{
  EFI_STATUS                                      Status;
  COMMAND_QUEUE_PORT_I3C0_STRUCT                  CmdPort;
  REGULAR_DATA_TRANSFER_COMMAND_LOW_WITHOUT_DAT   RegularCommandLow;
  REGULAR_DATA_TRANSFER_COMMAND_HIGH_WITHOUT_DAT  RegularCommandHigh;
  UINT8                                           TransactionID;
  UINT8                                           ReadOrWrite;
  UINT8                                           CmdPresent;
  UINT8                                           Toc;
  UINT8                                           Roc;
  //
  // determine the Read no Write field identifies direction of the transfer
  //
  switch (Attribute) {
  case AttrCccRead:
    ReadOrWrite = RNW_READ;
    CmdPresent = CP_CCC_HDR;
    Roc = ROC_REQUIRED;
    Toc = TOC_STOP;
    break;

  case AttrCccWrite:
    ReadOrWrite = RNW_WRITE;
    CmdPresent = CP_CCC_HDR;
    Roc = ROC_REQUIRED;
    Toc = TOC_STOP;
    break;

  case AttrNormalRead:
    ReadOrWrite = RNW_READ;
    CmdPresent = CP_TRANFSER;
    Roc = ROC_REQUIRED;
    Toc = TOC_STOP;
    break;

  case AttrNormalWrite:
    ReadOrWrite = RNW_WRITE;
    CmdPresent = CP_TRANFSER;
    Roc = ROC_REQUIRED;
    Toc = TOC_STOP;
    break;

  case AttrNormalWriteReStartRead:
    ReadOrWrite = RNW_WRITE;
    CmdPresent = CP_TRANFSER;
    Roc = ROC_NOT_REQUIRED;
    Toc = TOC_RESTART;
    break;

  default:

    return EFI_INVALID_PARAMETER;
    break;
  }

  Status = EFI_SUCCESS;
  TransactionID = TidCcc;

  //
  // Form read/write command
  //
  RegularCommandLow.Data = 0;
  RegularCommandLow.Bits.com_attr = I3C_COM_ATTR_XFER;

  RegularCommandLow.Bits.tid = TransactionID;
  RegularCommandLow.Bits.i2cni3c = I3C_DEVICE;
  if (CmdPresent == CP_CCC_HDR) {
    RegularCommandLow.Bits.cmd = CccCommand;
  }
  RegularCommandLow.Bits.cp = CmdPresent;
  RegularCommandLow.Bits.mode_speed = I3cSdr0I2cFm;
  RegularCommandLow.Bits.rnw = ReadOrWrite;
  RegularCommandLow.Bits.roc = Roc;
  RegularCommandLow.Bits.toc = Toc;

  RegularCommandHigh.Data = 0;
  RegularCommandHigh.Bits.data_length = *DataLength;

  CmdPort.Data = 0x0;
  CmdPort.Bits.command = RegularCommandLow.Data;

  Status = WaitForHostNotBusyTarget(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {

    return EFI_DEVICE_ERROR;
  }
  MmioWrite32(I3cInstanceAddress + COMMAND_QUEUE_PORT_I3C0_REG, CmdPort.Bits.command);

  CmdPort.Bits.command = RegularCommandHigh.Data;
  Status = WaitForHostNotBusyTarget(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {

    return EFI_DEVICE_ERROR;
  }
  MmioWrite32(I3cInstanceAddress + COMMAND_QUEUE_PORT_I3C0_REG, CmdPort.Bits.command);

  Status = WaitForWriteToCompleteTarget(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  Status = CheckResponseStatus(I3cInstanceAddress, TransactionID);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
SpdGetDdrMbistCapability(
  UINT32 I3cInstanceAddress
)
{
  UINT8 SpdReg = 0;
  EFI_STATUS Status;
  UINT8 DdrMbistCapability;

  Status = SpdReadByte(I3cInstanceAddress, SPD_SDRAM_BL32_POST_PACKAGE_REPAIR_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get DDR MBIST %r\n", Status);
    return Status;
  }

  DdrMbistCapability = (SpdReg & BIT1) >> 1;

  Print(L"DDR MBIST Capability 0x%02X\n", DdrMbistCapability);

  return Status;
}

EFI_STATUS
SpdGetSpdMfgId(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS  Status;
  UINT8 SpdReg = 0;
  UINT16 SpdMfgId = 0;

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_SPD_MANUFACTURER_ID_CODE_1_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"Get SPD MFG ID %r\n", Status);
    return Status;
  }
  SpdMfgId = (UINT16)(SpdReg << 8);

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_SPD_MANUFACTURER_ID_CODE_0_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"Get SPD MFG ID %r\n", Status);
    return Status;
  }
  SpdMfgId |= (UINT16)(SpdReg & ~BIT7);

  Print(L"SPD MFGID 0x%02X\n", SpdMfgId);

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_SPD_DEVICE_REVISION_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"Get SPD Revision %r\n", Status);
    return Status;
  }
  Print(L"SPD Revision 0x%02X\n", SpdReg);

  return Status;
}

EFI_STATUS
SpdGetTsodMfgId(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS Status;
  UINT8 SpdReg = 0;
  UINT16 TsodMfgId = 0;

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_THERMAL_SENSORS_TS_MANUFACTURER_ID_CODE_1_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get TSOD MFG ID %r\n", Status);
    return Status;
  }
  TsodMfgId = (UINT16)(SpdReg << 8);

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_THERMAL_SENSORS_TS_MANUFACTURER_ID_CODE_0_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get TSOD MFG ID %r\n", Status);
    return Status;
  }
  TsodMfgId |= (UINT16)(SpdReg & ~BIT7);

  Print(L"TSOD MFG ID 0x%02X\n", TsodMfgId);

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_THERMAL_SENSORS_TS_DEVICE_REVISION_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get TS Revision %r\n", Status);
    return Status;
  }
  Print(L"TSOD REVISION 0x%02X\n", SpdReg);

  return Status;
}

EFI_STATUS
SpdGetPmicVendor(
  UINT32 I3cInstanceAddress
)
{
  UINT8   SpdReg = 0;
  UINT16  PmicVendor = 0;
  EFI_STATUS Status;

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_PMIC_0_MANUFACTURER_ID_CODE_1_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get PMIC0 Vendor %r\n", Status);
    return Status;
  }
  PmicVendor = (UINT16)(SpdReg << 8);
  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_PMIC_0_MANUFACTURER_ID_CODE_0_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get PMIC0 Vendor %r\n", Status);
    return Status;
  }
  PmicVendor |= (UINT16)(SpdReg & ~BIT7);
  Print(L"PMIC0 ID: 0x%02X\n", PmicVendor);

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_PMIC_0_DEVICE_TYPE_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get PMIC0 Type %r\n", Status);
    return Status;
  }
  Print(L"PMIC0 Type: 0x%02X\n", SpdReg);

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_PMIC_0_DEVICE_REVISION_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get PMIC0 Revision %r\n", Status);
    return Status;
  }
  Print(L"PMIC0 Revision: 0x%02X\n", SpdReg);

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_PMIC_1_MANUFACTURER_ID_CODE_1_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get PMIC1 Vendor %r\n", Status);
    return Status;
  }
  PmicVendor = (UINT16)(SpdReg << 8);
  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_PMIC_1_MANUFACTURER_ID_CODE_0_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get PMIC1 Vendor %r\n", Status);
    return Status;
  }
  PmicVendor |= (UINT16)(SpdReg & ~BIT7);
  Print(L"PMIC1 ID: 0x%02X\n", PmicVendor);

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_PMIC_1_DEVICE_TYPE_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get PMIC1 Type %r\n", Status);
    return Status;
  }
  Print(L"PMCI1 Type 0x%02X\n", SpdReg);

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_PMIC_1_DEVICE_REVISION_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get PMIC1 Revision %r\n", Status);
    return Status;
  }
  Print(L"PMIC1 Revision: 0x%02X\n", SpdReg);

  return Status;
}

EFI_STATUS
SpdGetRcdRevision(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS Status;
  UINT8 SpdReg = 0;

  Status = SpdReadByte(I3cInstanceAddress, SPD_RDIMM_LRDIMM_REGISTERING_CLOCK_DRIVER_RCD_DEVICE_REVISION_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get RCD Revision %r\n", Status);
    return Status;
  }
  Print(L"Rcd Revision %02X\n", SpdReg);

  return Status;
}

EFI_STATUS
GetRcdDeviceTypeFromSpd(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS Status;
  RDIMM_LRDIMM_REGISTERING_CLOCK_DRIVER_RCD_DEVICE_TYPE_STRUCT RcdDeviceTypeReg;

  Status = SpdReadByte(I3cInstanceAddress, SPD_RDIMM_LRDIMM_REGISTERING_CLOCK_DRIVER_RCD_DEVICE_TYPE_REG, &RcdDeviceTypeReg.Data);
  if (EFI_ERROR(Status)) {
    Print(L"Get RCD Device Type %r\n", I3cInstanceAddress);
    return Status;
  }
  //
  // RCD device type bit definations is plus 1
  //
  Print(L"Rcd Device Type 0x%02X\n", (RcdDeviceTypeReg.Bits.device_type & 0xF) + 1);

  return Status;
}

EFI_STATUS
SpdGetRcdVendor(
  UINT32 I3cInstanceAddress
)
{
  UINT8 SpdReg = 0;
  UINT16 RcdVendor = 0;
  EFI_STATUS  Status;

  //
  // Registering Clock Driver (RCD) Manufacturer ID Code
  //

  Status = SpdReadByte(I3cInstanceAddress, SPD_RDIMM_LRDIMM_REGISTERING_CLOCK_DRIVER_RCD_MANUFACTURER_ID_CODE_1_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"Get Rcd Vendor %r\n", Status);
    return Status;
  }

  RcdVendor = (UINT16)(SpdReg << 8);

  Status = SpdReadByte(I3cInstanceAddress, SPD_RDIMM_LRDIMM_REGISTERING_CLOCK_DRIVER_RCD_MANUFACTURER_ID_CODE_0_REG, &SpdReg);
  if (EFI_ERROR(Status)) {
    Print(L"Get Rcd Vendor %r\n", Status);
    return Status;
  }

  RcdVendor |= (UINT16)(SpdReg & ~BIT7);

  Print(L"RCD Vendor 0x%04X\n", RcdVendor);
  return Status;
}

EFI_STATUS
SpdGetModulePartNum(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS Status;
  UINT8 RegData[SPD_MODULE_PART_DDR5];
  
  for (UINT8 i = 0; i < SPD_MODULE_PART_DDR5; i++) {
    Status = SpdReadByte(I3cInstanceAddress, SPD_MODULE_PART_NUMBER_0_REG + i, &RegData[i]);
    if (EFI_ERROR(Status)) {
      Print(L"SPD Get Module PartNum %r\n", Status);
      return Status;
    }
  }

  Print(L"Part Number:");
  for (UINT8 i = 0; i < SPD_MODULE_PART_DDR5; i++) {
    Print(L"%02X", RegData[i]);
  }
  Print(L"\n");

  return Status;
}

EFI_STATUS
SpdGetModuleSerialNumber(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS Status;
  UINT8 RegData[SPD_MODULE_SERIAL];

  for (UINT8 i = 0; i < SPD_MODULE_SERIAL; i++) {
    Status = SpdReadByte(I3cInstanceAddress, SPD_MODULE_SERIAL_NUMBER_0_REG + i, &RegData[i]);
    if (EFI_ERROR(Status)) {
      Print(L"SPD Get Module Serial Number %r\n", Status);
      return Status;
    }
  }
  Print(L"Serial Number: %02X%02X%02X%02X\n", RegData[0], RegData[1], RegData[2], RegData[3]);

  return Status;
}

EFI_STATUS
SpdGetModuleManufacturingDate(
  UINT32 I3cInstanceAddress
)
{
  UINT8 YearByte;
  UINT8 WeekByte;
  EFI_STATUS Status;

  Status = SpdReadByte(I3cInstanceAddress, SPD_MODULE_MANUFACTURING_DATE_0_REG, &YearByte);
  if (EFI_ERROR(Status)) {
    Print(L"Get Module Manufacturing Date %r\n", Status);
    return Status;
  }

  Status = SpdReadByte(I3cInstanceAddress, SPD_MODULE_MANUFACTURING_DATE_1_REG, &WeekByte);
  if (EFI_ERROR(Status)) {
    Print(L"Get Module Manufacturing Date %r\n", Status);
    return Status;
  }

  Print(L"ModDate: %02X/%02X\n", YearByte, WeekByte);

  return Status;
}

EFI_STATUS
SpdGetModuleManufacturingLocation(
  UINT32 I3cInstanceAddress
)
{
  UINT8             RegData;
  EFI_STATUS        Status;

  Status = SpdReadByte(I3cInstanceAddress, SPD_MODULE_MANUFACTURING_LOCATION_REG, &RegData);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Module Manufacturing Location %r\n", Status);
    return Status;
  }

  Print(L"Manufacturing Location: 0x%02X\n", RegData);

  return Status;
}

EFI_STATUS
SpdGetDramManufacturerId(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS Status;
  UINT16  DramManufacturerId;
  DRAM_MANUFACTURER_ID_CODE_0_STRUCT DramManufactureId0Reg;
  DRAM_MANUFACTURER_ID_CODE_1_STRUCT DramManufactureId1Reg;
  //
  // Get DRAM mfg id from SPD 552-553.
  //
  DramManufacturerId = 0;
  Status = SpdReadByte(I3cInstanceAddress, SPD_DRAM_MANUFACTURER_ID_CODE_0_REG, &DramManufactureId0Reg.Data);
  if (EFI_ERROR(Status)) {
    Print(L"Get DRAM Manufacture ID0 %r\n", Status);
  }

  Status = SpdReadByte(I3cInstanceAddress, SPD_DRAM_MANUFACTURER_ID_CODE_1_REG, &DramManufactureId1Reg.Data);
  if (EFI_ERROR(Status)) {
    Print(L"Get DRAM Manufacture ID1 %r\n", Status);
  }

  DramManufacturerId = (UINT16)(DramManufactureId1Reg.Bits.last_non_zero_byte_dram_manufacturer << 8)
    | (UINT16)(DramManufactureId0Reg.Bits.number_of_continuation_codes_dram_manufacturer);

  Print(L"Dram Manufactore ID: 0x%04X\n", DramManufacturerId);

  return Status;
}

EFI_STATUS
SpdGetModuleManufacturerId(
  UINT32 I3cInstanceAddress
)
{

  MODULE_MANUFACTURER_ID_CODE_0_STRUCT ManufactureId0Reg;
  MODULE_MANUFACTURER_ID_CODE_1_STRUCT ManufactureId1Reg;
  EFI_STATUS Status;
  UINT16    Manufactoreid;
  //
  // Get module mfg id from SPD 512-513.
  //

  Manufactoreid = 0;
  Status = SpdReadByte(I3cInstanceAddress, SPD_MODULE_MANUFACTURER_ID_CODE_0_REG, &ManufactureId0Reg.Data);
  if (EFI_ERROR(Status)) {
    Print(L"Get Module Manufacture ID0 %r\n", Status);
  }

  Status = SpdReadByte(I3cInstanceAddress, SPD_MODULE_MANUFACTURER_ID_CODE_1_REG, &ManufactureId1Reg.Data);
  if (EFI_ERROR(Status)) {
    Print(L"Get Module Manufacture ID1 %r\n", Status);
  }

  Manufactoreid = (UINT16)(ManufactureId1Reg.Bits.last_non_zero_byte_module_manufacturer << 8)
    | (UINT16)(ManufactureId0Reg.Bits.number_of_continuation_codes_module_manufacturer);

  Print(L"Module Manufactore ID: 0x%04X\n", Manufactoreid);

  return Status;
}

EFI_STATUS
SpdGetDIMMBusWidth(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS                              Status;
  COMMON_MEMORY_CHANNEL_BUS_WIDTH_STRUCT  ChannelBusWidthReg;
 
  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_MEMORY_CHANNEL_BUS_WIDTH_REG, &ChannelBusWidthReg.Data);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get Primary Bus Width %r\n", Status);
    return Status;
  }

  Print(L"Bus Width Extension %d\n", ChannelBusWidthReg.Bits.bus_width_extension_per_channel_in_bits);
  Print(L"Number Channels %d\n", ChannelBusWidthReg.Bits.number_of_channels_per_dimm);
  Print(L"Prinmary Bus Witdh %d\n", ChannelBusWidthReg.Bits.primary_bus_width_per_channel_in_bits);

  return Status;
}

EFI_STATUS
SpdGetRawCardRefDesign(
  UINT32 I3cInstanceAddress
)
{
  COMMON_REFERENCE_RAW_CARD_USED_STRUCT RawCardRefReg;
  EFI_STATUS Status;

  Status = SpdReadByte(I3cInstanceAddress, SPD_COMMON_REFERENCE_RAW_CARD_USED_REG, &RawCardRefReg.Data);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get Raw Card %r\n", Status);
    return Status;
  } 
  Print(L"Raw Card Design Revision %x Reference Design %x \n",
    RawCardRefReg.Bits.design_revision, RawCardRefReg.Bits.reference_design);

  return Status;
}

EFI_STATUS
SpdGetOperableEndurant(
  UINT32 I3cInstanceAddress
)
{
  UINT8             Endurant = 0;
  UINT8             Operable = 0;
  UINT8             OperableEndurant = 0;
  EFI_STATUS        Status;
  SDRAM_NOMINAL_VOLTAGE_VDD_STRUCT    SdramNomVolVdd;

  Status = SpdReadByte(I3cInstanceAddress, SPD_SDRAM_NOMINAL_VOLTAGE_VDD_REG, &SdramNomVolVdd.Data);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Get Operable Endurant %r\n");
    return Status;
  }

  Operable = SdramNomVolVdd.Bits.operable;
  Endurant = SdramNomVolVdd.Bits.endurant;
  OperableEndurant = (Operable << 2) | Endurant;
  if (OperableEndurant != SPD_VDD_110)
    Print(L"DIMM does not support 1.10v\n");
  else
    Print(L"DIMM Supports 1.10v\n");

  return Status;
}

EFI_STATUS
GetCommonDDR5DIMMConfig(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS  Status;

  Status = SpdGetOperableEndurant(I3cInstanceAddress);
  Status = SpdGetRawCardRefDesign(I3cInstanceAddress);
  Status = SpdGetDIMMBusWidth(I3cInstanceAddress);
  Status = SpdGetModuleManufacturerId(I3cInstanceAddress);
  Status = SpdGetDramManufacturerId(I3cInstanceAddress);
  Status = SpdGetModuleManufacturingLocation(I3cInstanceAddress);
  Status = SpdGetModuleManufacturingDate(I3cInstanceAddress);
  Status = SpdGetModuleSerialNumber(I3cInstanceAddress);
  Status = SpdGetModulePartNum(I3cInstanceAddress);
  Status = SpdGetRcdVendor(I3cInstanceAddress);
  Status = GetRcdDeviceTypeFromSpd(I3cInstanceAddress);
  Status = SpdGetRcdRevision(I3cInstanceAddress);
  Status = SpdGetPmicVendor(I3cInstanceAddress);
  Status = SpdGetTsodMfgId(I3cInstanceAddress);
  Status = SpdGetSpdMfgId(I3cInstanceAddress);
  Status = SpdGetDdrMbistCapability(I3cInstanceAddress);

  return Status;
}

EFI_STATUS
Ddr5MontageSpdHubA0Errata(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS    Status = EFI_SUCCESS;
  UINT8         SPDReg = 0;
  UINT8         DeviceRevision = 0;
  UINT16        VendorId;
  UINT16        DeviceType;

  //
  // Get Internal Thermal Sensor Device ID
  // MR0:MR1
  //
  SpdHubReadByte(I3cInstanceAddress, SPD_MR0_DEVICE_TYPE_MSB, &SPDReg);
  DeviceType = SPDReg << 8;
  SpdHubReadByte(I3cInstanceAddress, SPD_MR1_DEVICE_TYPE_LSB, &SPDReg);
  DeviceType |= (UINT16)SPDReg;
  Print(L"MR0:MR1 %X\n", DeviceType);

  //
  // Get Internal Thermal Sensor Device Revision
  // MR2[5:1]
  //
  SpdHubReadByte(I3cInstanceAddress, SPD_MR2_DEVICE_REVISION, &DeviceRevision);
  DeviceRevision = (DeviceRevision >> 1) & 0x1f;
  Print(L"MR2 Device Revision %d\n", DeviceRevision);

  //
  // Get Internal Thermal Sensor Vendor ID
  //
  SpdHubReadByte(I3cInstanceAddress, SPD_MR3_VENDOR_ID_0, &SPDReg);
  VendorId = SPDReg;
  SpdHubReadByte(I3cInstanceAddress, SPD_MR4_VENDOR_ID_1, &SPDReg);
  VendorId |= (SPDReg << 8);
  Print(L"MR3 VendorID %X\n", VendorId);


  return Status;
}

EFI_STATUS
SpdHubReadByte(
  UINT32  I3cInstanceAddress,
  UINT8   Register,
  UINT8*  Data
)
{
  EFI_STATUS                          Status = EFI_SUCCESS;
  SPD_DDR5_ADDRESS_FIRST_BYTE_STRUCT  SmbAddressData;

  SmbAddressData.Data = 0;

  Status = ProgramSpdPage(I3cInstanceAddress, 0);
  if (EFI_ERROR(Status)) {
    Print(L"ProgramSpdPage Error\n");
    return Status;
  }

  //
  // MemReg: 1 for NVM location(SPD), 0 for internal register
  //
  SmbAddressData.Data = 0;
  SmbAddressData.Bits.MemReg = SPD_INTERNAL_REGISTER;
  SmbAddressData.Bits.Address = Register;

  Status = ReadProcSmb(I3cInstanceAddress, Spd, SmbAddressData.Data, Data);
  if (EFI_ERROR(Status)) {
    Print(L"SpdHubReadByte %r\n", Status);
  }

  return Status;
}

EFI_STATUS
ProgramSpdPage(
  UINT32 I3cInstanceAddress,
  UINT8  SpdPage
)
{
  EFI_STATUS Status;
  SPD_DDR5_MR11_STRUCT                Mr11Data;
  SPD_DDR5_ADDRESS_FIRST_BYTE_STRUCT  SmbAddressData;
  UINT16                              SmbData;

  Mr11Data.Data = 0;
  SmbAddressData.Data = 0;
  SmbData = 0;

  // MemReg should be set to 0 for selecting page
  SmbAddressData.Bits.MemReg = SPD_INTERNAL_REGISTER;
  SmbAddressData.Bits.Address = SMB_MR11_ADDR;

  // Always use 1 Byte addressing
  Mr11Data.Bits.I2cLegacyMode = I2C_LEGACY_MODE;
  Mr11Data.Bits.Page = SpdPage;

  SmbData = Mr11Data.Data;
  Status = WriteProcSmb(I3cInstanceAddress, Spd, SmbAddressData.Data, (UINT8*)&SmbData);
  if (EFI_ERROR(Status)) {
    Print(L"ProgramSpdPage %r\n", Status);
  }
  //Print(L"ProgramSpdPage %X %r\n", SmbAddressData.Data, Status);

  return Status;
}

EFI_STATUS
SpdReadByte(
  UINT32 I3cInstanceAddress,
  UINT16 ByteOffset,
  UINT8* Data
)
{
  EFI_STATUS         Status;
  UINT8              SmbOffset;
  UINT8              SpdPage;
  UINT16             PageOffset;
  SPD_DDR5_ADDRESS_FIRST_BYTE_STRUCT  SmbAddressData;

  Status = EFI_SUCCESS;
  SpdPage = (UINT8)(ByteOffset / SPD_DDR5_PAGE_SIZE);
  PageOffset = SPD_DDR5_PAGE_SIZE * SpdPage;
  SmbAddressData.Data = 0;
  SmbAddressData.Bits.MemReg = SPD_NVM_LOCATION;
  SmbAddressData.Bits.Address = (UINT8)(ByteOffset - PageOffset);
  SmbOffset = SmbAddressData.Data;
  Spd.SpdPage = SpdPage;

  Status = ReadProcSmb(I3cInstanceAddress, Spd, SmbOffset, Data);
  if (EFI_ERROR(Status)) {
    //Print(L"SpdReadByte %r\n", Status);
  }

  return Status;
}

EFI_STATUS
SpdGetBaseModuleType(
  UINT32 I3cInstanceAddress
  )
{
  KEY_BYTE_MODULE_TYPE_STRUCT ModuleTypeReg;
  EFI_STATUS Status;

  Status = SpdReadByte(I3cInstanceAddress, SPD_KEY_BYTE_MODULE_TYPE_REG, &ModuleTypeReg.Data);
  if (!EFI_ERROR(Status)) {
    Print(L"Base Module: %X\n", ModuleTypeReg.Bits.base_module_type);
    Print(L"Hybrid Media: %X , Hybrid: %X\n", ModuleTypeReg.Bits.hybrid_media, ModuleTypeReg.Bits.hybrid);
  }

  return Status;
}

EFI_STATUS
SpdGetModuleType(
  UINT32  I3cInstanceAddress,
  UINT8*  Data
)
{
  EFI_STATUS Status;
  Status = EFI_SUCCESS;

  KEY_BYTE_HOST_BUS_COMMAND_PROTOCOL_TYPE_STRUCT BusCommandProtocolTypeReg;
  Status = SpdReadByte(I3cInstanceAddress, SPD_KEY_BYTE_HOST_BUS_COMMAND_PROTOCOL_TYPE_REG, &BusCommandProtocolTypeReg.Data);
  if (EFI_ERROR(Status)) {
    //Print(L"DIMM Type %X\n", BusCommandProtocolTypeReg.Bits.sdram_module_type);
    Print(L"SPD Get Module Type %r\n", Status);
    return Status;
  }
  *Data = BusCommandProtocolTypeReg.Bits.sdram_module_type;

  return Status;
}

EFI_STATUS
GatherSPDDataDDR5(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS  Status;
  UINTN  SpdSize;
  UINT8* SpdBuf;
  NUMBER_OF_BYTES_IN_SPD_DEVICE_STRUCT SPDReg;

  Status = SpdReadByte(I3cInstanceAddress, SPD_NUMBER_OF_BYTES_IN_SPD_DEVICE_REG, &SPDReg.Data);
  if (EFI_ERROR(Status)) {
    Print(L"SPD Dataa %r\n", Status);
    return Status;
  }

  if (SPDReg.Bits.spd_bytes_total == 1) SpdSize = 256;
  else if (SPDReg.Bits.spd_bytes_total == 2) SpdSize = 512;
  else if (SPDReg.Bits.spd_bytes_total == 3) SpdSize = 1024;

  Print(L"SPD Size %d Bytes\n", SpdSize);
  SpdBuf = AllocateZeroPool(SpdSize);
  if (SpdBuf == NULL) {
    Print(L"Allcate Zeoro Pool Fail\n");
    return EFI_UNSUPPORTED;
  }
  for (UINT16 i = 0; i < SpdSize; i++) {
    Status = SpdReadByte(I3cInstanceAddress, SPD_NUMBER_OF_BYTES_IN_SPD_DEVICE_REG+i, (UINT8*)(SpdBuf+i));
    if (EFI_ERROR(Status)) {
      Print(L"Gather SPD Index %d %r",i,Status);
      break;
    }
    Print(L"%02X",*(UINT8*)(SpdBuf+i));

    if (((1+i) % 16) == 0) Print(L"\n");
    else Print(L" ");
  }
  Print(L"\n");
  if (SpdBuf != NULL) FreePool(SpdBuf);

  return Status;
}

VOID
GatherSPDData(
  VOID
)
{
  EFI_STATUS Status;
  UINT8 DdrType;
  //
  // Initialize common parts of the smbDevice structure for all SPD devices
  //

  ZeroMem(&Spd, sizeof(Spd));
  Spd.compId = SPD;
  Spd.address.controller = PLATFORM_SMBUS_CONTROLLER_PROCESSOR;
  Spd.address.deviceType = DTI_EEPROM;
  Spd.address.I2cTwoBytesMode = I2C_2_BYTES_MODE;

  for (UINT8 i = 0; i < BHS_MAX_SMB_INSTANCE; i++) {
    if (!(I3cDevStatus & ((UINT8)BIT0 << i))) {
      continue;
    }

    for (UINT8 j = 0; j < sizeof(StrapAddress); j++) {
      Spd.address.strapAddress = StrapAddress[j];
      Status = SpdGetModuleType(I3cSpdBusBaseAddress[i], &DdrType);
      if (!EFI_ERROR(Status)) {
        Print(L"Channel %d-%d DDR Type %x\n", i, Spd.address.strapAddress, DdrType);
        Status = SpdGetBaseModuleType(I3cSpdBusBaseAddress[i]);
        if (EFI_ERROR(Status)) {
          continue;
        }
        Status = Ddr5MontageSpdHubA0Errata(I3cSpdBusBaseAddress[i]);
        if (EFI_ERROR(Status)) {
          continue;
        }
        Status = GetCommonDDR5DIMMConfig(I3cSpdBusBaseAddress[i]);
        if (EFI_ERROR(Status)) {
          continue;
        }
        Status = GatherSPDDataDDR5(I3cSpdBusBaseAddress[i]);
        if (EFI_ERROR(Status)) {
          continue;
        }
      } else {
        //Print(L"NON\n");
      }
    }
  }
}

EFI_STATUS
SpdEnumeration(
  VOID
)
{
  EFI_STATUS Status;
  DEVICE_CAPABILITIES_I3C0_STRUCT   DevCapabilites;
  UINT8 Data;
  UINT8 DataLength;

  //Save Periodic poll command enable status
  for (UINT8 i = 0; i < BHS_MAX_SMB_INSTANCE; i++) {
    PpCmdEnblReg[i] = MmioRead16(I3cSpdBusBaseAddress[i] + 0x26C);
    MmioWrite16(I3cSpdBusBaseAddress[i] + 0x26C, 0x0000);
  }

  for (UINT8 i=0; i<BHS_MAX_SMB_INSTANCE; i++) {
    //if (I3cDevStatus & ((UINT8)BIT0 << i)) {
      DevCapabilites.Data = MmioRead32(I3cSpdBusBaseAddress[i] + DEVICE_CAPABILITIES_SB_I3C0_REG);
      //Print(L"DetectSPD %d - 0x%04X\n", i, DevCapabilites.Data);
      if (DevCapabilites.Bits.combo_command == 0) {
        Print(L"I3C Instance %d: COMBO_COMMAND is not supported\n", i);
        continue;
      }
      //Print(L"Instance %d - 0x%X\n", i, I3cSpdBusBaseAddress[i]); //brnxxxx 250813
      //ResetProcSmb(I3cSpdBusBaseAddress[i]);
      //I3cBusReset(I3cSpdBusBaseAddress[i]);
      Print(L"Instance %d\n", i);
      Data = 0;
      DataLength = BROADCAST_DATA_LENGTH;
      Status = SendCccCmd(I3cSpdBusBaseAddress[i], CCC_BROADCAST_SETAASA, AttrCccWrite, & Data, & DataLength);
      Print(L"Send SETAASA Cmd %r\n", Status);
      //if (EFI_ERROR(Status)) {
      //  Print(L"Send CCC Cmd fail %r\n", Status);
      //  continue;
      //}
      //else {
      //}
      //Status = InitSpdAddressingMode(I3cSpdBusBaseAddress[i]);
    //}
  }

  //Restore Periodic poll command enable status
  for (UINT8 i = 0; i < BHS_MAX_SMB_INSTANCE; i++) {
    MmioWrite16(I3cSpdBusBaseAddress[i] + 0x26C, PpCmdEnblReg[i]);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
InitI3CDevices(
  void
)
{
  InitI3cDone = FALSE;
  I3cDevStatus = 0;

  if (VTD_SVID == PciRead32(PCI_LIB_ADDRESS(0, 0, 0, SVID_OFFSET))) {
    PciExpressBaseAddress = PciRead32(PCI_LIB_ADDRESS(0, 0, 0, MMCFG_OFFSET));
  }
  else
    return EFI_UNSUPPORTED;

  if (RACU_SVID == PciRead32(PCI_LIB_ADDRESS(RACU_BUS, RACU_DEV, RACU_FUN, SVID_OFFSET))) {
  
    ScfBaseAddress = PciRead32(PCI_LIB_ADDRESS(RACU_BUS, RACU_DEV, RACU_FUN, SCF_MMIO_OFFSET)) << 23 |
      (PciRead32(PCI_LIB_ADDRESS(RACU_BUS, RACU_DEV, RACU_FUN, SCF_BAR_OFFSET))& 0x000007FF) << 12;

    I3cSpdBusBaseAddress[0] = ScfBaseAddress + I3C_SPD_BUS0_ADDRESS;
    I3cSpdBusBaseAddress[1] = ScfBaseAddress + I3C_SPD_BUS1_ADDRESS;
    I3cSpdBusBaseAddress[2] = ScfBaseAddress + I3C_SPD_BUS2_ADDRESS;
    I3cSpdBusBaseAddress[3] = ScfBaseAddress + I3C_SPD_BUS3_ADDRESS;

    for(UINT8 i=0 ; i<BHS_MAX_SMB_INSTANCE; i++) {
      if (MmioRead8(I3cSpdBusBaseAddress[i]) != I3C_HCI_VERSION) {
        I3cSpdBusBaseAddress[i] = 0;
      }
    }
    //Print(L"spd0 0x%04x\n", I3cSpdBus0BaseAddress);
    //Print(L"spd1 0x%04x\n", I3cSpdBus1BaseAddress);
    //Print(L"spd2 0x%04x\n", I3cSpdBus2BaseAddress);
    //Print(L"spd3 0x%04x\n", I3cSpdBus3BaseAddress);
  }
  else
    return EFI_UNSUPPORTED;
  
  //Print(L"Check I3C mode\n");
  CheckI3cConfig();

  InitI3cDone = TRUE;
  //SpdEnumeration();
  GatherSPDData();

  return EFI_SUCCESS;
}

EFI_STATUS
InitSpdAddressingMode(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS                          Status = EFI_SUCCESS;
  SMB_DEVICE_STRUCT                   SpdDev;
  SPD_DDR5_MR11_STRUCT                Mr11Data;
  SPD_DDR5_ADDRESS_FIRST_BYTE_STRUCT  AddressData;
  UINT8                               SpdI2cAddressingMode;

  SpdI2cAddressingMode = I2C_2_BYTES_MODE;

  //
  // Fill out relevant data for a SPD SMbus transaction
  //
  SpdDev.compId = SPD;
  SpdDev.address.controller = PLATFORM_SMBUS_CONTROLLER_PROCESSOR;
  SpdDev.address.deviceType = DTI_EEPROM;
  SpdDev.address.SmbSocket = 0;
  SpdDev.address.I2cTwoBytesMode = SpdI2cAddressingMode;

  //
  // Init MR11 addressing mode and set page 0
  //
  AddressData.Data = 0;
  AddressData.Bits.MemReg = SPD_INTERNAL_REGISTER;
  AddressData.Bits.Address = SMB_MR11_ADDR;
  Print(L"Address Data %x\n", AddressData.Data);
  for (UINT8 i=0; i<MAX_CH_DDR; i++) {
    Print(L"Strap Address %x\n",StrapAddress[i]); //brnxxxx 250813
    SpdDev.address.strapAddress = StrapAddress[i];
    Mr11Data.Data = 0;
    Status = ReadProcSmb(I3cInstanceAddress, SpdDev, AddressData.Data, &Mr11Data.Data);

    Print(L"Mr11Data 0x%x\n", Mr11Data.Data);
    Print(L"Mr11Data i2c legacy mode 0x%x\n", Mr11Data.Bits.I2cLegacyMode);
    Print(L"Mr11Data i2c page 0x%x\n", Mr11Data.Bits.Page);
    if ((Status == EFI_SUCCESS) && ((Mr11Data.Bits.I2cLegacyMode != SpdI2cAddressingMode) || (Mr11Data.Bits.Page != 0))) {
      //
      // Init addressing mode and page 0
      //
      Print(L"Write Addressing mode and page 0\n");
      Mr11Data.Bits.I2cLegacyMode = SpdI2cAddressingMode;
      Mr11Data.Bits.Page = 0;  //Initial to page 0
      Status = WriteProcSmb(I3cInstanceAddress, SpdDev, AddressData.Data, &Mr11Data.Data);
      if (!EFI_ERROR(Status)) {
        Print(L"Init SpdHub %d addressing mode %d success!\n", i, SpdI2cAddressingMode);
        SpdDev.address.strapAddress = StrapAddress[i];
        Mr11Data.Data = 0;
        Status = ReadProcSmb(I3cInstanceAddress, SpdDev, AddressData.Data, &Mr11Data.Data);
        if (!EFI_ERROR(Status)) {
          Print(L"Mr11Data 0x%x\n", Mr11Data.Data);
          Print(L"Mr11Data i2c legacy mode 0x%x\n", Mr11Data.Bits.I2cLegacyMode);
          Print(L"Mr11Data i2c page 0x%x\n", Mr11Data.Bits.Page);
        }
      }
      else {
        Print(L"Init SpdHub %d addressing mode %d failed!\n", i, SpdI2cAddressingMode);
      }
    }
  }

  return Status;
}

EFI_STATUS
ReadProcSmb(
  UINT32             I3cInstanceAddress,
  SMB_DEVICE_STRUCT  Dev,
  UINT8              ByteOffset,
  volatile UINT8*    Data
)
{
  EFI_STATUS  Status = EFI_SUCCESS;
  UINT16      Data16 = 0;

  Status = SmbReadCommon(I3cInstanceAddress, Dev, ByteOffset, &Data16);
  if (EFI_ERROR(Status)) {
    //Print(L"Resume Smb %r\n", ResumeProcSmb(I3cInstanceAddress));
    ResumeProcSmb(I3cInstanceAddress);
  }
 
  *Data = (UINT8)Data16;

  return Status;
}

EFI_STATUS
SmbReadCommon(
  UINT32             I3cInstanceAddress,
  SMB_DEVICE_STRUCT  Dev,
  UINT8              ByteOffset,
  volatile UINT16*   Data
)
{
  EFI_STATUS                              Status = EFI_SUCCESS;
  RESPONSE_QUEUE_PORT_I3C0_STRUCT         I3cResp;
  UINT8                                   TransactionID;
  UINT8                                   I2cOrI3c;
  UINT8                                   SubOffsetLen;
  UINT32                                  SubOffset;
  COMMAND_QUEUE_PORT_I3C0_STRUCT          CmdPort;
  COMBO_TRANSFER_COMMAND_LOW_WITHOUT_DAT  ComboCommandLow;
  COMBO_TRANSFER_COMMAND_HIGH_WITHOUT_DAT ComboCommandHigh;
  // Same address with RX_DATA_PORT and TX_DATA_PORT, single bi-direction design
  volatile DATA_PORT_I3C0_STRUCT          DataPort;
  INTR_STATUS_I3C0_STRUCT                 I3cStatus;

  TransactionID = TidRead;
  I2cOrI3c = I3C_DEVICE;
  SubOffsetLen = SUBOFFSET_16_BIT;
  SubOffset = (Dev.SpdPage | (ByteOffset << 8));  // The low byte should follow the definition of SPD_DDR5_ADDRESS_SECOND_BYTE_STRUCT
  //Print(L"SmbReadCommon Suboffset %x\n", SubOffset);
  //
  // Form read command
  //
  ComboCommandLow.Data = 0x0;
  ComboCommandLow.Bits.com_attr = I3C_COM_ATTR_WWR_COMBO_XFER;  
  ComboCommandLow.Bits.tid = TransactionID;
  ComboCommandLow.Bits.i2cni3c = I2cOrI3c;
  ComboCommandLow.Bits.slave_address = (UINT32)((Dev.address.deviceType << I3C_STRAP_ADDRESS_OFFSET) | Dev.address.strapAddress);
  
  ComboCommandLow.Bits.suboffset_16_bit = SubOffsetLen;
  ComboCommandLow.Bits.mode_speed = I3cSdr0I2cFm;
  ComboCommandLow.Bits.rnw = RNW_READ; 
  ComboCommandLow.Bits.roc = ROC_REQUIRED; 
  ComboCommandLow.Bits.toc = TOC_STOP;

  ComboCommandHigh.Data = 0x0;
  ComboCommandHigh.Bits.offset_suboffset = SubOffset;

  if (Dev.compId == MTS) {
    ComboCommandHigh.Bits.data_length = 0x2;
  }
  else {
    ComboCommandHigh.Bits.data_length = 1;
  }

  CmdPort.Data = 0x0;
  CmdPort.Bits.command = ComboCommandLow.Data;  //write Low data
  //Print(L"Low Command %x\n", CmdPort.Bits.command);
  Status = WaitForHostNotBusyTarget(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {

    return EFI_DEVICE_ERROR;
  }
  MmioWrite32(I3cInstanceAddress + COMMAND_QUEUE_PORT_I3C0_REG, CmdPort.Bits.command);

  CmdPort.Bits.command = ComboCommandHigh.Data; //write high data
  //Print(L"High Command %x\n", CmdPort.Bits.command);
  Status = WaitForHostNotBusyTarget(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {

    return EFI_DEVICE_ERROR;
  }
  MmioWrite32(I3cInstanceAddress + COMMAND_QUEUE_PORT_I3C0_REG, CmdPort.Bits.command);

  Status = WaitForWriteToCompleteTarget(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  Status = WaitForDataReadyRead(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // If read data is valid
  //
  I3cStatus.Data = MmioRead32(I3cInstanceAddress + INTR_STATUS_I3C0_REG);
  if ((I3cStatus.Bits.rx_thld_stat == 1) && (I3cStatus.Bits.transfer_err_stat == 0)) {

    DataPort.Data = MmioRead32(I3cInstanceAddress + DATA_PORT_I3C0_REG);

    if (Dev.compId == MTS) {
      *Data = (UINT16)(DataPort.Bits.data_port & WORD_MASK); //lsb + msb
    }
    else {
      *Data = (UINT16)(DataPort.Bits.data_port & BYTE_MASK); //lsb
    }
  }
  else {
    //Print(L"Read Data is non-Valid\n");
    Status = EFI_DEVICE_ERROR;
  }

  //
  // Check response status
  //
  I3cResp.Data = MmioRead32(I3cInstanceAddress + RESPONSE_QUEUE_PORT_I3C0_REG);
  if ((I3cResp.Bits.tid != TransactionID) || I3cResp.Bits.err_status) {
    Status = EFI_DEVICE_ERROR;
  }

  return Status;
}

EFI_STATUS
WriteProcSmb(
  UINT32             I3cInstanceAddress,
  SMB_DEVICE_STRUCT  Dev,
  UINT8              ByteOffset,
  volatile UINT8*    Data
)
{
  EFI_STATUS  Status = EFI_SUCCESS;
  UINT16      Data16 = 0;

  Status = SmbWriteCommon(I3cInstanceAddress, Dev, ByteOffset, &Data16);
  if (EFI_ERROR(Status)) {
    Status = EFI_SUCCESS;
    Data16 = 0;
  }

  *Data = (UINT8) Data16;

  return  Status;
}

EFI_STATUS
SmbWriteCommon(
  UINT32             I3cInstanceAddress,
  SMB_DEVICE_STRUCT  Dev,
  UINT8              ByteOffset,
  volatile UINT16*   Data
)
{
  EFI_STATUS                                      Status = EFI_SUCCESS;
  RESPONSE_QUEUE_PORT_I3C0_STRUCT                 I3cResp;
  UINT8                                           TransactionID;
  UINT8                                           I2cOrI3c;
  COMMAND_QUEUE_PORT_I3C0_STRUCT                  CmdPort;
  REGULAR_DATA_TRANSFER_COMMAND_LOW_WITHOUT_DAT   RegularCommandLow;
  REGULAR_DATA_TRANSFER_COMMAND_HIGH_WITHOUT_DAT  RegularCommandHigh;
  DATA_PORT_I3C0_STRUCT                           DataPort;

  TransactionID = TidWrite;
  I2cOrI3c = I3C_DEVICE;
  //
  // Form write command
  //
  RegularCommandLow.Data = 0x0;
  RegularCommandLow.Bits.com_attr = I3C_COM_ATTR_XFER;  // I3C_COM_ATTR_XFER             0x0  // Regular Transfer
  RegularCommandLow.Bits.tid = TransactionID;           // Transaction ID field is used as identification tag for the command.
  RegularCommandLow.Bits.i2cni3c = I2cOrI3c;            // 0x0: I3C device 0x1: I2C device
  //RegularCommandLow.Bits.cmd // CMD field is not valid
  RegularCommandLow.Bits.cp = CP_TRANFSER;              // 0x0: TRANFSER: Describes SDR transfer. CMD field is not valid.
  RegularCommandLow.Bits.slave_address = (UINT32)((Dev.address.deviceType << I3C_STRAP_ADDRESS_OFFSET) | Dev.address.strapAddress);
  RegularCommandLow.Bits.mode_speed = I3cSdr0I2cFm;
  RegularCommandLow.Bits.rnw = RNW_WRITE;               // 0x0: WRITE: Write transfer
  RegularCommandLow.Bits.roc = ROC_REQUIRED;            // 0x1: REQUIRED: Response Status is required
  RegularCommandLow.Bits.toc = TOC_STOP;                // 0x1: STOP: Stop (P) is issued at end of the transfer

  RegularCommandHigh.Data = 0x0;

  CmdPort.Data = 0x0;
  CmdPort.Bits.command = RegularCommandLow.Data;

  //
  // data to write
  //
  DataPort.Data = 0;

  if (Dev.compId == MTS) {
    RegularCommandHigh.Bits.data_length = ONE_BYTE_ADDRESSING + 2;  // 1 Byte addressing + 2 bytes data
    DataPort.Bits.data_port = ((UINT32)ByteOffset) | ((UINT32)*Data << 8);
  }
  else {
    // Use 2 bytes addressing only when accessing the DDR5 SPD data
    if (((I2cOrI3c == I3C_DEVICE) || Dev.address.I2cTwoBytesMode) && (Dev.address.deviceType == DTI_EEPROM)) {
      RegularCommandHigh.Bits.data_length = TWO_BYTE_ADDRESSING + 1;  // 2 Byte addressing + 1 byte data
      DataPort.Bits.data_port = ((UINT32)ByteOffset) | ((UINT32)Dev.SpdPage << 8) | ((UINT32)(*Data & BYTE_MASK) << 16);
    }
    else {
      RegularCommandHigh.Bits.data_length = ONE_BYTE_ADDRESSING + 1;  // 1 Byte addressing + 1 byte data
      DataPort.Bits.data_port = ((UINT32)ByteOffset) | ((UINT32)(*Data & BYTE_MASK) << 8);
    }
  }

  Status = CheckTxFiFoSpace(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  MmioWrite32(I3cInstanceAddress + COMMAND_QUEUE_PORT_I3C0_REG, DataPort.Data);
  Status = WaitForHostNotBusyTarget(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {

    return EFI_DEVICE_ERROR;
  }

  //
  // Send command
  //
  // Low 32 bits
  Status = WaitForHostNotBusyTarget(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {

    return EFI_DEVICE_ERROR;
  }
  MmioWrite32(I3cInstanceAddress + COMMAND_QUEUE_PORT_I3C0_REG, CmdPort.Bits.command);
  //
  // High 32 bits
  CmdPort.Bits.command = RegularCommandHigh.Data;
  Status = WaitForHostNotBusyTarget(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {

    return EFI_DEVICE_ERROR;
  }
  MmioWrite32(I3cInstanceAddress + COMMAND_QUEUE_PORT_I3C0_REG, CmdPort.Bits.command);

  Status = WaitForWriteToCompleteTarget(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Check response status
  //
  I3cResp.Data = MmioRead32(I3cInstanceAddress + RESPONSE_QUEUE_PORT_I3C0_REG);
  if ((I3cResp.Bits.tid != TransactionID) || I3cResp.Bits.err_status) {
    Status = EFI_DEVICE_ERROR;
  }

  return Status;
}

EFI_STATUS
ResetProcSmb(
  UINT32 I3cInstanceAddress
)
{

  EFI_STATUS Status = EFI_SUCCESS;
  UINT32                                  Timeout;
  COMMON_DEVICE_CTRL_I3C0_STRUCT          I3cComDevCtrl;
  DEVICE_CONTROL_I3C0_STRUCT              I3cDevCtrl;
  DATA_BUFFER_THLD_CTRL_I3C0_STRUCT       I3cDataThld;
  QUEUE_THLD_CTRL_I3C0_STRUCT             I3cQueueThld;
  RESET_CTRL_I3C0_STRUCT                  ResetCtrl;
  SCL_LOW_MST_EXT_TIMEOUT_I3C0_STRUCT     I3cLowTimeout;
  IBI_NOTIFY_CTRL_I3C0_STRUCT             IbiNotify;
  SDA_HOLD_SWITCH_DLY_TIMING_I3C0_STRUCT  I3cSdaHold;
  SCL_I3C_OD_TIMING_I3C0_STRUCT           I3cOd;
  SCL_I3C_PP_TIMING_I3C0_STRUCT           I3cPp;
  SCL_I2C_FM_TIMING_I3C0_STRUCT           I2cFm;

  //
  // Disable I3C
  //
  I3cDevCtrl.Data = MmioRead32(I3cInstanceAddress + DEVICE_CONTROL_I3C0_REG);
  I3cDevCtrl.Bits.enable = I3C_DISABLE;
  MmioWrite32(I3cInstanceAddress + DEVICE_CONTROL_I3C0_REG, I3cDevCtrl.Data);

  //reset the sts and fifo
  ResetCtrl.Data = MmioRead32(I3cInstanceAddress + RESET_CTRL_I3C0_REG);
  ResetCtrl.Bits.soft_rst = I3C_ENABLE;
  ResetCtrl.Bits.cmd_queue_rst = I3C_ENABLE;
  ResetCtrl.Bits.resp_queue_rst = I3C_ENABLE;
  ResetCtrl.Bits.tx_fifo_rst = I3C_ENABLE;
  ResetCtrl.Bits.rx_fifo_rst = I3C_ENABLE;
  ResetCtrl.Bits.ibi_queue_rst = I3C_ENABLE;
  MmioWrite32(I3cInstanceAddress + RESET_CTRL_I3C0_REG, ResetCtrl.Data);

  //
  // Wait for reset completion.
  //
  Timeout = I3C_TIMEOUT;

  do {
    ResetCtrl.Data = MmioRead32(I3cInstanceAddress + RESET_CTRL_I3C0_REG);

    //MicroSecondDelay(1);
    gBS->Stall(1);
    Timeout--;

    if (Timeout <= 0) {
      Status = EFI_TIMEOUT;
      break;
    }

  } while ((ResetCtrl.Bits.soft_rst == 1) || (ResetCtrl.Bits.cmd_queue_rst == 1) || (ResetCtrl.Bits.resp_queue_rst == 1) ||
    (ResetCtrl.Bits.tx_fifo_rst == 1) || (ResetCtrl.Bits.rx_fifo_rst == 1) || (ResetCtrl.Bits.ibi_queue_rst == 1));


  I3cQueueThld.Data = MmioRead32(I3cInstanceAddress + QUEUE_THLD_CTRL_I3C0_REG);
  //set resp buf thld to 0  [15:8]
  I3cQueueThld.Bits.resp_buf_thld = 0;
  //set cmd empty thld buf to 1  [7:0]
  I3cQueueThld.Bits.cmd_empty_buf_thld = 1;
  MmioWrite32(I3cInstanceAddress + QUEUE_THLD_CTRL_I3C0_REG, I3cQueueThld.Data);


  I3cDataThld.Data = MmioRead32(I3cInstanceAddress + DATA_BUFFER_THLD_CTRL_I3C0_REG);
  //
  // set resp_buf_thld as 0 to identify every transaction is ready for reading/writing
  // set RX/TX Start/buf thld as n to support n+1 byte Read/Write
  // The supported values for RX_START_THLD/TX_START_THLD/RX_BUF_THLD/TX_BUF_THLD are:
  //   000 - 1;  001 - 4;  010 - 8;   011 - 16
  //   100 - 32; 101 - 64; 110 - 128; 111 - 256
  //
  //set RX Start thld to 0  [26:24]
  I3cDataThld.Bits.rx_start_thld = 0;
  //set RX buf thld to 0  [10:8]
  I3cDataThld.Bits.rx_buf_thld = 0;
  //set TX Start THLD to 0  [18:16]
  I3cDataThld.Bits.tx_start_thld = 0;
  //set tX buf thld to 0  [2:0]
  I3cDataThld.Bits.tx_buf_thld = 0;
  MmioWrite32(I3cInstanceAddress + DATA_BUFFER_THLD_CTRL_I3C0_REG, I3cDataThld.Data);

  // Enable I3C
  I3cDevCtrl.Bits.enable= I3C_ENABLE;
  MmioWrite32(I3cInstanceAddress + DEVICE_CONTROL_I3C0_REG, I3cDevCtrl.Data);
 
  //
  // Enable all the states
  //
  MmioWrite32(I3cInstanceAddress + INTR_STATUS_ENABLE_I3C0_REG, I3C_INTR_STATUS_ENABLE_ALL);

  //
  // Set Device NACK Retry Count and reject IBI
  //
  I3cComDevCtrl.Data = MmioRead32(I3cInstanceAddress + COMMON_DEVICE_CTRL_I3C0_REG);
  I3cComDevCtrl.Bits.dev_nack_retry_cnt = MAX_DEV_NACK_RETRY_CNT;
  I3cComDevCtrl.Bits.sir_reject = 1;
  MmioWrite32(I3cInstanceAddress + COMMON_DEVICE_CTRL_I3C0_REG, I3cComDevCtrl.Data);

  IbiNotify.Data = MmioRead32(I3cInstanceAddress + IBI_NOTIFY_CTRL_I3C0_REG);
  IbiNotify.Bits.notify_sir_rejected = 0;
  MmioWrite32(I3cInstanceAddress + IBI_NOTIFY_CTRL_I3C0_REG, IbiNotify.Data);

  //
  // Program SCL Low Timeout value
  //

  I3cLowTimeout.Data = MmioRead32(I3cInstanceAddress + SCL_LOW_MST_EXT_TIMEOUT_I3C0_REG);
  I3cLowTimeout.Bits.scl_low_mst_timeout_count = SCL_LOW_MST_TIMEOUT_COUNT;
  MmioWrite32(I3cInstanceAddress + SCL_LOW_MST_EXT_TIMEOUT_I3C0_REG, I3cLowTimeout.Data);

  //
  // Program SDA tx hold value
  //
  I3cSdaHold.Data = MmioRead32(I3cInstanceAddress + SDA_HOLD_SWITCH_DLY_TIMING_I3C0_REG);
  I3cSdaHold.Bits.sda_tx_hold = I3C_SDA_TX_HOLD;
  MmioWrite32(I3cInstanceAddress + SDA_HOLD_SWITCH_DLY_TIMING_I3C0_REG, I3cSdaHold.Data);

  //
  // Program timing registers
  //

  I3cPp.Data = MmioRead32(I3cInstanceAddress + SCL_I3C_PP_TIMING_I3C0_REG);
  I3cPp.Bits.i3c_pp_lcnt = 6;
  I3cPp.Bits.i3c_pp_hcnt = 5;
  MmioWrite32(I3cInstanceAddress + SCL_I3C_PP_TIMING_I3C0_REG, I3cPp.Data);

  I3cOd.Data = MmioRead32(I3cInstanceAddress + SCL_I3C_OD_TIMING_I3C0_REG);
  I3cOd.Bits.i3c_od_lcnt = 0x3c;
  I3cOd.Bits.i3c_od_hcnt = 0x28;
  MmioWrite32(I3cInstanceAddress + SCL_I3C_OD_TIMING_I3C0_REG, I3cOd.Data);

  I2cFm.Data = MmioRead32(I3cInstanceAddress + SCL_I2C_FM_TIMING_I3C0_REG);
  I2cFm.Bits.i2c_fm_lcnt = 0x3c;
  I2cFm.Bits.i2c_fm_hcnt = 0x28;
  MmioWrite32(I3cInstanceAddress + SCL_I2C_FM_TIMING_I3C0_REG, I2cFm.Data);

  Print(L"ResetProcSmb %r\n", Status);
  return Status;
}

EFI_STATUS
I3cBusReset(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS                  Status;
  UINT32                      Timeout;
  RESET_CTRL_I3C0_STRUCT      ResetCtrl;
  INTR_STATUS_I3C0_STRUCT     I3cStatus;

  Status = EFI_SUCCESS;
  //
  // Perform the SCL LOW TIMEOUT Reset, setup reset pattern and send Reset
  //
  ResetCtrl.Data = MmioRead32(I3cInstanceAddress + RESET_CTRL_I3C0_REG);
  ResetCtrl.Bits.bus_reset_type = (BIT1 + BIT0); // SCL Low Timeout Reset
  ResetCtrl.Bits.bus_reset = I3C_ENABLE;
  MmioWrite32(I3cInstanceAddress + RESET_CTRL_I3C0_REG, ResetCtrl.Data);

  //
  // Wait for bus reset completion.
  //
  Timeout = I3C_TIMEOUT;
  do {
    I3cStatus.Data = MmioRead32(I3cInstanceAddress + INTR_STATUS_I3C0_REG);

    //MicroSecondDelay(1);
    gBS->Stall(1000);
    Timeout--;

    if (Timeout <= 0) {
      Status = EFI_TIMEOUT;
      break;
    }

  } while (I3cStatus.Bits.bus_reset_done_stat == 0);

  if (I3cStatus.Bits.bus_reset_done_stat == 1) {
    // write 1 to clear
    MmioWrite32(I3cInstanceAddress + INTR_STATUS_I3C0_REG, I3cStatus.Data);;
  }

  Print(L"I3cBusReset %r\n", Status);
  return Status;
}

EFI_STATUS
ResumeProcSmb(
  UINT32 I3cInstanceAddress
)
{
  EFI_STATUS                  Status;
  UINT32                      Timeout;
  DEVICE_CONTROL_I3C0_STRUCT  I3cDevCtrl;
  RESET_CTRL_I3C0_STRUCT      ResetCtrl;
  INTR_STATUS_I3C0_STRUCT     I3cStatus;

  Status = EFI_SUCCESS;


  // reset queue and fifo
  //ResetCtrl.Data = UsraCsrRead(Socket, Instance, I3cResetReg);
  ResetCtrl.Data = MmioRead32(I3cInstanceAddress + RESET_CTRL_I3C0_REG);
  ResetCtrl.Bits.cmd_queue_rst = I3C_ENABLE;
  ResetCtrl.Bits.resp_queue_rst = I3C_ENABLE;
  ResetCtrl.Bits.tx_fifo_rst = I3C_ENABLE;
  ResetCtrl.Bits.rx_fifo_rst = I3C_ENABLE;
  ResetCtrl.Bits.ibi_queue_rst = I3C_ENABLE;
  MmioWrite32(I3cInstanceAddress + RESET_CTRL_I3C0_REG, ResetCtrl.Data);

  //
  // Wait for queue and fifo reset completion.
  //
  Timeout = I3C_TIMEOUT;

  do {
    ResetCtrl.Data = MmioRead32(I3cInstanceAddress + RESET_CTRL_I3C0_REG);

    //MicroSecondDelay(1);
    gBS->Stall(100);
    Timeout--;

    if (Timeout <= 0) {
      Status = EFI_TIMEOUT;
      break;
    }

  } while ((ResetCtrl.Bits.cmd_queue_rst == 1) || (ResetCtrl.Bits.resp_queue_rst == 1) || (ResetCtrl.Bits.tx_fifo_rst == 1) ||
    (ResetCtrl.Bits.rx_fifo_rst == 1) || (ResetCtrl.Bits.ibi_queue_rst == 1));

  //
  // Check error status
  //
  I3cStatus.Data = MmioRead32(I3cInstanceAddress + INTR_STATUS_I3C0_REG);

  if (I3cStatus.Bits.transfer_err_stat == 1) {
    // write 1 to clear
    MmioWrite32(I3cInstanceAddress + INTR_STATUS_I3C0_REG, I3cStatus.Data);

  }

  //
  // Resume I3C
  //
  I3cDevCtrl.Data = MmioRead32(I3cInstanceAddress + DEVICE_CONTROL_I3C0_REG);
  I3cDevCtrl.Bits.resume = 1;
  MmioWrite32(I3cInstanceAddress + DEVICE_CONTROL_I3C0_REG, I3cDevCtrl.Data);

  return Status;
}
