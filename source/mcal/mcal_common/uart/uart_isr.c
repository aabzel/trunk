#include "uart_isr.h"

#include "fifo_char.h"
#include "sys_constants.h"
#include "uart_mcal.h"

#ifdef HAS_TBFP
#include "tbfp_isr.h"
#endif

#ifdef HAS_NMEA
#include "nmea_protocol.h"
#endif

#ifdef HAS_GM67
#include "gm67_drv.h"
#endif

#ifdef HAS_STRING_READER
#include "string_reader.h"
#endif

#ifdef HAS_RS232
#include "rs232_mcal.h"
#endif /*HAS_RS232*/

#ifdef HAS_RS485
#include "rs485_mcal.h"
#endif /*HAS_RS485*/

bool UartTxProcIsrLL(UartHandle_t* const Node) {
    bool res = false;
    Node->tx_cnt++;
    Node->tx_done = true;
    Node->cnt.byte_tx++;
    res = true;
    return res;
}

bool UartTxProcIsr(uint8_t num) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        res = UartTxProcIsrLL(Node);
    }
    return res;
}

bool UartRxProcIsrLL(UartHandle_t* Node, uint8_t rx_byte) {
    bool res = false;
    Node->rx_byte = rx_byte;
    Node->rx_cnt++;
    Node->rx_done = true;
    Node->cnt.byte_rx++;
#ifdef HAS_STRING_READER
    Interfaces_t interface_if = UartNumToInterface(Node->num);
    res = string_reader_rx_byte(interface_if, rx_byte);
#endif

#ifdef HAS_TBFP
    res = tbfp_proc_byte_isr(Node->num, rx_byte);
#endif

#ifdef HAS_RS232
    res = rs232_rx_byte_isr(Node->num, rx_byte);
#endif /*HAS_RS232*/

#ifdef HAS_RS485
    res = rs485_rx_byte_isr(Node->num, rx_byte);
#endif /*HAS_RS485*/

#ifdef HAS_GM67
    res = gm67_proc_byte_isr(Node->num, rx_byte);
#endif

#ifdef HAS_NMEA
    NmeaHandle_t* Nmea = NmeaGetNodeByUartNum(Node->num);
    if(Nmea) {
        res = nmea_proc_byte_isr(Nmea, rx_byte);
    }
#endif

    res = fifo_push(&Node->RxFifo, (char)rx_byte);
    if(res) {
    } else {
        Node->error_cnt++;
    }
    return res;
}

bool UartRxProcIsr(uint8_t num, uint8_t rx_byte) {
    bool res = false;
    UartHandle_t* Node = UartGetNode(num);
    if(Node) {
        res = UartRxProcIsrLL(Node, rx_byte);
    }
    return res;
}
