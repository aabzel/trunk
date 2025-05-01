#ifndef CORE_GENERAL_DRV_H
#define CORE_GENERAL_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_CORTEX_M4
#include "cortex_m4_driver.h"
#endif

#ifdef HAS_CORTEX_M33
#include "cortex_m33_driver.h"
#endif

#if defined(HAS_CORTEX_M4) && defined(HAS_CORTEX_M33)
#error "Core contradiction!"
#endif

#define EXPECT_STACK_SIZE (2048)   // _Min_Stack_Size //(2048)

extern uint8_t* low_stack;

bool fpu_init(void);
uint32_t core_isr_handler_addr_get(int16_t irq_n);
uint32_t core_get_up_time_ms(void);
bool core_exeption(uint32_t in, uint32_t* out) ;
bool core_is_interrupt(void);
bool core_is_valid_isr_handler(int16_t irq_n);
bool is_ram_addr(register uint32_t address);
bool core_reboot(void);


#ifdef HAS_CORE_EXT
bool try_recursion(uint32_t max_depth, uint32_t* stack_size);
#endif

#ifdef HAS_CHECK_STACK
float stack_used(void);
#endif

void sampling_timer_interrupt_handler(void);

#ifdef __cplusplus
}
#endif

#endif /* CORE_GENERAL_DRV_H */
