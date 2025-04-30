#include "clock_divider.h"

#include <math.h>

#include "clock_divider_diag.h"
#include "code_generator.h"
#include "log.h"
#include "schmitt_trigger.h"

COMPONENT_GET_NODE(ClockDivider, clock_divider)
COMPONENT_GET_CONFIG(ClockDivider, clock_divider)

bool clock_divider_proc_period(uint8_t num) {
    bool res = false;
    ClockDividerHandle_t* Node = ClockDividerGetNode(num);
    if(Node) {
        Node->counter++;
        if(Node->divider < Node->counter) {
            Node->counter = 0;
            Node->cur_out = -Node->cur_out;
        }
        res = true;
    }
    return res;
}

bool clock_divider_divider_set(uint8_t num, uint32_t divider) {
    bool res = false;
    ClockDividerHandle_t* Node = ClockDividerGetNode(num);
    if(Node) {
        Node->divider = divider;
        res = true;
    }
    return res;
}

bool clock_divider_proc_one(uint8_t num, double in_val, double* out) {
    bool res = false;
    LOG_PARN(CLOCK_DIVIDER, "Proc:%u", num);
    ClockDividerHandle_t* Node = ClockDividerGetNode(num);
    if(Node) {
        LOG_DEBUG(CLOCK_DIVIDER, "%s", ClockDividerNodeToStr(Node));
        res = schmitt_trigger_proc_val(Node->schmitt_trigger_num, in_val);
        if(res) {
            *out = Node->cur_out;
        } else {
            LOG_ERROR(CLOCK_DIVIDER, "SCHMITT_TRIGGER_%u,Err", Node->schmitt_trigger_num);
        }
        Node->sample_cnt++;
    } else {
        LOG_ERROR(CLOCK_DIVIDER, "%u NodeErr", num);
    }
    return res;
}

bool clock_divider_init_custom(void) {
    bool res = true;
    log_level_get_set(CLOCK_DIVIDER, LOG_LEVEL_INFO);
    return res;
}

bool clock_divider_init_one(uint8_t num) {
    LOG_WARNING(CLOCK_DIVIDER, "INIT:%u", num);
    bool res = false;
    const ClockDividerConfig_t* Config = ClockDividerGetConfig(num);
    if(Config) {
        LOG_WARNING(CLOCK_DIVIDER, "%s", ClockDividerConfigToStr(Config));
        ClockDividerHandle_t* Node = ClockDividerGetNode(num);
        if(Node) {
            Node->amp = Config->amp;
            Node->divider = Config->divider;
            Node->schmitt_trigger_num = Config->schmitt_trigger_num;
            Node->sample_cnt = 0;
            Node->counter = 0;
            Node->valid = true;
            Node->cur_out = Node->amp;
            log_level_get_set(CLOCK_DIVIDER, LOG_LEVEL_INFO);
            res = true;
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(CLOCK_DIVIDER, CLOCK_DIVIDER, clock_divider)
