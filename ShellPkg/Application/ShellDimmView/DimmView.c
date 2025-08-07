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
  IN UINTN   Argc,
  IN CHAR16** Argv
)
{
  EFI_STATUS Status;
  Status = PopulateCpuType();


  return EFI_SUCCESS;

}


