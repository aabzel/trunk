
#include "uart_bsp.h"
#include "uart_config.h"
#include "uart_isr.h"

/*
 * Read characters from UART until line end is detected. Afterwards push the
 * data to the message queue.
 */
void uart2_callback(const struct device* dev, void* user_data) {
    uint8_t rx_byte;
    UartHandle_t* Node = UartGetNode(2);
    if(Node) {
        const struct device* uart_device = UartNum2Dev(2);
        if(!uart_irq_update(uart_device)) {
            return;
        }
        int ret = 0;
        bool res = false;
        ret = uart_irq_rx_ready(uart_device);
        while(ret) {
            rx_byte = ' ';
            ret = uart_fifo_read(uart_device, &rx_byte, 1);
            if(1 == ret) {
                res = fifo_push(&Node->RxFifo, rx_byte);
                if(false == res) {
                    Node->error_cnt++;
                }
            } else {
                Node->error_cnt++;
            }
            ret = uart_irq_rx_ready(uart_device);
        }
    }
}
