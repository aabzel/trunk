#include "uart_mcal.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit_utils.h"
#include "x86x_misc.h"
#include "fifo_char.h"
#include "hal_diag.h"
#include "interrupt_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "microcontroller_types.h"
#include "module_driver_fcuart.h"
#include "module_driver_pcc.h"
#include "std_includes.h"
#include "string_reader.h"
#include "time_mcal.h"
#include "uart_custom_drv.h"
#include "uart_custom_isr.h"
#include "uart_custom_types.h"
#include "uart_types.h"

#ifdef HAS_DMA
#include "dma_mcal.h"
#endif

#ifdef HAS_HEAP
#include "heap_allocator.h"
#endif

static volatile uint8_t rx_buff[UART_COUNT][4];

#if 0
#define UART_TX_BUFF 300
static uint8_t tx_buff[UART_COUNT][UART_TX_BUFF];
#endif

#define UART_INFO_ONE(NUM)                                                                                             \
    {                                                                                                                  \
        .num = NUM,                                                                                                    \
        .valid = true,                                                                                                 \
        .irq_n = FCUART##NUM##_IRQn,                                                                                   \
        .clk_src_type = PCC_CLK_FCUART##NUM,                                                                           \
        .instance_type = UART_INSTANCE_##NUM,                                                                          \
        .RxCallBack = Uart##NUM##_RxCallBack,                                                                          \
        .TxEmptyCallBack = Uart##NUM##_TxEmptyCallBack,                                                                \
        .TxCompleteCallBack = Uart##NUM##_TxCompleteCallBack,                                                          \
        .ErrorCallBack = Uart##NUM##_ErrorCallBack,                                                                    \
    },

#ifdef HAS_UART0
#define UART0_INFO UART_INFO_ONE(0)
#else
#define UART0_INFO
#endif

#ifdef HAS_UART1
#define UART1_INFO UART_INFO_ONE(1)
#else
#define UART1_INFO
#endif

#ifdef HAS_UART2
#define UART2_INFO UART_INFO_ONE(2)
#else
#define UART2_INFO
#endif

#ifdef HAS_UART3
#define UART3_INFO UART_INFO_ONE(3)
#else
#define UART3_INFO
#endif

#ifdef HAS_UART4
#define UART4_INFO UART_INFO_ONE(4)
#else
#define UART4_INFO
#endif

#ifdef HAS_UART5
#define UART5_INFO UART_INFO_ONE(5)
#else
#define UART5_INFO
#endif

#ifdef HAS_UART6
#define UART6_INFO UART_INFO_ONE(6)
#else
#define UART6_INFO
#endif

#ifdef HAS_UART7
#define UART7_INFO UART_INFO_ONE(7)
#else
#define UART7_INFO
#endif

#ifdef HAS_UART8
#define UART8_INFO UART_INFO_ONE(8)
#else
#define UART8_INFO
#endif

#ifdef HAS_UART9
#define UART9_INFO UART_INFO_ONE(9)
#else
#define UART9_INFO
#endif

#ifdef HAS_UART10
#define UART10_INFO UART_INFO_ONE(10)
#else
#define UART10_INFO
#endif

#ifdef HAS_UART11
#define UART11_INFO UART_INFO_ONE(11)
#else
#define UART11_INFO
#endif

#ifdef HAS_UART12
#define UART12_INFO UART_INFO_ONE(12)
#else
#define UART12_INFO
#endif

#ifdef HAS_UART13
#define UART13_INFO UART_INFO_ONE(13)
#else
#define UART13_INFO
#endif

#ifdef HAS_UART14
#define UART14_INFO UART_INFO_ONE(14)
#else
#define UART14_INFO
#endif

#ifdef HAS_UART15
#define UART15_INFO UART_INFO_ONE(15)
#else
#define UART15_INFO
#endif

#ifdef HAS_UART16
#define UART16_INFO UART_INFO_ONE(16)
#else
#define UART16_INFO
#endif

#ifdef HAS_UART17
#define UART17_INFO UART_INFO_ONE(17)
#else
#define UART17_INFO
#endif

#define UART_INFO_ALL                                                                                                  \
    UART0_INFO                                                                                                         \
    UART1_INFO                                                                                                         \
    UART2_INFO                                                                                                         \
    UART3_INFO                                                                                                         \
    UART4_INFO                                                                                                         \
    UART5_INFO                                                                                                         \
    UART6_INFO                                                                                                         \
    UART7_INFO                                                                                                         \
    UART8_INFO                                                                                                         \
    UART9_INFO                                                                                                         \
    UART10_INFO                                                                                                        \
    UART11_INFO                                                                                                        \
    UART12_INFO                                                                                                        \
    UART13_INFO                                                                                                        \
    UART14_INFO                                                                                                        \
    UART15_INFO                                                                                                        \
    UART16_INFO                                                                                                        \
    UART17_INFO

