#include "uart_custom_isr.h"

#include "Device/compiler.h"
#include "x86x_misc.h"
#include "microcontroller_const.h"
#include "string_reader.h"
#include "uart_mcal.h"

static bool Uart_RxCallBack(uint8_t num, FCUART_HandleType* pHandle, FCUART_DataType* pTxData) {
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < pTxData->u32DataLen; i++) {
        uint8_t rx_byte = pTxData->pDatas[i];
        res = UartRxProcIsr(num, rx_byte);
    }
    return res;
}

//----------------------------------------

#ifdef HAS_UART1
void Uart1_ErrorCallBack(FCUART_HandleType* pHandle, uint32_t error) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(error)
}

void Uart1_RxCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) { Uart_RxCallBack(1, pHandle, pTxData); }

void Uart1_TxCompleteCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(pTxData)
    UartTxProcIsr(1);
}

void Uart1_TxEmptyCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(pTxData)
}

void Uart1_IdleCallBack(FCUART_HandleType* pHandle) {}

#endif

//----------------------------------------
#ifdef HAS_UART2
void Uart2_ErrorCallBack(FCUART_HandleType* pHandle, uint32_t error) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(error)
}

void Uart2_RxCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) { Uart_RxCallBack(2, pHandle, pTxData); }

void Uart2_TxCompleteCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(pTxData)
    UartTxProcIsr(2);
}

void Uart2_TxEmptyCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(pTxData)
}

void Uart2_IdleCallBack(FCUART_HandleType* pHandle) {}
#endif

#ifdef HAS_UART3
void Uart3_ErrorCallBack(FCUART_HandleType* pHandle, uint32_t error) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(error)
}

void Uart3_RxCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) { Uart_RxCallBack(3, pHandle, pTxData); }

void Uart3_TxCompleteCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(pTxData)
    UartTxProcIsr(3);
}

void Uart3_TxEmptyCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(pTxData)
}

void Uart3_IdleCallBack(FCUART_HandleType* pHandle) {}
#endif

#ifdef HAS_UART4
void Uart4_ErrorCallBack(FCUART_HandleType* pHandle, uint44_t error) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(error)
}

void Uart4_RxCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) { Uart_RxCallBack(4, pHandle, pTxData); }

void Uart4_TxCompleteCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(pTxData)
    UartTxProcIsr(4);
}

void Uart4_TxEmptyCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(pTxData)
}

void Uart4_IdleCallBack(FCUART_HandleType* pHandle) {}
#endif

#ifdef HAS_UART5
void Uart5_ErrorCallBack(FCUART_HandleType* pHandle, uint55_t error) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(error)
}

void Uart5_RxCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) { Uart_RxCallBack(5, pHandle, pTxData); }

void Uart5_TxCompleteCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(pTxData)
    UartTxProcIsr(5);
}

void Uart5_TxEmptyCallBack(FCUART_HandleType* pHandle, FCUART_DataType* pTxData) {
    PROCESS_UNUSED_VAR(pHandle)
    PROCESS_UNUSED_VAR(pTxData)
}

void Uart5_IdleCallBack(FCUART_HandleType* pHandle) {}
#endif
