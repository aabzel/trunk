#include "dac_channel_mcal.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "dac_custom_diag.h"
#include "dac_custom_types.h"
#include "hal_mcal.h"
#include "dac_mcal.h"
#include "data_utils.h"
#include "gpio_diag.h"
#include "std_includes.h"
#include "stm32fx_hal.h"
#include "iqueue.h"
#include "time_mcal.h"

#ifdef HAS_LOG
#include "log.h"
#endif

static const DacChannelInfo_t DacChannelInfo[] = {
    {
        .num = 1,
        .dac_channel = 1,
        .dac_channel_code = DAC_CHANNEL_1,
        .pad = { .port = PORT_A, .pin = 4, },
    },

    {
        .num = 1,
        .dac_channel = 2,
        .dac_channel_code = DAC_CHANNEL_2,
        .pad = { .port = PORT_A, .pin = 5, },
    },
};

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

bool dac_channel_init(uint8_t dac_num, uint8_t channel) {
    LOG_DEBUG(DAC_CHANNEL, "Init,DAC%u_OUT%u", dac_num, channel);
    bool res = false;
    DacHandle_t *Dac = DacGetNode(dac_num);
    if (Dac) {
        DAC_ChannelConfTypeDef sConfig = { 0 };
        sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
        sConfig.DAC_Trigger = DAC_TRIGGER_SOFTWARE;
        HAL_StatusTypeDef ret;
        uint32_t Channel = DacChannel2HalChan(channel);
        ret = HAL_DAC_ConfigChannel(&Dac->dac_h, &sConfig, Channel);
        res = HAL_retToRes(ret);
    }
    return res;
}

bool dac_channel_init_custom(void) {
    bool res = false;
    LOG_INFO(DAC_CHANNEL, "DAC_CUSTOM_DRV_VER:%u", DAC_CUSTOM_DRV_VER);

    //res = dac_init_channel(1, 1);
    //res = dac_init_channel(1, 2) && res;

    return res;
}

bool dac_channel_code_set(const uint8_t num, DacChannel_t channel, const uint16_t code) {
    bool res = false;
    DacChannelHandle_t *Node = DacChannelGetNode(num);
    if (Node) {
        const DacChannelInfo_t *Info = DacChannelToInfo(Node->dac_num, channel);
        if (Info) {
            DacHandle_t *Dac = DacGetNode(Node->dac_num);
            if (Dac) {
                HAL_StatusTypeDef ret;
                ret = HAL_DAC_Start(&Dac->dac_h, Info->dac_channel_code);
                //res = HAL_retToRes(ret);
                //if (res) {
                ret = HAL_DAC_SetValue(&Dac->dac_h, Info->dac_channel_code, DAC_ALIGN_12B_L, (uint32_t) code);
                res = HAL_retToRes(ret);
                //}
            }
        }
    }
    return res;
}

bool dac_channel_voltage_set(uint8_t dac_num, DacChannel_t channel,  const float voltage) {
    uint16_t code = (uint16_t) (voltage * ((float) DAC_MAX_CODE) / (DAC_V_REF));
    bool res = dac_channel_code_set(dac_num, channel, code);
    return res;
}

bool dac_channel_voltage_get(const uint8_t num, float * voltage) {
    bool res = false;
    return res;
}

bool dac_channel_init_one(uint8_t num) {
    bool res = false;
    LOG_INFO(DAC_CHANNEL, "Init,%u", num);
    const DacChannelConfig_t *Config = DacChannelGetConfig(num);
    res = DacChannelIsValidConfig(Config);
    if (res) {
        LOG_WARNING(DAC_CHANNEL, "%s", DacChannelConfigToStr(Config));
        DacChannelHandle_t *Node = DacChannelGetNode(num);
        if (Node) {
            res = dac_channel_init_common(Config, Node);
            res = dac_channel_init_node( Node);
            i_status status = iqueue_init(&Node->iQueue, Config->SampleFifoMemCnt, sizeof(uint16_t), Config->SampleFifoMem);
            res = iqueue_ret_res(status);

            const DacChannelInfo_t *Info = DacChannelToInfo(Config->dac_num, Config->channel);
            if (Info) {
                res=dac_channel_init(  Config->dac_num,   Config->channel);
                DacHandle_t* Dac = DacGetNode(  Config->dac_num);
                if(Dac) {
                    HAL_StatusTypeDef ret;
                    ret = HAL_DAC_Start(&Dac->dac_h, Info->dac_channel_code);
                    res = HAL_retToRes(ret);
                    log_info_res_u32(DAC_CHANNEL, res, "Start", num);
                }
            }
        } else {
            LOG_ERROR(DAC_CHANNEL, "%u ConfigErr", num);
        }
    } else {
        LOG_ERROR(DAC_CHANNEL, "%u NodeErr", num);
    }
    return res;
}


