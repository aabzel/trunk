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

#include "data_utils.h"
#include "flash_config.h"
#include "sys_config.h"
#ifdef HAS_CLOCK
#include "none_blocking_pause.h"
#endif
#include "at32f435_437.h"
#include "flash_custom_const.h"

#ifdef HAS_FREE_RTOS
SemaphoreHandle_t xFlashWrireSem = NULL;
#endif

#if defined(AT32F437xM) || defined(AT32F435xM) || defined(AT32F437xD) || defined(AT32F435xD)
#define SECTOR_SIZE 4096 /* this parameter depends on the specific model of the chip */
#else
#define SECTOR_SIZE 2048 /* this parameter depends on the specific model of the chip */
#endif

/**
 * @brief  read data using halfword mode
 * @param  read_addr: the address of reading
 * @param  p_buffer: the buffer of reading data
 * @param  num_read: the number of reading data
 * @retval none
 */
void flash_read_u16(uint32_t read_addr, uint16_t* p_buffer, uint16_t num_read) {
    uint16_t i;
    for(i = 0; i < num_read; i++) {
        p_buffer[i] = *(uint16_t*)(read_addr);
        read_addr += 2;
    }
}

bool flash_init(void) {
    bool res = true;
    LOG_INFO(LG_FLASH, "Init");

    FlashInstance.start = ROM_START;
    FlashInstance.end = ROM_END;
    FlashInstance.size = ROM_SIZE;
    FlashInstance.init = true;
    FlashInstance.page_cnt = 8;
#ifdef HAS_FREE_RTOS
    xFlashWrireSem = xSemaphoreCreateMutex();
    xSemaphoreGive(xFlashWrireSem);
#endif
    LOG_INFO(LG_FLASH, "Ready");
    res = true;

    return res;
}

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
