#include "can_custom_isr.h"

#include "can_core.h"
#include "can_isr.h"
#include "hal_mcal.h"
#include "time_mcal.h"

#ifdef HAS_LED_MONO
#include "led_mono_drv.h"
#endif

bool CANx_IRQHandler(const uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        can_isr_ll(Node);
        HAL_CAN_IRQHandler(&Node->Handle);
    }
    return res;
}
