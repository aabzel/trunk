#ifndef HASH_TABLE_S8_MCAL_H
#define HASH_TABLE_S8_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "hash_table_s8_config.h"
#include "hash_table_s8_types.h"
#ifdef HAS_HASH_TABLE_S8_DIAG
#include "hash_table_s8_diag.h"
#endif

/* API */
const HashTableS8Config_t* HashTableS8GetConfig(uint8_t num);
HashTableS8Handle_t* HashTableS8GetNode(uint8_t num);

bool HashTableS8IsValidConfig(const HashTableS8Config_t* const Config);

bool hash_table_s8_mcal_init(void);
bool hash_table_s8_init_one(uint8_t num);
bool hash_table_s8_init_one_ll(const HashTableS8Config_t* const Config,HashTableS8Handle_t* const Node);

/*setters*/
bool hash_table_s8_push(uint8_t num, const int8_t value);
bool hash_table_s8_push_ll(HashTableS8Handle_t* Node, const int8_t value);
bool hash_table_s8_pull(uint8_t num, const int8_t value);
bool hash_table_s8_pull_ll(HashTableS8Handle_t* Node, const int8_t value);

/*getters*/
bool hash_table_s8_check_ll(HashTableS8Handle_t* Node, const int8_t value);
bool hash_table_s8_check(uint8_t num, const int8_t value);

#ifdef __cplusplus
}
#endif

#endif /* HASH_TABLE_S8_MCAL_H */
