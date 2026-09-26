#ifndef FILE_MCAL_H
#define FILE_MCAL_H

#include <stddef.h>

#include "std_includes.h"
#include "file_mcal_types.h"
#include "file_mcal_config.h"

#ifdef HAS_FILE_MCAL_DIAG
#include "file_mcal_diag.h"
#endif


/* API */
FileMcalHandle_t* FileMcalGetNode(uint8_t num);
const FileMcalConfig_t* FileMcalGetConfig(uint8_t num);
bool FileMcalIsValidConfig(const FileMcalConfig_t* const Config);

bool file_mcal_mcal_init(void);
bool file_mcal_init_custom(void);
bool file_mcal_init_common(const FileMcalConfig_t* const Config, FileMcalHandle_t* const Node);
bool file_mcal_init_node(FileMcalHandle_t* const Node);
bool file_mcal_init_one(uint8_t num);
bool file_mcal_is_valid_num(uint8_t num);

bool file_mcal_proc_one(uint8_t num);
bool file_mcal_proc(void);

/*getter*/
int32_t file_line_cnt(uint8_t num, const char* const file_name);
uint32_t file_mcal_read(uint8_t num, uint8_t* const out_buff, uint32_t size);
int32_t file_get_size(uint8_t num, const char* const file_name);
bool file_mcal_gets(FileMcalHandle_t* const Node, char * const line, uint32_t  size, uint32_t * const read_len_prt);
char* file_path_to_file_name(const char* const file_path);

/*setter*/
bool file_mcal_close(uint8_t num);
bool file_mcal_open_append(uint8_t num, const char* const file_name);
bool file_mcal_open_wb(uint8_t num, const char* const file_name);
bool file_mcal_open_re(uint8_t num, const char* const file_name);
bool file_mcal_write(uint8_t num, const uint8_t* const data, uint32_t size);
bool file_mcal_write_line(uint8_t num, const char* const line, uint32_t len) ;
bool file_array_to_binary_file(uint8_t num, const char* const file_name, const uint8_t* const data, uint32_t size);
bool file_save_array(uint8_t num, const char* const file_name, const uint8_t* const data, uint32_t size);
bool file_mcal_delete(uint8_t num, const char* const file_name);
bool file_mcal_rename(uint8_t num, const char* const old_name, const char* const new_name);


#endif /* FILE_MCAL_H */
