#include "interrupt_mcal.h"

#include <stdint.h>

//#include "c_defines_generated.h"
#include "core_driver.h"
#include "data_utils.h"
#include "debugger.h"
#include "microcontroller_drv.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

uint32_t interrupt_get_isr_handler(int16_t irq_n) {
    uint32_t handler_addr = core_isr_handler_addr_get(irq_n);
    return handler_addr;
}

bool interrupt_clear(void) {
    bool res = false;
    int32_t irq_n = 0;
    for(irq_n = 0; irq_n <= MAX_IRQ_NUM; irq_n++) {
        NVIC_ClearPendingIRQ((IRQn_Type)irq_n);
        res = true;
    }

    return res;
}

bool interrupt_mcal_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_WARNING(LG_INT, "IntInit");
#endif
    uint32_t cnt = 0;
    cnt = interrupt_get_cnt();
    ASSERT_CRITICAL(cnt);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
#ifdef HAS_CORE
        res = core_is_valid_isr_handler(InterruptConfig[i].irq_n);
        ASSERT_CRITICAL(res);
#endif
        NVIC_SetPriority(InterruptConfig[i].irq_n, InterruptConfig[i].priority);
        NVIC_EnableIRQ(InterruptConfig[i].irq_n);
#ifdef HAS_LOG
        // LOG_INFO(LG_INT, "INT[%s]On", InterruptConfig[i].name);
#endif
    }

    res = interrupt_clear();
    __enable_irq();
    return res;
}

bool interrupt_is_active(int16_t irq_n) {
    bool res = true;
    uint32_t status = NVIC_GetEnableIRQ((IRQn_Type)irq_n);
    res = (uint32_t)status;
    return res;
}

bool interrupt_get_priority(int16_t irq_n, uint8_t* const preempt_priority, uint8_t* const sub_priority) {
    bool res = false;
    uint32_t priority = NVIC_GetPriority((IRQn_Type)irq_n);
    *sub_priority = (uint8_t)priority;
    *preempt_priority = (uint8_t)priority;
    return res;
}

bool interrupt_set_priority(int16_t irq_n, uint8_t preempt_priority) {
    bool res = true;
    NVIC_SetPriority((IRQn_Type)irq_n, (uint32_t)preempt_priority);
    return res;
}

bool interrupt_enable(void) {
    bool res = true;
    __enable_irq();
    return res;
}

bool interrupt_is_valid_irq_num(int16_t irq_n) {
    bool res = false;
    if(irq_n <= CMU4_IRQn) {
        res = true;
    }
    return res;
}

bool interrupt_disable(void) {
    bool res = true;
    int32_t irq_n = 0;
    for(irq_n = 0; irq_n <= MAX_IRQ_NUM; irq_n++) {
        NVIC_DisableIRQ((IRQn_Type)irq_n);
    }
    __disable_irq();
    return res;
}

bool interrupt_control(int16_t irq_n, bool on_off) {
    bool res = false;
    if(on_off) {
        NVIC_EnableIRQ((IRQn_Type)irq_n);
        res = true;
    } else {
        NVIC_DisableIRQ((IRQn_Type)irq_n);
        res = true;
    }
    return res;
}
