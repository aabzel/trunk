#include "load_detect_drv.h"

#include <stdint.h>
#include <string.h>

#include "gpio_diag.h"
#include "gpio_drv.h"
#include "load_detect_diag.h"
#include "log.h"
#include "time_mcal.h"

LoadDetectHandle_t* LoadDetectGetNode(uint8_t num) {
    LoadDetectHandle_t* LdNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = load_detect_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == LoadDetectInstance[i].num) {
            if(LoadDetectInstance[i].valid) {
                LdNode = &LoadDetectInstance[i];
                break;
            }
        }
    }
    return LdNode;
}

const LoadDetectConfig_t* LoadDetectGetConfNode(uint8_t num) {
    const LoadDetectConfig_t* LDConfig = NULL;
    uint32_t i = 0;
    uint32_t cnt = load_detect_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == LoadDetectConfig[i].num) {
            if(LoadDetectConfig[i].valid) {
                LDConfig = &LoadDetectConfig[i];
                break;
            }
        }
    }
    return LDConfig;
}

const LoadDetectPinConfig_t* LoadDetectGetPinConfNode(uint8_t pin_num) {
    const LoadDetectPinConfig_t* PinConfig = NULL;
    uint32_t i = 0;
    uint32_t cnt = load_detect_get_pin_cnt();
    for(i = 0; i < cnt; i++) {
        if(pin_num == LoadDetectPinConfig[i].pin_num) {
            if(LoadDetectPinConfig[i].valid) {
                PinConfig = &LoadDetectPinConfig[i];
                break;
            }
        }
    }
    return PinConfig;
}

LoadDetectPinInfo_t* LoadDetectGetPinNode(uint8_t pin_num) {
    LoadDetectPinInfo_t* PinNode = NULL;
    uint32_t i = 0;
    uint32_t pin_cnt = load_detect_get_pin_cnt();
    for(i = 0; i < pin_cnt; i++) {
        if(pin_num == LoadDetectPinInstance[i].pin_num) {
            if(LoadDetectPinInstance[i].valid) {
                PinNode = &LoadDetectPinInstance[i];
                break;
            }
        }
    }
    return PinNode;
}

LoadDetectPinInfo_t* LoadDetectGetPinNodeByPad(Pad_t pad) {
    LoadDetectPinInfo_t* LoadDetectPinInfo = NULL;
    uint32_t i = 0;
    uint32_t cnt = load_detect_get_pin_cnt();
    for(i = 0; i < cnt; i++) {
        if(pad.byte == LoadDetectPinInstance[i].pad.byte) {
            if(LoadDetectPinInstance[i].valid) {
                LoadDetectPinInfo = &LoadDetectPinInstance[i];
                break;
            }
        }
    }
    return LoadDetectPinInfo;
}

bool load_detect_enable(uint8_t num, bool on_off) {
    bool res = false;
    LoadDetectHandle_t* Node = LoadDetectGetNode(num);
    if(Node) {
        Node->on_off = on_off;
        res = true;
    } else {
        LOG_ERROR(LOAD_DETECT, "NodeErr");
    }
    return res;
}

static bool load_detect_init_pin(const LoadDetectPinConfig_t* const PinConfig, LoadDetectPinInfo_t* const PinNode) {
    bool res = false;
    if(PinConfig) {
        if(PinNode) {
            uint32_t ok = 0;
            LOG_WARNING(LOAD_DETECT, "InitPad: %s In PullAir", GpioPad2Str(PinConfig->pad.byte));
            PinNode->num = PinConfig->num;
            PinNode->valid = PinConfig->valid;
            PinNode->pad = PinConfig->pad;
            PinNode->pin_num = PinConfig->pin_num;
            PinNode->on_off = true;

            PinNode->state = LOAD_DETECT_OUT_UNDEF;
            PinNode->prev_state = LOAD_DETECT_OUT_UNDEF;
            PinNode->llevel_at_pullair = GPIO_LVL_UNDEF;
            PinNode->llevel_at_pulldown = GPIO_LVL_UNDEF;
            PinNode->llevel_at_pullup = GPIO_LVL_UNDEF;

            res = gpio_set_dir(PinConfig->pad.byte, GPIO_DIR_IN);
            if(res) {
                ok++;
            } else {
                LOG_ERROR(LOAD_DETECT, "Pad: %s SetDirIn Err", GpioPad2Str(PinConfig->pad.byte));
            }

            res = gpio_set_pull(PinConfig->pad.byte, GPIO__PULL_AIR);
            if(res) {
                ok++;
            } else {
                LOG_ERROR(LOAD_DETECT, "Pad: %s SetPullAir Err", GpioPad2Str(PinConfig->pad.byte));
            }

#ifdef HAS_NRF5340
            res = gpio_set_pin_mcu(PinConfig->pad, NRF_GPIO_PIN_MUX_APP);
            if(res) {
                ok++;
            } else {
                LOG_ERROR(LOAD_DETECT, "Pad: %s SetAppCore Err", GpioPad2Str(PinConfig->pad.byte));
            }
#endif

            if(3 == ok) {
                res = true;
            } else {
                res = false;
            }
        }
    }

    return res;
}

