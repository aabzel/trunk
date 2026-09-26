#include "sw_uart_mcal.h"

#include <math.h>

#include "lib_iqueue.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "core_driver.h"
#include "fifo_char.h"
#include "iqueue.h"
#include "timer_mcal.h"
#include "bin_dac_mcal.h"
#include "bin_adc_mcal.h"
#include "gpio_mcal.h"
#include "array.h"

#ifdef HAS_STRING_READER
#include "string_reader.h"
#endif

#ifdef HAS_EXT_INT
#include "ext_int_mcal.h"
#endif

COMPONENT_GET_NODE(SwUart, sw_uart)
COMPONENT_GET_CONFIG(SwUart, sw_uart)

static bool SwUartIsValidConfigRx(const SwUartConfig_t* const Config) {
    bool res = true;

    bool l_res = true;
    l_res = timer_is_valid(Config->rx_timer_num);
    ifn(l_res) {
        LOG_ERROR(SW_UART, "SW_UART_%u,rx_timer_num,Err", Config->num);
        res = false;
    }

    l_res = bin_adc_is_valid_num(Config->bin_adc_num);
    ifn(l_res) {
        LOG_ERROR(SW_UART, "SW_UART_%u,bin_adc_num,Err", Config->num);
        res = false;
    }

    ifn(0<Config->rx_fifo_mem_size) {
        LOG_ERROR(SW_UART, "SW_UART_%u,rx_fifo_mem_size,Err", Config->num);
        res = false;
    }

    ifn(Config->RxFifoMem) {
        LOG_ERROR(SW_UART, "SW_UART_%u,RxFifoMem,Err", Config->num);
        res = false;
    }

    ifn(Config->rx_over_sampling < SW_UART_BIT_PER_FRAME_MAX) {
        LOG_ERROR(SW_UART, "SW_UART_%u,rxOverSampling,Big,Err", Config->num);
        res = false;
    }

    l_res = gpio_is_valid_pad(Config->Rx);
    ifn(l_res) {
        LOG_ERROR(SW_UART, "SW_UART_%u,RxPad,Err", Config->num);
        res = false;
    }

    ifn(1<=Config->rx_over_sampling) {
        LOG_ERROR(SW_UART, "SW_UART_%u,RxOverSampling,Err", Config->num);
        res = false;
    }
    return res;
}

