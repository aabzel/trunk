#ifndef STORAGE_TYPES_H
#define STORAGE_TYPES_H

#include <time.h>

#include "storage_const.h"
#include "std_includes.h"
#include "storage_file_ids.h"
#include "sys_constants.h"

typedef const char* (*StorageParserFunction_t)(const void * const data);


typedef union {
    int32_t s32;
    uint32_t u32;
    uint64_t u64;
    int64_t s64;
    uint16_t u16;
    int16_t s16;
    uint8_t u8;
    int8_t s8;
    bool logic;
    float real_float;
    double real_double;
    char temp[32];
    struct tm time_date ;
} StorageUnivervalType_t;

typedef struct {
    facility_t facility;
    StorageId_t id;
    uint16_t len;
    StorageType_t type;
    char* name;
    char* default_value;
    bool hide;
    StorageScale_t Scale;
    StorageAccess_t access;
    StorageParserFunction_t parser;
    StorageUnits_t Units; /*Meter Foot Inch Yard mile*/
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
