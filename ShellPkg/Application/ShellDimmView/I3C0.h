

#ifndef _I3C0_REGS_H_
#define _I3C0_REGS_H_

#define I3C_HCI_VERSION               0x52

#define DEVICE_CONTROL_I3C0_REG       0x004
typedef union {
  struct {
    UINT32 iba_include : 1; /**< IBA_INCLUDE */

                            /* Bits[0:0], Access Type=RW, default=0x00000001*/

                            /* --- */

    UINT32 iba_arb_bits : 3; /**< IBA_ARB_BITS */

                            /* Bits[3:1], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 reserved_4_6 : 3; /**< RESERVED_4_6 */

                            /* Bits[6:4], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 i2c_slave_present : 1; /**< I2C_SLAVE_PRESENT */

                            /* Bits[7:7], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 hot_join_ctrl : 1; /**< HOT_JOIN_CTRL */

                            /* Bits[8:8], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 reserved_9_28 : 20; /**< RESERVED_9_28 */

                            /* Bits[28:9], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 abort : 1; /**< ABORT */

                            /* Bits[29:29], Access Type=RW/V, default=0x00000000*/

                            /* --- */

    UINT32 resume : 1; /**< RESUME */

                            /* Bits[30:30], Access Type=RW/V, default=0x00000000*/

                            /* --- */

    UINT32 enable : 1; /**< ENABLE */

                            /* Bits[31:31], Access Type=RW/V, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} DEVICE_CONTROL_I3C0_STRUCT;


#define SCL_I3C_OD_TIMING_I3C0_REG    0x214

typedef union {
  struct {
    UINT32 i3c_od_lcnt : 8; /**< I3C_OD_LCNT */

                            /* Bits[7:0], Access Type=RW, default=0x000000FA*/

                            /* --- */

    UINT32 reserved_8_15 : 8; /**< RESERVED_8_15 */

                            /* Bits[15:8], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 i3c_od_hcnt : 8; /**< I3C_OD_HCNT */

                            /* Bits[23:16], Access Type=RW, default=0x000000FA*/

                            /* --- */

    UINT32 reserved_24_31 : 8; /**< RESERVED_24_31 */

                            /* Bits[31:24], Access Type=RO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} SCL_I3C_OD_TIMING_I3C0_STRUCT;


#define SCL_I3C_PP_TIMING_I3C0_REG    0x218

typedef union {
  struct {
    UINT32 i3c_pp_lcnt : 8; /**< I3C_PP_LCNT */

                            /* Bits[7:0], Access Type=RW, default=0x00000008*/

                            /* --- */

    UINT32 reserved_8_15 : 8; /**< RESERVED_8_15 */

                            /* Bits[15:8], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 i3c_pp_hcnt : 8; /**< I3C_PP_HCNT */

                            /* Bits[23:16], Access Type=RW, default=0x00000008*/

                            /* --- */

    UINT32 reserved_24_31 : 8; /**< RESERVED_24_31 */

                            /* Bits[31:24], Access Type=RO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} SCL_I3C_PP_TIMING_I3C0_STRUCT;

#define SCL_I2C_FM_TIMING_I3C0_REG    0x21C

typedef union {
  struct {
    UINT32 i2c_fm_lcnt : 16; /**< I2C_FM_LCNT */

                            /* Bits[15:0], Access Type=RW, default=0x000000FA*/

                            /* --- */

    UINT32 i2c_fm_hcnt : 8; /**< I2C_FM_HCNT */

                            /* Bits[23:16], Access Type=RW, default=0x000000FA*/

                            /* --- */

    UINT32 reserved_24_31 : 8; /**< RESERVED_24_31 */

                            /* Bits[31:24], Access Type=RO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} SCL_I2C_FM_TIMING_I3C0_STRUCT;

#endif _I3C0_REGS_H_
