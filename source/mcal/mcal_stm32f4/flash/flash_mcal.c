#include "flash_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_LOG
#include "log.h"
#endif
#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_DIAG
#include "hal_diag.h"
#endif

#ifdef HAS_ARRAY
#include "array.h"
#endif
#include "bit_utils.h"

#ifdef HAS_FREE_RTOS
#include "FreeRTOS.h"
#include "semphr.h"
#endif

#include "data_utils.h"
#include "sys_config.h"
#ifdef HAS_CLOCK
#include "none_blocking_pause.h"
#endif
#include "flash_custom_const.h"
#include "stm32f4xx_hal.h"

#ifdef HAS_FREE_RTOS
SemaphoreHandle_t xFlashWrireSem = NULL;
#endif

bool flash_init(void) {
    bool res = true;
    LOG_INFO(LG_FLASH, "Init");
    HAL_StatusTypeDef ret = HAL_ERROR;

#ifdef HAS_DEBUGGER
    ASSERT_CRITICAL(FlashConfig.start);
    ASSERT_CRITICAL(FlashConfig.size);
#endif
    res = flash_init_common(&FlashConfig, &FlashInstance);

    FlashInstance.init = true;
#ifdef HAS_FREE_RTOS
    xFlashWrireSem = xSemaphoreCreateMutex();
    xSemaphoreGive(xFlashWrireSem);
#endif
    /* write data to flash */
    HAL_FLASH_Unlock();
    uint32_t i = 0;
    for(i = 0; i < 5; i++) {
        ret = FLASH_WaitForLastOperation(5000);
        if(HAL_OK == ret) {
            LOG_INFO(LG_FLASH, "Ready");
            res = true;
            break;
        } else {
#ifdef HAS_DIAG
            LOG_ERROR(LG_FLASH, "Err %u=%s", ret, HalStatus2Str(ret));
#endif
            res = false;
        }
    }

    HAL_FLASH_Lock();

    return res;
}

#ifdef HAS_FLASH_WRITE
bool flash_mcal_write(uint32_t flash_addr, uint8_t* wr_array, uint32_t size) {
    bool res = false;
    LOG_DEBUG(LG_FLASH, "Write:Addr:0x%08x,Size:%u", flash_addr, size);

    res = is_flash_spare(flash_addr, size);
    if(res) {
        LOG_DEBUG(LG_FLASH, "WrInSpare");
    } else {
        LOG_WARNING(LG_FLASH, "NotSpare,%u Byte", size);
        res = flash_is_legal_change_array(flash_addr, wr_array, size);
#ifdef HAS_FLASH_DIAG
        flash_region_print(flash_addr, size);
#endif /*HAS_FLASH_DIAG*/
    }
#ifdef HAS_FREE_RTOS
    xSemaphoreTake(xFlashWrireSem, (TickType_t)0);
#endif /*HAS_FREE_RTOS*/
    uint32_t j = 0;
    uint32_t ok_cnt = 0;
    /* write data to flash */
    HAL_FLASH_Unlock();
    HAL_StatusTypeDef ret = HAL_ERROR;
    for(j = 0; j < size;) {
#if 0
            ret = FLASH_WaitForLastOperation(5000);
            if(HAL_OK == ret) {
            } else {
#ifdef HAS_DIAG
                LOG_ERROR(LG_FLASH, "BusyErr %u=%s", ret, HalStatus2Str(ret));
#endif
                res = false;
                //break;
            }
#endif
        ret = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, flash_addr, wr_array[j]);
        if(HAL_OK == ret) {
            flash_addr += 1;
            j++;
            ok_cnt++;
        } else {
#ifdef HAS_DIAG
            LOG_ERROR(LG_FLASH, "ProgramErr Array[%u]=0x%02x Err %u=%s", j, wr_array[j], ret, HalStatus2Str(ret));
#endif /*HAS_LOG*/
            res = false;
            break;
        }
    }
    HAL_FLASH_Lock();

    if(ok_cnt == size) {
        res = true;
    } else {
        LOG_ERROR(LG_FLASH, "WrPartial Real %u Need %u", ok_cnt, size);
        res = false;
    }