bool load_detect_init_pins(uint8_t num) {
    bool res = false;
    uint32_t pin_cnt = load_detect_get_pin_cnt();
    LOG_WARNING(LOAD_DETECT, "LD%u Init %u Pins", num, pin_cnt);
    uint32_t i;
    uint32_t ok = 0;
    for(i = 0; i < pin_cnt; i++) {
        if(num == LoadDetectPinConfig[i].num) {
            res = load_detect_init_pin(&LoadDetectPinConfig[i], &LoadDetectPinInstance[i]);
            if(res) {
                ok++;
                LOG_DEBUG(LOAD_DETECT, "InitPin %s Ok", GpioPad2Str(LoadDetectPinInstance[i].pad.byte));
            } else {
                LOG_ERROR(LOAD_DETECT, "InitPinErr %d", num);
            }
        }
    }
    if(0 < ok) {
        res = true;
    }
    return res;
}

bool load_detect_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(LOAD_DETECT, "Init %d", num);
    const LoadDetectConfig_t* Config = LoadDetectGetConfNode(num);
    if(Config) {
        LoadDetectHandle_t* Node = LoadDetectGetNode(num);
        if(Node) {
            Node->gpio_class = Config->gpio_class;
            Node->init_done = true;
            Node->on_off = true;
            Node->valid = true;
            Node->state = GPIO__PULL_AIR;
            Node->spin_cnt = 0;
            res = load_detect_init_pins(num);
            if(res) {
                LOG_INFO(LOAD_DETECT, "%u InitPinsOk", num);
            } else {
                LOG_ERROR(LOAD_DETECT, "%u InitPinsErr", num);
            }
        } else {
            LOG_ERROR(LOAD_DETECT, "%u NodeErr", num);
        }
    } else {
        LOG_ERROR(LOAD_DETECT, "%u ConfErr", num);
    }
    return res;
}

bool load_detect_init(void) {
    bool res = false;
    set_log_level(LOAD_DETECT, LOG_LEVEL_DEBUG);
    uint32_t cnt = load_detect_get_cnt();
    uint32_t ok = 0;
    LOG_WARNING(LOAD_DETECT, "Init Cnt %d", cnt);

    uint32_t i = 0;
    for(i = 1; i <= cnt; i++) {
        res = load_detect_init_one(i);
        if(res) {
            ok++;
            LOG_INFO(LOAD_DETECT, "LD%u InitOk", i);
        } else {
            LOG_ERROR(LOAD_DETECT, "LD%u InitErr", i);
        }
    }

    if(ok) {
        res = true;
        LOG_INFO(LOAD_DETECT, "Init %u Ok", ok);
    } else {
        res = false;
        LOG_ERROR(LOAD_DETECT, "InitErr");
    }

    set_log_level(LOAD_DETECT, LOG_LEVEL_INFO);
    return res;
}

bool load_detect_enable_pad(uint8_t num, Pad_t pad, bool enable) {
    bool res = false;
    LoadDetectPinInfo_t* PinNode = LoadDetectGetPinNodeByPad(pad);
    if(PinNode) {
        PinNode->on_off = enable;
        res = true;
    }

    return res;
}

static bool load_detect_set_mcu_ll(LoadDetectHandle_t* Node, GpioPullMode_t pull_mode) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    uint32_t cnt = load_detect_get_pin_cnt();
    for(i = 1; i <= cnt; i++) {
        LoadDetectPinInfo_t* PinNode = LoadDetectGetPinNode(i);
        if(PinNode) {
            if(PinNode->num == Node->num) {
                res = gpio_set_pull(PinNode->pad.byte, pull_mode);
                if(res) {
                    ok++;
                }
            }
        }
    }

    res = (ok == cnt) ? true : false;

    return res;
}

