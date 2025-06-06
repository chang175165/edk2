

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/ShellLib.h>
#include <Library/PrintLib.h>
#include <Library/FileHandleLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/ShellCEntryLib.h>
#include <Library/MemoryAllocationLib.h>

#define	VERSION_MAJOR						        3			// Major version
#define	VERSION_MINOR						        1			// Minor version
#define	VERSION_BUILD						        2			// Build version

#define V1                              6
#define V2                              2
#define V3                              9

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
  CHAR8 AsciiBuffer[128];
  CHAR16 UnicodeBuffer[128];
  UINTN AsciiSize;
  UINTN UnicodeNum;

  if (Argc < 2) {
    Print(L"Use ftest.efi file name\n");
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

  AsciiSPrint(
    AsciiBuffer,
    sizeof(AsciiBuffer),
    "TEST SW Version=%d.%d.%d\n Test2 FW version=%d.%d.%d\n",
    VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD,
    V1,V2,V3
  );

  AsciiSize = AsciiStrLen(AsciiBuffer);

  Status = ShellWriteFile(
    FileHandle,
    &AsciiSize,
    AsciiBuffer
  );

  if (EFI_ERROR(Status)) {
    Print(L"Can't Write File: %r\n", Status);
    return Status;
  }

  ShellCloseFile(&FileHandle);

  AsciiStrnToUnicodeStrS(
    AsciiBuffer,
    AsciiSize,
    UnicodeBuffer,
    sizeof(UnicodeBuffer)/sizeof(CHAR16),
    &UnicodeNum
  );

  AsciiPrint(AsciiBuffer);  //test

  Print(L"%s - number %d\n", UnicodeBuffer, UnicodeNum);

  ShellPrintHelp(
    L"Shell Command Help Test",
    L"Shell Section Test",
    TRUE);

  return EFI_SUCCESS;

}
