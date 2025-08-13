

#include "DimmView.h"
#include "Spd.h"
#include "I3cAccess.h"
#include "I3C0.h"
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
UINT8   StrapAddress[3] = { 0, 2, 4 };
UINT16  PpCmdEnblReg[4];



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
          Print(L"I3C Instance %d has I3C Devices\n", i);
          CheckI3cFreq(I3cSpdBusBaseAddress[i]);
          I3cDevStatus |= BIT0 << i;
      }
    }
    else {
      Print(L"I3C Instance %d is unsupported\n", i);
      return EFI_UNSUPPORTED;
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
CheckResponseStatus(
  UINT32 I3cInstanceAddress
)
{
  UINT32                                  Timeout;
  RESPONSE_QUEUE_PORT_I3C0_STRUCT         I3cResp;
  EFI_STATUS                              Status = EFI_DEVICE_ERROR;

  Timeout = 10000;

  //
  // Wait for there is space in the command queue
  //
  do {
    I3cResp.Data = MmioRead32(I3cInstanceAddress + RESPONSE_QUEUE_PORT_I3C0_REG);

    if (I3cResp.Bits.err_status == 0) {
      Status = EFI_SUCCESS;
      //Print(L"Response Queue No Error\n");
      break;
    }

    //MicroSecondDelay(1);
    gBS->Stall(1000);
    Timeout--;

    // Wait for timeout
  } while (Timeout > 0);

  if (Timeout <= 0) {
    Status = EFI_TIMEOUT;
  }

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

    // Wait for timeout
  } while (Timeout > 0);

  if (Timeout <= 0) {
    Status = EFI_TIMEOUT;
  }

  
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

    // Wait for timeout
  } while (Timeout > 0);

  if (Timeout <= 0) {
    Status = EFI_TIMEOUT;
  }

  return Status;

}

EFI_STATUS
WaitForDataReadyRead(
  UINT32 I3cInstanceAddress
)
{
  UINT32                      Timeout;
  INTR_STATUS_I3C0_STRUCT     I3cStatus;
  EFI_STATUS                  Status = EFI_DEVICE_ERROR;

  Timeout = 100;
  do {
    I3cStatus.Data = MmioRead32(I3cInstanceAddress + INTR_STATUS_I3C0_REG);

    //MicroSecondDelay(1);
    gBS->Stall(1);
    Timeout--;

    if (Timeout <= 0) {
      Status = EFI_TIMEOUT;
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

  Status = CheckResponseStatus(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
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
    if (I3cDevStatus & ((UINT8)BIT0 << i)) {
      DevCapabilites.Data = MmioRead32(I3cSpdBusBaseAddress[i] + DEVICE_CAPABILITIES_SB_I3C0_REG);
      //Print(L"DetectSPD %d - 0x%04X\n", i, DevCapabilites.Data);
      if (DevCapabilites.Bits.combo_command == 0) {
        Print(L"I3C Instance %d: COMBO_COMMAND is not supported", i);
        //return EFI_UNSUPPORTED;
        continue;
      }

      Data = 0;
      DataLength = BROADCAST_DATA_LENGTH;
      Status = SendCccCmd(I3cSpdBusBaseAddress[i], CCC_BROADCAST_SETAASA, AttrCccWrite, & Data, & DataLength);
      if (EFI_ERROR(Status)) {
        Print(L"Send CCC Cmd fail EFI DEVICE ERROR %d\n", i);
        //return EFI_DEVICE_ERROR;
        continue;
      }

      Status = InitSpdAddressingMode(I3cSpdBusBaseAddress[i]);
  
    }
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
  
  Print(L"Check I3C mode\n");
  CheckI3cConfig();

  InitI3cDone = TRUE;

  SpdEnumeration();

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

  for (UINT8 i=0; i<MAX_CH_DDR; i++) {
    SpdDev.address.strapAddress = StrapAddress[i];
    Mr11Data.Data = 0;
    Status = ReadProcSmb(I3cInstanceAddress, SpdDev, AddressData.Data, &Mr11Data.Data);

    if ((Status == EFI_SUCCESS) && ((Mr11Data.Bits.I2cLegacyMode != SpdI2cAddressingMode) || (Mr11Data.Bits.Page != 0))) {
      //
      // Init addressing mode and page 0
      //
      Mr11Data.Bits.I2cLegacyMode = SpdI2cAddressingMode;
      Mr11Data.Bits.Page = 0;  //Initial to page 0
      //Status = WriteSpdRegTarget(SpdDev, AddressData.Data, &Mr11Data.Data);
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
    Status = EFI_SUCCESS;
    Data16 = 0;
  }

  *Data = (UINT8) Data16;

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
  //UINT32                                  Timeout;
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
  Status = WaitForHostNotBusyTarget(I3cInstanceAddress);
  if (EFI_ERROR(Status)) {

    return EFI_DEVICE_ERROR;
  }
  MmioWrite32(I3cInstanceAddress + COMMAND_QUEUE_PORT_I3C0_REG, CmdPort.Bits.command);

  CmdPort.Bits.command = ComboCommandLow.Data; //write high data
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
