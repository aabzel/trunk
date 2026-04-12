#ifndef STORAGE_TYPES_H
#define STORAGE_TYPES_H

#include "storage_const.h"
#include "std_includes.h"
#include "storage_file_ids.h"
#include "sys_constants.h"

typedef const char* (*StorageParserFunction_t)(const void * const data);

typedef struct {
    facility_t facility;
    StorageId_t id;
    uint16_t len;
    StorageType_t type;
    char* name;
    char* default_value;
    bool hide;
    StorageParserFunction_t parser;
    StorageUnits_t Units; /*Meter Foot Inch Yard mile*/
    StorageScale_t Scale; /*kilo milli exa*/
    StoragePhysicalQuantity_t physical_quantity; /*Length mass time current*/
} StorageItem_t;

typedef struct {
    StorageType_t type;
    StorageId_t id;
} StorageIdInfo_t;


typedef struct {
    StorageType_t type;
    uint32_t len;
} StorageTypeInfo_t;

/*order matter it is frame structure (8 byte)*/
typedef struct {
    uint32_t address; /*4byte     24 bit address*/
    uint16_t size;     /*2byte    0...256*/
    StorageAccess_t operation; /* 1byte   read write*/
    uint8_t asic_num; /*1byte    SPI Flash ASIC num default 0*/
    //uint8_t data[0];     /*just for pointer*/
} __attribute__((__packed__)) StorageFrameHeader_t;

#endif /* STORAGE_TYPES_H */
