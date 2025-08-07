

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


#endif _CPUID_REGS_H_
