/**
 * NOR Flash Memory manager
 * This file contains implementation of key-val(file) map in Nor-Flash with
 * uniform deterioration of Nor Flash memory
 */
#include "flash_fs.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <esp_system.h>
#include <nvs.h>
#include <nvs_flash.h>

#include "crc8_autosar.h"
#include "data_utils.h"
#ifdef HAS_LOG
#include "io_utils.h"
#include "log.h"
#endif
#include "param_ids.h"

nvs_handle_t FsHandle;

FlashFs_t FlashFs;

bool mm_flash_format(void) {
    bool res = false;

    return res;
}

bool flash_fs_proc(void) {
    bool res = false;

    return res;
}

/**
 *     @brief   set new file to the variable with specified ID
 *
 *     @note    operation from user point of view is atomic - if something goes wrong during memory write,
 *             old file will be stored in memory, if old file doesn't exist - new variable will not be created
 *
 *     @param    data_id - data identifier to be written
 *             user could operate with data_id '0000' - '7FFF', other are reserved to the system
 *     @param    new_file - pointer to the new file of the variable
 *     @param    new_file_len - number of bytes within new_file
 *     @retval
 */
bool mm_set(uint16_t data_id, uint8_t* new_file, uint16_t new_file_len) {
    bool res = false;
    esp_err_t ret;
    char key[NVS_KEY_NAME_MAX_SIZE - 1];
    snprintf(key, sizeof(key), "%u", data_id);
    ret = nvs_set_blob(FsHandle, key, (const void*)new_file, (size_t)new_file_len);
    if(ESP_OK == ret) {
        ret = nvs_commit(FsHandle);
        if(ESP_OK == ret) {
            res = true;
        }
    } else {
        res = false;
    }
    return res;
}

/**
 *    @brief    get file of the specified variable
 *
 *    @param    data_id - data identifier to be read
 *    @param    file - pointer where data should be stored
 *    @param    maxValueLen - maximum number of bytes that could be stored within file
 *    @param    file_len - actual number of bytes stored within file

 */
bool mm_get(uint16_t data_id, uint8_t* file, uint16_t maxValueLen, uint16_t* file_len) {
    esp_err_t ret;
    bool res = false;
    char key[NVS_KEY_NAME_MAX_SIZE - 1];
    snprintf(key, sizeof(key), "%u", data_id);
    size_t length = (size_t)maxValueLen;
    ret = nvs_get_blob(FsHandle, key, (void*)file, &length);
    if(ESP_OK == ret) {
        if(length <= maxValueLen) {
            res = true;
            (*file_len) = length;
        } else {
            LOG_DEBUG(FLASH_FS, "GetLenErr Cur:%u Max:%u", *file_len, maxValueLen);
        }
    } else {
        res = false;
        LOG_DEBUG(FLASH_FS, "GetBlobErr %u %x", ret, ret); // 4364
    }
    return res;
}

/**
 *     @brief    invalidate (erase) specified variable, all references to specified variable will be removed
 *
 *     @note    this function does not erase actual file of the variable
 *             if user need to do that (if file is very sensitive), double page swap MUST be executed
 *
 *     @param    data_id - data identifier to be invalidated
 *     @retval
 */
bool mm_invalidate(uint16_t data_id) {
    bool res = false;
    char key[NVS_KEY_NAME_MAX_SIZE - 1];
    snprintf(key, sizeof(key), "%u", data_id);
    esp_err_t ret = nvs_erase_key(FsHandle, key);
    if(ESP_OK == ret) {
        res = true;
    } else {
        res = false;
    }

    return res;
}

/**
 *    @brief    flash memory is not mapped yet, remap it
 */
bool mm_flash_erase(void) {
    bool res = false;
    esp_err_t ret = nvs_flash_erase();
    if(ESP_OK == ret) {
        res = true;
    }
    return res;
}

bool flash_fs_init(void) {
    bool res = false;
    esp_err_t ret;
    ret = nvs_flash_init();
    if((ESP_ERR_NVS_NO_FREE_PAGES == ret) || (ESP_ERR_NVS_NEW_VERSION_FOUND == ret)) {
        ret = nvs_flash_erase();
        ret = nvs_flash_init();
    }
    nvs_open_mode_t open_mode = NVS_READWRITE;
    ret = nvs_open(STORAGE_NAMESPACE, open_mode, &FsHandle);
    if(ESP_OK == ret) {
        res = true;
    } else {
        res = false;
    }

    uint16_t reboot_cnt = 0;
    uint16_t file_len = 0;
    res = mm_get(PAR_ID_REBOOT_CNT, (uint8_t*)&reboot_cnt, sizeof(reboot_cnt), &file_len);
    if(res) {
        reboot_cnt++;
#ifdef HAS_LOG
        LOG_INFO(FLASH_FS, "reboot cnt: %u", reboot_cnt);
#endif
        res = mm_set(PAR_ID_REBOOT_CNT, (uint8_t*)&reboot_cnt, sizeof(reboot_cnt));
        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(FLASH_FS, "RebootCntSetErr");
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_WARNING(FLASH_FS, "lack of reboot counter");
#endif
        reboot_cnt = 0;
        res = mm_set(PAR_ID_REBOOT_CNT, (uint8_t*)&reboot_cnt, sizeof(reboot_cnt));
        if(false == res) {
#ifdef HAS_LOG
            LOG_WARNING(FLASH_FS, "ResetRebootCounter");
#endif
        }
    }
    return res;
}
