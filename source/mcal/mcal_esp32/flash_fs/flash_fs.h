/**
 * @brief Definitions of Memory Manager methods
 *
 * This file contains definitions of Memory Manager methods and constants
 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/nvs_flash.html#_CPPv412nvs_handle_t
 */

#ifndef FLASH_FS_NOR_FLASH_H
#define FLASH_FS_NOR_FLASH_H

#include <nvs.h>
#include <stdbool.h>
#include <stdint.h>

#include "flash_drv.h"
#include "timer_utils.h"

#define STORAGE_NAMESPACE "FlashFs"

#define FLASH_FS_PERIOD_US MIN_2_US(5)
#define FLASH_FS_MAX_FILE_SIZE 256

typedef struct xFlashFs_t {
    uint32_t err_set_cnt;
    uint32_t err_get_cnt;
} FlashFs_t;

extern FlashFs_t FlashFs;
extern nvs_handle_t FsHandle;

bool flash_fs_init(void);
bool flash_fs_proc(void);
bool mm_flash_format(void);
bool mm_flash_erase(void);
bool mm_get(uint16_t data_id, uint8_t* value, uint16_t max_value_len, uint16_t* value_len);
bool mm_invalidate(uint16_t data_id);
bool mm_set(uint16_t data_id, uint8_t* new_file, uint16_t new_file_len);
uint32_t mm_cnt_files(uint32_t start_page_addr, uint32_t page_len, uint32_t* spare_cnt);
uint32_t mm_get_remaining_space(void);

#endif /* FLASH_FS_NOR_FLASH_H */