static const UartInfo_t UartInfo[] = {UART_INFO_ALL};

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


static linflexd_uart_transfer_type_t UartMoveModeToTransferType(MoveMode_t momve_method) {
    linflexd_uart_transfer_type_t transition_type = FCUART_UART_USING_INTERRUPTS;
    switch(momve_method) {
    case MOVE_MODE_INTERRUPT:
        transition_type = FCUART_UART_USING_INTERRUPTS;
        break;
    case MOVE_MODE_DMA:
        transition_type = FCUART_UART_USING_DMA;
        break;
    default:
        transition_type = FCUART_UART_USING_INTERRUPTS;
        break;
    }
    return transition_type;
}

static bool UartComposeFc7300xConfig(const UartConfig_t* const Config, linflexd_uart_user_config_t* const Out) {
    bool res = false;
    if(Config) {
        if(Out) {
            Out->baudRate = Config->baud_rate;
            Out->parityCheck = Config->parity_check;
            Out->parityType = FCUART_UART_PARITY_EVEN;
            Out->stopBitsCount = UartStopBitsToYunTyStopBit(Config->stop_bit_cnt);
            Out->wordLength = UartWordLengthToYunTyWordLength(Config->word_len_bit);
            Out->txTransferType = UartMoveModeToTransferType(Config->momve_method);
            Out->rxTransferType = UartMoveModeToTransferType(Config->momve_method);
            ;
            Out->rxDMAChannel = 0;
            Out->txDMAChannel = 0;
            res = true;
        }
    }
    return res;
}
#endif

static FCUART_BitModeType UartWordLenToBitMode(uint8_t word_len_bit) {
    FCUART_BitModeType bit_mode = UART_BITMODE_8;
    switch(word_len_bit) {
    case 8:
        bit_mode = UART_BITMODE_8;
        break;
    case 9:
        bit_mode = UART_BITMODE_9;
        break;
    default:
        bit_mode = UART_BITMODE_8;
        break;
    }

    return bit_mode;
}

static FCUART_StopBitNumType UartStopBitsCntToStopBitNum(uint8_t stop_bit_cnt) {
    FCUART_StopBitNumType stop_bits = UART_STOPBIT_NUM_2;
    switch(stop_bit_cnt) {
    case 1:
        stop_bits = UART_STOPBIT_NUM_1;
        break;
    case 2:
        stop_bits = UART_STOPBIT_NUM_2;
        break;
    default:
        stop_bits = UART_STOPBIT_NUM_2;
        break;
    }

    return stop_bits;
}

static bool uart_compose_init_interrupts(const UartConfig_t* const Config, const UartInfo_t* const Info,
                                         FCUART_InitType* const init) {
    bool res = true;
    init->tInterruptCfg.bEnErrorInterrupt = Config->interrupts_on;
    init->tInterruptCfg.bEnRxInterrupt = Config->interrupts_on;
    init->tInterruptCfg.bEnTxInterrupt = Config->interrupts_on;
    init->tInterruptCfg.bEnIdleInterrupt = false;
    if(res) {
        res = false;
        init->tInterruptCfg.pIdleNotify = NULL;
        if(Info->RxCallBack) {
            init->tInterruptCfg.pRxNotify = Info->RxCallBack;
            if(Info->ErrorCallBack) {
                init->tInterruptCfg.pErrorNotify = Info->ErrorCallBack;
                if(Info->TxEmptyCallBack) {
                    init->tInterruptCfg.pTxEmptyNotify = Info->TxEmptyCallBack;
                    if(Info->TxCompleteCallBack) {
                        init->tInterruptCfg.pTxCompleteNotify = Info->TxCompleteCallBack;
                        res = true;
                    }
                }
            }
        }
    }
    return res;
}

