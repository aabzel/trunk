#include "uart_config.h"

#include "data_utils.h"
#include "log_config.h"
//#include "c_defines_generated.h"

#ifdef HAS_UART1
static uint8_t Uart1TxArray[UART_TX_FIFO_SIZE];
static uint8_t Uart1RxArray[16];
#endif

#ifdef HAS_UART2
static uint8_t Uart2TxArray[UART_TX_FIFO_SIZE];
static uint8_t Uart2RxArray[16];
#endif

#ifdef HAS_UART3
static uint8_t Uart3TxArray[UART_TX_FIFO_SIZE];
static uint8_t Uart3RxArray[16];
#endif

#ifdef HAS_UART6
static uint8_t Uart6TxArray[UART_TX_FIFO_SIZE];
static uint8_t Uart6RxArray[16];
#endif



#define UART_STATIC_INIT_CONFIG_ONE(NUM)                         \
        {                                                        \
            .num = NUM,                                          \
            .baud_rate = 460800,                                 \
            .tx_buff_size = sizeof(Uart##NUM##TxArray),          \
            .TxFifoArray = Uart##NUM##TxArray,                   \
            .rx_buff_size = sizeof(Uart##NUM##RxArray),          \
            .RxFifoArray = Uart##NUM##RxArray,                   \
            .momve_method = MOVE_MODE_INTERRUPT,                 \
            .valid = true,                                       \
            .interrupts_on = true,                               \
             .stop_bit_cnt = 2,                                  \
            .parity_check = false,                               \
            .word_len_bit = 8,                                   \
            .dma =                                               \
                {                                                \
                    .tx = false,                                 \
                    .rx = false,                                 \
                },                                               \
        },

           // .name = "UART#NUM",

#ifdef HAS_UART0
#define UART_STATIC_INIT_CONFIG_0 UART_STATIC_INIT_CONFIG_ONE(0)
#else
#define UART_STATIC_INIT_CONFIG_0
#endif

#ifdef HAS_UART1
#define UART_STATIC_INIT_CONFIG_1 UART_STATIC_INIT_CONFIG_ONE(1)
#else
#define UART_STATIC_INIT_CONFIG_1
#endif

#ifdef HAS_UART2
#define UART_STATIC_INIT_CONFIG_2 UART_STATIC_INIT_CONFIG_ONE(2)
#else
#define UART_STATIC_INIT_CONFIG_2
#endif

#ifdef HAS_UART3
#define UART_STATIC_INIT_CONFIG_3 UART_STATIC_INIT_CONFIG_ONE(3)
#else
#define UART_STATIC_INIT_CONFIG_3
#endif


#ifdef HAS_UART4
#define UART_STATIC_INIT_CONFIG_4 UART_STATIC_INIT_CONFIG_ONE(4)
#else
#define UART_STATIC_INIT_CONFIG_4
#endif


#ifdef HAS_UART5
#define UART_STATIC_INIT_CONFIG_5 UART_STATIC_INIT_CONFIG_ONE(5)
#else
#define UART_STATIC_INIT_CONFIG_5
#endif


#ifdef HAS_UART6
#define UART_STATIC_INIT_CONFIG_6 UART_STATIC_INIT_CONFIG_ONE(6)
#else
#define UART_STATIC_INIT_CONFIG_6
#endif


#ifdef HAS_UART7
#define UART_STATIC_INIT_CONFIG_7 UART_STATIC_INIT_CONFIG_ONE(7)
#else
#define UART_STATIC_INIT_CONFIG_7
#endif


#ifdef HAS_UART8
#define UART_STATIC_INIT_CONFIG_8 UART_STATIC_INIT_CONFIG_ONE(8)
#else
#define UART_STATIC_INIT_CONFIG_8
#endif


#ifdef HAS_UART9
#define UART_STATIC_INIT_CONFIG_9 UART_STATIC_INIT_CONFIG_ONE(9)
#else
#define UART_STATIC_INIT_CONFIG_9
#endif

#ifdef HAS_UART10
#define UART_STATIC_INIT_CONFIG_10 UART_STATIC_INIT_CONFIG_ONE(10)
#else
#define UART_STATIC_INIT_CONFIG_10
#endif


#ifdef HAS_UART11
#define UART_STATIC_INIT_CONFIG_11 UART_STATIC_INIT_CONFIG_ONE(11)
#else
#define UART_STATIC_INIT_CONFIG_11
#endif


#ifdef HAS_UART12
#define UART_STATIC_INIT_CONFIG_12 UART_STATIC_INIT_CONFIG_ONE(12)
#else
#define UART_STATIC_INIT_CONFIG_12
#endif


#ifdef HAS_UART13
#define UART_STATIC_INIT_CONFIG_13 UART_STATIC_INIT_CONFIG_ONE(13)
#else
#define UART_STATIC_INIT_CONFIG_13
#endif


#ifdef HAS_UART14
#define UART_STATIC_INIT_CONFIG_14 UART_STATIC_INIT_CONFIG_ONE(14)
#else
#define UART_STATIC_INIT_CONFIG_14
#endif


#ifdef HAS_UART15
#define UART_STATIC_INIT_CONFIG_15 UART_STATIC_INIT_CONFIG_ONE(15)
#else
#define UART_STATIC_INIT_CONFIG_15
#endif


#ifdef HAS_UART16
#define UART_STATIC_INIT_CONFIG_16 UART_STATIC_INIT_CONFIG_ONE(16)
#else
#define UART_STATIC_INIT_CONFIG_16
#endif


#ifdef HAS_UART17
#define UART_STATIC_INIT_CONFIG_17 UART_STATIC_INIT_CONFIG_ONE(17)
#else
#define UART_STATIC_INIT_CONFIG_17
#endif







#define UART_STATIC_INIT_NODE_ONE(NUM)                         \
    {                                                          \
        .num = NUM,                                            \
        .valid = true,                                         \
        .TxFifo =                                              \
            {                                                  \
                .err_cnt = 0,                                  \
                .init_done = false,                            \
                .array = Uart##NUM##TxArray,                   \
                .fifoState =                                   \
                    {                                          \
                        .size = sizeof(Uart##NUM##TxArray),    \
                        .start = 0,                            \
                        .end = 0,                              \
                        .count = 0,                            \
                        .errors = false,                       \
                    },                                         \
            },                                                 \
    },


#ifdef HAS_UART0
#define UART_STATIC_INIT_NODE_0 UART_STATIC_INIT_NODE_ONE(0)
#else
#define UART_STATIC_INIT_NODE_0
#endif

#ifdef HAS_UART1
#define UART_STATIC_INIT_NODE_1 UART_STATIC_INIT_NODE_ONE(1)
#else
#define UART_STATIC_INIT_NODE_1
#endif

#ifdef HAS_UART2
#define UART_STATIC_INIT_NODE_2 UART_STATIC_INIT_NODE_ONE(2)
#else
#define UART_STATIC_INIT_NODE_2
#endif

#ifdef HAS_UART3
#define UART_STATIC_INIT_NODE_3 UART_STATIC_INIT_NODE_ONE(3)
#else
#define UART_STATIC_INIT_NODE_3
#endif

#ifdef HAS_UART4
#define UART_STATIC_INIT_NODE_4 UART_STATIC_INIT_NODE_ONE(4)
#else
#define UART_STATIC_INIT_NODE_4
#endif

#ifdef HAS_UART5
#define UART_STATIC_INIT_NODE_5 UART_STATIC_INIT_NODE_ONE(5)
#else
#define UART_STATIC_INIT_NODE_5
#endif

#ifdef HAS_UART6
#define UART_STATIC_INIT_NODE_6 UART_STATIC_INIT_NODE_ONE(6)
#else
#define UART_STATIC_INIT_NODE_6
#endif

#ifdef HAS_UART7
#define UART_STATIC_INIT_NODE_7 UART_STATIC_INIT_NODE_ONE(7)
#else
#define UART_STATIC_INIT_NODE_7
#endif

#ifdef HAS_UART8
#define UART_STATIC_INIT_NODE_8 UART_STATIC_INIT_NODE_ONE(8)
#else
#define UART_STATIC_INIT_NODE_8
#endif

#ifdef HAS_UART9
#define UART_STATIC_INIT_NODE_9 UART_STATIC_INIT_NODE_ONE(9)
#else
#define UART_STATIC_INIT_NODE_9
#endif

#ifdef HAS_UART10
#define UART_STATIC_INIT_NODE_10 UART_STATIC_INIT_NODE_ONE(10)
#else
#define UART_STATIC_INIT_NODE_10
#endif

#ifdef HAS_UART11
#define UART_STATIC_INIT_NODE_11 UART_STATIC_INIT_NODE_ONE(11)
#else
#define UART_STATIC_INIT_NODE_11
#endif

#ifdef HAS_UART12
#define UART_STATIC_INIT_NODE_12 UART_STATIC_INIT_NODE_ONE(12)
#else
#define UART_STATIC_INIT_NODE_12
#endif

#ifdef HAS_UART13
#define UART_STATIC_INIT_NODE_13 UART_STATIC_INIT_NODE_ONE(13)
#else
#define UART_STATIC_INIT_NODE_13
#endif

#ifdef HAS_UART14
#define UART_STATIC_INIT_NODE_14 UART_STATIC_INIT_NODE_ONE(14)
#else
#define UART_STATIC_INIT_NODE_14
#endif

#ifdef HAS_UART15
#define UART_STATIC_INIT_NODE_15 UART_STATIC_INIT_NODE_ONE(15)
#else
#define UART_STATIC_INIT_NODE_15
#endif

#ifdef HAS_UART16
#define UART_STATIC_INIT_NODE_16 UART_STATIC_INIT_NODE_ONE(16)
#else
#define UART_STATIC_INIT_NODE_16
#endif

#ifdef HAS_UART17
#define UART_STATIC_INIT_NODE_17 UART_STATIC_INIT_NODE_ONE(17)
#else
#define UART_STATIC_INIT_NODE_17
#endif

#define UART_STATIC_INIT_NODE_ALL      \
    UART_STATIC_INIT_NODE_0            \
    UART_STATIC_INIT_NODE_1            \
    UART_STATIC_INIT_NODE_2            \
    UART_STATIC_INIT_NODE_3            \
    UART_STATIC_INIT_NODE_4            \
    UART_STATIC_INIT_NODE_5            \
    UART_STATIC_INIT_NODE_6            \
    UART_STATIC_INIT_NODE_7            \
    UART_STATIC_INIT_NODE_8            \
    UART_STATIC_INIT_NODE_9            \
    UART_STATIC_INIT_NODE_10           \
    UART_STATIC_INIT_NODE_11           \
    UART_STATIC_INIT_NODE_12           \
    UART_STATIC_INIT_NODE_13           \
    UART_STATIC_INIT_NODE_14           \
    UART_STATIC_INIT_NODE_15           \
    UART_STATIC_INIT_NODE_16           \
    UART_STATIC_INIT_NODE_17

#define UART_STATIC_INIT_CONFIG_ALL     \
    UART_STATIC_INIT_CONFIG_0           \
    UART_STATIC_INIT_CONFIG_1           \
    UART_STATIC_INIT_CONFIG_2           \
    UART_STATIC_INIT_CONFIG_3           \
    UART_STATIC_INIT_CONFIG_4           \
    UART_STATIC_INIT_CONFIG_5           \
    UART_STATIC_INIT_CONFIG_6           \
    UART_STATIC_INIT_CONFIG_7           \
    UART_STATIC_INIT_CONFIG_8           \
    UART_STATIC_INIT_CONFIG_9           \
    UART_STATIC_INIT_CONFIG_10           \
    UART_STATIC_INIT_CONFIG_11           \
    UART_STATIC_INIT_CONFIG_12           \
    UART_STATIC_INIT_CONFIG_13           \
    UART_STATIC_INIT_CONFIG_14           \
    UART_STATIC_INIT_CONFIG_15           \
    UART_STATIC_INIT_CONFIG_16           \
    UART_STATIC_INIT_CONFIG_17

/*TODO USE MACRO FUNCTION to compose identical config*/
/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {
    UART_STATIC_INIT_CONFIG_ALL
};

UartHandle_t UartInstance[] = {
    UART_STATIC_INIT_NODE_ALL
};

uint32_t uart_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(UartConfig);
    uint32_t cnt_ints = ARRAY_SIZE(UartInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
