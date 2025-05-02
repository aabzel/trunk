#include "eeprom_mcal.h"

#include <string.h>

#include "compiler_const.h"
#include "debug_info.h"
#include "eeprom_config.h"
#include "microcontroller_const.h"
#include "storage.h"

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_EEPROM_DIAG
#include "eeprom_diag.h"
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

EepromHandle_t* EepromGetNode(uint8_t num) {
    EepromHandle_t* Node = &EepromInstance;
    return Node;
}

const EepromConfig_t* EepromGetConfig(uint8_t num) {
    const EepromConfig_t* Config = &EepromConfig;
    return Config;
}

bool eeprom_is_valid_config(const EepromConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(EEPROM, "ConfigNull");
#endif
        res = false;
    }

    if(res) {
        /* YTM32 can start eeprom from 0x0 */
        if(0 <= Config->start) {
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(EEPROM, "EepromStartErr");
#endif
            res = false;
        }
    }

    if(res) {
        if(0 < Config->size) {

        } else {
#ifdef HAS_LOG
            LOG_ERROR(EEPROM, "EepromSizeErr");
#endif
            res = false;
        }
    }

    return res;
}

_WEAK_FUN_
bool eeprom_bytes_read(const uint32_t phy_addr, uint8_t* const data, const uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    for(i = 0; i < size; i++) {
        res = eeprom_byte_read(phy_addr + i, &data[i]);
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

_WEAK_FUN_
bool eeprom_is_address(uint32_t address) {
    bool res = false;
    if(EepromConfig.start <= address) {
        if(address < (EepromConfig.start + EepromConfig.size)) {
            res = true;
        }
    } else {
        res = false; /*Just for step-by-step debugging*/
    }
    return res;
}

#ifdef HAS_INTERVAL
bool eeprom_is_address_range(uint32_t address, uint32_t size) {
    bool res = false;
    IntervalE_t IntervalEeprom = {0};
    IntervalEeprom.start = EepromInstance.start;
    IntervalEeprom.end = EepromInstance.end;
    IntervalE_t IntervalData = {.start = address, .end = address + size};
    res = intervals_shared(&IntervalEeprom, &IntervalData);
    return res;
}
#endif

bool eeprom_scan(uint8_t* base, uint32_t size, float* usage_pec, uint32_t* spare, uint32_t* busy) {
    bool res = false;
    if(usage_pec && spare && busy) {
        res = true;
        *spare = 0;
        *busy = 0;
        uint8_t* addr = base;
        uint32_t cnt = 0;
        for(addr = base, cnt = 0; addr < (base + size); addr++, cnt++) {
            res = eeprom_is_address((uint32_t)addr);
            if(false == res) {
                break;
            }
            if(0xFF == (*addr)) {
                (*spare)++;
            } else {
                (*busy)++;
            }
            diag_progress_log(cnt, size, 500);
        }
        *usage_pec = (float)(((float)(100U * (*busy))) / ((float)size));
    }
    return res;
}

bool eeprom_init_common(const EepromConfig_t* const Config, EepromHandle_t* const Node) {
    bool res = false;
    if(Config) {
        res = eeprom_is_valid_config(Config);
#ifdef HAS_DEBUGGER
        ASSERT_CRITICAL(true == res);
#endif
        if(res) {
            res = false;
            if(Node) {
                Node->start = Config->start;
                Node->size = Config->size;
                Node->interrupt_on = Config->interrupt_on;

                Node->operation = EEPROM_OPERATION_NOPE;
                Node->input = EEPROM_INPUT_NONE;
                Node->state = EEPROM_STATE_IDLE;
                Node->wr_eeprom_addr = 0xFFFFFFFF;
                Node->start_ms = 0;
                Node->diff_ms = 0;
                Node->spin_cnt = 0;
                Node->wr_byte = 0xFF;
                Node->wr_word = 0xFFFF;
                Node->wr_qword = 0xFFFFFFFF;
                Node->loop = false;
                res = true;
            }
        }
    }
    return res;
}

bool eeprom_is_erased(uint32_t addr, uint32_t size) {
    bool res = false;
    res = is_arr_pat((uint8_t*)addr, size, 0xff);
    return res;
}

#ifdef HAS_EEPROM_WRITE
bool eeprom_dwords_zero(uint32_t address, uint32_t size) {
    bool res = false;
    LOG_WARNING(EEPROM, "Addr:0x%x Size:%u", address, size);
    uint32_t i = 0;
    uint32_t ok = 0;
    for(i = 0; i < size; i++) {
        uint8_t zero = 0;
        res = eeprom_mcal_write(address + i, &zero, 1);
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

/*
 Is there a continuously free block of given size starting at the address
 */
bool is_eeprom_spare(uint32_t address, uint32_t size) {
    uint32_t spare_size = 0;
    uint32_t busy_size = 0;
    bool res = false;
    float usage_pec = 0.0f;
    res = eeprom_scan((uint8_t*)address, size, &usage_pec, &spare_size, &busy_size);
    if(size == spare_size) {
        res = true;
    } else {
        res = false;
    }

    return res;
}

/*
 * find the first address of spare continuous block of given size
 * returns the start address
 * */
#ifdef HAS_EEPROM_EX
bool eeprom_find_spare_region(uint32_t* out_addr, uint32_t size) {
    uint32_t address = NOR_EEPROM_BASE;
    bool res = false;
    for(address = NOR_EEPROM_BASE; address < NOR_EEPROM_END; address++) {
        res = is_eeprom_spare(address, size);
        if(res) {
            *out_addr = address;
            break;
        }
    }
    return res;
}
#endif

#ifdef HAS_EEPROM_WRITE
_WEAK_FUN_ bool eeprom_mcal_erase(uint32_t addr, uint32_t size) {
    bool res = false;
    return res;
}
#endif

/* eeprom_read - busy name in Zephyr project
 * address - phy address
 * */
_WEAK_FUN_
bool eeprom_mcal_read(uint32_t address, uint8_t* const rx_array, uint32_t size) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(EEPROM, "Read,Addr:0x%08X,Size:%u", address, size);
#endif
    res = eeprom_is_address_range(address, size);
    if(res) {
        uint32_t i = 0;
        uint8_t* p_address = (uint8_t*)address;
        for(i = 0; i < size; i++) {
            rx_array[i] = *(p_address);
            p_address++;
        }
    }
    return res;
}

#ifdef HAS_EEPROM_WRITE

_WEAK_FUN_
bool eeprom_mcal_write(uint32_t eeprom_addr, uint8_t* data, uint32_t size) {
    bool res = false;
    return res;
}
#endif

bool eeprom_is_the_same(uint32_t addr_val, uint8_t* const array, uint32_t size) {
    bool res = false;
    int ret = 0;
    uint8_t* addr = (uint8_t*)addr_val;
    ret = memcmp((void*)addr, (void*)array, (uint32_t)size);
    if(0 == ret) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

int32_t eeprom_get_fragment_number(uint32_t in_addr, uint32_t fragment_size) {
    bool res = eeprom_is_address(in_addr);
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

_WEAK_FUN_
bool eeprom_mcal_init(void) {
    bool res = true;
    LOG_INFO(EEPROM, "Init");
    res = eeprom_is_valid_config(&EepromConfig);
    if(res) {
        res = eeprom_init_common(&EepromConfig, &EepromInstance);
    }
    return res;
}

bool eeprom_get_first_addr_spare_piece(const uint32_t size, uint32_t* const start_addr) {
    bool res = false;
    if(start_addr) {
        *start_addr = 0xFFFFFFFF;
        uint32_t a = EepromConfig.start;
        uint32_t end = EepromConfig.start + EepromConfig.size - size;
        for(a = EepromConfig.start; a < end; a++) {
            res = eeprom_is_erased(a, size);
            if(res) {
                res = true;
                break;
            }
        }

        if(res) {
            *start_addr = a;
        }
    }
    return res;
}

_WEAK_FUN_
bool eeprom_byte_write(const uint32_t phy_addr, const uint8_t byte) {
    bool res = false;
    LOG_DEBUG(EEPROM, "Write [0x%x]=0x%x", phy_addr, byte);
    res = eeprom_is_address_range(phy_addr, 1);
    if(res) {
        /*determine the address of the word in which the byte is located (dword_phy_addr) */
        uint32_t dword_phy_addr = phy_addr & (~MASK_2BIT); // clear the two least significant bits
        uint32_t byte_index = phy_addr & MASK_2BIT;        // select the two least significant bits
        Type32Union_t dWord = {0};
        dWord.u32 = 0;
        res = eeprom_dword_read(dword_phy_addr, &dWord.u32);
        if(res) {
            dWord.u8[byte_index] = byte;
            res = eeprom_dword_erase(dword_phy_addr);
            if(res) {
                res = eeprom_dword_write(dword_phy_addr, dWord.u32);
            }
        }
    }
    return res;
}

/*
   phy_addr = EEPROM physical address
*/
_WEAK_FUN_
bool eeprom_byte_erase(const uint32_t phy_addr) {
    bool res = false;
    LOG_DEBUG(EEPROM, "EraseByte[0x%x]", phy_addr);
    res = eeprom_byte_write(phy_addr, EEPROM_ERASE_PATTERN);
    return res;
}

_WEAK_FUN_
bool eeprom_bytes_erase(const uint32_t phy_addr, const uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    for(i = 0; i < size; i++) {
        res = eeprom_byte_erase(phy_addr + i);
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

_WEAK_FUN_
bool eeprom_bytes_write(const uint32_t phy_addr, const uint8_t* const data, const uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    /* print_hex(data,size); */
    for(i = 0; i < size; i++) {
        res = eeprom_byte_write(phy_addr + i, data[i]);
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

_WEAK_FUN_
bool eeprom_dword_read(const uint32_t phy_addr, uint32_t* const dword) {
    bool res = false;
    if(dword) {
        res = eeprom_is_address_range(phy_addr, 4);
        if(res) {
            *dword = read_addr_32bit(phy_addr);
        }
    }
    return res;
}

_WEAK_FUN_
bool eeprom_byte_read(const uint32_t phy_addr, uint8_t* const byte) {
    bool res = false;
    if(byte) {
        res = eeprom_is_address_range(phy_addr, 1);
        if(res) {
            *byte = read_addr_8bit(phy_addr);
            LOG_DEBUG(EEPROM, "Read[0x%x]=0x%x", phy_addr, *byte);
        }
    }
    return res;
}
