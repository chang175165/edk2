

#ifndef _DDR5_SPD_REGS_H_
#define _DDR5_SPD_REGS_H_

//
// DDR5 SPD Spec 0.986 Register Definitions
//

/*  Byte 0 (0x000): Number of Bytes in SPD Device  */

#define SPD_NUMBER_OF_BYTES_IN_SPD_DEVICE_REG       0x0000
//
// Update from SPD Spec 0.9 Beta Level 19
//
typedef union {
  struct {
    UINT8 beta_level_0_3 : 4;
                            /* Bits[0:3]
                               Bit0 to Bit3 of Beta Level
                            */
    UINT8 spd_bytes_total : 3;
                            /* Bits[4:6]
                               SPD Bytes Total
                               000: Undefined
                               001: 256
                               010: 512
                               011: 1024
                               All others reserved
                            */
    UINT8 beta_level_4 : 1;
                            /* Bit[7]
                               Bit4 of Beta Level
                            */
  } Bits;
  UINT8 Data;
} NUMBER_OF_BYTES_IN_SPD_DEVICE_STRUCT;

/*  Byte 1 (0x001): SPD Revision for Base Configuration Parameters  */

#define SPD_SPD_REVISION_FOR_BASE_CONFIGURATION_PARAMETERS_REG       0x0001

typedef union {
  struct {
    UINT8 additions_level : 4;
                            /* Bits[0:3]
                               Additions Level
                            */
    UINT8 encoding_level : 4;
                            /* Bits[4:7]
                               Encoding Level
                            */
  } Bits;
  UINT8 Data;
} SPD_REVISION_FOR_BASE_CONFIGURATION_PARAMETERS_STRUCT;

/*  Byte 2 (0x002): Key Byte / Host Bus Command Protocol Type  */

#define SPD_KEY_BYTE_HOST_BUS_COMMAND_PROTOCOL_TYPE_REG       0x0002

typedef union {
  struct {
    UINT8 sdram_module_type : 8;
                            /* Bits[0:7]
                               SDRAM / Module Type
                            */
  } Bits;
  UINT8 Data;
} KEY_BYTE_HOST_BUS_COMMAND_PROTOCOL_TYPE_STRUCT;

/*  Byte 3 (0x003): Key Byte / Module Type  */

#define SPD_KEY_BYTE_MODULE_TYPE_REG       0x0003

typedef union {
  struct {
    UINT8 base_module_type : 4;
                            /* Bits[0:3]
                               Base Module Type
                               0000: Reserved
                               0001: RDIMM
                               0010: UDIMM
                               0011: SO-DIMM
                               0100: LRDIMM
                               0101: Reserved
                               0110: Reserved
                               0111: Reserved
                               1000: Reserved // SO-RDIMM for revision lower than 0.9
                               1001: Reserved
                               1010: DDIMM
                               1011: Solder down
                               1100: Reserved
                               1101: Reserved
                               1110: Reserved
                               1111: Reserved
                            */
    UINT8 hybrid_media : 3;
                            /* Bits[4:6]
                               Hybrid Media
                               000: Not hybrid
                               001: NVDIMM-N Hybrid
                               010: NVDIMM-P Hybrid
                               All other codes reserved
                            */
    UINT8 hybrid : 1;
                            /* Bits[7]
                               Hybrid
                               0: Not hybrid
                               (Module is DRAM only)
                               1: Hybrid module
                               (See bits 6~4 for hybrid type)
                            */
  } Bits;
  UINT8 Data;
} KEY_BYTE_MODULE_TYPE_STRUCT;

/*  Byte 4 (0x004): First SDRAM Density and Package  */

#define SPD_FIRST_SDRAM_DENSITY_AND_PACKAGE_REG       0x0004

typedef union {
  struct {
    UINT8 sdram_density_per_die : 5;
                            /* Bits[0:4]
                               SDRAM Density Per Die
                               00000: No memory
                               not defined
                               00001: 4 Gb
                               00010: 8 Gb
                               00011: 12 Gb
                               00100: 16 Gb
                               00101: 24 Gb
                               00110: 32 Gb
                               00111: 48 Gb
                               01000: 64 Gb
                               All others reserved
                            */
    UINT8 die_per_package : 3;
                            /* Bits[5:7]
                               Die Per Package
                               000: 1 die
                               Monolithic SDRAM
                               001: Reserved // 2 die, DDP with multiple loads on inputs & outputs for reversion lower than 0.9
                               010: 2 die
                               2H 3DS, single load on inputs & outputs
                               011: 4 die
                               4H 3DS
                               100: 8 die
                               8H 3DS
                               101: 16 die
                               16H 3DS
                               All others reserved
                            */
  } Bits;
  UINT8 Data;
} FIRST_SDRAM_DENSITY_AND_PACKAGE_STRUCT;

/*  Byte 5 (0x005): First SDRAM Addressing  */

#define SPD_FIRST_SDRAM_ADDRESSING_REG       0x0005

typedef union {
  struct {
    UINT8 first_sdram_row_address_bits : 5;
                            /* Bits[0:4]
                               First SDRAM Row Address Bits for revision lower than 0.9
                               00000: 16 rows
                               00010: 17 rows
                               00011: 18 rows
                               All others reserved
                               First SDRAM Row Address Bits for revision not lower than 0.9
                               00000: 16 rows
                               00001: 17 rows
                               00010: 18 rows
                               All others reserved
                            */
    UINT8 first_sdram_column_address_bits : 3;
                            /* Bits[5:7]
                               First SDRAM Column Address Bits for revision lower than 0.9
                               000: 10 columns
                               010: 11 columns
                               All others reserved
                               First SDRAM Column Address Bits for revision not lower than 0.9
                               000: 10 columns
                               001: 11 columns
                               All others reserved
                            */
  } Bits;
  UINT8 Data;
} FIRST_SDRAM_ADDRESSING_STRUCT;

/*  Byte 6 (0x006): First SDRAM I/O Width  */

#define SPD_FIRST_SDRAM_I_O_WIDTH_REG       0x0006

typedef union {
  struct {
    UINT8 reserved_0_4 : 5;
                            /* Bits[0:4]
                               Reserved
                               Reserved
                               must be coded as 00000
                            */
    UINT8 sdram_i_o_width : 3;
                            /* Bits[5:7]
                               SDRAM I/O Width
                               000: x4
                               001: x8
                               010: x16
                               011: x32
                               All others reserved
                            */
  } Bits;
  UINT8 Data;
} FIRST_SDRAM_I_O_WIDTH_STRUCT;

/*  Byte 7 (0x007): First SDRAM Bank Groups & Banks Per Bank Group  */

#define SPD_FIRST_SDRAM_BANK_GROUPS_BANKS_PER_BANK_GROUP_REG       0x0007

typedef union {
  struct {
    UINT8 first_sdram_banks_per_bank_group : 3;
                            /* Bits[0:2]
                               First SDRAM Banks Per Bank Group
                               000: 1 bank per bank group
                               001: 2 banks per bank group
                               010: 4 banks per bank group
                               All others reserved
                            */
    UINT8 reserved_3_4 : 2;
                            /* Bits[3:4]
                               Reserved
                               Reserved
                               must be coded as 00
                            */
    UINT8 first_sdram_bank_groups : 3;
                            /* Bits[5:7]
                               First SDRAM Bank Groups
                               000: 1 bank group
                               001: 2 bank groups
                               010: 4 bank groups
                               011: 8 bank groups
                               All others reserved
                            */
  } Bits;
  UINT8 Data;
} FIRST_SDRAM_BANK_GROUPS_BANKS_PER_BANK_GROUP_STRUCT;

/*  Byte 8 (0x008): Second SDRAM Density and Package  */

#define SPD_SECOND_SDRAM_DENSITY_AND_PACKAGE_REG       0x0008

typedef union {
  struct {
    UINT8 sdram_density_per_die : 5;
                            /* Bits[0:4]
                               SDRAM Density Per Die
                               00000: No memory
                               not defined
                               00001: 4 Gb
                               00010: 8 Gb
                               00011: 12 Gb
                               00100: 16 Gb
                               00101: 24 Gb
                               00110: 32 Gb
                               00111: 48 Gb
                               01000: 64 Gb
                               All others reserved
                            */
    UINT8 die_per_package : 3;
                            /* Bits[5:7]
                               Die Per Package
                               000: 1 die
                               Monolithic SDRAM
                               001: Reserved // 2 die, DDP with multiple loads on inputs & outputs for reversion lower than 0.9
                               010: 2 die
                               2H 3DS, single load on inputs & outputs
                               011: 4 die
                               4H 3DS
                               100: 8 die
                               8H 3DS
                               101: 16 die
                               16H 3DS
                               All others reserved
                            */
  } Bits;
  UINT8 Data;
} SECOND_SDRAM_DENSITY_AND_PACKAGE_STRUCT;

/*  Byte 9 (0x009): Second SDRAM Addressing  */

#define SPD_SECOND_SDRAM_ADDRESSING_REG       0x0009

typedef union {
  struct {
    UINT8 second_sdram_row_address_bits : 5;
                            /* Bits[0:4]
                               Second SDRAM Row Address Bits for revision lower than 0.9
                               00000: 16 rows
                               00010: 17 rows
                               00011: 18 rows
                               All others reserved
                               Second SDRAM Row Address Bits for revision not lower than 0.9
                               00000: 16 rows
                               00001: 17 rows
                               00010: 18 rows
                               All others reserved
                            */
    UINT8 second_sdram_column_address_bits : 3;
                            /* Bits[5:7]
                               Second SDRAM Column Address Bits for revision lower than 0.9
                               000: 10 columns
                               010: 11 columns
                               All others reserved
                               Second SDRAM Column Address Bits for revision not lower than 0.9
                               000: 10 columns
                               001: 11 columns
                               All others reserved
                            */
  } Bits;
  UINT8 Data;
} SECOND_SDRAM_ADDRESSING_STRUCT;

/*  Byte 10 (0x00A): Secondary SDRAM I/O Width  */

#define SPD_SECONDARY_SDRAM_I_O_WIDTH_REG       0x000A

typedef union {
  struct {
    UINT8 reserved_0_4 : 5;
                            /* Bits[0:4]
                               Reserved
                               Reserved
                               must be coded as 00000
                            */
    UINT8 sdram_i_o_width : 3;
                            /* Bits[5:7]
                               SDRAM I/O Width
                               000: x4
                               001: x8
                               010: x16
                               011: x32
                               All others reserved
                            */
  } Bits;
  UINT8 Data;
} SECONDARY_SDRAM_I_O_WIDTH_STRUCT;

/*  Byte 11 (0x00B): Second SDRAM Bank Groups & Banks Per Bank Group  */

#define SPD_SECOND_SDRAM_BANK_GROUPS_BANKS_PER_BANK_GROUP_REG       0x000B

typedef union {
  struct {
    UINT8 second_sdram_banks_per_bank_group : 3;
                            /* Bits[0:2]
                               Second SDRAM Banks Per Bank Group
                               000: 1 bank per bank group
                               001: 2 banks per bank group
                               010: 4 banks per bank group
                               All others reserved
                            */
    UINT8 reserved_3_4 : 2;
                            /* Bits[3:4]
                               Reserved
                               Reserved
                               must be coded as 00
                            */
    UINT8 second_sdram_bank_groups : 3;
                            /* Bits[5:7]
                               Second SDRAM Bank Groups
                               000: 1 bank group
                               001: 2 bank groups
                               010: 4 bank groups
                               011: 8 bank groups
                               All others reserved
                            */
  } Bits;
  UINT8 Data;
} SECOND_SDRAM_BANK_GROUPS_BANKS_PER_BANK_GROUP_STRUCT;

/*  Byte 12 (0x00C): SDRAM BL32 & Post Package Repair  */

#define SPD_SDRAM_BL32_POST_PACKAGE_REPAIR_REG       0x000C

typedef union {
  struct {
    UINT8 mppr_hppr_abort : 1;
                            /* Bits[0]
                               mPPR/hPPR Abort
                               0: mPPR/hPPR Abort not supported
                               1: mPPR/hPPR Abort supported
                            */
    UINT8 mbist_mppr : 1;
                            /* Bits[1]
                               MBIST/mPPR
                               0: MBIST/mPPR not supported
                               1: MBIST/mPPR supported
                            */
    UINT8 reserved_2_3 : 2;
                            /* Bits[2:3]
                               Reserved
                               Reserved
                               must be coded as 00
                            */
    UINT8 bl32 : 1;
                            /* Bits[4]
                               BL32
                               0: Burst length 32 not supported
                               1: Burst length 32 supported
                            */
    UINT8 sppr_undo_lock : 1;
                            /* Bits[5]
                               sPPR Undo/Lock
                               0: sPPR Undo/Lock not supported
                               1: sPPR Undo/Lock supported
                            */
    UINT8 reserved_6 : 1;
                            /* Bits[6]
                               Reserved
                               Reserved
                               must be coded as 0
                            */
    UINT8 sppr_granularity : 1;
                            /* Bits[7]
                               sPPR Granularity
                               0: One repair element per bank group
                               1: One repair element per bank
                            */
  } Bits;
  UINT8 Data;
} SDRAM_BL32_POST_PACKAGE_REPAIR_STRUCT;

/*  Byte 13 (0x00D): SDRAM Duty Cycle Adjuster & Partial Array Self Refresh  */

