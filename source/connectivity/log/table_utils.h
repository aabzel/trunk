#ifndef TABLE_UTILS_H
#define TABLE_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "data_utils.h"
#include "table_types.h"
#ifdef HAS_LOG_UTILS
#include "stream.h"
#include "log_utils.h"
#endif

#ifdef HAS_LOG_UTILS

void table_cap(ostream_t* header_ostream, const table_col_t header_cols[], int16_t header_col_count);
void table_header(ostream_t* header_ostream, const table_col_t header_cols[], int16_t header_col_count);
void table_row_bottom(ostream_t* row_bottom_ostream, const table_col_t row_bottom_cols[], int16_t row_bottom_col_count);
void table_row_header(ostream_t* row_header_ostream, const table_col_t row_header_cols[], int16_t row_header_col_count);
void table_row_separator(ostream_t* row_separator_ostream, const table_col_t row_separator_cols[],
                         int16_t row_separator_col_count);
void table_row_top(ostream_t* row_top_ostream, const table_col_t row_top_cols[], int16_t row_top_col_count);
#endif

#ifdef __cplusplus
}
#endif

#endif /* TABLE_UTILS_H */
