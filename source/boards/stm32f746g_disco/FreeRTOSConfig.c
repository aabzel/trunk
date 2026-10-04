#include "FreeRTOSConfig.h"

#include "free_rtos_types.h"
#include "free_rtos_drv.h"
#include "usb_host.h"
#include "data_utils.h"

const RtosTaskConfig_t SECTION_CFG_DATA RtosTaskConfig[] = {
    { .num=1, .TaskCode=bare_bone, .name="BareBone", .stack_depth_byte=2048, .priority=PRIORITY_LOW, .valid=true,},
    { .num=2, .TaskCode=default_task, .name="DefTask", .stack_depth_byte=256, .priority=PRIORITY_LOW, .valid=true,},
    { .num=3, .TaskCode=usb_proc_task, .name="UsbHost", .stack_depth_byte=1024, .priority=PRIORITY_LOW, .valid=true,},
};

RtosTaskHandle_t RtosTaskInstance[] = {
    { .num=1, .valid=true, .handle=NULL,},
    { .num=2, .valid=true, .handle=NULL,},
    { .num=3, .valid=true, .handle=NULL,},
};

COMPONENT_GET_CNT(RtosTask, rtos_task)

