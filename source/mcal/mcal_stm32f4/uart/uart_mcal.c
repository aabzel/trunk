#include "uart_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit_utils.h"
#include "code_generator.h"
#include "hal_diag.h"
#ifdef HAS_HEAP
#include "heap_allocator.h"
#endif
#include "log.h"
#include "stm32f4xx_hal.h"
#include "time_mcal.h"
#include "uart_custom_types.h"

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

static USART_TypeDef* UartGetBase(uint8_t num) {
    USART_TypeDef* USARTx = NULL;
    switch(num) {
#ifdef USART1
    case 1:
        USARTx = USART1;
        break;
#endif /**/

#ifdef USART2
    case 2:
        USARTx = USART2;
        break;
#endif /**/

#ifdef USART3
    case 3:
        USARTx = USART3;
        break;
#endif /**/

#ifdef UART4
    case 4:
        USARTx = UART4;
        break;
#endif /**/

#ifdef UART5
    case 5:
        USARTx = UART5;
        break;
#endif /**/

#ifdef USART6
    case 6:
        USARTx = USART6;
        break;
#endif /**/

#ifdef UART7
    case 7:
        USARTx = UART7;
        break;
#endif /**/

#ifdef UART8
    case 8:
        USARTx = UART8;
        break;
#endif /**/

#ifdef UART9
    case 9:
        USARTx = UART9;
        break;
#endif /**/

#ifdef UART10
    case 10:
        USARTx = UART10;
        break;
#endif /**/
    default:
        break;
    }
    return USARTx;
}

int8_t get_uart_index(USART_TypeDef* USARTx) {
    int8_t num = -1;
#ifdef USART1
    if(USART1 == USARTx) {
        num = 1;
    }
#endif /*USART1*/

#ifdef USART2
    if(USART2 == USARTx) {
        num = 2;
    }
#endif

#ifdef USART3
    if(USART3 == USARTx) {
        num = 3;
    }
#endif

#ifdef UART4
    if(UART4 == USARTx) {
        num = 4;
    }
#endif

#ifdef UART5
    if(UART5 == USARTx) {
        num = 5;
    }
#endif

#ifdef USART3
    if(USART3 == USARTx) {
        num = 3;
    }
#endif

#ifdef UART4
    if(UART4 == USARTx) {
        num = 4;
    }
#endif

#ifdef UART5
    if(UART5 == USARTx) {
        num = 5;
    }
#endif

#ifdef USART6
    if(USART6 == USARTx) {
        num = 6;
    }
#endif

#ifdef UART7
    if(UART7 == USARTx) {
    }
#endif

#ifdef UART7
    if(UART7 == USARTx) {
        num = 7;
    }
#endif /*UART7*/

#ifdef UART8
    if(UART8 == USARTx) {
        num = 8;
    }
#endif /*UART8*/

#ifdef UART9
    if(UART9 == USARTx) {
        num = 9;
    }
#endif /*UART9*/

#ifdef UART10
    if(UART10 == USARTx) {
        num = 10;
    }
#endif /*UART10*/

    return num;
}

bool uart_init_one(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        const UartConfig_t* Config = UartGetConfig(num);
        if(Config) {

            res=uart_init_general_one(Config, Node);

            // res=fifo_init(&Node->TxFifo, Node->tx_array, UART_TX_FIFO_SIZE);
            Node->rx_buff = (volatile uint8_t*)&rx_buff[num][0];
            Node->rx_buff_size = 1;
            LOG_WARNING(UART, "UART%u Init %u Bit/s", num, Config->baud_rate);
            Node->uart_h.Init.BaudRate = Config->baud_rate;
            Node->uart_h.Init.HwFlowCtl = UART_HWCONTROL_NONE;
            Node->uart_h.Init.Mode = UART_MODE_TX_RX;
            Node->uart_h.Init.OverSampling = UART_OVERSAMPLING_16;
            Node->uart_h.Init.Parity = UART_PARITY_NONE;
            Node->uart_h.Init.StopBits = UART_STOPBITS_1;
            Node->uart_h.Init.WordLength = UART_WORDLENGTH_8B;
            Node->uart_h.Instance = UartGetBase(num);
            if(Node->uart_h.Instance) {
                HAL_StatusTypeDef ret = HAL_ERROR;
                ret = HAL_UART_Init(&Node->uart_h);
                if(HAL_OK != ret) {
                    res = false;
                    LOG_ERROR(UART, "%u init Err", num);
                } else {
                    res = true;
                    LOG_INFO(UART, "%u init Ok", num);
                    Node->init_done = true;
                }
                ret = HAL_UART_Receive_IT(&Node->uart_h, (uint8_t*)Node->rx_buff, 1);
                if(HAL_OK != ret) {
                    res = false;
                }
                char str[40] = "UART";
                uart_mcal_send(num, (uint8_t*)str, 4);
                snprintf(str, sizeof(str), "UART%u", num);
                size_t len = strlen(str);
                uart_mcal_send(num, (uint8_t*)str, len);
            }
        }
    }
    return res;
}

