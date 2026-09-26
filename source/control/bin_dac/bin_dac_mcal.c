#include "bin_dac_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "dma_channel_mcal.h"
#include "bit_fifo_mcal.h"
#include "gpio_mcal.h"
#include "bin_dac_isr.h"
#include "timer_mcal.h"

COMPONENT_IS_VALID(BinDac, bin_dac)
COMPONENT_GET_NODE(BinDac, bin_dac)
COMPONENT_GET_CONFIG(BinDac, bin_dac)

/*ISO-26262 require verify configuration*/
bool BinDacIsValidConfig(const BinDacConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        bool lres = true;
        ifn(Config->name) {
            LOG_ERROR(BIN_DAC, "BIN_DAC_%u,Name,Err", Config->num);
            res = false;
        }

        ifn(Config->TxFifoMem) {
            LOG_ERROR(BIN_DAC, "BIN_DAC_%u,TxFifoMem,Err", Config->num);
            res = false;
        }

        ifn(Config->GpioPortDataArray) {
            LOG_ERROR(BIN_DAC, "BIN_DAC_%u,GpioPortDataArray,Err", Config->num);
            res = false;
        }

        ifn(0<Config->sample_freq_hz) {
            LOG_ERROR(BIN_DAC, "BIN_DAC_%u,sample_freq_hz,Err", Config->num);
            res = false;
        }

        ifn(0 < Config->part_size) {
            LOG_ERROR(BIN_DAC, "BIN_DAC_%u,part_size,Err", Config->num);
            res = false;
        }

        ifn(0<Config->data_array_size) {
            LOG_ERROR(BIN_DAC, "BIN_DAC_%u,data_array_size,Err", Config->num);
            res = false;
        }

        lres = timer_is_valid(Config->timer_num);
        ifn(lres) {
            LOG_ERROR(BIN_DAC, "BIN_DAC_%u,timer_num,Err", Config->num);
            res = false;
        }

        ifn(0<Config->tx_fifo_mem_size) {
            LOG_ERROR(BIN_DAC, "BIN_DAC_%u,tx_fifo_mem_size,Err", Config->num);
            res = false;
        }

        lres = gpio_is_valid_pad(Config->debugPad);
        ifn(lres) {
            LOG_ERROR(BIN_DAC, "BIN_DAC_%u,debugPad,Err", Config->num);
            res = false;
        }

        lres= gpio_is_valid_pad(Config->outPad);
        ifn(lres) {
            LOG_ERROR(BIN_DAC, "BIN_DAC_%u,outPad,Err", Config->num);
            res = false;
        }

        DmaChannelHandle_t* DmaPad = DmaPadGetNodeItem(Config->DmaChPad);
        ifn(DmaPad) {
            LOG_ERROR(BIN_DAC, "BIN_DAC_%u,DmaPad,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool bin_dac_init_custom(void) {
    bool res = false;
    uint32_t cnt = bin_dac_get_cnt();
    LOG_INFO(BIN_DAC, "Version:%u", BIN_DAC_VERSION);
    LOG_INFO(BIN_DAC, "BIN_DAC_TX_SIZE:%u", BIN_DAC_TX_SIZE);
    LOG_INFO(BIN_DAC, "CNT:%u", cnt);
    if(cnt) {
        res = true;
    } else {
        LOG_ERROR(BIN_DAC, "NoConfig!");
        res = false;
    }
    return res;
}

bool bin_dac_sample_tx_ll( BinDacHandle_t *Node, const uint8_t* const bit_values, const uint32_t size) {
    bool res = false;
    if(Node) {
        LOG_DEBUG(BIN_DAC, "TxSample,Size:%u",size);
        uint32_t real_samples = MIN(size,BIN_DAC_TX_SIZE);
        res = gpio_sample_to_bsrr(Node->outPad.pin, bit_values, Node->GpioPortDataArray, real_samples);
        if(res) {
            res = bin_dac_bsrr_tx( Node->num,  Node->GpioPortDataArray,     real_samples);
        }
    }
    return res;
}

bool bin_dac_tx_next(const uint8_t num) {
    bool res = false;
    BinDacHandle_t* Node = BinDacGetNode(num);
    if(Node) {
        res = bin_dac_tx_next_ll(Node);
    }
    return res;
}

int32_t bin_dac_fifo_cnt_get(const uint8_t num) {
    int32_t count = false;
    BinDacHandle_t* Node = BinDacGetNode(num);
    if(Node) {
        count = bit_fifo_get_count(&Node->TxFifo);
    }
    return count;
}

bool bin_dac_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(BIN_DAC, "BIN_DAC_%u,Proc", num);
    BinDacHandle_t* Node = BinDacGetNode(num);
    if(Node) {

        //res = bin_dac_tx_next_ll(Node);
#if 0
        int32_t count = bit_fifo_get_count(&Node->TxFifo);
        if(0 < count) {
            uint8_t bit_part[100] = {0};
            uint32_t out_len = 0 ;
            res = bit_fifo_pull_array(&Node->TxFifo, bit_part, Node->part_size, &out_len);
            if(res) {
                if(0 < out_len) {
                    res = bin_dac_sample_tx(  num,  bit_part, out_len);
                }
            }

        }
#endif
        Node->spin++;
    }
    return res;
}

bool bin_dac_tx_pad_set(uint8_t num, const Pad_t outPad) {
    bool res = false;
    BinDacHandle_t* Node = BinDacGetNode(num);
    if(Node) {
        Node->outPad = outPad;
        LOG_INFO(BIN_DAC, "N:%u,Set,outPad:%s", num, GpioPadToStr(outPad));
        res = true;
    }
    return res;
}

bool bin_dac_part_size_set(const uint8_t num, const uint32_t part_size) {
    bool res = false;
    BinDacHandle_t *Node = BinDacGetNode(num);
    if (Node) {
        Node->part_size = part_size;
        //LOG_INFO(BIN_DAC, "N:%u,Set,partSize:%u Sam", num, part_size);
        res = true;
    }
    return res;
}

bool bin_dac_sample_freq_set(uint8_t num, const uint32_t sample_freq_hz) {
    bool res = false;
    BinDacHandle_t *Node = BinDacGetNode(num);
    if (Node) {
        if(sample_freq_hz){
            Node->sample_freq_hz = sample_freq_hz;
            res = timer_frequency_set(Node->timer_num, (float) sample_freq_hz);
            LOG_INFO(BIN_DAC, "N:%u,Set,Fs:%u Hz", num, sample_freq_hz);
        }
    }
    return res;
}


bool bin_dac_init_common(const BinDacConfig_t* const Config, BinDacHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->part_size = Config->part_size;
            Node->name = Config->name;
            Node->timer_num = Config->timer_num;
            Node->sample_freq_hz = Config->sample_freq_hz;
            Node->data_array_size = Config->data_array_size;
            Node->DmaChPad = Config->DmaChPad;
            Node->GpioPortDataArray = Config->GpioPortDataArray;
            Node->debugPad = Config->debugPad;
            Node->outPad = Config->outPad;
            Node->tx_fifo_mem_size = Config->tx_fifo_mem_size;
            Node->TxFifoMem = Config->TxFifoMem;
            res = true;
        }
    }
    return res;
}

