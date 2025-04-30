#include "ext_int_mcal.h"

#include <stdbool.h>
#include <stdint.h>

#include "data_utils.h"
#include "ext_int_custom_drv.h"
#include "gpio_mcal.h"
#include "log.h"
#include "microcontroller_const.h"

static const ExtIntInfo_t ExtIntInfo[] = {
    {
        .valid = true,
        .num = 0,
        .exint_line_n = EXINT_LINE_0,
        .irq_n = EXINT0_IRQn,
    },
    {
        .valid = true,
        .num = 1,
        .exint_line_n = EXINT_LINE_1,
        .irq_n = EXINT1_IRQn,
    },
    {
        .valid = true,
        .num = 2,
        .exint_line_n = EXINT_LINE_2,
        .irq_n = EXINT2_IRQn,
    },
    {
        .valid = true,
        .num = 3,
        .exint_line_n = EXINT_LINE_3,
        .irq_n = EXINT3_IRQn,
    },
    {
        .valid = true,
        .num = 4,
        .exint_line_n = EXINT_LINE_4,
        .irq_n = EXINT4_IRQn,
    },
    {
        .valid = true,
        .num = 5,
        .exint_line_n = EXINT_LINE_5,
        .irq_n = EXINT9_5_IRQn,
    },
    {
        .valid = true,
        .num = 6,
        .exint_line_n = EXINT_LINE_6,
        .irq_n = EXINT9_5_IRQn,
    },
    {
        .valid = true,
        .num = 7,
        .exint_line_n = EXINT_LINE_7,
        .irq_n = EXINT9_5_IRQn,
    },
    {
        .valid = true,
        .num = 8,
        .exint_line_n = EXINT_LINE_8,
        .irq_n = EXINT9_5_IRQn,
    },
    {
        .valid = true,
        .num = 9,
        .exint_line_n = EXINT_LINE_9,
        .irq_n = EXINT9_5_IRQn,
    },
    {
        .valid = true,
        .num = 10,
        .exint_line_n = EXINT_LINE_10,
        .irq_n = EXINT15_10_IRQn,
    },
    {
        .valid = true,
        .num = 11,
        .exint_line_n = EXINT_LINE_11,
        .irq_n = EXINT15_10_IRQn,
    },
    {
        .valid = true,
        .num = 12,
        .exint_line_n = EXINT_LINE_12,
        .irq_n = EXINT15_10_IRQn,
    },
    {
        .valid = true,
        .num = 13,
        .exint_line_n = EXINT_LINE_13,
        .irq_n = EXINT15_10_IRQn,
    },
    {
        .valid = true,
        .num = 14,
        .exint_line_n = EXINT_LINE_14,
        .irq_n = EXINT15_10_IRQn,
    },
    {
        .valid = true,
        .num = 15,
        .exint_line_n = EXINT_LINE_15,
        .irq_n = EXINT15_10_IRQn,
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

uint32_t num_exint_line(uint8_t num) {
    uint32_t exint_line = 0;
    switch(num) {
    case 0:
        exint_line = EXINT_LINE_0;
        break;
    case 1:
        exint_line = EXINT_LINE_1;
        break;
    case 2:
        exint_line = EXINT_LINE_2;
        break;
    case 3:
        exint_line = EXINT_LINE_3;
        break;
    case 4:
        exint_line = EXINT_LINE_4;
        break;
    case 5:
        exint_line = EXINT_LINE_5;
        break;
    case 6:
        exint_line = EXINT_LINE_6;
        break;
    case 7:
        exint_line = EXINT_LINE_7;
        break;
    case 8:
        exint_line = EXINT_LINE_8;
        break;
    case 9:
        exint_line = EXINT_LINE_9;
        break;
    case 10:
        exint_line = EXINT_LINE_10;
        break;
    case 11:
        exint_line = EXINT_LINE_11;
        break;
    case 12:
        exint_line = EXINT_LINE_12;
        break;
    case 13:
        exint_line = EXINT_LINE_13;
        break;
    case 14:
        exint_line = EXINT_LINE_14;
        break;
    case 15:
        exint_line = EXINT_LINE_15;
        break;
    default:
        break;
    }

    uint32_t ex_int_line1 = ((uint32_t)1) << (num + 1);
    if(ex_int_line1 == exint_line) {
    }

    return exint_line;
}

bool ext_int_init_custom(void) {
    bool res = false;
    log_level_get_set(EXT_INT, LOG_LEVEL_INFO);
    crm_periph_clock_enable(CRM_SCFG_PERIPH_CLOCK, TRUE);
    return res;
}

static exint_polarity_config_type GpioExpIntPotarityToArtery(PinIntEdge_t int_edge) {
    exint_polarity_config_type line_polarity = PIN_INT_EDGE_RISING;
    switch(int_edge) {
    case PIN_INT_EDGE_FALLING:
        line_polarity = PIN_INT_EDGE_FALLING;
        break;
    case PIN_INT_EDGE_RISING:
        line_polarity = PIN_INT_EDGE_RISING;
        break;
    case PIN_INT_EDGE_BOTH:
        line_polarity = PIN_INT_EDGE_BOTH;
        break;

    default:
        line_polarity = PIN_INT_EDGE_RISING;
        break;
    }
    return line_polarity;
}

static bool ext_int_init_common(ExtIntHandle_t* Node, const ExtIntConfig_t* Config) {
    bool res = false;
    if(Node) {
        if(Config) {
            Node->interrupt_on = Config->interrupt_on;
            Node->irq_priority = Config->irq_priority;
            Node->edge = Config->edge;
            Node->num = Config->num;
            Node->Pad = Config->Pad;
            Node->valid = true;
            res = true;
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
                exint_polarity_config_type line_polarity = GpioExpIntPotarityToArtery(Config->edge);
                uint32_t line_select = num_exint_line(Config->Pad.pin);
                exint_init_type ExIntInitStruct = {0};

                GpioPortInfo_t* PortInfo = GpioGetPortInfo(Config->Pad.port);
                if(PortInfo) {
                    scfg_exint_line_config(PortInfo->port_source, (scfg_pins_source_type)Config->Pad.pin);
                }

                exint_default_para_init(&ExIntInitStruct);
                ExIntInitStruct.line_enable = TRUE;
                ExIntInitStruct.line_mode = EXINT_LINE_INTERRUPUT;
                ExIntInitStruct.line_select = line_select;
                ExIntInitStruct.line_polarity = line_polarity;
                exint_init(&ExIntInitStruct);

                if(Config->interrupt_on) {
                    res = false;
                    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
                    const ExtIntInfo_t* ExtIntNode = ExtIntGetInfo(Config->Pad.pin);
                    if(ExtIntNode) {
                        nvic_irq_enable(ExtIntNode->irq_n, Config->irq_priority, Config->irq_priority);
                        res = true;
                    }
                }
                res = true;
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