static bool load_detect_pin_update(LoadDetectHandle_t* Node, LoadDetectPinInfo_t* PinNode,
                                   GpioLogicLevel_t logic_level) {
    bool res = false;
    LOG_DEBUG(LOAD_DETECT, "Update: %u %s %s %s", Node->num, GpioPad2Str(PinNode->pad.byte), GpioPull2Str(Node->state),
              GpioLevel2Str(logic_level));
    switch(Node->state) {
    case GPIO__PULL_AIR: {
        PinNode->llevel_at_pullair = logic_level;
        res = true;
    } break;
    case GPIO__PULL_DOWN: {
        PinNode->llevel_at_pulldown = logic_level;
        res = true;
    } break;
    case GPIO__PULL_UP: {
        PinNode->llevel_at_pullup = logic_level;
        res = true;
    } break;
    default:
        break;
    }
    return res;
}

static bool load_detect_measure_mcu_ll(LoadDetectHandle_t* Node) {
    bool res = false;
    LOG_DEBUG(LOAD_DETECT, "ProcMeasureMcu:%u", Node->num);
    uint32_t i = 0;
    uint32_t cnt = load_detect_get_pin_cnt();
    for(i = 1; i <= cnt; i++) {
        LoadDetectPinInfo_t* PinNode = LoadDetectGetPinNode(i);
        if(PinNode) {
            if(PinNode->num == Node->num) {
                GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
                res = gpio_get_state(PinNode->pad.byte, &logic_level);
                if(res) {
                    res = load_detect_pin_update(Node, PinNode, logic_level);
                }
            }
        }
    }

    return res;
}

static bool load_detect_set_pull_ll(LoadDetectHandle_t* Node, GpioPullMode_t pull_mode) {
    bool res = false;
    switch(Node->gpio_class) {
    case GPIO_CLASS_MCU:
        res = load_detect_set_mcu_ll(Node, pull_mode);
        break;
    case GPIO_CLASS_DW1000:
        res = false;
        break;
    case GPIO_CLASS_DW3000:
        res = false;
        break;
    default:
        LOG_ERROR(LOAD_DETECT, "UndefGPIO");
        break;
    }
    return res;
}

static bool load_detect_measure(LoadDetectHandle_t* Node) {
    bool res = false;
    LOG_DEBUG(LOAD_DETECT, "ProcMeasure:%u", Node->num);
    switch(Node->gpio_class) {
    case GPIO_CLASS_MCU:
        res = load_detect_measure_mcu_ll(Node);
        break;
    case GPIO_CLASS_DW1000:
        res = false;
        break;
    case GPIO_CLASS_DW3000:
        res = false;
        break;
    default:
        LOG_ERROR(LOAD_DETECT, "UndefGPIOclass");
        break;
    }
    return res;
}

static bool load_detect_calc_pin_solution(LoadDetectHandle_t* Node, LoadDetectPinInfo_t* PinNode) {
    bool res = false;
    if(Node) {
        LOG_DEBUG(LOAD_DETECT, "CalcSolution:%u", Node->num);
        if(PinNode) {
            if(PinNode->num == Node->num) {
                switch((uint8_t)PinNode->llevel_at_pullup) {
                case GPIO_LVL_LOW: {
                    PinNode->state = LOAD_DETECT_OUT_SHORT_GND;
                    res = true;
                } break;
                case GPIO_LVL_HI: {
                    res = true;

                } break;
                }

                switch((uint8_t)PinNode->llevel_at_pulldown) {
                case GPIO_LVL_LOW: {
                    res = true;
                } break;
                case GPIO_LVL_HI: {
                    PinNode->state = LOAD_DETECT_OUT_SHORT_VCC;
                    res = true;

                } break;
                }

                if(GPIO_LVL_LOW == PinNode->llevel_at_pulldown) {
                    if(GPIO_LVL_HI == PinNode->llevel_at_pullup) {
                        PinNode->state = LOAD_DETECT_OUT_OPEN;
                        res = true;
                    }
                }

                if(PinNode->prev_state != PinNode->state) {
                    LOG_WARNING(LOAD_DETECT, "Pad %s NewState %s->%s", GpioPad2Str(PinNode->pad.byte),
                                LoadDetectOut2Str(PinNode->prev_state), LoadDetectOut2Str(PinNode->state));
                }
                PinNode->prev_state = PinNode->state;
            }
        }
    }

    return res;
}

