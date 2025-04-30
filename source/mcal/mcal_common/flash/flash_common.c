#include "flash_mcal.h"

#include <string.h>

#include "compiler_const.h"
#include "flash_config.h"
#include "microcontroller_const.h"

#ifdef HAS_DEBUG_INFO
#include "debug_info.h"
#endif

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_FLASH_DIAG
#include "flash_diag.h"
#endif

#ifdef HAS_ARRAY
#include "array.h"
#endif

#ifdef HAS_INTERVAL
#include "interval.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

FlashHandle_t* FlashGetNode(uint8_t num) {
    FlashHandle_t* Node = &FlashInstance;
    return Node;
}

const FlashConfig_t* FlashGetConfig(uint8_t num) {
    const FlashConfig_t* Config = &FlashConfig;
    return Config;
}

bool flash_is_valid_config(const FlashConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LG_FLASH, "ConfigNull");
#endif
        res = false;
    }

    if(res) {
        if(Config->is_equal_sectors) {
            if(0 < Config->page_size) {
                res = true;
            } else {
#ifdef HAS_LOG
                LOG_ERROR(LG_FLASH, "FlashPageSizeErr");
#endif
                res = false;
            }
        } else {
            if(Config->PageArray) {
                res = true;
            } else {
#ifdef HAS_LOG
                LOG_ERROR(LG_FLASH, "NoFlashPageInfo");
#endif
                res = false;
            }
        }
    }

    if(res) {
        if(Config->page_cnt) {
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(LG_FLASH, "NoFlashPageCntInfo");
#endif
            res = false;
        }
    }

    if(res) {
        /* YTM32 can start flash from 0x0 */
        if(0 <= Config->start) {
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(LG_FLASH, "FlashStartErr");
#endif
            res = false;
        }
    }

    if(res) {
        if(0 <= Config->app_start) {
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(LG_FLASH, "FlashAppSizeErr");
#endif
            res = false;
        }
    }

    if(res) {
        if(0 <= Config->boot_start) {
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(LG_FLASH, "FlashBootSizeErr");
#endif
            res = false;
        }
    }

    if(res) {
        if(0 < Config->size) {

        } else {
#ifdef HAS_LOG
            LOG_ERROR(LG_FLASH, "FlashSizeErr");
#endif
            res = false;
        }
    }

    return res;
}

#ifdef HAS_FLASH_EX
_WEAK_FUN_
bool is_flash_addr(uint32_t address) {
    bool res = false;
    if(FlashConfig.start <= address) {
        if(address < (FlashConfig.size + FlashConfig.start)) {
            res = true;
        }
    } else {
        res = false; /*Just for step-by-step debugging*/
    }
    return res;
}
#endif

#ifdef HAS_INTERVAL
bool is_address_range(uint32_t address, uint32_t size) {
    bool res = false;
    IntervalE_t IntervalFlash = {0};
    IntervalFlash.start = FlashInstance.start;
    IntervalFlash.end = FlashInstance.start + FlashInstance.size;
    IntervalE_t IntervalData = {.start = address, .end = address + size};
    res = intervals_shared(&IntervalFlash, &IntervalData);
    return res;
}
#endif

#ifdef HAS_FLASH_EX
bool flash_scan(uint8_t* base, uint32_t size, float* usage_pec, uint32_t* spare, uint32_t* busy) {
    bool res = false;
    if(usage_pec && spare && busy) {
        res = true;
        *spare = 0;
        *busy = 0;
        uint8_t* addr = base;
        uint32_t cnt = 0;
        for(addr = base, cnt = 0; addr < (base + size); addr++, cnt++) {
            res = is_flash_addr((uint32_t)addr);
            if(false == res) {
                break;
            }
            if(0xFF == (*addr)) {
                (*spare)++;
            } else {
                (*busy)++;
            }
#ifdef HAS_DEBUG_INFO
            diag_progress_log(cnt, size, 500);
#endif
        }
        *usage_pec = (float)(((float)(100U * (*busy))) / ((float)size));
    }
    return res;
}
#endif

