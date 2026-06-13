#include "smooth_lamp.h"

#include <math.h>

#include "code_generator.h"
#include "compiler_const.h"
#include "drv8870_mcal.h"
#include "pwm_mcal.h"
#include "pid.h"
#include "float_utils.h"
#include "log.h"

#ifdef HAS_DELTA_SIGMA
#include "delta_sigma.h"
#endif

#ifdef HAS_INCREMENTAL_ENCODER
#include "incremental_encoder_mcal.h"
#endif

#ifdef HAS_LED_MONO_PWM
#include "led_mono_pwm_mcal.h"
#endif

COMPONENT_GET_NODE(SmoothLamp, smooth_lamp)
COMPONENT_GET_CONFIG(SmoothLamp, smooth_lamp)

/*ISO-26262 require verify configuration*/
bool SmoothLampIsValidConfig(const SmoothLampConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(SMOOTH_LAMP, "SMOOTH_LAMP_%u,Name,Err", Config->num);
            res = false;
        }
        ifn(0 < Config->pwm_freq_hz) {
            LOG_ERROR(SMOOTH_LAMP, "SMOOTH_LAMP_%u,pwm_freq_hz,Err", Config->num);
            res = false;
        }
        ifn(0 < Config->sample_rate_hz) {
            LOG_ERROR(SMOOTH_LAMP, "SMOOTH_LAMP_%u,sample_rate_hz,Err", Config->num);
            res = false;
        }
        ifn(0 < Config->scale) {
            LOG_ERROR(SMOOTH_LAMP, "SMOOTH_LAMP_%u,scale,Err", Config->num);
            res = false;
        }
        ifn(Config->lamp_type) {
            LOG_ERROR(SMOOTH_LAMP, "SMOOTH_LAMP_%u,lamp_type,Err", Config->num);
            res = false;
        }
        ifn(Config->cmd) {
            LOG_ERROR(SMOOTH_LAMP, "SMOOTH_LAMP_%u,cmd,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool smooth_lamp_init_custom(void) {
    bool res = false;
    LOG_INFO(SMOOTH_LAMP, "Version:%u", SMOOTH_LAMP_VERSION);
    return res;
}

#if 0
static float smooth_lamp_cmd_to_singnal(const SmoothLampCmd_t cmd, float scale) {
    float singnal = 0.0;
    switch(cmd) {
    case SMOOTH_LAPM_CMD_OFF:
        singnal = 1.0f-scale;
        break;
    case SMOOTH_LAPM_CMD_ON:
        singnal = 1.0f+scale;
        break;
    default:
        singnal = 0.0;
        break;
    }
    return singnal;
}
#endif

#if 0
static SmoothLampCmd_t smooth_lamp_on_off_to_cmd(const bool on_off) {
    SmoothLampCmd_t cmd = SMOOTH_LAPM_CMD_OFF;
    switch(on_off) {
    case true: {
        cmd = SMOOTH_LAPM_CMD_ON;
    } break;
    case false: {
        cmd = SMOOTH_LAPM_CMD_OFF;
    } break;
    default:
        break;
    }
    return cmd;
}
#endif

bool smooth_lamp_deploy_ll(SmoothLampHandle_t* Node) {
    bool res = false;
#ifdef HAS_INCREMENTAL_ENCODER
  //  res = incremental_encoder_set_counter(1, Node->signal_out*16);
#endif
    switch(Node->lamp_type) {
        case SMOOTH_LAPM_TYPE_PWM: {
            res = pwm_duty_set(Node->type_num, Node->signal_out);
            res = pwm_ctrl(Node->type_num, true);

            res = delta_sigma_target_set(Node->delta_sigma_num, Node->signal_out);
        } break;

        case SMOOTH_LAPM_TYPE_LED: {
#ifdef HAS_LED_MONO_PWM
            res = led_mono_pwm_set_duty(Node->type_num, Node->signal_out);
#endif
        } break;

        case SMOOTH_LAPM_TYPE_DRV8870: {
            res = drv8870_set(Node->type_num, DRV8870_MODE_FORWARD, Node->signal_out);
        } break;
        default: break;
    }
    return res;
}

bool smooth_lamp_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    SmoothLampHandle_t* Node = SmoothLampGetNode(num);
    if (Node) {
        switch (on_off) {
            case true: {
                res = pid_target_set(Node->pid_num, Node->limit_up);
            } break;
            case false: {
                res = pid_target_set(Node->pid_num, Node->limit_down);
            } break;
            default: {
            } break;
        }
#if 0
        Node->start_up_time_us = time_get_us();
        SmoothLampCmd_t new_cmd =  smooth_lamp_on_off_to_cmd( on_off);
        if(new_cmd!= Node->cmd) {
            Node->cmd = new_cmd;
            uint64_t up_time_us = time_get_us();
            float up_tims_s = USEC_2_SEC(up_time_us);
        }
#endif
    }
    return res;
}

