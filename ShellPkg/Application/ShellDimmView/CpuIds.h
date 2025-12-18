
#ifndef _CPUID_REGS_H_
#define _CPUID_REGS_H_

//
// Following CPUID definition is composed of CPUID leaf 1 fields:
// Ext-Model-ID  Rsvd     Proc-Type   Family-ID   Model
// BITS [19:16]  [15:14]  [13:12]     [11:8]      [7:4]
//
#define CPU_FAMILY_GNRSP   0xA06D      // GNR-SP CPU
#define CPU_FAMILY_GNRD    0xA06E      // GNR-D CPU
#define CPU_FAMILY_SRFSP   0xA06F      // SRF-SP CPU
#define CPU_FAMILY_CWF     0xD06D      // CWF CPU
#define CPU_FAMILY_GRR     0xB066      // GrandRidge
#define CPU_FAMILY_DMR     0x00F0      // DMR CPU
#define CPU_FAMILY_DMRD    0x00F1      // DMR-D CPU
#define CPU_FAMILY_RRF     0x00F2      // RRF CPU

//
// Processor Family and Model information.
//
#define NEHALEM_FAMILY_ID                 0x06

#define GRANITERAPIDS_SERVER_MODEL_ID     0xAD
#define GRANITERAPIDS_D_SERVER_MODEL_ID   0xAE
#define SIERRAFOREST_SERVER_MODEL_ID      0xAF
#define GRANDRIDGE_SERVER_MODEL_ID        0xB6
#define CLEARWATERFOREST_SERVER_MODEL_ID  0xDD

#define IS_GRANITERAPIDS_SERVER_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == GRANITERAPIDS_SERVER_MODEL_ID \
    ) \
   )

#define IS_GRANITERAPIDS_D_SERVER_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == GRANITERAPIDS_D_SERVER_MODEL_ID \
    ) \
   )

#define IS_SIERRAFOREST_SERVER_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == SIERRAFOREST_SERVER_MODEL_ID \
    ) \
   )

#define IS_CLEARWATERFOREST_SERVER_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == CLEARWATERFOREST_SERVER_MODEL_ID \
    ) \
   )

#define IS_GRANDRIDGE_SERVER_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == GRANDRIDGE_SERVER_MODEL_ID \
    ) \
   )

#define EFI_CACHE_UNCACHEABLE                 0
#define EFI_CACHE_WRITECOMBINING              1
#define EFI_CACHE_WRITETHROUGH                4
#define EFI_CACHE_WRITEPROTECTED              5
#define EFI_CACHE_WRITEBACK                   6


// CPU types
#define CPU_SPRSP      0     // SapphireRapids-SP: Mainstream Xeon - 10nm Wave 3
#define CPU_GNRSP      1     // GraniteRapids      Mainstream Xeon - 7nm Wave 4
#define CPU_SRFSP      2     // SierraForest       Atom core based - 7nm Wave 4
#define CPU_GRR        3     // GrandRidge:        Atom core based Micro-Server
#define CPU_EMRSP      4     // EmeraldRapids-SP:  Mainstream Xeon 10nm Wave 3
#define CPU_GNRD       5     // GraniteRapids-D    Xeon core based Micro-Server
#define CPU_DMR        6     // DiamondRapids:     Mainstream Xeon - Intel 18A Wave 5
#define CPU_DMRD       7     // DiamondRapids-D:   Xeon core based Micro-Server
#define CPU_RRF        8     // RogueRiverForest:  Atom core based Micro-Server
#define CPU_CWF        9     // ClearWaterForest:  Atom core based Micro-Server
#define CPU_MAX        0xFF  // MAX CPU limit


BOOLEAN IsIntelCpu = FALSE;
BOOLEAN IsAmdCpu = FALSE;

#define TjMax   105

/**
  Thermal Status Information (RO) Contains status information about the
  processor's thermal sensor and automatic thermal monitoring facilities. See
  Section 14.7.2, "Thermal Monitor". If CPUID.01H:EDX[22] = 1.

  @param  ECX  MSR_IA32_THERM_STATUS (0x0000019C)
  @param  EAX  Lower 32-bits of MSR value.
               Described by the type MSR_IA32_THERM_STATUS_REGISTER.
  @param  EDX  Upper 32-bits of MSR value.
               Described by the type MSR_IA32_THERM_STATUS_REGISTER.

  <b>Example usage</b>
  @code
  MSR_IA32_THERM_STATUS_REGISTER  Msr;

  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_THERM_STATUS);
  @endcode
  @note MSR_IA32_THERM_STATUS is defined as IA32_THERM_STATUS in SDM.
**/
#define MSR_IA32_THERM_STATUS  0x0000019C

