#include "pin_mcal.h"

#include <stddef.h>

#include "compiler_const.h"
#include "std_includes.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_CLOCK
#include "clock.h"
#endif

#ifdef HAS_CLI
#include "convert.h"
#endif

#ifdef HAS_TIME

#include "time_mcal.h"
#endif

#ifdef HAS_PIN_DIAG
#include "pin_diag.h"
#endif

#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif /*HAS_SUPER_CYCLE*/

#include "board_config.h"
//#include "data_utils.h"

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#include "microcontroller.h"
#include "pin_config.h"
#include "sys_config.h"

#ifdef HAS_PIN_EXT
uint8_t get_mcu_pin(uint8_t pad) {
    uint8_t mcu_pin = 0;
#ifdef HAS_PINS
    uint8_t i = 0;
    for(i = 0; i < pin_get_cnt(); i++) {
        if(((uint8_t)PinConfig[i].pad.byte) == pad) {
            mcu_pin = PinConfig[i].mcu_pin;
            break;
        }
    }
#endif
    return mcu_pin;
}
#endif

#ifdef HAS_PIN_EXT
_WEAK_FUN_ bool pin_init_one(const PinConfig_t* const pinInstance) {
    bool res = false;
    /*Determine in Sep file*/
    return res;
}
#endif

bool pin_mcal_init(void) {
    bool res = false;
#ifdef HAS_PIN_DIAG
    LOG_WARNING(PIN, "Init");
#endif

#ifdef HAS_PIN_CUSTOM_INIT
    res = pin_init_custom();
#endif

    return res;
}

#ifdef HAS_PIN_EXT
const PinConfig_t* pin_get_config(Pad_t pad) {
    const PinConfig_t* ConfNode = NULL;
    uint32_t cnt = pin_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(pad.byte == PinConfig[i].pad.byte) {
            ConfNode = &PinConfig[i];
            break;
        }
    }
    return ConfNode;
}
#endif

#ifdef HAS_PIN_EXT
bool pin_is_pin_single(uint8_t byte) {
    bool res = false;
    uint32_t i = 0, pin_cnt = 0;
    uint32_t pin_real_cnt = 0;
    pin_cnt = pin_get_cnt();
    for(i = 0; i < pin_cnt; i++) {
        if(byte == PinConfig[i].pad.byte) {
            pin_real_cnt++;
        }
    }
    if(1 == pin_real_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif

bool mcu_get_prev_pin(PinData_t cur_pin, PinData_t* prev_pin) {
    bool res = false;
    return res;
}

bool mcu_get_next_pin(PinData_t cur_pin, PinData_t* next_pin) {
    bool res = false;
    return res;
}

bool mcu_get_up_pin(PinData_t cur_pin, PinData_t* const up_pin) {
    bool res = false;
    return res;
}

bool mcu_get_down_pin(PinData_t cur_pin, PinData_t* const down_pin) {
    bool res = false;
    return res;
}

bool mcu_get_right_pin(PinData_t cur_pin, PinData_t* const right_pin) {
    bool res = false;
    return res;
}

bool mcu_get_left_pin(PinData_t cur_pin, PinData_t* const left_pin) {
    bool res = false;
    return res;
}

uint16_t get_mcu_pin(uint8_t pad) {
    uint16_t mcu_pin = 0;
#ifdef HAS_PIN
    uint16_t i = 0;
    for(i = 0; i < pin_get_cnt(); i++) {
        if(((uint8_t)PinConfig[i].pad.byte) == pad) {
            mcu_pin = (uint16_t)PinConfig[i].mcu_pin;
            break;
        }
    }
#endif
    return mcu_pin;
}
