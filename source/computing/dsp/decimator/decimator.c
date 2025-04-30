#include "decimator.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "code_generator.h"
#include "data_utils.h"
#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif
#include "log.h"
#include "decimator_config.h"
#include "decimator_diag.h"
#include "sys_config.h"

COMPONENT_GET_NODE(Decimator, decimator)

COMPONENT_GET_CONFIG(Decimator, decimator)


static bool DecimatorIsValidConfig(const DecimatorConfig_t* const Config) {
    bool res = false;
    if(Config) {
        if(1 < Config->samples_per_bit){
            res = true;
        }
    }
    return res;
}




DecimatorState_t decimator_get_state(uint8_t num) {
    DecimatorState_t out_state = DECIMATOR_STATE_UNDEF;
    DecimatorHandle_t* Node = DecimatorGetNode(num);
    if(Node) {
        out_state = Node->state;
    }
    return out_state;
}

bool decimator_adjust(uint8_t num, uint32_t samples_per_bit){
    bool res = false;
    DecimatorHandle_t* Node = DecimatorGetNode(num);
    if(Node) {
        Node->samples_per_bit = samples_per_bit;
        Node->valid_data = false ; // spot valid bit
        Node->value=DECIMATOR_DATA_INVALID;
        Node->data_out=DECIMATOR_DATA_INVALID; // extracted data bit after decimation
        Node->samples_cnt=0;
        Node->state=DECIMATOR_STATE_IDLE;
        Node->input=DECIMATOR_INPUT_UNDEF;
        Node->prev_state=DECIMATOR_STATE_IDLE;
        res = true;
    }
    return res;
}

static bool decimator_proc_one_ll(DecimatorHandle_t* const Node){
    bool res = false;
    switch(Node->input){
        case DECIMATOR_INPUT_ONE: {
            Node->state= DECIMATOR_STATE_ONE;
            Node->samples_cnt++;
            res = true;
        } break;
        case DECIMATOR_INPUT_ZERO:{
            Node->state= DECIMATOR_STATE_ZERO;
            Node->samples_cnt=1;
            res = true;
        } break;
        case DECIMATOR_INPUT_OVERFLOW:{
            Node->samples_cnt= 0;
            Node->valid_data = true;
            Node->data_out = 1;
            res = false;
        } break;
        default: res = false; break;
    }
    return res;
}

static bool decimator_proc_zero_ll(DecimatorHandle_t* const Node){
    bool res = false;
    switch(Node->input){
        case DECIMATOR_INPUT_ONE: {
            Node->state= DECIMATOR_STATE_ONE;
            Node->samples_cnt = 1;
            res = true;
        } break;
        case DECIMATOR_INPUT_ZERO:{
            Node->state= DECIMATOR_STATE_ZERO;
            Node->samples_cnt++;

            res = true;
        } break;
        case DECIMATOR_INPUT_OVERFLOW:{
            Node->samples_cnt= 0;
            Node->valid_data = true;
            Node->data_out = 0;
            res = false;
        } break;
        default: res = false; break;
    }
    return res;

}

static bool decimator_proc_idle_ll(DecimatorHandle_t* const Node){
    bool res = false;
    switch(Node->input){
        case DECIMATOR_INPUT_ONE: {
            Node->state= DECIMATOR_STATE_ONE;
            Node->samples_cnt=1;
            res = true;
        } break;
        case DECIMATOR_INPUT_ZERO:{
            Node->state= DECIMATOR_STATE_ZERO;
            Node->samples_cnt=1;
            res = true;
        } break;
        case DECIMATOR_INPUT_OVERFLOW:{
            Node->state= DECIMATOR_STATE_IDLE;
            Node->samples_cnt= 0;
            res = false;
        } break;
        default: res = false; break;
    }
    return res;
}

static bool decimator_proc_val_ll(DecimatorHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->valid_data = false;
        LOG_DEBUG(DECIMATOR, "%s", DecimatorNodeToStr(Node));
        switch(Node->state) {
            case DECIMATOR_STATE_ONE: res=decimator_proc_one_ll(Node); break;
            case DECIMATOR_STATE_ZERO: res=decimator_proc_zero_ll(Node); break;
            case DECIMATOR_STATE_IDLE: res=decimator_proc_idle_ll(Node); break;
            default: res = false; break;
        }

        Node->prev_state = Node->state;
    } else {
        LOG_ERROR(DECIMATOR, "NodeErr:%u", Node->num);
    }

    return res;
}

bool decimator_init_custom(void) { return true; }


static DecimatorInput_t DecimatorValToInpit(int8_t val) {
    DecimatorInput_t input=DECIMATOR_INPUT_UNDEF;
    switch(val) {
        case 0: input=DECIMATOR_INPUT_ZERO; break;
        case 1: input=DECIMATOR_INPUT_ONE; break;
        default: input=DECIMATOR_INPUT_UNDEF; break;
    }
    return input;
}

bool decimator_proc_val(uint8_t num, int8_t sample_in, int8_t* const sample_out) {
    bool res = false;
    DecimatorHandle_t* Node = DecimatorGetNode(num);
    if(Node) {
        Node->value = sample_in;
        Node->input = DecimatorValToInpit(sample_in);
        res = decimator_proc_val_ll(Node);
        if(Node->samples_per_bit<=Node->samples_cnt){
            Node->input = DECIMATOR_INPUT_OVERFLOW;
            res = decimator_proc_val_ll(Node);
        }
        if(Node->valid_data){
        	res = true;
            *sample_out = Node->data_out;
        }else{
        	res = false;
            *sample_out = DECIMATOR_DATA_INVALID;
        }
    } else {
        LOG_ERROR(DECIMATOR, "NodeErr %u", num);
    }

    return res;
}

bool decimator_init_one(uint8_t num) {
    bool res = false;
    const DecimatorConfig_t* Config = DecimatorGetConfig(num);
    if(Config) {
        LOG_WARNING(DECIMATOR, "Spot,Cfg,%s",DecimatorConfigToStr(Config));
        res = DecimatorIsValidConfig(Config);
        if(res) {
            DecimatorHandle_t* Node = DecimatorGetNode(num);
            if(Node) {
                Node->samples_per_bit = Config->samples_per_bit;
                Node->name = Config->name;
                Node->num = Config->num;

                Node->samples_cnt = 0;
                Node->state = DECIMATOR_STATE_UNDEF;
                Node->prev_state = DECIMATOR_STATE_UNDEF;
                Node->value = 0xFF;
                Node->valid = true;
                Node->init = true;
                LOG_INFO(DECIMATOR, "DECIMATOR:%u,Init,Ok", num);
                res = true;
            }
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(DECIMATOR, DECIMATOR, decimator)
