#include "scan.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "code_generator.h"
#include "data_utils.h"
#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif
#include "log.h"
#include "scan_config.h"
#include "scan_diag.h"
#include "sys_config.h"

COMPONENT_GET_NODE(Scan, scan)

COMPONENT_GET_CONFIG(Scan, scan)


static bool ScanIsValidConfig(const ScanConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(res){
            if(1 < Config->sample_freq_hz){
                res = true;
            }else{
                res = false;
            }
        }
        if(res){
            if(0.0 < Config->threshold){
                res = true;
            }else{
                res = false;
            }
        }

        if(res){
            if(0.0 < Config->timeout_s){
                res = true;
            }else{
                res = false;
            }
        }

    }
    return res;
}









bool scan_init_custom(void) { return true; }


static ScanInput_t ScanToInpit(ScanHandle_t* Node) {
    ScanInput_t input=SCAN_INPUT_UNDEF;

    if(Node->threshold <Node->value_in){
        input = SCAN_INPUT_UP;
    } else if (Node->value_in <= Node->threshold){
        input = SCAN_INPUT_DOWN;
    }

    if(Node->timeout_s < Node->up_time_s ) {
        input = SCAN_INPUT_TIME_OUT;
    }
    return input;
}

static bool scan_proc_acc_ll(ScanHandle_t* Node) {
    bool res = false;
    switch(Node->input){
    case SCAN_INPUT_DOWN: res = true; break;
    case SCAN_INPUT_UP: res = true; break;
    case SCAN_INPUT_TIME_OUT:
    	cli_printf(CRLF);
        LOG_PARN(SCAN, "TimeOut1:%s", ScanNodeToStr(Node));
        Node->state = SCAN_STATE_CAPTURE;
        Node->up_time_s = 0.0;
        res = true; break;
    default: res = false; break;
    }
    return res;
}


static bool scan_proc_capture_ll(ScanHandle_t* Node) {
    bool res = false;
    switch(Node->input) {
    case SCAN_INPUT_DOWN:  res = true; break;
    case SCAN_INPUT_UP:
    	LOG_PARN(SCAN, "SpotPeak:%s", ScanNodeToStr(Node));
        Node->up_time_s = 0.0;
        Node->action = SCAN_ACTION_CRLF;
        Node->state = SCAN_STATE_ACC;
        res = true;
        break;
    case SCAN_INPUT_TIME_OUT:
    	LOG_PARN(SCAN, "TimeOut2:%s", ScanNodeToStr(Node));
        Node->state = SCAN_STATE_ACC;
        Node->up_time_s = 0.0;
        res = true;
        break;
    default: res = false; break;
    }
    return res;
}


bool scan_proc_val(uint8_t num, float value_in, ScanAction_t* const action) {
    bool res = false;
    ScanHandle_t* Node = ScanGetNode(num);
    if(Node) {
        if(action) {
            Node->value_in = value_in;
            Node->up_time_s +=  1.0 /((float)Node->sample_freq_hz);
            Node->action = SCAN_ACTION_NONE;
            Node->input =  ScanToInpit(Node);
            Node->prev_state = Node->state;

            switch(Node->state) {
                case SCAN_STATE_ACC: {     res = scan_proc_acc_ll(Node);   }break;
                case SCAN_STATE_CAPTURE:{  res = scan_proc_capture_ll(Node);   } break;
                case SCAN_STATE_UNDEF: Node->state=SCAN_STATE_ACC; res = true; break;
                default: Node->state=SCAN_STATE_ACC; break;
            }

            *action = Node->action ;
            LOG_PARN(SCAN, "%s", ScanNodeToStr(Node));
        }
    } else {
        LOG_ERROR(SCAN, "NodeErr %u", num);
    }

    return res;
}




bool scan_init_one(uint8_t num) {
    bool res = false;
    const ScanConfig_t* Config = ScanGetConfig(num);
    if(Config) {
        LOG_WARNING(SCAN, "Spot,Cfg,%s",ScanConfigToStr(Config));
        res = ScanIsValidConfig(Config);
        if(res) {
            ScanHandle_t* Node = ScanGetNode(num);
            if(Node) {
                Node->sample_freq_hz = Config->sample_freq_hz;
                Node->threshold = Config->threshold;
                Node->timeout_s = Config->timeout_s;
                Node->name = Config->name;
                Node->num = Config->num;

                Node->state = SCAN_STATE_UNDEF;
                Node->prev_state = SCAN_STATE_UNDEF;
                Node->valid = true;
                Node->init = true;
                LOG_INFO(SCAN, "SCAN:%u,Init,Ok", num);
                res = true;
            }
        }
    }
    return res;
}







COMPONENT_INIT_PATTERT(SCAN, SCAN, scan)
