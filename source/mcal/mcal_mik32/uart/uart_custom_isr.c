#include "uart_custom_isr.h"

#include "mcu32_memory_map.h"
#include "mik32_hal_usart.h"
#include "std_includes.h"
#ifdef HAS_STRING_READER
#include "string_reader.h"
#endif
#include "uart_mcal.h"

static bool uart_irq_proc_one(const uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        uint32_t epic_mask = (1U << Node->irq_n);
        uint32_t epic_raw_status = EPIC->RAW_STATUS;
        if(epic_mask == (epic_raw_status & epic_mask)) {
            /*Receiving data: writing to buffer */
            if(HAL_USART_RXNE_ReadFlag(&(Node->Handle))) {
                char rx_byte = HAL_USART_ReadByte(&(Node->Handle));
                res = UartRxProcIsrLL(Node, rx_byte);
                // Interfaces_t interface_if = UartNumToInterface(num);
                // string_reader_rx_byte(interface_if, rx_byte);
                HAL_USART_RXNE_ClearFlag(&(Node->Handle));
            }

            /* Transferring data: reading from buffer */
            if(HAL_USART_TXC_ReadFlag(&(Node->Handle))) {
                // HAL_USART_WriteByte(&(Node->Handle), buf[buf_pointer]);
                res = UartTxProcIsrLL(Node);
                HAL_USART_TXC_ClearFlag(&(Node->Handle));
            }
        }
    }
    return res;
}

bool uart_irq_proc(void) {
    bool res = false;
#ifdef HAS_UART0
    res = uart_irq_proc_one(0);
#endif

#ifdef HAS_UART1
    res = uart_irq_proc_one(1);
#endif
    return res;
}
