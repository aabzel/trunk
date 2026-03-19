#include "ext_int_mcal.h"

#include "data_utils.h"
#include "ext_int_custom_drv.h"
#include "ext_int_diag.h"
#include "gpio_mcal.h"
#include "interrupt_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "std_includes.h"

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
    log_level_get_set(EXT_INT, LOG_LEVEL_INFO);
    return res;
}

static bool ext_int_init_common(ExtIntHandle_t* Node, const ExtIntConfig_t* Config) {
    bool res = false;
    if(Node) {
        if(Config) {
            Node->interrupt_on = Config->interrupt_on;
            Node->irq_priority = Config->irq_priority;
            Node->edge = Config->edge;
            Node->num = Config->num;
            Node->name = Config->name;
            Node->Pad = Config->Pad;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool ext_int_proc_one(uint8_t num) {
    bool res = false;
    ExtIntHandle_t* Node = ExtIntGetNode(num);
    if(Node) {
        if(Node->unprocessed) {
            LOG_DEBUG(EXT_INT, "%s", ExtIntNodeToStr(Node));
            Node->unprocessed = false;
        }
    }
    return res;
}

bool ext_int_init_one(uint8_t num) {
    bool res = false;
    log_level_get_set(EXT_INT, LOG_LEVEL_DEBUG);
    const ExtIntConfig_t* Config = ExtIntGetConfig(num);
    if(Config) {
        LOG_WARNING(EXT_INT, "%s", ExtIntConfigToStr(Config));
        ExtIntHandle_t* Node = ExtIntGetNode(num);
        if(Node) {
            ext_int_init_common(Node, Config);
            ExtIntInfo_t* ExIntInfo = ExtIntGetInfo(num);
            if(ExIntInfo) {
                res = false;
                //    exint_polarity_config_type line_polarity = GpioExpIntPotarityToArtery(Config->edge);
                // uint32_t line_select = num_exint_line(Config->Pad.pin);
                // exint_init_type ExIntInitStruct = {0};

#if 0
                GpioPortInfo_t* PortInfo = GpioGetPortInfo(Config->Pad.port);
                if(PortInfo) {
                //    scfg_exint_line_config(PortInfo->port_source, (scfg_pins_source_type)Config->Pad.pin);
                }
#endif

                res = true;
                const ExtIntInfo_t* Info = ExtIntGetInfo(Config->Pad.pin);
                if(Info) {
                    res = interrupt_control(Info->irq_n, Config->interrupt_on);
                }
            } else {
                LOG_ERROR(EXT_INT, "EXT_INT%u InstErr", num);
            }
        } else {
            LOG_ERROR(EXT_INT, "EXT_INT%u NodeErr", num);
        }
    } else {
        LOG_DEBUG(EXT_INT, "EXT_INT%u ConfErr", num);
    }
    log_level_get_set(EXT_INT, LOG_LEVEL_INFO);
    return res;
}
