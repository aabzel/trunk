#include "mic2026_drv.h"

#include "gpio_mcal.h"
#include "log.h"

Mic2026ChannelConfig_t* GetConfigRelyNode(Mic2026Channel_t ChanId) {
    Mic2026ChannelConfig_t* Config = NULL;
    uint8_t i = 0;
    for(i = 0; i < 2; i++) {
        if(Mic2026Config.Chan[i].ChanId == ChanId) {
            if(Mic2026Config.Chan[i].valid) {
                Config = &Mic2026Config.Chan[i];
                break;
            }
        }
    }
    return Config;
}

Mic2026ChannelVal_t* GetRelyNode(Mic2026Channel_t ChanId) {
    Mic2026ChannelVal_t* Node = NULL;
    uint8_t i = 0;
    for(i = 0; i < 2; i++) {
        if(Mic2026Item.ChanVal[i].ChanId == ChanId) {
            if(Mic2026Item.ChanVal[i].valid) {
                Node = &Mic2026Item.ChanVal[i];
                break;
            }
        }
    }
    return Node;
}

GpioLogicLevel_t mic2026_get_channel_ctrl(Mic2026Channel_t channel) {
    GpioLogicLevel_t out_ll = GPIO_LVL_UNDEF;
#ifdef HAS_MIC2026_DIAG
    LOG_DEBUG(MIC2026, "Get %s", Mic2026ChanToStr(channel));
#endif
    Mic2026ChannelConfig_t* Config = GetConfigRelyNode(channel);
    if(Config) {
        uint8_t pad_num = 0;
        pad_num = Config->CtrlPad.byte;
        bool res;
        res = gpio_get_state(pad_num, &out_ll);
        if(false == res) {
            out_ll = GPIO_LVL_UNDEF;
        }
    }

    return out_ll;
}

bool mic2026_set_channel_ctrl(Mic2026Channel_t channel, GpioLogicLevel_t logic_level) {
    bool res = false;
    uint8_t pad_num = 0;
#ifdef HAS_MIC2026_DIAG
    LOG_DEBUG(MIC2026, "Set %s %s", Mic2026ChanToStr(channel), GpioLevelToStr(logic_level));
#endif

    Mic2026ChannelConfig_t* Config = GetConfigRelyNode(channel);
    Mic2026ChannelVal_t* Node = GetRelyNode(channel);
    if(Config) {
        pad_num = Config->CtrlPad.byte;
        if(Node) {
            Node->CtrlPad.Set = logic_level;
            Node->CtrlPad.Real = GPIO_LVL_UNDEF;
            res = true;
        } else {
            LOG_ERROR(MIC2026, "NodeErr Chan %u", channel);
        }
    } else {
        LOG_ERROR(MIC2026, "ConfErr Chan %u", channel);
    }

    if(res) {
        res = gpio_logic_level_set(pad_num, logic_level);
#ifdef HAS_MIC2026_DIAG
        LOG_DEBUG(MIC2026, "SetOk %s %s", Mic2026ChanToStr(channel), GpioLevelToStr(logic_level));
#endif
    }
    return res;
}

bool mic2026_proc(void) {
    bool res = false;
    uint8_t channel = 0;
    for(channel = 1; channel <= 2; channel++) {
        Mic2026ChannelVal_t* RelyNode = GetRelyNode(channel);
        Mic2026ChannelConfig_t* ConfigNode = GetConfigRelyNode(channel);
        if(ConfigNode) {
            if(RelyNode) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(MIC2026, "NodeErr Chan %u", channel);
            }
        } else {
            res = false;
            LOG_ERROR(MIC2026, "ConfErr Chan %u", channel);
        }

        if(res) {
            res = gpio_get_state(ConfigNode->FbPad.byte, &RelyNode->FbPadVal);
            res = gpio_get_state(ConfigNode->CtrlPad.byte, &RelyNode->CtrlPad.Real);
            if(res) {
                if(RelyNode->CtrlPad.Real != RelyNode->CtrlPad.Set) {
                    LOG_ERROR(MIC2026, "SetDiff Chan:%u Set: %u Not Real %u", RelyNode->ChanId, RelyNode->CtrlPad.Set,
                              RelyNode->CtrlPad.Real);
                    res = gpio_logic_level_set(ConfigNode->CtrlPad.byte, RelyNode->CtrlPad.Set);
                }
            }
        }
    }

    return res;
}

static bool mic2026_init_one(Mic2026Channel_t channel) {
    bool res = false;
    LOG_INFO(MIC2026, "Init Channel %u..", channel);
    Mic2026ChannelVal_t* Node = GetRelyNode(channel);
    Mic2026ChannelConfig_t* ConfigNode = GetConfigRelyNode(channel);
    if(Node) {
        if(ConfigNode) {
            res = mic2026_set_channel_ctrl(channel, ConfigNode->CtrlDflt);
            Node->CtrlPad.Real = GPIO_LVL_UNDEF;
        }
    }
    return res;
}

bool mic2026_init(void) {
    bool res = false;
    LOG_INFO(MIC2026, "Init..");
    uint32_t cnt = 0;
    Mic2026Channel_t chan = 0;
    for(chan = CHANNEL_A; chan <= CHANNEL_B; chan++) {
        res = mic2026_init_one(chan);
        if(res) {
            cnt++;
        } else {
            LOG_ERROR(MIC2026, "Chan %u SetErr", chan);
        }
    }
    if(2 == cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
