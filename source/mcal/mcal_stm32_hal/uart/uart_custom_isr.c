#include "uart_custom_isr.h"

#include "hal_mcal.h"
#include "stm32fx_hal.h"
#include "uart_custom_drv.h"
#include "uart_mcal.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* uart_handle) {
    UartHandle_t *Node = UartHandleToNode(uart_handle);
    if(Node) {
        UartProcIsrLL(Node);
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_UART_Receive_IT(&Node->uart_h, (uint8_t*) Node->rx_data, 1);
        if(HAL_OK == ret) {
            bool res = UartRxProcIsrLL(Node, Node->rx_data[0]);
            if(!res) {
                Node->error_cnt++;
            }
        } else {
            Node->error_cnt++;
        }
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* uart_handle) {
    UartHandle_t *Node = UartHandleToNode(uart_handle);
    if(Node) {
        UartProcIsrLL(Node);
        UartTxProcIsrLL(Node);
        uart_tx_next_ll(Node);
    }
}

void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef* huart) {
    UartHandle_t *Node = UartHandleToNode(huart);
    if(Node) {
        UartDmaCallBackTxHalfCpltLL(Node);
    }
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef* huart) {
    UartHandle_t *Node = UartHandleToNode(huart);
    if(Node) {
        UartDmaCallBackRxHalfCpltLL( Node );
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef* huart) {
    UartHandle_t *Node = UartHandleToNode(huart);
    if(Node) {
        UartProcIsrLL(Node);
        UartErrorProcIsrLL(Node);
    }
}

/**
 * @brief  UART Abort Complete callback.
 * @param  huart UART handle.
 * @retval None
 */
void HAL_UART_AbortCpltCallback(UART_HandleTypeDef* huart) {
    UartHandle_t *Node = UartHandleToNode(huart);
    if(Node) {
        UartProcIsrLL(Node);
        Node->abort_cnt++;
        Node->abort = true;
    }
}
