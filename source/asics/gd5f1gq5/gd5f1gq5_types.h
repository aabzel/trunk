#ifndef GD5F1GQ5_TYPES_H
#define GD5F1GQ5_TYPES_H

#include "std_includes.h"
#include "gd5f1gq5_const.h"
#include "gpio_types.h"
#include "gd5f1gq5_reg_types.h"
#include "compiler_const.h"

/*    Figure 8-2. Read From Cache Sequence Diagram    */
typedef union {
    uint32_t dword;
    uint8_t buff[4];
    struct{
        uint32_t dummy8: 8;  /* bit:7-0     Dummy byte         */
        uint32_t addr: 12;   /*  bit:19-8    A11- A0           */
        uint32_t dummy4: 4;  /* bit:23-20   Dummy<3:0>         */
        uint32_t res1: 8;    /*                                */
    };
} Gd5f1gq5CacheAddress32_t;


/* Figure 8-2. Read From Cache Sequence Diagram  */
typedef union {
    uint32_t phy_address;
    uint8_t buff[4];
    struct{
        uint32_t column_address: 12;  /*  bit:11-0    A11- A0        */
        uint32_t page_in_block: 6;    /*  bit:7-0     Dummy byte         */
        uint32_t block_num: 10;       /*  bit:          */
        uint32_t dummy4: 4;           /* bit:23-20   Dummy<3:0>         */
    };
    struct{
        uint32_t column_address2: 12;  /*  bit:11-0    A11- A0        */
        uint32_t row_address: 16;    /*  bit:7-0      */
        uint32_t dummy4_2: 4;           /* bit:23-20   Dummy<3:0>         */
    };
} Gd5f1gq5PhyAddress_t;



typedef union {
    uint8_t u8[3];
    struct{
        uint32_t dummy8: 8;  /*   Dummy byte         */
        uint32_t addr: 12;  /*    A11- A0         */
        uint32_t dummy4: 4;  /*   Dummy<3:0>         */
    }_PACKED_;
} _PACKED_ Gd5f1gq5CacheAddress24_t;


typedef union {
    uint8_t buff[2];
    uint16_t word;
    struct {
        uint16_t column_address: 12; /* column address (CA)
        The 12-bit address is capable of addressing from 0 to 4095 bytes; however, only bytes 0
        through 2175 are valid. Bytes 2176 through 4095 of each page are “out of bounds,” do not exist in the device,
        and cannot be addressed. */
        uint16_t dummy: 4;           /* dummy */
    };
}Gd5f1gq5ProgramLoadAddress_t;


/*row_address- RA: Row Address. RA<5:0>selects a page inside a block, and RA<15:6>selects a block.*/
typedef union {
    uint8_t buff[2];
    uint16_t row_address;
    struct {
        uint16_t page: 6;   /*  RA<5:0>selects a page inside a block */
        uint16_t block: 10; /* RA<15:6>selects a block */
    };
}Gd5f1gq5RowAddress_t;



#define GD5F1GQ5_COMMON_VARIABLES                  \
    char* name;                                    \
    uint8_t num;                                   \
    uint8_t spi_num;                               \
    Pad_t chip_select;                             \
    bool valid;

typedef struct {
    GD5F1GQ5_COMMON_VARIABLES
}Gd5f1gq5Config_t;

typedef struct {
    GD5F1GQ5_COMMON_VARIABLES
    bool init;

    Gd5f1gq5RegProtection_t Protection;
    Gd5f1gq5RegFeatureB0_t FeatureB0;
    Gd5f1gq5RegStatusC0_t StatusC0;
    Gd5f1gq5RegStatusF0_t StatusF0;
    Gd5f1gq5RegDriverStrength_t DriverStrength;
    uint32_t error_cnt;
    uint32_t spin;
}Gd5f1gq5Handle_t;


#endif /* GD5F1GQ5_TYPES_H */
