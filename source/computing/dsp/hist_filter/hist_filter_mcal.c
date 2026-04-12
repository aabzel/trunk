#include "hist_filter_mcal.h"

#include "code_generator.h"
#include "schmitt_trigger.h"
#include "log.h"

COMPONENT_GET_NODE(HistFilter, hist_filter)
COMPONENT_GET_CONFIG(HistFilter, hist_filter)

static uint8_t SchTrigStateToU8(const SchmittTriggerState_t state) {
    uint8_t val = 0;
    switch (state) {
        case SCHMITT_TRIGGER_STATE_UP:
            val = 1;
            break;
        case SCHMITT_TRIGGER_STATE_DOWN:
            val = 0;
            break;
        default:
            break;
    }
    return val;
}

/*
https://docs.google.com/spreadsheets/d/1dAsB0f5b-lm0g4HAjEvebUA9jxHLjEZ7dJht3QiOLoY/edit?gid=0#gid=0
 */
static const int32_t StateValLUT[16] = { 0, 1, -1, 2, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, 4, };

static int32_t hist_filter_state_to_out( HistFilterHandle_t* const Node) {
    int32_t out_sample = 0;
    Node->state.tgrigger0 = SchTrigStateToU8(Node->SchmittTrigger[0].state);
    Node->state.tgrigger1 = SchTrigStateToU8(Node->SchmittTrigger[1].state);
    Node->state.tgrigger2 = SchTrigStateToU8(Node->SchmittTrigger[2].state);
    Node->state.tgrigger3 = SchTrigStateToU8(Node->SchmittTrigger[3].state);
    Node->state.res = 0;
    LOG_PARN(HIST_FILTER, "Code:0x%x",Node->state.byte);
    out_sample = StateValLUT[Node->state.byte];
    return out_sample;
}

int32_t hist_filter_proc_sample(uint8_t num, const float in_sample) {
    int32_t out_sample = 0;
    HistFilterHandle_t *Node = HistFilterGetNode(num);
    if (Node) {
        uint32_t i = 0;
        for (i = 0; i < 4; i++) {
            schmitt_trigger_proc_val_ll(&Node->SchmittTrigger[i], in_sample);
        }
        out_sample = hist_filter_state_to_out(Node);
        LOG_DEBUG(HIST_FILTER, "HIST_FILTER_%u,in:%f,Out:%d",num ,in_sample,out_sample);
    }else{
        LOG_ERROR(HIST_FILTER, "HIST_FILTER_%u,Node,Err", num);
    }
    return out_sample;
}

/*ISO-26262 require verify configuration*/
bool HistFilterIsValidConfig(const HistFilterConfig_t* const Config) {
    bool res = false;
    if (Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(HIST_FILTER, "HIST_FILTER_%u,Name,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool hist_filter_init_custom(void) {
    bool res = false;
    LOG_INFO(HIST_FILTER, "Version:%s", HIST_FILTER_VERSION);
    return res;
}

bool hist_filter_init_common(const HistFilterConfig_t* const Config, HistFilterHandle_t* const Node) {
    bool res = false;
    if (Config) {
        if (Node) {
            Node->name = Config->name;
            uint32_t i = 0;
            for (i = 0; i < 4; i++) {
                schmitt_trigger_init_node(&Node->SchmittTrigger[i]);
                Node->SchmittTrigger[i].num = Config->SchmittTriggerShortConfig[i].num;
                Node->SchmittTrigger[i].down_val = Config->SchmittTriggerShortConfig[i].down_val;
                Node->SchmittTrigger[i].up_val = Config->SchmittTriggerShortConfig[i].up_val;
                Node->SchmittTrigger[i].hysteresis = Config->SchmittTriggerShortConfig[i].hysteresis;
                Node->SchmittTrigger[i].switching_value = Config->SchmittTriggerShortConfig[i].switching_value;
                res = true;
            }
        }
    }
    return res;
}

static bool hist_filter_init_node(HistFilterHandle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->spin = 0;
        Node->init = true;
        Node->state.byte = 0;
        uint32_t i = 0;
        for (i = 0; i < 4; i++) {
            schmitt_trigger_init_node(&Node->SchmittTrigger[i]);
            Node->SchmittTrigger[i].state = SCHMITT_TRIGGER_STATE_DOWN;
            Node->SchmittTrigger[i].prev_state = SCHMITT_TRIGGER_STATE_DOWN;
            Node->SchmittTrigger[i].init = true;
            Node->SchmittTrigger[i].up_handler_cnt = 0;
            Node->SchmittTrigger[i].down_handler_cnt = 0;
            Node->SchmittTrigger[i].value = 0;
        }
        res = true;
    }
    return res;
}

bool hist_filter_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(HIST_FILTER, "HIST_FILTER_%u", num);
    const HistFilterConfig_t *Config = HistFilterGetConfig(num);
    if (Config) {
        res = HistFilterIsValidConfig(Config);
        if (res) {
#ifdef HAS_HIST_FILTER_DIAG
            LOG_WARNING(HIST_FILTER, "%s", HistFilterConfigToStr(Config));
#endif
            HistFilterHandle_t *Node = HistFilterGetNode(num);
            if (Node) {
                res = hist_filter_init_node(Node);
                res = hist_filter_init_common(Config, Node);
                Node->valid = true;
                Node->init = true;
            } else {
                LOG_ERROR(HIST_FILTER, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(HIST_FILTER, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(HIST_FILTER, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(HIST_FILTER, HIST_FILTER, hist_filter)
