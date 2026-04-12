#ifndef HASH_TABLE_S8_DIAG_H
#define HASH_TABLE_S8_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "hash_table_s8_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_HASH_TABLE_S8
#error "+HAS_HASH_TABLE_S8"
#endif /*HAS_HASH_TABLE_S8*/

#ifndef HAS_HASH_TABLE_S8_DIAG
#error "+HAS_HASH_TABLE_S8_DIAG"
#endif /*HAS_DIAG_HASH_TABLE_S8*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool hash_table_s8_diag(void);
const char* HashTableS8ConfigToStr(const HashTableS8Config_t* const Config);
const char* HashTableS8NodeToStr(const HashTableS8Handle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* HASH_TABLE_S8_DIAG_H  */
