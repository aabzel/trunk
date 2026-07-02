#include "ext_int_mcal.h"

#include "data_utils.h"
#include "ext_int_custom_drv.h"
#include "ext_int_diag.h"
#include "gpio_mcal.h"
#include "hal_mcal.h"
#include "interrupt_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "std_includes.h"

#ifdef HAS_IQUEUE
#include "iqueue.h"
#endif

static const ExtIntInfo_t ExtIntInfo[] = {
    {
        .valid = true,
        .num = 0,
        .irq_n = EXTI0_IRQn,
    },
    {
        .valid = true,
        .num = 1,
        .irq_n = EXTI1_IRQn,
    },
    {
        .valid = true,
        .num = 2,
        .irq_n = EXTI2_IRQn,
    },
    {
        .valid = true,
        .num = 3,
        .irq_n = EXTI3_IRQn,
    },
    {
        .valid = true,
        .num = 4,
        .irq_n = EXTI4_IRQn,
    },
    {
        .valid = true,
        .num = 5,
        .irq_n = EXTI9_5_IRQn,
    },
    {
        .valid = true,
        .num = 6,
        .irq_n = EXTI9_5_IRQn,
    },
    {
        .valid = true,
        .num = 7,
        .irq_n = EXTI9_5_IRQn,
    },
    {
        .valid = true,
        .num = 8,
        .irq_n = EXTI9_5_IRQn,
    },
    {
        .valid = true,
        .num = 9,
        .irq_n = EXTI9_5_IRQn,
    },
    {
        .valid = true,
        .num = 10,
        .irq_n = EXTI15_10_IRQn,
    },
    {
        .valid = true,
        .num = 11,
        .irq_n = EXTI15_10_IRQn,
    },
    {
        .valid = true,
        .num = 12,
        .irq_n = EXTI15_10_IRQn,
    },
    {
        .valid = true,
        .num = 13,
        .irq_n = EXTI15_10_IRQn,
    },
    {
        .valid = true,
        .num = 14,
        .irq_n = EXTI15_10_IRQn,
    },
    {
        .valid = true,
        .num = 15,
        .irq_n = EXTI15_10_IRQn,
    },
};

static const ExtIntInfo_t* ExtIntGetInfo(uint8_t num) {
    ExtIntInfo_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(ExtIntInfo);
    for(i = 0; i < cnt; i++) {
        if(num == ExtIntInfo[i].num) {
            if(ExtIntInfo[i].valid) {
                Node = &ExtIntInfo[i];
                break;
            }
        }
    }
    return Node;
}

bool ext_int_init_custom(void) {
    bool res = false;
    return res;
}

uint8_t exti_get_pin(void) {
    uint8_t gpio_pin = 0xFF;
    ExtIntRegPending_t Pending;
    Pending.qword = EXTI->PR;
    uint8_t cur_bit = 0;
    for(cur_bit = 0; cur_bit < 32; cur_bit++) {
        if(CHECK_BIT_NUM(Pending.qword, cur_bit)) {
            gpio_pin = cur_bit;
            break;
        }
    }
    return gpio_pin;
}


static uint32_t ExtIntGpioPinToLine(const uint8_t pin) {
    uint32_t line = 0;
    switch(pin) {
    case 0:
        line = EXTI_LINE_0;
        break;
    case 1:
        line = EXTI_LINE_1;
        break;
    case 2:
        line = EXTI_LINE_2;
        break;
    case 3:
        line = EXTI_LINE_3;
        break;
    case 4:
        line = EXTI_LINE_4;
        break;
    case 5:
        line = EXTI_LINE_5;
        break;
    case 6:
        line = EXTI_LINE_6;
        break;
    case 7:
        line = EXTI_LINE_7;
        break;
    case 8:
        line = EXTI_LINE_8;
        break;
    case 9:
        line = EXTI_LINE_9;
        break;
    case 10:
        line = EXTI_LINE_10;
        break;
    case 11:
        line = EXTI_LINE_11;
        break;
    case 12:
        line = EXTI_LINE_12;
        break;
    case 13:
        line = EXTI_LINE_13;
        break;
    case 14:
        line = EXTI_LINE_14;
        break;
    case 15:
        line = EXTI_LINE_15;
        break;
    default:
        break;
    }
    return line;
}