static bool SwUartIsValidConfigTx(const SwUartConfig_t* const Config) {
    bool res = true;
    bool l_res = true;
    l_res = timer_is_valid(Config->tx_timer_num);
    ifn(l_res) {
        LOG_ERROR(SW_UART, "SW_UART_%u,tx_timer_num,Err", Config->num);
        res = false;
    }

    l_res = gpio_is_valid_pad(Config->Tx);
    ifn(l_res) {
        LOG_ERROR(SW_UART, "SW_UART_%u,TxPad,Err", Config->num);
        res = false;
    }

    ifn(1<Config->tx_fifo_mem_size) {
        LOG_ERROR(SW_UART, "SW_UART_%u,tx_fifo_mem_size,Big,Err", Config->num);
        res = false;
    }

    ifn(Config->TxFifoMem) {
        LOG_ERROR(SW_UART, "SW_UART_%u,TxFifoMem,Big,Err", Config->num);
        res = false;
    }

    ifn(Config->tx_over_sampling < SW_UART_BIT_PER_FRAME_MAX) {
        LOG_ERROR(SW_UART, "SW_UART_%u,txOverSampling,Big,Err", Config->num);
        res = false;
    }

    ifn(1<=Config->tx_over_sampling) {
        LOG_ERROR(SW_UART, "SW_UART_%u,TxOverSampling,Err", Config->num);
        res = false;
    }

    l_res = bin_dac_is_valid_num(Config->bin_dac_num);
    ifn(l_res) {
        LOG_ERROR(SW_UART, "SW_UART_%u,bin_dac_num,Err", Config->num);
        res = false;
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool SwUartIsValidConfig(const SwUartConfig_t* const Config) {
    bool res = false;
    if (Config) {
        res = true;
        bool l_res = true;

        l_res = SwUartIsValidConfigRx(Config);
        ifn(l_res) {
            LOG_ERROR(SW_UART, "SW_UART_%u,Rx,Err", Config->num);
            res = false;
        }

        l_res = SwUartIsValidConfigTx(Config);
        ifn(l_res) {
            LOG_ERROR(SW_UART, "SW_UART_%u,Tx,Err", Config->num);
            res = false;
        }

        ifn(Config->name) {
            LOG_ERROR(SW_UART, "SW_UART_%u,Name,Err", Config->num);
            res = false;
        }

        ifn(0<Config->baud_rate) {
            LOG_ERROR(SW_UART, "SW_UART_%u,baud_rate,Err", Config->num);
            res = false;
        }

        ifn(0<Config->stop_bit_cnt) {
            LOG_ERROR(SW_UART, "SW_UART_%u,stop_bit_cnt,Err", Config->num);
            res = false;
        }

    }
    return res;
}

uint8_t sw_uart_last_rx_get(const uint8_t num) {
    uint8_t rx_byte = 0;
    SwUartHandle_t* Node = SwUartGetNode(num);
    if(Node) {
        rx_byte = Node->rx_byte;
    }
    return rx_byte;
}

bool sw_uart_last_rx_set(const uint8_t num, const uint8_t data) {
    bool res = false;
    SwUartHandle_t* Node = SwUartGetNode(num);
    if(Node) {
        Node->rx_byte=data;
        res = true;
    }
    return res;
}


bool sw_uart_baudrate_get(uint8_t num, uint32_t* const baudrate){
    bool res = false;
    return res;
}

bool sw_uart_baudrate_set(uint8_t num, const uint32_t baudrate){
    bool res = false;
    return res;
}

#define SW_UART_BITS_PER_FRAME 32
uint32_t sw_uart_compose_samples(const SwUartFrameTx_t Frame,
                                 const uint32_t tx_over_sampling,
                                 uint8_t* const tx_samples) {
    uint32_t tx_sample_cnt = 0;
    if( 0 < tx_over_sampling ) {
        tx_sample_cnt = SW_UART_BITS_PER_FRAME * tx_over_sampling;
        memset(tx_samples, 1, tx_sample_cnt);
        uint32_t offset = 0;
        for(offset=0; offset < SW_UART_BITS_PER_FRAME; offset++) {
            uint8_t bit_i = GET_BIT_NUM(Frame.dword, offset);
            memset(&tx_samples[offset*tx_over_sampling], bit_i , tx_over_sampling);
        }
    }
    return tx_sample_cnt;
}




static bool sw_uart_mcal_send_byte_ll(SwUartHandle_t* const Node, const uint8_t byte) {
    bool res = false;
    SwUartFrameTx_t Frame = { 0 };
    Frame.dword = 0xFFFFFFFF;
    Frame.start_bit = 0;
    Frame.byte = byte;
    Frame.stop1 = 1;
    Frame.stop2 = 1;
    Frame.parity = 1; // TODO

    uint32_t tx_sample_cnt = sw_uart_compose_samples(Frame, Node->tx_over_sampling, Node->txSamples);
    if (0 < tx_sample_cnt) {
            res = bin_dac_push_samples(Node->bin_dac_num, Node->txSamples, tx_sample_cnt);
            if (res) {
                uint32_t part_size = 0 ;
                part_size += tx_sample_cnt;
                res = bin_dac_part_size_set(Node->bin_dac_num, part_size);
                res = bin_dac_tx_next(Node->bin_dac_num);
                if (!res) {
                    Node->error_cnt++;
                }
            } else {
                Node->error_cnt++;
            }


        //res = bin_dac_sample_tx(Node->bin_dac_num, Node->txSamples, SW_UART_SAMPLE_PER_FRAME);
#ifdef HAS_BIN_DAC
#endif
    }
    return res;
}

bool sw_uart_tx_next_ll(SwUartHandle_t* const Node) {
    bool res = false;
    uint32_t count = fifo_get_count(&Node->TxByteFifo);
    if (count) {
        uint32_t i = 0 ;
        for (i = 0; i < count; i++) {
            uint8_t tx_byte = 0;
            res = fifo_peek(&Node->TxByteFifo, &tx_byte);
            if (res) {
                res = sw_uart_mcal_send_byte_ll(Node, tx_byte);
                if (res) {
                    res = fifo_pull(&Node->TxByteFifo, &tx_byte);
                } else {
                    break;
                }
            }
        }
    }
    return res;
}

bool sw_uart_tx_next(uint8_t num) {
    bool res = false;
    SwUartHandle_t* Node = SwUartGetNode(num);
    if(Node) {
        res = sw_uart_tx_next_ll(Node) ;
    }
    return res;
}

bool sw_uart_mcal_send(uint8_t num, const uint8_t* const data, uint32_t size) {
    bool res = false;
    SwUartHandle_t *Node = SwUartGetNode(num);
    if (Node) {
        res = fifo_push_array(&Node->TxByteFifo, data, size);
        res = sw_uart_tx_next_ll(Node);
#if 0
        uint32_t i = 0;
        for (i = 0; i < size; i++) {
            res = sw_uart_mcal_send_byte_ll(Node, data[i]);
        }
#endif
    }
    return res;
}




bool sw_uart_init_custom(void) {
    bool res = false;
    LOG_INFO(SW_UART, "Version:%s", SW_UART_VERSION);
    LOG_INFO(SW_UART, "SW_UART_MAX_SAMPLE_PER_BIT:%u", SW_UART_MAX_SAMPLE_PER_BIT);
    LOG_INFO(SW_UART, "SW_UART_BIT_PER_FRAME:%u", SW_UART_BIT_PER_FRAME);
    LOG_INFO(SW_UART, "SW_UART_SAMPLE_PER_FRAME:%u", SW_UART_SAMPLE_PER_FRAME);
    return res;
}

bool sw_uart_init_common(const SwUartConfig_t* const Config, SwUartHandle_t* const Node) {
    bool res = false;
    if (Config) {
        if (Node) {
            Node->tx_fifo_mem_size = Config->tx_fifo_mem_size;
            Node->TxFifoMem = Config->TxFifoMem;
            Node->tx_timer_num = Config->tx_timer_num;
            Node->Tx = Config->Tx;
            Node->bin_dac_num = Config->bin_dac_num;
            Node->tx_over_sampling = Config->tx_over_sampling;

            Node->rx_fifo_mem_size = Config->rx_fifo_mem_size;
            Node->RxFifoMem = Config->RxFifoMem;
            Node->Rx = Config->Rx;
            Node->rx_timer_num = Config->rx_timer_num;
            Node->rx_over_sampling = Config->rx_over_sampling;
            Node->bin_adc_num = Config->bin_adc_num;

            Node->name = Config->name;
            Node->baud_rate = Config->baud_rate;
            Node->parity_check = Config->parity_check;
            Node->stop_bit_cnt = Config->stop_bit_cnt;
            Node->baud_rate = Config->baud_rate;
            res = true;
        }
    }
    return res;
}

bool sw_uart_init_node(SwUartHandle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->valid = true;
        Node->init = true;
        Node->bit_duration_us = 1000000/Node->baud_rate;
        Node->max_frame_duration_us = Node->bit_duration_us*SW_UART_BIT_PER_FRAME;
        Node->rx_frame_state = SW_UART_RX_FRAME_STATE_IDLE;
        res = true;
    }
    return res;
}

#ifdef HAS_EXT_INT
GpioLogicLevel_t gpio_event_to_state(const PinIntDrop_t drop) {
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    switch(drop) {
        case PIN_INT_DROP_FALLING:logic_level = GPIO_LVL_LOW; break;
        case PIN_INT_DROP_RISING: logic_level = GPIO_LVL_HI;  break;
        default:logic_level = GPIO_LVL_UNDEF; break;
    }
    return logic_level;
}
#endif

uint32_t calc_bits_inside(const uint32_t event_pause_us,
                          const uint32_t bit_duration_us) {
    uint32_t rx_bit_diff = 0 ;
    if(bit_duration_us) {
        float arg = ((float )event_pause_us) / ((float )bit_duration_us);
        rx_bit_diff = (uint32_t) roundf(arg);
    }
    return rx_bit_diff;
}
#ifdef HAS_SW_UART_EVENT_PROC
static bool sw_uart_proc_bit(SwUartHandle_t* Node, uint8_t bit_value){
    bool res = false;
    LOG_DEBUG(SW_UART_BIT, "RxBit[%u]=%u",Node->bit_i, bit_value);
    if(Node->bit_i < SW_UART_BIT_PER_FRAME) {
        Node->RxBit[Node->bit_i]=bit_value;
        Node->bit_i++;
        if(SW_UART_BIT_PER_FRAME_PN_D8_S1<=Node->bit_i){
            Node->RxFrame.start_bit = Node->RxBit[0];
            Node->RxFrame.parity = 0;
            Node->RxFrame.res = 0;

            Node->RxFrame.byte= bit_u8_ctrl(Node->RxFrame.byte, 0,Node->RxBit[1]) ;
            Node->RxFrame.byte= bit_u8_ctrl(Node->RxFrame.byte, 1,Node->RxBit[2]) ;
            Node->RxFrame.byte= bit_u8_ctrl(Node->RxFrame.byte, 2,Node->RxBit[3]) ;
            Node->RxFrame.byte= bit_u8_ctrl(Node->RxFrame.byte, 3,Node->RxBit[4]) ;
            Node->RxFrame.byte= bit_u8_ctrl(Node->RxFrame.byte, 4,Node->RxBit[5]) ;
            Node->RxFrame.byte= bit_u8_ctrl(Node->RxFrame.byte, 5,Node->RxBit[6]) ;
            Node->RxFrame.byte= bit_u8_ctrl(Node->RxFrame.byte, 6,Node->RxBit[7]) ;
            Node->RxFrame.byte= bit_u8_ctrl(Node->RxFrame.byte, 7,Node->RxBit[8]) ;

            Node->RxFrame.stop= bit_u8_ctrl(Node->RxFrame.stop, 0,Node->RxBit[9]) ;
            Node->RxFrame.stop= bit_u8_ctrl(Node->RxFrame.stop, 1,Node->RxBit[10]) ;
            if(1<=Node->RxFrame.stop) {
                LOG_DEBUG(SW_UART_BIT, "RxFrame:[%s]",  SwUartFrameToStr(Node->RxFrame));
            }
        }
    } else {
        Node->bit_i=0;
    }
    return res;
}
#endif

#ifdef HAS_SW_UART_EVENT_PROC
static bool sw_uart_proc_event(SwUartHandle_t* Node, ExtIntEvent_t* Event) {
    bool res = false;
    Node->Event=*Event;
    Node->rx_state = gpio_event_to_state(Event->drop);
    Node->event_pause_us = Event->timestamp_us - Node->PrevEvent.timestamp_us;
    if(Node->max_frame_duration_us <Node->event_pause_us) {
        Node->bit_i=0;
    }

    Node->rx_bit_diff = calc_bits_inside(Node->event_pause_us, Node->bit_duration_us);

    if(Node->rx_bit_diff< 10) {
        uint32_t i = 0;
        for(i = 0; i < Node->rx_bit_diff; i++) {
            sw_uart_proc_bit(Node,(uint8_t)  Node->rx_state);
        }
    } else {
        sw_uart_proc_bit(Node, (uint8_t) Node->rx_state);
    }

    LOG_DEBUG(SW_UART, "%s", SwUartNodeToStr(Node));
    Node->PrevEvent = *Event;
    return res;
}
#endif

bool sw_uart_decimate(SwUartHandle_t* const Node) {
    bool res = true;
    res = true;
    SwUartFrameRx_t rxFrame;
    rxFrame.dword = 0;
    uint32_t b = 0;
    for (b = 0; b < SW_UART_BIT_PER_FRAME_MAX; b++) {
        uint8_t bit_i = array_bin_vote_u8(&Node->rxFrameSamples[b * Node->rx_over_sampling],
                                          Node->rx_over_sampling);
        Node->RxFrame[b] = bit_i;
        rxFrame.dword = bit_u32_ctrl(rxFrame.dword, b, bit_i);
    }

    if ( 0==rxFrame.start_bit ) {
        Node->rx_byte = rxFrame.byte;
        LOG_DEBUG(SW_UART, "RxByte,%s", SwUartNodeToStr(Node));
        res = fifo_push(&Node->RxByteFifo, Node->rx_byte);
    }

    return res;
}

bool sw_uart_proc_bit_idle(SwUartHandle_t* const Node) {
    bool res = false;
    if (0 == Node->sample) {
        Node->rx_frame_state = SW_UART_RX_FRAME_STATE_REC;
        Node->rx_frame_cnt = 0;
        Node->rxFrameSamples[0] = Node->sample;
        LOG_DEBUG(SW_UART, "StartBit,%s", SwUartNodeToStr(Node));
        res = true;
    }
    return res;
}

bool sw_uart_proc_bit_rec(SwUartHandle_t* const Node) {
    bool res = true;
    Node->rx_frame_cnt++;
    uint32_t frame_size_sample = Node->rx_over_sampling * SW_UART_BIT_PER_FRAME_MAX;
    if( frame_size_sample < Node->rx_frame_cnt) {
        res = sw_uart_decimate(Node);
        Node->rx_frame_cnt = 0;
        Node->rx_frame_state = SW_UART_RX_FRAME_STATE_IDLE;
    } else {
        Node->rxFrameSamples[Node->rx_frame_cnt] = Node->sample;
    }
    return res;
}

bool sw_uart_proc_bit(SwUartHandle_t* const Node, uint8_t sample) {
    bool res = false;
    Node->sample = sample;
    switch(Node->rx_frame_state) {
        case SW_UART_RX_FRAME_STATE_IDLE: {
            res = sw_uart_proc_bit_idle(Node);
        } break;

        case SW_UART_RX_FRAME_STATE_REC: {
            res = sw_uart_proc_bit_rec(Node);
        } break;

        default:{
            Node->rx_frame_state = SW_UART_RX_FRAME_STATE_IDLE;
            res = false;
        } break;
    }
    return res;
}

bool sw_uart_proc_part(SwUartHandle_t* Node, uint8_t part) {
    bool res = false;
    BinAdcHandle_t *BinAdc = BinAdcGetNode(Node->bin_adc_num);
    if(BinAdc) {
        uint32_t s = 0;
        uint32_t sample_cnt = BinAdc->data_array_size / 2;
        uint32_t offset = part*sample_cnt;
        for (s = 0; s < sample_cnt; s++) {
            uint8_t sample = GET_BIT_NUM(BinAdc->GpioPortDataArray[offset+s], Node->Rx.pin);
            res = sw_uart_proc_bit(Node, sample);
        }
        Node->rx_action = SW_UART_RX_ACTION_PROC_DONE;
    }
    return res;
}

void sw_uart_putc(void* stream_ptr, char ch) {
    sw_uart_mcal_send(1, (uint8_t*)&ch, 1);
}

void sw_uart_puts(void* stream_ptr, const char* str, int32_t len) {
    if(str) {
        if(len) {
            sw_uart_mcal_send(1, (uint8_t*)str, len);
        }
    }
}

bool sw_uart_writer_transmit(void* base) {
    bool res = false;
    WriterHandle_t* Writer = (WriterHandle_t*)base;
    if(Writer) {
        strcpy((char*)Writer->data, "");
        uint32_t out_len = 0;
        Writer->in_transmit = 0;
        res = fifo_pull_array(&Writer->fifo, Writer->data, 200, &out_len);
        if(false == res) {
            Writer->fifo.err_cnt++;
        } else {
            Writer->in_transmit = out_len;
        }
        if(0 < Writer->in_transmit) {
            Writer->tx_cnt += Writer->in_transmit;
            if(Writer->enable) {
                res = sw_uart_mcal_send(Writer->inter_face.num, (uint8_t*)Writer->data, Writer->in_transmit);
            }
            Writer->in_transmit = 0;
        }
    }
    return res;
}


bool sw_uart_proc_rx(SwUartHandle_t* Node) {
    bool res = false;
    switch (Node->rx_action) {
        case SW_UART_RX_ACTION_PROC1: {
            res = sw_uart_proc_part(Node, 0);
        } break;

        case SW_UART_RX_ACTION_PROC2: {
            res = sw_uart_proc_part(Node, 1);
        } break;

        default: {
        } break;
    }

    uint32_t count = fifo_get_count(&Node->RxByteFifo);
    if (0 < count) {
        uint32_t i = 0;
        for (i = 0; i < count; i++) {
            uint8_t rx_byte = 0;
            res = fifo_pull(&Node->RxByteFifo, &rx_byte);
            if (res) {
#ifdef HAS_STRING_READER
                InterfaceType_t interface_if = {0};
                interface_if.interface_name = INTERFACE_NAME_SW_UART;
                interface_if.num = Node->num;
                res = string_reader_rx_byte(interface_if, rx_byte);
#endif

                LOG_DEBUG(SW_UART, "RxByte:0x%02x", rx_byte);
            }
        }
    }

    return res;
}


bool sw_uart_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(SW_UART, "SW_UART_%u,Proc", num);
    SwUartHandle_t *Node = SwUartGetNode(num);
    if(Node) {
        res = sw_uart_proc_rx(Node);
#ifdef HAS_SW_UART_EVENT_PROC
        ExtIntHandle_t *Rx = ExtIntPadToNode(Node->Rx);
        if(Rx) {
            size_t size = 0;
            i_status ret = iqueue_size(&Rx->iQueue, &size);
            res = iqueue_ret_res(ret);
            if(res) {
                if(0 < size) {
                    LOG_DEBUG(SW_UART, "%sRxFiFoSz:%u", size);
                    uint32_t i = 0;
                    for(i=0; i < size; i++) {
                        ExtIntEvent_t Event = { 0 };
                        enter_critical();
                        ret = iqueue_dequeue((iqueue_t*) &Rx->iQueue, (void*) &Event);
                        exit_critical();
                        if(I_OK==ret) {
                            //LOG_DEBUG(SW_UART, "%s[%s]", ExtIntNodeToStr(Rx), ExtIntEventToStr(&Event, Rx));
                            res = sw_uart_proc_event(Node, &Event);
                            Node->event_cnt++;
                            Rx->prev_event_time_us = Event.timestamp_us;
                            Rx->PrevEvent = Event;
                        }
                    }
                }
            }
        }
#endif
        Node->spin++;
    }
    return res;
}

