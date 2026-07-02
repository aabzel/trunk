#include "i2s_full_duplex_isr.h"

#include <math.h>

#include "dma_config.h"
#ifdef HAS_ECHO_EFFECT
#include "echo_effect_isr.h"
#endif
#include "gpio_mcal.h"
#include "i2s_dma_mcal.h"
#include "i2s_full_duplex.h"
#ifdef HAS_FIR
#include "fir.h"
#endif

#ifdef HAS_FIR_INT
#include "fir_int.h"
#endif
#include "time_mcal.h"
#include "timer_mcal.h"

#define CHANNEL_INDEX_L (s * 2)
#define CHANNEL_INDEX_R (s * 2 + 1)
#define I2S_COMMON_BUFFER_SAMPLE_QUOTER (I2S_COMMON_BUFFER_SAMPLE_CNT / 4)

bool i2s_full_duplex_data_proc_ll(I2sFullDuplexHandle_t* Node, uint32_t part) {
    bool res = false;

#ifdef HAS_I2S_FULL_DUPLEX_DEBUG
    Pad_t DebugPad = {
        .port = PORT_B,
        .pin = 11,
    };
    gpio_logic_level_set(DebugPad.byte, GPIO_LVL_HI);
#endif

    uint32_t start = I2S_COMMON_BUFFER_SAMPLE_QUOTER * part;
    uint32_t end = start + I2S_COMMON_BUFFER_SAMPLE_QUOTER - 1;
    SampleType_t SampleOut = 0;
#ifdef HAS_FIR
    FirSample_t fir_sample;
    FirHandle_t* FirNode = FirGetNode(1);
#endif

#ifdef HAS_FIR_INT
    FirIntSample_t fir_sample;
    FirIntHandle_t* FirIntNode = FirIntGetNode(1);
#endif
    SampleType_t SampleCommon = 0;
    uint32_t s = 0;
    for(s = start; s <= end; s++) {
        // SampleType_t SampleLeft = Node->Buffer[CHANNEL_INDEX_L];
        // SampleType_t SampleRight = Node->Buffer[CHANNEL_INDEX_R];
        // SampleCommon =(SampleType_t)    (( ((int32_t)SampleLeft )+ ((int32_t)SampleRight) )/ 2);
        SampleCommon = Node->Buffer[CHANNEL_INDEX_L];

#ifdef HAS_FIR
        fir_sample = 0;
        res = fir_proc_in_out_ll(FirNode, ((FirSample_t)SampleCommon), &fir_sample);
        if(res) {
            if(fabsf(fir_sample) < 32768) {
                SampleOut = (SampleType_t)fir_sample;
            } else {
                SampleOut = 0;
            }
        } else {
            Node->error_cnt++;
        }
#else  /*HAS_FIR*/
        SampleOut = SampleCommon;
#endif /*HAS_FIR*/

#ifdef HAS_FIR_INT
        fir_sample = (FirIntSample_t)SampleCommon;
        res = fir_int_proc_in_out_ll(FirNode, ((FirIntSample_t)SampleCommon), &fir_sample);
        if(res) {
            SampleOut = (SampleType_t)fir_sample;
        } else {
            Node->error_cnt++;
        }
#endif

#ifdef HAS_ECHO_EFFECT
        res = echo_effect_proc_sample(Node->echo_effect_num, SampleCommon, &SampleOut);
#endif
        if(res) {
            Node->Buffer[CHANNEL_INDEX_L] = SampleOut;
            Node->Buffer[CHANNEL_INDEX_R] = SampleOut;
        } else {
            Node->error_cnt++;
        }
    }

#ifdef HAS_I2S_FULL_DUPLEX_DEBUG
    gpio_logic_level_set(DebugPad.byte, GPIO_LVL_LOW);
#endif

    return res;
}

