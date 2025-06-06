#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/ShellCEntryLib.h>
#include <Library/ShellLib.h>                 
#include <Library/FileHandleLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>


#define	VERSION_MAJOR						        0			// Major version
#define	VERSION_MINOR						        1			// Minor version
#define	VERSION_BUILD						        0			// Build version

#define V1                              1
#define V2                              2
#define V3                              3

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
  EFI_STATUS  Status;
  SHELL_FILE_HANDLE FileHandle;
  CHAR16* FileName;

  if (Argc < 2) {
    Print(L"Use ftest.efi file name \n");
    return EFI_INVALID_PARAMETER;
  }

  FileName = Argv[1];
  Print(L"Open file : %s\n", FileName);

  Status = ShellOpenFileByName(
    FileName,
    &FileHandle,
    EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
    0);

  if (EFI_ERROR(Status)) {
    Print(L"Can't Open File: %r\n", Status);
    return Status;
  }

  ShellCloseFile(&FileHandle);

  ShellPrintHelp(
    L"Shell Command Help Test",
    L"Shell Section Test",
    TRUE);

  return EFI_SUCCESS;

}
