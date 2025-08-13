

#ifndef _I3C0_REGS_H_
#define _I3C0_REGS_H_

// Clock Period values (for SMBUS freq) are based on 100 MHz FXCLK
#define SMB_100K_CLK_PERIOD    1000  // Clock period to be programmed for 100 kHz
#define SMB_100K_CLK_OFFSET    35    // Clock offset to be programmed for 100 kHz
#define SMB_400K_CLK_PERIOD    250   // Clock period to be programmed for 400 kHz
#define SMB_400K_CLK_OFFSET    35    // Clock offset to be programmed for 400 kHz
#define SMB_700K_CLK_PERIOD    144   // Clock period to be programmed for 700 kHz
#define SMB_700K_CLK_OFFSET    30    // Clock offset to be programmed for 700 kHz
#define SMB_1M_CLK_PERIOD      100   // Clock period to be programmed for 1 MHz
#define SMB_1M_CLK_OFFSET      19    // Clock offset to be programmed for 1 MHz

#define SMB_100K_CLK_PERIOD_L  750   // Low count of Clock period to be programmed for 100 kHz
#define SMB_100K_CLK_PERIOD_H  250   // High count of Clock period to be programmed for 100 kHz
#define SMB_200K_CLK_PERIOD    500   // Clock period to be programmed for 200 kHz
#define SMB_4M_CLK_PERIOD      25    // Clock period to be programmed for 4 MHz
#define SMB_6M_CLK_PERIOD      16    // Clock period to be programmed for 6 MHz ~ 6.25
#define SMB_8M_CLK_PERIOD      12    // Clock period to be programmed for 8 MHz ~ 8.3
#define SMB_9M_CLK_PERIOD      11    // Clock period to be programmed for 9 MHz ~ 9.09
#define SMB_10M_CLK_PERIOD     10    // Clock period to be programmed for 10 MHz

// For Birchstream (BHS) platform:
// AP 3 DIMMs (PP) - Frequency = 9.09 MHz, Duty_Cycle = 45.45 % (5 hcnt - 6 lcnt),     SDA_Tx_HOLD = 0x3 (30 ns)
// AP 3 DIMMs (OD) - Frequency = 1 MHz,    Duty_Cycle = 40 %    (40 hcnt - 60 lcnt),   SDA_Tx_HOLD = 0x3 (30 ns)
// SP 8 DIMMs (PP) - Frequency = 8.33 MHz, Duty_Cycle = 41.67 % (5 hcnt - 7 lcnt),     SDA_Tx_HOLD = 0x3 (30 ns)
// SP 8 DIMMs (OD) - Frequency = 1 MHz,    Duty_Cycle = 40 %    (40 hcnt - 60 lcnt),   SDA_Tx_HOLD = 0x3 (30 ns)
//
#define I3C_DUTY_CYCLE_PUSH_PULL   45 // will round to 45.45% at 9MHz; 41.67 using 8MHz
#define I3C_DUTY_CYCLE_OPEN_DRAIN  40
#define I3C_SDA_TX_HOLD             3

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

/** DEVICE_CAPABILITIES_SB_I3C0 desc:
  * Register default value:        0x00000004
  * Register full path in IP: sb_i3c_top_regs/sb_i3c_0/sb_i3c_ctrl_sb_i3c_ctrl_prim/DEVICE_CAPABILITIES
  * Security PolicyGroup: SB_I3C_MMIO_REGS_GP
  * DEVICE_CAPABILITIES
  */

#define DEVICE_CAPABILITIES_SB_I3C0_REG  0x00C

