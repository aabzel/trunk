#include "uart_config.h"

#include "log_config.h"
#include "data_utils.h"

/*constant compile-time known settings*/
const UartConfig_t UartConfigLuT[] = {
    { .num=1,   .baud_rate=460800,   .name = "CLI",   .rx_buff_size=0, .valid=true,},
};

uint8_t LogUartTxArray[UART_TX_FIFO_SIZE];

UartHandle_t UartInstance[]={

    {.num=1, .valid=true, .TxFifo={.err_cnt=0,
                                              .initDone=true,
                                              .array=(char *)LogUartTxArray,
                                              .fifoState={
                                                          .size=sizeof(LogUartTxArray),
                                                          .start=0,
                                                          .end=0,
                                                          .count=0,
                                                          .errors=false,
                                              },
    },
    },

};

uint32_t uart_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(UartConfigLuT);
    uint32_t cnt_ints = ARRAY_SIZE(UartInstance);
    if(cnt_conf==cnt_ints){
        cnt = cnt_ints;
    }
    return cnt;
}

