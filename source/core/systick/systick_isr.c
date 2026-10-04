#include "systick_isr.h"

#include "core_driver.h"
#include "mcal_common.h"
#include "systick_mcal.h"

void SysTickIntHandler(void) {
    SysTickHandle_t* Node = SysTickGetNode(1);
    if(Node) {
        if(Node->init_done) {
            enter_critical();
            Node->up_time_ms32++;
            Node->up_time_ms64++;
            // reload - Value to load into the Current Value register when the counter reaches 0
            Node->counter_wrap += Node->SYSTICKx->Load.reload;
            exit_critical();
        }
    }
}
