#include "flash_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_BIT_UTILS
#include "bit_utils.h"
#endif
#include "data_utils.h"
#include "flash_custom_const.h"
#include "flash_custom_drv.h"
#include "hal_mcal.h"
#include "mik32_hal.h"
#include "sys_config.h"

#ifdef HAS_EEPROM
#include "eeprom_mcal.h"
#include "mik32_hal_eeprom.h"
#endif

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

#ifdef HAS_FREE_RTOS
#include "FreeRTOS.h"
#include "semphr.h"
#endif

#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif
//#include "mik32_hal.h"

#ifdef HAS_FREE_RTOS
SemaphoreHandle_t xFlashWrireSem = NULL;
#endif

bool flash_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(LG_FLASH, "Init");
#endif
#ifdef HAS_DEBUGGER
    // ASSERT_CRITICAL(FlashConfig.end);
    // ASSERT_CRITICAL(FlashConfig.start);
#endif
    res = flash_init_common(&FlashConfig, &FlashInstance);
    return res;
}

#ifdef HAS_FLASH_WRITE

bool flash_mcal_write(uint32_t flash_addr, uint8_t* wr_array, uint32_t size) {
    bool res = false;
    LOG_DEBUG(LG_FLASH, "Write:Addr:0x%08x,Size:%u", flash_addr, size);
    return res;
}
#endif /*HAS_FLASH_WRITE*/

#ifdef HAS_FLASH_WRITE
bool flash_mcal_writeite_dword(uint32_t flash_addr, uint32_t* wr_array, size_t size) {
    bool res = true;

    return res;
}
#endif

#ifdef HAS_FLASH_EX
bool AddrToSectorSize(uint32_t addr, uint32_t* sector, uint32_t* sec_size) {
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

bool is_spi_flash_address(uint32_t address) {
    bool res = false;
    if(EXT_ROM_START <= address) {
        if(address < EXT_ROM_END) {
            res = true;
        }
    }
    return res;
}

bool is_flash_addr(uint32_t address) {
    bool res = false;

#ifdef HAS_EEPROM
    res = eeprom_is_address(address);
#endif

    if(false == res) {
        res = is_spi_flash_address(address);
    }

    return res;
}
