#include "uart_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/zephyr.h>

#ifdef HAS_LOG
#include "log.h"
#endif /*HAS_LOG*/

#ifdef HAS_BT1026
#include "bt1026_drv.h"
#endif /*HAS_BT1026*/

#include "uart_bsp.h"
#ifdef HAS_UART_ISR
#include "uart_isr.h"
#endif /*HAS_UART_ISR*/
#include "uart_types.h"
#include "uart_zephyr_types.h"
#include "uart_zephyr_dep.h"

// https://docs.zephyrproject.org/3.1.0/hardware/peripherals/uart.html

/*
 * Read characters from UART until line end is detected. Afterwards push the
 * data to the message queue.
static void serial_cb(const struct device *dev, void *user_data){
}
 */

//#define UART_DEVICE_NODE DT_CHOSEN(zephyr_shell_uart)
// static const struct device *uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);
// static const struct device *uart_dev = DEVICE_DT_GET(DT_N_S_soc_S_peripheral_50000000_S_uart_8000);

const UartZephyrInto_t UartInto[] = {
#ifdef HAS_UART0
    [0] =
        {
            .num = 0,
            .dev = DEVICE_DT_GET(DT_N_S_soc_S_peripheral_50000000_S_uart_8000),
            .valid = true,
#ifdef HAS_UART_ISR
            .uart_isr_callback = NULL,
#endif /*HAS_UART_ISR*/
        },
#endif

#ifdef HAS_UART1
    [1] =
        {
            .num = 1,
            .dev = DEVICE_DT_GET(DT_N_S_soc_S_peripheral_50000000_S_uart_9000),
            .valid = true,
#ifdef HAS_UART_ISR
            .uart_isr_callback = NULL,
#endif /*HAS_UART_ISR*/
        },
#endif

#ifdef HAS_UART2
    [2] =
        {
            .num = 2,
            .dev = DEVICE_DT_GET(DT_N_S_soc_S_peripheral_50000000_S_uart_b000),
            .valid = true,
#ifdef HAS_UART_ISR
            .uart_isr_callback = uart2_callback,
#endif /*HAS_UART_ISR*/
        },
#endif

#ifdef HAS_UART3
    [3] =
        {
            .num = 3,
            .dev = DEVICE_DT_GET(DT_N_S_soc_S_peripheral_50000000_S_uart_c000),
            .valid = true,
#ifdef HAS_UART_ISR
            .uart_isr_callback = NULL,
#endif /*HAS_UART_ISR*/

        },
#endif

};

const struct device* UartNum2Dev(uint8_t num) {
    const struct device* Node = NULL;
    uint32_t cnt = ARRAY_SIZE(UartInto);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(UartInto[i].num == num) {
            Node = UartInto[i].dev;
            break;
        }
    }
    return Node;
}

const UartZephyrInto_t* UartNum2DevNode(uint8_t num) {
    const UartZephyrInto_t* DevNode = NULL;
    uint32_t cnt = ARRAY_SIZE(UartInto);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(UartInto[i].num == num) {
            DevNode = &UartInto[i];
            break;
        }
    }
    return DevNode;
}

#if 0
static const struct device *uart_devs[UART_COUNT]={
};
#endif

#if 0
static const struct device *uart_devs[4]={
[0] = DEVICE_DT_GET(DT_CAT(DT_PATH(soc,peripheral_50000000),uart_8000)),
[1] = DEVICE_DT_GET(DT_CAT(DT_PATH(soc,peripheral_50000000),uart_9000)),
[2] = DEVICE_DT_GET(DT_CAT(DT_PATH(soc,peripheral_50000000),uart_b000)),
[3] = DEVICE_DT_GET(DT_CAT(DT_PATH(soc,peripheral_50000000),uart_c000)),
};
#endif

static bool uart_zephyr_sent(struct device* uart_dev, char* buf, uint32_t len) {
    bool res = false;
    if(uart_dev) {
        if(buf && len) {
            uint32_t i = 0;
            for(i = 0; i < len; i++) {
                uart_poll_out(uart_dev, buf[i]);
            }
            res = true;
        }
    }
    return res;
}

bool uart_wait_send_ll(uint8_t uart_num, uint8_t* tx_buffer, uint16_t length) {
    bool res = false;
    const struct device* uart_device = UartNum2Dev(uart_num);
    if(uart_device) {
        res = uart_zephyr_sent(uart_device, tx_buffer, length);
    }
    return res;
}

bool uart_send_wait_ll(uint8_t uart_num, uint8_t* tx_buffer, uint16_t length) {
    bool res = false;
    if(tx_buffer) {
        if(length) {
            const struct device* uart_device = UartNum2Dev(uart_num);
            if(uart_device) {
                res = uart_zephyr_sent(uart_device, tx_buffer, length);
            }
        }
    }
    return res;
}

bool uart_send_ll(uint8_t uart_num, uint8_t* array, uint16_t array_len, bool is_wait) {
    bool res = false;
    // We send mainly from Stack. Print ftom stack
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
        } else {
            LOG_ERROR(UART, "DataErr Len:%u", array_len);
        }
    } else {
        LOG_ERROR(UART, "%u NotAllowed", uart_num);
    }

    if(res) {
        res = uart_send_wait_ll(uart_num, array, array_len);
        if(false == res) {
            LOG_ERROR(UART, "%u SendWaitErr", uart_num);
        }
    }
    return res;
}

#if 0
bool uart_mcal_send(uint8_t uart_num, uint8_t* array, uint16_t array_len) {
    bool res = false;
    res = uart_send_wait_ll(uart_num, array, array_len);
    if(res) {
    }
    return res;
}
#endif

