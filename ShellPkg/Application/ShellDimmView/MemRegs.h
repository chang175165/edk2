
#ifndef _memregs_h
#define _memregs_h

//
// Serial Presence Detect bytes (JEDEC revision 1.0)
//
#define SPD_KEY_BYTE          2     // DRAM Device Type  //BYTE 2 - keyByte

#define SPD_TYPE_DDR4         0x0C  // DDR4 SDRAM
#define SPD_TYPE_DDR5         0x12  // DDR5 SDRAM
#define SPD_TYPE_AEP          0x0D  // DDRT SDRAM

  #define SPD_RDIMM           1     // Module type is RDIMM
  #define SPD_UDIMM           2     // Module type is UDIMM
  #define SPD_SODIMM          3     // Module type is SODIMM
  #define SPD_LRDIMM_DDR5     4     // Module type is LRDIMM (DDR5)
  #define SPD_MCRDIMM_DDR5    7     // SPD key byte to identify MCR DIMM

  #define SPD_NUM_RANKS_1   0
  #define SPD_NUM_RANKS_2   1
  #define SPD_NUM_RANKS_4   3

#define SPD_DIMM_TS_MASK_DDR5 (BIT7 | BIT6) // Bit 7 - TS0; Bit 6 - T10

// Begin module specific section
 #define RAW_CARD_A         0
 #define RAW_CARD_B         1
 #define RAW_CARD_C         2
 #define RAW_CARD_D         3
 #define RAW_CARD_E         4
 #define RAW_CARD_F         5
 #define RAW_CARD_G         6
 #define RAW_CARD_H         7
 #define RAW_CARD_J         8
 #define RAW_CARD_K         9
 #define RAW_CARD_L         10
 #define RAW_CARD_M         11
 #define RAW_CARD_N         12
 #define RAW_CARD_P         13
 #define RAW_CARD_R         14
 #define RAW_CARD_T         15
 #define RAW_CARD_U         16
 #define RAW_CARD_V         17
 #define RAW_CARD_W         18
 #define RAW_CARD_Y         19
 #define RAW_CARD_AA        20
 #define RAW_CARD_AB        21
 #define RAW_CARD_AC        22
 #define RAW_CARD_AD        23
 #define RAW_CARD_AE        24
 #define RAW_CARD_AF        25
 #define RAW_CARD_AG        26
 #define RAW_CARD_AH        27
 #define RAW_CARD_AJ        28
 #define RAW_CARD_AK        29
 #define RAW_CARD_AL        30
 #define RAW_CARD_ZZ        0x1F
 #define RAW_CARD_MASK      0x1F
 #define RAW_CARD_REV_MASK             (BIT7 | BIT6 | BIT5)
 #define RAW_CARD_REV_OFFSET           5
 #define RAW_CARD_DESIGN_REV_RESERVED  0x7
 #define RAW_CARD_EXT       BIT7
 #define RAW_CARD_AM        (RAW_CARD_EXT + 0)
 #define RAW_CARD_AN        (RAW_CARD_EXT + 1)
 #define RAW_CARD_AP        (RAW_CARD_EXT + 2)
 #define RAW_CARD_AR        (RAW_CARD_EXT + 3)
 #define RAW_CARD_AT        (RAW_CARD_EXT + 4)
 #define RAW_CARD_AU        (RAW_CARD_EXT + 5)
 #define RAW_CARD_AV        (RAW_CARD_EXT + 6)
 #define RAW_CARD_AW        (RAW_CARD_EXT + 7)
 #define RAW_CARD_AY        (RAW_CARD_EXT + 8)
 #define RAW_CARD_BA        (RAW_CARD_EXT + 9)
 #define RAW_CARD_BB        (RAW_CARD_EXT + 10)
 #define RAW_CARD_BC        (RAW_CARD_EXT + 11)
 #define RAW_CARD_BD        (RAW_CARD_EXT + 12)
 #define RAW_CARD_BE        (RAW_CARD_EXT + 13)
 #define RAW_CARD_BF        (RAW_CARD_EXT + 14)
 #define RAW_CARD_BG        (RAW_CARD_EXT + 15)
 #define RAW_CARD_BH        (RAW_CARD_EXT + 16)
 #define RAW_CARD_BJ        (RAW_CARD_EXT + 17)
 #define RAW_CARD_BK        (RAW_CARD_EXT + 18)
 #define RAW_CARD_BL        (RAW_CARD_EXT + 19)
 #define RAW_CARD_BM        (RAW_CARD_EXT + 20)
 #define RAW_CARD_BN        (RAW_CARD_EXT + 21)
 #define RAW_CARD_BP        (RAW_CARD_EXT + 22)
 #define RAW_CARD_BR        (RAW_CARD_EXT + 23)
 #define RAW_CARD_BT        (RAW_CARD_EXT + 24)
 #define RAW_CARD_BU        (RAW_CARD_EXT + 25)
 #define RAW_CARD_BV        (RAW_CARD_EXT + 26)
 #define RAW_CARD_BW        (RAW_CARD_EXT + 27)
 #define RAW_CARD_BY        (RAW_CARD_EXT + 28)
 #define RAW_CARD_CA        (RAW_CARD_EXT + 29)
 #define RAW_CARD_CB        (RAW_CARD_EXT + 30)

