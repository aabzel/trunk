#ifndef STORAGE_TYPES_H
#define STORAGE_TYPES_H

#include "storage_const.h"

#include "std_includes.h"

/*order matter it is frame structure (8 byte)*/
typedef struct {
    uint32_t address; /*4byte     24 bit address*/
    uint16_t size;     /*2byte    0...256*/
    StorageAccess_t operation; /* 1byte   read write*/
    uint8_t asic_num; /*1byte    SPI Flash ASIC num default 0*/
    //uint8_t data[0];     /*just for pointer*/
} __attribute__((__packed__)) StorageFrameHeader_t;

#endif /* STORAGE_TYPES_H */
