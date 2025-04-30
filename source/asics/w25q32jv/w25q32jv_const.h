#ifndef W25Q32JV_CONST_H
#define W25Q32JV_CONST_H

#define W25Q32JV_REG_CNT 1

#define REG_SET_TRY_CNT 3

#include "w25q32jv_dep.h"

#define W25Q32JV_FLASH_SIZE (4*1024*1024)
#define W25Q32JV_PAGE_SIZE 256U

#define W25Q32JV_BLOCK_SIZE (64*1024)   /* 128 blocks of 64KBytes */
#define W25Q32JV_SUBBLOCK_SIZE (32*1024)  /* 256 blocks of 32KBytes */
#define W25Q32JV_SECTOR_SIZE (4*1024)   /* 2048 sectors of 4kBytes */

#define W25_WR_TIMEOUT_MS 1000
#define W25Q32JV_PROGRAM_BUSY_TIMEOUT 100000

#define W25Q32JV_PERIOD_US 1000000

#define MANUFACTURER_ID 0xEF

typedef enum  {
    W25Q32JV_STATUS_REG_1 = 1, /*Status Register-1  05h */
    W25Q32JV_STATUS_REG_2 = 2, /*Status Register-2  35h */
    W25Q32JV_STATUS_REG_3 = 3, /*Status Register-3  15h */
    W25Q32JV_STATUS_REG_UNDEF = 0,
} W25q32jvRegisterIndex_t;


//Figure 4a. Status Register-1
typedef enum {
	W25Q32JV_STATUS_REGISTER_SPARE = 0,
	W25Q32JV_STATUS_REGISTER_BUSY  = 1,
	W25Q32JV_STATUS_REGISTER_UNDER = 2
} W25q32jvSreg1Busy_t;



typedef enum {
    W25_STAUS_2_QUAD_DISABLE= 0,
    W25_STAUS_2_QUAD_ENABLE = 1,

    W25_STAUS_2_QUAD_UNDEF = 2,
} W25Status2Quad_t;



typedef enum {
    W25_BLOCK_4K = 4,
    W25_BLOCK_32K = 32,
    W25_BLOCK_64K = 64,

    W25_BLOCK_UNDEF = 0,
} W25BlockSize_t;


typedef enum{
    W25Q32JV_WRITE_ENABLE = 0x06, /* Write Enable */
    W25Q32JV_VOLATILE_SR_WRITE_ENABLE = 0x50,/* Volatile SR Write Enable */
    W25Q32JV_WRITE_DISABLE = 0x04,/* Write Disable */
    W25Q32JV_RELEASE_POWERDOWN_ID = 0xAB,/* Release Power-down / ID */
    W25Q32JV_MANUFACTURER_DEVICE_ID = 0x90,/* Manufacturer/Device ID */
    W25Q32JV_JEDEC_ID = 0x9F,/* JEDEC ID */
    W25Q32JV_READ_UNIQUE_ID = 0x4B,/* Read Unique ID */
    W25Q32JV_READ_DATA = 0x03,/* Read Data */
    W25Q32JV_READ_SREG1 = 0x05,/* Read Status Register-1 */
    W25Q32JV_READ_SREG2 = 0x35,/* Read Status Register-2 */
    W25Q32JV_READ_STATUS_REG_3 = 0x15,/* Read Status Register-3 */
    W25Q32JV_READ_SFDP_REGISTERS = 0x5A,/* Read SFDP Register */
    W25Q32JV_READ_SECURITY_REGISTERS = 0x48,/* Read Security Register */
    W25Q32JV_READ_BLOCK_LOCK = 0x3D,/* Read Block Lock */
    W25Q32JV_FAST_READ = 0x0B,/* Fast Read */
    W25Q32JV_PAGE_PROGRAM = 0x02,/* Page Program */
    W25Q32JV_SECTOR_ERASE_4K = 0x20,/* Sector Erase (4KB) */
    W25Q32JV_BLOCK_ERASE_32K = 0x52,/* Block Erase (32KB) */
    W25Q32JV_BLOCK_ERASE_64K = 0xD8,/* Block Erase (64KB) */
    W25Q32JV_CHIP_ERASE = 0x60,/* Chip Erase */
    W25Q32JV_CHIP_ERASE_2 = 0xC7,/* Chip Erase */
    W25Q32JV_WRITE_SREG = 0x01,/* Write Status Register-1 */
    W25Q32JV_WRITE_SREG2 = 0x31,/* Write Status Register-2 */
    W25Q32JV_WRITE_STATUS_REG_3 = 0x11,/*Write Status Register-3 */
    W25Q32JV_ERASE_SECURITY_REGISTERS = 0x44,/* Erase Security Register */
    W25Q32JV_PROGRAM_SECURITY_REGISTERS = 0x42,/* Program Security Register */
    W25Q32JV_GLOBAL_BLOCK_LOCK = 0x7E,/* Global Block Lock */
    W25Q32JV_GLOBAL_BLOCK_UNLOCK = 0x98,/* Global Block Unlock */
    W25Q32JV_INDIVIDUAL_BLOCK_LOCK = 0x36,/* Individual Block Lock */
    W25Q32JV_INDIVIDUAL_BLOCK_UNLOCK = 0x39,/* Individual Block Unlock*/
    W25Q32JV_ERASE_PROGRAM_SUSPEND = 0x75,/* Erase / Program Suspend */
    W25Q32JV_ERASE_PROGRAM_RESUME = 0x7A,/* Erase / Program Resume */
    W25Q32JV_POWER_DOWN = 0xB9,/* Power-down */
    W25Q32JV_ENABLE_RESET = 0x66,/* Enable Reset */
    W25Q32JV_FAST_READ_DUAL_OUTPUT = 0x3B,/* Fast Read Dual Output */
    W25Q32JV_FAST_READ_DUAL_IO = 0xBB,/* Fast Read Dual I/O */
    W25Q32JV_MFTR_DEVICE_ID_DUAL_IO = 0x92,/* Mftr./Device ID Dual I/O */
    W25Q32JV_RESET = 0x99,/* Reset Device */
    W25Q32JV_MANUFACTURER_DEVICE_ID_BY_QUAD_IO = 0x94,/* Mftr./Device ID Quad I/O */
    W25Q32JV_QUAD_PAGE_PROGRAM = 0x32,/* Quad Input Page Program */
    W25Q32JV_FAST_READ_QUAD_OUTPUT = 0x6B,/* Fast Read Quad Output */
    W25Q32JV_SET_BURST_WITH_WRAP = 0x77,/* Set Burst with Wrap */
    W25Q32JV_FAST_READ_QUAD_IO = 0xEB,/* Fast Read Quad I/O */

    W25Q32JV_OPCODE_UNDEF= 0x07,/*  */
} W25q32jvOpCodes_t;



#endif /* W25Q32JV_CONST_H */
