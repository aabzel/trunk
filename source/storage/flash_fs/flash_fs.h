/*
 * Definitions of Memory Manager methods
 *
 * This file contains definitions of OnChip NorFlash Memory Manager methods and constants
 *
 */

#ifndef NOR_FLASH_FS_H
#define NOR_FLASH_FS_H


#include "std_includes.h"
#include "data_types.h"
#include "flash_fs_config.h"
#include "flash_fs_types.h"
#include "flash_mcal.h"

#ifndef HAS_FLASH
#error "+ HAS_FLASH"
#endif

#ifndef HAS_NVS
#error "+ HAS_NVS"
#endif

#ifndef HAS_FLASH_FS
#error "+ HAS_FLASH_FS"
#endif

#ifndef HAS_CRC8
#error "+HAS_CRC8"
#endif

#ifdef HAS_FLASH_FS_WRITE
bool flash_fs_format(void);
bool flash_fs_erase(void);
bool flash_fs_invalidate(uint16_t data_id);
bool flash_fs_set(uint16_t data_id, const void* const new_file, uint16_t new_file_len);
bool flash_fs_set_lazy(uint16_t data_id, const void* const new_file, uint16_t new_file_len);
bool flash_fs_maintain(void);
bool flash_fs_turn_page(void);
#endif

extern const uint32_t active_page_token ;
//extern const Type32Union_t ActivePageToken;

FlashFsPage_t flash_fs_get_active_page_num(void);
bool flash_fs_is_active(uint8_t page_num);
bool flash_fs_init(void);
bool flash_fs_proc(void);
bool flash_fs_get(uint16_t data_id, void* const value, uint16_t max_value_len, uint16_t* value_len);
bool flash_fs_get_active_page(uint32_t* flash_fs_page_start, uint32_t* flash_fs_page_len);
bool flash_fs_get_address(uint16_t data_id, uint8_t** value_address, uint16_t* value_len);
bool is_flash_fs_addr(uint32_t addr);
uint32_t flash_fs_get_page_size(uint8_t page_num);
uint32_t flash_fs_get_page_base_addr(uint8_t page_num);
uint32_t flash_fs_cnt_files(uint32_t start_page_addr, uint32_t page_len, uint32_t* spare_cnt);
uint32_t flash_fs_get_remaining_space(void);
double flash_fs_get_remaining_space_percent(void);
FlashFsPage_t addr2page_num(uint32_t page_start);

#endif /* NOR_FLASH_FS_H */
