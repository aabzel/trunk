#include "uart_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit_utils.h"
#include "gpio_mcal.h"
#include "hal_nrfx_diag.h"
#include "nrfx_uarte.h"
#include "uart_isr.h"
#include "uart_custom_drv.h"

#ifdef HAS_SOFTWARE_TIMER
#include "software_timer.h"
#endif

#ifdef HAS_CLI
#include "cli_config.h"
#include "string_reader.h"
#endif

#ifdef HAS_HEAP
#include "heap_allocator.h"
#endif
#ifdef HAS_LOG
#include "log.h"
#endif /*HAS_LOG*/
#include "uart_types.h"

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif

#include "sys_config.h"

const static UartInfo_t NrfUartInfoLut[] = {
#if NRFX_CHECK(NRFX_UARTE0_ENABLED)
    //#ifdef NRFX_UARTE0_ENABLED
    {
        .num = 0,
        .valid = true,
        .uart_int_id = NRFX_UARTE0_INST_IDX,
        .event_handler = nrfx_uart0_event_handler,
        .uart_ptr = NRF_UARTE0_S,
    },
#endif /*NRFX_UARTE0_ENABLED*/

#if NRFX_CHECK(NRFX_UARTE1_ENABLED)
    //#ifdef NRFX_UARTE1_ENABLED
    {.num = 1,
     .valid = true,
     .uart_int_id = NRFX_UARTE1_INST_IDX,
     .event_handler = nrfx_uart1_event_handler,
     .uart_ptr = /*NRF_UARTE1*/ NRF_UARTE1_S},
#endif

#if NRFX_CHECK(NRFX_UARTE2_ENABLED)
    //#ifdef NRFX_UARTE2_ENABLED
    {.num = 2,
     .valid = true,
     .uart_int_id = NRFX_UARTE2_INST_IDX,
     .event_handler = nrfx_uart2_event_handler,
     .uart_ptr = NRF_UARTE2_S /*NRF_UARTE2 NRF_UARTE2_S*/},
#endif

#if NRFX_CHECK(NRFX_UARTE3_ENABLED)
    //#ifdef NRFX_UARTE3_ENABLED
    {.num = 3,
     .valid = true,
     .uart_int_id = NRFX_UARTE3_INST_IDX,
     .event_handler = nrfx_uart3_event_handler,
     .uart_ptr = /*NRF_UARTE3*/ NRF_UARTE3_S},
#endif
};

static const UartInfo_t* UartNum2UartInfoNode(uint8_t num) {
    const UartInfo_t* UartInfoNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(NrfUartInfoLut);
    for(i = 0; i < cnt; i++) {
        if(NrfUartInfoLut[i].valid) {
            if(NrfUartInfoLut[i].num == num) {
                UartInfoNode = &NrfUartInfoLut[i];
                break;
            }
        }
    }
    return UartInfoNode;
}

static uint8_t UartNum2UartIntIdx2(uint8_t num) {
    uint8_t uart_int_idx = 0xFF;
    const UartInfo_t* UartInfoNode = UartNum2UartInfoNode(num);
    if(UartInfoNode) {
        uart_int_idx = UartInfoNode->uart_int_id;
    }
    return uart_int_idx;
}

static NRF_UARTE_Type* UartNum2Ptr(uint8_t num) {
    NRF_UARTE_Type* peripheral = NULL;
    const UartInfo_t* UartInfoNode = UartNum2UartInfoNode(num);
    if(UartInfoNode) {
        peripheral = UartInfoNode->uart_ptr;
    }
    switch(num) {
#ifdef NRF_UARTE0
    case 0:
        peripheral = NRF_UARTE0_S;
        break;
#else
#ifdef NRF_UARTE0_NS
    case 0:
        peripheral = NRF_UARTE0_NS;
        break;
#endif
#endif

#ifdef NRF_UARTE1
    case 1:
        peripheral = NRF_UARTE1_S;
        break;
#endif

#ifdef NRF_UARTE2
    case 2:
        peripheral = NRF_UARTE2_S;
        break;
#endif

#ifdef NRF_UARTE3
    case 3:
        peripheral = NRF_UARTE3_S;
        break;
#endif
    default:
        peripheral = NULL;
        break;
    }
    return peripheral;
}

