

#include <Register/Intel/Cpuid.h>
#include <Register/Amd/Cpuid.h>

#include "DimmView.h"
#include "CpuIds.h"

VOID
GetCpuBrandName()
{
  //UINT32                  RegEax;
  UINT32                  RegEbx;
  UINT32                  RegEcx;
  UINT32                  RegEdx;
  UINTN                   Index = 0;
  UINT8*                  RawBytes;
  CHAR16                  CpuBrand[13];

  AsmCpuid(CPUID_SIGNATURE, NULL, &RegEbx, &RegEcx, &RegEdx);

  RawBytes = (UINT8*)&RegEbx;
  for (int i = 0; i < 4; i++) {
    CpuBrand[Index++] = (CHAR16)RawBytes[i];
  }

  RawBytes = (UINT8*)&RegEdx;
  for (int i = 0; i < 4; i++) {
    CpuBrand[Index++] = (CHAR16)RawBytes[i];
  }

  RawBytes = (UINT8*)&RegEcx;
  for (int i = 0; i < 4; i++) {
    CpuBrand[Index++] = (CHAR16)RawBytes[i];
  }

  // Null terminator
  CpuBrand[Index] = L'\0';
  Print(L"%s CPU\n", CpuBrand);
}

EFI_STATUS
PopulateCpuType(
  void
)
{

  UINT32                  CpuFamily = GetCpuFamilyModel();
  UINT8                   CpuStepping = GetCpuSteppingId();
  UINT8                   CpuType;

  CpuType = (UINT8)-1;

  GetCpuBrandName();
  if (StandardSignatureIsAuthenticAMD()) {
    IsAmdCpu = TRUE;
  }
  else {
    switch (CpuFamily>>4) {
    case CPU_FAMILY_GNRSP:
      CpuType = CPU_GNRSP;
      break;

    case CPU_FAMILY_GNRD:
      CpuType = CPU_GNRD;
      break;

    case CPU_FAMILY_SRFSP:
      CpuType = CPU_SRFSP;
      break;

    case CPU_FAMILY_CWF:
      CpuType = CPU_CWF;
      break;

    case CPU_FAMILY_GRR:
      CpuType = CPU_GRR;
      break;

    default:
      Print(L"Unknown CPU family 0x%x\n", CpuFamily);
      return EFI_DEVICE_ERROR;
    }
    IsIntelCpu = TRUE;
  }

  Print(L"CPU family 0x%08x, Stepping 0x%02x and Type 0x%02x\n",
    CpuFamily, CpuStepping, CpuType);

  return EFI_SUCCESS;
}
