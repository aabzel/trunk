#include "uart_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit_utils.h"
#include "hal_diag.h"
#ifdef HAS_HEAP
#include "heap_allocator.h"
#endif
#include "log.h"
#include "sys_config.h"
#include "time_mcal.h"
#include "uart_custom_types.h"
#include "uart_types.h"

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif

#ifdef HAS_CLI
#include "cli_config.h"
#include "string_reader.h"
#endif

#include "sys_config.h"

uint32_t g_uart_rx_cnt = 0;
static volatile uint8_t rx_buff[UART_COUNT][1];

const static UartInfo_t UartInfo[] = {
#ifdef USART1
    {.valid = true,
     .UARTx = USART1,
     .clock_hz = APB2_CLOCK_HZ,
     .irq_n = USART1_IRQn,
     .num = 1,
     .clock_type = CRM_USART1_PERIPH_CLOCK},
#endif

#ifdef USART2
    {.valid = true,
     .UARTx = USART2,
     .clock_hz = APB1_CLOCK_HZ,
     .irq_n = USART2_IRQn,
     .num = 2,
     .clock_type = CRM_USART2_PERIPH_CLOCK},
#endif

#ifdef USART3
    {.valid = true,
     .UARTx = USART3,
     .clock_hz = APB1_CLOCK_HZ,
     .irq_n = USART3_IRQn,
     .num = 3,
     .clock_type = CRM_USART3_PERIPH_CLOCK},
#endif

#ifdef UART4
    {.valid = true,
     .UARTx = UART4,
     .clock_hz = APB1_CLOCK_HZ,
     .irq_n = UART4_IRQn,
     .num = 4,
     .clock_type = CRM_UART4_PERIPH_CLOCK},
#endif

#ifdef UART5
    {.valid = true,
     .UARTx = UART5,
     .clock_hz = APB1_CLOCK_HZ,
     .irq_n = UART5_IRQn,
     .num = 5,
     .clock_type = CRM_UART5_PERIPH_CLOCK},
#endif

#ifdef USART6
    {.valid = true,
     .UARTx = USART6,
     .clock_hz = APB2_CLOCK_HZ,
     .irq_n = USART6_IRQn,
     .num = 6,
     .clock_type = CRM_USART6_PERIPH_CLOCK},
#endif

#ifdef UART7
    {.valid = true,
     .UARTx = UART7,
     .clock_hz = APB1_CLOCK_HZ,
     .irq_n = UART7_IRQn,
     .num = 7,
     .clock_type = CRM_UART7_PERIPH_CLOCK},
#endif
};

UartInfo_t* UartGetInfo(uint8_t num) {
    UartInfo_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(UartInfo);
    for(i = 0; i < cnt; i++) {
        if(num == UartInfo[i].num) {
            if(UartInfo[i].valid) {
                Node = &UartInfo[i];
                break;
            }
        }
    }
    return Node;
}

static usart_type* UartGetBase(uint8_t num) {
    usart_type* USARTx = NULL;
    UartInfo_t* Info = UartGetInfo(num);
    if(Info) {
        USARTx = Info->UARTx;
    }
    return USARTx;
}

static int8_t get_uart_index(usart_type* USARTx) {
    int8_t num = -1;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(UartInfo);
    for(i = 0; i < cnt; i++) {
        if(USARTx == UartInfo[i].UARTx) {
            if(UartInfo[i].valid) {
                num = UartInfo[i].num;
                break;
            }
        }
    }

    return num;
}

