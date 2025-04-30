#include "uart_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit_utils.h"
#include "gpio_drv.h"
#include "hal_nrfx_diag.h"
#include "nrfx_uarte.h"
#include "uart_isr.h"
#include "uart_nrf_drv.h"

#ifdef HAS_SOFTWARE_TIMER
#include "software_timer.h"
#endif

#ifdef HAS_CLI
#include "cli_config.h"
#include "uart_string_reader.h"
#endif

#ifdef HAS_HEAP
#include "heap_allocator.h"
#endif
#ifdef HAS_LOG
#include "log.h"
#endif /*HAS_LOG*/
#include "uart_bsp.h"
#include "uart_types.h"

#ifdef HAS_TIME
#include "time_utils.h"
#endif

#ifdef HAS_TIMER
#include "timer_drv.h"
#endif

#include "sys_config.h"

const static NrfUartInfo_t NrfUartInfoLut[] = {
#if NRFX_CHECK(NRFX_UARTE0_ENABLED)
    //#ifdef NRFX_UARTE0_ENABLED
    {
        .uart_num = 0,
        .valid = true,
        .uart_int_id = NRFX_UARTE0_INST_IDX,
        .event_handler = nrfx_uart0_event_handler,
        .uart_ptr = NRF_UARTE0_S,
    },
#endif /*NRFX_UARTE0_ENABLED*/

#if NRFX_CHECK(NRFX_UARTE1_ENABLED)
    //#ifdef NRFX_UARTE1_ENABLED
    {.uart_num = 1,
     .valid = true,
     .uart_int_id = NRFX_UARTE1_INST_IDX,
     .event_handler = nrfx_uart1_event_handler,
     .uart_ptr = /*NRF_UARTE1*/ NRF_UARTE1_S},
#endif

#if NRFX_CHECK(NRFX_UARTE2_ENABLED)
    //#ifdef NRFX_UARTE2_ENABLED
    {.uart_num = 2,
     .valid = true,
     .uart_int_id = NRFX_UARTE2_INST_IDX,
     .event_handler = nrfx_uart2_event_handler,
     .uart_ptr = NRF_UARTE2_S /*NRF_UARTE2 NRF_UARTE2_S*/},
#endif

#if NRFX_CHECK(NRFX_UARTE3_ENABLED)
    //#ifdef NRFX_UARTE3_ENABLED
    {.uart_num = 3,
     .valid = true,
     .uart_int_id = NRFX_UARTE3_INST_IDX,
     .event_handler = nrfx_uart3_event_handler,
     .uart_ptr = /*NRF_UARTE3*/ NRF_UARTE3_S},
#endif
};

static const NrfUartInfo_t* UartNum2UartInfoNode(uint8_t uart_num) {
    const NrfUartInfo_t* UartInfoNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(NrfUartInfoLut);
    for(i = 0; i < cnt; i++) {
        if(NrfUartInfoLut[i].valid) {
            if(NrfUartInfoLut[i].uart_num == uart_num) {
                UartInfoNode = &NrfUartInfoLut[i];
                break;
            }
        }
    }
    return UartInfoNode;
}

static uint8_t UartNum2UartIntIdx2(uint8_t uart_num) {
    uint8_t uart_int_idx = 0xFF;
    const NrfUartInfo_t* UartInfoNode = UartNum2UartInfoNode(uart_num);
    if(UartInfoNode) {
        uart_int_idx = UartInfoNode->uart_int_id;
    }
    return uart_int_idx;
}

