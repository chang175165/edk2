

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


#endif _RACU_H_
