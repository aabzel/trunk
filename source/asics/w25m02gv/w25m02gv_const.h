#ifndef W25M02GV_CONST_H
#define W25M02GV_CONST_H

#include "time_mcal.h"
#include "w25m02gv_dep.h"

#define W25M02GV_REG_CNT 3
//see 8.1.1 Manufacturer and Device Identification
#define JEDEC_ID_MFR_ID_WINBOND ((uint8_t)0xEF)
#define JEDEC_ID_DEVICE_ID_W25M02GV 0x21AB
#define REG_SET_TRY_CNT 1
#define W25M02GV_VERIFY_DURATION_MS 1000
#define W25M02GV_VERIFY_AMP 1000
#define W25M02GV_PERIOD_US SEC_2_USEC(1)

// see 8.1.2 Instruction Set Table 1 (Continuous Read, BUF = 0, xxIT Default Power Up Mode)
typedef enum {
    W25_CMD_DEVICE_RESET = 0xFF, // Device RESET
    W25_CMD_SOFTWARE_DIE_SELECT = 0xC2, // Software Die Select
    W25_CMD_JEDEC_ID = 0x9F, // JEDEC ID
    W25_CMD_READ_STATUS_REGISTER = 0x0F, // Read Status Register
    W25_CMD_READ_STATUS_REGISTER_EXTRA = 0x05, // Read Status Register
    W25_CMD_WRITE_STATUS_REGISTER = 0x1F, // Write Status Register
    W25_CMD_WRITE_ENABLE = 0x06, // Write Enable
    W25_CMD_WRITE_DISABLE = 0x04, // Write Disable
    W25_CMD_BB_MANAGEMENT = 0xA1, // BB Management (Swap Blocks)
    W25_CMD_READ_BBM_LUT = 0xA5, // Read BBM LUT
    W25_CMD_LAST_ECC_FAILURE = 0xA9, // Last ECC failure Page Address
    W25_CMD_BLOCK_ERASE = 0xD8, //  Block Erase
    W25_CMD_PROGRAM_DATA_LOAD = 0x02, //  Program Data Load (Reset Buffer)
    W25_CMD_RANDOM_PROGRAM_DATA_LOAD = 0x84, //  Random Program Data Load
    W25_CMD_QUAD_PROGRAM_DATA_LOAD_RESET_BUFFER = 0x32, //  Quad Program Data Load (Reset Buffer)
    W25_CMD_RANDOM_QUAD_PROGRAM_DATA_LOAD = 0x34, //  Random Quad Program Data Load
    W25_CMD_PROGRAM_EXECUTE = 0x10, //  Program Execute
    W25_CMD_PAGE_DATA_READ = 0x13, //  Page Data Read
    W25_CMD_READ = 0x03, //  Read
    W25_CMD_FAST_READ = 0x0B, //  Fast Read
    W25_CMD_FAST_READ_WITH_4_BYTE_ADDRESS = 0x0C, //  Fast Read with 4-Byte Address
    W25_CMD_FAST_READ_DUAL_OUTPUT = 0x3B, //  Fast Read Dual Output
    W25_CMD_FAST_READ_DUAL_OUTPUT_WITH_4_BYTE_ADDRESS = 0x3C, //  Fast Read Dual Output with 4-Byte Address
    W25_CMD_FAST_READ_QUAD_OUTPUT = 0x6B, //  Fast Read Quad Output
    W25_CMD_FAST_READ_QUAD_OUTPUT_WITH_4_BYTE_ADDRESS = 0x6C, //  Fast Read Quad Output with 4-Byte Address
    W25_CMD_FAST_READ_DUAL_I_O = 0xBB, //  Fast Read Dual I/O
    W25_CMD_FAST_READ_DUAL_I_O_WITH_4_BYTE_ADDRESS = 0xBC, //  Fast Read Dual I/O with 4-Byte Address
    W25_CMD_FAST_READ_QUAD_I_O = 0xEB, //  Fast Read Quad I/O
    W25_CMD_FAST_READ_QUAD_I_O_WITH_4_BYTE_ADDRESS = 0xEC, //  Fast Read Quad I/O with 4-Byte Address

    W25_CMD_UNDEF = 0,
} w25m02gvCommands_t;

// Status Register Addresses:
typedef enum {
    W25M02GV_REG_PROTECTION = 0xA0,    // Status Register 1 /Addr 0b1010xxxx
    W25M02GV_REG_CONFIGURATION = 0xB0, // Status Register 2 /Addr 0b1011xxxx
    W25M02GV_REG_STATUS = 0xC0,        // Status Register 3 /Addr 0b1100xxxx

    W25M02GV_REG_UNDEF = 0x00,
} W25m02gvRegAddr_t;

// ECC Status
typedef enum {
    // Entire data output is successful, without any ECC correction
    W25M02GV_ECC_STATUS_SUCCESSFUL = 0,
    /*Entire data output is successful, with 1~4 bit/page ECC corrections in either a
     single page or multiple pages.*/
    W25M02GV_ECC_STATUS_1_4_BIT_PER_PAGE = 1,
    /*Entire data output contains more than 4 bits errors only in a single page
      which cannot be repaired by ECC.
      In the Continuous Read Mode, an additional command can be used to read out
      the Page Address (PA) which had the errors.*/
    W25M02GV_ECC_STATUS_MORE_4_BIT_PER_PAGE = 2,
    /*Entire data output contains more than 4 bits errors/page in multiple pages.
      In the Continuous Read Mode, the additional command can only provide the
      last Page Address (PA) that had failures, the user cannot obtain the PAs for
      other failure pages. Data is not suitable to use.*/
    W25M02GV_ECC_STATUS_MORE_4_BIT_PER_PAGES = 3,

    W25M02GV_ECC_STATUS_UNDEF = 4,
} W25m02gvEccStatus_t;



#endif /* W25M02GV_CONST_H */
