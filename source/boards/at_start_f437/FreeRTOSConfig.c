#include "FreeRTOSConfig.h"

#include "free_rtos_types.h"
#include "free_rtos_drv.h"
#include "usb_host.h"
#include "data_utils.h"

const RtosTaskConfig_t RtosTaskConfig[] = {
    { .num=1, .TaskCode=bare_bone, .name="BareBone", .stack_depth_byte=2048, .priority=PRIORITY_LOW, .valid=true,},
    { .num=2, .TaskCode=default_task, .name="DefTask", .stack_depth_byte=256, .priority=PRIORITY_LOW, .valid=true,},
    { .num=3, .TaskCode=usb_proc_task, .name="UsbHost", .stack_depth_byte=1024, .priority=PRIORITY_LOW, .valid=true,},
};

RtosTaskHandle_t RtosTaskInstance[] = {
    { .num=1, .valid=true, .handle=NULL,},
    { .num=2, .valid=true, .handle=NULL,},
    { .num=3, .valid=true, .handle=NULL,},
};

uint32_t rtos_task_get_cnt(void){
    uint32_t  cnt  = 0 ;
    uint32_t  cnt1  = 0 ;
    uint32_t  cnt2  = 0 ;
    cnt1 = ARRAY_SIZE(RtosTaskConfig);
    cnt2 = ARRAY_SIZE(RtosTaskInstance);
    if(cnt1==cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
