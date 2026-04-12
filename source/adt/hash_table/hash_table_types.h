#ifndef HASH_TABLE_TYPES_H
#define HASH_TABLE_TYPES_H

#include "std_includes.h"
#include "hash_table_const.h"

typedef struct {
    int32_t value;
    uint32_t cnt; /*the number of such elements*/
    bool collision_flag;
} HashTableCell_t;

#define HASH_TABLE_COMMON_VARIABLES                    \
    char* name;                                        \
    uint8_t num;                                       \
    HashTableCell_t* Memory;                           \
    uint32_t size;                                     \
    bool valid;

typedef struct {
    HASH_TABLE_COMMON_VARIABLES
}HashTableConfig_t;

typedef struct {
    HASH_TABLE_COMMON_VARIABLES
    bool init;
}HashTableHandle_t;


#endif /* HASH_TABLE_TYPES_H */
