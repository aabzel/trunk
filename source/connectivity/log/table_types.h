#ifndef TABLE_TYPES_H
#define TABLE_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "table_const.h"

typedef struct {
    uint8_t width;
    const char* name;
} table_col_t;

typedef struct {
    const char* left;
    const char* separator;
    const char* right;
    const char* fill;
} table_row_format_t;

#ifdef __cplusplus
}
#endif

#endif /* TABLE_TYPES_H */