static bool sw_uart_init_tx_one(SwUartHandle_t* Node) {
    bool res = false;
    uint32_t dac_fs_hz = Node->baud_rate * Node->tx_over_sampling;
    res = fifo_init(&Node->TxByteFifo, Node->TxFifoMem, Node->tx_fifo_mem_size);
    res = bin_dac_sample_freq_set(Node->bin_dac_num, dac_fs_hz) && res;
    res = bin_dac_tx_pad_set(Node->bin_dac_num, Node->Tx) && res;
    return res;
}

static bool sw_uart_init_rx_one( SwUartHandle_t *Node){
    bool res = false;
    uint32_t adc_fs_hz = Node->baud_rate * Node->rx_over_sampling ;
    res = bin_adc_sample_freq_set(Node->bin_adc_num, adc_fs_hz);
    res = fifo_init(&Node->RxByteFifo, Node->RxFifoMem, Node->rx_fifo_mem_size)&& res;
    res = bin_adc_rx_pad_set(Node->bin_dac_num, Node->Rx)&& res;
    return res;
}

bool sw_uart_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SW_UART, "SW_UART_%u", num);
    const SwUartConfig_t *Config = SwUartGetConfig(num);
    res = SwUartIsValidConfig(Config);
    if(res) {
#ifdef HAS_SW_UART_DIAG
        LOG_WARNING(SW_UART, "%s", SwUartConfigToStr(Config));
#endif
        SwUartHandle_t *Node = SwUartGetNode(num);
        if(Node) {
            res = sw_uart_init_common(Config, Node);
            res = sw_uart_init_node(Node)&& res;

#if 0
            uint32_t adc_fs_hz = Node->baud_rate * Node->rx_over_sampling ;
            res = bin_adc_sample_freq_set(Node->bin_adc_num, adc_fs_hz)&& res;
            res = bin_adc_rx_pad_set(Node->bin_dac_num, Node->Rx)&& res;

            res = fifo_init(&Node->RxByteFifo, Node->RxFifoMem, Node->rx_fifo_mem_size)&& res;

            uint32_t dac_fs_hz = Node->baud_rate*Node->tx_over_sampling ;
            res = bin_dac_sample_freq_set(Node->bin_dac_num, dac_fs_hz);
            res = bin_dac_tx_pad_set(Node->bin_dac_num, Node->Tx) && res;
#endif

            res = sw_uart_init_tx_one(Node) && res;
            res = sw_uart_init_rx_one(Node) && res;


            LOG_INFO(SW_UART, "%s", SwUartNodeToStr(Node));
        } else {
            LOG_ERROR(SW_UART, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(SW_UART, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(SW_UART, SW_UART, sw_uart)
COMPONENT_PROC_PATTERT(SW_UART, SW_UART, sw_uart)
