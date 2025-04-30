#include "tbfp_isr.h"

#include "fifo_char.h"
#include "tbfp.h"

/*ISR_code*/
bool tbfp_proc_byte_isr(uint8_t uart_num, uint8_t rx_byte) {
    bool res = false;
    TbfpHandle_t* Node = TbfpGetNodeByUart(uart_num);
    if(Node) {
        Node->rx_cnt++;
        // Node->rx_time_ms = time_get_ms32();
        res = fifo_push(&Node->RxFifo, (char)rx_byte);
    }
    return res;
}
