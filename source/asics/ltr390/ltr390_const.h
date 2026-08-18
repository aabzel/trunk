#ifndef LTR390_CONST_H
#define LTR390_CONST_H

#include "ltr390_dep.h"
#include "time_mcal.h"

#define LTR390_DRIVER_VERSION 1
#define LTR390_POLL_PERIOD_US MSEC_2_USEC(10)
#define LTR390_I2C_ADDR 0x53
#define LTR390_PERIOD_US SEC_2_USEC(0.5)
#define LTR390_REV_CODE 0xb2
#define LTR390_REG_ADDR_LAST 0x26
#define UV_SENSITIVITY 2300 /*UV Sensitivity Counts /UVI, for Gane 18 Resol 20-bit*/

typedef enum {
    REG_ACCESS_READ = 1,
    REG_ACCESS_READ_WRITE = 3,

    REG_ACCESS_UNDEF = 0
} RegAccess_t;

typedef enum {
    LTR390_REG_ADDR_MAIN_CTRL = 0x00,   // Main control register
    LTR390_REG_ADDR_MEAS_RATE = 0x04,   // Resolution and data rate
    LTR390_REG_ADDR_GAIN = 0x05,        // ALS and UVS gain range
    LTR390_REG_ADDR_PART_ID = 0x06,     // Part id/revision register
    LTR390_REG_ADDR_MAIN_STATUS = 0x07, // Main status register
    LTR390_REG_ADDR_ALS_DATA = 0x0D,    // ALS data lowest byte, 3 byte
    LTR390_REG_ADDR_UVS_DATA = 0x10,    // UVS data lowest byte, 3 byte
    LTR390_REG_ADDR_INT_CFG = 0x19,     // Interrupt configuration
    LTR390_REG_ADDR_INT_PST = 0x1A,     // Interrupt persistance config
    LTR390_REG_ADDR_THRES_UP = 0x21,    // Upper threshold, low byte, 3 byte
    LTR390_REG_ADDR_THRES_LOW = 0x24,   // Lower threshold, low byte, 3 byte

    LTR390_REG_ADDR_UNDEF = 0xFF
} Ltr390Reg_t;

typedef enum {
    LTR390_SRC_ALS = 0,
    LTR390_SRC_UVS = 1,

    LTR390_SRC_UNDEF = 2,
} DataSource_t;

// page  16
typedef enum {
    LTR390_RESOLUTION_CODE_20_BIT = 0,
    LTR390_RESOLUTION_CODE_19_BIT = 1,
    LTR390_RESOLUTION_CODE_18_BIT = 2,
    LTR390_RESOLUTION_CODE_17_BIT = 3,
    LTR390_RESOLUTION_CODE_16_BIT = 4,
    LTR390_RESOLUTION_CODE_13_BIT = 5,
    LTR390_RESOLUTION_CODE_RES1_BIT = 6,
    LTR390_RESOLUTION_CODE_RES2_BIT = 7,

    LTR390_RESOLUTION_CODE_UNDEF = 0xff
} Ltr390ResolutionCode_t;

typedef enum {
    LTR390_RESOLUTION_VAL_20_BIT = 20,
    LTR390_RESOLUTION_VAL_19_BIT = 19,
    LTR390_RESOLUTION_VAL_18_BIT = 18,
    LTR390_RESOLUTION_VAL_17_BIT = 17,
    LTR390_RESOLUTION_VAL_16_BIT = 16,
    LTR390_RESOLUTION_VAL_13_BIT = 13,

    LTR390_RESOLUTION_VAL_UNDEF = 0
} ResolutionVal_t;

typedef enum {
    LTR390_RATE_25_MS = 0,
    LTR390_RATE_50_MS = 1,
    LTR390_RATE_100_MS = 2,
    LTR390_RATE_200_MS = 3,
    LTR390_RATE_500_MS = 4,
    LTR390_RATE_1000_MS = 5,
    LTR390_RATE_2000_MS = 6,
    LTR390_RATE_2000__MS = 7,

    LTR390_RATE_UDEF = 8
} Ltr390Rate_t;

typedef enum {
    LTR390_GAIN_CODE_1 = 0,
    LTR390_GAIN_CODE_3 = 1,
    LTR390_GAIN_CODE_6 = 2,
    LTR390_GAIN_CODE_9 = 3,
    LTR390_GAIN_CODE_18 = 4,

    LTR390_GAIN_CODE_UDEF = 8
} Ltr390GainCode_t;

typedef enum {
    LTR390_GAIN_VAL_1 = 1,
    LTR390_GAIN_VAL_3 = 3,
    LTR390_GAIN_VAL_6 = 6,
    LTR390_GAIN_VAL_9 = 9,
    LTR390_GAIN_VAL_18 = 18,

    LTR390_GAIN_VAL_UDEF = 0
} Ltr390GainVal_t;

/*page 21*/
typedef enum {
    LTR390_INT_SEL_RES1 = 0,
    LTR390_INT_SEL_ALS_CHANNEL = 1,
    LTR390_INT_SEL_RES2 = 2,
    LTR390_INT_SEL_UVS_CHANNEL = 3,

    LTR390_INT_SEL_UNDEF = 4,
} Ltr390LsInterruptSelect_t;

typedef enum {
    LTR390_INT_DISABLE = 0,
    LTR390_INT_ENABLE = 1,

    LTR390_INT_UNDEF = 2,
} Ltr390LsInterrupt_t;

typedef enum {
    LTR390_LS_STANDBY = 0,
    LTR390_LS_ACTIVE = 1,

    LTR390_ENABLE_UNDEF = 2,
} Ltr390Enable_t;

typedef enum {
    LTR390_NO_RESET = 0,
    LTR390_SW_RESET = 1,

    LTR390_SW_RESET_UNDEF = 2,
} Ltr390SwReset_t;

#endif /* LTR390_CONST_H */
