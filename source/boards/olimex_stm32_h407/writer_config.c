#include "writer_config.h"

#include "data_utils.h"
#include "writer_types.h"
#include "writer_uart.h"

#ifdef HAS_ESP_01
#include "esp_01_data_tx.h"
#endif

WriterHandle_t* pDBGo = &WriterInstance[WRITER_NUM_UART3];


#ifdef HAS_UART
WriterHandle_t* curWriterPtr = &WriterInstance[WRITER_NUM_UART3];
#endif

#ifdef HAS_UART1
static uint8_t  Writer1Array[400] = {0};
#endif

#ifdef HAS_UART2
static uint8_t  Writer2Array[400] = {0};
#endif

#ifdef HAS_UART3
static uint8_t  Writer3Array[400] = {0};
#endif

#ifdef HAS_UART6
static uint8_t  Writer6Array[400] = {0};
#endif

#ifdef HAS_ESP_01
static uint8_t  WriterEsp01Array[400] = {0};
#endif


void writer_putc(void* _s, char ch);
void writer_puts(void* _s, const char* s, int32_t len);

const WriterConfig_t WriterConfig[4] = {


#ifdef HAS_UART2
    {
 .num = 1,
 .valid = true,
 .inter_face = IF_UART2,
 .TxArray = Writer2Array,
 .tx_array_size = ARRAY_SIZE(Writer2Array),
 .f_putch = uart2_putc,
 .f_putstr = uart2_puts,
 .f_transmit = uart_writer_transmit,
    },
#endif

#ifdef HAS_UART3
    {
 .num = WRITER_NUM_UART3,
 .valid = true,
 .inter_face = {.interface_name=INTERFACE_NAME_UART, .num=3,},
 .TxArray = Writer3Array,
 .tx_array_size = ARRAY_SIZE(Writer3Array),
 .f_putch = uart3_putc,
 .f_putstr = uart3_puts,
 .f_transmit = uart_writer_transmit,
    },
#endif

#ifdef HAS_UART6
    {
 .num = WRITER_NUM_UART6,
 .valid = true,
 .inter_face = IF_UART6,
 .TxArray = Writer6Array,
 .tx_array_size = ARRAY_SIZE(Writer6Array),
 .f_putch = uart6_putc,
 .f_putstr = uart6_puts,
 .f_transmit = uart_writer_transmit,
    },
#endif

#ifdef HAS_ESP_01
    {
     .num = WRITER_NUM_ESP_01,
     .valid = true,
     .inter_face = IF_ESP_01,
     .TxArray = WriterEsp01Array,
     .tx_array_size = ARRAY_SIZE(WriterEsp01Array),
     .f_putch = esp01_putc,
     .f_putstr = esp01_puts,
     .f_transmit = esp01_writer_transmit,
    },
#endif
};

WriterHandle_t WriterInstance[4] = {
#ifdef HAS_UART1
    {
        .valid = true,
        .num = WRITER_NUM_UART1,
        .valid = true,
        .stream = {.f_putch = uart1_putc, .f_putstr = uart1_puts},
        .in_transmit = 0,
        .inter_face = {.interface_name=INTERFACE_NAME_UART,  .num = 1, } ,
        .lost_char_count = 0,
        .tx_cnt = 0,
        .error_count = 0,
        .fifo = {.fifoState = {.size = sizeof(Writer1Array), .start = 0, .end = 0, .count = 0, .errors = 0},
                 .array = Writer1Array,
                 .init_done = true},
        .f_transmit = uart_writer_transmit,
        .enable = true,
        .busy = false,
        .data = "",
    },
#endif

#ifdef HAS_UART2
    {
        .num = WRITER_NUM_UART2,
        .valid = true,
        .stream = {.f_putch = uart2_putc, .f_putstr = uart2_puts},
        .in_transmit = 0,
        .inter_face = {.interface_name=INTERFACE_NAME_UART,  .num = 2, } ,
        .lost_char_count = 0,
        .tx_cnt = 0,
        .error_count = 0,
        .fifo = {.fifoState = {.size = sizeof(Writer2Array), .start = 0, .end = 0, .count = 0, .errors = 0},
                 .array = Writer2Array,
                 .init_done = true},
        .f_transmit = uart_writer_transmit,
        .enable = true,
        .busy = false,
        .data = "",

    },
#endif


#ifdef HAS_UART3
    {
        .num = WRITER_NUM_UART3,
        .valid = true,
        .stream = {.f_putch = uart3_putc, .f_putstr = uart3_puts},
        .in_transmit = 0,
        .inter_face = {.interface_name=INTERFACE_NAME_UART,  .num = 3, } ,
        .lost_char_count = 0,
        .tx_cnt = 0,
        .error_count = 0,
        .fifo = {.fifoState = {.size = sizeof(Writer3Array), .start = 0, .end = 0, .count = 0, .errors = 0},
                 .array = Writer3Array,
                 .init_done = true},
        .f_transmit = uart_writer_transmit,
        .enable = true,
        .busy = false,
        .data = "",

    },
#endif

#ifdef HAS_UART6
    {
        .num = WRITER_NUM_UART6,
        .valid = true,
        .stream = {.f_putch = uart6_putc, .f_putstr = uart6_puts},
        .in_transmit = 0,
        .inter_face = {.interface_name=INTERFACE_NAME_UART,  .num = 6, } ,
        .lost_char_count = 0,
        .tx_cnt = 0,
        .error_count = 0,
        .fifo = {.fifoState = {.size = sizeof(Writer6Array), .start = 0, .end = 0, .count = 0, .errors = 0},
                 .array = Writer6Array,
                 .init_done = true},
        .f_transmit = uart_writer_transmit,
        .enable = true,
        .busy = false,
        .data = "",

    },
#endif

#ifdef HAS_ESP_01
    {
        .num = 4,
        .valid = true,
    },
#endif
};

COMPONENT_GET_CNT(Writer, writer)
