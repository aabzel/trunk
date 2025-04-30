#include "uart_mcal.h"

#include <string.h>

#include "code_generator.h"
#include "common_functions.h"
#include "compiler_const.h"
#include "data_utils.h"

#include "std_includes.h"

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

#ifdef HAS_UART_EXT
/*TODO make TABLE*/
Interfaces_t UartNumToInterface(uint8_t num) {
    Interfaces_t interface_if = IF_UNDEF;
    switch(num) {
#ifdef HAS_UART0
    case 0:
        interface_if = IF_UART0;
        break;
#endif

#ifdef HAS_UART1
    case 1:
        interface_if = IF_UART1;
        break;
#endif

#ifdef HAS_UART2
    case 2:
        interface_if = IF_UART2;
        break;
#endif

#ifdef HAS_UART3
    case 3:
        interface_if = IF_UART3;
        break;
#endif

#ifdef HAS_UART4
    case 4:
        interface_if = IF_UART4;
        break;
#endif

#ifdef HAS_UART5
    case 5:
        interface_if = IF_UART5;
        break;
#endif

#ifdef HAS_UART6
    case 6:
        interface_if = IF_UART6;
        break;
#endif

#ifdef HAS_UART7
    case 7:
        interface_if = IF_UART7;
        break;
#endif

#ifdef HAS_UART8
    case 8:
        interface_if = IF_UART8;
        break;
#endif

#ifdef HAS_UART9
    case 9:
        interface_if = IF_UART9;
        break;
#endif

#ifdef HAS_UART10
    case 10:
        interface_if = IF_UART10;
        break;
#endif

#ifdef HAS_UART11
    case 11:
        interface_if = IF_UART11;
        break;
#endif

#ifdef HAS_UART12
    case 12:
        interface_if = IF_UART12;
        break;
#endif

#ifdef HAS_UART13
    case 13:
        interface_if = IF_UART13;
        break;
#endif

#ifdef HAS_UART14
    case 14:
        interface_if = IF_UART14;
        break;
#endif
    default:
        break;
    }
    return interface_if;
}
#endif

bool uart_init_general_one(const UartConfig_t* const Config, UartHandle_t* const Node) {
    bool res = true;
    if(Config) {
        if(Node) {
            Node->valid = Config->valid;
            Node->TxFifoArray = Config->TxFifoArray;
            Node->tx_buff_size = Config->tx_buff_size;

            Node->rx_buff_size = Config->rx_buff_size;
            Node->RxFifoArray = Config->RxFifoArray;

            Node->momve_method = Config->momve_method;
            Node->parity_check = Config->parity_check;
            Node->baud_rate = Config->baud_rate;
            Node->stop_bit_cnt = Config->stop_bit_cnt;
            Node->word_len_bit = Config->word_len_bit;
            Node->num = Config->num;
            Node->name = Config->name;
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
    float bit_time = 1.0 / ((float)baudrate);
    float byte_time = 0.0;
    byte_time = (12.0) * bit_time;
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
            Node->rx_rate.min = MIN(Node->rx_rate.min, Node->rx_rate.cur);
            Node->rx_rate.max = MAX(Node->rx_rate.max, Node->rx_rate.cur);
            Node->cnt_prev.byte_rx = Node->cnt.byte_rx;

            Node->tx_rate.cur = Node->cnt.byte_tx - Node->cnt_prev.byte_tx;
            Node->tx_rate.min = MIN(Node->tx_rate.min, Node->tx_rate.cur);
            Node->tx_rate.max = MAX(Node->tx_rate.max, Node->tx_rate.cur);
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
bool uart_send_ll(uint8_t num, uint8_t* data, uint16_t size, bool is_wait) {
    bool res = false;
    // We send mainly from Stack.
    (void)is_wait;
    res = uart_is_allowed(num);
    if(res) {
        if(data && size) {
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
                if(Node->tx_buff) {
                    /*print from heap*/
                    res = uart_wait_send_ll(num, Node->tx_buff, size);
                    if(false == res) {
#ifdef HAS_LOG
                        LOG_ERROR(UART, "%u WaitSendErr", num);
#endif
                    }
                } else {
                    /*Print ftom stack*/
                    res = uart_send_wait_ll(num, data, size);
                    if(false == res) {
#ifdef HAS_LOG
                        LOG_ERROR(UART, "%u SendWaitErr", num);
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
        LOG_ERROR(UART, "%u NotAllowed", num);
#endif
    }
    return res;
}
#endif

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
_WEAK_FUN_ bool uart_wait_send_ll(UartHandle_t* Node, const uint8_t* const data, size_t len) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool uart_send_wait_ll(UartHandle_t* Node, const uint8_t* const data, uint16_t len) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool uart_init_custom(void) {
    bool res = true;
    return res;
}
#endif

#ifdef HAS_UART_EXT
_WEAK_FUN_ bool uart_send_ll(uint8_t num, uint8_t* data, uint16_t array_len, bool is_wait) {
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
        FifoIndex_t cnt = fifo_get_size(&Node->RxFifo);
        if(cnt) {
            FifoIndex_t out_len = 0;
            char outArr[100] = {0};
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
bool uart_flush(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        if(Node->init_done) {
#ifdef HAS_FIFO
            FifoIndex_t cnt = 1;
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
#endif /*HAS_FIFO*/
        }
    }
    return res;
}
#endif

bool uart_mcal_send(uint8_t num, const uint8_t* const data, uint16_t size) {
    bool res = false;
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
                    res = fifo_push_array(&Node->TxFifo, (char* const)data, (FifoIndex_t)size);
#endif
                }
            }
        }
        uart_flush(num);
    }

#else
    res = uart_send_wait_ll(Node, data, size);
#endif

    return res;
}

/*ISR code*/

#ifdef HAS_UART_DMA
bool uart_dma_send_wait(uint8_t num, const uint8_t* const data, size_t size) {
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

bool uart_send_wait(uint8_t num, const uint8_t* const data, size_t size) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        if(data) {
            if(size) {
                if(Node->dma.tx) {
#ifdef HAS_UART_DMA
                    res = uart_dma_send_wait_ll(Node, data, size);
#endif
                } else {
                    res = uart_send_wait_ll(Node, data, size);
                }
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_UART_EXT
bool uart_wait_send(uint8_t num, const uint8_t* const data, size_t size) {
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

#ifdef HAS_UART_EXT
bool UartIsValidConfig(const UartConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;

        if(res) {
            if(Config->baud_rate) {
                res = true;
            } else {
                res = false;
            }
        }

        if(res) {
            if(Config->momve_method) {
                res = true;
            } else {
                res = false;
            }
        }

        if(res) {
            if(Config->rx_buff_size) {
                res = true;
            } else {
                res = false;
            }
        }

        if(res) {
            if(Config->tx_buff_size) {
                res = true;
            } else {
                res = false;
            }
        }

        if(res) {
            if(Config->RxFifoArray) {
                res = true;
            } else {
                res = false;
            }
        }

        if(res) {
            if(Config->TxFifoArray) {
                res = true;
            } else {
                res = false;
            }
        }

        if(res) {
            if(Config->stop_bit_cnt) {
                res = true;
            } else {
                res = false;
            }
        }

        if(res) {
            if(Config->word_len_bit) {
                res = true;
            } else {
                res = false;
            }
        }
    }
    return res;
}
#endif

COMPONENT_PROC_PATTERT_CNT(UART, UART, uart, UART_MAX_NUM)

COMPONENT_INIT_PATTERT_CNT(UART, UART, uart, UART_MAX_NUM)