static bool uart_compose_init(const UartConfig_t* const Config, const UartInfo_t* const Info,
                              FCUART_InitType* const init) {
    bool res = false;
    if(Config) {
        if(Info) {
            if(init) {
                uint32_t freq_hz = PCC_GetPccFunctionClock(Info->clk_src_type);
                if(freq_hz) {
                    /* check pcc clock if it is valid */
                    /* UART baud-rate           */
                    init->u32Baudrate = Config->baud_rate;
                    /* UART function clock      */
                    init->u32ClkSrcHz = freq_hz;
                    /* UART bit mode            */
                    init->eBitMode = UartWordLenToBitMode(Config->word_len_bit);
                    /* UART parity check enable */
                    init->bParityEnable = Config->parity_check;
                    ; /* Transmit timeout tick    */
                    init->u32TransmitTimeout = 0xFFFFFFFFU;
                    /* UART stop bit number     */
                    init->eStopBit = UartStopBitsCntToStopBitNum(Config->stop_bit_cnt);
                    /* UART rx fifo enable     */
                    init->bEnRxFifo = true;
                    /* UART rx fifo watermark         */
                    init->u8RxFifoWaterMark = 0;
                    init->eFifoRxIdleCharNum = FCUART_FIFO_RX_IDLE_DISABLE;
                    init->eIdleCharNum = FCUART_IDLE_CHARCTER_1;
                    init->eIdleStart = FCUART_START_AFTER_STOPBIT;

                    res = uart_compose_init_interrupts(Config, Info, init);

                    /* UART tx fifo enable      */
                    init->bEnTxFifo = true;
                    init->u8TxFifoWaterMark = 0U; /* UART tx fifo 16 bytes trigger */

                    UartHandle_t* Node = UartGetNode(Config->num);
                    if(Node) {
                        Node->RxMsg.pDatas = &(rx_buff[Config->num][0]); /* data buffer must set an array address */
                        Node->RxMsg.u32DataLen = 1;                      /* data buffer must set an array address */
                        init->tInterruptCfg.pRxBuf = &Node->RxMsg;
#if 0
                        Node->TxMsg.pDatas = &(tx_buff[Config->num][0]);   /* data buffer must set an array address */
                        Node->TxMsg.u32DataLen = UART_TX_BUFF;   /* data buffer must set an array address */
                        init->tInterruptCfg.pTxBuf = &Node->TxMsg;
#endif
                    }
                }
            }
        }
    }

    return res;
}
// LOG_ERROR can call uart_send_ll
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
#if 0
                   /*print from heap*/
                    res = uart_wait_send_ll(num, Node->tx_buff, array_len);
                    if(false == res) {
                        //LOG_ERROR(UART, "%u WaitSendErr", num);
                    }
#endif

                /*Print from stack*/
                res = uart_send_wait(num, array, array_len);
                if(false == res) {
                    // LOG_ERROR(UART, "%u SendWaitErr", num);
                }
            }

        } else {
            // LOG_ERROR(UART, "DataErr L:%u", array_len);
        }
    } else {
        // LOG_ERROR(UART, "%u NotAllowed", num);
    }
    return res;
}

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
bool uart_check(void) { return false; }


static bool uart_data_tx(uint8_t num, uint8_t* data, uint32_t size) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        if(data) {
            if(size) {
                uint32_t i = 0;
                for(i = 0; i < size; i++) {
#ifdef HAS_TIMER
                    timer_wait_us(100); // 500;1000 - ok
#endif
                    res = uart_wait_tx_done_ll(Node);
                    // wait_ms(1);
                }
            }
        }
    }
    return res;
}

bool uart_wait_send_ll(UartHandle_t* Node, const uint8_t* const data, uint32_t len) {
    bool res = false;
    if(Node) {
        //  LOG_DEBUG(UART, "UART%u Wait->Send 0x%p %u byte", Node->num, data, len);
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
                    // LOG_ERROR(UART, "%u TxErr %s", Node->num);
                }
            } else {
                Node->tx_done = true;
                // LOG_ERROR(UART, "%u WaitTxDoneErr", Node->num);
            }
        } else {
            // LOG_ERROR(UART, "ArgErr Len:%u Ptr:0x%p", len, data);
        }
    } else {
        // LOG_ERROR(UART, "%u NodeErr", Node->num);
    }
    return res;
}

#ifdef HAS_DMA
bool uart_dma_send_wait_ll(UartHandle_t* const Node, const uint8_t* const data, uint32_t size) {
    bool res = false;
    if(Node) {
    } else {
        // LOG_ERROR(UART, "NodeErr");
    }
    return res;
}
#endif

