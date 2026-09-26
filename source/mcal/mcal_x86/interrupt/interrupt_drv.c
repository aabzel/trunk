#include "interrupt_mcal.h"

#include <stdint.h>

#include "data_utils.h"
#include "microcontroller_drv.h"

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif


uint32_t interrupt_get_isr_handler(int16_t irq_n) {
    uint32_t handler_addr = 0xFFFFFFFF;
    return handler_addr;
}

bool interrupt_clear(void) {
    bool res = false;
    return res;
}

bool interrupt_mcal_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_WARNING(LG_INT, "IntInit");
#endif
    return res;
}

bool interrupt_is_active(int16_t irq_n) {
    bool res = true;
    return res;
}

bool interrupt_get_priority(int16_t irq_n, uint8_t* const preempt_priority, uint8_t* const sub_priority) {
    bool res = false;
    return res;
}

bool interrupt_set_priority(int16_t irq_n, uint8_t preempt_priority) {
    bool res = true;
    return res;
}

bool interrupt_enable(void) {
    bool res = true;
    return res;
}

bool interrupt_is_valid_irq_num(int16_t irq_n) {
    bool res = false;
    return res;
}

bool interrupt_disable(void) {
    bool res = true;
    return res;
}

bool interrupt_control(int16_t irq_n, bool on_off) {
    bool res = false;
    return res;
}
