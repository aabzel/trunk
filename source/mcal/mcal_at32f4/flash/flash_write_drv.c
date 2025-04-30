#include "flash_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_LOG
#include "log.h"
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

#include "artery_at32f4xx.h"
#include "data_utils.h"
#include "microcontroller_const.h"
#include "time_mcal.h"
#ifdef HAS_CLOCK
#include "none_blocking_pause.h"
#endif

bool flash_mcal_write(uint32_t flash_addr, uint8_t* data, uint32_t size) {
    bool res = false;
    uint32_t ok = 0;
    LOG_DEBUG(LG_FLASH, "Write:Addr:0x%08x,Size:%u", flash_addr, size);

    res = is_flash_spare(flash_addr, size);
    if(res) {
        LOG_DEBUG(LG_FLASH, "WrInSpare");
    } else {
        LOG_WARNING(LG_FLASH, "NotSpare,%u Byte", size);
        res = flash_is_legal_change_array(flash_addr, data, size);
#ifdef HAS_FLASH_DIAG
        flash_region_print(flash_addr, size);
#endif /*HAS_FLASH_DIAG*/
    }

    if(res) {
        res = flash_is_the_same(flash_addr, data, size);
        if(false == res) {

#ifdef HAS_FREE_RTOS
            xSemaphoreTake(xFlashWrireSem, (TickType_t)0);
#endif /*HAS_FREE_RTOS*/

            flash_unlock();
            flash_status_type ret = FLASH_PROGRAM_ERROR;
            uint32_t i = 0;
            for(i = 0; i < size; i++) {
                ret = flash_byte_program(flash_addr + i, data[i]);
                if(FLASH_OPERATE_DONE == ret) {
                    LOG_DEBUG(LG_FLASH, "WriteByteOk Addr:0x%08x,Offset:%u,Byte:0x%02x", flash_addr + i, i, data[i]);
                    ok++;
                } else {
                    LOG_ERROR(LG_FLASH, "WriteByteErr Addr:0x%08x,Offset:%u,Byte:0x%02x", flash_addr + i, i, data[i]);
                    LOG_ERROR(LG_FLASH, "WriteByteErr Ret:%u=%s", ret, FlashStatusToStr(ret));
                }
                /*TODO Add pause 1ms time_delay_ms(1)*/
            }
            flash_lock();
            if(ok == size) {
                res = true;
            } else {
#ifdef HAS_DIAG
                LOG_ERROR(LG_FLASH, "WriteErr Addr:0x%08x,Size:%u,WrOk:%u byte", flash_addr, size, ok);
#endif /*HAS_LOG*/
                res = false;
            }

#ifdef HAS_FREE_RTOS
            xSemaphoreGive(xFlashWrireSem);
#endif
        } else {
            LOG_WARNING(LG_FLASH, "AlreadyTheSame");
        }
    }
    return res;
}

bool flash_mcal_writeite_dword(uint32_t flash_addr, uint32_t* data, size_t size) {
    bool res = true;
    uint32_t flash_mcal_writeite_temp[MAX_SINGLE_WRITE_SIZE / 4];
    memset(flash_mcal_writeite_temp, 0xff, sizeof(flash_mcal_writeite_temp));
    if(size < sizeof(flash_mcal_writeite_temp)) {
        memcpy(flash_mcal_writeite_temp, data, size);
    } else {
        res = false;
    }

    /* ensure that data is 4 bytes aligned */
    if((size & 3) != 0) {
        res = false;
        size = ceil4byte(size);
    } else {
        res = false;
        flash_unlock();
        uint32_t ok = 0;
        uint32_t cur_address = flash_addr;
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
            cur_address = flash_addr + 4 * i;
            flash_status_type ret = flash_word_program(cur_address, data[i]);
            if(FLASH_OPERATE_DONE == ret) {
                ok++;
            } else {
                res = false;
            }
        }

        flash_lock();

        if(ok == size) {
            res = true;
        } else {
            res = false;
            LOG_ERROR(LG_FLASH, "WriteErr Addr:0x%08x,Size:%u", flash_addr, size);
        }
    }
    return res;
}

bool flash_mcal_erase(uint32_t addr, uint32_t size) {
    bool res = false;

    uint32_t sector_cnt = size / FlashConfig.page_size;
    (void)sector_cnt;

    res = is_erased(addr, size);
    if(false == res) {
        flash_unlock();

        uint32_t s = 0;
        for(s = 0; s < sector_cnt; s++) {
            flash_status_type ret = flash_sector_erase(addr + s * FlashConfig.page_size);
            if(FLASH_OPERATE_DONE == ret) {
                res = true;
            }
        }

        flash_lock();

    } else {
        LOG_DEBUG(LG_FLASH, "AlreadyErased");
    }
    return res;
}

// bool flash_erase_pages(uint8_t page_start, uint8_t page_end) { return false; }

bool flash_erase_sector(uint32_t addr) {
    bool res = false;
    res = flash_mcal_erase(addr, FlashConfig.page_size);
    return res;
}
