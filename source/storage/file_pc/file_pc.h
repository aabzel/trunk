#ifndef FILE_PC_H
#define FILE_PC_H

#include <stddef.h>
#include <stdio.h>

#include "std_includes.h"

#ifdef HAS_MCU
#error That code only for desktop builds
#endif


bool file_pc_realpath(const char* const in_path, char* const out_file);

int32_t file_pc_get_size(char* file_name);
int32_t file_pc_line_cnt(const char* const file_name);
bool file_pc_delete(const char* const file_name);
bool file_pc_array_to_binary_file(const char* const file_name, const uint8_t* const  data, size_t  size);
bool file_pc_save_array(const char* const file_name, const uint8_t* const  data, size_t  size);
bool file_pc_save_array_i8(const char* const file_name, const int8_t* const  data, size_t  size);
bool file_pc_print_array(const char* const file_name, const uint8_t* const array, size_t size);
bool file_pc_print_line(const char* const file_name, const char* const text, size_t size);
bool file_pc_load_to_array(const char* const file_name, uint8_t* const out_buff, size_t size, uint32_t* const out_size) ;
bool file_pc_load_to_array_i8(char* const file_name, size_t offset, int8_t* const out_buff, size_t size);
bool file_pc_load_to_array_i8_ll(FILE* FileNode, size_t offset, int8_t* const out_buff, size_t size);
bool file_pc_run_through_lines(char* in_file_name,
                            char* pattern,
                            char* rep,
                            char* out_file_name);
bool file_pc_replace_substr(const char* const file_name, const char * const prev_str ,const char* const new_str);

#endif /* FILE_PC_H */
