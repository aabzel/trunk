#include "uart_bsp.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "common_functions.h"
#ifdef HAS_CORE
#include "core_driver.h"
#endif

#include "data_utils.h"
#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_HEAP
#include "heap_allocator.h"
#endif

#ifdef HAS_TIMER
#include "timer_drv.h"
#endif

#ifdef HAS_UART
#include "uart_config.h"
#include "uart_drv.h"
#endif /*HAS_UART*/

#ifdef HAS_UART
bool uart_common_init(uint8_t uart_num) {
    UartHandle_t* UartNode = UartGetNode(uart_num);
    if(UartNode) {
        memset(UartNode, 0x00, sizeof(UartHandle_t));
        UartNode->rx_rate.min = 0xFFFFFFFF;
    }
    return true;
}
#endif /*HAS_UART*/

uint32_t calc_transfer_time_us(uint32_t baudrate, uint32_t bytes) {
    uint32_t tx_time_us = 0;
    double bit_time = 1.0 / (double)baudrate;
    double byte_time = 0.0;
    byte_time = (12.0) * bit_time;
    double byte_train_duration = byte_time * ((double)bytes);
    tx_time_us = (uint32_t)(byte_train_duration * 1000000.0);
    return tx_time_us;
}

uint32_t calc_transfer_time_ms(uint32_t baudrate, uint32_t bytes) {
    uint32_t tx_time_ms = 0;
    double bit_time = 1.0 / (float)baudrate;
    double byte_time = 0.0;
    byte_time = (12.0) * bit_time;
    double byte_train_duration = byte_time * bytes;
    tx_time_ms = (uint32_t)(byte_train_duration * 1000.0);
    return tx_time_ms;
}

#ifdef HAS_MCU
bool uart_calc_byte_rate(void) {
    bool res = false;
    uint8_t uart_num = 0;
    for(uart_num = 0; uart_num < uart_get_cnt(); uart_num++) {
        UartHandle_t* UartNode = UartGetNode(uart_num);
        if(UartNode) {
            UartNode->rx_rate.cur = UartNode->cnt.byte_rx - UartNode->cnt_prev.byte_rx;
            UartNode->rx_rate.min = min32u(UartNode->rx_rate.min, UartNode->rx_rate.cur);
            UartNode->rx_rate.max = max32u(UartNode->rx_rate.max, UartNode->rx_rate.cur);
            UartNode->cnt_prev.byte_rx = UartNode->cnt.byte_rx;

            UartNode->tx_rate.cur = UartNode->cnt.byte_tx - UartNode->cnt_prev.byte_tx;
            UartNode->tx_rate.min = min32u(UartNode->tx_rate.min, UartNode->tx_rate.cur);
            UartNode->tx_rate.max = max32u(UartNode->tx_rate.max, UartNode->tx_rate.cur);
            UartNode->cnt_prev.byte_tx = UartNode->cnt.byte_tx;
        }
        res = true;
    }
    return res;
}
#endif

bool uart_is_init(uint8_t uart_num) {
    bool res = false;
    UartHandle_t* UartNode = UartGetNode(uart_num);
    if(UartNode) {
        res = UartNode->init_done;
    }
    return res;
}

#ifdef HAS_UART
bool uart_send_banner(uint8_t uart_num, char* pattern) {
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
    res = uart_mcal_send(uart_num, banner, sizeof(banner));
    memset(banner, 0, sizeof(banner));
    strcpy((char*)banner, pattern);
    res = uart_mcal_send(uart_num, banner, strlen((char*)banner) + 1);
    return res;
}
#endif

bool print_banner(uint8_t uart_num) {
    bool res = false;

#ifdef HAS_BOOTLOADER
    res = uart_send_banner(uart_num, "bootloader") && res;
#endif
#ifdef HAS_GENERIC
    res = uart_send_banner(uart_num, "generic") && res;
#endif

    return res;
}

const UartConfig_t* UartGetConfNode(uint8_t uart_num) {
    const UartConfig_t* ConfNode = NULL;
    uint32_t i = 0;
    uint32_t uart_cnt = uart_get_cnt();
    for(i = 0; i < uart_cnt; i++) {
        if(uart_num == UartConfigLuT[i].num) {
            if(UartConfigLuT[i].valid) {
                ConfNode = &UartConfigLuT[i];
                break;
            }
        }
    }
    return ConfNode;
}

UartHandle_t* UartGetNode(uint8_t uart_num) {
    UartHandle_t* InstNode = NULL;
    uint32_t i = 0;
    uint32_t uart_cnt = uart_get_cnt();
    for(i = 0; i < uart_cnt; i++) {
        if(uart_num == UartInstance[i].num) {
            if(UartInstance[i].valid) {
                InstNode = &UartInstance[i];
                break;
            }
        }
    }
    return InstNode;
}

bool uart_is_allowed(uint8_t uart_num) {
    bool res = false;
    UartHandle_t* UartNode = UartGetNode(uart_num);
    if(UartNode) {
        const UartConfig_t* UartConfNode = UartGetConfNode(uart_num);
        if(UartConfNode) {
            res = true;
        }
    }

    return res;
}

uint32_t uart_get_cfg_baudrate(uint8_t uart_num) {
    uint32_t baudrate = UART_MIN_BAUDRATE;
    const UartConfig_t* UartConfNode = UartGetConfNode(uart_num);
    if(UartConfNode) {
        baudrate = UartConfNode->baud_rate;
    }
    return baudrate;
}

#if 0
bool uart_send_ll(uint8_t uart_num, uint8_t* array, uint16_t array_len, bool is_wait) {
    bool res = false;
    // We send mainly from Stack.
    (void)is_wait;
    res = uart_is_allowed(uart_num);
    if(res) {
        if(array && array_len) {
            UartHandle_t* UartNode = UartGetNode(uart_num);
            if(UartNode) {
                if(UartNode->init_done) {
                    UartNode->tx_buff = NULL;
                } else {
                    res = false;
                }
            } else {
                res = false;
            }
            if(res) {
                if(UartNode->tx_buff) {
                    /*print from heap*/
                    res = uart_wait_send_ll(uart_num, UartNode->tx_buff, array_len);
                    if(false == res) {
#ifdef HAS_LOG
                        LOG_ERROR(UART, "%u WaitSendErr", uart_num);
#endif
                    }
                } else {
                    /*Print ftom stack*/
                    res = uart_send_wait_ll(uart_num, array, array_len);
                    if(false == res) {
#ifdef HAS_LOG
                        LOG_ERROR(UART, "%u SendWaitErr", uart_num);
#endif
                    }
                }
            }

        } else {
#ifdef HAS_LOG
            LOG_ERROR(UART, "DataErr L:%u", array_len);
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(UART, "%u NotAllowed", uart_num);
#endif
    }
    return res;
}
#endif

bool uart_mcal_send(uint8_t uart_num, uint8_t* array, uint16_t array_len) {
    bool res = false;
#ifdef HAS_NORTOS
    res = core_is_interrupt();
#endif
    if(false == res) {
        uart_flush(uart_num);

        if(array && array_len) {
            UartHandle_t* UartNode = UartGetNode(uart_num);
            if(UartNode) {
#ifdef HAS_FIFO
                res = fifo_push_array(&UartNode->TxFifo, (char* const)array, (FifoIndex_t)array_len);
#endif
            }
        }
        uart_flush(uart_num);
    }

    return res;
}
