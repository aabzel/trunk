#ifndef SI4703_SPI_TYPES_H
#define SI4703_SPI_TYPES_H

#include "std_includes.h"

typedef union {
    uint32_t dword;
    uint16_t word[2];
    uint8_t buff[4];
    struct{
        uint32_t res:7;
        uint32_t data_word:16;
        uint32_t address_bit0:1;
        uint32_t address_bit1:1;
        uint32_t address_bit2:1;
        uint32_t address_bit3:1;
        uint32_t address_bit4:1;
        uint32_t write_bit:1;
        uint32_t address_bit5:1;
        uint32_t address_bit6:1;
        uint32_t address_bit7:1;
    } __attribute__((__packed__));
}  __attribute__((__packed__)) Si4703SpiFrameWrite_t;

typedef union {
    uint16_t word;
    uint8_t byte[2];
    struct {
        uint8_t res:7; /* Bit:6-0  */
        uint8_t address0:1; /* Bit:7  */
        uint8_t address1:1; /* Bit:8  */
        uint8_t address2:1; /* Bit:9  */
        uint8_t address3:1; /* Bit:10  */
        uint8_t address4:1; /* Bit:11  */
        uint8_t RW:1;       /* bit:12  */
        uint8_t address5:1; /* Bit:13  */
        uint8_t address6:1; /* Bit:14  */
        uint8_t address7:1; /* Bit:15  */
    } ;
}   Si4703SpiAddressRead_t;

#endif /* SI4703_SPI_TYPES_H */
