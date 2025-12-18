

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
  CHAR16                  CpuBrand[14];

  AsmCpuid(CPUID_SIGNATURE, NULL, &RegEbx, &RegEcx, &RegEdx);

  RawBytes = (UINT8*)&RegEbx;
  for (int i = 0; i < 4; i++) {
    CpuBrand[Index++] = (CHAR16)RawBytes[i];
  }

  RawBytes = (UINT8*)&RegEdx;
  for (int i = 0; i < 3; i++) {
    CpuBrand[Index++] = (CHAR16)RawBytes[i];
  }

  CpuBrand[Index++] = 0x0020;  //Space
  CpuBrand[Index++] = (CHAR16)RawBytes[3];

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
    IsIntelCpu = TRUE;
  }

  Print(L"CPU family 0x%08x, Stepping 0x%02x\n",
    CpuFamily, CpuStepping);

  return EFI_SUCCESS;
}


EFI_STATUS
GetCPUTemperauture(
  VOID
)
{
 
  MSR_IA32_THERM_STATUS_REGISTER ThermStatus;
  UINT8 Temperature;
  
  ThermStatus.Uint32 = AsmReadMsr32(MSR_IA32_THERM_STATUS);  
  Temperature = (UINT8)(ThermStatus.Uint32 >> 16) & 0x7F;
  if(Temperature > TjMax) return EFI_DEVICE_ERROR;

  Temperature = TjMax - Temperature;
  Print(L"CPU Temperature: %d'C\n", Temperature);
  return EFI_SUCCESS;
}
