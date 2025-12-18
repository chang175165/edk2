/** @file
  This is a test application that demonstrates how to use the C-style entry point
  for a shell application.

  Copyright (c) 1996 - 2024, Meritech Corporation. All rights reserved.<BR>


**/
#include "VC.h"
#include "MF.h"

#define VERSION_MAJOR						0
#define VERSION_MINOR						1
#define VERSION_BUILD					  0

#define MAX_ARGUMENT_STRING			16
#define SIZE_CMD_ARGS						16

 /*Function declaration*/
void
PrintHelpMsg(
  void
);

void ToUpperCase(
  CHAR16*,
  CHAR16*
);

EFI_STATUS
InitFileHandle(
  void
);

EFI_STATUS
ReadIPInfo(
  void
);

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
ShellAppMain (
  IN UINTN   Argc,
  IN CHAR16  **Argv
  )
{
  EFI_STATUS  Status = EFI_UNSUPPORTED;
  CHAR16 OpCmd[MAX_ARGUMENT_STRING] = { 0, };

  Print(L"IPReader for PCT3.0 MRDIMM Tester V%d.%d.%d %a\n",
    VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD, __DATE__);

  if (Argc == 1 || Argc > 3) {
    PrintHelpMsg();
    return Status;
  }

  Status = InitSerialPort();
  if (EFI_ERROR(Status)) {
    Print(L"  Failed to configure Serial Port %r \n", Status);
  }

  ToUpperCase(Argv[1], OpCmd);
    
  if (Argc == 2) {
    if (!StrCmp(OpCmd, L"-R")) {      //Read IP Info
      Status = ReadIPInfo();

      if (!EFI_ERROR(Status)) {
        Print(L"  ReadIp.TXT file create Ok! %r\n\n", Status);
      }
    }
  }
  else {
    if (!StrCmp(OpCmd, L"-W")) {      //Write IP Info
      IPv4_ADDRESS Addr;
      Status = StrToIpv4Address(
        Argv[2], NULL, &Addr, NULL
      );

      if (!EFI_ERROR(Status)) {
        Status = SaveIPAddr(&Addr);
        if (!EFI_ERROR(Status)) {
          Print(L"  Write BOARD IP:%d.%d.%d.%d OK\n",
            Addr.Addr[0], Addr.Addr[1], Addr.Addr[2], Addr.Addr[3]);
        }
        else {
          Print(L"  [ERROR] Failed to Save Address number...%r\n", Status);
        }
      }
      else {
        Print(L"  [ERROR] Invalid Address number...%r\n", Status);
      }
    }
  }

  if (EFI_ERROR(Status)) {
    Print(L"  [ERROR] %s is not valid command %r.\n", OpCmd, Status);
  }

  return Status;
}

void PrintHelpMsg(void)
{
  Print(L"Copyright (c) 1996 - 2025, Meritech Corporation. All rights reserved \n");
  Print(L"  usage : IPReader [-R/-W] [address]\n");
  Print(L"  examples:\n");
  Print(L"    IPReader -W address     (Write BOARD IP)\n");
  Print(L"    IPReader -R             (Read BOARD IP)\n");
  Print(L"  Author by Brian Cheng in TDC\n");
}

void ToUpperCase(CHAR16* src, CHAR16* dest)
{
  if (src == NULL || dest == NULL)
    return;

  while (*src) {
    *dest = CharToUpper(*src);
    src++;
    dest++;
  }
}

