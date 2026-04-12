#include "input_capture_mcal.h"

#include <stdbool.h>
#include <stdint.h>

#include "at32_misc.h"
#include "common_diag.h"
#include "data_utils.h"
#include "input_capture_config.h"
#include "input_capture_custom_types.h"
#include "log.h"
#include "microcontroller_const.h"
#include "timer_mcal.h"

bool input_capture_is_valid_channel(InputCaptureChannel_t channel) {
    bool res = false;
    if(INPUT_CAPTURE_CHANNEL_0 <= channel) {
        if(channel <= INPUT_CAPTURE_CHANNEL_5) {
            res = true;
        }
    }
    return res;
}

bool input_capture_start(uint8_t num) {
    bool res = false;
    InputCaptureHandle_t* Node = InputCaptureGetNode(num);
    if(Node) {
        res = timer_ctrl(Node->timer_num, true);
    }
    return res;
}

bool input_capture_stop(uint8_t num) {
    bool res = false;
    InputCaptureHandle_t* Node = InputCaptureGetNode(num);
    if(Node) {
        res = timer_ctrl(Node->timer_num, false);
    }
    return res;
}

bool input_capture_init_custom(void) {
    bool res = true;
    log_level_get_set(INPUT_CAPTURE, LOG_LEVEL_INFO);
    return res;
}

static tmr_channel_input_divider_type InputCaptureDividerToArtery(uint8_t divider) {
    tmr_channel_input_divider_type divider_factor = TMR_CHANNEL_INPUT_DIV_1;
    switch(divider) {
    case 1:
        divider_factor = TMR_CHANNEL_INPUT_DIV_1;
        break;
    case 2:
        divider_factor = TMR_CHANNEL_INPUT_DIV_2;
        break;
    case 4:
        divider_factor = TMR_CHANNEL_INPUT_DIV_4;
        break;
    case 8:
        divider_factor = TMR_CHANNEL_INPUT_DIV_8;
        break;
    default:
        divider_factor = TMR_CHANNEL_INPUT_DIV_1;
        break;
    }
    return divider_factor;
}

static sub_tmr_input_sel_type InputCaptureChannelToTrigger(InputCaptureChannel_t channel) {
    sub_tmr_input_sel_type input_sel = TMR_SUB_INPUT_SEL_IS0;
    switch((uint32_t)channel) {
    case INPUT_CAPTURE_CHANNEL_1:
        input_sel = TMR_SUB_INPUT_SEL_C1DF1;
        break;
    case INPUT_CAPTURE_CHANNEL_2:
        input_sel = TMR_SUB_INPUT_SEL_C2DF2;
        break;
    // case INPUT_CAPTURE_CHANNEL_3: input_sel=TMR_SUB_INPUT_SEL_IS2; break;
    // case INPUT_CAPTURE_CHANNEL_4: input_sel=TMR_SUB_INPUT_SEL_IS3; break;
    default:
        LOG_ERROR(INPUT_CAPTURE, "UndefChannel");
        break;
    }
    return input_sel;
}

static uint32_t InputCaptureChannelToInt(InputCaptureChannel_t channel) {
    uint32_t tmr_interrupt = TMR_C1_INT;
    switch((uint32_t)channel) {
    case INPUT_CAPTURE_CHANNEL_1:
        tmr_interrupt = TMR_C1_INT;
        break;
    case INPUT_CAPTURE_CHANNEL_2:
        tmr_interrupt = TMR_C2_INT;
        break;
    case INPUT_CAPTURE_CHANNEL_3:
        tmr_interrupt = TMR_C3_INT;
        break;
    case INPUT_CAPTURE_CHANNEL_4:
        tmr_interrupt = TMR_C4_INT;
        break;

    default:
        LOG_ERROR(INPUT_CAPTURE, "UndefChannel");
        break;
    }
    return tmr_interrupt;
}

static tmr_channel_select_type InputCaptureChannelToArtery(InputCaptureChannel_t channel) {
    tmr_channel_select_type input_channel_select = TMR_SELECT_CHANNEL_1;
    switch((uint32_t)channel) {
    case INPUT_CAPTURE_CHANNEL_1:
        input_channel_select = TMR_SELECT_CHANNEL_1;
        break;
    case INPUT_CAPTURE_CHANNEL_2:
        input_channel_select = TMR_SELECT_CHANNEL_2;
        break;
    case INPUT_CAPTURE_CHANNEL_3:
        input_channel_select = TMR_SELECT_CHANNEL_3;
        break;
    case INPUT_CAPTURE_CHANNEL_4:
        input_channel_select = TMR_SELECT_CHANNEL_4;
        break;
    case INPUT_CAPTURE_CHANNEL_5:
        input_channel_select = TMR_SELECT_CHANNEL_5;
        break;
    default:
        LOG_ERROR(INPUT_CAPTURE, "UndefChannel");
        break;
    }
    return input_channel_select;
}