bool uart_init_one(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        const UartConfig_t* Config = UartGetConfig(num);
        if(Config) {
            if(false == Node->RxFifo.initDone) {
                LOG_WARNING(UART, "RxFiFoInitLack");
            }
            if(Config->rx_buff_size) {
                Node->RxFifo.array = (char*)malloc(Config->rx_buff_size);
                if(Node->RxFifo.array) {
                    res = fifo_init(&Node->RxFifo, Node->RxFifo.array, Config->rx_buff_size);
                }
            }

            // res=fifo_init(&Node->TxFifo, Node->tx_array, UART_TX_FIFO_SIZE);
            Node->tx_done = true;
            Node->rx_done = true;
            Node->rx_buff = (volatile uint8_t*)&rx_buff[num][0];
            Node->rx_buff_size = 1;
            LOG_WARNING(UART, "UART%u Init %u Bit/s", num, Config->baud_rate);
            UartInfo_t* Info = UartGetInfo(num);
            if(Info) {
                Node->UARTx = Info->UARTx;
                crm_periph_clock_enable(Info->clock_type, TRUE);
                NVIC_SetPriority(Info->irq_n, 7);
                NVIC_EnableIRQ(Info->irq_n);
                nvic_irq_enable(Info->irq_n, 7, 7);

                usart_init(Info->UARTx, Config->baud_rate, USART_DATA_8BITS, USART_STOP_2_BIT);
                usart_transmitter_enable(Info->UARTx, TRUE);
                usart_receiver_enable(Info->UARTx, TRUE);
                usart_interrupt_enable(Info->UARTx, USART_RDBF_INT, TRUE);

                usart_enable(Info->UARTx, TRUE);

                usart_interrupt_enable(Info->UARTx, USART_TDBE_INT, TRUE); // err

                Node->init_done = true;
                char str[40] = "UART";
                uart_mcal_send(num, (uint8_t*)str, 4);
                snprintf(str, sizeof(str), "UART%u", num);
                size_t len = strlen(str);
                uart_mcal_send(num, (uint8_t*)str, len);
                res = true;
                LOG_INFO(UART, "%u init Ok", num);
            }
        }
    }
    return res;
}

#if 0
bool uart_init(void) {
    bool res = true;
    LOG_WARNING(UART, "Init..");
    bool out_res = true;
    uint8_t i = 0;
    uint32_t uart_cnt = uart_get_cnt();
    LOG_INFO(UART, "Cnt: %u", uart_cnt);
    for(i = 0; i <= 10; i++) {
        UartHandle_t* Node = UartGetNode(i);
        const UartConfig_t* Config = UartGetConfig(i);
        if(Node && Config) {
            LOG_DEBUG(UART, "%u SpotConfig", i);
            res = uart_init_one(Node->num);
            if(res) {
                LOG_INFO(UART, "%u Init" LOG_OK, Node->num);
            } else {
                out_res = false;
                LOG_ERROR(UART, "%u InitErr", Node->num);
            }
        }
    }

    return out_res;
}
#endif

#if 0
static bool uart_wait_tx_done_ll(UartHandle_t* Node) {
    bool res = true;
    if(Node) {
        Node->wait_iter = 0;
        int8_t num = get_uart_index(Node->UARTx);
        if(0 <= num) {
#ifdef HAS_UART_TX_TIMEOUT

            uint32_t time_out_us = 0;
            uint32_t baudrate = uart_get_cfg_baudrate(num);
            uint32_t start_us = time_get_us();
            uint32_t dutation_us = 0;
            uint32_t cur_us = 0;
            if(Node->tx_len) {
                time_out_us = calc_transfer_time_us(baudrate, (uint32_t)Node->tx_len + 1);
            } else { // for first call tx_len==0
                time_out_us = calc_transfer_time_us(baudrate, 150);
            }
#endif
            do {
                Node->wait_iter++;
#ifdef HAS_UART_TX_TIMEOUT
                cur_us = time_get_us();
                dutation_us = cur_us - start_us;
                if(500 * time_out_us < dutation_us) {
                    Node->tx_time_out_cnt++;
                    Node->tx_done = true;
                    res = false;
                    break;
                }
#endif

                if(Node->tx_done) {
                    res = true;
                    break;
                }

            } while(false == Node->tx_done);
        }
    }

    return res;
}
#endif

static bool uart_data_tx(uint8_t num, uint8_t* data, size_t size) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        if(data) {
            if(size) {
                size_t i = 0;
                for(i = 0; i < size; i++) {
                    usart_interrupt_enable(Node->UARTx, USART_TDBE_INT, TRUE);
                    usart_data_transmit(Node->UARTx, data[i]);
                    res = uart_wait_tx_done_ll(Node);
                }
            }
        }
    }
    return res;
}

bool uart_wait_send_ll(UartHandle_t* Node, const uint8_t* const data, size_t len) {
    bool res = false;
    if(Node) {
        LOG_DEBUG(UART, "UART%u Wait->Send 0x%p %u byte", Node->num, data, len);
        if(Node->init_done && (len) && data) {
            res = uart_wait_tx_done_ll(Node);
            if(res) {
                Node->tx_done = false;
                Node->tx_len = len;
                res = uart_data_tx(Node->num, data, len);
                if(res) {
                    res = true;
                } else {
                    res = false;
                    LOG_ERROR(UART, "%u TxErr %s", Node->num);
                }
            } else {
                Node->tx_done = true;
                LOG_ERROR(UART, "%u WaitTxDoneErr", Node->num);
            }
        } else {
            LOG_ERROR(UART, "ArgErr Len:%u Ptr:0x%p", len, data);
        }
    } else {
        LOG_ERROR(UART, "%u NodeErr", Node->num);
    }
    return res;
}