/**
  MSR information returned for MSR index #MSR_IA32_THERM_STATUS
**/
typedef union {
  ///
  /// Individual bit fields
  ///
  struct {
    ///
    /// [Bit 0] Thermal Status (RO):. If CPUID.01H:EDX[22] = 1.
    ///
    UINT32    ThermalStatus : 1;
    ///
    /// [Bit 1] Thermal Status Log (R/W):. If CPUID.01H:EDX[22] = 1.
    ///
    UINT32    ThermalStatusLog : 1;
    ///
    /// [Bit 2] PROCHOT # or FORCEPR# event (RO). If CPUID.01H:EDX[22] = 1.
    ///
    UINT32    PROCHOT_FORCEPR_Event : 1;
    ///
    /// [Bit 3] PROCHOT # or FORCEPR# log (R/WC0). If CPUID.01H:EDX[22] = 1.
    ///
    UINT32    PROCHOT_FORCEPR_Log : 1;
    ///
    /// [Bit 4] Critical Temperature Status (RO). If CPUID.01H:EDX[22] = 1.
    ///
    UINT32    CriticalTempStatus : 1;
    ///
    /// [Bit 5] Critical Temperature Status log (R/WC0).
    /// If CPUID.01H:EDX[22] = 1.
    ///
    UINT32    CriticalTempStatusLog : 1;
    ///
    /// [Bit 6] Thermal Threshold #1 Status (RO). If CPUID.01H:ECX[8] = 1.
    ///
    UINT32    ThermalThreshold1Status : 1;
    ///
    /// [Bit 7] Thermal Threshold #1 log (R/WC0). If CPUID.01H:ECX[8] = 1.
    ///
    UINT32    ThermalThreshold1Log : 1;
    ///
    /// [Bit 8] Thermal Threshold #2 Status (RO). If CPUID.01H:ECX[8] = 1.
    ///
    UINT32    ThermalThreshold2Status : 1;
    ///
    /// [Bit 9] Thermal Threshold #2 log (R/WC0). If CPUID.01H:ECX[8] = 1.
    ///
    UINT32    ThermalThreshold2Log : 1;
    ///
    /// [Bit 10] Power Limitation Status (RO). If CPUID.06H:EAX[4] = 1.
    ///
    UINT32    PowerLimitStatus : 1;
    ///
    /// [Bit 11] Power Limitation log (R/WC0). If CPUID.06H:EAX[4] = 1.
    ///
    UINT32    PowerLimitLog : 1;
    ///
    /// [Bit 12] Current Limit Status (RO). If CPUID.06H:EAX[7] = 1.
    ///
    UINT32    CurrentLimitStatus : 1;
    ///
    /// [Bit 13] Current Limit log (R/WC0). If CPUID.06H:EAX[7] = 1.
    ///
    UINT32    CurrentLimitLog : 1;
    ///
    /// [Bit 14] Cross Domain Limit Status (RO). If CPUID.06H:EAX[7] = 1.
    ///
    UINT32    CrossDomainLimitStatus : 1;
    ///
    /// [Bit 15] Cross Domain Limit log (R/WC0). If CPUID.06H:EAX[7] = 1.
    ///
    UINT32    CrossDomainLimitLog : 1;
    ///
    /// [Bits 22:16] Digital Readout (RO). If CPUID.06H:EAX[0] = 1.
    ///
    UINT32    DigitalReadout : 7;
    UINT32    Reserved1 : 4;
    ///
    /// [Bits 30:27] Resolution in Degrees Celsius (RO). If CPUID.06H:EAX[0] =
    /// 1.
    ///
    UINT32    ResolutionInDegreesCelsius : 4;
    ///
    /// [Bit 31] Reading Valid (RO). If CPUID.06H:EAX[0] = 1.
    ///
    UINT32    ReadingValid : 1;
    UINT32    Reserved2 : 32;
  } Bits;
  ///
  /// All bit fields as a 32-bit value
  ///
  UINT32    Uint32;
  ///
  /// All bit fields as a 64-bit value
  ///
  UINT64    Uint64;
} MSR_IA32_THERM_STATUS_REGISTER;

#endif _CPUID_REGS_H_