#define SPD_SDRAM_DUTY_CYCLE_ADJUSTER_PARTIAL_ARRAY_SELF_REFRESH_REG       0x000D

typedef union {
  struct {
    UINT8 dca_types_supported : 2;
                            /* Bits[0:1]
                               DCA Types Supported
                               00 = Device does not support DCA
                               01 = Device supports DCA for single/2-phase internal clock(s)
                               10 = Device supports DCA for 4-phase internal clock(s)
                               11 = Reserved
                            */
    UINT8 reserved_2_3 : 2;
                            /* Bits[2:3]
                               Reserved
                               Reserved
                               must be coded as 00
                            */
    UINT8 pasr : 1;
                            /* Bits[4]
                               PASR
                               0: PASR not supported
                               1: PASR supported
                            */
    UINT8 reserved_5_7 : 3;
                            /* Bits[5:7]
                               Reserved
                               Reserved
                               must be coded as 000
                            */
  } Bits;
  UINT8 Data;
} SDRAM_DUTY_CYCLE_ADJUSTER_PARTIAL_ARRAY_SELF_REFRESH_STRUCT;

/*  Byte 14 (0x00E): SDRAM Fault Handling  */

#define SPD_SDRAM_FAULT_HANDLING_REG       0x000E

typedef union {
  struct {
    UINT8 bounded_fault : 1;
                            /* Bits[0]
                               Bounded Fault
                               0: Bounded Fault not supported
                               1: Bounded Fault supported
                            */
    UINT8 x4_rmw_ecs_writeback_suppression_mr_selector : 1;
                            /* Bits[1]
                               x4 RMW/ECS Writeback Suppression MR Selector
                               0: Writeback suppression control in MR9
                               1: Writeback suppression control in MR15
                            */
    UINT8 x4_rmw_ecs_writeback_suppression : 1;
                            /* Bits[2]
                               x4 RMW/ECS Writeback Suppression
                               0: Writeback suppression not supported
                               1: Writeback suppression supported
                            */
    UINT8 reserved_3_7 : 5;
                            /* Bits[3:7]
                               Reserved
                               Reserved
                               must be coded as 00000
                            */
  } Bits;
  UINT8 Data;
} SDRAM_FAULT_HANDLING_STRUCT;

/*  Byte 16 (0x010): SDRAM Nominal Voltage, VDD  */

#define SPD_SDRAM_NOMINAL_VOLTAGE_VDD_REG       0x0010

typedef union {
  struct {
    UINT8 endurant : 2;
                            /* Bits[0:1]
                               Endurant
                               00: 1.1 V
                               All others reserved
                            */
    UINT8 operable : 2;
                            /* Bits[2:3]
                               Operable
                               00: 1.1 V
                               All others reserved
                            */
    UINT8 nominal : 4;
                            /* Bits[4:7]
                               Nominal
                               0000: 1.1 V
                               All others reserved
                            */
  } Bits;
  UINT8 Data;
} SDRAM_NOMINAL_VOLTAGE_VDD_STRUCT;

/*  Byte 17 (0x011): SDRAM Nominal Voltage, VDDQ  */

#define SPD_SDRAM_NOMINAL_VOLTAGE_VDDQ_REG       0x0011

typedef union {
  struct {
    UINT8 endurant : 2;
                            /* Bits[0:1]
                               Endurant
                               00: 1.1 V
                               All others reserved
                            */
    UINT8 operable : 2;
                            /* Bits[2:3]
                               Operable
                               00: 1.1 V
                               All others reserved
                            */
    UINT8 nominal : 4;
                            /* Bits[4:7]
                               Nominal
                               0000: 1.1 V
                               All others reserved
                            */
  } Bits;
  UINT8 Data;
} SDRAM_NOMINAL_VOLTAGE_VDDQ_STRUCT;

/*  Byte 18 (0x012): SDRAM Nominal Voltage, VPP  */

#define SPD_SDRAM_NOMINAL_VOLTAGE_VPP_REG       0x0012

typedef union {
  struct {
    UINT8 endurant : 2;
                            /* Bits[0:1]
                               Endurant
                               00: 1.8 V
                               All others reserved
                            */
    UINT8 operable : 2;
                            /* Bits[2:3]
                               Operable
                               00: 1.8 V
                               All others reserved
                            */
    UINT8 nominal : 4;
                            /* Bits[4:7]
                               Nominal
                               0000: 1.8 V
                               All others reserved
                            */
  } Bits;
  UINT8 Data;
} SDRAM_NOMINAL_VOLTAGE_VPP_STRUCT;

/*  SDRAM Minimum Cycle Time (tCKAVGmin) Byte 20 (0x014): Least Significant Byte  */

#define SPD_SDRAM_MINIMUM_CYCLE_TIME_TCKAVGMIN_LSB_REG       0x0014