bool smooth_lamp_limit_down(uint8_t num, float limit_down) {
    bool res = false;
    SmoothLampHandle_t* Node = SmoothLampGetNode(num);
    if(Node) {
        Node->limit_down = limit_down;
        LOG_INFO(SMOOTH_LAMP,"SetDownLim:%f", Node->limit_down);
        res = true;
    }
    return res;
}

bool smooth_lamp_limit_up(uint8_t num, float limit_up) {
    bool res = false;
    SmoothLampHandle_t* Node = SmoothLampGetNode(num);
    if(Node) {
        LOG_INFO(SMOOTH_LAMP,"SetUpLim:%f %%",limit_up);
        Node->limit_up = limit_up;
        res = true;
    }
    return res;
}

bool  smooth_lamp_logistic_shift(uint8_t num,float logistic_shift_s){
    bool res = false;
    SmoothLampHandle_t* Node = SmoothLampGetNode(num);
    if(Node) {
        LOG_INFO(SMOOTH_LAMP,"SetLogisticShift:%f s",logistic_shift_s);
        Node->logistic_shift_s = logistic_shift_s;
        res = true;
    }
    return res;
}

bool smooth_lamp_mult(uint8_t num, float scale) {
    bool res = false;
    SmoothLampHandle_t* Node = SmoothLampGetNode(num);
    if(Node) {
        LOG_INFO(SMOOTH_LAMP,"SetScale:%f %%",scale);
        Node->scale = scale;
        res = true;
    }
    return res;
}

#if 0
static float calc_mult(float k, float signal_out) {
    float mult = k * signal_out;
    if(signal_out < 0.5) { //0.6.... 1.0
        mult = 0.005;
    } else if(60 < signal_out) {
        mult = 5.0;
    }else{
        mult = k * signal_out;
    }
    return mult;
}
#endif

float calc_decay1(SmoothLampHandle_t* Node){
    float up_tims_s = USEC_2_SEC(Node->up_time_us);
    float zero_offset_s = Node->scale/Node->limit_up;
    float signal_out = Node->scale / (up_tims_s+ zero_offset_s - Node->off_time_s);
    return signal_out ;
}

float calc_climax2(SmoothLampHandle_t* Node) {
    float up_tims_s = USEC_2_SEC(Node->up_time_us);
    float signal_out = Node->limit_up * (1.0f-expf(- Node->scale * (up_tims_s-Node->on_time_s))) ;
    return signal_out ;
}

float calc_decay2(SmoothLampHandle_t* Node) {
    float up_tims_s = USEC_2_SEC(Node->up_time_us);
    float signal_out = Node->limit_up * expf(- Node->scale * (up_tims_s-Node->off_time_s) );
    return signal_out ;
}

#if 0
static float calc_climax(SmoothLampHandle_t* Node, float on_time_s) {
    float up_tims_s = USEC_2_SEC(Node->up_time_us);
    float time1_s = up_tims_s- Node->logistic_shift_s;
    float signal_out = logistic_function(Node->limit_up,Node->scale, time1_s-on_time_s) + Node->limit_down ;
//  illumination_climax =    max_illum/ (1.0  + np.exp(-scale*time1_s))
    return signal_out ;
}
#endif

#if 0
static float calc_decay(SmoothLampHandle_t* Node, float off_time_s) {
    //float up_tims_s = USEC_2_SEC(Node->up_time_us);
    //float time1_s=up_tims_s-10.0/2.0f;
    float signal_out = Node->limit_up - calc_climax(Node, off_time_s) + Node->limit_down ;
    return signal_out ;
}
#endif

