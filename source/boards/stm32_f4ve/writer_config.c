#include "writer_config.h"

#include "data_utils.h"
#include "writer_types.h"
#include "writer_uart.h"

#ifdef HAS_ESP_01
#include "esp_01_data_tx.h"
#endif

#ifdef HAS_SEGGER_RTT
#include "segger_rtt_mcal.h"
#endif

//#define MAX_UART_BLOCK 100U
uint8_t DbgOutData[DBG_TX_ARRAY_SIZE] = {0};

 WriterHandle_t dbg_o = {
    .stream = {.f_putch = uart1_putc, .f_putstr = uart1_puts},
    .in_transmit = 0,
    .inter_face =  {.interface_name=INTERFACE_NAME_UART, .num=1,},
    .lost_char_count = 0,
    .tx_cnt = 0,
    .error_count = 0,
    .fifo = {.fifoState = {.size = sizeof(DbgOutData), .start = 0, .end = 0, .count = 0, .errors = 0},
             .array = DbgOutData,
             .init_done = true},
    .f_transmit = uart_writer_transmit,
    .enable = true,
    .busy = false,
    .data = "",
};

#ifdef HAS_UART
WriterHandle_t* curWriterPtr = &dbg_o;
#else

#ifdef HAS_SWD
WriterHandle_t* curWriterPtr = &swd_o;
#else  /*HAS_SWD*/
WriterHandle_t* curWriterPtr = NULL;
#endif /*HAS_SWD*/

#endif /*HAS_UART*/

#ifdef HAS_SEGGER_RTT
static uint8_t  WriterSeggerRtt1Array[400] = {0};
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

#ifdef HAS_USB_SERIAL
static uint8_t  WriterUsbSerial1Array[400] = {0};
#endif

#ifdef HAS_ESP_01
static uint8_t  WriterEsp01Array[400] = {0};
#endif


void writer_putc(void* _s, char ch);
void writer_puts(void* _s, const char* s, int32_t len);

const WriterConfig_t WriterConfig[] = {

#ifdef HAS_SEGGER_RTT
    {
        .num = WRITER_NUM_SEGGER_RTT,
        .valid = true,
        .name = "SEGGER_RTT1",
        .inter_face = {.interface_name=INTERFACE_NAME_SEGGER_RTT, .num=1,},
        .TxArray = WriterSeggerRtt1Array,
        .tx_array_size = ARRAY_SIZE(WriterSeggerRtt1Array),
        .f_putch = segger_rtt1_putc,
        .f_putstr = segger_rtt1_puts,
        .f_transmit = segger_rtt1_writer_transmit,
    },
#endif

#ifdef HAS_UART1
    {
        .num = WRITER_NUM_UART1,
        .valid = true,
        .inter_face = {.interface_name=INTERFACE_NAME_UART, .num=1,},
        .TxArray = Writer1Array,
        .tx_array_size = ARRAY_SIZE(Writer1Array),
        .f_putch = uart1_putc,
        .f_putstr = uart1_puts,
        .f_transmit = uart_writer_transmit,
    },
#endif

#ifdef HAS_UART2
    {
        .num = WRITER_NUM_UART2,
        .valid = true,
        .inter_face =  {.interface_name = INTERFACE_NAME_UART, .num = 2,},
        .TxArray = Writer2Array,
        .tx_array_size = ARRAY_SIZE(Writer2Array),
        .f_putch = uart2_putc,
        .f_putstr = uart2_puts,
        .f_transmit = uart_writer_transmit,
    },
#endif

#ifdef HAS_USB_SERIAL
    {
     .num = WRITER_NUM_USB_SERIAL,
     .valid = true,
     .name = "UsbSerial",
     .inter_face = {.interface_name=INTERFACE_NAME_USB, .num=1,},
     .TxArray = WriterUsbSerial1Array,
     .tx_array_size = ARRAY_SIZE(WriterUsbSerial1Array),
     .f_putch = usb_serial_putc,
     .f_putstr = usb_serial_puts,
     .f_transmit = usb_serial_writer_transmit,
    },
#endif

#ifdef HAS_UART6
    {
        .num = WRITER_NUM_UART6,
        .valid = true,
        .inter_face = {.interface_name = INTERFACE_NAME_UART, .num = 6,},
        .TxArray = Writer6Array,
        .tx_array_size = ARRAY_SIZE(Writer6Array),
        .f_putch = uart6_putc,
        .f_putstr = uart6_puts,
        .f_transmit = uart_writer_transmit,
    },
#endif

#ifdef HAS_ESP_01
    {
        .num = WRITER_NUM_SEGGER_ESP_01,
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

WriterHandle_t WriterInstance[] = {
#ifdef HAS_SEGGER_RTT
    { .num = WRITER_NUM_SEGGER_RTT, .valid = true, },
#endif

#ifdef HAS_UART1
    {        .num = WRITER_NUM_UART1,        .valid = true,    },
#endif

#ifdef HAS_UART2
    {        .num = WRITER_NUM_UART2,        .valid = true,    },
#endif

#ifdef HAS_USB_SERIAL
    { .num = WRITER_NUM_USB_SERIAL, .valid = true, },
#endif

#ifdef HAS_UART6
    {        .num = WRITER_NUM_UART6,        .valid = true,    },
#endif

#ifdef HAS_ESP_01
    {        .num = WRITER_NUM_ESP_01,        .valid = true,    },
#endif
};

COMPONENT_GET_CNT(Writer, writer)