//
//DIMM revision
//
//
 #define DIMM_REV_0          0
 #define DIMM_REV_1          1
 #define DIMM_REV_2          2
 #define DIMM_REV_3          3
 #define DIMM_REV_4          4
 #define DIMM_REV_5          5
 #define DIMM_REV_6          6

//
// DDR4 Specific Bytes
//
  #define SPD_SIGNAL_LOADING       (BIT0 | BIT1)         // Signal Loading Mask
  #define SPD_MULTI_LOAD_TYPE      BIT0
  #define SPD_3DS_TYPE             BIT1                  // Encoding for Single load stack (3DS)
  #define SPD_NON_MONOLITHIC_TYPE  BIT7
  #define SPD_MONOLITHIC_TYPE      0

  #define SPD_PPR_MASK        (BIT7 | BIT6) // Mask for PPR capability
    #define SPD_PPR_HARD_1R   BIT6  // Hard PPR with 1 row per BG
  #define SPD_SOFT_PPR        BIT5  // Soft PPR capability

#define SPD_HALF_SIZE_SECOND_RANK    BIT2
#define SPD_QUARTER_SIZE_SECOND_RANK BIT3

#define SPD_VDD_120           3     // Module operable and endurant 1.20V
#define SPD_VDD_110           0x0  // module Nominal, Operable and Endurant 1.10V, DDR5 SPD spec proposed

  #define SPD_BUS_WIDTH_EXT   (BIT3 | BIT4)  // Bus width extension mask (01 = 8 bit ECC)
  #define SPD_BUS_WIDTH_EXT_BIT_OFFSET   3   // Bit [4, 3]
  #define SPD_BUS_WIDTH_EXT_0_BITS_DDR5  0
  #define SPD_BUS_WIDTH_EXT_4_BITS_DDR5  1   // DDR5 only, No 4 bits ECC for DDR4
  #define SPD_BUS_WIDTH_EXT_8_BITS_DDR5  2   // DDR5 only, 8 bits ECC for DDR4 is encoded as 1

//
// RCD device type bit definations for SpdGetRcdRevision()
//
#define RCD_DEVICE_TYPE_GEN1_INTEL 0
#define RCD_DEVICE_TYPE_GEN1       1
#define RCD_DEVICE_TYPE_GEN2       2
#define RCD_DEVICE_TYPE_GEN3       3
#define RCD_DEVICE_TYPE_GEN4       4

#define SPD_RCD_DEVICE_TYPE_GEN1_INTEL 0x8

//
// AEP Dimm Specific Bytes Rev 2
//
#define FMC_BWV_TYPE                               0x7B
#define FMC_CWV_TYPE                               0x7C

#define SPD_INTEL_DIMM_SERIAL_NUMBER   0x3FB  // Intel Dimm Serial Number DDR5 (Bytes 1019~1023)

//
// TS5111, TS5110 Serial Bus Thermal Sensor Specification (JC40.1 July 25, 2019 Rev 0.76 JESD302-1 JEDEC STANDARD)
//
#define TS5_MR0_DEVICE_TYPE_MSB        0x00  // "MR0"  0x00 ROE: Device Type MSB
#define TS5_MR2_DEVICE_REVISION        0x02  // "MR2"  0x02 ROE: Device Revision
#define TS5_MR3_VENDOR_ID_0            0x03  // "MR3"  0x03 ROE: Vendor ID Byte 0
#define TS5_MR18_DEVICE_CONFIGURATION  0x12  // "MR18" 0x12 RW, RO Device Configuration
#define TS5_MR49_TEMP                  0x31  // "MR49" 0x31 RO: TS Current Sensed Temperature

