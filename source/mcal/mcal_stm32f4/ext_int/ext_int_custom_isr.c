#include "ext_int_custom_isr.h"

#include "ext_int_custom_drv.h"
#include "ext_int_isr.h"
#include "ext_int_mcal.h"
#include "gpio_mcal.h"
#include "microcontroller_const.h"

#ifdef HAS_IR_RECEIVER
#include "ir_receiver_mcal.h"
#endif

static bool ext_int_proc_egde(ExtIntHandle_t* Node) {
    bool res = false;
    switch(Node->edge) {
    case PIN_INT_EDGE_FALLING:
        res = ExtIntFallingCallBack(Node);
        break;
    case PIN_INT_EDGE_RISING:
        res = ExtIntRisingCallBack(Node);
        break;
    default:
        res = false;
        break;
    }
    return res;
}

bool EXINTx_IRQHandler(const uint8_t num) {
    bool res = false;
    ExtIntHandle_t* Node = ExtIntGetNode(num);
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
        res = gpio_get_state(Node->Pad, &logic_level);
        Node->edge = gpio_logic_level_to_edge(logic_level);
#ifdef HAS_IR_RECEIVER
        res = ir_receiver_proc_event(1, Node->edge);
#endif

        res = ext_int_proc_egde(Node);
        Node->unprocessed = true;
    }
    HAL_GPIO_EXTI_IRQHandler(1 << num);

    return res;
}