bool flash_init_common(const FlashConfig_t* const Config, FlashHandle_t* const Node) {
    bool res = false;
    if(Config) {
        res = flash_is_valid_config(Config);
#ifdef HAS_DEBUGGER
        ASSERT_CRITICAL(true == res);
#endif
        if(res) {
            res = false;
            if(Node) {
                Node->start = Config->start;
                Node->size = Config->size;
                Node->app_start = Config->app_start;
                Node->boot_start = Config->boot_start;
                Node->page_cnt = Config->page_cnt;
                Node->page_size = Config->page_size;
                Node->interrupt_on = Config->interrupt_on;
                Node->is_equal_sectors = Config->is_equal_sectors;
                res = true;

                Node->operation = FLASH_OPERATION_NOPE;
                Node->input = FLASH_INPUT_NONE;
                Node->state = FLASH_STATE_IDLE;
                Node->wr_flash_addr = 0xFFFFFFFF;
                Node->start_ms = 0;
                Node->diff_ms = 0;
                Node->spin_cnt = 0;
                Node->wr_byte = 0xFF;
                Node->wr_word = 0xFFFF;
                Node->wr_qword = 0xFFFFFFFF;
                Node->loop = false;
            }
        }
    }
    return res;
}

#ifdef HAS_ARRAY
bool is_erased(uint32_t addr, uint32_t size) {
    bool res = false;
    res = is_arr_pat((uint8_t*)addr, size, 0xff);
    return res;
}
#endif

#ifdef HAS_FLASH_EX
bool is_text_addr(uint32_t addr) { return is_flash_addr(addr); }
#endif

