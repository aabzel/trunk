#include "uart_mcal.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit_utils.h"
#include "clock_mcal.h"
#include "code_generator.h"
#include "hal_mcal.h"
#include "interrupt_mcal.h"
#include "log.h"
#include "std_includes.h"
#include "stm32f4xx_hal.h"
#include "time_mcal.h"
#include "uart_custom_types.h"
#ifdef HAS_HEAP
#include "heap_allocator.h"
#endif

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif

#ifdef HAS_CLI
#include "cli_config.h"
#include "string_reader.h"
#endif

//#include "sys_config.h"

static uint32_t UasrtWordSizeBitsToWordLength(const uint8_t word_len_bit) {
    uint32_t word_length = UART_WORDLENGTH_8B;
    switch(word_len_bit) {
    case 8:
        word_length = UART_WORDLENGTH_8B;
        break;
    case 9:
        word_length = UART_WORDLENGTH_9B;
        break;
    default:
        word_length = UART_WORDLENGTH_8B;
        break;
    }
    return word_length;
}

static uint32_t UasrtStopBitToStopBits(const uint8_t stop_bit_cnt) {
    uint32_t stop_bits = UART_STOPBITS_2;
    switch(stop_bit_cnt) {
    case 1:
        stop_bits = UART_STOPBITS_1;
        break;
    case 2:
        stop_bits = UART_STOPBITS_2;
        break;
    default:
        stop_bits = UART_STOPBITS_2;
        break;
    }
    return stop_bits;
}

static USART_TypeDef* UartGetBase(uint8_t num) {
    USART_TypeDef* USARTx = NULL;
    const UartInfo_t* Info = UartGetInfo(num);
    if(Info) {
        USARTx = Info->UARTx;
    }
    return USARTx;
}

int8_t get_uart_index(const USART_TypeDef* const USARTx) {
    int8_t num = -1;

    const UartInfo_t* Info = UartUSARTxToInfo(USARTx);
    if(Info) {
        num = Info->num;
    }

    return num;
}

bool uart_init_node(UartHandle_t* Node) {
    bool res = true;
    return res;
}

#define UART_INFO_ONE(NUM, PHY, CLKBUS, IRQ_N)                                                                         \
    {                                                                                                                  \
        .num = NUM,                                                                                                    \
        .UARTx = PHY,                                                                                                  \
        .clock_bus = CLKBUS,                                                                                           \
        .irq_n = IRQ_N,                                                                                                \
        .valid = true,                                                                                                 \
    },

#ifdef USART1
#define UART_INFO_UART1 UART_INFO_ONE(1, USART1, CLOCK_BUS_APB2, USART1_IRQn)
#else
#define UART_INFO_UART1
#endif

#ifdef USART2
#define UART_INFO_UART2 UART_INFO_ONE(2, USART2, CLOCK_BUS_APB1, USART2_IRQn)
#else
#define UART_INFO_UART2
#endif

#ifdef USART3
#define UART_INFO_UART3 UART_INFO_ONE(3, USART3, CLOCK_BUS_APB1, USART3_IRQn)
#else
#define UART_INFO_UART3
#endif

#ifdef UART4
#define UART_INFO_UART4 UART_INFO_ONE(4, UART4, CLOCK_BUS_APB1, UART4_IRQn)
#else
#define UART_INFO_UART4
#endif

#ifdef UART5
#define UART_INFO_UART5 UART_INFO_ONE(5, UART5, CLOCK_BUS_APB1, UART5_IRQn)
#else
#define UART_INFO_UART5
#endif

#ifdef USART6
#define UART_INFO_UART6 UART_INFO_ONE(6, USART6, CLOCK_BUS_APB2, USART6_IRQn)
#else
#define UART_INFO_UART6
#endif

#ifdef UART7
#define UART_INFO_UART7 UART_INFO_ONE(7, UART7, CLOCK_BUS_APB1, UART7_IRQn)
#else
#define UART_INFO_UART7
#endif