typedef union {
  struct {
    UINT8 sdram_minimum_cycle_time_tckavgmin_ps : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Cycle Time (tCKAVGmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MINIMUM_CYCLE_TIME_TCKAVGMIN_LSB_STRUCT;

/*  SDRAM Minimum Cycle Time (tCKAVGmin) Byte 21 (0x015): Most Significant Byte   */

#define SPD_SDRAM_MINIMUM_CYCLE_TIME_TCKAVGMIN_MSB_REG       0x0015

typedef union {
  struct {
    UINT8 sdram_minimum_cycle_time_tckavgmin_ps : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Cycle Time (tCKAVGmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MINIMUM_CYCLE_TIME_TCKAVGMIN_MSB_STRUCT;

/*  SDRAM Maximum Cycle Time (tCKAVGmax) Byte 22 (0x016): Least Significant Byte  */

#define SPD_SDRAM_MAXIMUM_CYCLE_TIME_TCKAVGMAX_LSB_REG       0x0016

typedef union {
  struct {
    UINT8 sdram_maximum_cycle_time_tckavgmax_ps : 8;
                            /* Bits[0:7]
                               SDRAM Maximum Cycle Time (tCKAVGmax) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MAXIMUM_CYCLE_TIME_TCKAVGMAX_LSB_STRUCT;

/*  SDRAM Maximum Cycle Time (tCKAVGmax) Byte 23 (0x017): Most Significant Byte   */

#define SPD_SDRAM_MAXIMUM_CYCLE_TIME_TCKAVGMAX_MSB_REG       0x0017

typedef union {
  struct {
    UINT8 sdram_maximum_cycle_time_tckavgmax_ps : 8;
                            /* Bits[0:7]
                               SDRAM Maximum Cycle Time (tCKAVGmax) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MAXIMUM_CYCLE_TIME_TCKAVGMAX_MSB_STRUCT;

/*  SDRAM CAS Latencies Supported Byte 24 (0x018): First Byte  */

#define SPD_SDRAM_CAS_LATENCIES_SUPPORTED_0_REG       0x0018

typedef union {
  struct {
    UINT8 cl : 8;
                            /* Bits[0:7]
                               cl
                               Bit 7:CL =34
                               Bit 6:CL =32
                               Bit 5:CL =30
                               Bit 4:CL =28
                               Bit 3:CL =26
                               Bit 2:CL =24
                               Bit 1:CL =22
                               Bit 0:CL =20
                            */
  } Bits;
  UINT8 Data;
} SDRAM_CAS_LATENCIES_SUPPORTED_0_STRUCT;

/*  SDRAM CAS Latencies Supported Byte 25 (0x019): Second Byte  */

#define SPD_SDRAM_CAS_LATENCIES_SUPPORTED_1_REG       0x0019

typedef union {
  struct {
    UINT8 cl : 8;
                            /* Bits[0:7]
                               cl
                               Bit 7:CL =50
                               Bit 6:CL =48
                               Bit 5:CL =46
                               Bit 4:CL =44
                               Bit 3:CL =42
                               Bit 2:CL =40
                               Bit 1:CL =38
                               Bit 0:CL =36
                            */
  } Bits;
  UINT8 Data;
} SDRAM_CAS_LATENCIES_SUPPORTED_1_STRUCT;

/*  SDRAM CAS Latencies Supported Byte 26 (0x01A): Third Byte  */

#define SPD_SDRAM_CAS_LATENCIES_SUPPORTED_2_REG       0x001A

typedef union {
  struct {
    UINT8 cl : 8;
                            /* Bits[0:7]
                               cl
                               Bit 7:CL =66
                               Bit 6:CL =64
                               Bit 5:CL =62
                               Bit 4:CL =60
                               Bit 3:CL =58
                               Bit 2:CL =56
                               Bit 1:CL =54
                               Bit 0:CL =52
                            */
  } Bits;
  UINT8 Data;
} SDRAM_CAS_LATENCIES_SUPPORTED_2_STRUCT;

/*  SDRAM CAS Latencies Supported Byte 27 (0x01B): Fourth Byte  */

#define SPD_SDRAM_CAS_LATENCIES_SUPPORTED_3_REG       0x001B

typedef union {
  struct {
    UINT8 cl : 8;
                            /* Bits[0:7]
                               cl
                               Bit 7:CL =82
                               Bit 6:CL =80
                               Bit 5:CL =78
                               Bit 4:CL =76
                               Bit 3:CL =74
                               Bit 2:CL =72
                               Bit 1:CL =70
                               Bit 0:CL =68
                            */
  } Bits;
  UINT8 Data;
} SDRAM_CAS_LATENCIES_SUPPORTED_3_STRUCT;

/*  SDRAM CAS Latencies Supported Byte 28 (0x01C): Fifth Byte  */

#define SPD_SDRAM_CAS_LATENCIES_SUPPORTED_4_REG       0x001C

typedef union {
  struct {
    UINT8 cl : 8;
                            /* Bits[0:7]
                               cl
                               Bit 7:CL =98
                               Bit 6:CL =96
                               Bit 5:CL =94
                               Bit 4:CL =92
                               Bit 3:CL =90
                               Bit 2:CL =88
                               Bit 1:CL =86
                               Bit 0:CL =84
                            */
  } Bits;
  UINT8 Data;
} SDRAM_CAS_LATENCIES_SUPPORTED_4_STRUCT;

/*  SDRAM Minimum CAS Latency Time (tAAmin) Byte 30 (0x01E): Least Significant Byte  */

#define SPD_SDRAM_MINIMUM_CAS_LATENCY_TIME_TAAMIN_LSB_REG       0x001E

typedef union {
  struct {
    UINT8 sdram_minimum_cas_latency_time_taamin_ps : 8;
                            /* Bits[0:7]
                               SDRAM Minimum CAS Latency Time (tAAmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MINIMUM_CAS_LATENCY_TIME_TAAMIN_LSB_STRUCT;

/*  SDRAM Minimum CAS Latency Time (tAAmin) Byte 31 (0x01F): Most Significant Byte   */

#define SPD_SDRAM_MINIMUM_CAS_LATENCY_TIME_TAAMIN_MSB_REG       0x001F

typedef union {
  struct {
    UINT8 sdram_minimum_cas_latency_time_taamin_ps : 8;
                            /* Bits[0:7]
                               SDRAM Minimum CAS Latency Time (tAAmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MINIMUM_CAS_LATENCY_TIME_TAAMIN_MSB_STRUCT;

/*  SDRAM Minimum RAS to CAS Delay Time (tRCDmin) Byte 32 (0x020): Least Significant Byte  */

#define SPD_SDRAM_MINIMUM_RAS_TO_CAS_DELAY_TIME_TRCDMIN_LSB_REG       0x0020

typedef union {
  struct {
    UINT8 sdram_minimum_ras_to_cas_delay_time_trcdmin_ps : 8;
                            /* Bits[0:7]
                               SDRAM Minimum RAS to CAS Delay Time (tRCDmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MINIMUM_RAS_TO_CAS_DELAY_TIME_TRCDMIN_LSB_STRUCT;

/*  SDRAM Minimum RAS to CAS Delay Time (tRCDmin) Byte 33 (0x021): Most Significant Byte   */

#define SPD_SDRAM_MINIMUM_RAS_TO_CAS_DELAY_TIME_TRCDMIN_MSB_REG       0x0021

typedef union {
  struct {
    UINT8 sdram_minimum_ras_to_cas_delay_time_trcdmin_ps : 8;
                            /* Bits[0:7]
                               SDRAM Minimum RAS to CAS Delay Time (tRCDmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MINIMUM_RAS_TO_CAS_DELAY_TIME_TRCDMIN_MSB_STRUCT;

/*  SDRAM Minimum Row Precharge Delay Time (tRPmin) Byte 34 (0x022): Least Significant Byte  */

#define SPD_SDRAM_MINIMUM_ROW_PRECHARGE_DELAY_TIME_TRPMIN_LSB_REG       0x0022

typedef union {
  struct {
    UINT8 sdram_minimum_row_precharge_delay_time_trpmin_ps : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Row Precharge Delay Time (tRPmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MINIMUM_ROW_PRECHARGE_DELAY_TIME_TRPMIN_LSB_STRUCT;

/*  SDRAM Minimum Row Precharge Delay Time (tRPmin) Byte 35 (0x023): Most Significant Byte   */

#define SPD_SDRAM_MINIMUM_ROW_PRECHARGE_DELAY_TIME_TRPMIN_MSB_REG       0x0023

typedef union {
  struct {
    UINT8 sdram_minimum_row_precharge_delay_time_trpmin_ps : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Row Precharge Delay Time (tRPmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MINIMUM_ROW_PRECHARGE_DELAY_TIME_TRPMIN_MSB_STRUCT;

/*  SDRAM Minimum Active to Precharge Delay Time (tRASmin) Byte 36 (0x024): Least Significant Byte  */

#define SPD_SDRAM_MIN_ACTIVE_TO_PRECHARGE_DELAY_TRAS_LSB_REG       0x0024

typedef union {
  struct {
    UINT8 sdram_min_active_to_precharge_delay_tras : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Active to Precharge Delay Time (tRASmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MIN_ACTIVE_TO_PRECHARGE_DELAY_TRAS_LSB_STRUCT;

/*  SDRAM Minimum Active to Precharge Delay Time (tRASmin) Byte 37 (0x025): Most Significant Byte   */

#define SPD_SDRAM_MIN_ACTIVE_TO_PRECHARGE_DELAY_TRAS_MSB_REG       0x0025

typedef union {
  struct {
    UINT8 sdram_min_active_to_precharge_delay_tras : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Active to Precharge Delay Time (tRASmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MIN_ACTIVE_TO_PRECHARGE_DELAY_TRAS_MSB_STRUCT;

/*  SDRAM Minimum Active to Active/Refresh Delay Time (tRCmin) Byte 38 (0x026): Least Significant Byte  */

#define SPD_SDRAM_MIN_ACTIVE_TO_ACTIVE_REFRESH_DELAY_TRC_LSB_REG       0x0026

typedef union {
  struct {
    UINT8 sdram_min_active_to_active_refresh_delay_trc : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Active to Active/Refresh Delay Time (tRCmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MIN_ACTIVE_TO_ACTIVE_REFRESH_DELAY_TRC_LSB_STRUCT;

/*  SDRAM Minimum Active to Active/Refresh Delay Time (tRCmin) Byte 39 (0x027): Most Significant Byte   */

#define SPD_SDRAM_MIN_ACTIVE_TO_ACTIVE_REFRESH_DELAY_TRC_MSB_REG       0x0027

typedef union {
  struct {
    UINT8 sdram_min_active_to_active_refresh_delay_trc : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Active to Active/Refresh Delay Time (tRCmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MIN_ACTIVE_TO_ACTIVE_REFRESH_DELAY_TRC_MSB_STRUCT;

/*  SDRAM Minimum Write Recovery Time (tWRmin) Byte 40 (0x028): Least Significant Byte  */

#define SPD_SDRAM_MINIMUM_WRITE_RECOVERY_TIME_TWRMIN_LSB_REG       0x0028

typedef union {
  struct {
    UINT8 sdram_minimum_write_recovery_time_twrmin_ps : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Write Recovery Time (tWRmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MINIMUM_WRITE_RECOVERY_TIME_TWRMIN_LSB_STRUCT;

/*  SDRAM Minimum Write Recovery Time (tWRmin) Byte 41 (0x029): Most Significant Byte   */

#define SPD_SDRAM_MINIMUM_WRITE_RECOVERY_TIME_TWRMIN_MSB_REG       0x0029

typedef union {
  struct {
    UINT8 sdram_minimum_write_recovery_time_twrmin_ps : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Write Recovery Time (tWRmin) ps
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MINIMUM_WRITE_RECOVERY_TIME_TWRMIN_MSB_STRUCT;

/*  SDRAM Minimum Refresh Recovery Delay Time (tRFC1min, tRFC1 slr min) Byte 42 (0x02A): Least Significant Byte  */

#define SPD_SDRAM_MIN_REFRESH_RECOVERY_DELAY_TRFC1_SLR_LSB_REG       0x002A

typedef union {
  struct {
    UINT8 sdram_min_refresh_recovery_delay_trfc1_slr : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Refresh Recovery Delay Time (tRFC1min, tRFC1_slr min) ns
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MIN_REFRESH_RECOVERY_DELAY_TRFC1_SLR_LSB_STRUCT;

/*  SDRAM Minimum Refresh Recovery Delay Time (tRFC1min, tRFC1 slr min) Byte 43 (0x02B): Most Significant Byte   */

#define SPD_SDRAM_MIN_REFRESH_RECOVERY_DELAY_TRFC1_SLR_MSB_REG       0x002B

typedef union {
  struct {
    UINT8 sdram_min_refresh_recovery_delay_trfc1_slr : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Refresh Recovery Delay Time (tRFC1min, tRFC1_slr min) ns
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MIN_REFRESH_RECOVERY_DELAY_TRFC1_SLR_MSB_STRUCT;

/*  SDRAM Minimum Refresh Recovery Delay Time (tRFC2min, tRFC2 slr min) Byte 44 (0x02C): Least Significant Byte  */

#define SPD_SDRAM_MIN_REFRESH_RECOVERY_DELAY_TRFC2_SLR_LSB_REG       0x002C

typedef union {
  struct {
    UINT8 sdram_min_refresh_recovery_delay_trfc2_slr : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Refresh Recovery Delay Time (tRFC2min, tRFC2_slr min) ns
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MIN_REFRESH_RECOVERY_DELAY_TRFC2_SLR_LSB_STRUCT;

/*  SDRAM Minimum Refresh Recovery Delay Time (tRFC2min, tRFC2 slr min) Byte 45 (0x02D): Most Significant Byte   */

#define SPD_SDRAM_MIN_REFRESH_RECOVERY_DELAY_TRFC2_SLR_MSB_REG       0x002D

typedef union {
  struct {
    UINT8 sdram_min_refresh_recovery_delay_trfc2_slr : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Refresh Recovery Delay Time (tRFC2min, tRFC2_slr min) ns
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MIN_REFRESH_RECOVERY_DELAY_TRFC2_SLR_MSB_STRUCT;

/*  SDRAM Minimum Refresh Recovery Delay Time (tRFCsbmin, tRFCsb slr min) Byte 46 (0x02E): Least Significant Byte  */

#define SPD_SDRAM_MIN_REFRESH_RECOVERY_DELAY_TRFCSB_SLR_LSB_REG       0x002E

typedef union {
  struct {
    UINT8 sdram_min_refresh_recovery_delay_trfcsb : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Refresh Recovery Delay Time (tRFCsbmin) ns
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MIN_REFRESH_RECOVERY_DELAY_TRFCSB_SLR_LSB_STRUCT;

/*  SDRAM Minimum Refresh Recovery Delay Time (tRFCsbmin, tRFCsb slr min) Byte 47 (0x02F): Most Significant Byte   */

#define SPD_SDRAM_MIN_REFRESH_RECOVERY_DELAY_TRFCSB_SLR_MSB_REG       0x002F

typedef union {
  struct {
    UINT8 sdram_min_refresh_recovery_delay_trfcsb : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Refresh Recovery Delay Time (tRFCsbmin) ns
                            */
  } Bits;
  UINT8 Data;
} SDRAM_MIN_REFRESH_RECOVERY_DELAYE_TRFCSB_SLR_MSB_STRUCT;

/*  SDRAM Minimum Refresh Recovery Delay Time, 3DS Different Logical Rank (tRFC1 dlr min) Byte 48 (0x030): Least Significant Byte  */

#define SPD_MIN_REFRESH_RECOVERY_DELAY_3DS_DIFF_LOGIC_RANK_TRFC1_LSB_REG       0x0030

typedef union {
  struct {
    UINT8 sdram_min_refresh_recovery_delay_trfc1_dlr : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Refresh Recovery Delay Time (tRFC1_dlr min) ns
                            */
  } Bits;
  UINT8 Data;
} MIN_REFRESH_RECOVERY_DELAY_3DS_DIFF_LOGIC_RANK_TRFC1_LSB_STRUCT;

/*  SDRAM Minimum Refresh Recovery Delay Time, 3DS Different Logical Rank (tRFC1 dlr min) Byte 49 (0x031): Most Significant Byte   */

#define SPD_MIN_REFRESH_RECOVERY_DELAY_3DS_DIFF_LOGIC_RANK_TRFC1_MSB_REG       0x0031

typedef union {
  struct {
    UINT8 sdram_min_refresh_recovery_delay_trfc1_dlr : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Refresh Recovery Delay Time (tRFC1_dlr min) ns
                            */
  } Bits;
  UINT8 Data;
} MIN_REFRESH_RECOVERY_DELAY_3DS_DIFF_LOGIC_RANK_TRFC1_MSB_STRUCT;

/*  SDRAM Minimum Refresh Recovery Delay Time, 3DS Different Logical Rank (tRFC2 dlr min) Byte 50 (0x032): Least Significant Byte  */

#define SPD_MIN_REFRESH_RECOVERY_DELAY_3DS_DIFF_LOGIC_RANK_TRFC2_LSB_REG       0x0032

typedef union {
  struct {
    UINT8 sdram_min_refresh_recovery_delay_trfc2_dlr : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Refresh Recovery Delay Time (tRFC2_dlr min) ns
                            */
  } Bits;
  UINT8 Data;
} MIN_REFRESH_RECOVERY_DELAY_3DS_DIFF_LOGIC_RANK_TRFC2_LSB_STRUCT;

/*  SDRAM Minimum Refresh Recovery Delay Time, 3DS Different Logical Rank (tRFC2 dlr min) Byte 51 (0x033): Most Significant Byte   */

#define SPD_MIN_REFRESH_RECOVERY_DELAY_3DS_DIFF_LOGIC_RANK_TRFC2_MSB_REG       0x0033

typedef union {
  struct {
    UINT8 sdram_min_refresh_recovery_delay_trfc2_dlr : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Refresh Recovery Delay Time (tRFC2_dlr min) ns
                            */
  } Bits;
  UINT8 Data;
} MIN_REFRESH_RECOVERY_DELAY_3DS_DIFF_LOGIC_RANK_TRFC2_MSB_STRUCT;

/*  SDRAM Minimum Refresh Recovery Delay Time, 3DS Different Logical Rank (tRFCsb dlr min) Byte 52 (0x034): Least Significant Byte  */

#define SPD_MIN_REFRESH_RECOVERY_DELAY_3DS_DIFF_LOGIC_RANK_TRFCSB_LSB_REG       0x0034

typedef union {
  struct {
    UINT8 sdram_min_refresh_recovery_delay_trfcsb_dlr : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Refresh Recovery Delay Time (tRFCsb_dlr min) ns
                            */
  } Bits;
  UINT8 Data;
} MIN_REFRESH_RECOVERY_DELAY_3DS_DIFF_LOGIC_RANK_TRFCSB_LSB_STRUCT;

/*  SDRAM Minimum Refresh Recovery Delay Time, 3DS Different Logical Rank (tRFCsb dlr min) Byte 53 (0x035): Most Significant Byte   */

#define SPD_MIN_REFRESH_RECOVERY_DELAY_3DS_DIFF_LOGIC_RANK_TRFCSB_MSB_REG       0x0035

typedef union {
  struct {
    UINT8 sdram_min_refresh_recovery_delay_trfcsb_dlr : 8;
                            /* Bits[0:7]
                               SDRAM Minimum Refresh Recovery Delay Time (tRFCsb_dlr min) ns
                            */
  } Bits;
  UINT8 Data;
} MIN_REFRESH_RECOVERY_DELAY_3DS_DIFF_LOGIC_RANK_TRFCSB_MSB_STRUCT;

/*  Primary SDRAM Refresh Management Byte 54 (0x036): First Byte  */

#define SPD_PRIMARY_SDRAM_REFRESH_MANAGEMENT_0_REG       0x0036

typedef union {
  struct {
    UINT8 rfm_required : 1;
                            /* Bits[0]
                               RFM Required
                               0: Refresh management not required
                               1: Refresh management required
                            */
    UINT8 raaimt : 4;
                            /* Bits[1:4]
                               RAAIMT
                               0000-0011: Reserved
                               0100: 32 (Normal), 16 (FGR)
                               0101: 40 (Normal), 20 (FGR)
                               ...
                               1001: 72 (Normal), 36 (FGR)
                               1010: 80 (Normal), 40 (FGR)
                               All other codings
                               reserved
                            */
    UINT8 raammt : 3;
                            /* Bits[5:7]
                               RAAMMT
                               000~010: Reserved
                               011: 3X (Normal), 6X (FGR)
                               100: 4X (Normal), 8X (FGR)
                               101: 5X (Normal), 10X (FGR)
                               110: 6X (Normal), 12X (FGR)
                               111: Reserved
                            */
  } Bits;
  UINT8 Data;
} PRIMARY_SDRAM_REFRESH_MANAGEMENT_0_STRUCT;

/*  Primary SDRAM Refresh Management Byte 55 (0x037): Second Byte  */

#define SPD_PRIMARY_SDRAM_REFRESH_MANAGEMENT_1_REG       0x0037

typedef union {
  struct {
    UINT8 reserved_0_3 : 4;
                            /* Bits[0:3]
                               Reserved
                               Reserved
                               must be coded as 0000
                            */
    UINT8 arfm_level : 2;
                            /* Bits[4:5]
                               Reserved
                               must be coded in the SPD as 00
                               modified by the host controller in the SDRAM to select ARFM Leve
                            */
    UINT8 rfm_raa_counter_decrement_per_ref_command : 2;
                            /* Bits[6:7]
                               RFM RAA Counter Decrement per REF command
                               00: RAAIMT
                               01: RAAIMT / 2
                               Other codes reserved
                            */
  } Bits;
  UINT8 Data;
} PRIMARY_SDRAM_REFRESH_MANAGEMENT_1_STRUCT;

/*  Secondary SDRAM Refresh Management Byte 56 (0x038): First Byte  */

#define SPD_SECONDARY_SDRAM_REFRESH_MANAGEMENT_0_REG       0x0038

typedef union {
  struct {
    UINT8 rfm_required : 1;
                            /* Bits[0]
                               RFM Required
                               0: Refresh management not required
                               1: Refresh management required
                            */
    UINT8 raaimt : 4;
                            /* Bits[1:4]
                               RAAIMT
                               0000-0011: Reserved
                               0100: 32 (Normal), 16 (FGR)
                               0101: 40 (Normal), 20 (FGR)
                               ...
                               1001: 72 (Normal), 36 (FGR)
                               1010: 80 (Normal), 40 (FGR)
                               All other codings
                               reserved
                            */
    UINT8 raammt : 3;
                            /* Bits[5:7]
                               RAAMMT
                               000~010: Reserved
                               011: 3X (Normal), 6X (FGR)
                               100: 4X (Normal), 8X (FGR)
                               101: 5X (Normal), 10X (FGR)
                               110: 6X (Normal), 12X (FGR)
                               111: Reserved
                            */
  } Bits;
  UINT8 Data;
} SECONDARY_SDRAM_REFRESH_MANAGEMENT_0_STRUCT;

/*  Secondary SDRAM Refresh Management Byte 57 (0x039): Second Byte  */

#define SPD_SECONDARY_SDRAM_REFRESH_MANAGEMENT_1_REG       0x0039

typedef union {
  struct {
    UINT8 reserved_0_3 : 4;
                            /* Bits[0:3]
                               Reserved
                               Reserved
                               must be coded as 0000
                            */
    UINT8 arfm_level : 2;
                            /* Bits[4:5]
                               Reserved
                               must be coded in the SPD as 00
                               modified by the host controller in the SDRAM to select ARFM Leve
                            */
    UINT8 rfm_raa_counter_decrement_per_ref_command : 2;
                            /* Bits[6:7]
                               RFM RAA Counter Decrement per REF command
                               00: RAAIMT
                               01: RAAIMT / 2
                               Other codes reserved
                            */
  } Bits;
  UINT8 Data;
} SECONDARY_SDRAM_REFRESH_MANAGEMENT_1_STRUCT;

/*  First SDRAM Adaptive Refresh Management (ARFM) Byte 58 (0x03A): First Byte  */

#define SPD_FIRST_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_A_0_REG       0x003A

typedef union {
  struct {
    UINT8 arfm_level : 1;
                            /* Bits[0]
                               ARFM Level
                               0: ARFM Level not supported
                               1: ARFM Level supported
                            */
    UINT8 raaimt : 4;
                            /* Bits[1:4]
                               RAAIMT
                               0000-0011: Reserved
                               0100: 32 (Normal), 16 (FGR)
                               0101: 40 (Normal), 20 (FGR)
                               ...
                               1001: 72 (Normal), 36 (FGR)
                               1010: 80 (Normal), 40 (FGR)
                               All other codings
                               reserved
                            */
    UINT8 raammt : 3;
                            /* Bits[5:7]
                               RAAMMT
                               000~010: Reserved
                               011: 3X (Normal), 6X (FGR)
                               100: 4X (Normal), 8X (FGR)
                               101: 5X (Normal), 10X (FGR)
                               110: 6X (Normal), 12X (FGR)
                               111: Reserved
                            */
  } Bits;
  UINT8 Data;
} FIRST_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_A_0_STRUCT;

/*  First SDRAM Adaptive Refresh Management (ARFM) Byte 59 (0x03B): Second Byte  */

#define SPD_FIRST_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_A_1_REG       0x003B

typedef union {
  struct {
    UINT8 reserved_0_3 : 4;
                            /* Bits[0:3]
                               Reserved
                               Reserved
                               must be coded as 0000
                            */
    UINT8 arfm_level : 2;
                            /* Bits[4:5]
                               Reserved
                               must be coded in the SPD as 00
                               modified by the host controller in the SDRAM to select ARFM Leve
                            */
    UINT8 rfm_raa_counter_decrement_per_ref_command : 2;
                            /* Bits[6:7]
                               RFM RAA Counter Decrement per REF command
                               00: RAAIMT
                               01: RAAIMT / 2
                               Other codes reserved
                            */
  } Bits;
  UINT8 Data;
} FIRST_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_A_1_STRUCT;

/*  Second SDRAM Adaptive Refresh Management (ARFM) Byte 60 (0x03C): First Byte  */

#define SPD_SECOND_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_A_0_REG       0x003C

typedef union {
  struct {
    UINT8 arfm_level : 1;
                            /* Bits[0]
                               ARFM Level
                               0: ARFM Level not supported
                               1: ARFM Level supported
                            */
    UINT8 raaimt : 4;
                            /* Bits[1:4]
                               RAAIMT
                               0000-0011: Reserved
                               0100: 32 (Normal), 16 (FGR)
                               0101: 40 (Normal), 20 (FGR)
                               ...
                               1001: 72 (Normal), 36 (FGR)
                               1010: 80 (Normal), 40 (FGR)
                               All other codings
                               reserved
                            */
    UINT8 raammt : 3;
                            /* Bits[5:7]
                               RAAMMT
                               000~010: Reserved
                               011: 3X (Normal), 6X (FGR)
                               100: 4X (Normal), 8X (FGR)
                               101: 5X (Normal), 10X (FGR)
                               110: 6X (Normal), 12X (FGR)
                               111: Reserved
                            */
  } Bits;
  UINT8 Data;
} SECOND_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_A_0_STRUCT;

/*  Second SDRAM Adaptive Refresh Management (ARFM) Byte 61 (0x03D): Second Byte  */

#define SPD_SECOND_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_A_1_REG       0x003D

typedef union {
  struct {
    UINT8 reserved_0_3 : 4;
                            /* Bits[0:3]
                               Reserved
                               Reserved
                               must be coded as 0000
                            */
    UINT8 arfm_level : 2;
                            /* Bits[4:5]
                               Reserved
                               must be coded in the SPD as 00
                               modified by the host controller in the SDRAM to select ARFM Leve
                            */
    UINT8 rfm_raa_counter_decrement_per_ref_command : 2;
                            /* Bits[6:7]
                               RFM RAA Counter Decrement per REF command
                               00: RAAIMT
                               01: RAAIMT / 2
                               Other codes reserved
                            */
  } Bits;
  UINT8 Data;
} SECOND_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_A_1_STRUCT;

/*  First SDRAM Adaptive Refresh Management (ARFM) Byte 62 (0x03E): First Byte  */

#define SPD_FIRST_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_B_0_REG       0x003E

typedef union {
  struct {
    UINT8 arfm_level : 1;
                            /* Bits[0]
                               ARFM Level
                               0: ARFM Level not supported
                               1: ARFM Level supported
                            */
    UINT8 raaimt : 4;
                            /* Bits[1:4]
                               RAAIMT
                               0000-0011: Reserved
                               0100: 32 (Normal), 16 (FGR)
                               0101: 40 (Normal), 20 (FGR)
                               ...
                               1001: 72 (Normal), 36 (FGR)
                               1010: 80 (Normal), 40 (FGR)
                               All other codings
                               reserved
                            */
    UINT8 raammt : 3;
                            /* Bits[5:7]
                               RAAMMT
                               000~010: Reserved
                               011: 3X (Normal), 6X (FGR)
                               100: 4X (Normal), 8X (FGR)
                               101: 5X (Normal), 10X (FGR)
                               110: 6X (Normal), 12X (FGR)
                               111: Reserved
                            */
  } Bits;
  UINT8 Data;
} FIRST_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_B_0_STRUCT;

/*  First SDRAM Adaptive Refresh Management (ARFM) Byte 63 (0x03F): Second Byte  */

#define SPD_FIRST_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_B_1_REG       0x003F

typedef union {
  struct {
    UINT8 reserved_0_3 : 4;
                            /* Bits[0:3]
                               Reserved
                               Reserved
                               must be coded as 0000
                            */
    UINT8 arfm_level : 2;
                            /* Bits[4:5]
                               Reserved
                               must be coded in the SPD as 00
                               modified by the host controller in the SDRAM to select ARFM Leve
                            */
    UINT8 rfm_raa_counter_decrement_per_ref_command : 2;
                            /* Bits[6:7]
                               RFM RAA Counter Decrement per REF command
                               00: RAAIMT
                               01: RAAIMT / 2
                               Other codes reserved
                            */
  } Bits;
  UINT8 Data;
} FIRST_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_B_1_STRUCT;

/*  Second SDRAM Adaptive Refresh Management (ARFM) Byte 64 (0x040): First Byte  */

#define SPD_SECOND_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_B_0_REG       0x0040

typedef union {
  struct {
    UINT8 arfm_level : 1;
                            /* Bits[0]
                               ARFM Level
                               0: ARFM Level not supported
                               1: ARFM Level supported
                            */
    UINT8 raaimt : 4;
                            /* Bits[1:4]
                               RAAIMT
                               0000-0011: Reserved
                               0100: 32 (Normal), 16 (FGR)
                               0101: 40 (Normal), 20 (FGR)
                               ...
                               1001: 72 (Normal), 36 (FGR)
                               1010: 80 (Normal), 40 (FGR)
                               All other codings
                               reserved
                            */
    UINT8 raammt : 3;
                            /* Bits[5:7]
                               RAAMMT
                               000~010: Reserved
                               011: 3X (Normal), 6X (FGR)
                               100: 4X (Normal), 8X (FGR)
                               101: 5X (Normal), 10X (FGR)
                               110: 6X (Normal), 12X (FGR)
                               111: Reserved
                            */
  } Bits;
  UINT8 Data;
} SECOND_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_B_0_STRUCT;

/*  Second SDRAM Adaptive Refresh Management (ARFM) Byte 65 (0x041): Second Byte  */

#define SPD_SECOND_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_B_1_REG       0x0041

typedef union {
  struct {
    UINT8 reserved_0_3 : 4;
                            /* Bits[0:3]
                               Reserved
                               Reserved
                               must be coded as 0000
                            */
    UINT8 arfm_level : 2;
                            /* Bits[4:5]
                               Reserved
                               must be coded in the SPD as 00
                               modified by the host controller in the SDRAM to select ARFM Leve
                            */
    UINT8 rfm_raa_counter_decrement_per_ref_command : 2;
                            /* Bits[6:7]
                               RFM RAA Counter Decrement per REF command
                               00: RAAIMT
                               01: RAAIMT / 2
                               Other codes reserved
                            */
  } Bits;
  UINT8 Data;
} SECOND_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_B_1_STRUCT;

/*  First SDRAM Adaptive Refresh Management (ARFM) Byte 66 (0x042): First Byte  */

#define SPD_FIRST_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_C_0_REG       0x0042

typedef union {
  struct {
    UINT8 arfm_level : 1;
                            /* Bits[0]
                               ARFM Level
                               0: ARFM Level not supported
                               1: ARFM Level supported
                            */
    UINT8 raaimt : 4;
                            /* Bits[1:4]
                               RAAIMT
                               0000-0011: Reserved
                               0100: 32 (Normal), 16 (FGR)
                               0101: 40 (Normal), 20 (FGR)
                               ...
                               1001: 72 (Normal), 36 (FGR)
                               1010: 80 (Normal), 40 (FGR)
                               All other codings
                               reserved
                            */
    UINT8 raammt : 3;
                            /* Bits[5:7]
                               RAAMMT
                               000~010: Reserved
                               011: 3X (Normal), 6X (FGR)
                               100: 4X (Normal), 8X (FGR)
                               101: 5X (Normal), 10X (FGR)
                               110: 6X (Normal), 12X (FGR)
                               111: Reserved
                            */
  } Bits;
  UINT8 Data;
} FIRST_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_C_0_STRUCT;

/*  First SDRAM Adaptive Refresh Management (ARFM) Byte 67 (0x043): Second Byte  */

#define SPD_FIRST_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_C_1_REG       0x0043

typedef union {
  struct {
    UINT8 reserved_0_3 : 4;
                            /* Bits[0:3]
                               Reserved
                               Reserved
                               must be coded as 0000
                            */
    UINT8 arfm_level : 2;
                            /* Bits[4:5]
                               Reserved
                               must be coded in the SPD as 00
                               modified by the host controller in the SDRAM to select ARFM Leve
                            */
    UINT8 rfm_raa_counter_decrement_per_ref_command : 2;
                            /* Bits[6:7]
                               RFM RAA Counter Decrement per REF command
                               00: RAAIMT
                               01: RAAIMT / 2
                               Other codes reserved
                            */
  } Bits;
  UINT8 Data;
} FIRST_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_C_1_STRUCT;

/*  Second SDRAM Adaptive Refresh Management (ARFM) Byte 68 (0x044): First Byte  */

#define SPD_SECOND_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_C_0_REG       0x0044

typedef union {
  struct {
    UINT8 arfm_level : 1;
                            /* Bits[0]
                               ARFM Level
                               0: ARFM Level not supported
                               1: ARFM Level supported
                            */
    UINT8 raaimt : 4;
                            /* Bits[1:4]
                               RAAIMT
                               0000-0011: Reserved
                               0100: 32 (Normal), 16 (FGR)
                               0101: 40 (Normal), 20 (FGR)
                               ...
                               1001: 72 (Normal), 36 (FGR)
                               1010: 80 (Normal), 40 (FGR)
                               All other codings
                               reserved
                            */
    UINT8 raammt : 3;
                            /* Bits[5:7]
                               RAAMMT
                               000~010: Reserved
                               011: 3X (Normal), 6X (FGR)
                               100: 4X (Normal), 8X (FGR)
                               101: 5X (Normal), 10X (FGR)
                               110: 6X (Normal), 12X (FGR)
                               111: Reserved
                            */
  } Bits;
  UINT8 Data;
} SECOND_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_C_0_STRUCT;

/*  Second SDRAM Adaptive Refresh Management (ARFM) Byte 69 (0x045): Second Byte  */

#define SPD_SECOND_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_C_1_REG       0x0045

typedef union {
  struct {
    UINT8 reserved_0_3 : 4;
                            /* Bits[0:3]
                               Reserved
                               Reserved
                               must be coded as 0000
                            */
    UINT8 arfm_level : 2;
                            /* Bits[4:5]
                               Reserved
                               must be coded in the SPD as 00
                               modified by the host controller in the SDRAM to select ARFM Leve
                            */
    UINT8 rfm_raa_counter_decrement_per_ref_command : 2;
                            /* Bits[6:7]
                               RFM RAA Counter Decrement per REF command
                               00: RAAIMT
                               01: RAAIMT / 2
                               Other codes reserved
                            */
  } Bits;
  UINT8 Data;
} SECOND_SDRAM_ADAPTIVE_REFRESH_MANAGEMENT_LEVEL_C_1_STRUCT;

/*  SDRAM Minimum Downbin CAS Latency 3200 Byte 70 (0x046)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_3200_REG       0x0046

/*  SDRAM Minimum Downbin CAS Latency 3600 Byte 71 (0x047)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_3600_REG       0x0047

/*  SDRAM Minimum Downbin CAS Latency 4000 Byte 72 (0x048)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_4000_REG       0x0048

/*  SDRAM Minimum Downbin CAS Latency 4400 Byte 73 (0x049)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_4400_REG       0x0049

/*  SDRAM Minimum Downbin CAS Latency 4800 Byte 74 (0x04A)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_4800_REG       0x004A

/*  SDRAM Minimum Downbin CAS Latency 5200 Byte 75 (0x04B)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_5200_REG       0x004B

/*  SDRAM Minimum Downbin CAS Latency 5600 Byte 76 (0x04C)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_5600_REG       0x004C

/*  SDRAM Minimum Downbin CAS Latency 6000 Byte 77 (0x04D)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_6000_REG       0x004D

/*  SDRAM Minimum Downbin CAS Latency 6400 Byte 78 (0x04E)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_6400_REG       0x004E

/*  SDRAM Minimum Downbin CAS Latency 6800 Byte 79 (0x04F)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_6800_REG       0x004F

/*  SDRAM Minimum Downbin CAS Latency 7200 Byte 80 (0x050)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_7200_REG       0x0050

/*  SDRAM Minimum Downbin CAS Latency 7600 Byte 81 (0x051)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_7600_REG       0x0051

/*  SDRAM Minimum Downbin CAS Latency 8000 Byte 82 (0x052)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_8000_REG       0x0052

/*  SDRAM Minimum Downbin CAS Latency 8400 Byte 83 (0x053)  */

#define SPD_SDRAM_MINIMUM_DOWNBIN_CAS_LATENCY_8400_REG       0x0053


/*  (Common): SPD Revision for Module Information Byte 192 (0x0C0)  */

#define SPD_COMMON_SPD_REVISION_FOR_MODULE_INFORMATION_REG       0x00C0

/*  Common SPD Manufacturer ID Code, First Byte Byte 194 (0x0C2)  */

#define SPD_COMMON_SPD_MANUFACTURER_ID_CODE_0_REG       0x00C2

/*  Common SPD Manufacturer ID Code, Second Byte Byte 195 (0x0C3)  */

#define SPD_COMMON_SPD_MANUFACTURER_ID_CODE_1_REG       0x00C3

/*  Common SPD Device Type Byte 196 (0x0C4)  */

#define SPD_COMMON_SPD_DEVICE_TYPE_REG       0x00C4

typedef union {
  struct {
    UINT8 device_type : 4;
                            /* Bits[0:3]
                               Device Type
                               0000: SPD5118 (see JESD300-5)
                               0001: SPD5108 (see JESD300-5)
                               All other codes reserved
                            */
    UINT8 reserved_4_5 : 2;
                            /* Bits[4:5]
                               Reserved
                               Reserved. Must be coded as 00
                            */
    UINT8 devices_installed : 2;
                            /* Bits[6:7]
                               Devices Installed
                               Bit 7
                               0 = Not installed
                               1 = Installed
                               Bit 6 Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} COMMON_SPD_DEVICE_TYPE_STRUCT;

/*  Common SPD Device Revision Byte 197 (0x0C5)  */

#define SPD_COMMON_SPD_DEVICE_REVISION_REG       0x00C5

typedef union {
  struct {
    UINT8 minor_revision : 4;
                            /* Bits[0:3]
                               minor revision
                            */
    UINT8 major_revision : 4;
                            /* Bits[4:7]
                               major revision
                            */
  } Bits;
  UINT8 Data;
} COMMON_SPD_DEVICE_REVISION_STRUCT;

/*  Common PMIC 0 Manufacturer ID Code, First Byte Byte 198 (0x0C6)  */

#define SPD_COMMON_PMIC_0_MANUFACTURER_ID_CODE_0_REG       0x00C6

/*  Common PMIC 0 Manufacturer ID Code, Second Byte Byte 199 (0x0C7)  */

#define SPD_COMMON_PMIC_0_MANUFACTURER_ID_CODE_1_REG       0x00C7

/*  Common PMIC 0 Device Type Byte 200 (0x0C8)  */

#define SPD_COMMON_PMIC_0_DEVICE_TYPE_REG       0x00C8

typedef union {
  struct {
    UINT8 device_type : 4;
                            /* Bits[0:3]
                               Device Type
                               0000: PMIC5000 (see JESD301-1)
                               0001: PMIC5010 (see JESD301-1)
                               0010: PMIC5100 (see JESD301-2)
                               All other codes reserved
                            */
    UINT8 reserved_4_5 : 2;
                            /* Bits[4:5]
                               Reserved
                               Reserved. Must be coded as 00
                            */
    UINT8 devices_installed : 2;
                            /* Bits[6:7]
                               Devices Installed
                               Bit 7
                               0 = Not installed
                               1 = Installed
                               Bit 6
							   Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} COMMON_PMIC_0_DEVICE_TYPE_STRUCT;

/*  Common PMIC 0 Device Revision Byte 201 (0x0C9)  */

#define SPD_COMMON_PMIC_0_DEVICE_REVISION_REG       0x00C9

typedef union {
  struct {
    UINT8 minor_revision : 4;
                            /* Bits[0:3]
                               minor revision
                            */
    UINT8 major_revision : 4;
                            /* Bits[4:7]
                               major revision
                            */
  } Bits;
  UINT8 Data;
} COMMON_PMIC_0_DEVICE_REVISION_STRUCT;

/*  Common PMIC 1 Manufacturer ID Code, First Byte Byte 202 (0x0CA)  */

#define SPD_COMMON_PMIC_1_MANUFACTURER_ID_CODE_0_REG       0x0CA

/*  Common PMIC 1 Manufacturer ID Code, Second Byte Byte 203 (0x0CB)  */

#define SPD_COMMON_PMIC_1_MANUFACTURER_ID_CODE_1_REG       0x0CB

/*  Common PMIC 1 Device Type Byte 204 (0x0CC)  */

#define SPD_COMMON_PMIC_1_DEVICE_TYPE_REG       0x00CC

typedef union {
  struct {
    UINT8 device_type : 4;
                            /* Bits[0:3]
                               Device Type
                               0000: PMIC5000 (see JESD301-1)
                               0001: PMIC5010 (see JESD301-1)
                               0010: PMIC5100 (see JESD301-2)
                               All other codes reserved
                            */
    UINT8 reserved_4_5 : 2;
                            /* Bits[4:5]
                               Reserved
                               Reserved. Must be coded as 00
                            */
    UINT8 devices_installed : 2;
                            /* Bits[6:7]
                               Devices Installed
                               Bit 7
                               0 = Not installed
                               1 = Installed
                               Bit 6
							   Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} COMMON_PMIC_1_DEVICE_TYPE_STRUCT;

/*  Common PMIC 1 Device Revision Byte 205 (0x0CD)  */

#define SPD_COMMON_PMIC_1_DEVICE_REVISION_REG       0x00CD

typedef union {
  struct {
    UINT8 minor_revision : 4;
                            /* Bits[0:3]
                               minor revision
                            */
    UINT8 major_revision : 4;
                            /* Bits[4:7]
                               major revision
                            */
  } Bits;
  UINT8 Data;
} COMMON_PMIC_1_DEVICE_REVISION_STRUCT;

/*  Common PMIC 2 Manufacturer ID Code, First Byte Byte 206 (0x0CE)  */

#define SPD_COMMON_PMIC_2_MANUFACTURER_ID_CODE_0_REG       0x0CE

/*  Common PMIC 2 Manufacturer ID Code, Second Byte Byte 207 (0x0CF)  */

#define SPD_COMMON_PMIC_2_MANUFACTURER_ID_CODE_1_REG       0x0CF

/*  Common PMIC 2 Device Type Byte 208 (0x0D0)  */

#define SPD_COMMON_PMIC_2_DEVICE_TYPE_REG       0x00D0

typedef union {
  struct {
    UINT8 device_type : 4;
                            /* Bits[0:3]
                               Device Type
                               0000: PMIC5000 (see JESD301-1)
                               0001: PMIC5010 (see JESD301-1)
                               0010: PMIC5100 (see JESD301-2)
                               All other codes reserved
                            */
    UINT8 reserved_4_5 : 2;
                            /* Bits[4:5]
                               Reserved
                               Reserved. Must be coded as 00
                            */
    UINT8 devices_installed : 2;
                            /* Bits[6:7]
                               Devices Installed
                               Bit 7
                               0 = Not installed
                               1 = Installed
                               Bit 6
                               Reserved. Must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} COMMON_PMIC_2_DEVICE_TYPE_STRUCT;

/*  Common PMIC 2 Device Revision Byte 209 (0x0D1)  */

#define SPD_COMMON_PMIC_2_DEVICE_REVISION_REG       0x00D1

typedef union {
  struct {
    UINT8 minor_revision : 4;
                            /* Bits[0:3]
                               minor revision
                            */
    UINT8 major_revision : 4;
                            /* Bits[4:7]
                               major revision
                            */
  } Bits;
  UINT8 Data;
} COMMON_PMIC_2_DEVICE_REVISION_STRUCT;

/*  Common Thermal Sensors (TS) Manufacturer ID Code, First Byte Byte 210 (0x0D2)  */

#define SPD_COMMON_THERMAL_SENSORS_TS_MANUFACTURER_ID_CODE_0_REG       0x0D2

/*  Common Thermal Sensors (TS) Manufacturer ID Code, Second Byte Byte 211 (0x0D3)  */

#define SPD_COMMON_THERMAL_SENSORS_TS_MANUFACTURER_ID_CODE_1_REG       0x0D3

/*  Common Thermal Sensors (TS) Device Type Byte 212 (0x0D4)  */

#define SPD_COMMON_THERMAL_SENSORS_TS_DEVICE_TYPE_REG       0x00D4

typedef union {
  struct {
    UINT8 device_type : 4;
                            /* Bits[0:3]
                               Device Type
                               0000: TS5111 (see JESD302-1)
                               0001: TS5110 (see JESD302-1)
                               All other codes reserved
                            */
    UINT8 reserved_4_5 : 2;
                            /* Bits[4:5]
                               Reserved
                               Reserved. Must be coded as 00
                            */
    UINT8 devices_installed : 2;
                            /* Bits[6:7]
                               Devices Installed
                               Bit 7
                               0 = TS0 Not installed
                               1 = TS Installed
                               Bit 6
                               0 = TS1 Not installed
                               1 = TS1 Installed
                            */
  } Bits;
  UINT8 Data;
} COMMON_THERMAL_SENSORS_TS_DEVICE_TYPE_STRUCT;

/*  Common Thermal Sensors (TS) Device Revision Byte 213 (0x0D5)  */

#define SPD_COMMON_THERMAL_SENSORS_TS_DEVICE_REVISION_REG       0x00D5

typedef union {
  struct {
    UINT8 minor_revision : 4;
                            /* Bits[0:3]
                               minor revision
                            */
    UINT8 major_revision : 4;
                            /* Bits[4:7]
                               major revision
                            */
  } Bits;
  UINT8 Data;
} COMMON_THERMAL_SENSORS_TS_DEVICE_REVISION_STRUCT;

/*  (Common): Module Nominal Height Byte 230 (0x0E6)  */

#define SPD_COMMON_MODULE_NOMINAL_HEIGHT_REG       0x00E6

typedef union {
  struct {
    UINT8 module_nominal_height_max : 5;
                            /* Bits[0:4]
                               Module Nominal Height max, in mm (baseline height = 15 mm)
                               00000 = height <= 15 mm
                               00001 = 15 < height <= 16 mm
                               00010 = 16 < height <= 17 mm
                               00011 = 17 < height <= 18 mm
                               00100 = 18 < height <= 19 mm
                               01010 = 24 < height <= 25 mm
                               01011 = 25 < height <= 26 mm
                               01111 = 29 < height <= 30 mm
                               10000 = 30 < height <= 31 mm
                               10001 = 31 < height <= 32 mm
                               11111 = 45 mm < height
                            */
    UINT8 reserved_5_7 : 3;
                            /* Bits[5:7]
                               Reserved
                               Reserved
                               must be coded as 000
                            */
  } Bits;
  UINT8 Data;
} COMMON_MODULE_NOMINAL_HEIGHT_STRUCT;

/*  (Common): Module Maximum Thickness Byte 231 (0x0E7)  */

#define SPD_COMMON_MODULE_MAXIMUM_THICKNESS_REG       0x00E7

typedef union {
  struct {
    UINT8 module_maximum_thickness_max_front : 4;
                            /* Bits[0:3]
                               Module Maximum Thickness max, Front, in mm (baseline thickness = 1 mm)
                               0000 = thickness <= 1 mm
                               0001 = 1 < thickness <= 2 mm
                               0010 = 2 < thickness <= 3 mm
                               0011 = 3 < thickness <= 4 mm
                               1110 = 14 < thickness <= 15 mm
                               1111 = 15 < thickness
                            */
    UINT8 module_maximum_thickness_max_back : 4;
                            /* Bits[4:7]
                               Module Maximum Thickness max, Back, in mm (baseline thickness = 1 mm)
                               0000 = thickness <= 1 mm
                               0001 = 1 < thickness <= 2 mm
                               0010 = 2 < thickness <= 3 mm
                               0011 = 3 < thickness <= 4 mm
                               1110 = 14 < thickness <= 15 mm
                               1111 = 15 < thickness
                            */
  } Bits;
  UINT8 Data;
} COMMON_MODULE_MAXIMUM_THICKNESS_STRUCT;

/*  (Common): Reference Raw Card Used Byte 232 (0x0E8)  */

#define SPD_COMMON_REFERENCE_RAW_CARD_USED_REG       0x00E8

typedef union {
  struct {
    UINT8 reference_design : 5;
                            /* Bits[0:4]
                               Reference Design
                               00000 = A
                               00001 = B
                               00010 = C
                               00011 = D
                               00100 = E
                               00101 = F
                               00110 = G
                               00111 = H
                               01000 = J
                               01001 = K
                               01010 = L
                               01011 = M
                               01100 = N
                               01101 = P
                               01110 = R
                               01111 = T
                               10000 = U
                               10001 = V
                               10010 = W
                               10011 = Y
                               10100 = AA
                               10101 = AB
                               10110 = AC
                               10111 = AD
                               11000 = AE
                               11001 = AF
                               11010 = AG
                               11011 = AH
                               11100 = AJ
                               11101 = AK
                               11110 = Reserved
                               11111 = ZZ (No reference used)
                            */
    UINT8 design_revision : 3;
                            /* Bits[5:7]
                               Design Revision
                               000 = Revision 0
                               001 = Revision 1
                               010 = Revision 2
                               011 = Revision 3
                               100 = Revision 4
                               101 = Revision 5
                               110 = Revision 6
                               111 = Reserved
                            */
  } Bits;
  UINT8 Data;
} COMMON_REFERENCE_RAW_CARD_USED_STRUCT;

/*  (Common): DIMM Attributes Byte 233 (0x0E9)  */

#define SPD_COMMON_DIMM_ATTRIBUTES_REG       0x00E9

typedef union {
  struct {
    UINT8 of_rows_of_drams_on_module : 2;
                            /* Bits[0:1]
                               # of rows of DRAMs on Module
                               00 = Undefined
                               01 = 1 row
                               10 = 2 rows
                               11 = Reserved
                            */
    UINT8 heat_spreader : 1;
                            /* Bits[2]
                               Heat Spreader
                               0 = Not installed
                               1 = Installed
                            */
    UINT8 reserved_3 : 1;
                            /* Bits[3]
                               Reserved
                               Reserved
                               must be coded as 0
                            */
    UINT8 operating_temperature_range : 4;
                            /* Bits[4:7]
                               Operating Temperature Range
                               0000 = A1T (-40 to +125 C)
                               0001 = A2T (-40 to +105 C)
                               0010 = A3T (-40 to +85 C)
                               0011 = IT (-40 to +90 C)
                               0100 = ST (-25 to +85 C)
                               0101 = ET (-25 to +105 C)
                               0110 = RT (0 to +45 C)
                               0111 = NT (0 to +85 C)
                               1000 = XT (0 to +95 C)
                               All other codings reserved
                            */
  } Bits;
  UINT8 Data;
} COMMON_DIMM_ATTRIBUTES_STRUCT;

/*  (Common): Module Organization Byte 234 (0x0EA)  */

#define SPD_COMMON_MODULE_ORGANIZATION_REG       0x00EA

typedef union {
  struct {
    UINT8 reserved_0_2 : 3;
                            /* Bits[0:2]
                               Reserved
                               Reserved
                               must be coded as 000
                            */
    UINT8 number_of_package_ranks_per_channel : 3;
                            /* Bits[3:5]
                               Number of Package Ranks per Channel
                               Bit [5, 4, 3] :
                               000 = 1 Package Rank
                               001 = 2 Package Ranks
                               010 = 3 Package Ranks
                               011 = 4 Package Ranks
                               100 = 5 Package Ranks
                               101 = 6 Package Ranks
                               110 = 7 Package Ranks
                               111 = 8 Package Ranks
                            */
    UINT8 rank_mix : 1;
                            /* Bits[6]
                               Rank Mix
                               0 = Symmetrical
                               1 = Asymmetrical
                            */
    UINT8 reserved_7 : 1;
                            /* Bits[7]
                               Reserved
                               Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} COMMON_MODULE_ORGANIZATION_STRUCT;

/*  (Common): Memory Channel Bus Width Byte 235 (0x0EB)  */

#define SPD_COMMON_MEMORY_CHANNEL_BUS_WIDTH_REG       0x00EB

typedef union {
  struct {
    UINT8 primary_bus_width_per_channel_in_bits : 3;
                            /* Bits[0:2]
                               Primary bus width per Channel, in bits
                               Bit [2, 1, 0] :
                               000 = 8 bits
                               001 = 16 bits
                               010 = 32 bits
                               011 = 64 bits All others reserved
                            */
    UINT8 bus_width_extension_per_channel_in_bits : 2;
                            /* Bits[3:4]
                               Bus width extension per Channel, in bits
                               Bit [4, 3] :
                               00 = 0 bits (no extension)
                               01 = 4 bits
                               10 = 8 bits All others reserved
                            */
    UINT8 number_of_channels_per_dimm : 2;
                            /* Bits[5:6]
                               Number of Channels per DIMM
                               Bit [6, 5] :
                               00 = 1 channel
                               01 = 2 channels All others reserved
                            */
    UINT8 reserved_7 : 1;
                            /* Bits[7]
                               Reserved
                               Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} COMMON_MEMORY_CHANNEL_BUS_WIDTH_STRUCT;

/*  Registered (RDIMM) or Load Reduced (LRDIMM) Registering Clock Driver (RCD) Manufacturer ID Code, First Byte Byte 240 (0x0F0)  */

#define SPD_RDIMM_LRDIMM_REGISTERING_CLOCK_DRIVER_RCD_MANUFACTURER_ID_CODE_0_REG       0x0F0

/*  Registered Differential Memory Buffer (DMB) Manufacturer ID Code, First Byte Byte 240 (0x0F0)  */

#define SPD_RDIMM_DIFFERENTIAL_MEMORY_BUFFER_DMB_MANUFACTURER_ID_CODE_0_REG       0x0F0

/*  NVDIMM-N Registering Clock Driver (RCD) Manufacturer ID Code, First Byte Byte 240 (0x0F0)  */

#define SPD_NVDIMM_N_REGISTERING_CLOCK_DRIVER_RCD_MANUFACTURER_ID_CODE_0_REG       0x0F0

/*  NVDIMM-P Registering Clock Driver (RCD) Manufacturer ID Code, First Byte Byte 240 (0x0F0)  */

#define SPD_NVDIMM_P_REGISTERING_CLOCK_DRIVER_RCD_MANUFACTURER_ID_CODE_0_REG       0x0F0

/*  Registered (RDIMM) or Load Reduced (LRDIMM) Registering Clock Driver (RCD) Manufacturer ID Code, Second Byte Byte 241 (0x0F1)  */

#define SPD_RDIMM_LRDIMM_REGISTERING_CLOCK_DRIVER_RCD_MANUFACTURER_ID_CODE_1_REG       0x0F1

/*  Registered Differential Memory Buffer (DMB) Manufacturer ID Code, Second Byte Byte 241 (0x0F1)  */

#define SPD_RDIMM_DIFFERENTIAL_MEMORY_BUFFER_DMB_MANUFACTURER_ID_CODE_1_REG       0x0F1

/*  NVDIMM-N Registering Clock Driver (RCD) Manufacturer ID Code, Second Byte Byte 241 (0x0F1)  */

#define SPD_NVDIMM_N_REGISTERING_CLOCK_DRIVER_RCD_MANUFACTURER_ID_CODE_1_REG       0x0F1

/*  NVDIMM-P Registering Clock Driver (RCD) Manufacturer ID Code, Second Byte Byte 241 (0x0F1)  */

#define SPD_NVDIMM_P_REGISTERING_CLOCK_DRIVER_RCD_MANUFACTURER_ID_CODE_1_REG       0x0F1

/*  Registered (RDIMM) or Load Reduced (LRDIMM) Registering Clock Driver (RCD) Device Type Byte 242 (0x0F2)  */

#define SPD_RDIMM_LRDIMM_REGISTERING_CLOCK_DRIVER_RCD_DEVICE_TYPE_REG       0x00F2

typedef union {
  struct {
    UINT8 device_type : 4;
                            /* Bits[0:3]
                               Device Type
                               0000: DDR5RCD01 (see JESD82-511)
                               0001: DDR5RCD02 (see JESD82-512)
                               All other codes reserved
                            */
    UINT8 reserved_4_5 : 2;
                            /* Bits[4:5]
                               Reserved
                               Reserved. Must be coded as 00
                            */
    UINT8 devices_installed : 2;
                            /* Bits[6:7]
                               Devices Installed
                               Bit 7
                               0 = Not installed
                               1 = Installed
                               Bit 6 Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} RDIMM_LRDIMM_REGISTERING_CLOCK_DRIVER_RCD_DEVICE_TYPE_STRUCT;

/*  Registered Differential Memory Buffer (DMB) Device Type Byte 242 (0x0F2)  */

#define SPD_RDIMM_DIFFERENTIAL_MEMORY_BUFFER_DMB_DEVICE_TYPE_REG       0x00F2

typedef union {
  struct {
    UINT8 device_type : 4;
                            /* Bits[0:3]
                               Device Type
                               0000: DMB501 (see JESD303-1)
                               All other codes reserved
                            */
    UINT8 reserved_4_5 : 2;
                            /* Bits[4:5]
                               Reserved
                               Reserved. Must be coded as 00
                            */
    UINT8 devices_installed : 2;
                            /* Bits[6:7]
                               Devices Installed
                               Bit 7
                               0 = Not installed
                               1 = Installed
                               Bit 6 Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} RDIMM_DIFFERENTIAL_MEMORY_BUFFER_DMB_DEVICE_TYPE_STRUCT;

/*  NVDIMM-N Registering Clock Driver (RCD) Device Type Byte 242 (0x0F2)  */

#define SPD_NVDIMM_N_REGISTERING_CLOCK_DRIVER_RCD_DEVICE_TYPE_REG       0x00F2

typedef union {
  struct {
    UINT8 device_type : 4;
                            /* Bits[0:3]
                               Device Type
                               0000: DDR5RCD01 (see JESD82-511)
                               All other codes reserved
                            */
    UINT8 reserved_4_5 : 2;
                            /* Bits[4:5]
                               Reserved
                               Reserved. Must be coded as 00
                            */
    UINT8 devices_installed : 2;
                            /* Bits[6:7]
                               Devices Installed
                               Bit 7
                               0 = Not installed
                               1 = Installed
                               Bit 6 Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} NVDIMM_N_REGISTERING_CLOCK_DRIVER_RCD_DEVICE_TYPE_STRUCT;

/*  NVDIMM-P Registering Clock Driver (RCD) Device Type Byte 242 (0x0F2)  */

#define SPD_NVDIMM_P_REGISTERING_CLOCK_DRIVER_RCD_DEVICE_TYPE_REG       0x00F2

typedef union {
  struct {
    UINT8 device_type : 4;
                            /* Bits[0:3]
                               Device Type
                               0000: DDR5RCD01 (see JESD82-511)
                               All other codes reserved
                            */
    UINT8 reserved_4_5 : 2;
                            /* Bits[4:5]
                               Reserved
                               Reserved. Must be coded as 00
                            */
    UINT8 devices_installed : 2;
                            /* Bits[6:7]
                               Devices Installed
                               Bit 7
                               0 = Not installed
                               1 = Installed
                               Bit 6 Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} NVDIMM_P_REGISTERING_CLOCK_DRIVER_RCD_DEVICE_TYPE_STRUCT;

/*  Registered (RDIMM) or Load Reduced (LRDIMM) Registering Clock Driver (RCD) Device Revision Byte 243 (0x0F3)  */

#define SPD_RDIMM_LRDIMM_REGISTERING_CLOCK_DRIVER_RCD_DEVICE_REVISION_REG       0x00F3

/*  Registered Differential Memory Buffer (DMB) Device Revision Byte 243 (0x0F3)  */

#define SPD_RDIMM_DIFFERENTIAL_MEMORY_BUFFER_DMB_DEVICE_REVISION_REG       0x00F3

/*  NVDIMM-N Registering Clock Driver (RCD) Device Revision Byte 243 (0x0F3)  */

#define SPD_NVDIMM_N_REGISTERING_CLOCK_DRIVER_RCD_DEVICE_REVISION_REG       0x00F3

/*  NVDIMM-P Registering Clock Driver (RCD) Device Revision Byte 243 (0x0F3)  */

#define SPD_NVDIMM_P_REGISTERING_CLOCK_DRIVER_RCD_DEVICE_REVISION_REG       0x00F3

/*  Load Reduced Data Buffers (DB) Manufacturer ID Code, First Byte Byte 244 (0x0F4)  */

#define SPD_LRDIMM_DBS_DB_MANUFACTURER_ID_CODE_0_REG       0x0F4

/*  NVDIMM-N Data Buffers (DB) Manufacturer ID Code, First Byte Byte 244 (0x0F4)  */

#define SPD_NVDIMM_N_DBS_DB_MANUFACTURER_ID_CODE_0_REG       0x0F4

/*  NVDIMM-P Data Buffers (DB) Manufacturer ID Code, First Byte Byte 244 (0x0F4)  */

#define SPD_NVDIMM_P_DBS_DB_MANUFACTURER_ID_CODE_0_REG       0x0F4

/*  Load Reduced Data Buffers (DB) Manufacturer ID Code, Second Byte Byte 245 (0x0F5)  */

#define SPD_LRDIMM_DBS_DB_MANUFACTURER_ID_CODE_1_REG       0x0F5

/*  NVDIMM-N Data Buffers (DB) Manufacturer ID Code, Second Byte Byte 245 (0x0F5)  */

#define SPD_NVDIMM_N_DBS_DB_MANUFACTURER_ID_CODE_1_REG       0x0F5

/*  NVDIMM-P Data Buffers (DB) Manufacturer ID Code, Second Byte Byte 245 (0x0F5)  */

#define SPD_NVDIMM_P_DBS_DB_MANUFACTURER_ID_CODE_1_REG       0x0F5

/*  Load Reduced Data Buffers (DB) Device Type Byte 246 (0x0F6)  */

#define SPD_LRDIMM_DBS_DB_DEVICE_TYPE_REG       0x00F6

typedef union {
  struct {
    UINT8 device_type : 4;
                            /* Bits[0:3]
                               Device Type
                               0000: DDR5DB01 (see JESD82-521)
                               0001: DDR5DB02 (see JESD82-522)
                               All other codes reserved
                               RDIMM: code as 0000
                            */
    UINT8 reserved_4_5 : 2;
                            /* Bits[4:5]
                               Reserved
                               Reserved. Must be coded as 00
                            */
    UINT8 devices_installed : 2;
                            /* Bits[6:7]
                               Devices Installed
                               Bit 7
                               0 = Not installed (RDIMM)
                               1 = Installed (LRDIMM)
                               Bit 6
                               Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} LRDIMM_DBS_DB_DEVICE_TYPE_STRUCT;

/*  NVDIMM-N Data Buffers (DB) Device Type Byte 246 (0x0F6)  */

#define SPD_NVDIMM_N_DBS_DB_DEVICE_TYPE_REG       0x00F6

typedef union {
  struct {
    UINT8 device_type : 4;
                            /* Bits[0:3]
                               Device Type
                               0000: DDR5DB01 (see JESD82-521)
                               All other codes reserved
                            */
    UINT8 reserved_4_5 : 2;
                            /* Bits[4:5]
                               Reserved
                               Reserved. Must be coded as 00
                            */
    UINT8 devices_installed : 2;
                            /* Bits[6:7]
                               Devices Installed
                               Bit 7
                               0 = Not installed
                               1 = Installed
                               Bit 6
                               Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} NVDIMM_N_DBS_DB_DEVICE_TYPE_STRUCT;

/*  NVDIMM-P Data Buffers (DB) Device Type Byte 246 (0x0F6)  */

#define SPD_NVDIMM_P_DBS_DB_DEVICE_TYPE_REG       0x00F6

typedef union {
  struct {
    UINT8 device_type : 4;
                            /* Bits[0:3]
                               Device Type
                               0000: DDR5DB01 (see JESD82-521)
                               All other codes reserved
                            */
    UINT8 reserved_4_5 : 2;
                            /* Bits[4:5]
                               Reserved
                               Reserved. Must be coded as 00
                            */
    UINT8 devices_installed : 2;
                            /* Bits[6:7]
                               Devices Installed
                               Bit 7
                               0 = Not installed
                               1 = Installed
                               Bit 6
                               Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} NVDIMM_P_DBS_DB_DEVICE_TYPE_STRUCT;

/*  Load Reduced Data Buffers (DB) Device Revision Byte 247 (0x0F7)  */

#define SPD_LRDIMM_DBS_DB_DEVICE_REVISION_REG       0x00F7

/*  NVDIMM-N Data Buffers (DB) Device Revision Byte 247 (0x0F7)  */

#define SPD_NVDIMM_N_DBS_DB_DEVICE_REVISION_REG       0x00F7

/*  NVDIMM-P Data Buffers (DB) Device Revision Byte 247 (0x0F7)  */

#define SPD_NVDIMM_P_DBS_DB_DEVICE_REVISION_REG       0x00F7

/*  RDIMM/LRDIMM RCD-RW08 Clock Driver Enable Byte 248 (0x0F8)  */

#define SPD_RDIMM_LRDIMM_RCD_RW08_Clock_Driver_Enable_REG       0x00F8

typedef union {
  struct {
    UINT8 qack_t_qack_c : 1;
                            /* Bits[0]
                               QACK_t/ QACK_c
                               0: Enabled
                               1: Disabled
                            */
    UINT8 qbck_t_qbck_c : 1;
                            /* Bits[1]
                               QBCK_t/ QBCK_c
                               0: Enabled
                               1: Disabled
                            */
    UINT8 qcck_t_qcck_c : 1;
                            /* Bits[2]
                               QCCK_t/ QCCK_c
                               0: Enabled
                               1: Disabled
                            */
    UINT8 qdck_t_qdck_c : 1;
                            /* Bits[3]
                               QDCK_t/ QDCK_c
                               0: Enabled
                               1: Disabled
                            */
    UINT8 reserved_4 : 1;
                            /* Bits[4]
                               Reserved
                               Reserved
                               must be coded as 0
                            */
    UINT8 bck_t_bck_c : 1;
                            /* Bits[5]
                               BCK_t/ BCK_c
                               0: Enabled
                               1: Disabled
                            */
    UINT8 reserved_6_7 : 2;
                            /* Bits[6:7]
                               Reserved
                               Reserved
                               must be coded as 00
                            */
  } Bits;
  UINT8 Data;
} RDIMM_LRDIMM_RCD_RW08_Clock_Driver_Enable_STRUCT;

/*  RDIMM/LRDIMM RCD-RW09 Output Address and Control Enable Byte 249 (0x0F9)  */

#define SPD_RDIMM_LRDIMM_RCD_RW09_OUTPUT_ADDRESS_AND_CONTROL_ENABLE_REG       0x00F9

typedef union {
  struct {
    UINT8 qaca_outputs : 1;
                            /* Bits[0]
                               QACA outputs
                               0: Enabled
                               1: Disabled
                            */
    UINT8 qbca_outputs : 1;
                            /* Bits[1]
                               QBCA outputs
                               0: Enabled
                               1: Disabled
                            */
    UINT8 dcs1_n_input_buffer_qxcs1_n_outputs : 1;
                            /* Bits[2]
                               DCS1_n input buffer & QxCS1_n outputs
                               0: Enabled
                               1: Disabled
                            */
    UINT8 bcs_n_bcom_brst_n_outputs : 1;
                            /* Bits[3]
                               BCS_n, BCOM[2:0] & BRST_n outputs
                               0: Enabled (LRDIMM)
                               1: Disabled (RDIMM)
                            */
    UINT8 qca13_output_driver : 1;
                            /* Bits[4]
                               Q[B:A]CA13 output driver
                               0 = Enabled
                               1 = Disabled
                            */
    UINT8 qacs_n_output : 1;
                            /* Bits[5]
                               QACS[1:0]_n output
                               0 = Enabled
                               1 = Disabled
                            */
    UINT8 qbcs_n_output : 1;
                            /* Bits[6]
                               QBCS[1:0]_n output
                               0 = Enabled
                               1 = Disabled
                            */
    UINT8 reserved_7 : 1;
                            /* Bits[7]
                               Reserved
                               Reserved
                               must be coded as 0
                            */
  } Bits;
  UINT8 Data;
} RDIMM_LRDIMM_RCD_RW09_OUTPUT_ADDRESS_AND_CONTROL_ENABLE_STRUCT;

/*  RDIMM/LRDIMM RCD-RW0A QCK Driver Characteristics Byte 250 (0x0FA)  */

#define SPD_RDIMM_LRDIMM_RCD_RW0A_QCK_DRIVER_CHARACTERISTICS_REG       0x00FA

typedef union {
  struct {
    UINT8 qack_t_qack_c : 2;
                            /* Bits[0:1]
                               QACK_t/QACK_c
                               00 = RZQ/12 (20 ohm)
                               01 = RZQ/17 (14 ohm)
                               10 = RZQ/24 (10 ohm)
                               11 = Reserved
                            */
    UINT8 qbck_t_qbck_c : 2;
                            /* Bits[2:3]
                               00 = RZQ/12 (20 ohm)
                               01 = RZQ/17 (14 ohm)
                               10 = RZQ/24 (10 ohm)
                               11 = Reserved
                            */
    UINT8 qcck_t_qcck_c : 2;
                            /* Bits[4:5]
                               QCCK_t/QCCK_c
                               00 = RZQ/12 (20 ohm)
                               01 = RZQ/17 (14 ohm)
                               10 = RZQ/24 (10 ohm)
                               11 = Reserved
                            */
    UINT8 qdck_t_qdck_c : 2;
                            /* Bits[6:7]
                               QDCK_t/QDCK_c
                               00 = RZQ/12 (20 ohm)
                               01 = RZQ/17 (14 ohm)
                               10 = RZQ/24 (10 ohm)
                               11 = Reserved
                            */
  } Bits;
  UINT8 Data;
} RDIMM_LRDIMM_RCD_RW0A_QCK_DRIVER_CHARACTERISTICS_STRUCT;

/*  RDIMM/LRDIMM RCD-RW0B Byte 251 (0x0FB)  */

#define SPD_RDIMM_LRDIMM_RCD_RW0B_REG       0x00FB

typedef union {
  struct {
    UINT8 reserved_0_7 : 8;
                            /* Bits[0:7]
                               Reserved
                               Reserved
                               must be coded as 00000000
                            */
  } Bits;
  UINT8 Data;
} RDIMM_LRDIMM_RCD_RW0B_STRUCT;


/*  RDIMM/LRDIMM RCD-RW0C QxCA and QxCS_n Driver Characteristics Byte 252 (0x0FC)  */

#define SPD_RDIMM_LRDIMM_RCD_RW0C_QXCA_AND_QXCS_DRIVER_CHARACTERISTICS_REG       0x00FC

typedef union {
  struct {
    UINT8 driver_strength_address_command_for_both_a_b_outputs : 2;
                            /* Bits[0:1]
                               Driver Strength Address/Command for both A&B outputs
                               00 = RZQ/12 (20 ohm)
                               01 = RZQ/17 (14 ohm)
                               10 = RZQ/24 (10 ohm)
                               11 = Reserved
                            */
    UINT8 reserved_2_3 : 2;
                            /* Bits[2:3]
                               Reserved
                               Reserved
                               must be coded as 00
                            */
    UINT8 driver_strength_qcs_qcck : 2;
                            /* Bits[4:5]
                               Driver Strength QxCS0_n, QxCS1_n, QCCK_t/QCCK_c
                               00 = RZQ/12 (20 ohm)
                               01 = RZQ/17 (14 ohm)
                               10 = RZQ/24 (10 ohm)
                               11 = Reserved
                            */
    UINT8 reserved_6_7 : 2;
                            /* Bits[6:7]
                               Reserved
                               Reserved
                               must be coded as 00
                            */
  } Bits;
  UINT8 Data;
} RDIMM_LRDIMM_RCD_RW0C_QXCA_AND_QXCS_DRIVER_CHARACTERISTICS_STRUCT;

/*  RDIMM/LRDIMM RCD-RW0D Data Buffer Interface Driver Characteristics Byte 253 (0x0FD)  */

#define SPD_RDIMM_LRDIMM_RCD_RW0D_DATA_BUFFER_INTERFACE_DRIVER_CHARACTERISTICS_REG       0x00FD

typedef union {
  struct {
    UINT8 driver_strength_bcom_bcs : 2;
                            /* Bits[0:1]
                               Driver Strength BCOM[2:0], BCS_n
                               00 = RZQ/12 (20 ohm)
                               01 = RZQ/17 (14 ohm)
                               10 = Reserved
                               11 = Reserved
                            */
    UINT8 reserved_2 : 1;
                            /* Bits[2]
                               Reserved
                               Reserved
                               must be coded as 0
                            */

    UINT8 driver_strength_bck : 2;
                            /* Bits[3:4]
                               Driver Strength BCK_t/BCK_c
                               00 = RZQ/12 (20 ohm)
                               01 = RZQ/17 (14 ohm)
                               10 = RZQ/24 (10 ohm)
                               11 = Reserved
                            */
    UINT8 reserved_5_7 : 3;
                            /* Bits[5:7]
                               Reserved
                               Reserved
                               must be coded as 000
                            */
  } Bits;
  UINT8 Data;
} RDIMM_LRDIMM_RCD_RW0D_DATA_BUFFER_INTERFACE_DRIVER_CHARACTERISTICS_STRUCT;

/*  RDIMM/LRDIMM RCD-RW0E QCK, QCA, and QCS Output Slew Rate Byte 254 (0x0FE)  */

#define SPD_RDIMM_LRDIMM_RCD_RW0E_QCK_QCA_AND_QCS_OUTPUT_SLEW_RATE_REG       0x00FE

typedef union {
  struct {
    UINT8 qck_differential_slew_rate : 2;
                            /* Bits[0:1]
                               QCK[D:A]_t/QCK[D:A]_c Differential Slew Rate
                               00 = Moderate (12-20 V/ns)
                               01 = Fast (14-27 V/ns)
                               10 = Reserved
                               11 = Reserved
                            */
    UINT8 qca_single_ended_slew_rate : 2;
                            /* Bits[2:3]
                               Q[B:A]CA[13:0] Single Ended Slew Rate
                               00 = Moderate (4-7 V/ns)
                               01 = Fast (6-10 V/ns)
                               10 = Slow (2.7-4.5 V/ns)
                               11 = Reserved
                            */
    UINT8 qcs_single_ended_slew_rate : 2;
                            /* Bits[4:5]
                               Q[B:A]CS[1:0]_n Single Ended Slew Rate
                               00 = Moderate (4-7 V/ns)
                               01 = Fast (6-10 V/ns)
                               10 = Slow (2.7-4.5 V/ns)
                               11 = Reserved
                            */
    UINT8 reserved_6_7 : 2;
                            /* Bits[6:7]
                               Reserved
                               Reserved
                               must be coded as 00
                            */
  } Bits;
  UINT8 Data;
} RDIMM_LRDIMM_RCD_RW0E_QCK_QCA_AND_QCS_OUTPUT_SLEW_RATE_STRUCT;

/*  RDIMM/LRDIMM RCD-RW0F BCK, BCOM, and BCS Output Slew Rate Byte 255 (0x0FF)  */

#define SPD_RDIMM_LRDIMM_RCD_RW0F_BCK_BCOM_BCS_OUTPUT_SLEW_RATE_REG       0x00FF

typedef union {
  struct {
    UINT8 bcom_bcs_single_ended_slew_rate : 2;
                            /* Bits[0:1]
                               BCOM[2:0], BCS_n Single Ended slew rate
                               00 = Moderate (3.7-6.7 V/ns)
                               01 = Fast (5.2-9.2 V/ns)
                               10 = Slow (2.5-4.3 V/ns)
                               11 = Reserved
                            */
    UINT8 bck_differential_slew_rate : 2;
                            /* Bits[2:3]
                               BCK_t/BCK_c Differential Slew Rate
                               00 = Moderate (12-20 V/ns)
                               01 = Fast (14-27 V/ns)
                               10 = Reserved
                               11 = Reserved
                            */
    UINT8 reserved_4_7 : 4;
                            /* Bits[4:7]
                               Reserved
                               Reserved
                               must be coded as 0000
                            */
  } Bits;
  UINT8 Data;
} RDIMM_LRDIMM_RCD_RW0F_BCK_BCOM_BCS_OUTPUT_SLEW_RATE_STRUCT;

/*  LRDIMM DB-RW86 DQS RTT Park Termination Byte 256 (0x100)  */

#define SPD_LRDIMM_DB_RW86_DQS_RTT_PARK_TERMINATION_REG       0x0100

typedef union {
  struct {
    UINT8 dqs_rtt_park_termination : 3;
                            /* Bits[0:2]
                               DQS RTT Park Termination
                               000 = RTT_OFF (default)
                               001 = RZQ/1 (240 ohm)
                               010 = RZQ/2 (120 ohm)
                               011 = RZQ/3 (80  ohm)
                               100 = RZQ/4 (60  ohm)
                               101 = RZQ/5 (48  ohm)
                               110 = RZQ/6 (40  ohm)
                               111 = RZQ/7 (34  ohm)
                            */
    UINT8 reserved_3_7 : 5;
                            /* Bits[3:7]
                               Reserved
                               Reserved
                               must be coded as 00000
                            */
  } Bits;
  UINT8 Data;
} LRDIMM_DB_RW86_DQS_RTT_PARK_TERMINATION_STRUCT;

/*  Byte 510 (0x1FE): Cyclical Redundancy Code (CRC) for SPD Bytes 0~509, Least Significant Byte  */

#define SPD_CRC_FOR_BYTES_0_509_LSB_REG       0x01FE

/*  Byte 511 (0x1FF): Cyclical Redundancy Code (CRC) for SPD Bytes 0~509, Most Significant Byte  */

#define SPD_CRC_FOR_BYTES_0_509_MSB_REG       0x01FF

/*  Byte 512 (0x200): Module Manufacturer ID Code, First Byte  */

#define SPD_MODULE_MANUFACTURER_ID_CODE_0_REG       0x0200

typedef union {
  struct {
    UINT8 number_of_continuation_codes_module_manufacturer : 7;
                            /* Bits[0:6]
                               Number of continuation codes, Module Manufacturer
                               See JEP-106
                            */
    UINT8 odd_parity_for_byte_512_bits_6_0 : 1;
                            /* Bits[7]
                               Odd Parity for Byte 512, bits 6~0
                            */
  } Bits;
  UINT8 Data;
} MODULE_MANUFACTURER_ID_CODE_0_STRUCT;

/*  Byte 513 (0x201): Module Manufacturer ID Code, Second Byte   */

#define SPD_MODULE_MANUFACTURER_ID_CODE_1_REG       0x0201

typedef union {
  struct {
    UINT8 last_non_zero_byte_module_manufacturer : 8;
                            /* Bits[0:7]
                               Last non-zero byte, Module Manufacturer
                               See JEP-106
                            */
  } Bits;
  UINT8 Data;
} MODULE_MANUFACTURER_ID_CODE_1_STRUCT;

/*  Byte 514 (0x202): Module Manufacturing Location  */

#define SPD_MODULE_MANUFACTURING_LOCATION_REG       0x202

/*  Byte 551 (0x227): Module Revision Code  */

#define SPD_MODULE_REVISION_CODE_REG       0x227

/*  Byte 552 (0x228): DRAM Manufacturer ID Code, First Byte  */

#define SPD_DRAM_MANUFACTURER_ID_CODE_0_REG       0x0228

typedef union {
  struct {
    UINT8 number_of_continuation_codes_dram_manufacturer : 7;
                            /* Bits[0:6]
                               Number of continuation codes, DRAM Manufacturer
                               See JEP-106
                            */
    UINT8 odd_parity_for_byte_552_bits_6_0 : 1;
                            /* Bits[7]
                               Odd Parity for Byte 552, bits 6~0
                            */
  } Bits;
  UINT8 Data;
} DRAM_MANUFACTURER_ID_CODE_0_STRUCT;

/*  Byte 553 (0x229): DRAM Manufacturer ID Code, Second Byte   */

#define SPD_DRAM_MANUFACTURER_ID_CODE_1_REG       0x0229

typedef union {
  struct {
    UINT8 last_non_zero_byte_dram_manufacturer : 8;
                            /* Bits[0:7]
                               Last non-zero byte, DRAM Manufacturer
                               See JEP-106
                            */
  } Bits;
  UINT8 Data;
} DRAM_MANUFACTURER_ID_CODE_1_STRUCT;

/*  Byte 554 (0x22A): DRAM Stepping  */

#define SPD_DRAM_STEPPING_REG       0x022A

typedef union {
  struct {
    UINT8 dram_stepping : 8;
                            /* Bits[0:7]
                               DRAM Stepping
                               Programmed in straight Hex format - no conversion needed. 00 - Valid
                               01 - Valid
                               FE - Valid
                               FF - Undefined (No Stepping Number Provided)
                            */
  } Bits;
  UINT8 Data;
} DRAM_STEPPING_STRUCT;

/*  Bytes 515~516 (0x203~0x204): Module Manufacturing Date
Byte 515 (0x203)  Module Manufacturing Date  */

#define SPD_MODULE_MANUFACTURING_DATE_0_REG       0x0203

/*  Bytes 515~516 (0x203~0x204): Module Manufacturing Date
Byte 516 (0x204)  Module Manufacturing Date  */

#define SPD_MODULE_MANUFACTURING_DATE_1_REG       0x0204

/*  Bytes 517~520 (0x205~0x208): Module Serial Number
Byte 517 (0x205)  Module Serial Number  */

#define SPD_MODULE_SERIAL_NUMBER_0_REG       0x0205

/*  Bytes 517~520 (0x205~0x208): Module Serial Number
Byte 518 (0x206)  Module Serial Number  */

#define SPD_MODULE_SERIAL_NUMBER_1_REG       0x0206

/*  Bytes 517~520 (0x205~0x208): Module Serial Number
Byte 519 (0x207)  Module Serial Number  */

#define SPD_MODULE_SERIAL_NUMBER_2_REG       0x0207

/*  Bytes 517~520 (0x205~0x208): Module Serial Number
Byte 520 (0x208)  Module Serial Number  */

#define SPD_MODULE_SERIAL_NUMBER_3_REG       0x0208

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 521 (0x209)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_0_REG       0x0209

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 522 (0x20A)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_1_REG       0x020A

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 523 (0x20B)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_2_REG       0x020B

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 524 (0x20C)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_3_REG       0x020C

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 525 (0x20D)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_4_REG       0x020D

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 526 (0x20E)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_5_REG       0x020E

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 527 (0x20F)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_6_REG       0x020F

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 528 (0x210)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_7_REG       0x0210

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 529 (0x211)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_8_REG       0x0211

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 530 (0x212)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_9_REG       0x0212

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 531 (0x213)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_10_REG       0x0213

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 532 (0x214)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_11_REG       0x0214

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 533 (0x215)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_12_REG       0x0215

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 534 (0x216)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_13_REG       0x0216

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 535 (0x217)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_14_REG       0x0217

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 536 (0x218)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_15_REG       0x0218

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 537 (0x219)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_16_REG       0x0219

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 538 (0x21A)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_17_REG       0x021A

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 539 (0x21B)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_18_REG       0x021B

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 540 (0x21C)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_19_REG       0x021C

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 541 (0x21D)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_20_REG       0x021D

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 542 (0x21E)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_21_REG       0x021E

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 543 (0x21F)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_22_REG       0x021F

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 544 (0x220)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_23_REG       0x0220

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 545 (0x221)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_24_REG       0x0221

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 546 (0x222)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_25_REG       0x0222

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 547 (0x223)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_26_REG       0x0223

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 548 (0x224)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_27_REG       0x0224

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 549 (0x225)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_28_REG       0x0225

/*  Bytes 521~550 (0x209~0x226): Module Part Number
Byte 550 (0x226)  Module Part Number  */

#define SPD_MODULE_PART_NUMBER_29_REG       0x0226

/*  Bytes 15 (0x00F) Reserved; must be coded as 0x00  */

/*  Byte 19 (0x013): Reserved, and all field is reserved  */

/*  Byte 29 (0x01D):Reserved, must be coded as 0x00  */

/*  Bytes 84~127 (0x054~0x07F): Reserved, Base Configuration Section Must be coded as 0x00  */

/*  (Common): Reserved, Byte 193 (0x0C1): Must be coded as 0x00  */

/*  (Common): Reserved Bytes 236~239 (0x0EC~0EF) Reserved -- must be coded as 0x00  */

/*  (Common): Module Type Specific Information Bytes 240~447 (0x0F0~0x1BF)  */

/*  (Solder Down): Bytes 240~445 (0x0F8~0x1BD) : Reserved -- must be coded as 0x00.  */

/*  (Unbuffered): Reserved Bytes 240~445 (0x0F8~0x1BD) Reserved -- must be coded as 0x00  */

/*  (Registered): Reserved Bytes 257~447 (0x101~0x1BF) Reserved -- must be coded as 0x00  */

/*  (Load Reduced): Reserved Bytes 257~447 (0x101~0x1BF) Reserved -- must be coded as 0x00  */

/*  (Differential): Reserved Bytes 204~445 (0x0CC~0x1BD) Reserved -- must be coded as 0x00  */

/*  (NVDIMM-N): Reserved Bytes 248~445 (0x0F8~0x1BD) Reserved -- must be coded as 0x00  */

/*  (NVDIMM-P): Reserved Bytes 248~445 (0x0F8~0x1BD) Reserved -- must be coded as 0x00  */

/*  Bytes 555~575 (0x22B~23F): Manufacturer's Specific Data  */

/*  Bytes 576~639 (0x240~27F): Manufacturer's Specific Data or Error Logging Data*/

/*  Bytes 638~639 (0x22A): Reserved, must be coded as 0x00  */

/*  End User Programmable, Bytes 640~1023 (0x280~0x3FF)  */
#endif  // #ifndef _DDR5_SPD_REGS_H_
