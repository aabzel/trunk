#include "rtos_drv.h"

#include "log.h"
#include "super_cycle.h"
#include "code_generator.h"

COMPONENT_GET_NODE(RtosTask, rtos_task)
COMPONENT_GET_CONFIG(RtosTask, rtos_task)

static bool rtos_task_init_custom(void) {
    bool res = true;
    return res;
}

bool rtos_delay_ms(uint32_t delay_ms){
    bool res = false;
    if(delay_ms) {
#ifdef HAS_FREE_RTOS
            vTaskDelay(2);
            res = true;
#endif
    }
    return res;
}

#if 0
RtosTaskHandle_t* RtosTaskGetNode(uint8_t num){
    RtosTaskHandle_t* RtosTaskNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = rtos_task_cnt();
    for(i=0; i<=cnt; i++) {
        if(num == RtosTaskInstance[i].num) {
            if(RtosTaskInstance[i].valid) {
                RtosTaskNode = &RtosTaskInstance[i];
                break;
            }
        }
    }
    return RtosTaskNode;
}

const RtosTaskConfig_t* RtosTaskGetConfig(uint8_t num){
    const  RtosTaskConfig_t* RtosTaskConfNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = rtos_task_cnt();
    for(i=0; i<=cnt; i++) {
        if(num == RtosTaskConfig[i].num){
            if(RtosTaskConfig[i].valid){
                RtosTaskConfNode = &RtosTaskConfig[i];
                break;
            }
        }
    }
    return RtosTaskConfNode;
}
#endif

static bool rtos_task_init_one(uint8_t num) {
    bool res = false;
    LOG_INFO(RTOS,"Init:%u", num);
        const RtosTaskConfig_t* Config = RtosTaskGetConfig(num);
        if(Config) {
            RtosTaskHandle_t* Node = RtosTaskGetNode(num);
            if(Node) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(RTOS,"NodeLack Task:%u", num);
            }
        } else {
            LOG_ERROR(RTOS,"CfgLack Task:%u", num);
        }
    return res;
}


COMPONENT_INIT_PATTERT(RTOS, RTOS, rtos_task)
