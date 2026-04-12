#include "systick_isr.h"

#include "systick_mcal.h"

void SysTickIntHandler(void) {
    SysTickHandle_t* Node = SysTickGetNode(1);
    if(Node) {
        Node->up_time_ms32++;
        Node->up_time_ms64++;
    }
}
