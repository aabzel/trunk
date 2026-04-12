#ifndef CSV_H
#define CSV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "std_includes.h"
#include "csv_types.h"
#include "csv_diag.h"

#ifndef HAS_CSV
#error "+HAS_CSV"
#endif

uint32_t csv_cnt(const char* const in_text, char separator);

bool csv_proc_fetch_value(CsvFsm_t* Node, uint32_t cur_index) ;
bool csv_parse_last_text(const char* const in_text, char separator, char* const out_text, uint32_t out_size);

uint32_t csv_del_node_front(const char* const in_text, char separator, const char* const name);
uint32_t csv_count_node(const char* const in_text, char separator, const char* const name);
bool csv_add_back(char* const in_text, char separator, char* const suffix);
bool csv_fetch_text(const char* const in_text, uint32_t size, char separator, uint32_t index,  uint32_t* const offset);
bool csv_parse_text(const char* const in_text, char separator, uint32_t index, char* const out_text, uint32_t size);
bool csv_parse_uint8(const char* const in_text, char separator, uint32_t index, uint8_t* const byte);
bool csv_parse_int16(const char* const in_text, char separator, uint32_t index, int16_t* const word);
bool csv_parse_double(const char* const in_text, uint32_t index, double* const value);
#ifdef HAS_PC
bool csv_save_two_float_int_end(char* file_name,
                            uint32_t t,
                            const float xf,
                            const int32_t yd) ;
bool csv_save_to_end(char* file_name, double x, double y) ;
bool csv_save_two_double(char* file_name, uint32_t size, double* x, double* y);
bool csv_save_two_float_int(char* file_name, uint32_t size, const float* const x, const int32_t* const y);
#endif

#ifdef __cplusplus
}
#endif

#endif /* CSV_H */
