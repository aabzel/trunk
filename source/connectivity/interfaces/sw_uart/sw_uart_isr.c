#include "sw_uart_isr.h"

#include "sw_uart_mcal.h"
#include "gpio_mcal.h"
#include "bin_adc_mcal.h"

bool sw_uart_proc_event(uint8_t num, uint8_t part_num) {
    bool res = false;
    SwUartHandle_t *Node = SwUartGetNode(num);
    if(Node) {
        BinAdcHandle_t* Adc=BinAdcGetNode(Node->bin_adc_num);
        switch (part_num) {
        case 1: {
            gpio_logic_level_set(Adc->debugPad, GPIO_LVL_HI);
            Node->rx_action = SW_UART_RX_ACTION_PROC1;
            res = true;
        }
            break;
        case 2: {
            gpio_logic_level_set(Adc->debugPad, GPIO_LVL_LOW);
            Node->rx_action = SW_UART_RX_ACTION_PROC2;
            res = true;
        }
            break;
        default: {
            res = false;
        }
            break;
        }
    }
    return res;
}