/*see Figure 4. STM32F413xG/H block diagram*/
static const UartInfo_t UartInfo[] = {
#ifdef USART1
    {
        .num = 1,
        .clock_hz = APB2_CLOCK_HZ,
    },
#endif

#ifdef USART2
    {
        .num = 2,
        .clock_hz = APB1_CLOCK_HZ,
    },
#endif

#ifdef USART3
    {
        .num = 3,
        .clock_hz = APB1_CLOCK_HZ,
    },
#endif

#ifdef UART4
    {
        .num = 4,
        .clock_hz = APB1_CLOCK_HZ,
    },
#endif

#ifdef UART5
    {
        .num = 5,
        .clock_hz = APB1_CLOCK_HZ,
    },
#endif

#ifdef USART6
    {
        .num = 6,
        .clock_hz = APB2_CLOCK_HZ,
    },
#endif

#ifdef UART7
    {
        .num = 7,
        .clock_hz = APB1_CLOCK_HZ,
    },
#endif

#ifdef UART8
    {
        .num = 8,
        .clock_hz = APB1_CLOCK_HZ,
    },
#endif

#ifdef UART9
    {
        .num = 9,
        .clock_hz = APB2_CLOCK_HZ,
    },
#endif

#ifdef UART10
    {
        .num = 10,
        .clock_hz = APB2_CLOCK_HZ,
    },
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

static bool uart_wait_tx_done_ll(UartHandle_t* Node) {
    bool res = true;
    if(Node) {
        Node->wait_iter = 0;
#ifdef HAS_UART_TX_TIMEOUT
        uint8_t num = get_uart_index(Node->uart_h.Instance);
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

            if(HAL_UART_STATE_READY == Node->uart_h.gState) {
                res = true; // was true
                break;
            }
        } while(false == Node->tx_done);
    }

    return res;
}
#endif