typedef union {
  struct {
    UINT32 reserved_0_1 : 2; /**< RESERVED_0_1 */

                            /* Bits[1:0], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 combo_command : 1; /**< COMBO_COMMAND */

                            /* Bits[2:2], Access Type=RO, default=0x00000001*/

                            /* --- */

    UINT32 auto_command : 1; /**< AUTO_COMMAND */

                            /* Bits[3:3], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 sg_for_ring_ptrs : 1; /**< SG_FOR_RING_PTRS */

                            /* Bits[4:4], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 non_current_master_cap : 1; /**< NON_CURRENT_MASTER_CAP */

                            /* Bits[5:5], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 hdr_ddr_en : 1; /**< HDR_DDR_EN */

                            /* Bits[6:6], Access Type=RO, default=0x00000001*/

                            /* --- */

    UINT32 hdr_ts_en : 1; /**< HDR_TS_EN */

                            /* Bits[7:7], Access Type=RO, default=0x00000001*/

                            /* --- */

    UINT32 reserved_8_31 : 24; /**< RESERVED_8_31 */

                            /* Bits[31:8], Access Type=RO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} DEVICE_CAPABILITIES_I3C0_STRUCT;


#define INTR_STATUS_I3C0_REG          0x020

typedef union {
  struct {
    UINT32 tx_thld_stat : 1; /**< TX_THLD_STAT */

                            /* Bits[0:0], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 rx_thld_stat : 1; /**< RX_THLD_STAT */

                            /* Bits[1:1], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 ibi_status_thld_stat : 1; /**< IBI_STATUS_THLD_STAT */

                            /* Bits[2:2], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 cmd_queue_ready_stat : 1; /**< CMD_QUEUE_READY_STAT */

                            /* Bits[3:3], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 resp_ready_stat : 1; /**< RESP_READY_STAT */

                            /* Bits[4:4], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 transfer_abort_stat : 1; /**< TRANSFER_ABORT_STAT */

                            /* Bits[5:5], Access Type=RW/1C, default=0x00000000*/

                            /* --- */

    UINT32 reserved_6_8 : 3; /**< RESERVED_6_8 */

                            /* Bits[8:6], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 transfer_err_stat : 1; /**< TRANSFER_ERR_STAT */

                            /* Bits[9:9], Access Type=RW/1C, default=0x00000000*/

                            /* --- */

    UINT32 hc_internal_err_stat : 1; /**< HC_INTERNAL_ERR_STAT */

                            /* Bits[10:10], Access Type=RW/1C, default=0x00000000*/

                            /* --- */

    UINT32 reserved_11_13 : 3; /**< RESERVED_11_13 */

                            /* Bits[13:11], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 ppoll_cmd_miss_stat : 1; /**< PPOLL_CMD_MISS_STAT */

                            /* Bits[14:14], Access Type=RW/1C, default=0x00000000*/

                            /* --- */

    UINT32 bus_reset_done_stat : 1; /**< BUS_RESET_DONE_STAT */

                            /* Bits[15:15], Access Type=RW/1C, default=0x00000000*/

                            /* --- */

    UINT32 reserved_16_31 : 16; /**< RESERVED_16_31 */

                            /* Bits[31:16], Access Type=RO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} INTR_STATUS_I3C0_STRUCT;

#define COMMAND_QUEUE_PORT_I3C0_REG   0x0C0

typedef union {
  struct {
    UINT32 command : 32; /**< COMMAND */

                            /* Bits[31:0], Access Type=WO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} COMMAND_QUEUE_PORT_I3C0_STRUCT;

#define RESPONSE_QUEUE_PORT_I3C0_REG  0x0C4

typedef union {
  struct {
    UINT32 data_length : 16; /**< DATA_LENGTH */

                            /* Bits[15:0], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 reserved_16_23 : 8; /**< RESERVED_16_23 */

                            /* Bits[23:16], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 tid : 4; /**< TID */

                            /* Bits[27:24], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 err_status : 4; /**< ERR_STATUS */

                            /* Bits[31:28], Access Type=RO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} RESPONSE_QUEUE_PORT_I3C0_STRUCT;

#define DATA_PORT_I3C0_REG         0x0C8

typedef union {
  struct {
    UINT32 data_port : 32; /**< TX_DATA_PORT */

                            /* Bits[31:0], Access Type=WO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} DATA_PORT_I3C0_STRUCT;

#define DATA_PORT_SB_I3C0_WIDTH 32

#define DATA_PORT_SB_I3C0_DATA_PORT_LSB 0x0000
#define DATA_PORT_SB_I3C0_DATA_PORT_SIZE 0x0020

/** DATA_BUFFER_THLD_CTRL_SB_I3C0 desc:
  * Register default value:        0x01010404
  * Register full path in IP: sb_i3c_top_regs/sb_i3c_0/sb_i3c_ctrl_sb_i3c_ctrl_prim/DATA_BUFFER_THLD_CTRL
  * Security PolicyGroup: SB_I3C_MMIO_REGS_GP
  * DATA_BUFFER_THLD_CTRL
  */

#define DATA_BUFFER_THLD_CTRL_I3C0_REG 0x0d4

typedef union {
  struct {
    UINT32 tx_buf_thld : 3; /**< TX_BUF_THLD */

                            /* Bits[2:0], Access Type=RW, default=0x00000004*/

                            /* --- */

    UINT32 reserved_3_7 : 5; /**< RESERVED_3_7 */

                            /* Bits[7:3], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 rx_buf_thld : 3; /**< RX_BUF_THLD */

                            /* Bits[10:8], Access Type=RW, default=0x00000004*/

                            /* --- */

    UINT32 reserved_11_15 : 5; /**< RESERVED_11_15 */

                            /* Bits[15:11], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 tx_start_thld : 3; /**< TX_START_THLD */

                            /* Bits[18:16], Access Type=RW, default=0x00000001*/

                            /* --- */

    UINT32 reserved_19_23 : 5; /**< RESERVED_19_23 */

                            /* Bits[23:19], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 rx_start_thld : 3; /**< RX_START_THLD */

                            /* Bits[26:24], Access Type=RW, default=0x00000001*/

                            /* --- */

    UINT32 reserved_27_31 : 5; /**< RESERVED_27_31 */

                            /* Bits[31:27], Access Type=RO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} DATA_BUFFER_THLD_CTRL_I3C0_STRUCT;

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


#define COMMON_DEVICE_CTRL_I3C0_REG   0x018

typedef union {
  struct {
    UINT32 ibi_payload : 1; /**< IBI_PAYLOAD */

                            /* Bits[0:0], Access Type=RW, default=0x00000001*/

                            /* --- */

    UINT32 sir_reject : 1; /**< SIR_REJECT */

                            /* Bits[1:1], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 mr_reject : 1; /**< MR_REJECT */

                            /* Bits[2:2], Access Type=RW, default=0x00000001*/

                            /* --- */

    UINT32 reserved_3_28 : 26; /**< RESERVED_3_28 */

                            /* Bits[28:3], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 dev_nack_retry_cnt : 2; /**< DEV_NACK_RETRY_CNT */

                            /* Bits[30:29], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 reserved_31_31 : 1; /**< RESERVED_31_31 */

                            /* Bits[31:31], Access Type=RO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} COMMON_DEVICE_CTRL_I3C0_STRUCT;


/** QUEUE_THLD_CTRL_SB_I3C0 desc:
  * Register default value:        0x00200002
  * Register full path in IP: sb_i3c_top_regs/sb_i3c_0/sb_i3c_ctrl_sb_i3c_ctrl_prim/QUEUE_THLD_CTRL
  * Security PolicyGroup: SB_I3C_MMIO_REGS_GP
  * QUEUE_THLD_CTRL
  */

#define QUEUE_THLD_CTRL_I3C0_REG      0x0d0

typedef union {
  struct {
    UINT32 cmd_empty_buf_thld : 8; /**< CMD_EMPTY_BUF_THLD */

                            /* Bits[7:0], Access Type=RW, default=0x00000002*/

                            /* --- */

    UINT32 resp_buf_thld : 8; /**< RESP_BUF_THLD */

                            /* Bits[15:8], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 ibi_data_thld : 8; /**< IBI_DATA_THLD */

                            /* Bits[23:16], Access Type=RW, default=0x00000020*/

                            /* --- */

    UINT32 ibi_status_thld : 8; /**< IBI_STATUS_THLD */

                            /* Bits[31:24], Access Type=RW, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} QUEUE_THLD_CTRL_I3C0_STRUCT;


/** RESET_CTRL_SB_I3C0 desc:
  * Register default value:        0x00000000
  * Register full path in IP: sb_i3c_top_regs/sb_i3c_0/sb_i3c_ctrl_sb_i3c_ctrl_prim/RESET_CTRL
  * Security PolicyGroup: SB_I3C_MMIO_REGS_GP
  * RESET_CTRL
  */

#define RESET_CTRL_I3C0_REG           0x010

typedef union {
  struct {
    UINT32 soft_rst : 1; /**< SOFT_RST */

                            /* Bits[0:0], Access Type=RW/V, default=0x00000000*/

                            /* --- */

    UINT32 cmd_queue_rst : 1; /**< CMD_QUEUE_RST */

                            /* Bits[1:1], Access Type=RW/V, default=0x00000000*/

                            /* --- */

    UINT32 resp_queue_rst : 1; /**< RESP_QUEUE_RST */

                            /* Bits[2:2], Access Type=RW/V, default=0x00000000*/

                            /* --- */

    UINT32 tx_fifo_rst : 1; /**< TX_FIFO_RST */

                            /* Bits[3:3], Access Type=RW/V, default=0x00000000*/

                            /* --- */

    UINT32 rx_fifo_rst : 1; /**< RX_FIFO_RST */

                            /* Bits[4:4], Access Type=RW/V, default=0x00000000*/

                            /* --- */

    UINT32 ibi_queue_rst : 1; /**< IBI_QUEUE_RST */

                            /* Bits[5:5], Access Type=RW/V, default=0x00000000*/

                            /* --- */

    UINT32 reserved_6_28 : 23; /**< RESERVED_6_28 */

                            /* Bits[28:6], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 bus_reset_type : 2; /**< BUS_RESET_TYPE */

                            /* Bits[30:29], Access Type=RW/V, default=0x00000000*/

                            /* --- */

    UINT32 bus_reset : 1; /**< BUS_RESET */

                            /* Bits[31:31], Access Type=RW/V, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} RESET_CTRL_I3C0_STRUCT;


/** SCL_LOW_MST_EXT_TIMEOUT_SB_I3C0 desc:
  * Register default value:        0x003567E0
  * Register full path in IP: sb_i3c_top_regs/sb_i3c_0/sb_i3c_ctrl_sb_i3c_ctrl_prim/SCL_LOW_MST_EXT_TIMEOUT
  * Security PolicyGroup: SB_I3C_MMIO_REGS_GP
  * SCL_LOW_MST_EXT_TIMEOUT
  */

#define SCL_LOW_MST_EXT_TIMEOUT_I3C0_REG 0x23c

typedef union {
  struct {
    UINT32 scl_low_mst_timeout_count : 26; /**< SCL_LOW_MST_TIMEOUT_COUNT */

                            /* Bits[25:0], Access Type=RW, default=0x003567E0*/

                            /* --- */

    UINT32 reserved_26_31 : 6; /**< RESERVED_26_31 */

                            /* Bits[31:26], Access Type=RO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} SCL_LOW_MST_EXT_TIMEOUT_I3C0_STRUCT;


/** IBI_NOTIFY_CTRL_SB_I3C0 desc:
  * Register default value:        0x00000000
  * Register full path in IP: sb_i3c_top_regs/sb_i3c_0/sb_i3c_ctrl_sb_i3c_ctrl_prim/IBI_NOTIFY_CTRL
  * Security PolicyGroup: SB_I3C_MMIO_REGS_GP
  * IBI_NOTIFY_CTRL
  */

#define IBI_NOTIFY_CTRL_I3C0_REG      0x058

typedef union {
  struct {
    UINT32 notify_hj_rejected : 1; /**< NOTIFY_HJ_REJECTED */

                            /* Bits[0:0], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 notify_mr_rejected : 1; /**< NOTIFY_MR_REJECTED */

                            /* Bits[1:1], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 reserved_2_2 : 1; /**< RESERVED_2_2 */

                            /* Bits[2:2], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 notify_sir_rejected : 1; /**< NOTIFY_SIR_REJECTED */

                            /* Bits[3:3], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 reserved_4_31 : 28; /**< RESERVED_4_31 */

                            /* Bits[31:4], Access Type=RO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} IBI_NOTIFY_CTRL_I3C0_STRUCT;


/** SDA_HOLD_SWITCH_DLY_TIMING_SB_I3C0 desc:
  * Register default value:        0x00010000
  * Register full path in IP: sb_i3c_top_regs/sb_i3c_0/sb_i3c_ctrl_sb_i3c_ctrl_prim/SDA_HOLD_SWITCH_DLY_TIMING
  * Security PolicyGroup: SB_I3C_MMIO_REGS_GP
  * SDA_HOLD_SWITCH_DLY_TIMING
  */

#define SDA_HOLD_SWITCH_DLY_TIMING_I3C0_REG 0x230

typedef union {
  struct {
    UINT32 sda_od_pp_switch_dly : 3; /**< SDA_OD_PP_SWITCH_DLY */

                            /* Bits[2:0], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 reserved_3_7 : 5; /**< RESERVED_3_7 */

                            /* Bits[7:3], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 sda_pp_od_switch_dly : 3; /**< SDA_PP_OD_SWITCH_DLY */

                            /* Bits[10:8], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 reserved_11_15 : 5; /**< RESERVED_11_15 */

                            /* Bits[15:11], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 sda_tx_hold : 3; /**< SDA_TX_HOLD */

                            /* Bits[18:16], Access Type=RW, default=0x00000001*/

                            /* --- */

    UINT32 reserved_19_23 : 5; /**< RESERVED_19_23 */

                            /* Bits[23:19], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 sda_rx_hold : 3; /**< SDA_RX_HOLD */

                            /* Bits[26:24], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 reserved_27_31 : 5; /**< RESERVED_27_31 */

                            /* Bits[31:27], Access Type=RO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} SDA_HOLD_SWITCH_DLY_TIMING_I3C0_STRUCT;


/** INTR_STATUS_ENABLE_SB_I3C0 desc:
  * Register default value:        0x00000000
  * Register full path in IP: sb_i3c_top_regs/sb_i3c_0/sb_i3c_ctrl_sb_i3c_ctrl_prim/INTR_STATUS_ENABLE
  * Security PolicyGroup: SB_I3C_MMIO_REGS_GP
  * INTR_STATUS_ENABLE
  */

#define INTR_STATUS_ENABLE_I3C0_REG   0x024

typedef union {
  struct {
    UINT32 tx_thld_stat_en : 1; /**< TX_THLD_STAT_EN */

                            /* Bits[0:0], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 rx_thld_stat_en : 1; /**< RX_THLD_STAT_EN */

                            /* Bits[1:1], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 ibi_thld_stat_en : 1; /**< IBI_THLD_STAT_EN */

                            /* Bits[2:2], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 cmd_queue_ready_stat_en : 1; /**< CMD_QUEUE_READY_STAT_EN */

                            /* Bits[3:3], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 resp_ready_stat_intr_en : 1; /**< RESP_READY_STAT_INTR_EN */

                            /* Bits[4:4], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 transfer_abort_stat_en : 1; /**< TRANSFER_ABORT_STAT_EN */

                            /* Bits[5:5], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 reserved_6_8 : 3; /**< RESERVED_6_8 */

                            /* Bits[8:6], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 transfer_err_stat_en : 1; /**< TRANSFER_ERR_STAT_EN */

                            /* Bits[9:9], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 hc_internal_err_stat_en : 1; /**< HC_INTERNAL_ERR_STAT_EN */

                            /* Bits[10:10], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 reserved_11_13 : 3; /**< RESERVED_11_13 */

                            /* Bits[13:11], Access Type=RO, default=0x00000000*/

                            /* --- */

    UINT32 ppoll_cmd_miss_stat_en : 1; /**< PPOLL_CMD_MISS_STAT_EN */

                            /* Bits[14:14], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 bus_reset_done_stat_en : 1; /**< BUS_RESET_DONE_STAT_EN */

                            /* Bits[15:15], Access Type=RW, default=0x00000000*/

                            /* --- */

    UINT32 reserved_16_31 : 16; /**< RESERVED_16_31 */

                            /* Bits[31:16], Access Type=RO, default=0x00000000*/

                            /* --- */

  }     Bits;
  UINT32 Data;
} INTR_STATUS_ENABLE_I3C0_STRUCT;


#endif _I3C0_REGS_H_
