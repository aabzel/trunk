#ifndef CORE_GENERAL_DRV_H
#define CORE_GENERAL_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "core_types.h"
#include "core_config.h"

#ifdef HAS_CORE_DIAG
#include "core_diag.h"
#endif

#ifdef HAS_CORTEX_M4
#include "cortex_m4_driver.h"
#endif

#ifdef HAS_CORTEX_M7
#include "cortex_m7_driver.h"
#endif

#ifdef HAS_CORTEX_M33
#include "cortex_m33_driver.h"
#endif

#if defined(HAS_CORTEX_M4) && defined(HAS_CORTEX_M33)
#error "Core contradiction!"
#endif

#ifdef HAS_LOG
#define CORE_NAME .name="CORE",
#else
#define CORE_NAME
#endif


#define CORE_MCAL_INIT { .init_function=core_mcal_init, CORE_NAME},

//#define EXPECT_STACK_SIZE (2048)   // _Min_Stack_Size //(2048)

extern uint8_t* low_stack;

/*API*/
CoreHandle_t* CoreGetNode(uint8_t num);
const CoreConfig_t* CoreGetConfig(uint8_t num);
bool core_stack_monitor_proc(void);
bool core_mcal_init(void);
bool fpu_init(void);

/*getter*/
#ifdef HAS_CORE_EXT
bool arm_is_vector(const ArmCortexVectorTable_t* const Node) ;
#endif
bool arm_cortex_check_arm_vector_table(const uint32_t vector_table_addr);
bool is_ram_addr(uint32_t phy_address);
bool core_is_interrupt(void);
bool core_is_valid_isr_handler(int16_t irq_n);
bool core_check_address(volatile const char *address);
uint32_t core_isr_handler_addr_get(int16_t irq_n);
uint32_t cortex_offset_size_get(uint32_t const start);
#ifdef HAS_CORE_EXT
FloatFixPoint_t core_stack_used(const uint32_t top_stack_val, const uint32_t stack_size);
bool try_recursion(const uint32_t stack_top_addr, const uint32_t max_depth, uint32_t* const stack_size);
#endif

/*setters*/
bool core_reboot(void);

bool core_exeption(uint32_t in, uint32_t* out) ;
void sampling_timer_interrupt_handler(void);



#ifdef HAS_CHECK_STACK
float stack_used(void);
#endif


#ifdef __cplusplus
}
#endif

#endif /* CORE_GENERAL_DRV_H */