#ifdef HAS_FREE_RTOS
    xSemaphoreGive(xFlashWrireSem);
#endif
    return res;
}
#endif /*HAS_FLASH_WRITE*/

#ifdef HAS_FLASH_WRITE
bool flash_mcal_writeite_dword(uint32_t flash_addr, uint32_t* wr_array, size_t size) {
    bool res = true;
    uint32_t flash_mcal_writeite_temp[MAX_SINGLE_WRITE_SIZE / 4];
    memset(flash_mcal_writeite_temp, 0xff, sizeof(flash_mcal_writeite_temp));
    if(size < sizeof(flash_mcal_writeite_temp)) {
        memcpy(flash_mcal_writeite_temp, wr_array, size);
    } else {
        res = false;
    }
    /* ensure that data is 4 bytes aligned */
    if((size & 3) != 0) {
        res = false;
        size = ceil4byte(size);
    } else {
        uint32_t i = 0, j = 0;
        /* write data to flash */
        HAL_FLASH_Unlock();
        for(i = 0, j = 0; j < size; i++, j += QWORD_LEN) {
            if(HAL_OK == HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, flash_addr, flash_mcal_writeite_temp[i])) {
                flash_addr += QWORD_LEN;
            } else {
                HAL_FLASH_Lock();
                return false;
            }
        }
        HAL_FLASH_Lock();
    }
    return res;
}
#endif

#ifdef HAS_FLASH_EX
bool Addr2SectorSize(uint32_t addr, uint32_t* sector, uint32_t* sec_size) {
    bool res = false;
    if(sector && sec_size) {
        uint32_t cnt = flash_get_sector_cnt();
        uint32_t i = 0;
        for(i = 0; i < cnt; i++) {
            uint32_t end_addr = FlashSectorConfig[i].start + FlashSectorConfig[i].size;
            if((FlashSectorConfig[i].start <= addr) && (addr <= end_addr)) {
                (*sector) = (uint32_t)FlashSectorConfig[i].sector;
                (*sec_size) = (uint32_t)FlashSectorConfig[i].size;
                res = true;
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_FLASH_WRITE
bool flash_mcal_erase(uint32_t addr, uint32_t size) {
    bool res = false;
    uint32_t sector = 0;
    uint32_t sec_cnt = 0;
    uint32_t sec_size = 0;
    res = is_erased(addr, size);
    if(false == res) {
#ifdef HAS_FLASH_EX
        res = Addr2SectorSize(addr, &sector, &sec_size);
        if(res) {
            if(size <= sec_size) {
                sec_cnt = 1;
            } else {
                sec_cnt = 2;
            }
        }

        if(res) {
            FLASH_EraseInitTypeDef EraseInitStruct;
            uint32_t SectorError = 0;
            EraseInitStruct.Banks = FLASH_BANK_1;
            EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
            EraseInitStruct.Sector = sector;
            EraseInitStruct.NbSectors = sec_cnt;
            EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;

            /* actual erase flash */
            HAL_FLASH_Unlock();
            HAL_StatusTypeDef ret = HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError);
            HAL_FLASH_Lock();
            if(HAL_OK != ret) {
                res = false;
            }
        }
#endif
    } else {
        LOG_DEBUG(LG_FLASH, "AlreadyErased");
    }
    return res;
}
#endif

#ifdef HAS_FLASH_WRITE
bool flash_mcal_erasepages(uint8_t page_start, uint8_t page_end) { return false; }
#endif

#ifdef HAS_FLASH_WRITE
bool flash_mcal_erasesector(uint32_t addr) {
    bool res = flash_mcal_erasepage(addr);
    return res;
}
#endif
