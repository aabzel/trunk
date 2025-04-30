#include "uart_custom_isr.h"

#include "microcontroller_const.h"
#include "string_reader.h"
#include "uart_mcal.h"
#ifdef HAS_HEAP
#include "heap_allocator.h"
#endif

bool UART_TxCpltCallback(usart_type* UARTx) {
    int8_t num = 0;
    bool res = false;
    num = get_uart_index(UARTx);
    UartHandle_t* Node = UartGetNode((uint8_t)num);
    if(Node) {
        Node->tx_cnt++;
        Node->tx_done = true;
        Node->tx_cpl_cnt++;
        Node->cnt.byte_tx++;
#ifdef HAS_HEAP
        res = h_free((void*)Node->tx_buff);
        if(false == res) {
            Node->err_heap++;
        }
#endif
        res = true;
    }
    return res;
}

bool UART_RxCpltCallback(usart_type* UARTx) {
    g_uart_rx_cnt++;
    int8_t num = 0;
    bool res = false;
    num = get_uart_index(UARTx);
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        Node->rx_cnt++;
        Node->rx_done = true;
        usart_receiver_enable(UARTx, TRUE);
        Interfaces_t interface_if = UartNumToInterface(num);
        res = false;
        (void)res;
        res = string_reader_rx_byte(interface_if, Node->rx_buff[0]);
#if 0
#ifdef HAS_CLI
        if(CliInstance[0].if_num == num) {
            string_reader_rx_callback(&CliInstance[0].Reader, Node->rx_buff[0]);
        }
#endif /*HAS_CLI*/
#endif

#ifdef HAS_BC127
        if(Bc127Config.num == num) {
            bool res = fifo_push(&Node->RxFifo, Node->rx_buff[0]);
            if(false == res) {
                Node->RxFifo.err_cnt++;
            }
        }
#endif /*HAS_BC127*/
        res = true;
    }
    return res;
}

bool UartIRQHandler(uint8_t num) {
    bool res = false;
    UartInfo_t* Info = UartGetInfo(num);
    if(Info) {
        flag_status ret = usart_interrupt_flag_get(Info->UARTx, USART_RDBF_FLAG);
        if(SET == ret) {
            /* usart receive data buffer full interrupt */
            /* read one byte from the receive data register */
            uint16_t rx_word = usart_data_receive(Info->UARTx);
            res = UartRxProcIsr(num, (uint8_t)rx_word);
            usart_interrupt_enable(Info->UARTx, USART_RDBF_INT, TRUE);
        }

        ret = usart_interrupt_flag_get(Info->UARTx, USART_TDC_FLAG);
        if(SET == ret) {
            /* write one byte to the transmit data register */
            /* usart transmit data complete interrupt */
            res = UartTxProcIsr(num);
            usart_interrupt_enable(Info->UARTx, USART_TDC_INT, FALSE);
        }

        ret = usart_interrupt_flag_get(Info->UARTx, USART_TDBE_FLAG);
        if(SET == ret) {
            /* usart transmit data buffer empty interrupt */
            /* write one byte to the transmit data register */
            res = UartTxProcIsr(num);
            usart_interrupt_enable(Info->UARTx, USART_TDBE_INT, FALSE);
        }

        ret = usart_interrupt_flag_get(Info->UARTx, USART_PERR_FLAG);
        if(SET == ret) {
            /* usart parity error interrupt */
            usart_interrupt_enable(Info->UARTx, USART_ERR_INT, FALSE);
        }

        ret = usart_interrupt_flag_get(Info->UARTx, USART_FERR_FLAG);
        if(SET == ret) {
            /* usart framing error flag */
            /* usart error interrupt */
            usart_interrupt_enable(Info->UARTx, USART_ERR_INT, FALSE);
        }

        ret = usart_interrupt_flag_get(Info->UARTx, USART_NERR_FLAG);
        if(SET == ret) {
            /* usart noise error flag */
            usart_interrupt_enable(Info->UARTx, USART_ERR_INT, FALSE);
        }

        ret = usart_interrupt_flag_get(Info->UARTx, USART_ROERR_FLAG);
        if(SET == ret) {
            /* usart error interrupt */
            usart_interrupt_enable(Info->UARTx, USART_ERR_INT, FALSE);
        }

        ret = usart_interrupt_flag_get(Info->UARTx, USART_IDLEF_FLAG);
        if(SET == ret) {
            /* usart idle interrupt */
            usart_interrupt_enable(Info->UARTx, USART_IDLE_INT, FALSE);
        }

        ret = usart_interrupt_flag_get(Info->UARTx, USART_BFF_FLAG);
        if(SET == ret) {
            /* usart break frame interrupt */
            usart_interrupt_enable(Info->UARTx, USART_BF_INT, FALSE);
        }

        ret = usart_interrupt_flag_get(Info->UARTx, USART_CTSCF_FLAG);
        if(SET == ret) {
            /* usart cts change interrupt */
            usart_interrupt_enable(Info->UARTx, USART_CTSCF_INT, FALSE);
        }
    }
    return res;
}