static bool i2s_full_duplex_proc_tx_ll(I2sFullDuplexHandle_t* Node, I2sFullDuplexInputs_t input) {
    bool res = false;
    switch((uint32_t)input) {
    case I2S_FULL_DUPLEX_INPUTS_STOP: {
        res = i2s_full_duplex_stop_ll(Node);
    } break;
    case I2S_FULL_DUPLEX_INPUTS_RX_DONE:
    case I2S_FULL_DUPLEX_INPUTS_RX_HALF: {
        Node->state = I2S_FULL_DUPLEX_STATE_RX_TX;
        res = true;
    } break;

    case I2S_FULL_DUPLEX_INPUTS_TX_HALF: {
        Node->state = I2S_FULL_DUPLEX_STATE_TX;
        // res = i2s_dma_ctrl(  Node->i2s_rx_num, true);
        res = i2s_api_read_dma(Node->i2s_rx_num, Node->Buffer, I2S_COMMON_BUFFER_CHANNELS_CNT, DMA_MODE_CIRCULAR);
        DmaChannelHandle_t* ChannelNode = NULL;
        ChannelNode = I2sNumToDmaChannel(Node->i2s_rx_num);
        if(ChannelNode) {
            ChannelNode->CallBackHalf = DmaRxHalf;
            ChannelNode->CallBackDone = DmaRxDone;
        }

    } break;
    case I2S_FULL_DUPLEX_INPUTS_START:
    case I2S_FULL_DUPLEX_INPUTS_TX_DONE: {
        res = true;
    } break;
    }
    return res;
}
static bool i2s_full_duplex_proc_rx_ll(I2sFullDuplexHandle_t* Node, I2sFullDuplexInputs_t input) {
    bool res = false;

    switch((uint32_t)input) {
    case I2S_FULL_DUPLEX_INPUTS_RX_DONE:
    case I2S_FULL_DUPLEX_INPUTS_START: {
        res = true;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_STOP: {
        res = i2s_full_duplex_stop_ll(Node);
    } break;

    case I2S_FULL_DUPLEX_INPUTS_RX_HALF: {
        Node->state = I2S_FULL_DUPLEX_STATE_RX;
        // res = i2s_dma_ctrl(  Node->i2s_tx_num, true);
        res = i2s_api_write_dma(Node->i2s_tx_num, Node->Buffer, I2S_COMMON_BUFFER_CHANNELS_CNT, DMA_MODE_CIRCULAR);
        DmaChannelHandle_t* ChannelNode = NULL;
        ChannelNode = I2sNumToDmaChannel(Node->i2s_tx_num);
        if(ChannelNode) {
            ChannelNode->CallBackHalf = DmaTxHalf;
            ChannelNode->CallBackDone = DmaTxDone;
        }

    } break;

    case I2S_FULL_DUPLEX_INPUTS_TX_DONE:
    case I2S_FULL_DUPLEX_INPUTS_TX_HALF: {
        Node->state = I2S_FULL_DUPLEX_STATE_RX_TX;
        res = true;
    } break;

    default: {
        res = i2s_full_duplex_stop_ll(Node);
    } break;
    }

    return res;
}

static uint8_t i2s_full_duplex_input_to_timer_percent(I2sFullDuplexInputs_t input) {
    uint8_t timer_percent = 0;
    switch(input) {
    case I2S_FULL_DUPLEX_INPUTS_RX_HALF: {
        timer_percent = 25;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_TX_DONE: {
        timer_percent = 25;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_RX_DONE: {
        timer_percent = 75;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_TX_HALF: {
        timer_percent = 75;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_START: {
        timer_percent = 0;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_STOP: {
        timer_percent = 0;
    } break;
    default:
        timer_percent = 0;
        break;
    }
    return timer_percent;
}

static bool i2s_full_duplex_proc_rx_tx_ll(I2sFullDuplexHandle_t* Node, I2sFullDuplexInputs_t input) {
    bool res = false;
    switch((uint32_t)input) {
    case I2S_FULL_DUPLEX_INPUTS_RX_HALF: {
        Node->state = I2S_FULL_DUPLEX_STATE_RX_TX;
        res = true;
        // res = i2s_dma_restart(Node->i2s_tx_num);
    } break;
    case I2S_FULL_DUPLEX_INPUTS_TX_HALF: {
        Node->state = I2S_FULL_DUPLEX_STATE_RX_TX;
        res = i2s_dma_restart(Node->i2s_rx_num);
    } break;

    case I2S_FULL_DUPLEX_INPUTS_START: {
        res = true;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_STOP: {
        res = i2s_full_duplex_stop_ll(Node);
    } break;
    case I2S_FULL_DUPLEX_INPUTS_RX_DONE:
    case I2S_FULL_DUPLEX_INPUTS_TX_DONE: {
        res = true;
    } break;
    default: {
        Node->state = I2S_FULL_DUPLEX_STATE_IDLE;
        res = i2s_full_duplex_stop_ll(Node);
    } break;
    }
    return res;
}

static bool i2s_full_duplex_proc_idle_ll(I2sFullDuplexHandle_t* Node, I2sFullDuplexInputs_t input) {
    bool res = false;
    switch((uint32_t)input) {
    case I2S_FULL_DUPLEX_INPUTS_STOP: {
        res = true;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_RX_HALF: {
        Node->state = I2S_FULL_DUPLEX_STATE_RX;
        res = true;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_RX_DONE: {
        Node->state = I2S_FULL_DUPLEX_STATE_RX;
        res = true;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_TX_HALF: {
        Node->state = I2S_FULL_DUPLEX_STATE_TX;
        res = true;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_TX_DONE: {
        Node->state = I2S_FULL_DUPLEX_STATE_RX;
        res = true;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_START: {
        res = i2s_full_duplex_start_ll(Node);
    } break;
    default: {
        Node->state = I2S_FULL_DUPLEX_STATE_IDLE;
    } break;
    }
    return res;
}

static bool i2s_full_duplex_cnt_input(I2sFullDuplexHandle_t* Node) {
    bool res = false;
    switch(Node->input) {
    case I2S_FULL_DUPLEX_INPUTS_RX_HALF: {
        Node->rx_half_cnt++;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_RX_DONE: {
        Node->rx_done_cnt++;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_TX_HALF: {
        Node->tx_half_cnt++;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_TX_DONE: {
        Node->tx_done_cnt++;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_START: {
        Node->start_cnt++;
    } break;
    case I2S_FULL_DUPLEX_INPUTS_STOP: {
        Node->stop_cnt++;
    } break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool i2s_full_duplex_run_proc_ll(I2sFullDuplexHandle_t* Node, I2sFullDuplexInputs_t input) {
    bool res = false;
    switch(input) {
    case I2S_FULL_DUPLEX_INPUTS_RX_HALF: {
        res = i2s_full_duplex_data_proc_ll(Node, 1);
    } break;
    case I2S_FULL_DUPLEX_INPUTS_RX_DONE: {
        res = i2s_full_duplex_data_proc_ll(Node, 3);
    } break;

#if 0
        case I2S_FULL_DUPLEX_INPUTS_TX_DONE: {
        	// or I2S_FULL_DUPLEX_INPUTS_RX_HALF
            res = i2s_full_duplex_data_proc_ll(Node, 1);
        } break;
        case I2S_FULL_DUPLEX_INPUTS_TX_HALF: {
        	// or I2S_FULL_DUPLEX_INPUTS_RX_DONE
            res = i2s_full_duplex_data_proc_ll(Node, 3);
        } break;
#endif
    default: {
    } break;
    } // switch(input)
    return res;
}

/*that is isr code*/
bool i2s_full_duplex_proc_input(uint8_t num, I2sFullDuplexInputs_t input) {
    bool res = false;
    I2sFullDuplexHandle_t* Node = I2sFullDuplexGetNode(num);
    if(Node) {
        if(Node->on_off) {
#ifdef HAS_I2S_FULL_DUPLEX_DEBUG
            switch(input) {
            case I2S_FULL_DUPLEX_INPUTS_RX_HALF: {
                gpio_logic_level_set(Node->DebugPadRx.byte, GPIO_LVL_HI);
            } break;
            case I2S_FULL_DUPLEX_INPUTS_RX_DONE: {
                gpio_logic_level_set(Node->DebugPadRx.byte, GPIO_LVL_LOW);
            } break;
            case I2S_FULL_DUPLEX_INPUTS_TX_HALF: {
                gpio_logic_level_set(Node->DebugPadTx.byte, GPIO_LVL_HI);
            } break;
            case I2S_FULL_DUPLEX_INPUTS_TX_DONE: {
                gpio_logic_level_set(Node->DebugPadTx.byte, GPIO_LVL_LOW);
            } break;
            default:
                break;
            }
#endif /*HAS_I2S_FULL_DUPLEX_DEBUG*/
            uint8_t counter_percent = i2s_full_duplex_input_to_timer_percent(input);
            res = timer_counter_set_percent_u(Node->timer_num, counter_percent);

            Node->input = input;
            Node->proc_cnt++;
            res = i2s_full_duplex_cnt_input(Node);
            switch(Node->state) {
            case I2S_FULL_DUPLEX_STATE_IDLE: {
                res = i2s_full_duplex_proc_idle_ll(Node, input);
            } break;
            case I2S_FULL_DUPLEX_STATE_TX: {
                res = i2s_full_duplex_proc_tx_ll(Node, input);
            } break;
            case I2S_FULL_DUPLEX_STATE_RX: {
                res = i2s_full_duplex_proc_rx_ll(Node, input);
            } break;
            case I2S_FULL_DUPLEX_STATE_RX_TX: {
                res = i2s_full_duplex_proc_rx_tx_ll(Node, input);
            } break;
            default: {

                Node->state = I2S_FULL_DUPLEX_STATE_IDLE;
            } break;
            }

            res = i2s_full_duplex_run_proc_ll(Node, input);
        }
#if 0
        uint32_t cur_up_time = time_get_ms32();
        uint32_t  diff_ms =cur_up_time- Node->last_input_time_stamp;
        if(1000<diff_ms){
            Node->state = I2S_FULL_DUPLEX_STATE_IDLE;
        }
        Node->last_input_time_stamp = time_get_ms32();
#endif
    }
    return res;
}
