#include "bicycle_headlamp_mcal.h"

#include "ir_samsung_mcal.h"
#include "smooth_lamp.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "float_utils.h"

COMPONENT_GET_NODE(BicycleHeadLamp, bicycle_headlamp)
COMPONENT_GET_CONFIG(BicycleHeadLamp, bicycle_headlamp)

/*ISO-26262 require verify configuration*/

bool BicycleHeadLampIsValidConfig(const BicycleHeadLampConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(BICYCLE_HEADLAMP, "BICYCLE_HEADLAMP_%u,Name,Err", Config->num);
            res = false;
        }
    }
    return res;
}


bool bicycle_headlamp_init_custom(void) {
    bool res = false;
    LOG_INFO(BICYCLE_HEADLAMP, "Version:%u", BICYCLE_HEADLAMP_VERSION);
    return res;
}



static bool bicycle_headlamp_cmd_to_control(BicycleHeadLampHandle_t* const Node, const IrSamsungCmd_t cmd) {
    bool res = false;
    switch (cmd) {
        case IR_SAMSUNG_CMD_DOWN: {
            Node->limit_up  = Node->limit_up*0.9f;
            Node->limit_up = float_limiter_down_up(Node->limit_up, Node->limit_down, 100.0f);
            //Node->limit_up = float_limiter_down(Node->limit_up, 0.0f);
            res = smooth_lamp_limit_up(Node->smooth_lamp_num,    Node->limit_up) ;
        } break;

        case IR_SAMSUNG_CMD_UP: {
            Node->limit_up =  Node->limit_up*1.1f;
            Node->limit_up = float_limiter_up(Node->limit_up, 100.0f);
            res = smooth_lamp_limit_up(Node->smooth_lamp_num,    Node->limit_up) ;
        } break;

        case IR_SAMSUNG_CMD_EXIT: {
            res = smooth_lamp_ctrl(Node->smooth_lamp_num, false);
        } break;

        case IR_SAMSUNG_CMD_VOL_PLUS: {
            if(0.0<Node->limit_down ){
                Node->limit_down = Node->limit_down*1.1f;
            }else{
                Node->limit_down = 0.8;
            }
            res = smooth_lamp_limit_down(Node->smooth_lamp_num, Node->limit_down) ;
        } break;

        case IR_SAMSUNG_CMD_VOL_MINUS: {
            if(0.0<Node->limit_down){
                Node->limit_down = Node->limit_down*0.9f;
            }else{
                Node->limit_down = 0.8;
            }
            res = smooth_lamp_limit_down(Node->smooth_lamp_num, Node->limit_down) ;
        } break;

        case IR_SAMSUNG_CMD_POWER: {
            res = smooth_lamp_ctrl(Node->smooth_lamp_num, true);
        } break;

        case IR_SAMSUNG_CMD_PROG_NEXT: {
            //Node->mult += 0.05;
            //res = smooth_lamp_mult(1, Node->mult);
        } break;


        case IR_SAMSUNG_CMD_PROG_PREV: {
            //Node->mult -=0.05;
            //res=smooth_lamp_mult(1,   Node->mult);
        }break;

        case IR_SAMSUNG_CMD_SOURCE: {
        } break;
        case IR_SAMSUNG_CMD_SLEEP: {
        } break;

        case IR_SAMSUNG_CMD_1: {
            res = smooth_lamp_limit_up(Node->smooth_lamp_num, 10);
        } break;
        case IR_SAMSUNG_CMD_2: {
            res = smooth_lamp_limit_up(Node->smooth_lamp_num, 20);
        } break;
        case IR_SAMSUNG_CMD_3: {
            res = smooth_lamp_limit_up(Node->smooth_lamp_num, 30);
        } break;
        case IR_SAMSUNG_CMD_4: {
            res = smooth_lamp_limit_up(Node->smooth_lamp_num, 40);
        } break;
        case IR_SAMSUNG_CMD_5: {
            res = smooth_lamp_limit_up(Node->smooth_lamp_num, 50);
        } break;
        case IR_SAMSUNG_CMD_6: {
            res = smooth_lamp_limit_up(Node->smooth_lamp_num, 60);
        } break;
        case IR_SAMSUNG_CMD_7: {
            res = smooth_lamp_limit_up(Node->smooth_lamp_num, 70);
        }
            break;
        case IR_SAMSUNG_CMD_8: {
            res = smooth_lamp_limit_up(Node->smooth_lamp_num, 80);
        }
            break;
        case IR_SAMSUNG_CMD_9: {
        }
            break;
        case IR_SAMSUNG_CMD_MUTE: {
        }
            break;
        case IR_SAMSUNG_CMD_0: {
            res = smooth_lamp_limit_up(1, 0);
        }
            break;
        case IR_SAMSUNG_CMD_PIC_SIZE: {
        }
            break;
        case IR_SAMSUNG_CMD_STOP: {
        }
            break;
        case IR_SAMSUNG_CMD_RECORD: {
        }
            break;
        case IR_SAMSUNG_CMD_PLAY: {
        }
            break;
        case IR_SAMSUNG_CMD_PAUSE: {
        }
            break;
        case IR_SAMSUNG_CMD_AD_SUBT: {
        }
            break;
        case IR_SAMSUNG_CMD_RIGHT: {
        }
            break;
        case IR_SAMSUNG_CMD_LEFT: {
        }
            break;
        case IR_SAMSUNG_CMD_A: {
        }
            break;
        case IR_SAMSUNG_CMD_PRE_CH: {
        }
            break;
        case IR_SAMSUNG_CMD_B: {
        }
            break;
        case IR_SAMSUNG_CMD_C: {
        }
            break;
        case IR_SAMSUNG_CMD_D: {
        }
            break;
        case IR_SAMSUNG_CMD_MENU: {
        }
            break;
        case IR_SAMSUNG_CMD_GUIDE: {
        }
            break;
        case IR_SAMSUNG_CMD_INFO: {
        }
            break;
        case IR_SAMSUNG_CMD_TOOLS: {
        }
            break;
        case IR_SAMSUNG_CMD_RETURN: {
        }
            break;
        case IR_SAMSUNG_CMD_ENTER: {
        }
            break;
        case IR_SAMSUNG_CMD_MANUAL: {
        }
            break;
        case IR_SAMSUNG_CMD_EXTRA: {
        }
            break;
        case IR_SAMSUNG_CMD_PLAY_FORWARD: {
        }
            break;
        case IR_SAMSUNG_CMD_PLAY_BACK: {
        }
            break;
        case IR_SAMSUNG_CMD_SPORTS: {
        }
            break;
        case IR_SAMSUNG_CMD_SEARCH: {
        }
            break;
        case IR_SAMSUNG_CMD_PICTURE: {
        }
            break;
        case IR_SAMSUNG_CMD_TTX_MIX: {
        }
            break;
        case IR_SAMSUNG_CMD_CH_LIST: {
        }
            break;
        case IR_SAMSUNG_CMD_SMART_HUB: {
        }
            break;
        case IR_SAMSUNG_CMD_BACK_PLAY: {
        }
            break;
        case IR_SAMSUNG_CMD_TV_O: {
        }
            break;
        case IR_SAMSUNG_CMD_DASH_DASH_DASH: {
        }
            break;

        default: {
        }
            break;
    }
    return res;
}


