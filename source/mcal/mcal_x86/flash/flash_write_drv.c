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

#include "x86x.h"
#include "data_utils.h"
#include "microcontroller_const.h"
#include "time_mcal.h"
#ifdef HAS_CLOCK
#include "none_blocking_pause.h"
#endif

bool flash_mcal_write(uint32_t flash_addr, uint8_t* data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(LG_FLASH, "Write:Addr:0x%08x,Size:%u", flash_addr, size);
    res = is_flash_spare(flash_addr, size);
    if(res) {
        LOG_DEBUG(LG_FLASH, "WrInSpare");
    } else {
        LOG_WARNING(LG_FLASH, "NotSpare,%u Byte", size);
        res = flash_is_legal_change_array(flash_addr, data, size);
    }

    if(res) {
        res = flash_is_the_same(flash_addr, data, size);
        if(false == res) {
        } else {
            LOG_WARNING(LG_FLASH, "AlreadyTheSame");
        }
    }
    return res;
}

bool flash_write_dwords(uint32_t flash_addr, uint32_t* data, size_t size) {
    bool res = true;
    uint32_t flash_write_temp[MAX_SINGLE_WRITE_SIZE / 4];
    memset(flash_write_temp, 0xff, sizeof(flash_write_temp));
    if(size < sizeof(flash_write_temp)) {
        memcpy(flash_write_temp, data, size);
    } else {
        res = false;
    }

    /* ensure that data is 4 bytes aligned */
    if((size & 3) != 0) {
        res = false;
        size = ceil4byte(size);
    } else {
        res = false;
    }
    return res;
}

bool flash_mcal_erase(uint32_t addr, uint32_t size) {
    bool res = false;
    uint32_t sector_cnt = size / FlashConfig.page_size;
    (void)sector_cnt;
    res = is_erased(addr, size);
    return res;
}

// bool flash_erase_pages(uint8_t page_start, uint8_t page_end) { return false; }

bool flash_erase_sector(uint32_t addr) {
    bool res = false;
    res = flash_mcal_erase(addr, FlashConfig.page_size);
    return res;
}