//
// SPD5118, SPD5108 Hub and Serial Presence Detect Device Standard - Feb 2020 JESD300-5 JEDEC STANDARD
//
// MR Address Definitions
#define SPD_MR0_DEVICE_TYPE_MSB        0x00  // "MR0"  0x00 ROE: Device Type MSB
#define SPD_MR1_DEVICE_TYPE_LSB        0x01  // "MR1"  0x01 ROE: Device Type LSB
#define SPD_MR2_DEVICE_REVISION        0x02  // "MR2"  0x02 ROE: Device Revision
#define SPD_MR3_VENDOR_ID_0            0x03  // "MR3"  0x03 ROE: Vendor ID Byte 0
#define SPD_MR4_VENDOR_ID_1            0x04  // "MR4"  0x04 ROE: Vendor ID Byte 1
#define SPD_MR12_PROTECTION_CONFIG     0x0C  // "MR12" 0x0C RW: NVM Protection Configuration for Blocks [7:0]
#define SPD_MR13_PROTECTION_CONFIG     0x0D  // "MR13" 0x0D RW: NVM Protection Configuration for Blocks [15:8]
#define SPD_MR19_CLEAR_ERROR_CMD       0x13  // "MR19" 0x13 1O: Clear Register MR51 Error Status Command
#define SPD_MR27_INTERRUPT_CONFIG      0x1B  // "MR27" 0x1B 1O/RO/RW: Interrupt Configurations
#define SPD_MR28_TEMP_HIGH_0           0x1C  // "MR28" 0x1C RW: TS Temp High Limit Configuration - Low Byte
#define SPD_MR29_TEMP_HIGH_1           0x1D  // "MR29" 0x1D RW: TS Temp High Limit Configuration - High Byte
#define SPD_MR32_CRITICAL_TEMP_HIGH_0  0x20  // "MR32" 0x20 RW: TS Critical Temp High Limit Configuration - Low Byte
#define SPD_MR33_CRITICAL_TEMP_HIGH_1  0x21  // "MR33" 0x21 RW: TS Critical Temp High Limit Configuration - High Byte

#define MAX_SPD_HUB_REG  0x80 // 128 bytes volatile register space

// SPD Write-Protect Config Masks
#define SPD_WP_CONFIG_MASK_PP        0x003F  // "MR13:MR12" RW: Expected WP status for blocks [15:0], for modules with SPD rev [0.0 : 1.0), i.e. pre-production
#define SPD_WP_CONFIG_MASK_10        0x00FF  // "MR13:MR12" RW: Expected WP status for blocks [15:0], for modules with SPD rev [1.0 : 1.1)
#define SPD_WP_CONFIG_MASK_11        0x01FF  // "MR13:MR12" RW: Expected WP status for blocks [15:0], for modules with SPD rev [1.1 : ]

typedef union {
  struct {
    UINT8 Reserved : 1;
    /* RV 0 MR18[0]: Reserved */

    UINT8 DEF_RD_ADDR_POINT_BL : 1;
    /*  RW 0
        MR18[1]: DEF_RD_ADDR_POINT_BL
        Burst Length for Read Pointer Address for PEC Calculation
        0 = 2 Bytes
        1 = 4 Bytes
    */

    UINT8 DEF_RD_ADDR_POINT_START : 2;
    /*  RW 0
        MR18[3:2]: DEF_RD_ADDR_POINT_START
        Default Read Pointer Starting Address7
        00 = Table 93, "MR49"
        01 = Reserved
        10 = Reserved
        11 = Reserved
    */

    UINT8 DEF_RD_ADDR_POINT_EN : 1;
    /*  RW 0
        MR18[4]: DEF_RD_ADDR_POINT_EN
        Default Read Address Pointer Enable
        0 = Disable Default Read Address Pointer (Address pointer is set by the Host)
        1 = Enable Default Read Address Pointer;Address selected by register bits [3:2]
    */

    UINT8 INF_SEL : 1;
    /*  RO 0
        MR18[5]: INF_SEL
        Interface Selection
        0 = I2C Protocol (Max speed of 1 MHz)
        1 = I3C Basic Protocol
    */

    UINT8 PAR_DIS : 1;
    /*  RW 0
        MR18[6]: PAR_DIS
        Parity (T bit) Disable
        0 = Enable
        1 = Disable
    */
    UINT8 PEC_EN : 1;
    /*  RW 0
        MR18[7]: PEC_EN
        PEC Enable
        0 = Disable
        1 = Enable
    */

  } Bits;
  UINT8 Data;
} TS5_MR18_DEVICE_CONFIGURATION_STRUCT;


#endif // _memregs_h