bool bicycle_headlamp_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(BICYCLE_HEADLAMP, "BICYCLE_HEADLAMP_%u,Proc", num);
    BicycleHeadLampHandle_t* Node = BicycleHeadLampGetNode(num);
    if(Node) {
        Node->spin++;
        IrSamsungHandle_t* IrSamsung = IrSamsungGetNode(Node->ir_samsung_num);
        if(IrSamsung) {
            if(IrSamsung->unproc_cmd) {
                LOG_INFO(BICYCLE_HEADLAMP, "CMD:%s", IrSamsungCmdToKeyName(IrSamsung->cmd) );
                res = bicycle_headlamp_cmd_to_control(Node, IrSamsung->cmd);
                Node->cmd_start_ms = time_get_ms32();
                IrSamsung->cmd = IR_SAMSUNG_CMD_UNDEF;
                IrSamsung->unproc_cmd = false;
            }
        }
    }
    return res;
}

bool bicycle_headlamp_init_common(const BicycleHeadLampConfig_t* const Config,
                                  BicycleHeadLampHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->limit_down = Config->limit_down;
            Node->limit_up = Config->limit_up;
            Node->smooth_lamp_num = Config->smooth_lamp_num;
            Node->name = Config->name;
            Node->mult = Config->mult;
            Node->ir_samsung_num = Config->ir_samsung_num;
            res = true;
        }
    }
    return res;
}

bool bicycle_headlamp_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(BICYCLE_HEADLAMP, "BicycleHeadLamp_%u", num);
    const BicycleHeadLampConfig_t *Config = BicycleHeadLampGetConfig(num);
    res = BicycleHeadLampIsValidConfig(Config);
    if(res) {
#ifdef HAS_BICYCLE_HEADLAMP_DIAG
        LOG_WARNING(BICYCLE_HEADLAMP, "%s", BicycleHeadLampConfigToStr(Config));
#endif
        BicycleHeadLampHandle_t *Node = BicycleHeadLampGetNode(num);
        if(Node) {
            res = bicycle_headlamp_init_common(Config, Node);
            Node->valid = true;
            Node->init = true;
        } else {
            LOG_ERROR(BICYCLE_HEADLAMP, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(BICYCLE_HEADLAMP, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(BICYCLE_HEADLAMP, BICYCLE_HEADLAMP, bicycle_headlamp)
COMPONENT_PROC_PATTERT(BICYCLE_HEADLAMP, BICYCLE_HEADLAMP, bicycle_headlamp)