bool UartRetToRes(FCUART_ErrorType ret) {
    bool res = false;
    switch(ret) {
    case FCUART_ERROR_OK:
        res = true;
        break;
    case FCUART_ERROR_INVALID_VERSION:
        res = false;
        break;
    case FCUART_ERROR_FAILED:
        res = false;
        break;
    case FCUART_ERROR_INVALID_PARAM:
        res = false;
        break;
    case FCUART_ERROR_INVALID_SIZE:
        res = false;
        break;
    case FCUART_ERROR_INVALID_SEQUENCE:
        res = false;
        break;
    case FCUART_ERROR_TIMEOUT:
        res = false;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

bool uart_send_wait_ll(UartHandle_t* const Node, const uint8_t* const data, uint32_t len) {
    bool res = false;
    // TODO make sure that global ISR enabled
    // We send mainly from Stack. We need wait the end of transfer.
    if(Node) {
        if(data) {
            if(len) {
                if(Node->init_done) {
                    FCUART_DataType UartData = {0};
                    UartData.pDatas = data;
                    UartData.u32DataLen = len;
                    FCUART_ErrorType ret = FCUART_Transmit(&Node->Handle, &UartData);
                    res = UartRetToRes(ret);
                }
            }
        }
    } else {
        // LOG_ERROR(UART, "NodeErr");
    }
    return res;
}

bool uart_init_custom(void) {
    bool res = true;
    return res;
}

bool uart_read(uint8_t num, uint8_t* out_array, uint16_t array_len) {
    bool res = false;

    return res;
}

bool uart_set_baudrate(uint8_t num, uint32_t baudrate) {
    bool res = false;
    return res;
}

uint32_t UartGetBaseClock(uint8_t num) {
    uint32_t clock_hz = 0;

    return clock_hz;
}

bool uart_get_baud_rate(uint8_t num, uint32_t* const baudrate) {
    bool res = false;
    return res;
}

static bool uart_init_clock(const UartInfo_t* const Info) {
    bool res = false;
    /* start initial UART */
    PCC_CtrlType tPcc = {0};

    /* Configure PCC */
    tPcc.eClockName = Info->clk_src_type; // PCC_ClkSrcType PCC_CLK_FCUART1;
    tPcc.bEn = true;
    tPcc.eClkSrc = PCC_CLKGATE_SRC_PLL0DIV;
    tPcc.eDivider = PCC_CLK_UNINVOLVED;
#if PCC_DWP_SUPPORT
    tPcc.eCtrlOwner = PCC_CTRL_BY_ALL;
#endif
#if PCC_DWPLK_SUPPORT
    tPcc.bLockCtrl = false;
#endif

    PCC_StatusType pcc_status = PCC_SetPcc(&tPcc);
    if(PCC_STATUS_SUCCESS == pcc_status) {
        res = true;
    }
    return res;
}

static bool uart_verify(const UartHandle_t* const Node) {
    bool res = false;
    char str[20] = "UART";
    str[4] = 0x30 + Node->num;
    str[5] = '\r';
    str[6] = '\n';
    res = uart_send_wait_ll(Node, (uint8_t*)str, 7);
    // LOG_INFO(UART, "%u init Ok", Node->num);
    log_level_get_set(UART, LOG_LEVEL_INFO);
    return res;
}

static bool uart_init_fifo_one(const UartConfig_t* Config, UartHandle_t* Node) {
    bool res = false;
    if(false == Node->RxFifo.initDone) {
        // LOG_WARNING(UART, "RxFiFoInitLack");
    }
    if(Config->rx_buff_size) {
        if(Config->RxFifoArray) {
            res = fifo_init(&Node->RxFifo,  Config->RxFifoArray, (uint16_t)Config->rx_buff_size);
        }
    }

    if(Config->tx_buff_size) {
        if(Config->TxFifoArray) {
            res = fifo_init(&Node->TxFifo,  Config->TxFifoArray, (uint16_t)Config->tx_buff_size);
        }
    }
    return res;
}

bool uart_proc_one(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        uint32_t cnt = fifo_get_count(&Node->RxFifo);
        if(0 < cnt) {
            // LOG_DEBUG(UART, "UART%u,RxFifo:%u byte", num, cnt);
        }
        res = true;
    }
    return res;
}

bool uart_init_one(uint8_t num) {
    bool res = false;
    FCUART_InitType InitCfg = {0};
    const UartConfig_t* Config = UartGetConfig(num);
    UartInfo_t* Info = UartGetInfo(num);
    UartHandle_t* Node = UartGetNode(num);
    if(Config) {
        if(Node) {
            res = uart_init_common_one(Config, Node);
            res = uart_init_fifo_one(Config, Node);

            Node->rx_buff = (volatile uint8_t*)&rx_buff[num][0];
            Node->rx_buff_size = 1;
            // LOG_WARNING(UART, "UART%u,Init:%u,Bit/s", num, Config->baud_rate);
            if(Info) {
                Node->UARTx = Info->UARTx;
                Node->init_done = true;
            }
        }
    }
    if(res) {
        res = uart_init_clock(Info);
    }
    if(res) {
        res = false;
        FCUART_InitStructure(&Node->Handle);
        Node->Handle.eInstance = Info->instance_type;

        res = uart_compose_init(Config, Info, &InitCfg);
    }

    if(res) {
        res = interrupt_control(Info->irq_n, Config->interrupts_on);
    }

    if(res) {
        FCUART_ErrorType ret = FCUART_Init(&Node->Handle, &InitCfg);
        if(FCUART_ERROR_OK == ret) {
        } else {
            // LOG_ERROR(UART, "UART%u,InitErr:%u=%s", num, ret, FcUartErrorTypeToStr(ret));
        }

        res = uart_verify(Node);

        FCUART_StartReceive(&Node->Handle);
    }
    return res;
}
