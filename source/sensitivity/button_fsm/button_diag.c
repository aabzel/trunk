#include "button_diag.h"

#include <stdio.h>

#include "button_const.h"
#include "gpio_diag.h"
#include "log.h"

const char* ButtonState2Str(ButtonState_t state) {
    const char* name = "?";
    switch((uint8_t)state) {
    case BUTTON_STATE_UNPRESSED:
        name = "Relesed";
        break;
    case BUTTON_STATE_PRESSED:
        name = "Pressed";
        break;
    case BUTTON_STATE_PRESSED_PROCESSED:
        name = "Processed";
        break;
    default:
        name = "err";
        break;
    }
    return name;
}

const char* ButtonPressType2Str(ButtonPressType_t press_type) {
    const char* name = "?";
    switch((uint8_t)press_type) {
    case BUTTON_PRESS_SHORT:
        name = "Short";
        break;
    case BUTTON_PRESS_LONG:
        name = "Long";
        break;
    default:
        name = "err";
        break;
    }
    return name;
}

const char* ButtonInput2Str(ButtonInput_t input) {
    const char* name = "?";
    switch((uint8_t)input) {
    case BUTTON_IN_PASSIVE:
        name = "Passive";
        break;
    case BUTTON_IN_ACTIVE:
        name = "Active";
        break;
    case BUTTON_IN_TIME_OUT:
        name = "TimeOut";
        break;
    default:
        name = "err";
        break;
    }
    return name;
}

bool ButtonConfigDiag(const ButtonConfig_t* const Config) {
    bool res = false;
    if(Config) {
        char lText[120] = {0};
        sprintf(lText, "%s,LED%u,Active:%s", GpioPad2Str(Config->pad.byte), Config->debug_led_num,
                GpioLevel2Str(Config->active));
        LOG_WARNING(BUTTON, "%s", lText);
        res = true;
    }
    return res;
}
