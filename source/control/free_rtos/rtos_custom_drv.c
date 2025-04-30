#include "rtos_custom_drv.h"

#include "FreeRTOS.h"

#include "log.h"
#include "task.h"
#include "super_cycle.h"
#include "rtos_drv.h"
#include "code_generator.h"


void bare_bone(void * argument) {
    super_cycle_start();
}


void default_task(void  * argument){
    for(;;)  {
        vTaskDelay(1);
    }
}


//COMPONENT_GET_NODE(RtosTask, rtos_task)
#if 0
RtosTaskHandle_t* RtosTaskGetNode(uint8_t task_num){
    RtosTaskHandle_t* RtosTaskNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = rtos_task_get_cnt();
    for(i=0; i<=cnt; i++) {
        if(task_num == RtosTaskInstance[i].num) {
            if(RtosTaskInstance[i].valid) {
                RtosTaskNode = &RtosTaskInstance[i];
            }
        }
    }
    return RtosTaskNode;
}
#endif


//COMPONENT_GET_CONFIG(RtosTask, rtos_task)
#if 0
const RtosTaskConfig_t* RtosTaskGetConfig(uint8_t task_num){
    const  RtosTaskConfig_t* RtosTaskConfNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = rtos_task_get_cnt();
    for(i=0; i<=cnt; i++) {
        if(task_num == RtosTaskConfig[i].num){
            if(RtosTaskConfig[i].valid){
                RtosTaskConfNode = &RtosTaskConfig[i];
            }
        }
    }
    return RtosTaskConfNode;
}
#endif

static UBaseType_t  RtosPriorityToFreeRtosPriority(Priority_t priority){
    UBaseType_t uxPriority =0;
    switch(priority){
    case PRIORITY_LOW:uxPriority =0; break;
    case PRIORITY_MID:uxPriority =configMAX_PRIORITIES/2; break;
    case PRIORITY_HI:uxPriority =configMAX_PRIORITIES - 1; break;
    default:uxPriority =0; break;

    }
    return uxPriority ;
}


static bool free_rtos_init_one(uint8_t num){
    bool res = false;
    LOG_INFO(FREE_RTOS,"Init:%u",num);
        const RtosTaskConfig_t* Config= RtosTaskGetConfig(num);
        if(Config) {
            RtosTaskHandle_t* Node = RtosTaskGetNode(num);
            if(Node) {
                BaseType_t ret ;
                UBaseType_t uxPriority = RtosPriorityToFreeRtosPriority(Config->priority);
                ret = xTaskCreate((TaskFunction_t) Config->TaskCode, Config->name, Config->stack_depth_byte/2, NULL, uxPriority, &(Node->handle));
                if(pdPASS== ret ) {
                    LOG_INFO(FREE_RTOS,"Task %s CreateOk %u", Config->name, num);
                    res = true;
                }else {
                     res = false;
                    LOG_ERROR(FREE_RTOS,"Task %s,CreateErr %u", Config->name, num);
                }
            } else {
                 res = false;
                LOG_ERROR(FREE_RTOS,"NodeLack Task:%u", num);
            }
        } else {
             res = false;
            LOG_ERROR(FREE_RTOS,"CfgLack Task:%u", num);
        }
    return res;
}

bool free_rtos_init(void) {
    bool res = false;
    uint32_t err_cnt = 0;
    uint32_t ok_cnt = 0;
    uint32_t cnt = 0;
    cnt = rtos_task_get_cnt();
    LOG_INFO(FREE_RTOS,"InitAll:%u",cnt);
    uint32_t i = 0;
    for(i=1; i<=cnt; i++) {
        res=free_rtos_init_one(i);
        if(res) {
            ok_cnt++;
        }else {
            err_cnt++;
        }
    }

    if(0==err_cnt) {
        LOG_DEBUG(FREE_RTOS,"Init,Ok,Cnt:%u",ok_cnt);
        res = true;
    }else{
        LOG_ERROR(FREE_RTOS,"Init,Err,Cnt:%u",err_cnt);
        res = false;
    }

    return res;
}

