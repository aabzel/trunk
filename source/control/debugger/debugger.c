#include "debugger.h"

#include <stdio.h>
#include <string.h>

#include "board_config.h"
#include "std_includes.h"

#ifdef HAS_LOG
#include "debug_info.h"
#endif

#ifdef HAS_MCAL
#include "mcal_types.h"
#endif

#ifdef HAS_DIAG
#include "table_utils.h"
#include "writer_config.h"
#endif

#ifdef HAS_BIN_2_STR
#include "num_to_str.h"
#endif

#ifdef HAS_ALLOCATOR
#include "allocator_types.h"
#endif

#ifdef HAS_HEAP
#include "allocator_config.h"
#include "heap_allocator.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_MICROCONTROLLER
#include "sys_config.h"
#endif

#ifdef HAS_WRITE_ADDR
/*
 Works with RAM REG
 Will not work with ROM Flash
 * */
bool write_addr_32bit(uint32_t address, uint32_t value) {
    LOG_INFO(DBG, "WrireAddr[0x%08x]=0x%08x", address, value);
    bool res = true;
#ifdef CC26X2
    HWREG(address) = value;
#else  /*CC26X2*/
    volatile uint32_t* addr = NULL;
    addr = (volatile uint32_t*)address;
    (*addr) = value; /*May cause HardFault_Handler*/
#endif /*CC26X2*/
    return res;
}
bool write_addr_8bit(uint32_t address, uint8_t value) {
    LOG_DEBUG(DBG, "WrireAddr[0x%08x]=0x%02x", address, value);
    bool res = true;
    volatile uint8_t* addr = NULL;
    addr = (volatile uint8_t*)address;
    (*addr) = value; /*May cause HardFault_Handler*/
    return res;
}
bool write_addr_16bit(uint32_t address, uint16_t value) {
    LOG_DEBUG(DBG, "WrireAddr[0x%08x]=0x%04x", address, value);
    bool res = true;
    volatile uint16_t* addr = NULL;
    addr = (volatile uint16_t*)address;
    (*addr) = value; /*May cause HardFault_Handler*/
    return res;
}
#endif

uint8_t read_addr_8bit(uint32_t address) {
    uint8_t value = 0u;

    volatile uint8_t* p_addr = NULL;
    /*MISRA 2012 Rule 11.4: integer should not be converted to pointer */
    p_addr = (volatile uint8_t*)address;
    if(p_addr) {
        value = *p_addr;
    }
#ifdef HAS_LOG
    LOG_DEBUG(DBG, "Read[0x%08X]=0x%02X", address, value);
#endif
    return value;
}

uint16_t read_addr_16bit(uint32_t address) {
    uint16_t value = 0u;

    volatile uint16_t* p_addr = NULL;
    /*MISRA 2012 Rule 11.4: integer should not be converted to pointer */
    p_addr = (volatile uint16_t*)address;
    value = *p_addr;
#ifdef HAS_LOG
    LOG_DEBUG(DBG, "Read[0x%08X]=0x%04X", address, value);
#endif
    return value;
}

uint32_t read_addr_32bit(uint32_t address) {
    uint32_t value = 0u;
    volatile uint32_t* addr = NULL;
    /*MISRA 2012 Rule 11.4: integer should not be converted to pointer */
    addr = (volatile uint32_t*)address;
    value = *addr;
#ifdef HAS_LOG
    LOG_DEBUG(DBG, "Read[0x%08X]=0x%08X", address, value);
#endif
    return value;
}

uint32_t read_register(uint32_t address) {
    uint32_t value = 0;
    volatile uint32_t* addr = (volatile uint32_t*)address;
    value = *addr;
#ifdef HAS_BIN_2_STR
    // PrintReg32(value);
    // cli_printf("Address:*(0x%p):Value:0x%04x=%u=0b%s" CRLF, addr, value, value, utoa_bin32(value));
#endif
    return value;
}

uint64_t read_addr_64bit(uint32_t address) {
    uint64_t value = 0u;
    volatile uint64_t* addr = NULL;
    /*MISRA 2012 Rule 11.4: integer should not be converted to pointer */
    addr = (volatile uint64_t*)address;
    value = *addr;
    return value;
}

/*
 * byte_num - value size
 * val - seek value
 * */
bool find_addr_by_val(uint16_t byte_num, uint32_t val, uint32_t start_addr, uint32_t end_addr) {
    bool res = false;
#ifdef HAS_STREAM
    uint32_t cnt = 0;
    if(1 == byte_num) {
        uint8_t value = (uint8_t)val;
        uint8_t* ptr = (uint8_t*)start_addr;
        for(ptr = (uint8_t*)start_addr; ptr < ((uint8_t*)end_addr); ptr++) {
            if((*ptr) == value) {
                cli_printf("%u: address *(0x%p)= 0x%04x=%u" CRLF, cnt, ptr, value, value);
                res = true;
            }
        }
    }

    if(2 == byte_num) {
        uint16_t value = (uint16_t)val;
        uint16_t* ptr = (uint16_t*)start_addr;
        for(ptr = (uint16_t*)start_addr; ptr < ((uint16_t*)end_addr); ptr++) {
            if((*ptr) == value) {
#ifdef HAS_STREAM
                cli_printf("%u: addr *(0x%p)=0x%04x=%u" CRLF, cnt, ptr, value, value);
#endif
                res = true;
            }
        }
    }

    if(4 == byte_num) {
        uint32_t value = (uint32_t)val;
        uint32_t* ptr = (uint32_t*)start_addr;
        for(ptr = (uint32_t*)start_addr; ptr < ((uint32_t*)end_addr); ptr++) {
            if((*ptr) == value) {
#ifdef HAS_STREAM
                cli_printf("%u: addr *(0x%p)=0x%08x=%u" CRLF, cnt, ptr, value, value);
#endif
                res = true;
            }
        }
    }
#endif
    return res;
}

