#ifndef USART_CUSTOM_ISR_H
#define USART_CUSTOM_ISR_H

#include "std_includes.h"
#include "microcontroller_types.h"
#include "module_driver_fcuart.h"

#ifdef HAS_UART1
void Uart1_IdleCallBack(FCUART_HandleType *pHandle);
void Uart1_ErrorCallBack(FCUART_HandleType *pHandle, uint32_t error);
void Uart1_RxCallBack(FCUART_HandleType *pHandle, FCUART_DataType *pTxData);
void Uart1_TxEmptyCallBack(FCUART_HandleType *pHandle, FCUART_DataType *pTxData);
void Uart1_TxCompleteCallBack(FCUART_HandleType *pHandle, FCUART_DataType *pTxData);
#endif

#ifdef HAS_UART2
void Uart2_IdleCallBack(FCUART_HandleType* pHandle) ;
void Uart2_ErrorCallBack(FCUART_HandleType *pHandle, uint32_t error);
void Uart2_RxCallBack(FCUART_HandleType *pHandle, FCUART_DataType *pTxData);
void Uart2_TxEmptyCallBack(FCUART_HandleType *pHandle, FCUART_DataType *pTxData);
void Uart2_TxCompleteCallBack(FCUART_HandleType *pHandle, FCUART_DataType *pTxData);
#endif

#ifdef HAS_UART3
void Uart3_IdleCallBack(FCUART_HandleType* pHandle) ;
void Uart3_ErrorCallBack(FCUART_HandleType *pHandle, uint32_t error);
void Uart3_RxCallBack(FCUART_HandleType *pHandle, FCUART_DataType *pTxData);
void Uart3_TxEmptyCallBack(FCUART_HandleType *pHandle, FCUART_DataType *pTxData);
void Uart3_TxCompleteCallBack(FCUART_HandleType *pHandle, FCUART_DataType *pTxData);
#endif

#ifdef HAS_UART4
void Uart4_IdleCallBack(FCUART_HandleType* pHandle) ;
void Uart4_ErrorCallBack(FCUART_HandleType *pHandle, uint32_t error);
void Uart4_RxCallBack(FCUART_HandleType *pHandle, FCUART_DataType *pTxData);
void Uart4_TxEmptyCallBack(FCUART_HandleType *pHandle, FCUART_DataType *pTxData);
void Uart4_TxCompleteCallBack(FCUART_HandleType *pHandle, FCUART_DataType *pTxData);
#endif


#endif /* USART_CUSTOM_ISR_H  */