bool uart_wait_send_ll(UartHandle_t* Node, const uint8_t* const data, size_t len) {
    bool res = false;
    LOG_DEBUG(UART, "UART%u,Wait->Send,Data:0x%p,%u byte", Node->num, data, len);
    if(Node) {
        if(Node->init_done && (len) && data) {
            res = uart_wait_tx_done_ll(Node);
            if(res) {
                Node->tx_done = false;
                Node->tx_len = len;
                HAL_StatusTypeDef ret = HAL_ERROR;
                ret = HAL_UART_Transmit_IT(&Node->uart_h, data, len);
                if(HAL_OK == ret) {
                    res = true;
                } else {
                    res = false;
                    LOG_ERROR(UART, "%u TxErr %s", Node->num, HalStatus2Str(ret));
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

bool uart_send_wait_ll(UartHandle_t* Node, const uint8_t* const  data, uint16_t len){
    bool res = false;
    // TODO make sure that global ISR enabled
    // We send mainly from Stack. We need wait the end of transfer.
    if(Node) {
        if(Node->init_done && (len) && data) {
            uint32_t init_tx_cnt = Node->tx_cnt;
#ifdef HAS_UART_TX_TIMEOUT
            uint32_t baudrate = uart_get_cfg_baudrate(Node->num);
            uint32_t time_out_us = uart_calc_transfer_time_us(baudrate, (uint32_t)len);
#endif
            uint32_t dutation_us = 0;
            uint32_t cur_us = 0;
            uint32_t start_us = time_get_us();
            HAL_StatusTypeDef stat = HAL_ERROR;
            stat = HAL_UART_Transmit_IT(&Node->uart_h, data, len);
            if(HAL_OK == stat) {
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

                    if(HAL_UART_STATE_READY == Node->uart_h.gState) {
                        res = true;
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
    USART_TypeDef* UARTx = UartGetBase(num);

    if(UARTx) {
        UartRegCtrl1_t Reg;
        Reg.reg_val = UARTx->CR1;
        uint32_t pclk = HAL_RCC_GetPCLK1Freq();
        if(1 == Reg.over8) {
            UARTx->BRR = UART_BRR_SAMPLING8(pclk, baudrate);
        } else {
            UARTx->BRR = UART_BRR_SAMPLING16(pclk, baudrate);
        }
        res = true;
    }

    return res;
}

void HAL_UART_MspInit(UART_HandleTypeDef* uart_handle) {
#ifdef USART1
    if(USART1 == uart_handle->Instance) {
        __HAL_RCC_USART1_CLK_ENABLE();
        HAL_NVIC_SetPriority(USART1_IRQn, 7, 7);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
#endif

#ifdef USART2
    if(USART2 == uart_handle->Instance) {
        __HAL_RCC_USART2_CLK_ENABLE();

        HAL_NVIC_SetPriority(USART2_IRQn, 3, 3);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
    }
#endif

#ifdef USART3
    if(USART3 == uart_handle->Instance) {
        __HAL_RCC_USART3_CLK_ENABLE();

        HAL_NVIC_SetPriority(USART3_IRQn, 3, 3);
        HAL_NVIC_EnableIRQ(USART3_IRQn);
    }
#endif

#ifdef UART4
    if(UART4 == uart_handle->Instance) {
        __HAL_RCC_UART4_CLK_ENABLE();

        HAL_NVIC_SetPriority(UART4_IRQn, 7, 7);
        HAL_NVIC_EnableIRQ(UART4_IRQn);
    }
#endif

#ifdef UART5
    if(UART5 == uart_handle->Instance) {
        __HAL_RCC_UART5_CLK_ENABLE();

        HAL_NVIC_SetPriority(UART5_IRQn, 7, 7);
        HAL_NVIC_EnableIRQ(UART5_IRQn);
    }
#endif

#ifdef USART6
    if(USART6 == uart_handle->Instance) {
        __HAL_RCC_USART6_CLK_ENABLE();

        HAL_NVIC_SetPriority(USART6_IRQn, 7, 0);
        HAL_NVIC_EnableIRQ(USART6_IRQn);
    }
#endif

#ifdef UART7
    if(UART7 == uart_handle->Instance) {
        __HAL_RCC_UART7_CLK_ENABLE();

        HAL_NVIC_SetPriority(UART7_IRQn, 7, 0);
        HAL_NVIC_EnableIRQ(UART7_IRQn);
    }
#endif
}

static uint32_t UartGetBaseClock(uint8_t num) {
    uint32_t clock_hz = 0;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(UartInfo); i++) {
        if(num == UartInfo[i].num) {
            clock_hz = UartInfo[i].clock_hz;
            break;
        }
    }
    return clock_hz;
}


uint32_t uart_baud_rate_get_ll(uint8_t num, uint16_t* mantissa, uint16_t* fraction, uint8_t* over_sampling) {
    uint32_t baud_rate = 0;
    USART_TypeDef* UARTx = UartGetBase(num);
    if(UARTx) {
        UartRegCtrl1_t RegCtrl1;
        RegCtrl1.reg_val = UARTx->CR1;
        UartRegBaud_t Reg;
        Reg.reg_val = UARTx->BRR;
        (*fraction) = Reg.fraction;
        (*mantissa) = Reg.mantissa;
        if(1 == RegCtrl1.over8) {
            (*over_sampling) = 8U;
        } else {
            (*over_sampling) = 16U;
        }
        baud_rate = UartGetBaseClock(num) / ((*over_sampling) * ((*mantissa) + (*fraction) / (*over_sampling)));
    }
    return baud_rate;
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uart_handle) {
#ifdef USART2
    if(uart_handle->Instance == USART2) {
        __HAL_RCC_USART2_CLK_DISABLE();

        /* USART2 interrupt Deinit */
        HAL_NVIC_DisableIRQ(USART2_IRQn);
    }
#endif

#ifdef USART3
    if(USART3 == uart_handle->Instance) {
        __HAL_RCC_USART3_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(USART3_IRQn);
    }
#endif

#ifdef UART4
    if(uart_handle->Instance == UART4) {
        __HAL_RCC_UART4_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(UART4_IRQn);
    }
#endif

#ifdef UART7
    if(uart_handle->Instance == UART7) {
        __HAL_RCC_UART7_CLK_DISABLE();

        HAL_NVIC_DisableIRQ(UART7_IRQn);
    }
#endif
#ifdef USART6
    if(USART6 == uart_handle->Instance) {
        __HAL_RCC_USART6_CLK_DISABLE();

        HAL_NVIC_DisableIRQ(USART6_IRQn);
    }
#endif
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
                    res = uart_wait_send_ll(Node, Node->tx_buff, array_len);
                    if(false == res) {
                        LOG_ERROR(UART, "%u WaitSendErr", num);
                    }
#endif

                /*Print from stack*/
                res = uart_send_wait_ll(Node, array, array_len);
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

#if 0
bool proc_uarts(void) {
    bool res = false;
    uint8_t num = 0;
    for(num = 0; num <= 10; num++) {
        res = uart_flush(num);
    }
    return res;
}
#endif

bool uart_check(void) { return false; }
