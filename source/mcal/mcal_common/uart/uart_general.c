#include "uart_mcal.h"

#include <string.h>

#include "code_generator.h"
#include "common_functions.h"
#include "compiler_const.h"
#include "data_utils.h"
#include "interrupt_mcal.h"
#include "log_config.h"
#include "std_includes.h"
#include "uart_config.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_ARRAY_DIAG
#include "array_diag.h"
#endif

#ifdef HAS_STRING_READER
#include "string_reader.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_HEAP
#include "heap_allocator.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif

COMPONENT_GET_CONFIG(Uart, uart)
COMPONENT_GET_NODE(Uart, uart)

#ifdef HAS_UART_EXT
_WEAK_FUN_ bool uart_check(void) {
    bool res = false;
    return res;
}
#endif

_WEAK_FUN_
bool uart_set_baudrate(uint8_t num, uint32_t baudrate) {
    bool res = false;
    return res;
}

static const UartIfInfo_t UartIfInfo[] = {
#ifdef HAS_UART0
    {
        .num = 0,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 0,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART1
    {
        .num = 1,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 1,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART2
    {
        .num = 2,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 2,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART3
    {
        .num = 3,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 3,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART4
    {
        .num = 4,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 4,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART5
    {
        .num = 5,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 5,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART6
    {
        .num = 6,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 6,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART7
    {
        .num = 7,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 7,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART8
    {
        .num = 8,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 8,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART9
    {
        .num = 9,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 9,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART10
    {
        .num = 10,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 10,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART11
    {
        .num = 11,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 11,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART12
    {
        .num = 12,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 12,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART13
    {
        .num = 13,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 13,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART14
    {
        .num = 14,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 14,
            },
        .valid = true,
    },
#endif

#ifdef HAS_UART15
    {
        .num = 15,
        .Interface =
            {
                .interface_name = INTERFACE_NAME_UART,
                .num = 15,
            },
        .valid = true,
    },
#endif
};

uint8_t UartInterfaceToNum(const InterfaceType_t Interface) {
    uint8_t num = 0xFF;
    uint32_t cnt = ARRAY_SIZE(UartIfInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(Interface.word == UartIfInfo[i].Interface.word) {
            num = UartIfInfo[i].num;
            break;
        }
    }
    return num;
}

#ifdef HAS_UART_EXT
InterfaceType_t UartNumToInterface(const uint8_t num) {
    InterfaceType_t interface_if = {0};

    uint32_t cnt = ARRAY_SIZE(UartIfInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(num == UartIfInfo[i].num) {
            interface_if = UartIfInfo[i].Interface;
            break;
        }
    }

    return interface_if;
}
#endif

bool uart_init_common(const UartConfig_t* const Config, UartHandle_t* const Node) {
    bool res = true;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->valid = Config->valid;
            Node->name = Config->name;

            Node->TxFifoArray = Config->TxFifoArray;
            Node->tx_buff_size = Config->tx_buff_size;

            Node->rx_buff_size = Config->rx_buff_size;
            Node->RxFifoArray = Config->RxFifoArray;
            Node->interrupts_on = Config->interrupts_on;
            Node->irq_priority = Config->irq_priority;
            Node->momve_method = Config->momve_method;

            Node->parity_check = Config->parity_check;
            Node->baud_rate = Config->baud_rate;
            Node->stop_bit_cnt = Config->stop_bit_cnt;
            Node->word_len_bit = Config->word_len_bit;

#ifdef HAS_UART_DMA
            const UartInfo_t* Info = UartGetInfo(Config->num);
            if(Info) {
                Node->DmaPadTx = Info->DmaPadTx;
                Node->DmaPadRx = Info->DmaPadRx;
                Node->dma = Config->dma;
            }
#endif
            res = true;
        }
    }
    return res;
}

bool uart_wait_tx_done_ll(UartHandle_t* Node) {
    bool res = true;
    if(Node) {
        Node->wait_iter = 0;
#ifdef HAS_UART_TX_TIMEOUT
#ifdef HAS_TIME
        bool time_out = false;
        uint32_t time_out_us = 0;
        (void)time_out_us;
        uint32_t baudrate = uart_get_cfg_baudrate(Node->num);
        uint32_t start_ms = time_get_ms32();
        uint32_t dutation_ms = 0;
        uint32_t cur_ms = 0;
        if(Node->tx_len) {
            time_out_us = uart_calc_transfer_time_us(baudrate, (uint32_t)Node->tx_len + 1);
        } else { // for first call tx_len==0
            time_out_us = uart_calc_transfer_time_us(baudrate, 150);
        }
#endif
#endif
        while(false == Node->tx_done) {
            Node->wait_iter++;
#ifdef HAS_UART_TX_TIMEOUT
#ifdef HAS_TIME
            cur_ms = time_get_ms32();
            dutation_ms = cur_ms - start_ms;
            if(UART_TX_TIME_OUT_MS < dutation_ms) {
                Node->tx_time_out_cnt++;
                Node->tx_done = true;
                res = false;
                break;
            }
#endif
#endif

            if(Node->tx_done) {
                res = true;
                break;
            }
        }
#ifdef HAS_UART_TX_TIMEOUT
#ifdef HAS_TIME
        if(false == time_out) {
            res = true;
        } else {
            res = false;
        }
#endif
#endif
    }
    return res;
}

#ifdef HAS_UART_EXT
uint32_t uart_calc_transfer_time_us(uint32_t baudrate, uint32_t bytes) {
    uint32_t tx_time_us = 0;
    float bit_time = 1.0f / ((float)baudrate);
    float byte_time = 0.0f;
    byte_time = (12.0f) * bit_time;
    float byte_train_duration = byte_time * ((float)bytes);
    tx_time_us = (uint32_t)(byte_train_duration * 1000000.0);
    return tx_time_us;
}
#endif

#ifdef HAS_UART_EXT
uint32_t uart_calc_transfer_time_ms(uint32_t baudrate, uint32_t bytes) {
    uint32_t tx_time_ms = 0;
    uint32_t tx_time_us = uart_calc_transfer_time_us(baudrate, bytes);
    tx_time_ms = tx_time_us / 1000;
    return tx_time_ms;
}
#endif

#ifdef HAS_UART_EXT
bool uart_calc_byte_rate(void) {
    bool res = false;
    uint8_t num = 0;
    for(num = 0; num < uart_get_cnt(); num++) {
        UartHandle_t* Node = UartGetNode(num);
        if(Node) {
            Node->rx_rate.cur = Node->cnt.byte_rx - Node->cnt_prev.byte_rx;
            Node->rx_rate.min = DATA_MIN(Node->rx_rate.min, Node->rx_rate.cur);
            Node->rx_rate.max = DATA_MAX(Node->rx_rate.max, Node->rx_rate.cur);
            Node->cnt_prev.byte_rx = Node->cnt.byte_rx;

            Node->tx_rate.cur = Node->cnt.byte_tx - Node->cnt_prev.byte_tx;
            Node->tx_rate.min = DATA_MIN(Node->tx_rate.min, Node->tx_rate.cur);
            Node->tx_rate.max = DATA_MAX(Node->tx_rate.max, Node->tx_rate.cur);
            Node->cnt_prev.byte_tx = Node->cnt.byte_tx;
        }
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_UART_EXT
bool uart_is_init(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        res = Node->init_done;
    }
    return res;
}
#endif

#ifdef HAS_UART_EXT
bool uart_send_banner(uint8_t num, char* pattern) {
    bool res = false;
    uint8_t banner[80] = {0};
    uint32_t i = 0;
    for(i = 0; i < sizeof(banner); i++) {
        banner[i] = (uint8_t)pattern[0];
    }
    banner[0] = 0x0A;
    banner[1] = 0x0D;
    banner[sizeof(banner) - 2] = 0x0A;
    banner[sizeof(banner) - 1] = 0x0D;
    res = uart_mcal_send(num, banner, sizeof(banner));
    memset(banner, 0, sizeof(banner));
    strcpy((char*)banner, pattern);
    res = uart_mcal_send(num, banner, strlen((char*)banner) + 1);
    return res;
}
#endif

#ifdef HAS_UART_EXT
bool print_banner(uint8_t num) {
    bool res = false;

#ifdef HAS_BOOTLOADER
    res = uart_send_banner(num, "BootLoader" CRLF);
#endif

#ifdef HAS_GENERIC
    res = uart_send_banner(num, "Generic" CRLF);
#endif

    return res;
}
#endif

#ifdef HAS_UART_EXT
bool uart_banner_init(void) {
    bool res = false;
#ifdef HAS_LOG
    res = print_banner(LOG_UART_NUM);
#endif
    return res;
}
#endif

#ifdef HAS_UART_EXT
bool uart_is_allowed(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        const UartConfig_t* Config = UartGetConfig(num);
        if(Config) {
            res = true;
        }
    }

    return res;
}
#endif

#ifdef HAS_UART_EXT
uint32_t uart_get_cfg_baudrate(uint8_t num) {
    uint32_t baudrate = UART_BAUDRATE_MIN;
    const UartConfig_t* Config = UartGetConfig(num);
    if(Config) {
        baudrate = Config->baud_rate;
    }
    return baudrate;
}
#endif

#if 0
bool uart_send_ll(UartHandle_t* Node, uint8_t* data, uint16_t size, bool is_wait) {
    bool res = false;
    if(Node) {
    // We send mainly from Stack.
    (void)is_wait;
    res = uart_is_allowed(Node->num);
    if(res) {
        if(data && size) {

                if(Node->init_done) {
                    Node->tx_buff = NULL;
                } else {
                    res = false;
                }
            } else {
                res = false;
            }
            if(res) {
                if(Node->tx_buff) {
                    /*print from heap*/
                    res = uart_wait_send_ll(Node->num, Node->tx_buff, size);
                    if(false == res) {
#ifdef HAS_LOG
                        LOG_ERROR(UART, "%u WaitSendErr", Node->num);
#endif
                    }
                } else {
                    /*Print ftom stack*/
                    res = uart_send_wait_ll(Node->num, data, size);
                    if(false == res) {
#ifdef HAS_LOG
                        LOG_ERROR(UART, "%u SendWaitErr", Node->num);
#endif
                    }
                }
            }

        } else {
#ifdef HAS_LOG
            LOG_ERROR(UART, "DataErr L:%u", size);
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(UART, "%u NotAllowed", Node->num);
#endif
    }
    return res;
}
#endif

_WEAK_FUN_ bool uart_tx_next(const uint8_t num) {
    bool res = false;
    return res;
}

#ifdef HAS_UART_EXT
_WEAK_FUN_ bool uart_init_one(uint8_t num) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_UART_EXT
_WEAK_FUN_
bool uart_get_baud_rate(uint8_t num, uint32_t* const baudrate) {
    bool res = true;
    return res;
}
#endif

#ifdef HAS_UART_EXT
_WEAK_FUN_ bool uart_wait_send_ll(UartHandle_t* Node, const uint8_t* const data, uint32_t len) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool uart_send_wait_ll(UartHandle_t* const Node, const uint8_t* const data, uint32_t len) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool uart_init_custom(void) {
    bool res = true;
    return res;
}

_WEAK_FUN_
bool uart_heartbeat_proc_one(uint8_t num) {
    bool res = true;
    return res;
}
#endif

#ifdef HAS_UART_EXT
_WEAK_FUN_ bool uart_send_ll(UartHandle_t* Node, uint8_t* data, uint16_t array_len, bool is_wait) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_UART_EXT
_WEAK_FUN_
bool uart_proc_one(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        uint32_t cnt = fifo_get_size(&Node->RxFifo);
        if(cnt) {
            uint32_t out_len = 0;
            uint8_t outArr[100] = {0};
            res = fifo_pull_array(&Node->RxFifo, outArr, sizeof(outArr), &out_len);
            if(res) {
                if(out_len) {
#ifdef HAS_ARRAY_DIAG
                    LOG_DEBUG(UART, "UART%u,Rx%u:[%s]", num, out_len, ArrayToStr((uint8_t*)outArr, out_len));
#endif
#ifdef HAS_LOG
                    LOG_DEBUG(UART, "UART%u,Rx%uByte", num, out_len);
#endif
                }
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_UART_EXT
_WEAK_FUN_
bool uart_flush(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        if(Node->init_done) {
#ifdef HAS_FIFO
            uint32_t cnt = 1;
            do {
                cnt = fifo_get_count(&Node->TxFifo);
                if(cnt) {
                    uint8_t TxBuff[50];
                    uint32_t out_len = 0;
                    res = fifo_pull_array(&Node->TxFifo, TxBuff, sizeof(TxBuff), &out_len);
                    if(res) {
                        if(out_len) {
                            res = uart_send_ll(Node, (uint8_t*)TxBuff, out_len, true);
                        } else {
                            res = false;
                        }
                    }
                }
            } while(cnt);
#endif /*HAS_FIFO*/
        }
    }
    return res;
}
#endif

/*Wait until a free spot appears in the queue*/
_WEAK_FUN_
bool uart_wait_fifo_space_ll(UartHandle_t* Node, uint32_t size) {
    bool res = false;
    if(Node->init_done) {
        uint32_t cnt = 0;
        uint32_t up_time_start = time_get_ms32();
        while(1) {
            cnt++;
            uint32_t spare = fifo_get_spare(&Node->TxFifo);
            if(size <= spare) {
                res = true;
                break;
            }
            uint32_t up_time = time_get_ms32();
            uint32_t diff = up_time - up_time_start;
            if(UART_TX_FIFO_WAIT_TIMEOUT_MS < diff) {
                res = false;
                break;
            }
        }
    } else {
        res = true;
    }
    return res;
}

_WEAK_FUN_
bool uart_mcal_send(const uint8_t num, const uint8_t* const data, uint32_t size) {
    bool res = false;
    if(size) {
        if(data) {
            UartHandle_t* Node = UartGetNode(num);
            if(Node) {
                uart_wait_fifo_space_ll(Node, size);
                res = interrupt_control_all(false);
#ifdef HAS_FIFO
                res = fifo_push_array(&Node->TxFifo, (uint8_t*)data, (uint32_t)size);
                if(false == res) {
                    Node->tx_error_cnt++;
                }
#endif
                uart_tx_next(num);
                res = interrupt_control_all(true);
            }
        } else {
            res = false;
        }
    } else {
        res = false;
    }

    return res;
}

#if 0
bool uart_mcal_send_v0(uint8_t num, const uint8_t* const data, uint32_t size) {
    bool res = false;
    if(size) {

        UartHandle_t* Node = UartGetNode(num);
#ifdef HAS_UART_EXT

#ifdef HAS_CORE
        res = core_is_interrupt();
#endif
        if(false == res) {
            uart_flush(num);

            if(data) {
                if(size) {
                    if(Node) {
#ifdef HAS_FIFO
                        res = fifo_push_array(&Node->TxFifo, (uint8_t*)data, (uint32_t)size);
                        if(false == res) {
                            Node->tx_error_cnt++;
                        }
#endif
                    }
                }
            }
            uart_flush(num);
        }

#else
        res = uart_send_wait_ll(Node, data, size);
#endif
    } else {
        res = true;
    }

    return res;
}
#endif

/*ISR code*/

#ifdef HAS_UART_DMA
_WEAK_FUN_
bool uart_dma_send(uint8_t num, const uint8_t* const data, uint32_t size) {
    bool res = false;
    res = uart_dma_send_wait(num, data, size);
    return res;
}

_WEAK_FUN_
bool uart_dma_send_wait(uint8_t num, const uint8_t* const data, uint32_t size) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        if(data) {
            if(size) {
                res = uart_dma_send_wait_ll(Node, data, size);
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_UART_EXT
_WEAK_FUN_
bool uart_send_wait(uint8_t num, const uint8_t* const data, uint32_t size) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        if(data) {
            if(size) {
#ifdef HAS_DMA_CHANNEL
                if(Node->dma.tx) {
#ifdef HAS_UART_DMA
                    res = uart_dma_send_wait_ll(Node, data, size);
#endif // HAS_UART_DMA
                }
#endif // HAS_DMA_CHANNEL
                if(!res) {
                    res = uart_send_wait_ll(Node, data, size);
                }
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_UART_EXT
_WEAK_FUN_
bool uart_wait_send(uint8_t num, const uint8_t* const data, uint32_t size) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        if(data) {
            if(size) {
                res = uart_wait_send_ll(Node, data, size);
            }
        }
    }
    return res;
}
#endif

_WEAK_FUN_
bool uart_writer(const uint8_t num) {
    bool res = false;
    InterfaceType_t interface_if;
    interface_if.num = num;
    interface_if.interface_name = INTERFACE_NAME_UART;
    res = writer_interface_set(interface_if);
    return res;
}

#ifdef HAS_UART_EXT
_WEAK_FUN_
bool UartIsValidConfig(const UartConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;

        ifn(Config->baud_rate) { res = false; }

        ifn(Config->momve_method) { res = false; }

        ifn(Config->rx_buff_size) { res = false; }

        ifn(Config->tx_buff_size) { res = false; }

        ifn(Config->RxFifoArray) { res = false; }

        ifn(Config->TxFifoArray) { res = false; }

        ifn(Config->stop_bit_cnt) { res = false; }

        ifn(Config->word_len_bit) { res = false; }
    }
    return res;
}
#endif

#ifdef HAS_UART_EXT
_WEAK_FUN_
bool uart_heartbeat_proc(void) {
    bool res = false;
    uint32_t ok = 0;
    uint32_t num = 0;
    for(num = 0; num <= UART_MAX_NUM; num++) {
        res = uart_heartbeat_proc_one(num);
        ok = ok_cnt_update(ok, res);
    }
    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif

COMPONENT_PROC_PATTERT_CNT(UART, UART, uart, UART_MAX_NUM)
COMPONENT_INIT_ANY_PATTERT_CNT(UART, UART, uart, UART_MAX_NUM)
