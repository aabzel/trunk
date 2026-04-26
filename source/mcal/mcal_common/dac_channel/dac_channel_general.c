#include "dac_channel_mcal.h"

#include "analog_misc.h"
#include "dac_const.h"
#include "dac_mcal.h"
#include "time_mcal.h"
#include "analog_misc.h"
#include "code_generator.h"
#include "gpio_mcal.h"
#include "iqueue_diag.h"
#include "dds_drv.h"
#include "compiler_const.h"
#include "log.h"
#include "microcontroller_const.h"
#include "std_includes.h"

COMPONENT_GET_CONFIG(DacChannel, dac_channel)
COMPONENT_GET_NODE(DacChannel, dac_channel)

_WEAK_FUN_
bool DacChannelIsValidConfig(const DacChannelConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(DAC_CHANNEL, "DAC_CHANNEL_%u,Name,Err", Config->num);
            res = false;
        }

        ifn(Config->SampleFifoMem) {
            LOG_ERROR(DAC_CHANNEL, "DAC_CHANNEL_%u,SampleFifoMem,Err", Config->num);
            res = false;
        }

        ifn(Config->SampleFifoMemCnt) {
            LOG_ERROR(DAC_CHANNEL, "DAC_CHANNEL_%u,SampleFifoMemCnt,Err", Config->num);
            res = false;
        }

        ifn(0.0f<Config->scale) {
            LOG_ERROR(DAC_CHANNEL, "DAC_CHANNEL_%u,scale,Err", Config->num);
            res = false;
        }

        res = gpio_is_valid_pad(Config->Pad);
        ifn(res) {
            LOG_ERROR(DAC_CHANNEL, "DAC_CHANNEL_%u,Pad,Err", Config->num);
            res = false;
        }
        // uint8_t dac_num;
        // DacChannel_t channel;
        // Pad_t Pad;
    }
    return res;
}


_WEAK_FUN_
bool dac_channel_read(uint8_t dac_num, uint16_t dac_channel, uint32_t* const code) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool dac_channel_voltage_read(uint8_t dac_num, DacChannel_t channel, float* const voltage) {
    bool res = false;
    LOG_DEBUG(DAC_CHANNEL, "Read,Dac:%u,Ch:%u", dac_num, channel);
    uint32_t code = 0;
    res = dac_channel_read(dac_num, channel, &code);
    if(res) {
        float val = 0.0;
        val = AnalogSample12ToVoltageVef3_3(code);
        LOG_PARN(DAC_CHANNEL, "DAC%u CH%u Code:%u=0x%x ->%f V", dac_num, channel, code, code, val);
        (*voltage) = val;
    }
    return res;
}

_WEAK_FUN_
float DacChannelGetVoltageScale(uint8_t num) {
    float voltage_real = 0.0;
    DacChannelHandle_t* Node = DacChannelGetNode(num);
    if(Node) {
        voltage_real = Node->voltage_real;
    } else {
        LOG_INFO(DAC_CHANNEL, "InvalidNode %u", num);
    }
    return voltage_real;
}

_WEAK_FUN_
bool DacChannelGetVoltage(uint8_t node_num, float* const voltage_scale) {
    bool res = false;
    DacChannelHandle_t* DacNode = DacChannelGetNode(node_num);
    if(DacNode) {
        if(DacNode->new_val) {
            *voltage_scale = DacNode->voltage_real;
            DacNode->new_val = false;
            res = true;
        } else {
            LOG_DEBUG(DAC_CHANNEL, "%u NoNews", node_num);
        }
    } else {
        LOG_INFO(DAC_CHANNEL, "InvalidNode %u", node_num);
    }
    return res;
}

_WEAK_FUN_
const DacChannelConfig_t* DacChannelGetConfigV2(uint8_t dac_num, DacChannel_t channel) {
    const DacChannelConfig_t* ChConfig = NULL;
    uint32_t i = 0;
    uint32_t cnt = dac_channel_get_cnt();
    for(i = 0; i < cnt; i++) {
        // DacDiagConfigChannel(&DacChannelConfig[i]);
        if(dac_num == DacChannelConfig[i].dac_num) {
            if(channel == DacChannelConfig[i].channel) {
                if(DacChannelConfig[i].valid) {
                    ChConfig = &DacChannelConfig[i];
                    break;
                } else {
                    LOG_INFO(DAC_CHANNEL, "InvalidChan %u", i);
                }
            }
        }
    }
    return ChConfig;
}