bool uart_send_wait_ll(UartHandle_t* Node, uint8_t* data, uint16_t len) {
    bool res = false;
    // TODO make sure that global ISR enabled
    // We send mainly from Stack. We need wait the end of transfer.
    if(Node) {
        if(Node->init_done && (len) && data) {
            uint32_t init_tx_cnt = Node->tx_cnt;
#ifdef HAS_UART_TX_TIMEOUT
            uint32_t baudrate = uart_get_cfg_baudrate(Node->num);
            uint32_t time_out_us = calc_transfer_time_us(baudrate, (uint32_t)len);
#endif
            uint32_t dutation_us = 0;
            uint32_t cur_us = 0;
            uint32_t start_us = time_get_us();
            res = uart_data_tx(Node->num, data, len);

            if(res) {
                res = true;
                // We send mainly from Stack. We need wait the end of transfer.
                // Otherwise tx data will not be valid
                while(init_tx_cnt == Node->tx_cnt) {
                    cur_us = time_get_us();
                    dutation_us = cur_us - start_us;
#ifdef HAS_UART_TX_TIMEOUT
                    if((4000 * time_out_us) < dutation_us) {
                        res = false;
                        Node->tx_time_out_cnt++;
                        break;
                    }

#endif
                }
                Node->real_byte_tx_time_us = dutation_us / len;
            }

        } else {
            LOG_ERROR(UART, "SettingErr Len:%u Ptr:0x%p", len, data);
        }
    } else {
        LOG_ERROR(UART, "NodeErr");
    }
    return res;
}

bool uart_read(uint8_t num, uint8_t* out_array, uint16_t array_len) {
    bool res = false;

    return res;
}

bool uart_set_baudrate(uint8_t num, uint32_t baudrate) {
    bool res = false;
    usart_type* UARTx = UartGetBase(num);
    if(UARTx) {
        res = true;
    }

    return res;
}

uint32_t UartGetBaseClock(uint8_t num) {
    uint32_t clock_hz = 0;

    return clock_hz;
}

uint32_t uart_get_baud_rate(uint8_t num, uint16_t* mantissa, uint16_t* fraction, uint8_t* over_sampling) {
    uint32_t baud_rate = 0;
    usart_type* UARTx = UartGetBase(num);
    if(UARTx) {
    }
    return baud_rate;
}

#if 0
void UART_MspDeInit(usart_type* UARTx) {
    if(  USART1== UARTx) {
        crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, FALSE);

        /* USART2 interrupt Deinit */
        NVIC_DisableIRQ(USART1_IRQn);
    }

#ifdef USART2
    if(  USART2== UARTx) {
        crm_periph_clock_enable(CRM_USART2_PERIPH_CLOCK, FALSE);

        /* USART2 interrupt Deinit */
        NVIC_DisableIRQ(USART2_IRQn);
    }
#endif

#ifdef USART3
    if(USART3 == UARTx) {
    	crm_periph_clock_enable(CRM_USART3_PERIPH_CLOCK, FALSE);
        NVIC_DisableIRQ(USART3_IRQn);
    }
#endif

#ifdef UART4
    if(  UART4== UARTx) {
    	crm_periph_clock_enable(CRM_UART4_PERIPH_CLOCK, FALSE);
        NVIC_DisableIRQ(UART4_IRQn);
    }
#endif

#ifdef UART7
    if( UART7== UARTx) {
    	crm_periph_clock_enable(CRM_UART7_PERIPH_CLOCK, FALSE);

        NVIC_DisableIRQ(UART7_IRQn);
    }
#endif


    if(USART6 == UARTx) {
    	crm_periph_clock_enable(CRM_USART6_PERIPH_CLOCK, FALSE);

        NVIC_DisableIRQ(USART6_IRQn);
    }
}
#endif