EFI_STATUS
ReadIPInfo(
  void
)
{
  EFI_STATUS Status = EFI_UNSUPPORTED;
  IPv4_ADDRESS IPAddr;
  CHAR8 AsciiBuffer[32];
  UINTN AsciiSize;
  SHELL_FILE_HANDLE FileHandle;

  Status = ShellOpenFileByName(
    L"ReadIp.TXT",
    &FileHandle,
    EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
    0
  );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = GetIPAddr(&IPAddr);
  if (EFI_ERROR(Status)) return Status;

  // Board IP String
  SetMem(AsciiBuffer, sizeof(AsciiBuffer), 0);
  AsciiSPrint(
    AsciiBuffer,
    sizeof(AsciiBuffer),
    "BOARD IP:%d.%d.%d.%d\n",
    IPAddr.Addr[0], IPAddr.Addr[1], IPAddr.Addr[2], IPAddr.Addr[3]
  );

  AsciiSize = AsciiStrLen(AsciiBuffer);
  Status = ShellWriteFile(
    FileHandle,
    &AsciiSize,
    AsciiBuffer
  );
  if (EFI_ERROR(Status)) return Status;

  AsciiPrint("%s", AsciiBuffer);

  // TPC IP String
  SetMem(AsciiBuffer, sizeof(AsciiBuffer), 0);
  AsciiSPrint(
    AsciiBuffer,
    sizeof(AsciiBuffer),
    "TPC IP:%d.%d.%d.250\n",
    IPAddr.Addr[0], IPAddr.Addr[1], IPAddr.Addr[2]
  );

  AsciiSize = AsciiStrLen(AsciiBuffer);
  Status = ShellWriteFile(
    FileHandle,
    &AsciiSize,
    AsciiBuffer
  );
  if (EFI_ERROR(Status)) return Status;

  AsciiPrint("%s", AsciiBuffer);

  // TCP Port String
  SetMem(AsciiBuffer, sizeof(AsciiBuffer), 0);
  AsciiSPrint(
    AsciiBuffer,
    sizeof(AsciiBuffer),
    "TPC PORT : 30001\n"
  );

  AsciiSize = AsciiStrLen(AsciiBuffer);
  Status = ShellWriteFile(
    FileHandle,
    &AsciiSize,
    AsciiBuffer
  );
  if (EFI_ERROR(Status)) return Status;
  AsciiPrint("%s", AsciiBuffer);

  // TEMP IP String
  SetMem(AsciiBuffer, sizeof(AsciiBuffer), 0);
  AsciiSPrint(
    AsciiBuffer,
    sizeof(AsciiBuffer),
    "TEMP IP:%d.%d.%d.%d\n",
    IPAddr.Addr[0], IPAddr.Addr[1], IPAddr.Addr[2], IPAddr.Addr[3] + 5
  );

  AsciiSize = AsciiStrLen(AsciiBuffer);
  Status = ShellWriteFile(
    FileHandle,
    &AsciiSize,
    AsciiBuffer
  );
  if (EFI_ERROR(Status)) return Status;
  AsciiPrint("%s", AsciiBuffer);

  // TEMP Port String
  SetMem(AsciiBuffer, sizeof(AsciiBuffer), 0);
  AsciiSPrint(
    AsciiBuffer,
    sizeof(AsciiBuffer),
    "TEMP PORT:30002\n"
  );

  AsciiSize = AsciiStrLen(AsciiBuffer);
  Status = ShellWriteFile(
    FileHandle,
    &AsciiSize,
    AsciiBuffer
  );
  if (EFI_ERROR(Status)) return Status;
  AsciiPrint("%s", AsciiBuffer);

  // NET Mask String
  SetMem(AsciiBuffer, sizeof(AsciiBuffer), 0);
  AsciiSPrint(
    AsciiBuffer,
    sizeof(AsciiBuffer),
    "NETMASK:255.255.0.0\n"
  );

  AsciiSize = AsciiStrLen(AsciiBuffer);
  Status = ShellWriteFile(
    FileHandle,
    &AsciiSize,
    AsciiBuffer
  );
  if (EFI_ERROR(Status)) return Status;
  AsciiPrint("%s", AsciiBuffer);

  // Get Way String
  SetMem(AsciiBuffer, sizeof(AsciiBuffer), 0);
  AsciiSPrint(
    AsciiBuffer,
    sizeof(AsciiBuffer),
    "GATEWAY:%d.%d.1.1\n",
    IPAddr.Addr[0], IPAddr.Addr[1]
  );

  AsciiSize = AsciiStrLen(AsciiBuffer);
  Status = ShellWriteFile(
    FileHandle,
    &AsciiSize,
    AsciiBuffer
  );
  if (EFI_ERROR(Status)) return Status;
  AsciiPrint("%s", AsciiBuffer);

  // Version String
  SetMem(AsciiBuffer, sizeof(AsciiBuffer), 0);
  AsciiSPrint(
    AsciiBuffer,
    sizeof(AsciiBuffer),
    "Version:%d.%d.%d[%a]\n",
    VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD, __DATE__
  );

  AsciiSize = AsciiStrLen(AsciiBuffer);
  Status = ShellWriteFile(
    FileHandle,
    &AsciiSize,
    AsciiBuffer
  );
  if (EFI_ERROR(Status)) return Status;
  AsciiPrint("%s", AsciiBuffer);

  return EFI_SUCCESS;
}