_WEAK_FUN_
DacChannelHandle_t* DacChannelGetNodeV2(uint8_t dac_num, DacChannel_t channel) {
    DacChannelHandle_t* Channel = NULL;
    uint32_t i = 0;
    uint32_t cnt = dac_channel_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(dac_num == DacChannelInstance[i].dac_num) {
            if(channel == DacChannelInstance[i].channel) {
                if(DacChannelInstance[i].valid) {
                    Channel = &DacChannelInstance[i];
                    break;
                }
            }
        }
    }
    return Channel;
}

_WEAK_FUN_
bool dac_channel_init_common(const DacChannelConfig_t* const Config, DacChannelHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->SampleFifoMemCnt = Config->SampleFifoMemCnt;
            Node->SampleFifoMem = Config->SampleFifoMem;
            Node->dac_num = Config->dac_num;
            Node->dds_num = Config->dds_num;
            Node->Pad = Config->Pad;
            Node->scale = Config->scale;
            Node->channel = Config->channel;
            Node->num = Config->num;
            Node->mode = Config->mode;
            Node->valid = true;
            Node->name = Config->name;
            Node->code = 0;
            Node->read_cnt = 0;
            Node->err_cnt = 0;
            Node->init_done = true;
            res = true;
        }
    }
    return res;
}

bool dac_channel_init_node(DacChannelHandle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->code = 0;
        Node->read_cnt = 0;
        Node->err_cnt = 0;
        Node->init_done = true;
        Node->spin_cnt= 0;
        Node->voltage= 0.0f;
        Node->voltage_real= 0.0f;
        Node->new_val= 0;
        res = true;
    }
    return res;
}

_WEAK_FUN_
bool dac_channel_code_read(uint8_t dac_num, DacChannel_t channel, int32_t* const code) {
    bool res = false;
    return res;
}

_WEAK_FUN_
float dac_channel_voltage_read_short(uint8_t dac_num, DacChannel_t channel) {
    float voltage = 0.0;
    return voltage;
}

_WEAK_FUN_
bool dac_channel_init_custom(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool dac_channel_init_one(uint8_t num) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool dac_code_to_params(DacChannelHandle_t* const Channel) {
    bool res = false;
    if(Channel) {
        Channel->voltage = AnalogSample12ToVoltageVef3_3(Channel->code);
        Channel->voltage_real = Channel->voltage * Channel->scale;
        res = true;
    }
    return res;
}

bool dac_channel_proc_from_fifo(DacChannelHandle_t* Node) {
    bool res = false;
    //     log_level_t ll = log_level_get(DAC_CHANNEL);
    i_status ret;

    uint16_t sample = 0;
    ret = iqueue_dequeue(&Node->iQueue, (void*) &sample);
    if (I_OK == ret) {
        //  if (LOG_LEVEL_DEBUG == ll) {
        //cli_printf("\rDac:Code:%4u,%5.3f V", sample, AnalogSample12ToVoltageVef3_3(sample));
        //  }
        res = dac_channel_code_set(Node->dac_num, Node->channel, sample);
    } else {
        LOG_DEBUG(DAC_CHANNEL, "FiFoPull,Err:%u=%s", ret, iQueueStatusToStr(ret));
    }

    return res;
}


static bool dac_channel_proc_from_dds(DacChannelHandle_t* Node) {
    bool res = false;

    DdsHandle_t *Dds = DdsGetNode(Node->dds_num);
    if (Dds) {
        uint16_t sample = 0;
        uint64_t time_us = time_get_us();
        res=dds_calc_one_sample(Dds, time_us, (SampleType_t* )&sample);
        if (res) {
            res = dac_channel_code_set(Node->dac_num, Node->channel, sample);
        }
    }
    return res;
}

bool dac_channel_proc_one(uint8_t num) {
    bool res = false ;
    DacChannelHandle_t *Node = DacChannelGetNode(num);
    if (Node) {
        switch(Node->mode){
            case DAC_MODE_FROM_FIFO:{
                res = dac_channel_proc_from_fifo(Node );
            } break;
            case DAC_MODE_FROM_DDS:{
                res = dac_channel_proc_from_dds(Node );
            } break;
            default: break;
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(DAC_CHANNEL, DAC_CHANNEL, dac_channel)
COMPONENT_PROC_PATTERT(DAC_CHANNEL, DAC_CHANNEL, dac_channel)
