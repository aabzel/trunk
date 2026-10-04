#ifndef GD5F1GQ5_REG_TYPES_H
#define GD5F1GQ5_REG_TYPES_H

#include "std_includes.h"
#include "gd5f1gq5_const.h"

typedef union {
    uint8_t buff[256];

    // Parameter Page structure for GD5F1GQ5xExxG (1Gbit SPI NAND)
    // Based on datasheet pages 28-31
    struct {
        // Bytes 0-3: Parameter page signature "ONFI"
        uint32_t signature; // 0x4F, 0x4E, 0x46, 0x49 ('O','N','F','I')

        // Bytes 4-5: Revision number (0x0000 = reserved)
        uint16_t revision; // Typically 0x00, 0x00

        // Bytes 6-7: Features supported (reserved)
        uint16_t features_supported; // 0x00, 0x00

        // Bytes 8-9: Reserved
        uint16_t reserved_8_9;

        // Bytes 10-31: Reserved (all zeros)
        uint8_t reserved_10_31[22];

        // --- Manufacturer Information block (bytes 32-79) ---

        // Bytes 32-43: Device manufacturer (12 ASCII chars) "GIGADEVICE  "
        uint8_t manufacturer[12]; // "GIGADEVICE  "

        // Bytes 44-63: Device model (20 ASCII chars) "GD5F1GQ5U" or "GD5F1GQ5R"
        uint8_t device_model[20]; // Model name with spaces padding

        // Byte 64: JEDEC manufacturer ID
        uint8_t jedec_manufacturer_id; // 0xC8 for GigaDevice

        // Bytes 65-66: Date code (typically 0x00, 0x00)
        uint16_t date_code;

        // Bytes 67-79: Reserved
        uint8_t reserved_67_79[13];

        // --- Memory organization block (bytes 80-127) ---

        // Bytes 80-83: Number of data bytes per page (0x00000800 = 2048)
        uint32_t bytes_per_page; // 2048 decimal (0x00000800)

        // Bytes 84-85: Number of spare bytes per page (0x0080 = 128)
        uint16_t spare_bytes_per_page; // 128 decimal

        // Bytes 86-89: Number of data bytes per partial page (0x00000200 = 512)
        uint32_t data_bytes_per_partial_page; // 512 decimal

        // Bytes 90-91: Number of spare bytes per partial page (0x0020 = 32)
        uint16_t spare_bytes_per_partial_page; // 32 decimal

        // Bytes 92-95: Number of pages per block (0x00000040 = 64)
        uint32_t pages_per_block; // 64 decimal

        // Bytes 96-99: Number of blocks per logical unit (LUN) (0x00000400 = 1024)
        uint32_t blocks_per_lun; // 1024 decimal

        // Byte 100: Number of logical units (LUNs) (0x01 = 1)
        uint8_t num_luns;

        // Byte 101: Reserved
        uint8_t reserved_101;

        // Byte 102: Number of bits per cell (0x01 = SLC)
        uint8_t bits_per_cell;

        // Bytes 103-104: Bad blocks maximum (0x0014 = 20)
        uint16_t max_bad_blocks;

        // Bytes 105-106: Block endurance (0x0105 = 261? Actually 0x05,0x01? Careful)
        // Datasheet shows 0x01, 0x05 -> typical 100K P/E cycles
        uint16_t block_endurance;

        // Byte 107: Guaranteed valid blocks at beginning of target (0x01)
        uint8_t guaranteed_valid_blocks;

        // Bytes 108-109: Block endurance for guaranteed valid blocks (0x0000)
        uint16_t endurance_guaranteed_blocks;

        // Byte 110: Number of programs per page (0x04)
        uint8_t programs_per_page;

        // Byte 111: Partial programming attributes
        uint8_t partial_program_attrs;

        // Byte 112: Number of bits ECC correctability (0x00 = default 4 bits? Check)
        // Note: Datasheet says 4 bits/528byte, but field is 0x00 typically
        uint8_t ecc_correctability_bits;

        // Byte 113: Number of interleaved address bits
        uint8_t interleaved_addr_bits;

        // Byte 114: Interleaved operation attributes
        uint8_t interleaved_attrs;

        // Bytes 115-127: Reserved
        uint8_t reserved_115_127[13];

        // --- Electrical parameters block (bytes 128-163) ---

        // Byte 128: I/O capacitance (0x08 = 8pF typical)
        uint8_t io_capacitance;

        // Bytes 129-130: IO clock support (0x0000)
        uint16_t io_clock_support;

        // Bytes 131-132: Reserved
        uint16_t reserved_131_132;

        // Bytes 133-134: tPROG maximum page program time (us) (0x0258 = 600us)
        uint16_t tPROG_max_us;

        // Bytes 135-136: tBERS maximum block erase time (us) (0x2710 = 10000us = 10ms)
        uint16_t tBERS_max_us;

        // Bytes 137-138: tR maximum page read time (us) (0x003C = 60us)
        uint16_t tR_max_us;

        // Bytes 139-140: Reserved
        uint16_t reserved_139_140;

        // Bytes 141-163: Reserved
        uint8_t reserved_141_163[23];

        // --- Vendor block (bytes 164-255) ---

        // Bytes 164-165: Vendor specific Revision number
        uint16_t vendor_revision;

        // Bytes 166-253: Vendor specific data (88 bytes)
        uint8_t vendor_specific[88];

        // Bytes 254-255: Integrity CRC (16-bit)
        uint16_t crc16; // CRC value for bytes 0-255

    // --- Redundant parameter pages (bytes 256-511) ---
    // First redundant copy of bytes 0-255
    //uint8_t redundant_copy1[256];

    // Bytes 512-767: Second redundant copy
    //uint8_t redundant_copy2[256];

    // Note: Additional redundant pages may exist beyond 768
    // This structure may need extension for full redundant pages
    } __attribute__((packed));

} Gd5f1gq5ParameterPage_t;