static bool load_detect_calc_solution(LoadDetectHandle_t* Node) {
    bool res = false;
    uint32_t pin_cnt = load_detect_get_pin_cnt();
    LOG_DEBUG(LOAD_DETECT, "CalcSolution:%u for %u pins", Node->num, pin_cnt);
    Node->spin_cnt++;
    uint32_t i = 0;
    uint32_t ok = 0;
    for(i = 0; i < pin_cnt; i++) {
        res = load_detect_calc_pin_solution(Node, &LoadDetectPinInstance[i]);
        if(res) {
            ok++;
        }
    }

    if(pin_cnt == ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

static bool load_detect_proc_air_ll(LoadDetectHandle_t* const Node) {
    bool res = false;
    LOG_DEBUG(LOAD_DETECT, "ProcAir:%u", Node->num);
    if(ONE_STATE_TIME_OUT_MS < Node->pause_ms) {
        /*TODO Measure all pins ll*/
        load_detect_measure(Node);
        Node->state = GPIO__PULL_DOWN;
        Node->time_start = time_get_ms32();
        LOG_DEBUG(LOAD_DETECT, "SwitchState");
        res = load_detect_set_pull_ll(Node, GPIO__PULL_DOWN);
    }

    return res;
}

static bool load_detect_proc_down_ll(LoadDetectHandle_t* Node) {
    bool res = false;
    LOG_DEBUG(LOAD_DETECT, "ProcDown:%u", Node->num);
    if(ONE_STATE_TIME_OUT_MS < Node->pause_ms) {
        load_detect_measure(Node);
        Node->state = GPIO__PULL_UP;
        Node->time_start = time_get_ms32();
        LOG_DEBUG(LOAD_DETECT, "SwitchState");
        res = load_detect_set_pull_ll(Node, GPIO__PULL_UP);
    }

    return res;
}

static bool load_detect_proc_up_ll(LoadDetectHandle_t* Node) {
    bool res = false;
    LOG_DEBUG(LOAD_DETECT, "ProcUp:%u", Node->num);
    if(ONE_STATE_TIME_OUT_MS < Node->pause_ms) {
        load_detect_measure(Node);
        Node->state = GPIO__PULL_AIR;
        Node->time_start = time_get_ms32();
        LOG_DEBUG(LOAD_DETECT, "PullState:Up->Air");
        res = load_detect_set_pull_ll(Node, GPIO__PULL_AIR);

        res = load_detect_calc_solution(Node);
    }

    return res;
}

/*UP->AIR->Down->Up*/
bool load_detect_proc_one(uint8_t num) {
    bool res = false;
    uint32_t up_time = time_get_ms32();
    LOG_DEBUG(LOAD_DETECT, "Proc:%u UpTime %u ms", num, up_time);
    LoadDetectHandle_t* Node = LoadDetectGetNode(num);
    if(Node) {
        if(Node->on_off) {
            Node->pause_ms = up_time - Node->time_start;
            LOG_DEBUG(LOAD_DETECT, "Proc Cnt:%u Pause %u ms", num, Node->pause_ms);
            switch(Node->state) {
            case GPIO__PULL_AIR:
                res = load_detect_proc_air_ll(Node);
                break;
            case GPIO__PULL_DOWN:
                res = load_detect_proc_down_ll(Node);
                break;
            case GPIO__PULL_UP:
                res = load_detect_proc_up_ll(Node);
                break;
            default:
                Node->state = GPIO__PULL_AIR;
                res = false;
                break;
            }
        }
    } else {
        LOG_ERROR(LOAD_DETECT, "NodeErr %u", num);
    }
    return res;
}

bool load_detect_proc(void) {
    bool res = false;
    uint8_t ok = 0;
    uint8_t cnt = load_detect_get_cnt();
    LOG_DEBUG(LOAD_DETECT, "Proc Cnt:%u", cnt);
    for(uint32_t i = 1; i <= cnt; i++) {
        res = load_detect_proc_one(i);
        if(res) {
            ok++;
        }
    }

    if(ok) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