static uint32_t ExtIntEdgeToTrigger(const PinIntEdge_t edge) {
    uint32_t trigger = 0;
    switch(edge) {
    case PIN_INT_EDGE_RISING:
        trigger = EXTI_TRIGGER_RISING;
        break;
    case PIN_INT_EDGE_NONE:
        trigger = EXTI_TRIGGER_NONE;
        break;
    case PIN_INT_EDGE_FALLING:
        trigger = EXTI_TRIGGER_FALLING;
        break;
    case PIN_INT_EDGE_BOTH:
        trigger = EXTI_TRIGGER_RISING_FALLING;
        break;
    default:
        break;
    }
    return trigger;
}

static uint32_t ExtIntGpioPortToGPIOSel(const uint8_t port) {
    uint32_t gpio_sel = 0;
    switch(port) {
    case PORT_A:
        gpio_sel = EXTI_GPIOA;
        break;
    case PORT_B:
        gpio_sel = EXTI_GPIOB;
        break;
    case PORT_C:
        gpio_sel = EXTI_GPIOC;
        break;

#if defined(GPIOD)
    case PORT_D:
        gpio_sel = EXTI_GPIOD;
        break;
#endif /* GPIOD */

#if defined(GPIOE)
    case PORT_E:
        gpio_sel = EXTI_GPIOE;
        break;
#endif /* GPIOE */

#if defined(GPIOF)
    case PORT_F:
        gpio_sel = EXTI_GPIOF;
        break;
#endif /* GPIOF */

#if defined(GPIOG)
    case PORT_G:
        gpio_sel = EXTI_GPIOG;
        break;
#endif /* GPIOG */

#if defined(GPIOH)
    case PORT_H:
        gpio_sel = EXTI_GPIOH;
        break;
#endif /* GPIOH */

#if defined(GPIOI)
    case PORT_I:
        gpio_sel = EXTI_GPIOI;
        break;
#endif /* GPIOI */

#if defined(GPIOJ)
    case PORT_J:
        gpio_sel = EXTI_GPIOJ;
        break;
#endif /* GPIOJ */

#if defined(GPIOK)
    case PORT_K:
        gpio_sel = EXTI_GPIOK;
        break;
#endif /* GPIOK */
    default:
        break;
    }
    return gpio_sel;
}

bool ext_int_init_one(uint8_t num) {
    bool res = false;
    const ExtIntConfig_t* Config = ExtIntGetConfig(num);
    res = ExtIntIsValidConfig(Config);
    if(res) {
        res = false;
        LOG_WARNING(EXT_INT, "%s", ExtIntConfigToStr(Config));

        ExtIntHandle_t* Node = ExtIntGetNode(num);
        if(Node) {
            ext_int_init_common(Node, Config);
            ExtIntInfo_t* ExIntInfo = ExtIntGetInfo(num);
            if(ExIntInfo) {
                res = false;
                const ExtIntInfo_t* Info = ExtIntGetInfo(Config->Pad.pin);
                if(Info) {
                    EXTI_ConfigTypeDef ExtiConfig = {0};
                    /*!< The Exti line to be configured. This parameter
                    can be a value of @ref EXTI_Line */
                    ExtiConfig.Line = ExtIntGpioPinToLine(Config->Pad.pin);
                    ExtiConfig.Mode = EXTI_MODE_INTERRUPT; /*!< The Exit Mode to be configured for a core.
                                          This parameter can be a combination of @ref EXTI_Mode */
                    ExtiConfig.Trigger = ExtIntEdgeToTrigger(Config->edge);
                    /*!< The Exti Trigger to be configured. This parameter
                    can be a value of @ref EXTI_Trigger */
                    ExtiConfig.GPIOSel = ExtIntGpioPortToGPIOSel(Config->Pad.port);
                    /*!< The Exti GPIO multiplexer selection to be configured.
                      This parameter is only possible for line 0 to 15. It
                      can be a value of @ref EXTI_GPIOSel */

                    HAL_StatusTypeDef ret = HAL_EXTI_SetConfigLine(&(Node->h_exti), &ExtiConfig);
                    res = HAL_retToRes(ret);
                    res = interrupt_control(Info->irq_n, true);
                }

#ifdef HAS_EXT_INT_EVENT_FIFO
                i_status ret = iqueue_init(&Node->iQueue,
                                           Node->event_mem_size,
                                           sizeof(ExtIntEvent_t),
                                           Node->EventMem);
                res = iqueue_ret_res(ret);
#endif

            } else {
                LOG_ERROR(EXT_INT, "EXT_INT%u,InstErr", num);
            }
        } else {
            LOG_ERROR(EXT_INT, "EXT_INT%u,NodeErr", num);
        }
    } else {
        LOG_DEBUG(EXT_INT, "EXT_INT%u,ConfErr", num);
    }
    return res;
}
