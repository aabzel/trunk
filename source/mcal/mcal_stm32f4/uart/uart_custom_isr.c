#include "uart_custom_isr.h"

#include "hal_mcal.h"
#include "stm32f4xx_hal.h"
#include "uart_custom_drv.h"
#include "uart_mcal.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* uart_handle) {
    int8_t num = 0;
    num = get_uart_index(uart_handle->Instance);
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_UART_Receive_IT(&Node->uart_h, (uint8_t*)Node->rx_data, 1);
        if(HAL_OK == ret) {
            bool res = UartRxProcIsr(num, Node->rx_data[0]);
            if(res) {

            } else {
                Node->error_cnt++;
            }
        } else {
            Node->error_cnt++;
        }
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* uart_handle) {
    int8_t num = 0;
    num = get_uart_index(uart_handle->Instance);
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        Node->tx_done = true;
        Node->tx_cnt++;
        Node->cnt.byte_tx++;
        uart_tx_next(num);
    }
}
