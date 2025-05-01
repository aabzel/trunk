#include "core_driver.h"

#include "microcontroller_const.h"
#include "microcontroller_drv.h"

#ifdef HAS_LOG
#include "log.h"
#endif
#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_CORE_EXT
#include <string.h>

#ifdef HAS_ARRAY
#include "array.h"
#endif /*HAS_ARRAY*/

#endif

#ifdef HAS_BOOT
//#include "boot_config.h"
#endif

#ifdef HAS_FLASH
#include "flash_config.h"
#endif

#ifdef HAS_CORTEX_M33
#include "cortex_m33_driver.h"
#endif

#ifdef HAS_CORTEX_M4
#include "cortex_m4_driver.h"
#endif

#ifdef HAS_RISC_V
#include "rv32imc_driver.h"
#endif

#ifndef RAM_START
#error "Define MCU RAM_START"
#endif

#ifndef RAM_SIZE
#error "Define MCU RAM_SIZE configs"
#endif

uint8_t* low_stack = (uint8_t*)RAM_END;

/*TODO: Test it*/
#ifdef HAS_CORE_EXT
bool core_is_interrupt(void) {
    bool res = false;
#ifdef HAS_CORTEX_M4
    res = cortex_m4_is_interrupt();
#endif
    return res;
}
#endif

#ifdef HAS_CORE_EXT
void sampling_timer_interrupt_handler(void) {
    uint8_t* current_stack;
    int some_variable_on_stack = 0;
    current_stack = (uint8_t*)&some_variable_on_stack;
    if(current_stack < low_stack) {
        low_stack = current_stack;
    }
}
#endif

#ifdef HAS_CORE_EXT
bool is_ram_addr(register uint32_t address) {
    bool res = false;
    if((RAM_START <= address) && (address <= (RAM_START + RAM_SIZE))) {
        res = true;
    }

    return res;
}
#endif

#ifdef HAS_CORE_EXT
static bool call_recursion(uint32_t cur_depth, uint32_t max_depth, uint32_t* stack_size) {
    bool res = false;
    if(cur_depth < max_depth) {
        res = call_recursion(cur_depth + 1, max_depth, stack_size);
    } else if(cur_depth == max_depth) {
        uint32_t top_stack_val = *((uint32_t*)(APP_START_ADDRESS));
        uint32_t cur_stack_use = top_stack_val - ((uint32_t)&res);
        *stack_size = cur_stack_use;
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif

#ifdef HAS_CORE_EXT
bool try_recursion(uint32_t max_depth, uint32_t* stack_size) {
    bool res = false;
    res = call_recursion(0, max_depth, stack_size);
    return res;
}
#endif

#ifdef HAS_CHECK_STACK
float stack_used(void) {
    float precent = 0.0f;
    uint32_t busy = 0;
#ifdef HAS_GENERIC
    uint32_t top_stack_val = *((uint32_t*)(APP_START_ADDRESS));
#endif
#ifdef HAS_BOOTLOADER
    uint32_t top_stack_val = *((uint32_t*)0);
#endif

    uint32_t max_cont_patt = 0;
    bool res = array_max_cont((uint8_t*)top_stack_val - EXPECT_STACK_SIZE, EXPECT_STACK_SIZE, 0, &max_cont_patt);
    busy = EXPECT_STACK_SIZE - max_cont_patt;
    if(res) {
        precent = ((float)100 * busy) / ((float)EXPECT_STACK_SIZE);
    }

    return precent;
}
#endif

bool core_reboot(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(CORE, "ReBootNow!");
#endif

#ifdef HAS_TIME
    wait_ms(1000);
#endif

#ifdef HAS_CORTEX_M33
    res = cortex_m33_reboot();
#endif

#ifdef HAS_CORTEX_M4
    res = cortex_m4_reboot();
#endif

#ifdef HAS_RISC_V
    res = rv32imc_boot_addr(EXT_ROM_START);
#endif

    return res;
}

#ifdef HAS_CORE_EXT
bool core_exeption(uint32_t in, uint32_t* out) {
    bool res = false;
    if(out) {
        uint32_t temp = 0;
#ifdef HAS_LOG
        LOG_INFO(CORE, "TryEception:%u/0=?", in);
#endif
        // temp = in/0;
#ifdef HAS_LOG
        LOG_INFO(CORE, "Eception:%u/0=%u", in, temp);
#endif
        *out = temp;
        res = true;
    }
    return res;
}
#endif

/*        offset          Function
  .word   0               Reset_Handler
  .word   1         0     NMI_Handler
  .word   2         4     HardFault_Handler
  .word   3         8     MemManage_Handler
  .word   4         12    BusFault_Handler
  .word   5         16    UsageFault_Handler
  .word   6         20    0
  .word   7         24    0
  .word   8         28    0
  .word   9         32    0
  .word   10        36    SVC_Handler
  .word   11        40    DebugMon_Handler
  .word   12        44    0
  .word   13        48    PendSV_Handler
  .word   14        52    SysTick_Handler
  .word   15        60
 */

#ifdef HAS_CORE_EXT
// core_isr_handler_addr_get->core_isr_handler_addr_get
uint32_t core_isr_handler_addr_get(int16_t irq_n) {
    uint32_t isr_handler_addr = 0;
    (void)isr_handler_addr;
#ifdef HAS_CMSIS
    int32_t offset = 0;
    uint32_t vector_table_addr = 0;
    offset = ((int32_t)60) + ((int32_t)irq_n * 4);
    vector_table_addr += ((uint32_t)SCB->VTOR + 4);
    vector_table_addr += ((uint32_t)offset);
    isr_handler_addr = read_addr_32bit(vector_table_addr);
#ifdef HAS_LOG
    LOG_INFO(SYS, "IRQ:%d,Offset:%d,Addr:0x%08p=0x%08x", irq_n, offset, vector_table_addr, isr_handler_addr);
#endif
#endif // HAS_CMSIS

    return isr_handler_addr;
}
#endif

#ifdef HAS_CORE_EXT
bool core_is_valid_isr_handler(int16_t irq_n) {
    bool res = false;
    uint32_t isr_handler_addr = core_isr_handler_addr_get(irq_n);
    res = mcu_is_text_addr(isr_handler_addr);
    return res;
}
#endif

#ifdef HAS_FPU
bool fpu_init(void) {
    bool res = true;
    /* set CP10 and CP11 Full Access */
#ifdef HAS_CMSIS
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
#endif
    return res;
}
#endif

uint32_t core_get_up_time_ms(void) {
    static uint32_t up_time_ms = 0;
#ifdef HAS_RV32IMC_EXT
    up_time_ms = rv32imc_up_time_get_ms32();
#else
    up_time_ms++;
#endif
    return up_time_ms;
}
