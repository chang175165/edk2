

#ifndef _DIMM_VIEW_H_
#define _DIMM_VIEW_H_

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiLib.h>
#include <Library/CpuLib.h>
#include <Library/IoLib.h>
#include <Library/ShellLib.h>
#include <Library/PrintLib.h>
#include <Library/ShellCEntryLib.h>
#include <Library/UefiBootServicesTableLib.h>

EFI_STATUS
PopulateCpuType(
  VOID
);

EFI_STATUS
InitI3CDevices(
  VOID
);

EFI_STATUS
GatherSPDData(
  VOID
);

EFI_STATUS
SmbTsodHandler(
  VOID
);

EFI_STATUS
ControllHandler(
  VOID
);

#endif _DIMM_VIEW_H_