typedef const char* (*Gd5f1gq5RegParserCallBack_t)(const void * const memory);


typedef struct {
    bool valid;
    char* reg_name;
    uint8_t reg_addr;
    Gd5f1gq5RegParserCallBack_t regParserCallBack;
}Gd5f1gq5RegInfo_t;

/*
 Protection (  0xA0)
 Table 12-1. Features Settings */
typedef union {
    uint8_t byte;
    struct {
        uint8_t RES1 : 1;  // bit 0
        uint8_t CMP  : 1;  // bit 1
        uint8_t INV  : 1;  // bit 2
        uint8_t BP  : 3;   // bit 5-3 (see Table 12-7. Block Lock Register Block Protect Bits)
        uint8_t RES2 : 1;  // bit 6
        uint8_t BRWD : 1;  // bit 7 Block register write disable
    } ;
}Gd5f1gq5RegProtection_t;


/**
 * @brief Feature Register (Feature Address B0h)
 * Table 12-1. Features Settings
 * Controls OTP, ECC, Quad Enable, and Power Lock Down Protection.
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t QE          : 1;    /* bit 0   - Quad Enable (QE) */
        uint8_t RES1        : 2;    /* bit 2-1 - Reserved (must be 0) */
        uint8_t BPL         : 1;    /* bit 3   - Block Protection Lock (BPL) */
        uint8_t ECC_EN      : 1;    /* bit 4   - ECC Enable (ECC_EN) */
        uint8_t RES2        : 1;    /* bit 5   - Reserved (must be 0) */
        uint8_t OTP_EN      : 1;    /* bit 6   - OTP Enable (OTP_EN) */
        uint8_t OTP_PRT     : 1;    /* bit 7   - OTP Protect (OTP_PRT) - Non-volatile */
    } ;
} Gd5f1gq5RegFeatureB0_t;


/**
 * @brief Status Register (Feature Address C0h)
 *Table 12-1. Features Settings
 * Read-only register providing operation status and ECC results.
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t OIP         : 1;    /* bit 0 - Operation In Progress (OIP) */
        uint8_t WEL         : 1;    /* bit 1 - Write Enable Latch (WEL) */
        uint8_t E_FAIL      : 1;    /* bit 2 - Erase Fail (E_FAIL) */
        uint8_t P_FAIL      : 1;    /* bit 3 - Program Fail (P_FAIL) */
        uint8_t ECCS        : 2;    /* bit 5-4 - ECC Status bits  (ECCS0 ECCS1) */
        uint8_t RES1        : 2;    /* bit 7-6 - Reserved */
    } ;
} Gd5f1gq5RegStatusC0_t;

/*
  Alternate Status Register (Feature Address F0h)
  Table 12-1. Features Settings
  Extended status including block protection status.
 */
typedef union {
    uint8_t byte;              /* Raw register value */
    struct {
        uint8_t RES1   : 3;    /* bits 2-0 - Reserved */
        uint8_t BPS    : 1;    /* bit 3 - Block Protection Status (BPS) */
        uint8_t ECCSE   : 2;    /* bit 5-4 - ECC Status bits (ECCS0 ECCS1) */
        uint8_t RES2   : 2;    /* bits 7-8 - Reserved */
    } ;
} Gd5f1gq5RegStatusF0_t;

/*
  @brief Driver Strength Register (Feature Address D0h)
  Controls output driver strength for I/O pins.
  Table 12-1. Features Settings
 */
typedef union {
    uint8_t byte;                    /* Raw register value */
    struct {
        uint8_t RES1        : 5;    /* bits 4-0 - Reserved */
        uint8_t DS_IO       : 2;    /* bit 6-5 - Driver Strength bit 0 (DS_IO[0]) */
        uint8_t RES2        : 1;    /* bits 7 - Reserved  */
    } ;
} Gd5f1gq5RegDriverStrength_t;

typedef union {
    uint8_t buff[2];
    uint16_t word;
    struct {
        uint8_t manufacturer_id; /* first in SPI*/
        uint8_t device_id;       /* second in SPI*/
    };
}Gd5f1gq5ID_t;






#endif /* GD5F1GQ5_REG_TYPES_H */