static const NrfUartBaudRateInfo_t NrfUartBaudRateInfoLut[] = {
    {.baudrate = 1200, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_1200, .valid = true},
    {.baudrate = 2400, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_2400, .valid = true},
    {.baudrate = 4800, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_4800, .valid = true},
    {.baudrate = 9600, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_9600, .valid = true},
    {.baudrate = 14400, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_14400, .valid = true},
    {.baudrate = 19200, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_19200, .valid = true},
    {.baudrate = 28800, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_28800, .valid = true},
    {.baudrate = 31250, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_31250, .valid = true},
    {.baudrate = 38400, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_38400, .valid = true},
    {.baudrate = 56000, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_56000, .valid = true},
    {.baudrate = 76800, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_76800, .valid = true},
    {.baudrate = 57600, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_57600, .valid = true},
    {.baudrate = 115200, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_115200, .valid = true},
    {.baudrate = 230400, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_230400, .valid = true},
    {.baudrate = 250000, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_250000, .valid = true},
    {.baudrate = 460800, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_460800, .valid = true},
    {.baudrate = 921600, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_921600, .valid = true},
    {.baudrate = 1000000, .nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_1000000, .valid = true},
};

static nrf_uarte_baudrate_t UartBaudRate2Code(uint32_t baudrate) {
    nrf_uarte_baudrate_t nrf_uarte_baudrate = NRF_UARTE_BAUDRATE_460800;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(NrfUartBaudRateInfoLut);
    for(i = 0; i < cnt; i++) {
        if(NrfUartBaudRateInfoLut[i].valid) {
            if(NrfUartBaudRateInfoLut[i].baudrate == baudrate) {
                nrf_uarte_baudrate = NrfUartBaudRateInfoLut[i].nrf_uarte_baudrate;
                break;
            }
        }
    }
    return nrf_uarte_baudrate;
}

bool uart_init_one(uint8_t num) {
    bool res = false;
    char str[50];
    LOG_WARNING(UART, "Init %u", num);
    strncpy(str, "USART_", sizeof(str));
    UartHandle_t* Node = UartGetNode(num);
    const UartConfig_t* Config = UartGetConfig(num);
    if(Config) {
        if(Node) {
#ifdef HAS_FIFO
            if(Config->rx_buff_size) {
                Node->RxFifo.array = (char*)malloc(Config->rx_buff_size);
                if(Node->RxFifo.array) {
                    res = fifo_init(&Node->RxFifo, Node->RxFifo.array, Config->rx_buff_size);
                }
            }
#endif

            NRF_UARTE_Type* UartInstance = UartNum2Ptr(num);
            if(UartInstance) {
#ifdef HAS_GPIO
                Node->config.pseltxd = Config->TxPad.byte;    ///< TXD pin number.
                Node->config.pselrxd = Config->RxPad.byte;    ///< RXD pin number.
                Node->config.pselcts = NRF_UARTE_PSEL_DISCONNECTED; ///< CTS pin number.
                Node->config.pselrts = NRF_UARTE_PSEL_DISCONNECTED; ///< RTS pin number.
#endif                                                              /*HAS_GPIO*/
                Node->config.p_context = NULL;                      ///< Context passed to interrupt handler.
                Node->config.baudrate = UartBaudRate2Code(Config->baud_rate); ///< Baud rate.
                LOG_INFO(UART, "baudrateCode 0x%x", Node->config.baudrate);
                Node->config.hal_cfg.parity =
                    NRF_UARTE_PARITY_EXCLUDED;                       ///< Parity, flow control and stop bits settings.
                Node->config.hal_cfg.hwfc = NRF_UARTE_HWFC_DISABLED; ///< Flow control configuration.
                // Node->config.interrupt_priority= NRFX_UARTE_DEFAULT_CONFIG_IRQ_PRIORITY;
                // Node->config.hal_cfg.stop = NRFX_UARTE_DEFAULT_EXTENDED_STOP_CONFIG       ;
                // Node->config.hal_cfg.paritytype=NRFX_UARTE_DEFAULT_EXTENDED_PARITYTYPE_CONFIG   ;
                nrfx_uarte_event_handler_t event_handler = NULL;
#ifdef HAS_UART_ISR
                LOG_INFO(UART, "InterruptsEnable");
                Node->config.interrupt_priority = 1;
                event_handler = UartNum2EventHandler(num);
#endif /*HAS_UART_ISR*/
                Node->uart__h.p_reg = UartNum2Ptr(num);
                Node->uart__h.drv_inst_idx = UartNum2UartIntIdx2(num);
                Node->tx_done = true;
                // uart_interupts_enable(num);
                nrfx_err_t ret = nrfx_uarte_init(&Node->uart__h, &Node->config, event_handler);
                if(NRFX_SUCCESS == ret) {
                    Node->init_done = true;
                    gpio_set_pull(Config->RxPad.byte, GPIO__PULL_UP);
                    res = true;
                }
            }
        }
    }

    if(res) {
        uart_send_wait_ll(Node, (uint8_t*)str, strlen(str));
        snprintf(str, sizeof(str), "UART%u %u bit/s", num, Config->baud_rate);
        size_t len = strlen(str);
        uart_send_wait_ll(Node, (uint8_t*)str, len);
        uart_wait_send_ll(Node, (uint8_t*)str, len);
#ifdef HAS_CLI
        res = uart_read(num, &Node->rx_dma_buf[0], 1);
#endif /*HAS_CLI*/
    }
    return res;
}

