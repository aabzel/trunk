#include "flash_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_CRC16
#include "crc16_ccitt.h"
#endif

//#include "array.h"
#include "bit_utils.h"
#include "data_utils.h"
#include "flash_drv.h"

#ifdef HAS_FLASH_DIAG
#include "flash_diag.h"
#endif

#include "sys_config.h"

#ifdef HAS_CLOCK
#include "none_blocking_pause.h"
#endif

#include "flash_config.h"
#include "flash_custom_const.h"
#include "flash_custom_dep.h"
#include "flash_custom_drv.h"
#include "hal_nrfx_diag.h"
#include "nrfx_nvmc.h"

#ifdef HAS_FLASH_WRITE
bool flash_wr(uint32_t address, uint8_t* wr_array, uint32_t num_bytes) {
    LOG_INFO(LG_FLASH, "Wrire Addr:0x%08x Size %u byte", address, num_bytes);
    bool res = false;
    nrfx_nvmc_bytes_write(address, wr_array, num_bytes);
    res = true;
    return res;
}
#endif

#if 0
bool is_erased(uint32_t addr, uint32_t size) {
    bool res = false;
    res = is_arr_pat((uint8_t*)addr, size, 0xff);
    return res;
}
#endif

#ifdef HAS_FLASH_WRITE
bool flash_wr4(uint32_t addr, uint32_t* wr_array, size_t size) {
    bool res = true;

#if 0
    /* ensure that data is 4 bytes aligned */
    if((size & 3) != 0) {
        res = false;
        size = ceil4byte(size);
    } else {
    }
#endif

    res = is_flash_addr_range(addr, size);
    if(res) {
        nrfx_nvmc_words_write(addr, (void const*)wr_array, size);
        res = true;
    }
    return res;
}
#endif

#if 0
bool is_flash_addr(uint32_t flash_addr) {
    bool res = false;
#ifdef HAS_CORE_APP
    if(FLASH_START_APP_CORE <= flash_addr) {
        if(flash_addr < FLASH_END_APP_CORE) {
#ifdef HAS_LOG
            LOG_PARN(LG_FLASH, "App Flash 0x%x", flash_addr);
#endif /**/
            res = true;
        }
    }
#endif /*HAS_CORE_APP*/

#ifdef HAS_CORE_NET
    if((FLASH_START_NET_CORE <= flash_addr) && (flash_addr < FLASH_END_NET_CORE)) {
#ifdef HAS_LOG
        LOG_PARN(LG_FLASH, "Net Flash 0x%x", flash_addr);
#endif /*HAS_LOG*/
        res = true;
    }
#endif /*HAS_CORE_NET*/
    return res;
}
#endif

#if 0
/*
 Is there a continuously free block of given size starting at the flash_addr
 */
