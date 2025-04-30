#ifndef HEAP_DEBUGGER_H
#define HEAP_DEBUGGER_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h>

#include "std_includes.h"
#include "debugger_types.h"
#ifdef HAS_MCAL
#include "mcal_types.h"
#endif
#include "log.h"
#ifdef HAS_ALLOCATOR
#include "allocator_types.h"
#endif


#ifndef HAS_MICROCONTROLLER
#warning "That code only for MCU where all RAM memory is physical"
#endif

#ifndef HAS_DEBUGGER
#error "It is needed HAS_DEBUGGER option for that component"
#endif

#define ASSERT_CRITICAL(CONDITION)                                                                                     \
    do {                                                                                                               \
        if(0 == (CONDITION)) {                                                                                         \
            while(1) ;                                                                                                  \
                                                                                                                      \
        }                                                                                                              \
    } while(0);

#define ASSERT_DYNAMIC(CONDITION)                                                                                      \
    do {                                                                                                               \
        if(0 == (CONDITION)) {                                                                                         \
            LOG_ERROR(SYS, "DynAssert Line %u", __LINE__);                                                             \
        }                                                                                                              \
    } while(0);

#ifdef HAS_MCAL
bool debug_raw_reg_diag(facility_t facility, uint32_t base_address, const Reg32_t* const RegArray,
                        uint32_t reg_cnt );
#endif

uint32_t read_register(uint32_t address);

bool find_addr_by_val(uint16_t byte_num, uint32_t val, uint32_t start_addr, uint32_t end_addr);
#ifdef HAS_ALLOCATOR
bool h_count_link(void* addr, LinkCounter_t* LinkCounter);
#endif
uint8_t read_addr_8bit(uint32_t addr_val);
uint16_t read_addr_16bit(uint32_t addr_val);
uint32_t read_addr_32bit(register uint32_t addr_val);
uint64_t read_addr_64bit(uint32_t addr_val);

#ifdef HAS_WRITE_ADDR
bool write_addr_8bit(uint32_t in_addr, uint8_t addr_val);
bool write_addr_16bit(uint32_t in_addr, uint16_t addr_val);
bool write_addr_32bit(uint32_t in_addr, uint32_t addr_val);
#endif

#ifdef __cplusplus
}
#endif

#endif /* HEAP_DEBUGGER_H */