void UART_RxCpltCallback(usart_type* UARTx) {
    g_uart_rx_cnt++;
    int8_t num = 0;
    num = get_uart_index(UARTx);
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        Node->rx_cnt++;
        Node->rx_done = true;
        usart_receiver_enable(UARTx, TRUE);
#ifdef HAS_CLI
        if(CliInstance[0].if_num == num) {
            string_reader_rx_callback(&CliInstance[0].Reader, Node->rx_buff[0]);
        }
#endif /*HAS_CLI*/

#ifdef HAS_BC127
        if(Bc127Config.num == num) {
            bool res = fifo_push(&Node->RxFifo, Node->rx_buff[0]);
            if(false == res) {
                Node->RxFifo.err_cnt++;
            }
        }
#endif /*HAS_BC127*/
    }
}

void UART_TxCpltCallback(usart_type* UARTx) {
    int8_t num = 0;
    num = get_uart_index(UARTx);
    UartHandle_t* Node = UartGetNode((uint8_t)num);
    if(Node) {
        Node->tx_cnt++;
        Node->tx_done = true;
        Node->tx_cpl_cnt++;
        Node->cnt.byte_tx++;
#ifdef HAS_HEAP
        bool res = h_free((void*)Node->tx_buff);
        if(false == res) {
            Node->err_heap++;
        }
#endif
    }
}

bool uart_send_ll(uint8_t num, uint8_t* array, uint16_t array_len, bool is_wait) {
    bool res = false;
    // We send mainly from Stack.
    (void)is_wait;
    res = uart_is_allowed(num);
    if(res) {
        if(array && array_len) {
            UartHandle_t* Node = UartGetNode(num);
            if(Node) {
                if(Node->init_done) {
                    Node->tx_buff = NULL;
                } else {
                    res = false;
                }
            } else {
                res = false;
            }
            if(res) {

                /*print from heap*/
#if 0
                    res = uart_wait_send_ll(num, Node->tx_buff, array_len);
                    if(false == res) {
                        LOG_ERROR(UART, "%u WaitSendErr", num);
                    }
#endif

                /*Print from stack*/
                res = uart_send_wait(num, array, array_len);
                if(false == res) {
                    LOG_ERROR(UART, "%u SendWaitErr", num);
                }
            }

        } else {
#ifdef HAS_LOG
            LOG_ERROR(UART, "DataErr L:%u", array_len);
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(UART, "%u NotAllowed", num);
#endif
    }
    return res;
}

#if 0
bool uart_flush(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        if(Node->init_done) {
            FifoIndex_t cnt = 0;
            do {
                cnt = fifo_get_count(&Node->TxFifo);
                if(cnt) {
                    char TxBuff[50];
                    FifoIndex_t out_len = 0;
                    res = fifo_pull_array(&Node->TxFifo, TxBuff, sizeof(TxBuff), &out_len);
                    if(res) {
                        if(out_len) {
                            res = uart_send_ll(num, (uint8_t*)TxBuff, out_len, true);
                        } else {
                            res = false;
                        }
                    }
                }
            } while(cnt);
        }
    }
    return res;
}
#endif

bool proc_uarts(void) {
    bool res = false;
    uint8_t num = 0;
    for(num = 0; num <= 10; num++) {
        res = uart_flush(num);
    }
    return res;
}

bool uart_check(void) { return false; }

#define USART_ALL_INT (USART_CTSCF_INT | USART_ERR_INT | USART_BF_INT | USART_PERR_INT | USART_TDC_INT | USART_IDLE_INT)

bool UartIRQHandler(uint8_t num) {
    bool res = false;
    UartInfo_t* Info = UartGetInfo(num);
    if(Info) {
        flag_status ret = usart_interrupt_flag_get(Info->UARTx, USART_RDBF_FLAG);
        if(SET == ret) {
            /* read one byte from the receive data register */
            uint16_t rx_word = usart_data_receive(Info->UARTx);
            res = UartRxProcIsr(num, (uint8_t)rx_word);
            usart_interrupt_enable(Info->UARTx, USART_RDBF_INT, TRUE);
        } else {
            ret = usart_interrupt_flag_get(Info->UARTx, USART_TDBE_FLAG);
            if(SET == ret) {
                /* write one byte to the transmit data register */
                res = UartTxProcIsr(num);
                usart_interrupt_enable(Info->UARTx, USART_TDBE_INT, FALSE);
            } else {
                usart_interrupt_enable(Info->UARTx, USART_ALL_INT, FALSE);
            }
        }
    }
    return res;
}