#ifdef HAS_FLASH_WRITE
bool flash_zero(uint32_t address, uint32_t size) {
    bool res = false;
    LOG_WARNING(LG_FLASH, "Addr:0x%x Size:%u", address, size);
    uint32_t i = 0;
    uint32_t ok = 0;
    for(i = 0; i < size; i++) {
        uint8_t zero = 0;
        res = flash_mcal_write(address + i, &zero, 1);
        if(res) {
            ok++;
        }
    }

    if(ok == size) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif

#ifdef HAS_FLASH_EX
/*
 Is there a continuously free block of given size starting at the address
 */
bool is_flash_spare(uint32_t address, uint32_t size) {
    uint32_t spare_size = 0;
    uint32_t busy_size = 0;
    bool res = false;
    float usage_pec = 0.0f;
    res = flash_scan((uint8_t*)address, size, &usage_pec, &spare_size, &busy_size);
    if(size == spare_size) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
#endif

/*
 * find the first address of spare continuous block of given size
 * returns the start address
 * */
#ifdef HAS_FLASH_EX
bool flash_find_spare_region(uint32_t* out_addr, uint32_t size) {
    uint32_t address = NOR_FLASH_BASE;
    bool res = false;
    for(address = NOR_FLASH_BASE; address < NOR_FLASH_END; address++) {
        res = is_flash_spare(address, size);
        if(res) {
            *out_addr = address;
            break;
        }
    }
    return res;
}
#endif

#ifdef HAS_FLASH_EX
static bool flash_is_sector_addr(uint32_t sector, uint32_t address) {
    bool res = false;
    uint32_t start_addr = FlashSectorConfig[sector].start;
    uint32_t end_addr = FlashSectorConfig[sector].start + FlashSectorConfig[sector].size - 4;
    if((start_addr <= address) && (address <= end_addr)) {
#ifdef HAS_LOG
        LOG_INFO(LG_FLASH, "Sector:%u 0x%p", sector, address);
#endif
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_FLASH_EX
bool flash_is_generic(uint32_t* address) {
    bool res = false;
    res = is_flash_addr((uint32_t)address);
    if(res) {
#ifdef HAS_LOG
        LOG_DEBUG(LG_FLASH, "Flash 0x%p", address);
#endif
        uint32_t sector_num = 0;
        uint32_t cnt = flash_get_sector_cnt();
        res = false;
        for(sector_num = 0; sector_num < cnt; sector_num++) {
            res = false;
            switch((uint8_t)FlashSectorConfig[sector_num].content) {
            case MEM_CONTENT_GENERIC_APP:
            case MEM_CONTENT_GENERIC_NET:
            case MEM_CONTENT_GENERIC: {
                res = flash_is_sector_addr(sector_num, (uint32_t)address);
                if(res) {
#ifdef HAS_FLASH_DIAG
                    LOG_INFO(LG_FLASH, "Addr: 0x%p Region:%s", address,
                             MemContent2Str(FlashSectorConfig[sector_num].content));
#endif
                    sector_num = cnt * 2;
                    break;
                }

            } break;

            } // switch
        }     // for
    }         // if
    return res;
}
#endif

#ifdef HAS_FLASH_EX
bool flash_is_bootloader(uint32_t* address) {
    bool res = false;
    res = is_flash_addr((uint32_t)address);
    if(res) {
#ifdef HAS_LOG
        LOG_INFO(LG_FLASH, "Flash %p", address);
#endif
        res = false;
        uint32_t sector_num = 0;
        uint32_t cnt = flash_get_sector_cnt();
        for(sector_num = 0; sector_num < cnt; sector_num++) {
            if(MEM_CONTENT_BOOTLADER == FlashSectorConfig[sector_num].content) {
                res = flash_is_sector_addr(sector_num, (uint32_t)address);
                if(res) {
                    break;
                }
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_FLASH_EX
bool flash_is_mbr(uint32_t address) {
    bool res = false;
    res = is_flash_addr((uint32_t)address);
    if(res) {
#ifdef HAS_LOG
        LOG_INFO(LG_FLASH, "Flash %p", address);
#endif
        res = false;
        uint32_t sector_num = 0;
        uint32_t cnt = flash_get_sector_cnt();
        for(sector_num = 0; sector_num < cnt; sector_num++) {
            if(MEM_CONTENT_MBR == FlashSectorConfig[sector_num].content) {
                res = flash_is_sector_addr(sector_num, (uint32_t)address);
                if(res) {
                    break;
                }
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_FLASH_WRITE
_WEAK_FUN_ bool flash_mcal_erase(uint32_t addr, uint32_t size) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_FLASH_EX
// flash_read - busy name in Zephyr project
_WEAK_FUN_
bool flash_mcal_read(uint32_t address, uint8_t* const rx_array, uint32_t size) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(LG_FLASH, "Read,Addr:0x%08X,Size:%u", address, size);
#endif
    res = is_address_range(address, size);
    if(res) {
        uint32_t i = 0;
        uint8_t* p_address = (uint8_t*)address;
        for(i = 0; i < size; i++) {
            res = is_flash_addr((uint32_t)p_address);
            if(res) {
                rx_array[i] = *(p_address);
                p_address++;
            } else {
                break;
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_FLASH_WRITE
/*
  | old_bit     |    new_bit  | is_legal?
0 |    0        |    0        | ok
1 |    0        |    1        | err
2 |    1        |    0        | ok
3 |    1        |    1        | ok
 */
bool flash_is_legal_change(uint8_t prev_byte, uint8_t new_byte) {
    bool res = false;
    uint8_t error = 0;
    error = (~prev_byte) & new_byte;
    if(error) {
        res = false;
    } else {
        res = true;
    }
    return res;
}

bool flash_is_legal_change_array(uint32_t flash_addr, const uint8_t* const wr_array, uint32_t size) {
    bool res = false;
    if(wr_array) {
        if(size) {
            uint32_t i = 0;
            uint32_t ok_cnt = 0;
            for(i = 0; i < size; i++) {
                uint8_t* prev_byte_ptr = (uint8_t*)flash_addr + i;
                res = flash_is_legal_change(*prev_byte_ptr, wr_array[i]);
                if(res) {
                    ok_cnt++;
                } else {
                    LOG_ERROR(LG_FLASH, "IllegalModification %u:0x%02x->0x%02x", i, *prev_byte_ptr, wr_array[i]);
                }
            }
            if(size == ok_cnt) {
                res = true;
            } else {
                res = false;
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_FLASH_WRITE
_WEAK_FUN_
bool flash_mcal_erasepage(uint32_t addr) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool flash_mcal_write(uint32_t flash_addr, uint8_t* data, uint32_t size) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_FLASH_EX
_WEAK_FUN_
bool flash_mcal_unlock(void) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_FLASH_EX
_WEAK_FUN_
bool flash_mcal_lock(void) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_FLASH_EX
_WEAK_FUN_ bool flash_lock_ctrl(bool on_off) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_FLASH_WRITE
_WEAK_FUN_ bool flash_mcal_erasesector(uint32_t addr) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_FLASH_EX
uint32_t flash_get_first_spare_page(void) {
    uint32_t spare_addr = 0xFFFFFFFF;
#ifdef HAS_FLASH_EQUAL_SECTORS
    uint32_t cur_addr = 0xFFFFFFFF;
    uint32_t i = 0;
    bool res = false;
    LOG_INFO(LG_FLASH, "SectorCnt:%u,SectorSize:%u Byte", FLASH_SECTOR_CNT, FLASH_PAGE_SIZE);

    for(i = 0; i < FLASH_SECTOR_CNT; i++) {
        cur_addr = ROM_START + FLASH_PAGE_SIZE * i;
        res = is_flash_spare(cur_addr, FLASH_PAGE_SIZE);
        if(res) {
            spare_addr = cur_addr;
            LOG_INFO(LG_FLASH, "SpotSparePage:0x%08x, Size:%u Byte", spare_addr, FLASH_PAGE_SIZE);
            break;
        } else {
            LOG_PARN(LG_FLASH, "busyPage:0x%08x, Size:%u Byte", cur_addr, FLASH_PAGE_SIZE);
        }
    }
#endif
    return spare_addr;
}
#endif

#ifdef HAS_FLASH_EX
bool flash_is_the_same(uint32_t addr_val, uint8_t* const array, size_t size) {
    bool res = false;
    int ret = 0;
    uint8_t* addr = (uint8_t*)addr_val;
    ret = memcmp((void*)addr, (void*)array, (size_t)size);
    if(0 == ret) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif

#ifdef HAS_FLASH_EX
bool flash_is_sector_start(uint32_t rand_addr, uint32_t chunk) {
    bool res = false;
    uint32_t sector_start = ROM_START;
    for(sector_start = ROM_START; sector_start <= (ROM_END - chunk); sector_start += chunk) {
        if(sector_start == rand_addr) {
            res = true;
            break;
        }
    }
    return res;
}
#endif

#ifdef HAS_FLASH_EX
bool flash_get_sector_start(uint32_t rand_addr, uint32_t chunk, uint32_t* sector_start_out) {
    bool res = false;
    uint32_t sector_start = ROM_START;
    for(sector_start = ROM_START; sector_start <= (ROM_END - chunk); sector_start += chunk) {
        uint32_t sector_end = sector_start + chunk;
        if(sector_start <= rand_addr) {
            if(rand_addr < sector_end) {
                *sector_start_out = sector_start;
                res = true;
                break;
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_FLASH_EX
int32_t flash_get_fragment_number(uint32_t in_addr, uint32_t fragment_size) {
    bool res = is_flash_addr(in_addr);
    int32_t block_number = -1;
    if(res) {
        uint32_t blok_start = ROM_START;
        for(blok_start = ROM_START; blok_start < ROM_END; blok_start += fragment_size) {
            uint32_t blok_end = blok_start + fragment_size;
            if(blok_start <= in_addr) {
                if(in_addr < blok_end) {
                    break;
                }
            }
            block_number++;
        }
    }

    return block_number;
}
#endif

#ifdef HAS_FLASH_EX
_WEAK_FUN_
bool flash_init(void) {
    bool res = true;
    // LOG_INFO(LG_FLASH, "Init");
    res = flash_is_valid_config(&FlashConfig);
    if(res) {
        res = flash_init_common(&FlashConfig, &FlashInstance);
    }
    return res;
}
#endif