#if 0
bool uart_init(void) {
    bool res = true;
    LOG_WARNING(UART, "Init..");
    bool out_res = true;
    uint8_t i = 0;
    uint32_t cnt = 0;
    cnt = uart_get_cnt();
    LOG_WARNING(UART, "Init Cnt: %u", cnt);
    for(i = 0; i <= 4; i++) {
        UartHandle_t* Node = UartGetNode(i);
        const UartConfig_t* Config = UartGetConfig(i);
        if(Node && Config) {
            LOG_DEBUG(UART, "%u SpotConfig", i);
            res = uart_init_one(Node->num);
            if(res) {
                LOG_INFO(UART, "UART%u Init" LOG_OK, Node->num);
            } else {
                out_res = false;
                LOG_ERROR(UART, "UART%u InitErr", Node->num);
            }
        }
    }

    return out_res;
}
#endif

bool uart_wait_send_ll(UartHandle_t* Node, const uint8_t* const data, size_t size)  {
    bool res = false;

    res = uart_wait_tx_done_ll(Node);
    res = false;
    Node->tx_done = false;
    res = nrfx_uarte_tx_in_progress(&Node->uart__h);
    if(false == res) {
        if(data && size) {
            if(size < UART_TX_BUFF_SIZE) {
                memcpy(Node->TxBuff, data, (size_t)size);
                nrfx_err_t ret;
                Node->in_progress = true;
                ret = nrfx_uarte_tx((nrfx_uarte_t const*)&Node->uart__h, (uint8_t const*)Node->TxBuff, (size_t)size);
                if(NRFX_SUCCESS == ret) {
                    res = true;
                }
            } else {
                memcpy(Node->TxBuff, data, UART_TX_BUFF_SIZE);
                Node->in_progress = true;
                nrfx_err_t ret;
                ret = nrfx_uarte_tx((nrfx_uarte_t const*)&Node->uart__h, (uint8_t const*)Node->TxBuff,
                                    (size_t)UART_TX_BUFF_SIZE);
                if(NRFX_SUCCESS == ret) {
                    res = true;
                }
            }
        }
    }

    return res;
}

static bool uart_rx_timeout_ll(UartHandle_t* Node) {
    bool res = false;
    if(Node) {
        nrfx_uarte_rx_abort(&Node->uart__h);
        Node->rx_time_out_cnt++;
        res = true;
    }
    return res;
}

bool uart0_rx_timeout(void) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(0);
    res = uart_rx_timeout_ll(Node);
    return res;
}

bool uart1_rx_timeout(void) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(1);
    res = uart_rx_timeout_ll(Node);
    return res;
}

bool uart2_rx_timeout(void) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(2);
    res = uart_rx_timeout_ll(Node);
    return res;
}

