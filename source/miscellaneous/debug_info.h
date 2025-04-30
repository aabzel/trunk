#ifndef DEBUG_INFO_H
#define DEBUG_INFO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_LOG_UTILS
#include "ostream.h"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_STREAM
#error "+HAS_STREAM"
#endif

#include "data_types.h"



const char* OffSetToStr(uint32_t offset);
const char* ProgressRealToStr(float cur, float total) ;
const char* ProgressFloatToStr(float cur, float total) ;
const char* ProgressToStr(uint32_t cur, uint32_t total);
float diag_progress_log(uint32_t cur, uint32_t total, uint32_t parts);
bool print_progress(uint32_t cur, uint32_t total);
bool explore_stack_dir(void);
bool is_little_endian(void);
bool parse_stack(void);
bool print_ascii_line(char* buff, uint16_t size, uint16_t indent);
bool print_array(uint8_t* memory, uint32_t size);
bool print_binary(uint8_t const* const buff, uint32_t size);
bool check_main(void);
bool print_u64_un(U64_bit_t un);
//bool print_hex(const uint8_t* const buff, uint32_t size);
bool print_16bit_types(void* val);
bool print_64bit_types(void* val);
bool print_bit_hint(uint16_t offset, uint32_t bitness);
bool print_bit_representation(uint32_t val);
//bool print_mem(const uint8_t* const addr, int32_t len, bool is_bin, bool is_ascii, bool new_line, bool is_packed);
//bool print_bin(uint8_t const* const buff, uint32_t size, uint16_t indent);
bool print_vector_table(uint32_t vectors_table_base);
bool print_version(void);
bool print_sys_info(void);
bool print_indent(uint16_t indent);
void error_handler(void);
void print_sysinfo(void);
bool print_mem_ascii(uint8_t* memory, uint32_t size);
void print_hex_buf(const uint8_t* s, uint32_t len);
bool min_max_diag(U32Value_t* val, char* name);

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_INFO_H */
