/** @file
  Main file for DIMM View application

  Copyright (c) 2020,  All rights reserved.<BR>
 
**/

#include "DimmView.h"
#include "CpuIds.h"


/**
  UEFI application entry point which has an interface similar to a
  standard C main function.

  The ShellCEntryLib library instance wrappers the actual UEFI application
  entry point and calls this ShellAppMain function.

  @param[in] Argc     The number of items in Argv.
  @param[in] Argv     Array of pointers to strings.

  @retval  0               The application exited normally.
  @retval  Other           An error occurred.

**/
INTN
EFIAPI
ShellAppMain(
  IN UINTN  Argc,
  IN CHAR16** Argv
)
{
  EFI_STATUS Status;
  UINTN Index;

  if (Argc == 1) {
    Status = PopulateCpuType();
    return Status;
  }

  Status = InitI3CDevices();
  if (Argc >= 2 && Argv[1] != NULL) {
    for (Index = 1; Index < Argc; Index++) {
      //Print(L"Argv[%d]: \"%s\"\n", Index, Argv[Index]);
      if (StrCmp(Argv[Index], L"-dv") == 0) {
        GatherSPDData();
        break;
      }
      if (StrCmp(Argv[Index], L"-dt") == 0) {
        Status = SmbTsodHandler();
        break;
      }
    }
  }
  
  return Status;
}


