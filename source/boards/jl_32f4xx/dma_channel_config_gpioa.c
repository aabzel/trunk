#include "dma_channel_config_gpioa.h"

#include "data_utils.h"
#include "microcontroller_const.h"
#include "gpio_mcal.h"

#ifdef HAS_BIN_DAC
#include "bin_dac_mcal.h"
#endif

#ifdef HAS_SW_UART
#include "sw_uart_mcal.h"
#endif

uint16_t PortAtoArray[GPIO_SAMPLE_SIZE] = {0};

bool CallBackHalfPortARx(void) {
    bool res = false;
#ifdef HAS_SW_UART
    res = sw_uart_proc_event(1,1);
#endif
    return res;
}

bool CallBackDonePortARx(void) {
    bool res = false;
#ifdef HAS_SW_UART
    res = sw_uart_proc_event(1,2);
#endif
    return res;
}

bool CallBackDonePortATx(void){
    bool res = false;
#ifdef HAS_BIN_DAC
    res = bin_dac_tx_done(1);

    int32_t cnt = bin_dac_fifo_cnt_get(1);
    if(0==cnt) {
#ifdef HAS_SW_UART
        res = sw_uart_tx_next(1);
#endif
    }

#endif
    return res;
}

bool CallBackHalfPortATx(void) {
    bool res = false;
    return res;
}



