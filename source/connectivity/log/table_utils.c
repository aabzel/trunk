#include "table_utils.h"

#ifdef HAS_LOG_UTILS
#include "ostream.h"
#endif

#include <string.h>

static int16_t get_col_count(const table_col_t cols[]) {
    int16_t count = 0;
    while(0U < cols[count].width) {
        count++;
    }
    return count;
}

static void table_row(ostream_t* row_ostream, const table_col_t row_cols[], int16_t row_col_count,
                      const table_row_format_t* row_format) {
    int16_t row_col_index;
    int16_t cnt_row_col_count = row_col_count;
    if(cnt_row_col_count < 0) {
        cnt_row_col_count = get_col_count(row_cols);
    }
    for(row_col_index = 0; row_col_index < cnt_row_col_count; row_col_index++) {
        uint8_t w;
        if(0 == row_col_index) {
            oputs(row_ostream, row_format->left);
        } else {
            oputs(row_ostream, row_format->separator);
        }
        w = row_cols[row_col_index].width;
        while(w > 0U) {
            oputs(row_ostream, row_format->fill);
            w--;
        }
    }
    oputs(row_ostream, row_format->right);
    oputs(row_ostream, CRLF);
}

void table_row_top(ostream_t* row_top_ostream, const table_col_t row_top_cols[], int16_t row_top_col_count) {
    static const table_row_format_t row_top_format = {TABLE_TOP_LEFT, TABLE_TOP_SEPARATOR, TABLE_TOP_RIGHT,
                                                      TABLE_TOP_FILL};
    table_row(row_top_ostream, row_top_cols, row_top_col_count, &row_top_format);
}

void table_row_separator(ostream_t* row_separator_ostream, const table_col_t row_separator_cols[],
                         int16_t row_separator_col_count) {
    static const table_row_format_t row_separator_format = {TABLE_SEP_LEFT, TABLE_SEP_SEPARATOR, TABLE_SEP_RIGHT,
                                                            TABLE_SEP_FILL};
    table_row(row_separator_ostream, row_separator_cols, row_separator_col_count, &row_separator_format);
}

void table_row_bottom(ostream_t* row_bottom_ostream, const table_col_t row_bottom_cols[],
                      int16_t row_bottom_col_count) {
    static const table_row_format_t row_bottom_format = {TABLE_BTM_LEFT, TABLE_BTM_SEPARATOR, TABLE_BTM_RIGHT,
                                                         TABLE_BTM_FILL};
    table_row(row_bottom_ostream, row_bottom_cols, row_bottom_col_count, &row_bottom_format);
}

static void table_row_hdr(ostream_t* row_hdr_ostream, const table_col_t row_hdr_cols[], int16_t row_hdr_col_count,
                          const table_row_format_t* row_hdr_format) {
    int16_t hdr_col_index;
    int16_t cnt_row_hdr_col_count = row_hdr_col_count;
    if(cnt_row_hdr_col_count < 0) {
        cnt_row_hdr_col_count = get_col_count(row_hdr_cols);
    }
    for(hdr_col_index = 0; hdr_col_index < cnt_row_hdr_col_count; hdr_col_index++) {
        uint32_t text_len = strlen(row_hdr_cols[hdr_col_index].name);
        if(0 == hdr_col_index) {
            oputs(row_hdr_ostream, row_hdr_format->left);
        } else {
            oputs(row_hdr_ostream, row_hdr_format->separator);
        }
        if(row_hdr_cols[hdr_col_index].width < text_len) {
            oputs_len(row_hdr_ostream, row_hdr_cols[hdr_col_index].name, (int32_t)row_hdr_cols[hdr_col_index].width);
        } else {
            uint32_t hdr_col_width = (uint32_t)row_hdr_cols[hdr_col_index].width;
            uint8_t sl = (uint8_t)((hdr_col_width - text_len) / 2U);
            uint8_t sr = (uint8_t)((hdr_col_width - (uint32_t)sl) - text_len);
            while(sl > 0U) {
                oputs(row_hdr_ostream, row_hdr_format->fill);
                sl--;
            }
            oputs(row_hdr_ostream, row_hdr_cols[hdr_col_index].name);
            while(sr > 0U) {
                oputs(row_hdr_ostream, row_hdr_format->fill);
                sr--;
            }
        }
    }
    oputs(row_hdr_ostream, row_hdr_format->right);
    oputs(row_hdr_ostream, CRLF);
}

void table_row_header(ostream_t* row_header_ostream, const table_col_t row_header_cols[],
                      int16_t row_header_col_count) {
    static const table_row_format_t row_header_format = {TABLE_LEFT, TABLE_SEPARATOR, TABLE_RIGHT, TABLE_FILL};
    table_row_hdr(row_header_ostream, row_header_cols, row_header_col_count, &row_header_format);
}

void table_header(ostream_t* header_ostream, const table_col_t header_cols[], int16_t header_col_count) {
    if(header_ostream) {
        table_row_top(header_ostream, header_cols, header_col_count);
        table_row_header(header_ostream, header_cols, header_col_count);
        table_row_separator(header_ostream, header_cols, header_col_count);
    }
}

void table_cap(ostream_t* header_ostream, const table_col_t header_cols[], int16_t header_col_count) {
    if(header_ostream) {
        table_row_top(header_ostream, header_cols, header_col_count);
        table_row_header(header_ostream, header_cols, header_col_count);
    }
}