/*O(n)*/
#if defined(HAS_ALLOCATOR)
bool h_count_link(register void* addr, LinkCounter_t* LinkCounter) { // 1
    // uint32_t addr_val = (uint32_t ) addr;//1
    bool res = false;
#if defined(HAS_MICROCONTROLLER)
    // LOG_DEBUG(HEAP,"CountLinksForAddr: 0x%p",addr);
    if(LinkCounter) {
        LinkCounter->in_heap = 0;
        LinkCounter->out_heap = 0;
        res = true;
#ifdef HAS_MICROCONTROLLER
        res = is_ram_addr((uint32_t)addr); // 2
#endif
        if(res) {
            register uint8_t* ram_mem = NULL;
            for(ram_mem = (uint8_t*)RAM_START; ram_mem <= (uint8_t*)(RAM_END - sizeof(uint32_t)); ram_mem++) {
                uint32_t mem_value = read_addr_32bit((uint32_t)ram_mem);
                if(mem_value == (uint32_t)addr) { // 3
#ifdef HAS_HEAP
                    res = h_is_heap_addr((void*)ram_mem); // 4
                    if(res) {
                        LinkCounter->in_heap++;
                        // LOG_PARN(HEAP,"[0x%p]=0x%p in heap",mem, addr);
                    } else {
                        LinkCounter->out_heap++;
                        // LOG_PARN(HEAP,"[0x%p]=0x%p out heap",mem, addr);
                    }
#else
                    LinkCounter->out_heap++;
#endif /*HAS_HEAP*/
                }
            }
        }
        //    LOG_DEBUG(HEAP,"CountLinksForAddr: 0x%p i%u o%u",addr, LinkCounter->in_heap, LinkCounter->out_heap);
    }
#endif
    return res;
}

#endif

#if defined(HAS_DIAG) && defined(HAS_MCAL)
bool debug_raw_reg_diag(facility_t facility, uint32_t base_address, const Reg32_t* const RegArray, uint32_t reg_cnt) {
    bool res = false;
    if(RegArray) {

        LOG_INFO(facility, "Base:0x%08x,Cnt:%u", base_address, reg_cnt);
        static const table_col_t cols[] = {
            {5, "N"},       {20, "Name"}, {7, "offset"}, {6, "size"}, {12, "Addr"}, {12, "ValHex"},
#ifdef HAS_NUM_DIAG
            {43, "ValBin"},
#endif
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        int32_t offset_prev = 0;
        uint32_t r = 0;
        for(r = 0; r < reg_cnt; r++) {
            int32_t offset_diff = ((int32_t)RegArray[r].offset) - offset_prev;
            uint32_t addr_val = base_address + RegArray[r].offset;

            char temp[120] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, r + 1);
            snprintf(temp, sizeof(temp), "%s %18s " TSEP, temp, RegArray[r].name);
            snprintf(temp, sizeof(temp), "%s 0x%03x " TSEP, temp, RegArray[r].offset);
            snprintf(temp, sizeof(temp), "%s %4d " TSEP, temp, offset_diff);
            snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, addr_val);
            if(ACCESS_WRITE_ONLY == RegArray[r].access) {
                snprintf(temp, sizeof(temp), "%s %10s " TSEP, temp, "WO");
                snprintf(temp, sizeof(temp), "%s %41s " TSEP, temp, "WriteOnly");
            } else {
                uint32_t value = read_addr_32bit(addr_val);
                snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, value);
#ifdef HAS_BIN_2_STR
                snprintf(temp, sizeof(temp), "%s 0b%39s " TSEP, temp, utoa_bin32(value));
#endif
            }

            cli_printf("%s" CRLF, temp);
            offset_prev = (int32_t)RegArray[r].offset;
            res = true;
        }

        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}
#endif // HAS_DIAG

#ifdef HAS_WRITE_ADDR
static bool memmory_test_byte(const uint32_t address, const uint8_t pattern) {
    bool res = false;
    res = write_addr_8bit(address, pattern);
    uint8_t read = read_addr_8bit(address);
    if(read == pattern) {
        LOG_DEBUG(DBG, "Base:0x%08x,Pattern:0x%02x", address, pattern);
        res = true;
    } else {
        LOG_ERROR(DBG, "Base:0x%08x,Set:0x%02x,Get:0x%02x", address, pattern, read);
        res = false;
    }
    return res;
}

static bool memmory_test_byte_one(const uint32_t address) {
    bool res = false;
    res = memmory_test_byte(address, 0x55);
    if(res) {
        res = memmory_test_byte(address, 0xAA);
    }
    return res;
}

bool memmory_test(const uint32_t address, const uint32_t size) {
    bool res = false;
    LOG_INFO(DBG, "TestMemory,Base:0x%08x,Size:%u Byte", address, size);
    uint32_t run = 0;
    uint32_t end = address + size;
    for(run = address; run < end; run++) {
        uint8_t orig = read_addr_8bit(run);
        res = memmory_test_byte_one(run);
        if(res) {
            res = write_addr_8bit(run, orig);
        }

        if(!res) {
            LOG_ERROR(DBG, "Addr:0x%08x,Err", run);
            break;
        }
        diag_progress_log(run - address, size, 1000);
    }
    return res;
}
#endif