static NRF_UARTE_Type* UartNum2Ptr(uint8_t uart_num) {
    NRF_UARTE_Type* peripheral = NULL;
    const NrfUartInfo_t* UartInfoNode = UartNum2UartInfoNode(uart_num);
    if(UartInfoNode) {
        peripheral = UartInfoNode->uart_ptr;
    }
    switch(uart_num) {
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

bool uart_init_ll(uint8_t uart_num) {
    bool res = false;
    char str[40];
    strncpy(str, "USART_", sizeof(str));
    UartHandle_t* UartNode = UartGetNode(uart_num);
    const UartConfig_t* UartConfNode = UartGetConfNode(uart_num);
    if(UartNode) {
        if(UartConfNode) {
#ifdef HAS_FIFO
            if(UartConfNode->rx_buff_size) {
                UartNode->RxFifo.array = (char*)malloc(UartConfNode->rx_buff_size);
                if(UartNode->RxFifo.array) {
                    res = fifo_init(&UartNode->RxFifo, UartNode->RxFifo.array, UartConfNode->rx_buff_size);
                }
            }
#endif

            NRF_UARTE_Type* UartInstance = UartNum2Ptr(uart_num);
            if(UartInstance) {
#ifdef HAS_GPIO
                UartNode->config.pseltxd = UartConfNode->TxPad.byte;    ///< TXD pin number.
                UartNode->config.pselrxd = UartConfNode->RxPad.byte;    ///< RXD pin number.
                UartNode->config.pselcts = NRF_UARTE_PSEL_DISCONNECTED; ///< CTS pin number.
                UartNode->config.pselrts = NRF_UARTE_PSEL_DISCONNECTED; ///< RTS pin number.
#endif                                                                  /*HAS_GPIO*/
                UartNode->config.p_context = NULL;                      ///< Context passed to interrupt handler.
                UartNode->config.baudrate = UartBaudRate2Code(UartConfNode->baud_rate); ///< Baud rate.
                UartNode->config.hal_cfg.parity =
                    NRF_UARTE_PARITY_EXCLUDED; ///< Parity, flow control and stop bits settings.
                UartNode->config.hal_cfg.hwfc = NRF_UARTE_HWFC_DISABLED; ///< Flow control configuration.
                // UartNode->config.interrupt_priority= NRFX_UARTE_DEFAULT_CONFIG_IRQ_PRIORITY;
                // UartNode->config.hal_cfg.stop = NRFX_UARTE_DEFAULT_EXTENDED_STOP_CONFIG       ;
                // UartNode->config.hal_cfg.paritytype=NRFX_UARTE_DEFAULT_EXTENDED_PARITYTYPE_CONFIG   ;
                nrfx_uarte_event_handler_t event_handler = NULL;
#ifdef HAS_UART_ISR
                LOG_INFO(UART, "InterruptsEnable");
                UartNode->config.interrupt_priority = 1;
                event_handler = UartNum2EventHandler(uart_num);
#endif /*HAS_UART_ISR*/
                UartNode->uart__h.p_reg = UartNum2Ptr(uart_num);
                UartNode->uart__h.drv_inst_idx = UartNum2UartIntIdx2(uart_num);
                UartNode->tx_done = true;
                // uart_interupts_enable(uart_num);
                nrfx_err_t ret = nrfx_uarte_init(&UartNode->uart__h, &UartNode->config, event_handler);
                if(NRFX_SUCCESS == ret) {
                    UartNode->init_done = true;
                    res = true;
                }
            }
        }
    }

    if(res) {
        uart_send_wait_ll(uart_num, (uint8_t*)str, strlen(str));
        snprintf(str, sizeof(str), "UART%u %u", uart_num, UartConfNode->baud_rate);
        size_t len = strlen(str);
        uart_send_wait_ll(uart_num, (uint8_t*)str, len);
        uart_wait_send_ll(uart_num, (uint8_t*)str, len);
#ifdef HAS_CLI
        res = uart_read(uart_num, &UartNode->rx_dma_buf[0], 1);
#endif /*HAS_CLI*/
    }
    return res;
}

bool uart_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(UART, "Init..");
#endif /*HAS_LOG*/
    bool out_res = true;
    uint8_t i = 0;
#ifdef HAS_LOG
    uint32_t uart_cnt = 0;
    uart_cnt = uart_get_cnt();
    LOG_INFO(UART, "Cnt: %u", uart_cnt);
#endif /*HAS_LOG*/
    for(i = 0; i <= 4; i++) {
        UartHandle_t* UartNode = UartGetNode(i);
        const UartConfig_t* UartConfNode = UartGetConfNode(i);
        if(UartNode && UartConfNode) {
#ifdef HAS_LOG
            LOG_DEBUG(UART, "%u SpotConfig", i);
#endif /*HAS_LOG*/
            res = uart_init_ll(UartNode->num);
            if(res) {
                LOG_INFO(UART, "%u Init" LOG_OK, UartNode->num);
#ifdef HAS_LOG
#endif /*HAS_LOG*/
            } else {
                out_res = false;
#ifdef HAS_LOG
                LOG_ERROR(UART, "%u InitErr", UartNode->num);
#endif /*HAS_LOG*/
            }
        }
    }

    return out_res;
}

static bool uart_wait_tx_done_ll(UartHandle_t* UartNode) {
    bool res = false;
    if(UartNode) {
        bool time_out = false;

        uint32_t start_ms = time_get_ms32();
        uint32_t cur_ms = start_ms;
        uint32_t diff_ms = 0;

        while(false == UartNode->tx_done) {
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            if(UART_TX_TIME_OUT_MS < diff_ms) {
                res = false;
                time_out = true;
                UartNode->tx_done = true;
                break;
            }
        }
        if(false == time_out) {
            res = true;
        } else {
            res = false;
        }
    }

    return res;
}

bool uart_wait_send_ll(uint8_t uart_num, uint8_t* tx_buffer, uint16_t length) {
    bool res = false;

    UartHandle_t* UartNode = UartGetNode(uart_num);
    res = uart_wait_tx_done_ll(UartNode);

    res = false;
    UartNode->tx_done = false;
    res = nrfx_uarte_tx_in_progress(&UartNode->uart__h);
    if(false == res) {
        if(tx_buffer && length) {
            if(length < UART_TX_BUFF_SIZE) {
                memcpy(UartNode->TxBuff, tx_buffer, (size_t)UART_TX_BUFF_SIZE);
                nrfx_err_t ret;
                UartNode->in_progress = true;
                ret = nrfx_uarte_tx((nrfx_uarte_t const*)&UartNode->uart__h, (uint8_t const*)UartNode->TxBuff,
                                    (size_t)length);
                if(NRFX_SUCCESS == ret) {
                    res = true;
                }
            } else {
                memcpy(UartNode->TxBuff, UART_TX_BUFF_SIZE, UART_TX_BUFF_SIZE);
                UartNode->in_progress = true;
                nrfx_err_t ret;
                ret = nrfx_uarte_tx((nrfx_uarte_t const*)&UartNode->uart__h, (uint8_t const*)UartNode->TxBuff,
                                    (size_t)UART_TX_BUFF_SIZE);
                if(NRFX_SUCCESS == ret) {
                    res = true;
                }
            }
        }
    }

    return res;
}

static bool uart_rx_timeout_ll(UartHandle_t* UartNode) {
    bool res = false;
    if(UartNode) {
        nrfx_uarte_rx_abort(&UartNode->uart__h);
        UartNode->rx_time_out_cnt++;
        res = true;
    }
    return res;
}

bool uart0_rx_timeout(void) {
    bool res = false;
    UartHandle_t* UartNode = UartGetNode(0);
    res = uart_rx_timeout_ll(UartNode);
    return res;
}

bool uart1_rx_timeout(void) {
    bool res = false;
    UartHandle_t* UartNode = UartGetNode(1);
    res = uart_rx_timeout_ll(UartNode);
    return res;
}

bool uart2_rx_timeout(void) {
    bool res = false;
    UartHandle_t* UartNode = UartGetNode(2);
    res = uart_rx_timeout_ll(UartNode);
    return res;
}

bool uart3_rx_timeout(void) {
    bool res = false;
    UartHandle_t* UartNode = UartGetNode(3);
    res = uart_rx_timeout_ll(UartNode);
    return res;
}

bool uart_send_wait_ll(uint8_t uart_num, uint8_t* tx_buffer, uint16_t length) {
    bool res = false;
    // We send mainly from Stack. We need wait the end of transfer.
    UartHandle_t* UartNode = UartGetNode(uart_num);
    if(UartNode) {
        res = false;
        res = nrfx_uarte_tx_in_progress(&UartNode->uart__h);
        if((false == res) && tx_buffer && length) {
            UartNode->tx_done = false;
            UartNode->in_progress = true;
            nrfx_err_t ret;
            ret = nrfx_uarte_tx((nrfx_uarte_t const*)&UartNode->uart__h, (uint8_t const*)tx_buffer, (size_t)length);
            if(NRFX_SUCCESS == ret) {
                res = true;
#ifdef HAS_UART_ISR
                res = uart_wait_tx_done_ll(UartNode);
#endif /*HAS_UART_ISR*/
            }
        }
    }
    return res;
}

bool uart_read(uint8_t uart_num, uint8_t* out_array, uint16_t array_len) {
    bool res = false;
    UartHandle_t* UartNode = UartGetNode(uart_num);
    if(UartNode) {
        UartNode->rx_done = false;
#ifdef HAS_UART_RX_TIMEOUT
        res = sw_timer_ctrl(TIMER_UART_RX_TIME_OUT, UART_RX_TIMEOUT_MS, 0, SW_TIMER_MODE_CONTINUOUS,
                            SW_TIMER_CNT_DIR_DOWN, true);
#endif /*HAS_UART_RX_TIMEOUT*/
        nrfx_err_t ret = nrfx_uarte_rx(&UartNode->uart__h, out_array, (size_t)array_len);
        if(NRFX_SUCCESS == ret) {
            UartNode->in_progress = true;
            res = true;
        }
    }

    return res;
}

bool uart_set_baudrate(uint8_t uart_num, uint32_t baudrate) {
    bool res = false;
    UartHandle_t* UartNode = UartGetNode(uart_num);
    if(UartNode && baudrate) {
        UartNode->uart__h.p_reg->BAUDRATE = UartBaudRate2Code(baudrate);
        res = true;
    }

    return res;
}

uint32_t uart_get_baud_rate(uint8_t uart_num, uint16_t* mantissa, uint16_t* fraction, uint8_t* over_sampling) {
    uint32_t baud_rate = 0;

    return baud_rate;
}

bool uart_send_ll(uint8_t uart_num, uint8_t* array, uint16_t array_len, bool is_wait) {
    bool res = false;
    (void)is_wait;
    // The send starts transmitting mainly from Stack.
    UartHandle_t* UartNode = NULL;
    res = uart_is_allowed(uart_num);
    if(res) {
        if(array && array_len) {
            UartNode = UartGetNode(uart_num);
            if(UartNode) {
                if(UartNode->init_done) {
                    res = true;
                }
            } else {
                res = false;
            }
        } else {
            LOG_ERROR(UART, "DataErr L:%u", array_len);
        }
    } else {
        LOG_ERROR(UART, "%u NotAllowed", uart_num);
    }

    if(res) {
        /*Print ftom stack*/
#if 0
            res = uart_wait_send_ll(uart_num, UartNode->tx_buff, array_len);
            if(false == res) {
                LOG_ERROR(UART, "%u WaitSendErr", uart_num);
            }
#endif
        res = uart_send_wait_ll(uart_num, array, array_len);
        if(false == res) {
            LOG_ERROR(UART, "%u SendWaitErr", uart_num);
        }
    }
    return res;
}

bool uart_flush(uint8_t uart_num) {
    bool res = false;
    UartHandle_t* UartNode = UartGetNode(uart_num);
    if(UartNode) {
        if(UartNode->init_done) {
#ifdef HAS_FIFO
            FifoIndex_t cnt = 0;
            do {
                cnt = fifo_get_count(&UartNode->TxFifo);
                if(cnt) {
                    char txBuff[100];
                    FifoIndex_t out_len = 0;
                    res = fifo_pull_array(&UartNode->TxFifo, txBuff, sizeof(txBuff), &out_len);
                    if(res) {
                        res = uart_send_ll(uart_num, (uint8_t*)txBuff, out_len, true);
                    }
                }
            } while(cnt);
#endif
        }
    }
    return res;
}

bool uart_check(void) { return false; }

#if 0
void UARTE0_IRQHandler(void) {
    UartHandle_t* UartNode = UartGetNode(0);
    if(UartNode) {
       // uint8_t data;

        if (UartNode->uart_h->EVENTS_ENDRX) {
            UartNode->uart_h->EVENTS_ENDRX = 0;
            // uint32_t rx_cnt = 0;
            // rx_cnt = UartNode->uart_h->RXD.AMOUNT;
#ifdef HAS_CLI
            if(UART_NUM_CLI == 0) {
                uart_string_reader_rx_callback(&cmd_reader, (char) UartNode->rx_dma_buf[0][0]);
            }
#endif /*HAS_CLI*/
        }

        if (UartNode->uart_h->EVENTS_RXSTARTED)   {
            UartNode->uart_h->EVENTS_RXSTARTED = 0;
            UartNode->uart_h->RXD.PTR = (uint32_t)UartNode->rx_dma_buf[0];
        }

        if (UartNode->uart_h->EVENTS_ERROR) {
            UartNode->uart_h->EVENTS_ERROR = 0;
        }
    }
}
#endif

#if 0

void UARTE2_IRQHandler(void) {
    UartHandle_t* UartNode = UartGetNode(2);
    if(UartNode) {
       // uint8_t data;

        if (UartNode->uart_h->EVENTS_ENDRX) {
            UartNode->uart_h->EVENTS_ENDRX = 0;
            // uint32_t rx_cnt = 0;
            // rx_cnt = UartNode->uart_h->RXD.AMOUNT;
#ifdef HAS_CLI
            if(2==UART_NUM_CLI ) {
                uart_string_reader_rx_callback(&cmd_reader, (char) UartNode->rx_dma_buf[0][0]);
            }
#endif /*HAS_CLI*/
        }

        if (UartNode->uart_h->EVENTS_RXSTARTED)   {
            UartNode->uart_h->EVENTS_RXSTARTED = 0;
            UartNode->uart_h->RXD.PTR = (uint32_t)UartNode->rx_dma_buf[0];
        }

        if (UartNode->uart_h->EVENTS_ERROR) {
            UartNode->uart_h->EVENTS_ERROR = 0;
        }
    }
}
#endif

bool uart_poll(uint8_t uart_num, uint8_t* out_array, uint16_t size, uint16_t* read_cnt) {
    bool res = false;
    return res;
}
#ifndef HAS_UART_ISR
bool uart_poll_read(uint8_t uart_num) {
    bool res = false;
    uint16_t cnt = 0;

    uint8_t data[2];
    nrfx_err_t ret;

    UartHandle_t* UartNode = NULL;

    UartNode = UartGetNode(uart_num);
    if(UartNode) {
        res = true;
    }

    if(res) {
#if 0
        if(false==UartNode->first_rx){
            UartNode->first_rx = true;
#ifdef HAS_SOFTWARE_TIMER
            res = sw_timer_ctrl(TIMER_UART_RX_TIME_OUT, UART_RX_TIMEOUT_MS, 0, SW_TIMER_MODE_CONTINUOUS,SW_TIMER_CNT_DIR_DOWN,true);
#endif
            ret  = nrfx_uarte_rx(&UartNode->uart__h, &data[0], 1);
            if(NRFX_SUCCESS==ret) {
                cnt++;
            }
        }
#endif

        do {
            res = nrfx_uarte_rx_ready(&UartNode->uart__h);
            if(res) {
#ifdef HAS_SOFTWARE_TIMER
                res = sw_timer_ctrl(TIMER_UART_RX_TIME_OUT, UART_RX_TIMEOUT_MS, 0, SW_TIMER_MODE_CONTINUOUS,
                                    SW_TIMER_CNT_DIR_DOWN, true);
#endif
                ret = nrfx_uarte_rx(&UartNode->uart__h, data, 1);
                if(NRFX_SUCCESS == ret) {
                    res = false;
                    cnt++;
#ifdef HAS_CLI
                    if(UART_NUM_CLI == UartNode->num) {
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

bool proc_uarts(void) {
    bool res = false;
    uint8_t uart_num = 0;
    for(uart_num = 0; uart_num <= 10; uart_num++) {
        res = uart_flush(uart_num);
#ifndef HAS_UART_ISR
        res = uart_poll_read(uart_num);
#endif
    }
    return res;
}