#ifdef UART8
#define UART_INFO_UART8 UART_INFO_ONE(8, UART8, CLOCK_BUS_APB1, UART8_IRQn)
#else
#define UART_INFO_UART8
#endif

#ifdef UART9
#define UART_INFO_UART9 UART_INFO_ONE(9, UART9, CLOCK_BUS_APB2, UART9_IRQn)
#else
#define UART_INFO_UART9
#endif

#ifdef UART10
#define UART_INFO_UART10 UART_INFO_ONE(10,UART10,CLOCK_BUS_APB?,UART10_IRQn)
#else
#define UART_INFO_UART10
#endif

#define UART_INFO_ALL                                                                                                  \
    UART_INFO_UART1                                                                                                    \
    UART_INFO_UART2                                                                                                    \
    UART_INFO_UART3                                                                                                    \
    UART_INFO_UART4                                                                                                    \
    UART_INFO_UART5                                                                                                    \
    UART_INFO_UART6                                                                                                    \
    UART_INFO_UART7                                                                                                    \
    UART_INFO_UART8                                                                                                    \
    UART_INFO_UART9                                                                                                    \
    UART_INFO_UART10

/*see Figure 4. STM32F413xG/H block diagram*/
static const UartInfo_t UartInfo[] = {UART_INFO_ALL};

const UartInfo_t* UartUSARTxToInfo(const USART_TypeDef* const USARTx) {
    const UartInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(UartInfo);
    for(i = 0; i < cnt; i++) {
        if(USARTx == UartInfo[i].UARTx) {
            if(UartInfo[i].valid) {
                Info = &UartInfo[i];
                break;
            }
        }
    }
    return Info;
}

const UartInfo_t* UartGetInfo(uint8_t num) {
    UartInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(UartInfo);
    for(i = 0; i < cnt; i++) {
        if(num == UartInfo[i].num) {
            if(UartInfo[i].valid) {
                Info = &UartInfo[i];
                break;
            }
        }
    }
    return Info;
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
        HAL_NVIC_SetPriority(UART5_IRQn, 0, 0);
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

#ifdef UART8
    if(UART8 == uart_handle->Instance) {
        __HAL_RCC_UART8_CLK_ENABLE();

        HAL_NVIC_SetPriority(UART8_IRQn, 7, 0);
        HAL_NVIC_EnableIRQ(UART8_IRQn);
    }
#endif
}

uint32_t UartGetBaseClock(const uint8_t num) {
    uint32_t clock_hz = 0;
    const UartInfo_t* Info = UartGetInfo(num);
    if(Info) {
        clock_hz = clock_freq_get(Info->clock_bus);
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
#ifdef USART1
    if(uart_handle->Instance == USART1) {
        __HAL_RCC_USART1_CLK_DISABLE();

        /* USART1 interrupt Deinit */
        HAL_NVIC_DisableIRQ(USART1_IRQn);
    }
#endif

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

#ifdef UART5
    if(uart_handle->Instance == UART5) {
        __HAL_RCC_UART5_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(UART5_IRQn);
    }
#endif

#ifdef USART6
    if(USART6 == uart_handle->Instance) {
        __HAL_RCC_USART6_CLK_DISABLE();

        HAL_NVIC_DisableIRQ(USART6_IRQn);
    }
#endif

#ifdef UART7
    if(uart_handle->Instance == UART7) {
        __HAL_RCC_UART7_CLK_DISABLE();

        HAL_NVIC_DisableIRQ(UART7_IRQn);
    }
#endif

#ifdef UART8
    if(uart_handle->Instance == UART8) {
        __HAL_RCC_UART8_CLK_DISABLE();

        HAL_NVIC_DisableIRQ(UART8_IRQn);
    }
#endif
}

bool uart_check(void) { return false; }

bool uart_heartbeat_proc_one(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        char str[60] = "UART";
        strcpy(str, "");
        snprintf(str, sizeof(str), "%sUART%u,", str, num);
        snprintf(str, sizeof(str), "%sSN%u,", str, Node->sn++);
        uint32_t len = strlen(str);
        uart_mcal_send(num, (uint8_t*)str, len);

        HAL_StatusTypeDef ret = HAL_UART_Receive_IT(&Node->uart_h, (uint8_t*)Node->rx_data, 1);
        res = HAL_retToRes(ret);
    }
    return res;
}

