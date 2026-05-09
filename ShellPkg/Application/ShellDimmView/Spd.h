
#ifndef _SPD_DATA_H
#define _SPD_DATA_H

// Defines

#define DDR5_PAGE_BITWIDTH  0x4         // Number of bits each cached page occupies
#define DDR5_SPD_PAGE_MASK  0xF         // Used to keep only relevant page

#define SPD_DDR5_PAGE_SIZE        128 // Size of 1 SPD page for DDR5

#define SPD_DDR5_EUP_RANGE  0x280  // End User Programmable offset begins at 640 (0x280)

#define MEM_REG_SHIFT  7  // Bit7 is MemReg bit for DDR5 SPD Hub device

#define SPD_WRITE_TIME              5000  // 5 ms write time per Jedec SPD5xx8 Hub Spec

//
// Mask used in GetDimmTemperatureI3c to check the sign of the temperature
// xxx0 0000 0010 11xx + 2.75 C
// xxx1 1111 1111 11xx - 0.25 C
//
#define DIMM_TEMP_SIGNED_MASK 0x1FFC

//
// Mask used in GetDimmTemperatureI3c for sign extend in Dimm temperature
// if temperature is negative
//
#define DIMM_TEMP_SIGN_EXTEND_MASK 0xE000
//
// Shift the value to 0.5 C units
// Original value:
// xxx0 0000 0010 11xx + 2.75 C
// xxx1 1111 1111 11xx - 0.25 C
// So by shifting 3 bits (divide by 8) the value we got:
// 000 0000 0010 1 + 2.50 C
// 111 1111 1111 1 - 0.50 C
//
#define DIMM_TEMP_SHIFT_UNIT 8


//
// DDR5 specific 4-bit DTI(SPD5 Device Type ID) / LID(Local Device Type ID) Code
//
#define DDR5_TS0            0x02  // '0010' specifies TS0
#define DDR5_TS1            0x06  // '0110' specifies TS1
#define DTI_PMIC0           0x09  // '1001' specifies PMIC0
#define DTI_PMIC1           0x0C  // '1100' specifies PMIC1
#define DTI_EEPROM          0x0A  // '1010' specifies EEPROM's
#define DTI_RCD             0x0B  // '1011' specifies RCD

//
// SPD I2C addressing mode
//
#define I2C_LEGACY_MODE     0     // I2C Legacy Mode, 1 byte mode
#define I2C_2_BYTES_MODE    1     // I2C 2 bytes mode

//
// Structure which describes how addresses are conveyed to the SPD5 Hub device (DDR5)
//
typedef union {
  struct {
    UINT8 Address : 7; // Bits[6:0] - Address bits
    UINT8 MemReg : 1; // Bits[7]   - 1 for NVM location, 0 for internal register
  } Bits;
  UINT8 Data;
} SPD_DDR5_ADDRESS_FIRST_BYTE_STRUCT;

#define SPD_INTERNAL_REGISTER 0
#define SPD_NVM_LOCATION      1

//
// The second byte only used when MR[11] = 1 in I2C mode or in I3C mode
//
typedef union {
  struct {
    UINT8 blk_addr_3_1 : 3; // Bits[2:0] - SpdPage
    UINT8 rnw : 1;          // Bits[3]   - this field only applicable when PEC is enabled in I3C native mode. 0x0: Write 0x1: Read
    UINT8 cmd : 3;         // Bits[6:4] - this field only applicable when PEC is enabled in I3C native mode
    UINT8 rsvd_7 : 1;      // Bits[7]
  } Bits;
  UINT8 Data;
} SPD_DDR5_ADDRESS_SECOND_BYTE_STRUCT;

#define SMB_MR11_ADDR       0xB   // MR11 address

//
// Structure which describes how data is conveyed to MR11 for page selection (DDR5)
//
typedef union {
  struct {
    UINT8 Page : 3; // Bits[2:0] - Page to be selected
    UINT8 I2cLegacyMode : 1; // Bits[3]   - I2C Legacy Mode Addressing
    UINT8 Reserved : 4; // Bits[7:4] - Reserved
  } Bits;
  UINT8 Data;
} SPD_DDR5_MR11_STRUCT;

//
// Definitions for use with SMB_ADDRESS_STRUCT controller member,
// Enumerated Platform SMBUS controllers
//

#define PLATFORM_SMBUS_CONTROLLER_PROCESSOR   0
#define PLATFORM_SMBUS_CONTROLLER_PCH         1

///
/// SM Bus Address Data Structure.
//
typedef struct smbAddress {

  ///
  /// SPD I2C 2 bytes addressing mode
  //
  UINT16   I2cTwoBytesMode : 1;

  ///
  /// SM Bus slave address (0...7).
  //
  UINT16   strapAddress : 3;

  ///
  /// @brief
  /// SM Bus device type.<BR>
  /// @details
  ///   0x03 = TSOD.<BR>
  ///   0x06 = write-protect operation for an EEPROM.<BR>
  ///   0x0B = LRDIMM buffer.<BR>
  ///   0x05 = DCP_FIVE  DDR3 Vref control on the reference platform.<BR>
  ///   0x07 = DCP_SEVEN, an alternate for Vref control.<BR>
  ///   0x0A = EEPROM.<BR>
  ///   0x0B = NVMCTLR device.<BR>
  //
  UINT16   deviceType : 4;

  ///
  /// SMBus Instance.
  //
  UINT16   SmbInstance : 4;

  ///
  /// @brief
  /// SM Bus controller location.<BR>
  /// @details
  ///   0 = Processor.<BR>
  ///   1 = PCH.<BR>
  //
  UINT16   controller : 1;

  ///
  /// Socket on which the SM Bus controller resides
  //
  UINT16    SmbSocket : 3;
} SMB_ADDRESS_STRUCT;

//
// Definitions for use with SMB_DEVICE_STRUCT compId member,
// Enumerated Unique Platform Component IDs
//
#define NOT_INITIALIZED                 0
#define SPD                             1
#define DCP_ISL9072X                    2
#define DCP_AD5247                      3
#define MTS                             4  //TSOD
#define RSTPLD                          5
#define NO_DEV                          0xFFFF

typedef struct smbDevice {
  ///
  /// @brief
  /// Component ID.<BR>
  /// @details
  ///   1 = SPD.<BR>
  ///   2 = DCP_ISL9072X.<BR>
  ///   3 = DCP_AD5247.<BR>
  ///   4 = MTS.<BR>
  ///   5 = RSTPLD.<BR>
  ///   6 = NO_DEV.<BR>
  //
  UINT16              compId;

  ///
  /// I3cInstance Address
  //
  UINT32               I3cInstance;

  ///
  /// SM Bus device address.
  //
  SMB_ADDRESS_STRUCT  address;

  ///
  /// SPD Page Number.
  //
  UINT8               SpdPage;
} SMB_DEVICE_STRUCT;

#endif // !_SPD_DATA_H
