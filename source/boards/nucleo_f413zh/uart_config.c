#include "uart_config.h"

#include "log_config.h"
#include "data_utils.h"

#ifdef HAS_UART2
static uint8_t Uart2TxArray[UART_TX_FIFO_SIZE]={0};
#endif

#ifdef HAS_UART3
static uint8_t Uart3TxArray[UART_TX_FIFO_SIZE]={0};
#endif

/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {
    { .num=2, .baud_rate=9600,     .name = "UART2", .rx_buff_size=0, .valid=true, },
    { .num=3, .baud_rate=460800,   .name = "UART3", .rx_buff_size=0, .valid=true,},
};

UartHandle_t UartInstance[] = {
#ifdef HAS_UART2
    {.num=2, .valid=true, .TxFifo={.err_cnt=0, .initDone=true, .array=(char *)Uart2TxArray, .fifoState={.size=sizeof(Uart2TxArray), .start=0, .end=0, .count=0, .errors=false,},},},
#endif


#ifdef HAS_UART3
    {.num=3, .valid=true, .TxFifo={.err_cnt=0, .initDone=true, .array=(char *)Uart3TxArray, .fifoState={.size=sizeof(Uart3TxArray), .start=0, .end=0, .count=0, .errors=false,},},},
#endif


};

uint32_t uart_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(UartConfig);
    uint32_t cnt_ints = ARRAY_SIZE(UartInstance);
    if(cnt_conf==cnt_ints){
        cnt = cnt_ints;
    }
    return cnt;
}