bool bin_dac_init_node(BinDacHandle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->spin = 0;
        Node->valid = true;
        Node->busy = false;
        res = true;
    }
    return res;
}

bool bin_dac_bsrr_tx(const uint8_t num, const uint32_t* const data_bsrr, const uint32_t size) {
    bool res = false;
    BinDacHandle_t *Node = BinDacGetNode(num);
    if(Node) {
        res = dma_channel_is_done(Node->DmaChPad);
        if(res) {
            Node->GpioPortDataArray = data_bsrr;
            Node->data_array_size = size;
            GPIO_TypeDef *GPIOx = GpioPortToPortPtr(Node->outPad.port);
            res = dma_channel_source_address_set(Node->DmaChPad, Node->GpioPortDataArray);
            res = dma_channel_destination_address_set(Node->DmaChPad, &GPIOx->BSRR);
            res = dma_channel_cnt_set(Node->DmaChPad, Node->data_array_size);
            res = dma_channel_start(Node->DmaChPad);
            res = gpio_logic_level_set(Node->debugPad,GPIO_LVL_HI);
            Node->busy = res;
            Node->start_cnt++;
        } else {
            Node->busy_cnt++;
        }
    }
    return res;
}

bool bin_dac_push_samples(uint8_t num, const uint8_t* const bit_values, const uint32_t size) {
    bool res = false;
    BinDacHandle_t *Node = BinDacGetNode(num);
    if(Node) {
        res = bit_fifo_push_array(&Node->TxFifo,  bit_values,  size);
    }
    return res;
}

bool bin_dac_sample_tx(uint8_t num, const uint8_t* const bit_values, const uint32_t size){
    bool res = false;
    BinDacHandle_t *Node = BinDacGetNode(num);
    if(Node) {
        res = bin_dac_sample_tx_ll(Node, bit_values, size);
    }
    return res;
}

bool bin_dac_init_one(uint8_t num) {
    bool res = false;
    uint32_t cnt = bin_dac_get_cnt();
    LOG_WARNING(BIN_DAC, "BIN_DAC_%u/%u", num, cnt);
    const BinDacConfig_t *Config = BinDacGetConfig(num);
    res = BinDacIsValidConfig(Config);
    if(res) {
#ifdef HAS_BIN_DAC_DIAG
        LOG_WARNING(BIN_DAC, "%s", BinDacConfigToStr(Config));
#endif
        BinDacHandle_t *Node = BinDacGetNode(num);
        if(Node) {
            res = bin_dac_init_common(Config, Node);
            res = bin_dac_init_node(Node);
            res = bit_fifo_init(&Node->TxFifo, Node->TxFifoMem, Node->tx_fifo_mem_size ) ;
            res = gpio_init_out_pad(Node->debugPad);
            res = gpio_logic_level_set(Node->debugPad,GPIO_LVL_LOW);
            Node->init = true;
        } else {
            LOG_ERROR(BIN_DAC, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(BIN_DAC, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(BIN_DAC, BIN_DAC, bin_dac)
COMPONENT_PROC_PATTERT(BIN_DAC, BIN_DAC, bin_dac)
