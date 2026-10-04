#ifndef GD5F1GQ5_CONST_H
#define GD5F1GQ5_CONST_H

#include "time_mcal.h"
#include "gd5f1gq5_dep.h"

#define GD5F1GQ5_VERSION 4
#define GD5F1GQ5_PAGE_SIZE (2048UL)
#define GD5F1GQ5_PAGES_PER_BLOCK (64UL)
#define GD5F1GQ5_BLOCK_COUNT (1024UL)

#define GD5F1GQ5_PAGE_COUNT (GD5F1GQ5_BLOCK_COUNT*GD5F1GQ5_PAGES_PER_BLOCK)
#define GD5F1GQ5_BLOCK_SIZE  (GD5F1GQ5_PAGES_PER_BLOCK*GD5F1GQ5_PAGE_SIZE)
#define GD5F1GQ5_TOTAL_SIZE (GD5F1GQ5_BLOCK_COUNT*GD5F1GQ5_BLOCK_SIZE)

#define GD5F1GQ5_LAST_BLOCK (GD5F1GQ5_BLOCK_COUNT-1)
#define GD5F1GQ5_LAST_PAGE (GD5F1GQ5_PAGE_COUNT-2)
#define GD5F1GQ5_FIRST_PAGE_OF_LAST_BLOCK (GD5F1GQ5_PAGES_PER_BLOCK*(GD5F1GQ5_BLOCK_COUNT-1))

#define GD5F1GQ5_PERIOD_US MSEC_2_USEC(5000)

/* Table 8-1. READ ID Table */
#define GD5F1GQ5UEXXG_DEVICE_ID 0x51
#define GD5F1GQ5REXXG_DEVICE_ID 0x41
#define GD5F1GQ5_MANUFACTURER_ID 0xc8

/* Table 12-1. Features Settings */
typedef enum {
    GD5F1GQ5_REG_PROTECTION_A0H = 0xA0, /* BRWD   BP  INV CMP  */
    GD5F1GQ5_REG_FEATURE_B0H = 0xB0,    /* OTP_PRT OTP_EN   ECC_EN BPL     QE*/
    GD5F1GQ5_REG_STATUS_C0H = 0xC0,     /* ECCS P_FAIL E_FAIL WEL OIP*/
    GD5F1GQ5_REG_FEATURE_D0H = 0xD0,    /* DS_IO          */
    GD5F1GQ5_REG_STATUS_F0H = 0xF0,     /* ECCSE BPS      */
} Gd5f1gq5Regs_t;

/* Table 12-2. Status Register Bit Descriptions */
typedef enum {
    /*When the bit is 0, the interface is in the ready state. */
    GD5F1GQ5_STATUS_OIP_READY = 0,

    /* This bit is set (OIP = 1 ) when a PROGRAM EXECUTE, PAGE READ, BLOCK ERASE, or RESET command is
       executing, indicating the device is busy.  */
    GD5F1GQ5_STATUS_OIP_PROGRAM_EXECUTE = 1,
    GD5F1GQ5_STATUS_OIP_UNDEF = 2,
} Gd5f1gq5StatusOip_t;

/* Based on datasheet Table 6. Commands Set (pages 14-15)
   GD5F1GQ5UExxG series (3.3V version)  */
typedef enum {
    /* --- Write Operations (Section 7) --- */
    GD5F_CMD_WRITE_ENABLE               = 0x06, /* WREN - Set Write Enable Latch (WEL) bit */
    GD5F_CMD_WRITE_DISABLE              = 0x04, /* WRDI - Reset Write Enable Latch (WEL) bit */

    /* --- Feature Operations (Section 12.1) --- */
    GD5F_CMD_GET_FEATURES               = 0x0F, /* Get Features - Read device status/configuration */
    GD5F_CMD_SET_FEATURES               = 0x1F, /* Set Features - Modify device behavior */

    /* --- Read Operations (Section 8) --- */
    GD5F_CMD_PAGE_READ_TO_CACHE         = 0x13, /* Page Read to Cache - Transfer page from array to cache */
    GD5F_CMD_READ_FROM_CACHE            = 0x03, /* Read from Cache - Standard SPI read (low speed) */
    GD5F_CMD_READ_FROM_CACHE_ALT        = 0x0B, /* Read from Cache Fast - Fast read with dummy byte */
    GD5F_CMD_READ_FROM_CACHE_X2         = 0x3B, /* Read from Cache x2 - Dual output mode */
    GD5F_CMD_READ_FROM_CACHE_X4         = 0x6B, /* Read from Cache x4 - Quad output mode (requires QE=1) */
    GD5F_CMD_READ_FROM_CACHE_DUAL_IO    = 0xBB, /* Read from Cache Dual IO - Dual I/O mode */
    GD5F_CMD_READ_FROM_CACHE_QUAD_IO    = 0xEB, /* Read from Cache Quad IO - Quad I/O mode (requires QE=1) */
    GD5F_CMD_READ_FROM_CACHE_QUAD_DTR   = 0xEE, /* Read from Cache Quad I/O DTR - Double Transfer Rate mode */

    /* --- Identification Commands (Section 8.9, 8.10, 8.11) --- */
    GD5F_CMD_READ_ID                    = 0x9F, /* Read ID - Get Manufacturer ID (0xC8) and Device ID */
    //GD5F_CMD_READ_PARAMETER_PAGE        = 0x13, /* Read Parameter Page - Requires OTP_EN and address 0x000004 */
    //GD5F_CMD_READ_UID                   = 0x13, /* Read UID - Requires OTP_EN and address 0x000006 */

    /* --- Program Operations (Section 9) --- */
    GD5F_CMD_PROGRAM_LOAD_X4            = 0x32, /* Program Load x4 - Quad input mode (requires QE=1) */
    GD5F_CMD_PROGRAM_EXECUTE            = 0x10, /* Program Execute - Transfer cache to main array (needs WREN) */
    GD5F_CMD_PROGRAM_LOAD               = 0x02, /* Program Load - Load data to cache register (standard SPI) */

    /* --- Program Random Data (Internal Data Move, Section 9.6, 9.7) --- */
    GD5F_CMD_PROGRAM_LOAD_RANDOM        = 0x84, /* Program Load Random Data - Update data during internal move */
    GD5F_CMD_PROGRAM_LOAD_RANDOM_X4     = 0xC4, /* Program Load Random Data x4 - Quad input (C4H version) */
    GD5F_CMD_PROGRAM_LOAD_RANDOM_X4_ALT = 0x34, /* Program Load Random Data x4 - Quad input (34H version) */

    /* --- Erase Operations (Section 10) --- */
    GD5F_CMD_BLOCK_ERASE                = 0xD8, /* Block Erase - Erase 128KB block (needs WREN) */

    /* --- Reset Operations (Section 11) --- */
    GD5F_CMD_SOFT_RESET                 = 0xFF, /* Soft Reset - Stops all operations, resets status bits */
    GD5F_CMD_ENABLE_POWER_ON_RESET      = 0x66, /* Enable Power on Reset - Must precede GD5F_CMD_POWER_ON_RESET */
    GD5F_CMD_POWER_ON_RESET             = 0x99, /* Power on Reset - Returns to power-on state (after 0x66) */
    GD5F_CMD_UNDEF                      = 0x00, /* */

} Gd5f1gq5Command_t;

#endif /* GD5F1GQ5_CONST_H */