bool smooth_lamp_proc_one(uint8_t num) {
    bool res = false;
    SmoothLampHandle_t* Node = SmoothLampGetNode(num);
    if(Node) {
        PidHandle_t* Pid = PidGetNode(Node->pid_num);
        if(Pid){
#if 0
            float duty_effective=0.0f;
            pwm_duty_get(Node->type_num, &duty_effective);
            float error = Pid->target - duty_effective;
#endif
            float error = Pid->target - Pid->out;
            res = pid_proc_value_lll(Pid, error, &Node->signal_out);
            if(res) {
                Node->signal_out = float_limiter_down_up(Node->signal_out, Node->limit_down, Node->limit_up);
                res = smooth_lamp_deploy_ll(Node);
            }
        }

#if 0
        Node->up_time_us = time_get_us();
        uint32_t transient_diration_us =  Node->up_time_us- Node->start_up_time_us;
        float transient_diration_s = USEC_2_SEC(transient_diration_us);
#endif
#if 0
        if(transient_diration_s < (Node->logistic_shift_s*4.0f)) {

            //float up_tims_s = USEC_2_SEC(Node->up_time_us);
            LOG_DEBUG(SMOOTH_LAMP, "Proc,%s", SmoothLampNodeToStr(Node));
            Node->scale_real = smooth_lamp_cmd_to_singnal(Node->cmd,Node->scale );
            switch(Node->cmd) {
                case SMOOTH_LAPM_CMD_OFF: {
                    Node->signal_out = calc_decay(Node, Node->off_time_s);
                }break;
                case SMOOTH_LAPM_CMD_ON: {
                    Node->signal_out = calc_climax(Node, Node->on_time_s);
                }break;
                default: break;
            }

            //Node->signal_out = Node->signal_in * calc_mult(Node->mult, Node->signal_out) + Node->signal_out;
            //Node->signal_out = Node->scale_real  * Node->signal_out;
            Node->signal_out = float_limiter_down_up(Node->signal_out, Node->limit_down, Node->limit_up);
            res = smooth_lamp_deploy_ll(Node);
            res = is_float_equal_absolute(100.0, Node->signal_out, 0.00001);
            if (res) {
                if(0==Node->state ) {
                    LOG_NOTICE(SMOOTH_LAMP, "Top,%s", SmoothLampNodeToStr(Node));
                    Node->state = 1;
                }
            } else {
                Node->state = 0;
            }
        }

#endif
        log_level_t ll = log_level_get(SMOOTH_LAMP);
        if(LOG_LEVEL_DEBUG==ll) {
            cli_printf("\r%s",SmoothLampNodeToStr(Node));
        }
        Node->spin++;
    }
    return res;
}

bool smooth_lamp_init_common(const SmoothLampConfig_t* const Config, SmoothLampHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->pid_num = Config->pid_num;
            Node->name = Config->name;
            Node->sample_rate_hz = Config->sample_rate_hz;
            Node->pwm_freq_hz = Config->pwm_freq_hz;
            Node->limit_up = Config->limit_up;
            Node->limit_down = Config->limit_down;
            Node->type_num = Config->type_num;
            Node->scale = Config->scale;
            Node->lamp_type = Config->lamp_type;
            Node->logistic_shift_s = Config->logistic_shift_s;
            Node->delta_sigma_num = Config->delta_sigma_num;
            Node->cmd = Config->cmd;
            res = true;
        }
    }
    return res;
}

bool smooth_lamp_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SMOOTH_LAMP, "SMOOTH_LAMP_%u", num);
    const SmoothLampConfig_t* Config = SmoothLampGetConfig(num);
    if(Config) {
        res = SmoothLampIsValidConfig(Config);
        if(res) {
#ifdef HAS_SMOOTH_LAMP_DIAG
            LOG_WARNING(SMOOTH_LAMP, "%s", SmoothLampConfigToStr(Config));
#endif
            SmoothLampHandle_t* Node = SmoothLampGetNode(num);
            if(Node) {
                res = smooth_lamp_init_common(Config, Node);
                res = drv8870_freq_set(Config->type_num, Config->pwm_freq_hz);
                Node->cmd = SMOOTH_LAPM_CMD_UNDEF;
                //res = smooth_lamp_ctrl(num, false);
                Node->valid = true;
                Node->init = true;
                LOG_INFO(SMOOTH_LAMP, "InitOk,%u", num);
            } else {
                LOG_ERROR(SMOOTH_LAMP, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(SMOOTH_LAMP, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(SMOOTH_LAMP, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(SMOOTH_LAMP, SMOOTH_LAMP, smooth_lamp)
COMPONENT_PROC_PATTERT(SMOOTH_LAMP, SMOOTH_LAMP, smooth_lamp)
