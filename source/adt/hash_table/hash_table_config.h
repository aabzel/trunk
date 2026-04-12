#ifndef HASH_TABLE_CONFIG_H
#define HASH_TABLE_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "hash_table_types.h"
#include "hash_table_dep.h"

extern const HashTableConfig_t HashTableConfig[];
extern HashTableHandle_t HashTableInstance[];

uint32_t hash_table_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* HASH_TABLE_CONFIG_H */
