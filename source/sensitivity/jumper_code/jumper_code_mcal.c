#include "jumper_code_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "gpio_mcal.h"
#include "log.h"

COMPONENT_IS_VALID(JumperCode, jumper_code)
COMPONENT_GET_NODE(JumperCode, jumper_code)
COMPONENT_GET_CONFIG(JumperCode, jumper_code)

/*ISO-26262 require verify configuration*/
bool JumperCodeIsValidConfig(const JumperCodeConfig_t* const Config) {
    bool res = false;
    bool out_res = false;
    if(Config) {
        out_res = true;
        res = true;
        ifn(Config->name) {
            LOG_ERROR(JUMPER_CODE, "JUMPER_CODE_%u,Name,Err", Config->num);
            out_res = false;
        }

        ifn(Config->Position) {
            LOG_ERROR(JUMPER_CODE, "JUMPER_CODE_%u,Position,Err", Config->num);
            out_res = false;
        }

        ifn(Config->position_cnt) {
            LOG_ERROR(JUMPER_CODE, "JUMPER_CODE_%u,position_cnt,Err", Config->num);
            out_res = false;
        }

        if(Config->Position) {
            uint32_t i = 0;
            for (i = 0; i < Config->position_cnt; i++) {
                res = gpio_is_valid_pad(Config->Position[i].get);
                ifn(res) {
                    LOG_ERROR(JUMPER_CODE, "%u,GetGPIO,Pos[%u],Err", Config->num, i);
                    out_res = false;
                }

                res = gpio_is_valid_pad(Config->Position[i].set);
                ifn(res) {
                    LOG_ERROR(JUMPER_CODE, "%u,SetGPIO,Pos[%u],Err", Config->num, i);
                    out_res = false;
                }
            }
        }
    }
    return out_res;
}

bool jumper_code_init_custom(void) {
    bool res = false;
    LOG_INFO(JUMPER_CODE, "Version:%u", JUMPER_CODE_VERSION);
    return res;
}

bool jumper_code_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(JUMPER_CODE, "JUMPER_CODE_%u,Proc", num);
    JumperCodeHandle_t* Node = JumperCodeGetNode(num);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool jumper_code_init_common(const JumperCodeConfig_t* const Config, JumperCodeHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->Position = Config->Position;
            Node->position_cnt = Config->position_cnt;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool jumper_code_init_node(JumperCodeHandle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->code = 0xFFFFFFFF;
        Node->spin = 0;
        Node->valid = true;
        res = true;
    }
    return res;
}

uint32_t jumper_code_get(const uint8_t num) {
    uint32_t code = 0xFFFFFFFF;
    JumperCodeHandle_t *Node = JumperCodeGetNode(num);
    if(Node) {
        Node->code = 0;
        uint32_t i = 0;
        for (i = 0; i < Node->position_cnt; i++) {
            GpioLogicLevel_t logic_l = gpio_get_state_short(Node->Position[i].get);
            if(GPIO_LVL_HI == logic_l) {
                Node->code = Node->Position[i].code;
                code = Node->Position[i].code;
                break;
            }
        }
    }
    return code;
}

bool jumper_code_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(JUMPER_CODE, "JUMPER_CODE_%u", num);
    const JumperCodeConfig_t *Config = JumperCodeGetConfig(num);
    res = JumperCodeIsValidConfig(Config);
    if(res) {
#ifdef HAS_JUMPER_CODE_DIAG
        LOG_WARNING(JUMPER_CODE, "%s", JumperCodeConfigToStr(Config));
#endif
        JumperCodeHandle_t *Node = JumperCodeGetNode(num);
        if(Node) {
            res = jumper_code_init_common(Config, Node);
            res = jumper_code_init_node(Node);

            uint32_t i = 0;
            for (i = 0; i < Config->position_cnt; i++) {
                res = gpio_init_input(Config->Position[i].get, GPIO__PULL_DOWN);

                res = gpio_init_out(Config->Position[i].set);
                res = gpio_logic_level_set(Config->Position[i].set, GPIO_LVL_HI);
            }

            uint32_t code = jumper_code_get(num);
            LOG_INFO(JUMPER_CODE, "N:%u,Code:%u", num,code);

            Node->init = true;
        } else {
            LOG_ERROR(JUMPER_CODE, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(JUMPER_CODE, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(JUMPER_CODE, JUMPER_CODE, jumper_code)
COMPONENT_PROC_PATTERT(JUMPER_CODE, JUMPER_CODE, jumper_code)
