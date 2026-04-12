#ifndef HASH_TABLE_DIAG_H
#define HASH_TABLE_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "hash_table_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_HASH_TABLE
#error "+HAS_HASH_TABLE"
#endif /*HAS_HASH_TABLE*/

#ifndef HAS_HASH_TABLE_DIAG
#error "+HAS_HASH_TABLE_DIAG"
#endif /*HAS_DIAG_HASH_TABLE*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool hash_table_diag(void);
const char* HashTableCellToStr(const HashTableCell_t* const Cell);
const char* HashTableConfigToStr(const HashTableConfig_t* const Config);
const char* HashTableNodeToStr(const HashTableHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* HASH_TABLE_DIAG_H  */
