#include "input_capture_mcal.h"

#include <string.h>

#include "code_generator.h"
#include "common_diag.h"
#include "input_capture_config.h"
#include "log.h"
#include "timer_mcal.h"

COMPONENT_GET_NODE(InputCapture, input_capture)

COMPONENT_GET_CONFIG(InputCapture, input_capture)

InputCaptureMode_t InputCaptureOnOffToMode(bool on_off) {
    InputCaptureMode_t mode = INPUT_CAPTURE_MODE_OFF;
    switch((uint8_t)on_off) {
    case true:
        mode = INPUT_CAPTURE_MODE_ON;
        break;
    case false:
        mode = INPUT_CAPTURE_MODE_OFF;
        break;
    default:
        mode = INPUT_CAPTURE_MODE_OFF;
        break;
    }
    return mode;
}

bool input_capture_is_valid_duty_cycle(double duty_cycle) {
    bool res = false;
    if(0.0 <= duty_cycle) {
        if(duty_cycle <= 100.0) {
            res = true;
        }
    }
    return res;
}

bool input_capture_init_cache(const InputCaptureConfig_t* const Config, InputCaptureHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->channel = Config->channel;
            Node->divider = Config->divider;
            Node->direction = Config->direction;
            Node->interrupt_on = Config->interrupt_on;
            Node->on = Config->on;
            Node->polarity = Config->polarity;
            Node->Pad = Config->Pad;
            Node->timer_num = Config->timer_num;
            res = true;
        }
    }
    return res;
}

bool input_capture_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    InputCaptureHandle_t* Node = InputCaptureGetNode(num);
    if(Node) {
        res = input_capture_ctrl_ll(Node, on_off);
    }

    return res;
}

__attribute__((weak)) bool input_capture_init_one(uint8_t num) {
    bool res = true;
    LOG_ERROR(INPUT_CAPTURE, "[%s]NotImplemented", __FUNCTION__);
    return res;
}

__attribute__((weak)) bool input_capture_init_custom(void) {
    bool res = false;
    LOG_ERROR(INPUT_CAPTURE, "[%s]NotImplemented", __FUNCTION__);
    return res;
}

__attribute__((weak)) bool input_capture_pad_get(uint8_t num, Pad_t* const pad) {
    bool res = false;
    LOG_ERROR(INPUT_CAPTURE, "[%s]NotImplemented", __FUNCTION__);
    return res;
}

__attribute__((weak)) bool input_capture_ctrl_ll(InputCaptureHandle_t* Node, bool on_off) {
    bool res = false;
    LOG_WARNING(INPUT_CAPTURE, "INPUT_CAPTURE%u,%s", Node->num, OnOffToStr(on_off));
    if(Node) {
        res = timer_channel_ctrl(Node->timer_num, (TimerCapComChannel_t)Node->channel, on_off);
        if(res) {
            LOG_PARN(INPUT_CAPTURE, "TIMER%u,%s,CtrlOk", Node->timer_num, OnOffToStr(on_off));
        } else {
            LOG_WARNING(INPUT_CAPTURE, "TIMER%u CtrlErr", Node->timer_num);
            res = false;
        }
    }

    return res;
}

COMPONENT_INIT_PATTERT(INPUT_CAPTURE, INPUT_CAPTURE, input_capture)
