#include "writer_config.h"

#include "data_utils.h"
#include "writer_types.h"

#ifdef HAS_ISO_TP
#include "iso_tp_mcal.h"
#endif

#ifdef HAS_UART
#include "writer_uart.h"
#endif

static uint8_t DbgOutData[DBG_TX_ARRAY_SIZE] = {0};

#ifdef HAS_ISO_TP
static uint8_t WriterIsoTp1Array[200] = {0};
static uint8_t WriterIsoTp2Array[200] = {0};
#endif

#ifdef HAS_UART1
static uint8_t WriterUart1Array[200] = {0};
#endif

#ifdef HAS_UART3
static uint8_t WriterUart3Array[200] = {0};
#endif

#ifdef HAS_SEGGER_RTT
#include "segger_rtt_mcal.h"
#endif


WriterHandle_t dbg_o = {
#ifdef HAS_UART1
    .stream = {.f_putch = uart1_putc, .f_putstr = uart1_puts},
    .in_transmit = 0,
    .inter_face =
        {
            .interface_name = INTERFACE_NAME_UART,
            .num = 1,
        },
#endif
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
// generic_writer_t* curWriterPtr = &dbg_o;
WriterHandle_t* curWriterPtr = &dbg_o;
#else 

WriterHandle_t* curWriterPtr = NULL;
#endif

#ifdef HAS_SEGGER_RTT
static uint8_t  WriterSeggerRtt1Array[200] = {0};
#endif


void writer_putc(void* _s, char ch);
void writer_puts(void* _s, const char* s, int32_t len);

const WriterConfig_t SECTION_CFG_DATA WriterConfig[] = {
#ifdef HAS_SEGGER_RTT
    {
     .num = WRITER_NUM_SEGGER_RTT1,
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

#ifdef HAS_ISO_TP
    {
     .num = WRITER_NUM_ISO_TP1,
     .valid = true,
     .name = "ISOTP1",
     .inter_face = {.interface_name=INTERFACE_NAME_ISO_TP, .num=1,},
     .TxArray = WriterIsoTp1Array,
     .tx_array_size = ARRAY_SIZE(WriterIsoTp1Array),
     .f_putch = iso_tp1_putc,
     .f_putstr = iso_tp1_puts,
     .f_transmit = iso_tp1_writer_transmit,
    },

    {
     .num = WRITER_NUM_ISO_TP2,
     .valid = true,
     .name = "ISOTP2",
     .inter_face = {.interface_name=INTERFACE_NAME_ISO_TP, .num=2,},
     .TxArray = WriterIsoTp2Array,
     .tx_array_size = ARRAY_SIZE(WriterIsoTp2Array),
     .f_putch = iso_tp2_putc,
     .f_putstr = iso_tp2_puts,
     .f_transmit = iso_tp2_writer_transmit,
    },
#endif

#ifdef HAS_UART1
    {
        .num = WRITER_NUM_UART1,
        .valid = true,
        .TxArray = WriterUart1Array,
        .tx_array_size = ARRAY_SIZE(WriterUart1Array),
        .name = "UART1",
        .inter_face = {.interface_name = INTERFACE_NAME_UART, .num = 1, } ,
        .f_putch = uart1_putc,
        .f_putstr = uart1_puts,
        .f_transmit = uart_writer_transmit,
    },
#endif

#ifdef HAS_UART3
    {
        .num = WRITER_NUM_UART3,
        .valid = true,
        .TxArray = WriterUart3Array,
        .tx_array_size = ARRAY_SIZE(WriterUart3Array),
        .name = "UART3",
        .inter_face = {.interface_name = INTERFACE_NAME_UART, .num = 3, } ,
        .f_putch = uart3_putc,
        .f_putstr = uart3_puts,
        .f_transmit = uart_writer_transmit,
    },
#endif
};

WriterHandle_t WriterInstance[6] = {

#ifdef HAS_SEGGER_RTT
    { .num = WRITER_NUM_SEGGER_RTT1, .valid = true, },
#endif

#ifdef HAS_UART1
    { .num = WRITER_NUM_UART1, .valid = true, },
#endif

#ifdef HAS_UART3
    { .num = WRITER_NUM_UART3, .valid = true, },
#endif

#ifdef HAS_ISO_TP
    { .num = WRITER_NUM_ISO_TP1, .valid = true, },
    { .num = WRITER_NUM_ISO_TP2, .valid = true, },
#endif
};

COMPONENT_GET_CNT(Writer, writer)
