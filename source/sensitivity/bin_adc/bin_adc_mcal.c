#include "bin_adc_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "timer_mcal.h"
#include "gpio_mcal.h"
#include "dma_channel_mcal.h"

//COMPONENT_IS_VALID(BinAdc, bin_adc)
COMPONENT_GET_NODE(BinAdc, bin_adc)
COMPONENT_GET_CONFIG(BinAdc, bin_adc)

bool bin_adc_is_valid_num(uint8_t num) {
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < bin_adc_get_cnt(); i++) {
        if(num == BinAdcInstance[i].num) {
            if(BinAdcInstance[i].valid) {
                res = BinAdcInstance[i].init;
                break;
            }
        }
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool BinAdcIsValidConfig(const BinAdcConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        bool lres = false;
        ifn(Config->name) {
            LOG_ERROR(BIN_ADC, "BIN_ADC_%u,Name,Err", Config->num);
            res = false;
        }

        lres = timer_is_valid(Config->timer_num);
        ifn(lres) {
            LOG_ERROR(BIN_ADC, "BIN_ADC_%u,timer_num,Err", Config->num);
            res = false;
        }

        ifn(0<Config->sample_freq_hz) {
            LOG_ERROR(BIN_ADC, "BIN_ADC_%u,sample_freq_hz,Err", Config->num);
            res = false;
        }

        ifn(Config->GpioPortDataArray) {
            LOG_ERROR(BIN_ADC, "BIN_ADC_%u,GpioPortDataArray,Err", Config->num);
            res = false;
        }

        ifn(0<Config->data_array_size) {
            LOG_ERROR(BIN_ADC, "BIN_ADC_%u,data_array_size,Err", Config->num);
            res = false;
        }

        DmaChannelHandle_t* DmaCh = DmaChannelToNode(Config->DmaChPad);
        ifn(DmaCh) {
            LOG_ERROR(BIN_ADC, "BIN_ADC_%u,DmaCh,Err", Config->num);
            res = false;
        }

        lres= gpio_is_valid_pad(Config->inPad);
        ifn(lres) {
            LOG_ERROR(BIN_ADC, "BIN_ADC_%u,inPad,Err", Config->num);
            res = false;
        }

    }
    return res;
}

bool bin_adc_init_custom(void) {
    bool res = false;
    LOG_INFO(BIN_ADC, "Version:%u", BIN_ADC_VERSION);
    return res;
}

bool bin_adc_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(BIN_ADC, "BIN_ADC_%u,Proc", num);
    BinAdcHandle_t* Node = BinAdcGetNode(num);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool bin_adc_init_common(const BinAdcConfig_t* const Config, BinAdcHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->on_off = Config->on_off;
            Node->debugPad = Config->debugPad;
            Node->inPad = Config->inPad;
            Node->DmaChPad = Config->DmaChPad;
            Node->data_array_size = Config->data_array_size;
            Node->GpioPortDataArray = Config->GpioPortDataArray;
            Node->sample_freq_hz = Config->sample_freq_hz;
            Node->timer_num = Config->timer_num;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}



bool bin_adc_init_node(BinAdcHandle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->spin = 0;
        Node->valid = true;
        res = true;
    }
    return res;
}

bool bin_adc_rx_pad_set(const uint8_t num, const Pad_t inPad) {
    bool res = false;
    BinAdcHandle_t * Node = BinAdcGetNode(num);
    if(Node) {
        Node->inPad = inPad;
        res = true;
    }
    return res;
}

bool bin_adc_sample_freq_set(const uint8_t num,
                             const uint32_t sample_frequency_hz) {
    bool res = false;
    BinAdcHandle_t *Node = BinAdcGetNode(num);
    if(Node) {
        if(sample_frequency_hz) {
            res = timer_frequency_set(Node->timer_num, (float) sample_frequency_hz);
        }
    }
    return res;
}

bool bin_adc_start(const uint8_t num) {
    bool res = false;
    BinAdcHandle_t *Node = BinAdcGetNode(num);
    if(Node) {
        bool lres = dma_channel_is_done(Node->DmaChPad);
        if( lres) {
            GPIO_TypeDef* GPIOx = GpioPortToPortPtr(Node->inPad.port);
            res = dma_channel_source_address_set(Node->DmaChPad, &GPIOx->IDR);
            res = dma_channel_destination_address_set(Node->DmaChPad, Node->GpioPortDataArray);
            res = dma_channel_cnt_set(Node->DmaChPad, Node->data_array_size);
            res = dma_channel_start(Node->DmaChPad);
            Node->busy = res;
            Node->start_cnt++;
        }else{
            Node->busy_cnt++;
        }
    }
    return res;
}

bool bin_adc_init_one(uint8_t num) {
    bool res = false;
    uint32_t cnt = bin_adc_get_cnt();
    LOG_WARNING(BIN_ADC, "BIN_ADC_%u/%u", num, cnt);
    const BinAdcConfig_t *Config = BinAdcGetConfig(num);
    res = BinAdcIsValidConfig(Config);
    if(res) {
#ifdef HAS_BIN_ADC_DIAG
        LOG_WARNING(BIN_ADC, "%s", BinAdcConfigToStr(Config));
#endif
        BinAdcHandle_t *Node = BinAdcGetNode(num);
        if(Node) {
            res = bin_adc_init_common(Config, Node);
            res = bin_adc_init_node(Node);
            if(Node->on_off){
                res = bin_adc_start(num);
            }
            gpio_init_out_pad(Node->debugPad);
            gpio_logic_level_set(Node->debugPad,GPIO_LVL_LOW);
            Node->init = true;
        } else {
            LOG_ERROR(BIN_ADC, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(BIN_ADC, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(BIN_ADC, BIN_ADC, bin_adc)
COMPONENT_PROC_PATTERT(BIN_ADC, BIN_ADC, bin_adc)
