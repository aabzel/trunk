#ifndef STORAGE_CONST_H
#define STORAGE_CONST_H

#include "storage_dep.h"

#define STORAGE_PAYLOAD_SIZE 256
#define STORAGE_HEADER_SIZE sizeof(StorageFrameHeader_t)
#define STORAGE_DATA_SIZE (STORAGE_HEADER_SIZE+STORAGE_PAYLOAD_SIZE)

typedef enum {
    TYPE_UINT8 = 1,
    TYPE_BOOL = 2,
    TYPE_INT8 = 3,
    TYPE_UINT16 = 4,
    TYPE_INT16 = 5,
    TYPE_UINT32 = 6,
    TYPE_UINT32_HEX = 7,
    TYPE_INT32 = 8,
    TYPE_UINT64 = 9,
    TYPE_INT64 = 10,
    TYPE_STRING = 11,
    TYPE_FLOAT = 12,
    TYPE_DOUBLE = 13,
    TYPE_STRUCT = 14,
    TYPE_TIME_DATE = 15,
    TYPE_OPERATION = 16,
    TYPE_ARRAY = 17,

    TYPE_UNDEF = 0,
} StorageType_t;

typedef enum {
    ACCESS_READ_ONLY = 1,
    ACCESS_WRITE_ONLY = 2,
    ACCESS_ERASE = 3,
    ACCESS_READ_WRITE = 4,
    ACCESS_ERASE_SECTOR = 5,

    ACCESS_UNDEF = 0,
} StorageAccess_t;

#endif /* STORAGE_CONST_H */
