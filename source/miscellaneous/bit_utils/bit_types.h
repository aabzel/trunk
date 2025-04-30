#ifndef BIT_TYPES_H
#define BIT_TYPES_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifndef HAS_BIT_UTILS
#error "+HAS_BIT_UTILS"
#endif



#include "bit_const.h"

typedef union{
    uint8_t byte;
    struct {
        uint8_t low : 4;/*Bits: 0-3 */
        uint8_t high : 4;/*Bits: 4-7 */
    };
} ByteNimble_t;


typedef union{
    uint8_t byte;
    struct {
        int8_t sp0 : 2;/*Bits: 0-1 */
        int8_t sp1 : 2;/*Bits: 2-3 */
        int8_t sp2 : 2;/*Bits: 4-5 */
        int8_t sp3 : 2;/*Bits: 6-7 */
    };
} BitFieldInt2_t;

typedef union{
    uint8_t byte;
    struct {
        uint8_t sp0 : 2;/*Bits: 0-1 */
        uint8_t sp1 : 2;/*Bits: 2-3 */
        uint8_t sp2 : 2;/*Bits: 4-5 */
        uint8_t sp3 : 2;/*Bits: 6-7 */
    };
} BitFieldUint2_t;

typedef union{
    uint32_t address_phy;
    uint32_t address_byte;
    struct {
        uint32_t index1bit : 1;     /* Bits: 0 */
        uint32_t address_word : 31; /* Bits:  31:1 */
    };
    struct {
        uint32_t index2bit : 2;      /* Bits: 1:0 */
        uint32_t address_dword : 30; /* Bits: 31:2  */
    };
    struct {
        uint32_t index3bit : 3;      /* Bits: 2:0 */
        uint32_t address_qword : 29; /* Bits: 31:3  */
    };
} Address32bit_t;


typedef struct  {
    uint8_t bit0 : 1;
    uint8_t bit1 : 1;
    uint8_t bit2 : 1;
    uint8_t bit3 : 1;
    uint8_t bit4 : 1;
    uint8_t bit5 : 1;
    uint8_t bit6 : 1;
    uint8_t bit7 : 1;
} BitField8_t;

typedef struct  {
    uint8_t bit0 : 1;
    uint8_t bit1 : 1;
    uint8_t bit2 : 1;
    uint8_t bit3 : 1;
    uint8_t bit4 : 1;
    uint8_t bit5 : 1;
    uint8_t bit6 : 1;
    uint8_t bit7 : 1;
    uint8_t bit8 : 1;
    uint8_t bit9 : 1;
    uint8_t bit10 : 1;
    uint8_t bit11 : 1;
    uint8_t bit12 : 1;
    uint8_t bit13 : 1;
    uint8_t bit14 : 1;
    uint8_t bit15 : 1;
} BitField16_t;

typedef struct  {
    uint8_t bit0 : 1;
    uint8_t bit1 : 1;
    uint8_t bit2 : 1;
    uint8_t bit3 : 1;
    uint8_t bit4 : 1;
    uint8_t bit5 : 1;
    uint8_t bit6 : 1;
    uint8_t bit7 : 1;
    uint8_t bit8 : 1;
    uint8_t bit9 : 1;
    uint8_t bit10 : 1;
    uint8_t bit11 : 1;
    uint8_t bit12 : 1;
    uint8_t bit13 : 1;
    uint8_t bit14 : 1;
    uint8_t bit15 : 1;
    uint8_t bit16 : 1;
    uint8_t bit17 : 1;
    uint8_t bit18 : 1;
    uint8_t bit19 : 1;
    uint8_t bit20 : 1;
    uint8_t bit21 : 1;
    uint8_t bit22 : 1;
    uint8_t bit23 : 1;
} BitField24_t;

typedef union{
	uint32_t dword;
	struct{
		uint32_t bit0 : 1;
        uint32_t bit1 : 1;
        uint32_t bit2 : 1;
        uint32_t bit3 : 1;
        uint32_t bit4 : 1;
        uint32_t bit5 : 1;
        uint32_t bit6 : 1;
        uint32_t bit7 : 1;
        uint32_t bit8 : 1;
        uint32_t bit9 : 1;
        uint32_t bit10 : 1;
        uint32_t bit11 : 1;
        uint32_t bit12 : 1;
        uint32_t bit13 : 1;
        uint32_t bit14 : 1;
        uint32_t bit15 : 1;
        uint32_t bit16 : 1;
        uint32_t bit17 : 1;
        uint32_t bit18 : 1;
        uint32_t bit19 : 1;
        uint32_t bit20 : 1;
        uint32_t bit21 : 1;
        uint32_t bit22 : 1;
        uint32_t bit23 : 1;
        uint32_t bit24 : 1;
        uint32_t bit25 : 1;
        uint32_t bit26 : 1;
        uint32_t bit27 : 1;
        uint32_t bit28 : 1;
        uint32_t bit29 : 1;
        uint32_t bit30 : 1;
        uint32_t bit31 : 1;
	};
} BitField32_t;

typedef struct  {
    uint8_t bit0 : 1;
    uint8_t bit1 : 1;
    uint8_t bit2 : 1;
    uint8_t bit3 : 1;
    uint8_t bit4 : 1;
    uint8_t bit5 : 1;
    uint8_t bit6 : 1;
    uint8_t bit7 : 1;
    uint8_t bit8 : 1;
    uint8_t bit9 : 1;
    uint8_t bit10 : 1;
    uint8_t bit11 : 1;
    uint8_t bit12 : 1;
    uint8_t bit13 : 1;
    uint8_t bit14 : 1;
    uint8_t bit15 : 1;
    uint8_t bit16 : 1;
    uint8_t bit17 : 1;
    uint8_t bit18 : 1;
    uint8_t bit19 : 1;
    uint8_t bit20 : 1;
    uint8_t bit21 : 1;
    uint8_t bit22 : 1;
    uint8_t bit23 : 1;
    uint8_t bit24 : 1;
    uint8_t bit25 : 1;
    uint8_t bit26 : 1;
    uint8_t bit27 : 1;
    uint8_t bit28 : 1;
    uint8_t bit29 : 1;
    uint8_t bit30 : 1;
    uint8_t bit31 : 1;
    uint8_t bit32 : 1;
    uint8_t bit33 : 1;
    uint8_t bit34 : 1;
    uint8_t bit35 : 1;
    uint8_t bit36 : 1;
    uint8_t bit37 : 1;
    uint8_t bit38 : 1;
    uint8_t bit39 : 1;
    uint8_t bit40 : 1;
    uint8_t bit41 : 1;
    uint8_t bit42 : 1;
    uint8_t bit43 : 1;
    uint8_t bit44 : 1;
    uint8_t bit45 : 1;
    uint8_t bit46 : 1;
    uint8_t bit47 : 1;
    uint8_t bit48 : 1;
    uint8_t bit49 : 1;
    uint8_t bit50 : 1;
    uint8_t bit51 : 1;
    uint8_t bit52 : 1;
    uint8_t bit53 : 1;
    uint8_t bit54 : 1;
    uint8_t bit55 : 1;
    uint8_t bit56 : 1;
    uint8_t bit57 : 1;
    uint8_t bit58 : 1;
    uint8_t bit59 : 1;
    uint8_t bit60 : 1;
    uint8_t bit61 : 1;
    uint8_t bit62 : 1;
    uint8_t bit63 : 1;
} BitField64_t;


#ifdef __cplusplus
}
#endif

#endif /* BIT_TYPES_H */
