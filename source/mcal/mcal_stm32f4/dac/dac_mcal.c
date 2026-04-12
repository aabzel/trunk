#include "dac_mcal.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "dac_custom_diag.h"
#include "dac_custom_types.h"
#include "hal_mcal.h"
#include "data_utils.h"
#include "gpio_diag.h"
#include "std_includes.h"
#include "stm32f4xx_hal.h"
#include "time_mcal.h"

#ifdef HAS_LOG
#include "log.h"
#endif

static const DacInfo_t DacInfo[] = {
#ifdef HAS_DAC1
    {
        .DACx = DAC1,
        .num = 1,
        .valid = true,
        .irq_n = TIM6_DAC_IRQn,
        .resolution = 12,
    },
#endif
        };

static const DacChannelInfo_t DacChannelInfo[] = { { .num = 1, .dac_channel = 1, //DAC_OUT1
        .dac_channel_code = DAC_CHANNEL_1, //DAC_OUT1
        .pad = { .port = PORT_A, .pin = 4, }, }, { .num = 1, .dac_channel = 1, //DAC_OUT2
        .dac_channel_code = DAC_CHANNEL_2, //DAC_OUT2
        .pad = { .port = PORT_A, .pin = 5, }, }, };

const DacChannelInfo_t* DacChannelToInfo(uint8_t num, uint8_t channel) {
    const DacChannelInfo_t *Info = NULL;
    uint32_t i = 0;
    for (i = 0; i < ARRAY_SIZE(DacChannelInfo); i++) {
        if(num == DacChannelInfo[i].num) {
            if(channel == DacChannelInfo[i].dac_channel) {
                Info = &DacChannelInfo[i];
                break;
            }
        }
    }
    return Info;
}

DAC_TypeDef* DacGetDACx(uint8_t num) {
    DAC_TypeDef *DACx = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(DacInfo);
    for (i = 0; i < cnt; i++) {
        if(DacInfo[i].num == num) {
            if(DacInfo[i].valid) {
                DACx = DacInfo[i].DACx;
                break;
            }
        }
    }
    return DACx;
}

uint8_t DacDACx2Num(DAC_TypeDef* DACx) {
    uint8_t num = 0;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(DacInfo);
    for (i = 0; i < cnt; i++) {
        if(DacInfo[i].DACx == DACx) {
            if(DacInfo[i].valid) {
                num = DacInfo[i].num;
                break;
            }
        }
    }
    return num;
}

uint32_t DacChannel2HalChan(uint32_t dac_channel) {
    uint32_t code = 0;
    uint32_t i = 0;
    for (i = 0; i < ARRAY_SIZE(DacChannelInfo); i++) {
        if(DacChannelInfo[i].dac_channel == dac_channel) {
            code = DacChannelInfo[i].dac_channel_code;
            break;
        }
    }
    return code;
}

bool dac_init_channel(uint8_t num, uint8_t channel) {
    LOG_DEBUG(LG_DAC, "Init,DAC%u_OUT%u", num, channel);
    bool res = false;
    DacHandle_t *Node = DacGetNode(num);
    if(Node) {
        DAC_ChannelConfTypeDef sConfig = { 0 };
        sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
        sConfig.DAC_Trigger = DAC_TRIGGER_SOFTWARE;
        uint32_t Channel = DacChannel2HalChan(channel);
        HAL_StatusTypeDef ret;
        ret = HAL_DAC_ConfigChannel(&Node->dac_h, &sConfig, Channel);
        res = HAL_retToRes(ret);
    }
    return res;
}

bool dac_init_custom(void) {
    bool res = false;
    LOG_INFO(LG_DAC, "DAC_CUSTOM_DRV_VER:%u", DAC_CUSTOM_DRV_VER);

    res = dac_init_channel(1, 1);
    res = dac_init_channel(1, 2) && res;

    return res;
}

bool dac_code_u16_set(const uint8_t num, const uint16_t code) {
    bool res = false;
    DacHandle_t *Node = DacGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret;
        ret = HAL_DAC_Start(&Node->dac_h, DAC_CHANNEL_1);
        ret = HAL_DAC_SetValue(&Node->dac_h, DAC_CHANNEL_1, DAC_ALIGN_12B_L, (uint32_t) code);
        res = HAL_retToRes(ret);
    }
    return res;
}

bool dac_voltage_set(const uint8_t num, const float voltage) {
    uint16_t code = (uint16_t) (voltage * ((float) DAC_MAX_CODE) / (DAC_V_REF));
    bool res = dac_code_u16_set(num, code);
    return res;
}

bool dac_init_one(uint8_t num) {
    LOG_INFO(LG_DAC, "Init %u", num);
    bool res = false;
    DacHandle_t *Node = DacGetNode(num);
    if(Node) {
        const DacConfig_t *Config = DacGetConfig(num);
        if(Config) {
            Node->dac_h.Instance = DacGetDACx(Config->num);
            HAL_StatusTypeDef ret;
            ret = HAL_DAC_Init(&Node->dac_h);
            res = HAL_retToRes(ret);
            if(res) {
                LOG_INFO(LG_DAC, "DAC%u,InitOk", num);
            } else {
                LOG_ERROR(LG_DAC, "DAC%u,InitErr", num);
            }
            if(res) {
                ret = HAL_DAC_Start(&Node->dac_h, DAC_CHANNEL_1);
                res = HAL_retToRes(ret);
                log_parn_res(LG_DAC, res, "Start1");
                ret = HAL_DAC_Start(&Node->dac_h, DAC_CHANNEL_2);
                res = HAL_retToRes(ret);
                log_parn_res(LG_DAC, res, "Start1");

            }
        } else {
            LOG_ERROR(LG_DAC, "%u ConfigErr", num);
        }
    } else {
        LOG_ERROR(LG_DAC, "%u NodeErr", num);
    }
    return res;
}

void HAL_DAC_MspInit(DAC_HandleTypeDef* dacHandle) {
#ifdef HAS_DAC1
    if(DAC1 == dacHandle->DACx) {
        __HAL_RCC_DAC_CLK_ENABLE();
        HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 4, 4);
        HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
    }
#endif
}

void HAL_DAC_MspDeInit(DAC_HandleTypeDef* dacHandle) {
#ifdef HAS_DAC1
    if(DAC1 == dacHandle->DACx) {
        __HAL_RCC_DAC_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
    }
#endif
}