static uint8_t Rx2Buff[100];

bool uart_init_ll(uint8_t uart_num) {
    bool res = false;
    LOG_INFO(UART, "%u Init", uart_num);
    UartHandle_t* UartNode = UartGetNode(uart_num);
    const UartConfig_t* UartConfNode = UartGetConfNode(uart_num);
    if(UartNode) {
        const UartZephyrInto_t* DevNode = UartNum2DevNode(uart_num);
        if(DevNode && DevNode->dev) {
            res = device_is_ready(DevNode->dev);
            if(res) {
                LOG_INFO(UART, "%u Device found!", uart_num);
                if(2==uart_num){
                    //int ret= uart_rx_buf_rsp(DevNode->dev,Rx2Buff,sizeof(Rx2Buff));
                    //LOG_INFO(UART, "ret %d", ret);
                }
#ifdef HAS_UART_ISR
                LOG_INFO(UART, "%u ISRmode", uart_num);
                if(DevNode->uart_isr_callback) {
                    uart_irq_callback_user_data_set(DevNode->dev, DevNode->uart_isr_callback, NULL);
                    uart_irq_rx_enable(DevNode->dev);
                }
#endif /*HAS_UART_ISR*/

            } else {
                LOG_ERROR(UART, "%u Device not found!", uart_num);
                return;
            }
            if(UartConfNode) {
#ifdef HAS_FIFO
                if(UartConfNode->rx_buff_size) {
                    UartNode->RxFifo.array = (char*)malloc(UartConfNode->rx_buff_size);
                    if(UartNode->RxFifo.array) {
                        res = fifo_init(&UartNode->RxFifo, UartNode->RxFifo.array, UartConfNode->rx_buff_size);
                    } else {
                        res = false;
                    }
                }
#endif /*HAS_FIFO*/
            }
        }
    }

    char str[40];
    snprintf(str, sizeof(str), "Init_UART%u" CRLF, uart_num);
    uint32_t msg_len = strlen(str);
    res = uart_send_wait_ll(uart_num, str, msg_len);

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
    for(i = 0; i <= UART_COUNT; i++) {
        UartHandle_t* UartNode = UartGetNode(i);
        const UartConfig_t* UartConfNode = UartGetConfNode(i);
        if(UartNode && UartConfNode) {
#ifdef HAS_LOG
            LOG_DEBUG(UART, "%u SpotConfig", i);
#endif /*HAS_LOG*/
            res = uart_init_ll(UartNode->num);
            if(res) {
                UartNode->init_done = true;
#ifdef HAS_LOG
                LOG_INFO(UART, "%u Init" LOG_OK, UartNode->num);
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

bool uart_read(uint8_t uart_num, uint8_t* out_array, uint16_t array_len) {
    bool res = false;
    // int uart_poll_in(const struct device *dev, unsigned char *p_char)
    return res;
}

bool uart_set_baudrate(uint8_t uart_num, uint32_t baudrate) {
    bool res = false;
    return res;
}

uint32_t uart_get_baud_rate(uint8_t uart_num, uint16_t* mantissa, uint16_t* fraction, uint8_t* over_sampling) {
    uint32_t baud_rate = 0;
    return baud_rate;
}

bool uart_check(void) { return false; }

bool uart_poll(uint8_t uart_num, uint8_t* out_array, uint16_t size, uint16_t* read_cnt) {
    bool res = false;
    return res;
}

bool uart_poll_read(uint8_t uart_num) {
    bool res = false;
    const struct device* uart_device = UartNum2Dev(uart_num);
    if(uart_device) {
        LOG_PARN(UART, "Proc UART%u", uart_num);
        UartHandle_t* UartNode = UartGetNode(uart_num);
        if(UartNode) {
            unsigned char rx_byte = '=';
            int ret = -1;
            while(1) {
            	//ret= uart_fifo_read(uart_device,  &rx_byte, 1); HangOn
                ret = uart_poll_in(uart_device, &rx_byte);
                if(0 == ret) {
                    LOG_DEBUG(UART, "UART%u Rx 0x%02x=[%c]", uart_num, rx_byte, rx_byte);
#ifdef HAS_BT1026
                    if(Bt1026Config.uart_num == uart_num) {
                        res = fifo_push(&UartNode->RxFifo, rx_byte);
                        if(false == res) {
                        	LOG_ERROR(UART, "UART%u PushErr", uart_num);
                            UartNode->RxFifo.err_cnt++;
                        }
                    }
#endif /*HAS_BT1026*/
                } else {
                    LOG_PARN(UART, "%u RxErr %d=%s [%c]", uart_num, ret, ErrNo2Str(ret), rx_byte);
                    UartNode->error_cnt++;
                    break;
                }
#ifdef HAS_ZEPHYR_RTOS
        k_msleep(5);
#endif
            }
        } else {
            LOG_DEBUG(UART, "%u NodeError", uart_num);
        }
    } else {
        LOG_PARN(UART, "%u NoInTree", uart_num);
    }
    return res;
}

bool uart_proc(void) {
    bool res = false;
    LOG_PARN(UART, "Proc Max%u", UART_MAX_NUM);
    uint8_t uart_num = 0;
    for(uart_num = 0; uart_num <= UART_MAX_NUM; uart_num++) {
        res = uart_flush(uart_num);
#ifndef HAS_UART_ISR
        res = uart_poll_read(uart_num);
#endif /*HAS_UART_ISR*/
    }
    return res;
}