bool is_flash_spare(uint32_t flash_addr, uint32_t size) {
    uint32_t spare_size = 0;
    uint32_t busy_size = 0;
    bool res = false;
    float usage_pec = 0.0f;
    res = flash_scan((uint8_t*)flash_addr, size, &usage_pec, &spare_size, &busy_size);
    if(size == spare_size) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
#endif

/* find the first address of spare continuous block of given size
 * returns the start address
 * */
#if 0
bool flash_find_spare_region(uint32_t* out_addr, uint32_t size) {
    uint32_t flash_addr = ON_CHIP_NOR_FLASH_START;
    bool res = false;
    for(flash_addr = ON_CHIP_NOR_FLASH_START; flash_addr < ON_CHIP_NOR_FLASH_END; flash_addr++) {
        res = is_flash_spare(flash_addr, size);
        if(res) {
            *out_addr = flash_addr;
            break;
        }
    }
    return res;
}
#endif

uint32_t Nrf53Page2Addr(uint8_t page_start) {
    uint32_t address = 0;
    address = APP_START_ADDRESS + page_start * ON_CHIP_NOR_FLASH_PAGE_SIZE;
    return address;
}

#ifdef HAS_FLASH_WRITE
bool flash_mcal_erasepages(uint8_t page_start, uint8_t page_end) {
    bool res = false;
    nrfx_err_t ret = NRFX_ERROR_NULL;
    uint32_t address = 0;
    uint8_t page = 0;
    for(page = page_start; page <= page_end; page++) {
        address = Nrf53Page2Addr(page_start);
        ret = nrfx_nvmc_page_erase(address);
        if(NRFX_SUCCESS == ret) {
            LOG_INFO(LG_FLASH, "Page %u Errase Ok", page);
        } else {
            LOG_ERROR(LG_FLASH, "Page %u Errase Err %u=%s", page, ret, HalStatus2Str(ret));
        }
    }
    return res;
}
#endif

bool flash_is_page_start(uint32_t addr) {
    bool res = false;
    uint32_t page_start = 0;
    for(page_start = APP_START_ADDRESS; page_start < FLASH_END_APP_CORE; page_start += ON_CHIP_NOR_FLASH_PAGE_SIZE) {
        if(addr == page_start) {
            res = true;
            break;
        }
    }
    return res;
}

uint8_t Address2PageNum(uint32_t address) {
    uint8_t page = 0;
    page = (address - APP_START_ADDRESS) / ON_CHIP_NOR_FLASH_PAGE_SIZE;
    return page;
}

#ifdef HAS_FLASH_WRITE
bool flash_mcal_erase(uint32_t address, uint32_t size) {
    bool res = false;
    LOG_DEBUG(LG_FLASH, "Errase Addr: 0x%08x Size:%u", address, size);
    res = is_erased(address, size);
    if(false == res) {
        uint32_t page_cnt = size / ON_CHIP_NOR_FLASH_PAGE_SIZE;
        uint32_t rest_byte = size % ON_CHIP_NOR_FLASH_PAGE_SIZE;
        if(0 == rest_byte) {
            res = flash_is_page_start(address);
            if(res) {
                LOG_WARNING(LG_FLASH, "Errase Addr: 0x%08x Size:%u byte=%u Pages Rest:%u byte", address, size, page_cnt,
                            rest_byte);
                uint8_t page_start = Address2PageNum(address);
                res = flash_mcal_erasepages(page_start, page_start + page_cnt);
                if(res) {
                    LOG_INFO(LG_FLASH, "PageStart %u:%u Errase Ok", page_start, page_cnt);
                } else {
                    LOG_ERROR(LG_FLASH, "PageStart %u Errase Err", page_start);
                }
            }
        } else {
            LOG_ERROR(LG_FLASH, "SizeErr Rest %u byte", rest_byte);
        }
    } else {
        LOG_INFO(LG_FLASH, "Already Errased Addr:0x%x Size:%u", address, size);
    }

    return res;
}
#endif /*HAS_FLASH_WRITE*/

#if 0
bool flash_read_(uint32_t in_flash_addr, uint8_t* rx_array, uint32_t array_len) {
    bool res = false;
    uint32_t i = 0;
    uint8_t* p_flash_addr = (uint8_t*)in_flash_addr;
    for(i = 0; i < array_len; i++) {
        res = is_flash_addr((uint32_t)p_flash_addr);
        if(res) {
            rx_array[i] = *(p_flash_addr);
            p_flash_addr++;
        } else {
            LOG_ERROR(LG_FLASH, "ReadErr 0x%x", p_flash_addr);
            break;
        }
    }
    return res;
}
#endif

uint32_t flash_get_first_spare_page(void) {
    bool res = false;
    uint32_t flash_addr = 0;
    uint32_t flash_addr_res = 0xFFFFFFFF;
    for(flash_addr = 0; flash_addr < (ON_CHIP_NOR_FLASH_SIZE - ON_CHIP_NOR_FLASH_PAGE_SIZE);
        flash_addr += ON_CHIP_NOR_FLASH_PAGE_SIZE) {
        res = is_flash_spare(flash_addr, ON_CHIP_NOR_FLASH_PAGE_SIZE);
        if(res) {
            flash_addr_res = flash_addr;
            break;
        }
    }
    return flash_addr_res;
}

#ifdef HAS_FLASH_WRITE
bool flash_mcal_eraseall(void) {
    bool res = false;
    LOG_WARNING(LG_FLASH, "ErraseAll!");
    nrfx_nvmc_all_erase();
    res = true;
    return res;
}
#endif

bool flash_init(void) {
    bool res = true;
    LOG_WARNING(LG_FLASH, "On-Chip Init");
    LOG_INFO(LG_FLASH, "StartAddress: 0x%08x PageSize %u Bytes", APP_START_ADDRESS, ON_CHIP_NOR_FLASH_PAGE_SIZE);
    LOG_INFO(LG_FLASH, "TotalSize: %u Byte 0x%x Byte", ON_CHIP_NOR_FLASH_SIZE, ON_CHIP_NOR_FLASH_SIZE);
    LOG_INFO(LG_FLASH, "TotalSize %u Pages", ON_CHIP_NOR_FLASH_PAGE_CNT);
#ifdef HAS_CRC16
    FlashItem.crc16 = calc_crc16_ccitt_false((const uint8_t* const)APP_START_ADDRESS, ON_CHIP_NOR_FLASH_SIZE);
    LOG_INFO(LG_FLASH, "AllFlash CRC16 0x%x", FlashItem.crc16);
#endif
    FlashItem.start = APP_START_ADDRESS;
    FlashItem.size = nrfx_nvmc_flash_size_get();
    FlashItem.page_size = nrfx_nvmc_flash_page_size_get();
    FlashItem.page_cnt = nrfx_nvmc_flash_page_count_get();
    FlashItem.end = APP_START_ADDRESS + FlashItem.size;
#ifdef HAS_FLASH_DIAG
    FlashDiagNode(&FlashItem);
#endif

    FlashItem.init = true;
    return res;
}
