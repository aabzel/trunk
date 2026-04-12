#ifndef HASH_TABLE_S8_CONFIG_H
#define HASH_TABLE_S8_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "hash_table_s8_types.h"
#include "hash_table_s8_dep.h"

extern const HashTableS8Config_t HashTableS8Config[];
extern HashTableS8Handle_t HashTableS8Instance[];

uint8_t hash_table_s8_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* HASH_TABLE_S8_CONFIG_H */
