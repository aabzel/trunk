#include "interrupt_mcal.h"

#include <stdbool.h>
#include <stddef.h>

#include "compiler_const.h"
#include "microcontroller_const.h"

const InterruptConfig_t* InterruptGetConfig(int16_t int_n) {
    InterruptConfig_t* Config = NULL;
    uint32_t cnt = interrupt_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(InterruptConfig[i].irq_n == int_n) {
            Config = &InterruptConfig[i];
            break;
        }
    }
    return Config;
}

_WEAK_FUN_ uint32_t interrupt_get_isr_handler(int16_t irq_n) { return 0; }

_WEAK_FUN_ bool interrupt_clear(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool interrupt_enable(void){
    bool res = false;
    return res;
}

#ifdef HAS_INTERRUPT_EXT
_WEAK_FUN_ bool interrupt_control_all(bool on_off) {
    bool res = false;
    if(on_off) {
        res = interrupt_enable();
    } else {
        res = interrupt_disable();
    }
    return res;
}
#endif

#ifdef HAS_INTERRUPT_EXT
_WEAK_FUN_ bool interrupt_is_active(int16_t irq_n) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_INTERRUPT_EXT
_WEAK_FUN_ bool interrupt_set_priority(int16_t irq_n, uint8_t preempt_priority) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_INTERRUPT_EXT
_WEAK_FUN_ bool interrupt_control(int16_t irq_n, bool on_off) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_INTERRUPT_EXT
_WEAK_FUN_ bool interrupt_get_priority(int16_t irq_n, uint8_t* const preempt_priority, uint8_t* const sub_priority) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_INTERRUPT_EXT
_WEAK_FUN_ bool interrupt_disable(void) {
    bool res = false;

    return res;
}
#endif

#ifdef HAS_INTERRUPT_EXT
bool interrupt_is_valid_irq_num(int16_t irq_n) {
    bool res = false;
    if(irq_n <= MAX_IRQ_NUM) {
        res = true;
    }
    return res;
}
#endif

static bool interrupt_init_one(const InterruptConfig_t* const Config) {
    bool res = true;
    if(Config) {
        res = interrupt_control(Config->irq_n, Config->on_off);
    }
    return res;
}

_WEAK_FUN_ bool interrupt_init_custom(void){
    bool res = true;
    return res;
}

_WEAK_FUN_ bool interrupt_mcal_init(void) {
    bool res = true;
    uint32_t i = 0;
    res = interrupt_init_custom();
    uint32_t cnt = interrupt_get_cnt();
    if(cnt) {
        for(i = 0; i < cnt; i++) {
            res = interrupt_init_one(&InterruptConfig[i]);
        }
    }
    interrupt_enable(); // hang on here
    return res;
}
