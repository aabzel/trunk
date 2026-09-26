#include "ext_int_isr.h"

#include "core_driver.h"
#include "ext_int_mcal.h"
#include "gpio_mcal.h"
#include "time_mcal.h"

#ifdef HAS_DCF77
#include "dcf77_mcal.h"
#endif

#ifdef HAS_IR_RECEIVER
#include "ir_receiver_mcal.h"
#endif

#ifdef HAS_INCREMENTAL_ENCODER
#include "incremental_encoder_mcal.h"
#endif

#ifdef HAS_IQUEUE
#include "iqueue.h"
#endif

bool ExtIntFallingCallBack(ExtIntHandle_t* const Node) {
    bool res = true;
    Node->falling_cnt++;
    Node->falling_done = true;
    if(Node->CallBackFalling) {
        res = Node->CallBackFalling();
    }
    return res;
}

bool ExtIntRisingCallBack(ExtIntHandle_t* const Node) {
    bool res = true;
    Node->rising_cnt++;
    Node->rising_done = true;
    if(Node->CallBackRising) {
        res = Node->CallBackRising();
    }
    return res;
}

PinIntDrop_t ExtIntEdgeToDrop(const PinIntEdge_t edge_effective) {
    PinIntDrop_t drop = PIN_INT_DROP_UNDEF;
    switch(edge_effective) {
    case PIN_INT_EDGE_FALLING:
        drop = PIN_INT_DROP_FALLING;
        break;
    case PIN_INT_EDGE_RISING:
        drop = PIN_INT_DROP_RISING;
        break;
    default:
        break;
    }
    return drop;
}

static bool ext_int_proc_egde(ExtIntHandle_t* Node, const uint32_t timestamp_us) {
    bool res = false;
#ifdef HAS_IQUEUE
    ExtIntEvent_t Event = {0};
    (void) Event;
    Event.timestamp_us = timestamp_us;
    Event.drop = ExtIntEdgeToDrop(Node->edge_effective);
#endif
    switch(Node->edge_effective) {
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

#ifdef HAS_EXT_INT_EVENT_FIFO
#ifdef HAS_IQUEUE
    // Push Event to event fifo
    i_status ret = iqueue_enqueue(&Node->iQueue, (void*)&Event);
    res = iqueue_ret_res(ret);
#endif
#endif
    return res;
}

bool ext_int_irq_handler(const uint8_t pin_num, const uint32_t timestamp_us) {
    bool res = false;
    enter_critical();
    GpioPort_t port_x = ext_int_pin_to_port(pin_num);
    Pad_t Pad = {.port=port_x, .pin=pin_num,};
    ExtIntHandle_t* Node = ExtIntPadToNode(Pad);
    if(Node) {
        // res = gpio_get_state(Node->Pad, &logic_level);
        GpioLogicLevel_t logic_level = gpio_get_state_short(Node->Pad);
        Node->edge_effective = gpio_logic_level_to_edge(logic_level);
        res = ext_int_proc_egde(Node, timestamp_us);
        Node->it_cnt++;
        Node->it_done = true;
#ifdef HAS_IR_RECEIVER
        res = ir_receiver_proc_event(1, Node->edge_effective);
#endif

#ifdef HAS_INCREMENTAL_ENCODER
        res = incremental_encoder_proc_event(Pad, Node->edge_effective);
#endif

#ifdef HAS_DCF77
        res = dcf77_proc_event(Pad, Node->edge_effective);
#endif
        Node->unprocessed = true;
    }
    exit_critical();
    return res;
}
