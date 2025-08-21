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
        //Status = SmbTsodHandler();
        Status = ControllHandler();
        break;
      }
    }
  }
  
  return Status;
}

EFI_STATUS
ControllHandler(
  VOID
)
{
  EFI_STATUS Status;
  EFI_INPUT_KEY Key;
  EFI_EVENT TimerEvent;
  UINTN Index;
  UINTN curCol, curRow;
  UINTN Ticks = 0;
  const UINT64 ONE_SECOND_100NS = 10 * 1000 * 1000;
  //
  // Get the users response and if valid open the selected port.
  //
  Status = gBS->CreateEvent(EVT_TIMER, TPL_CALLBACK, NULL, NULL, &TimerEvent);
  if (EFI_ERROR(Status)) {
    Print(L"CreateEvent failed: %r\n", Status);
    return Status;
  }
  Status = gBS->SetTimer(TimerEvent, TimerPeriodic, ONE_SECOND_100NS);
  if (EFI_ERROR(Status)) {
    Print(L"SetTimer failed: %r\n", Status);
    gBS->CloseEvent(TimerEvent);
    return Status;
  }

  gST->ConIn->Reset(gST->ConIn, FALSE);
  gST->ConOut->ClearScreen(gST->ConOut);

  Print(L"Press ESC to exit.\n");
  curCol = gST->ConOut->Mode->CursorColumn;
  curRow = gST->ConOut->Mode->CursorRow
  EFI_EVENT Events[2] = { TimerEvent, gST->ConIn->WaitForKey };
  while (TRUE) {
    Status = gBS->WaitForEvent(2, Events, &Index);
    if (EFI_ERROR(Status)) {
      break;
    }

    if (Index == 0) {
      Status = SmbTsodHandler();
      if (EFI_ERROR(Status)) continue;
      ++Ticks;
      Print(L"[tick %u]\n", Ticks);
      gST->ConOut->SetCursorPosition(gST->ConOut, curCol, curRow);
    }
    else if (Index == 1) {
      if (!EFI_ERROR(gST->ConIn->ReadKeyStroke(gST->ConIn, &Key))) {
        if (Key.ScanCode == SCAN_ESC) {
          Print(L"ESC pressed, exiting...\n");
          break;
        }
      }
    }
  }

  gBS->SetTimer(TimerEvent, TimerCancel, 0);
  gBS->CloseEvent(TimerEvent);

  return Status;
}
