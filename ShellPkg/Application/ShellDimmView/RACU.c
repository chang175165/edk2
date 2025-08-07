

#include "DimmView.h"
#include "RACU.h"
#include "I3C0.h"

UINT32  PciExpressBaseAddress;
UINT32  ScfBaseAddress;
//UINT32  I3cSpdBus0BaseAddress;
//UINT32  I3cSpdBus1BaseAddress;
//UINT32  I3cSpdBus2BaseAddress;
//UINT32  I3cSpdBus3BaseAddress;
UINT32  I3cSpdBusBaseAddress[4];

EFI_STATUS
CheckI3cConfig(
  void
)
{
  DEVICE_CONTROL_I3C0_STRUCT I3cDevCtrl;

  for (UINT8 i=0; i<4; i++) {
    if (I3cSpdBusBaseAddress[i] != 0) {
      I3cDevCtrl.Data = MmioRead32(I3cSpdBusBaseAddress[i] + DEVICE_CONTROL_I3C0_REG);
     
      if (I3cDevCtrl.Bits.iba_include == 1 &&
          I3cDevCtrl.Bits.i2c_slave_present == 0 &&
          I3cDevCtrl.Bits.enable == 1) {
          Print(L"I3C Instance %d has I3C Devices\n", i);
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
InitI3CDevices(
  void
)
{

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

    for(UINT8 i=0 ; i<4 ; i++) {
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
  
  Print(L"Check I3C mode start\n");
  CheckI3cConfig();

  return EFI_SUCCESS;
}


