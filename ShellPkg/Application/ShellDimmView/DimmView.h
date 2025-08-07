

#ifndef _DIMM_VIEW_H_
#define _DIMM_VIEW_H_

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/CpuLib.h>
#include <Library/IoLib.h>
#include <Library/PrintLib.h>
#include <Library/ShellCEntryLib.h>

EFI_STATUS
PopulateCpuType(
  void
);

EFI_STATUS
InitI3CDevices(
  void
);



#endif _DIMM_VIEW_H_
