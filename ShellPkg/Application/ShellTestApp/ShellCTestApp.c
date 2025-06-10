/** @file
  This is a test application that demonstrates how to use the C-style entry point
  for a shell application.

  Copyright (c) 2009 - 2015, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/ShellCEntryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SerialPortLib.h>
#include <Library/IoLib.h>
#include <Protocol/SimpleFileSystem.h>


#define COM2    0x2f8


void initUartPort()
{
  UINTN port = COM2;
  IoWrite8(0x80, 0x08);
  IoWrite8(port + 3, 0x80);
  IoWrite8(port + 1, 0);
  IoWrite8(port, 0x01);    // 115200 bps
  IoWrite8(port + 3, 0x03);
  IoWrite8(port + 2, 0xC7);
  IoWrite8(port + 1, 0x00);

  // Delay 20ms
}

void sendUartBuffer(UINT8* tbuf, UINTN tcnt)
{
  UINT8 i;
  UINT8 regData;


  i = 0;
  while (i < tcnt) {
    do {
      regData = IoRead8(COM2 + 5);
    } while (!(regData & (1 << 5)));

    IoWrite8(COM2, tbuf[i]);

    i++;
  }

  IoWrite8(0x80, 0xAA);
  // printf("\n");
}

VOID SerialOutTest()
{
  //UINT8 HelloStr[] = { "Hello World GNRAP\n" };
  //UINT8 StrSize = sizeof(HelloStr);
  //sendUartBuffer(&HelloStr[0], StrSize);
  //sendUartBuffer(&HelloStr[0], 18);

  UINT8 TestBuf[8] = { 0x02,0x42,0x88, 0x99, 0, 0, 0, 0x3 };
  sendUartBuffer(&TestBuf[0], 8);
}


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
  UINT8 UartTest[8] = {0x02, 0x42, 0x0B, 0x0B, 0x00, 0x00, 0x00, 0x03};  //post code test send
  UINTN NumBytes;
  UINTN RetBytes;
  UINTN P80Num;
  

  NumBytes = sizeof(UartTest);
  RetBytes = 0xFF;
  P80Num = 0;

  IoWrite8(0x80, 0x99);
  
  Status = SerialPortInitialize();
  initUartPort();

  if (EFI_ERROR(Status)) {
    Print(L" Failed Serial Port Initialize \n");
    return Status;
  }

  if (Argc >= 2 && Argv[1] != NULL) {
    if (StrCmp(Argv[1], L"1") == 0) {
      sendUartBuffer(UartTest, NumBytes);
      IoWrite8(0x80, 0xEE);
    }
    else {

      P80Num = StrHexToUintn(Argv[1]);
      UartTest[2] = (UINT8)P80Num;
      RetBytes = SerialPortWrite(UartTest, NumBytes);

      if (RetBytes == NumBytes) {
        Print(L"Serial Port Write %d Bytes done\n", RetBytes);
      }

      Print(L"Serial Port Write %x \n", (UartTest[2]));
      IoWrite8(0x80, (UINT8)P80Num);
    }
  }

  return 0;
}