static tmr_input_polarity_type InputCapturePolarityToArtery(InputCapturePolarity_t polarity) {
    tmr_input_polarity_type code_pol = TMR_SELECT_CHANNEL_1;
    switch((uint32_t)polarity) {
    case INPUT_CAPTURE_EDGE_FALING:
        code_pol = TMR_INPUT_FALLING_EDGE;
        break;
    case INPUT_CAPTURE_EDGE_RISING:
        code_pol = TMR_INPUT_RISING_EDGE;
        break;
    case INPUT_CAPTURE_EDGE_BOTH:
        code_pol = TMR_INPUT_BOTH_EDGE;
        break;
    default:
        LOG_ERROR(INPUT_CAPTURE, "UndefPolarity");
        break;
    }
    return code_pol;
}

static tmr_count_mode_type InputCaptureDirectionToArtery(InputCaptureCountDirection_t direction) {
    tmr_count_mode_type dir_code = TMR_SELECT_CHANNEL_1;
    switch((uint32_t)direction) {
    case INPUT_CAPTURE_CNT_DIRR_DOWN:
        dir_code = TMR_COUNT_DOWN;
        break;
    case INPUT_CAPTURE_CNT_DIRR_UP:
        dir_code = TMR_COUNT_UP;
        break;

    default:
        LOG_ERROR(INPUT_CAPTURE, "UndefDir");
        break;
    }
    return dir_code;
}

bool input_capture_reset(uint8_t num) {
    bool res = false;
    LOG_WARNING(INPUT_CAPTURE, "IC:%u,Reset", num);
    InputCaptureHandle_t* Node = InputCaptureGetNode(num);
    if(Node) {
        res = timer_counter_set(Node->timer_num, 0);
    }
    return res;
}

bool input_capture_counter_get(uint8_t num, uint32_t* const counter) {
    bool res = false;
    InputCaptureHandle_t* Node = InputCaptureGetNode(num);
    if(Node) {
        *counter = timer_counter_get(Node->timer_num);
        res = true;
    }
    return res;
}

// 14.2 General-purpose timer (TMR2 to TMR5)
#define TIMER_PRESCALER 0
bool input_capture_init_one(uint8_t num) {
    bool res = false;
    const InputCaptureConfig_t* Config = InputCaptureGetConfig(num);
    if(Config) {
        LOG_WARNING(INPUT_CAPTURE, "Init:%u,%s", num, InputCaptureConfigToStr(Config));
        InputCaptureHandle_t* Node = InputCaptureGetNode(num);
        if(Node) {
            res = input_capture_init_cache(Config, Node);
            TimerInfo_t* TimerInfo = TimerGetInfo(Config->timer_num);
            if(TimerInfo) {
                LOG_INFO(INPUT_CAPTURE, "%s", TimerInfoToStr(TimerInfo));

                crm_periph_clock_enable(TimerInfo->clock_type, TRUE);

                uint32_t max_val = (uint32_t)(ipow(2, (uint32_t)TimerInfo->resolution_bit) - 1);
                tmr_base_init(TimerInfo->TMRx, max_val, TIMER_PRESCALER);

                tmr_count_mode_type tmr_cnt_dir;
                tmr_cnt_dir = InputCaptureDirectionToArtery(Config->direction);
                tmr_cnt_dir_set(TimerInfo->TMRx, tmr_cnt_dir);

                tmr_channel_value_set(TimerInfo->TMRx, TMR_SELECT_CHANNEL_2, 5);

                tmr_input_config_type TmrInputConfigStruct = {0};

                /* input channel select */
                TmrInputConfigStruct.input_channel_select = InputCaptureChannelToArtery(Config->channel);
                /* input polarity select */
                TmrInputConfigStruct.input_polarity_select = InputCapturePolarityToArtery(Config->polarity);
                /* channel mapped direct or indirect */
                TmrInputConfigStruct.input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
                TmrInputConfigStruct.input_filter_value = 0;

                tmr_channel_input_divider_type divider_factor = TMR_CHANNEL_INPUT_DIV_1;
                divider_factor = InputCaptureDividerToArtery(Config->divider);
                tmr_input_channel_init(TimerInfo->TMRx, &TmrInputConfigStruct, divider_factor);

                if(Config->interrupt_on) {
                    uint32_t tmr_interrupt = InputCaptureChannelToInt(Config->channel);
                    tmr_interrupt_enable(TimerInfo->TMRx, tmr_interrupt, TRUE);
                    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
                    nvic_irq_enable(TimerInfo->irq_n, 2, 2);
                }

                // input channel just stops cnt incresing
                sub_tmr_input_sel_type trigger_select = TMR_SUB_INPUT_SEL_C2DF2;
                trigger_select = InputCaptureChannelToTrigger(Config->channel);
                tmr_trigger_input_select(TimerInfo->TMRx, trigger_select);

                /* select the slave mode: external mode a*/
                tmr_sub_mode_select_type sub_mode = TMR_SUB_EXTERNAL_CLOCK_MODE_A;
                tmr_sub_mode_select(TimerInfo->TMRx, sub_mode);

                tmr_counter_enable(TimerInfo->TMRx, OnOffToConfirmState(Config->on));

                res = input_capture_reset(num);
            }

            res = true;
        }
    }
    return res;
}

bool input_capture_pad_get(uint8_t num, Pad_t* const pad) {
    bool res = false;
    InputCaptureHandle_t* Node = InputCaptureGetNode(num);
    if(Node) {
    }
    return res;
}