bool uart3_rx_timeout(void) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(3);
    res = uart_rx_timeout_ll(Node);
    return res;
}

bool uart_send_wait_ll(UartHandle_t* Node , uint8_t* data, uint16_t size) {
    bool res = false;
    // We send mainly from Stack. We need wait the end of transfer.
    if(Node) {
        res = false;
        res = nrfx_uarte_tx_in_progress(&Node->uart__h);
        if((false == res) && data && size) {
            Node->tx_done = false;
            Node->in_progress = true;
            nrfx_err_t ret;
            ret = nrfx_uarte_tx((nrfx_uarte_t const*)&Node->uart__h, (uint8_t const*)data, (size_t)size);
            if(NRFX_SUCCESS == ret) {
                res = true;
#ifdef HAS_UART_ISR
                res = uart_wait_tx_done_ll(Node);
#endif /*HAS_UART_ISR*/
            }
        }
    }
    return res;
}

bool uart_read(uint8_t num, uint8_t* out_array, uint16_t array_len) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        Node->rx_done = false;
#ifdef HAS_UART_RX_TIMEOUT
        res = sw_timer_ctrl(TIMER_UART_RX_TIME_OUT, UART_RX_TIMEOUT_MS, 0, SW_TIMER_MODE_CONTINUOUS,
                            SW_TIMER_CNT_DIR_DOWN, true);
#endif /*HAS_UART_RX_TIMEOUT*/
        nrfx_err_t ret = nrfx_uarte_rx(&Node->uart__h, out_array, (size_t)array_len);
        if(NRFX_SUCCESS == ret) {
            Node->in_progress = true;
            res = true;
        }
    }

    return res;
}

bool uart_set_baudrate(uint8_t num, uint32_t baudrate) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node && baudrate) {
        Node->uart__h.p_reg->BAUDRATE = UartBaudRate2Code(baudrate);
        res = true;
    }

    return res;
}

uint32_t uart_get_baud_rate(uint8_t num, uint16_t* mantissa, uint16_t* fraction, uint8_t* over_sampling) {
    uint32_t baud_rate = 0;

    return baud_rate;
}

bool uart_send_ll(uint8_t num, uint8_t* array, uint16_t array_len, bool is_wait) {
    bool res = false;
    (void)is_wait;
    // The send starts transmitting mainly from Stack.
    UartHandle_t* Node = NULL;
    res = uart_is_allowed(num);
    if(res) {
        if(array && array_len) {
            Node = UartGetNode(num);
            if(Node) {
                if(Node->init_done) {
                    res = true;
                }
            } else {
                res = false;
            }
        } else {
            LOG_ERROR(UART, "DataErr L:%u", array_len);
        }
    } else {
        LOG_ERROR(UART, "%u NotAllowed", num);
    }

    if(res) {
        /*Print ftom stack*/
#if 0
            res = uart_wait_send_ll(Node, Node->tx_buff, array_len);
            if(false == res) {
                LOG_ERROR(UART, "%u WaitSendErr", num);
            }
#endif
        res = uart_send_wait_ll(Node, array, array_len);
        if(false == res) {
            LOG_ERROR(UART, "%u SendWaitErr", num);
        }
    }
    return res;
}

#if 0
bool uart_flush(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        if(Node->init_done) {
#ifdef HAS_FIFO
            FifoIndex_t cnt = 0;
            do {
                cnt = fifo_get_count(&Node->TxFifo);
                if(cnt) {
                    char txBuff[100];
                    FifoIndex_t out_len = 0;
                    res = fifo_pull_array(&Node->TxFifo, txBuff, sizeof(txBuff), &out_len);
                    if(res) {
                        res = uart_send_ll(num, (uint8_t*)txBuff, out_len, true);
                    }
                }
            } while(cnt);
#endif
        }
    }
    return res;
}
#endif

bool uart_check(void) { return false; }

