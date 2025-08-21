

#ifndef _RACU_H_
#define _RACU_H_

#include <Library/PciLib.h>
#include <Library/PciExpressLib.h>

#define VTD_SVID  0x09A28086
#define RACU_SVID 0x32518086

#define I3C_SPD_BUS0_ADDRESS  0x23C000
#define I3C_SPD_BUS1_ADDRESS  0x244000
#define I3C_SPD_BUS2_ADDRESS  0x23E000    //only in AP processors
#define I3C_SPD_BUS3_ADDRESS  0x246000    //only in AP processors

#define SVID_OFFSET       0x00
#define MMCFG_OFFSET      0x90
#define MMCFG_LIMT_OFFSET 0x98

#define RACU_BUS          0xFE
#define RACU_DEV          0x00
#define RACU_FUN          0x01
#define SCF_MMIO_OFFSET   0xD0
#define SCF_BAR_OFFSET    0xD4

#define MAX_CH_DDR        3

#define BYTE_MASK          0xFF
#define WORD_MASK          0xFFFF

VOID
SelectI3cPpFreq (
  UINT32
);

VOID
SelectI3cOdFreq (
  UINT32
);

VOID
SelectI2cFmFreq (
  UINT32
);

EFI_STATUS
CheckI3cFreq (
  UINT32
);

EFI_STATUS
CheckI3cConfig (
  VOID
);

EFI_STATUS
CheckResponseStatus (
  UINT32,
  UINT8
);

EFI_STATUS
WaitForWriteToCompleteTarget (
  UINT32
);

EFI_STATUS
WaitForHostNotBusyTarget (
  UINT32
);

EFI_STATUS
WaitForDataReadyRead (
  UINT32
);

EFI_STATUS
CheckTxFiFoSpace (
  UINT32
);

EFI_STATUS
SendCccCmd (
  UINT32,
  UINT8,
  SMB_ATTR_FLAG,
  UINT8*,
  UINT8*
);

EFI_STATUS
SpdEnumeration (
  VOID
);

EFI_STATUS
InitSpdAddressingMode (
  UINT32
);

EFI_STATUS
ReadProcSmb (
  UINT32,
  SMB_DEVICE_STRUCT,
  UINT8,
  volatile UINT8* 
);

EFI_STATUS
SmbReadCommon (
  UINT32,
  SMB_DEVICE_STRUCT,
  UINT8 ,
  volatile UINT16*
);

EFI_STATUS
WriteProcSmb (
  UINT32,
  SMB_DEVICE_STRUCT,
  UINT8,
  volatile UINT8*
);

EFI_STATUS
SmbWriteCommon (
  UINT32,
  SMB_DEVICE_STRUCT,
  UINT8,
  volatile UINT16*
);

EFI_STATUS
ResetProcSmb (
  UINT32
);

EFI_STATUS
I3cBusReset (
  UINT32
);

EFI_STATUS
ResumeProcSmb (
  UINT32
);

EFI_STATUS
SpdGetModuleType (
  UINT32,
  UINT8*
);

EFI_STATUS
SpdGetBaseModuleType (
  UINT32
);

EFI_STATUS
SpdReadByte (
  UINT32,
  UINT16,
  UINT8*
);

EFI_STATUS
ProgramSpdPage (
  UINT32,
  UINT8
);

EFI_STATUS
SpdHubReadByte (
  UINT32,
  UINT8,
  UINT8*
);

EFI_STATUS
Ddr5MontageSpdHubA0Errata (
  UINT32
);

EFI_STATUS
GetCommonDDR5DIMMConfig (
  UINT32
);

EFI_STATUS
SpdGetOperableEndurant (
  UINT32
);

EFI_STATUS
SpdGetRawCardRefDesign (
  UINT32
);

EFI_STATUS
SpdGetDIMMBusWidth (
  UINT32
);

EFI_STATUS
SpdGetModuleManufacturerId (
  UINT32
);

EFI_STATUS
SpdGetDramManufacturerId (
  UINT32
);

EFI_STATUS
SpdGetModuleManufacturingLocation(
  UINT32
);


EFI_STATUS
SpdGetModuleManufacturingDate(
  UINT32
);

EFI_STATUS
SpdGetModuleSerialNumber(
  UINT32
);

EFI_STATUS
SpdGetModulePartNum(
  UINT32
);

EFI_STATUS
SpdGetRcdVendor(
  UINT32
);

EFI_STATUS
GetRcdDeviceTypeFromSpd(
  UINT32
);

EFI_STATUS
SpdGetRcdRevision(
  UINT32
);

EFI_STATUS
SpdGetPmicVendor(
  UINT32
);

EFI_STATUS
SpdGetTsodMfgId(
  UINT32
);

EFI_STATUS
SpdGetSpdMfgId(
  UINT32
);

EFI_STATUS
SpdGetDdrMbistCapability(
  UINT32
);

EFI_STATUS
GatherSPDDataDDR5(
  UINT32
);

EFI_STATUS
ReadProcSmbTsod(
  UINT32,
  SMB_DEVICE_STRUCT,
  UINT8,
  volatile UINT16* Data
);

#endif _RACU_H_
