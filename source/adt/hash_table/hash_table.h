#ifndef HASH_TABLE_MCAL_H
#define HASH_TABLE_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "hash_table_config.h"
#include "hash_table_types.h"
#ifdef HAS_HASH_TABLE_DIAG
#include "hash_table_diag.h"
#endif

/* API */
const HashTableConfig_t* HashTableGetConfig(uint8_t num);
HashTableHandle_t* HashTableGetNode(uint8_t num);

bool HashTableIsValidConfig(const HashTableConfig_t* const Config);

bool hash_table_mcal_init(void);
bool hash_table_init_one(uint8_t num);
bool hash_table_init_one_ll(const HashTableConfig_t* const Config,HashTableHandle_t* const Node);

/*setters*/
bool hash_table_push(uint8_t num, const int32_t value);
bool hash_table_push_ll(HashTableHandle_t* Node, const int32_t value);
bool hash_table_pull(uint8_t num, const int32_t value);
bool hash_table_pull_ll(HashTableHandle_t* Node, const int32_t value);

/*getters*/
bool hash_table_peek_ll(HashTableHandle_t* Node, const int32_t value);
bool hash_table_peek(uint8_t num, const int32_t value);

#ifdef __cplusplus
}
#endif

#endif /* HASH_TABLE_MCAL_H */
