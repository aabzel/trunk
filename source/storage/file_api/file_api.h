#ifndef FILE_API_H
#define FILE_API_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "file_api_types.h"


int32_t file_line_cnt(const char* const filename);
int32_t file_get_size(const char* const file_name);
bool file_array_to_binary_file(const char* const file_name, const uint8_t* const  data, size_t  size);
bool file_save_array(const char* const file_name, const uint8_t* const array, size_t size);
bool file_load_to_array(const char* const file_name, uint8_t* const out_buff, uint32_t size, uint32_t* const read_size);
bool file_api_open_re(FileApiHandle_t* const Node,const char* const file_name);
bool file_api_close(FileApiHandle_t* const Node);
bool file_api_gets(FileApiHandle_t* const Node, char * const line, size_t size, size_t* const read_len_prt);

#endif /* FILE_API_H */