#if 0
void UARTE0_IRQHandler(void) {
    UartHandle_t* Node = UartGetNode(0);
    if(Node) {
       // uint8_t data;

        if (Node->uart_h->EVENTS_ENDRX) {
            Node->uart_h->EVENTS_ENDRX = 0;
            // uint32_t rx_cnt = 0;
            // rx_cnt = Node->uart_h->RXD.AMOUNT;
#ifdef HAS_CLI
            if(UART_NUM_CLI == 0) {
                uart_string_reader_rx_callback(&cmd_reader, (char) Node->rx_dma_buf[0][0]);
            }
#endif /*HAS_CLI*/
        }

        if (Node->uart_h->EVENTS_RXSTARTED)   {
            Node->uart_h->EVENTS_RXSTARTED = 0;
            Node->uart_h->RXD.PTR = (uint32_t)Node->rx_dma_buf[0];
        }

        if (Node->uart_h->EVENTS_ERROR) {
            Node->uart_h->EVENTS_ERROR = 0;
        }
    }
}
#endif

#if 0

void UARTE2_IRQHandler(void) {
    UartHandle_t* Node = UartGetNode(2);
    if(Node) {
       // uint8_t data;

        if (Node->uart_h->EVENTS_ENDRX) {
            Node->uart_h->EVENTS_ENDRX = 0;
            // uint32_t rx_cnt = 0;
            // rx_cnt = Node->uart_h->RXD.AMOUNT;
#ifdef HAS_CLI
            if(2==UART_NUM_CLI ) {
                uart_string_reader_rx_callback(&cmd_reader, (char) Node->rx_dma_buf[0][0]);
            }
#endif /*HAS_CLI*/
        }

        if (Node->uart_h->EVENTS_RXSTARTED)   {
            Node->uart_h->EVENTS_RXSTARTED = 0;
            Node->uart_h->RXD.PTR = (uint32_t)Node->rx_dma_buf[0];
        }

        if (Node->uart_h->EVENTS_ERROR) {
            Node->uart_h->EVENTS_ERROR = 0;
        }
    }
}
#endif

bool uart_poll(uint8_t num, uint8_t* out_array, uint16_t size, uint16_t* read_cnt) {
    bool res = false;
    return res;
}

#ifndef HAS_UART_ISR
bool uart_poll_read(uint8_t num) {
    bool res = false;
    uint16_t cnt = 0;

    uint8_t data[2];
    nrfx_err_t ret;

    UartHandle_t* Node = NULL;

    Node = UartGetNode(num);
    if(Node) {
        res = true;
    }

    if(res) {
#if 0
        if(false==Node->first_rx){
            Node->first_rx = true;
#ifdef HAS_SOFTWARE_TIMER
            res = sw_timer_ctrl(TIMER_UART_RX_TIME_OUT, UART_RX_TIMEOUT_MS, 0, SW_TIMER_MODE_CONTINUOUS,SW_TIMER_CNT_DIR_DOWN,true);
#endif
            ret  = nrfx_uarte_rx(&Node->uart__h, &data[0], 1);
            if(NRFX_SUCCESS==ret) {
                cnt++;
            }
        }
#endif

        do {
            res = nrfx_uarte_rx_ready(&Node->uart__h);
            if(res) {
#ifdef HAS_SOFTWARE_TIMER
                res = sw_timer_ctrl(TIMER_UART_RX_TIME_OUT, UART_RX_TIMEOUT_MS, 0, SW_TIMER_MODE_CONTINUOUS,
                                    SW_TIMER_CNT_DIR_DOWN, true);
#endif
                ret = nrfx_uarte_rx(&Node->uart__h, data, 1);
                if(NRFX_SUCCESS == ret) {
                    res = false;
                    cnt++;
#ifdef HAS_CLI
                    if(CliConfig.if_num == Node->num) {
                        uart_string_reader_rx_callback(&cmd_reader, data[0]);
                    }
#endif /*HAS_CLI*/
                } else {
                    LOG_DEBUG(UART, "Err:%s", HalStatus2Str(ret));
                    res = false;
                    break;
                }
            } else {
                res = false;
                break;
            }
        } while(res);
    }
    return res;
}
#endif

#if 0
bool uart_proc(void) {
    bool res = false;
    uint8_t num = 0;
    for(num = 0; num <= 10; num++) {
        res = uart_flush(num);
#ifndef HAS_UART_ISR
        res = uart_poll_read(num);
#endif
    }
    return res;
}
#endif