/*can be called form ISR TODO rename to uart_tx_next */
bool uart_tx_next(const uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        // uint32_t count = fifo_get_count(&Node->TxFifo);
        if(Node->init_done) {
            if(HAL_UART_STATE_READY == Node->uart_h.gState) {
                uint32_t outLen = 0;
                res = fifo_pull_array(&Node->TxFifo, Node->txBlock, sizeof(Node->txBlock), &outLen);
                if(res) {
                    HAL_StatusTypeDef ret = HAL_UART_Transmit_IT(&Node->uart_h, Node->txBlock, outLen);
                    res = HAL_retToRes(ret);
                    if(res) {
                        Node->tx_start_ms = time_get_ms32();
                        Node->tx_done = false;
                    }
                }
            }
        }
    }
    return res;
}

bool uart_proc_one(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
#if 0
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_UART_Receive_IT(&Node->uart_h, (uint8_t*) Node->rx_data, 1);
        res = HAL_retToRes(ret);
#endif
        UartInfo_t* Info = UartGetInfo(num);
        if(Info) {
            res = interrupt_is_active(Info->irq_n);
            if(!res) {
                res = interrupt_control(Info->irq_n, true);
            }
        }
    }
    return res;
}

static bool uart_init_hal_struct(const UartConfig_t* Config, UART_InitTypeDef* const Init) {
    bool res = true;
    Init->BaudRate = Config->baud_rate;
    Init->WordLength = UasrtWordSizeBitsToWordLength(Config->word_len_bit);
    Init->StopBits = UasrtStopBitToStopBits(Config->stop_bit_cnt);
    Init->HwFlowCtl = UART_HWCONTROL_NONE;
    Init->Mode = UART_MODE_TX_RX;
    Init->OverSampling = UART_OVERSAMPLING_16;
    Init->Parity = UART_PARITY_NONE;
    return res;
}

bool uart_init_one(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        const UartConfig_t* Config = UartGetConfig(num);
        if(Config) {
#ifdef HAS_UART_DIAG
            LOG_WARNING(UART, "%s", UartConfigToStr(Config));
#endif
            res = UartIsValidConfig(Config);
            if(res) {
                UartInfo_t* Info = UartGetInfo(num);
                if(Info) {
                    Node->uart_h.Instance = Info->UARTx; // UartGetBase(num);

                    res = uart_init_common(Config, Node);
                    res = uart_init_node(Node);
                    res = interrupt_control(Info->irq_n, Config->interrupts_on);
                    res = interrupt_set_priority(Info->irq_n, Config->irq_priority);
                    res = uart_init_hal_struct(Config, &Node->uart_h.Init);
                    if(Node->uart_h.Instance) {
                        HAL_StatusTypeDef ret = HAL_ERROR;
                        interrupt_control_all(false);
                        ret = HAL_UART_Init(&Node->uart_h);
                        res = HAL_retToRes(ret);
                        if(res) {
                            LOG_INFO(UART, "UART%u,init,Ok", num);
                            Node->init_done = true;
                            ret = HAL_UART_Receive_IT(&Node->uart_h, (uint8_t*)Node->rx_data, 1);
                            res = HAL_retToRes(ret);
                            char str[40] = "UART";
                            res = uart_mcal_send(num, (uint8_t*)str, 4);
                            snprintf(str, sizeof(str), "UART%u", num);
                            uint32_t len = strlen(str);
                            res = uart_mcal_send(num, (uint8_t*)str, len);
                        } else {
                            LOG_ERROR(UART, "UART%u,init,Err", num);
                        }

                        interrupt_control_all(true);
                    }
                }
            }
        }
    }
    return res;
}
