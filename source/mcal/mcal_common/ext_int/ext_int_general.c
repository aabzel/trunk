#include "ext_int_mcal.h"

#include <stdio.h>
#include <string.h>

#include "byte_utils.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "core_driver.h"
#include "gpio_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "std_includes.h"

#ifdef HAS_IQUEUE
#include "iqueue.h"
#include "lib_iqueue.h"
#endif

//COMPONENT_GET_NODE(ExtInt, ext_int)

ExtIntHandle_t* ExtIntGetNode(uint8_t num) {
    ExtIntHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = ext_int_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == ExtIntInstance[i].num) {
            if(ExtIntInstance[i].valid) {
                Node = &ExtIntInstance[i];
                break;
            }
        }
    }
    return Node;
}


COMPONENT_GET_CONFIG(ExtInt, ext_int)

PinIntEdge_t gpio_logic_level_to_edge(const GpioLogicLevel_t logic_level) {
    PinIntEdge_t edge = PIN_INT_EDGE_UNDEF;
    switch(logic_level) {
    case GPIO_LVL_LOW:
        edge = PIN_INT_EDGE_FALLING;
        break;
    case GPIO_LVL_HI:
        edge = PIN_INT_EDGE_RISING;
        break;
    default:
        edge = PIN_INT_EDGE_UNDEF;
        break;
    }
    return edge;
}

bool ext_int_init_common(ExtIntHandle_t* Node, const ExtIntConfig_t* Config) {
    bool res = false;
    if(Node) {
        if(Config) {
            Node->irq_priority = Config->irq_priority;
            Node->CallBackRising = Config->CallBackRising;
            Node->CallBackFalling = Config->CallBackFalling;
            Node->edge = Config->edge;
            Node->num = Config->num;
            Node->name = Config->name;
            Node->event_mem_size = Config->event_mem_size;
            Node->EventMem = Config->EventMem;
            Node->Pad = Config->Pad;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool ExtIntIsValidConfig(const ExtIntConfig_t* Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->CallBackFalling) {
            LOG_ERROR(EXT_INT, "%u,CallBackFalling,Err", Config->num);
            res = false;
        }

        ifn(Config->CallBackRising) {
            LOG_ERROR(EXT_INT, "%u,CallBackRising,Err", Config->num);
            res = false;
        }

        ifn(Config->name) {
            LOG_ERROR(EXT_INT, "%u,name,Err", Config->num);
            res = false;
        }

        ifn(Config->EventMem) {
            LOG_ERROR(EXT_INT, "%u,EventMem,Err", Config->num);
            res = false;
        }

        ifn(Config->event_mem_size) {
            LOG_ERROR(EXT_INT, "%u,event_mem_size,Err", Config->num);
            res = false;
        }

        ifn(Config->edge) {
            LOG_ERROR(EXT_INT, "%u,edge,Err", Config->num);
            res = false;
        }

        res = gpio_is_valid_pad(Config->Pad);
        ifn(res) {
            LOG_ERROR(EXT_INT, "%u,GpioPad,Err", Config->num);
            res = false;
        }
    }
    return res;
}

GpioPort_t ext_int_pin_rise_to_port(const uint8_t gpio_pin_num) {
    bool res = false;
    Pad_t Pad;
    Pad.port = GPIO_PORT_UNDEF;
    Pad.pin = gpio_pin_num;
    for(Pad.port = GPIO_PORT_A; Pad.port < GPIO_PORT_CNT; Pad.port++) {
        GpioLogicLevel_t logic_level;
        logic_level = gpio_get_state_short(Pad);
        if(GPIO_LVL_HI == logic_level) {
            ExtIntHandle_t* ExtInt = ExtIntPadToNode(Pad);
            if(ExtInt) {
                if(PIN_INT_EDGE_BOTH == ExtInt->edge) {
                    res = true;
                    break;
                }
                if(PIN_INT_EDGE_RISING == ExtInt->edge) {
                    res = true;
                    break;
                }
            }
        }
    }

    if(false == res) {
        Pad.port = GPIO_PORT_UNDEF;
    }

    return Pad.port;
}

GpioPort_t ext_int_pin_fail_to_port(const uint8_t gpio_pin_num) {
    bool res = false;
    Pad_t Pad;
    Pad.port = GPIO_PORT_UNDEF;
    Pad.pin = gpio_pin_num;
    for(Pad.port = GPIO_PORT_A; Pad.port < GPIO_PORT_CNT; Pad.port++) {
        GpioLogicLevel_t logic_level;
        logic_level = gpio_get_state_short(Pad);
        if(GPIO_LVL_LOW == logic_level) {
            ExtIntHandle_t* ExtInt = ExtIntPadToNode(Pad);
            if(ExtInt) {
                if(PIN_INT_EDGE_BOTH == ExtInt->edge) {
                    res = true;
                    break;
                }
                if(PIN_INT_EDGE_FALLING == ExtInt->edge) {
                    res = true;
                    break;
                }
            }
        }
    }

    if(false == res) {
        Pad.port = GPIO_PORT_UNDEF;
    }

    return Pad.port;
}

GpioPort_t ext_int_pin_to_port(const uint8_t gpio_pin_num) {
    GpioPort_t port = GPIO_PORT_UNDEF;
    GpioPort_t port_fail = ext_int_pin_fail_to_port(gpio_pin_num);
    if(GPIO_PORT_UNDEF != port_fail) {
        port = port_fail;
    } else {
        GpioPort_t port_rise = ext_int_pin_rise_to_port(gpio_pin_num);
        if(GPIO_PORT_UNDEF != port_rise) {
            port = port_rise;
        }
    }
    return port;
}

ExtIntHandle_t* ExtIntPadToNode(const Pad_t Pad) {
    ExtIntHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = ext_int_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(Pad.byte == ExtIntInstance[i].Pad.byte) {
            if(ExtIntInstance[i].valid) {
                Node = &ExtIntInstance[i];
                break;
            }
        }
    }
    return Node;
}

_WEAK_FUN_
bool ext_int_init_custom(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool ext_int_init_one(uint8_t num) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool ext_int_proc_one(uint8_t num) {
    bool res = false;
    ExtIntHandle_t* Node = ExtIntGetNode(num);
    if(Node) {
        if(Node->unprocessed) {
            // LOG_DEBUG(EXT_INT, "%s", ExtIntNodeToStr(Node));
            Node->unprocessed = false;
        }

        if(Node->fifo_pull){
#ifdef HAS_IQUEUE

            size_t size = 0;
            i_status ret = iqueue_size(&Node->iQueue, &size);
            res = iqueue_ret_res(ret);
            if(res) {
                if(0 < size) {
                    ExtIntEvent_t Event = {0};
                    enter_critical();
                    ret = iqueue_dequeue((iqueue_t*)&Node->iQueue, (void*)&Event);
                    exit_critical();
                    res = iqueue_ret_res(ret);
                    if(res) {
                        LOG_DEBUG(EXT_INT, "%s[%s]", ExtIntNodeToStr(Node), ExtIntEventToStr(&Event, Node));
                        Node->prev_event_time_us = Event.timestamp_us;
                    }
                }
            }
#endif
        }
    }
    return res;
}

COMPONENT_INIT_ANY_PATTERT_CNT(EXT_INT, EXT_INT, ext_int, EXT_INT_COUNT)
COMPONENT_PROC_PATTERT_CNT(EXT_INT, EXT_INT, ext_int, EXT_INT_COUNT)
