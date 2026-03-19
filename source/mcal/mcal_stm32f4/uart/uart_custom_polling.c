#include "uart_custom_polling.h"

#include "hal_diag.h"
#include "time_mcal.h"

bool uart_wait_send_ll(UartHandle_t* Node, const uint8_t* const data, uint32_t len) {
    bool res = false;
    if(Node) {
        //LOG_DEBUG(UART, "UART%u,Wait->Send,Data:0x%p,%u byte", Node->num, data, len);
        if(Node->init_done && len && data) {
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
                }
            } else {
                Node->tx_done = true;
            }
        }
    }
    return res;
}

bool uart_send_wait_ll(UartHandle_t* const Node, const uint8_t* const data, uint32_t len) {
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
        }
    }
    return res;
}

bool uart_send_ll(uint8_t num, uint8_t* data, uint16_t size) {
    bool res = false;
    // We send mainly from Stack.
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

                /*print from heap*/
#if 0
                    res = uart_wait_send_ll(Node, Node->tx_buff, size);
                    if(false == res) {
                    }
#endif

                /*Print from stack*/
                res = uart_send_wait_ll(Node, data, size);
            }
        }
    }
    return res;
}
