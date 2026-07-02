#include "i2s_full_duplex.h"

#include <string.h>

#include "code_generator.h"
#include "dma_config.h"
#include "dma_mcal.h"
#include "dma_types.h"
#ifdef HAS_ECHO_EFFECT
#include "echo_effect.h"
#include "echo_effect_isr.h"
#endif
#include "gpio_mcal.h"
#include "i2s_dma_mcal.h"
#include "i2s_mcal.h"
#include "log.h"
#include "num_to_str.h"
#include "timer_mcal.h"

COMPONENT_GET_NODE(I2sFullDuplex, i2s_full_duplex)
COMPONENT_GET_CONFIG(I2sFullDuplex, i2s_full_duplex)

DmaChannelHandle_t* I2sNumToDmaChannel(uint32_t i2s_num) {
    DmaChannelHandle_t* ChannelNode = NULL;
    I2sHandle_t* Node = I2sGetNode(i2s_num);
    if(Node) {
        ChannelNode = DmaPadGetNodeItem(Node->Dma);
    }
    return ChannelNode;
}

bool i2s_full_duplex_start_ll(I2sFullDuplexHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->on_off = true;
#ifdef HAS_ECHO_EFFECT
        res = echo_effect_reset(Node->echo_effect_num);
#endif
        res = i2s_api_write_dma(Node->i2s_tx_num, Node->Buffer, I2S_COMMON_BUFFER_CHANNELS_CNT, DMA_MODE_CIRCULAR);
        if(res) {
            Node->start_cnt++;
            Node->state = I2S_FULL_DUPLEX_STATE_TX;
        }

        DmaChannelHandle_t* ChannelNode = NULL;
        ChannelNode = I2sNumToDmaChannel(Node->i2s_tx_num);
        if(ChannelNode) {
            ChannelNode->CallBackHalf = DmaTxHalf;
            ChannelNode->CallBackDone = DmaTxDone;
        }

        if(res) {
            res = timer_ctrl(Node->timer_num, true);
        }
    }
    return res;
}

bool i2s_full_duplex_start(uint8_t num) {
    bool res = false;
    I2sFullDuplexHandle_t* Node = I2sFullDuplexGetNode(num);
    if(Node) {
        res = i2s_full_duplex_start_ll(Node);
    }
    return res;
}

bool i2s_full_duplex_stop_ll(I2sFullDuplexHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->stop_cnt++;
        Node->state = I2S_FULL_DUPLEX_STATE_IDLE;
        res = i2s_dma_ctrl(Node->i2s_tx_num, false);
        if(res) {
            res = i2s_dma_ctrl(Node->i2s_rx_num, false);
            if(res) {
                res = timer_ctrl(Node->timer_num, false);
            }
        }
    }
    return res;
}

bool i2s_full_duplex_stop(uint8_t num) {
    bool res = false;
    I2sFullDuplexHandle_t* Node = I2sFullDuplexGetNode(num);
    if(Node) {
        Node->on_off = false;
        res = i2s_full_duplex_stop_ll(Node);
    }
    return res;
}

static bool i2s_full_duplex_ctrl_ll(I2sFullDuplexHandle_t* Node, bool on_off) {
    bool res = false;
    if(Node) {
        if(on_off) {
            res = i2s_full_duplex_start_ll(Node);
        } else {
            res = i2s_full_duplex_stop_ll(Node);
        }
    }
    return res;
}

bool i2s_full_duplex_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    I2sFullDuplexHandle_t* Node = I2sFullDuplexGetNode(num);
    if(Node) {
        res = i2s_full_duplex_ctrl_ll(Node, on_off);
    }
    return res;
}

static bool i2s_full_duplex_init_custom(void) {
    bool res = true;
    return res;
}

bool i2s_full_duplex_init_one(uint8_t num) {
    bool res = false;
    const I2sFullDuplexConfig_t* Config = I2sFullDuplexGetConfig(num);
    if(Config) {
        LOG_WARNING(I2S_FULL_DUPLEX, "%s", I2sFullDuplexToStr(Config));
        I2sFullDuplexHandle_t* Node = I2sFullDuplexGetNode(num);
        if(Node) {
            Node->DebugPadRx = Config->DebugPadRx;
            Node->DebugPadTx = Config->DebugPadTx;
            Node->timer_num = Config->timer_num;
            Node->echo_effect_num = Config->echo_effect_num;
            Node->i2s_rx_num = Config->i2s_rx_num;
            Node->i2s_tx_num = Config->i2s_tx_num;
            Node->name = Config->name;

            Node->state = I2S_FULL_DUPLEX_STATE_IDLE;
            Node->prev_state = I2S_FULL_DUPLEX_STATE_IDLE;
            Node->init_done = true;
            Node->valid = true;
            memset(Node->Buffer, 0, sizeof(Node->Buffer));

            res = i2s_proc_ctrl(Config->i2s_rx_num, false);
            if(res) {
                res = i2s_proc_ctrl(Config->i2s_tx_num, false);
            }

            if(res) {
                res = i2s_full_duplex_stop(num);
            }

            if(res) {
                double period_s = ((double)I2S_COMMON_BUFFER_SAMPLE_CNT) / 48000.0;
                LOG_INFO(I2S_FULL_DUPLEX, "TimerPeriod:%s s", DoubleToStr(period_s));
                res = timer_period_set_s(Node->timer_num, period_s);
            }
        }
    }
    return res;
}

static bool i2s_full_duplex_is_active(I2sFullDuplexHandle_t* Node) {
    bool res = false;
    switch(Node->state) {
    case I2S_FULL_DUPLEX_STATE_RX:
    case I2S_FULL_DUPLEX_STATE_TX:
    case I2S_FULL_DUPLEX_STATE_RX_TX: {
        res = true;
    } break;
    default: {
        res = false;
    } break;
    }
    return res;
}

bool i2s_full_duplex_proc_one(uint8_t num) {
    bool res = false;
    I2sFullDuplexHandle_t* Node = I2sFullDuplexGetNode(num);
    if(Node) {
        if(Node->state != Node->prev_state) {
            LOG_INFO(I2S_FULL_DUPLEX, "%s->%s", I2sFullDuplexStateToStr(Node->prev_state),
                     I2sFullDuplexStateToStr(Node->state));
        }
        res = i2s_full_duplex_is_active(Node);
        if(false == res) {
            res = i2s_full_duplex_start(num);
        }
        Node->prev_state = Node->state;
        res = true;
    }

    return res;
}

COMPONENT_INIT_PATTERT(I2S_FULL_DUPLEX, I2S_FULL_DUPLEX, i2s_full_duplex)
COMPONENT_PROC_PATTERT(I2S_FULL_DUPLEX, I2S_FULL_DUPLEX, i2s_full_duplex)
