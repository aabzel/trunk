#ifndef HASH_TABLE_S8_TYPES_H
#define HASH_TABLE_S8_TYPES_H

#include "std_includes.h"
#include "hash_table_s8_const.h"

#define HASH_TABLE_S8_COMMON_VARIABLES                    \
    char* name;                                        \
    uint8_t num;                                       \
    bool valid;

typedef struct {
    HASH_TABLE_S8_COMMON_VARIABLES
}HashTableS8Config_t;

typedef struct {
    HASH_TABLE_S8_COMMON_VARIABLES
    bool init;
    uint32_t HashTable[257];
}HashTableS8Handle_t;


#endif /* HASH_TABLE_S8_TYPES_H */
