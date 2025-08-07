

#include "DimmView.h"
#include "RACU.h"

UINT32  PciExpressBaseAddress;
UINT32  ScfBaseAddress;
UINT32  I3cSpdBus0BaseAddress;
UINT32  I3cSpdBus1BaseAddress;
UINT32  I3cSpdBus2BaseAddress;
UINT32  I3cSpdBus3BaseAddress;

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
        
    I3cSpdBus0BaseAddress = ScfBaseAddress + I3C_SPD_BUS0_ADDRESS;
    I3cSpdBus1BaseAddress = ScfBaseAddress + I3C_SPD_BUS1_ADDRESS;
    I3cSpdBus2BaseAddress = ScfBaseAddress + I3C_SPD_BUS2_ADDRESS;
    I3cSpdBus3BaseAddress = ScfBaseAddress + I3C_SPD_BUS3_ADDRESS;

    //Print(L"spd0 0x%04x\n", I3cSpdBus0BaseAddress);
    //Print(L"spd1 0x%04x\n", I3cSpdBus1BaseAddress);
    //Print(L"spd2 0x%04x\n", I3cSpdBus2BaseAddress);
    //Print(L"spd3 0x%04x\n", I3cSpdBus3BaseAddress);
  }
  else
    return EFI_UNSUPPORTED;
  

  return EFI_SUCCESS;

}
