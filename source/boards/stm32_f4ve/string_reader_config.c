#include "string_reader_config.h"

#include "data_utils.h"
#include "cli_drv.h"

static uint8_t FifoData1[100]={0};
static uint8_t LineData1[100]={0};

#ifdef HAS_USB_KEYBOARD
static uint8_t FifoData3[100]={0};
static uint8_t LineData3[100]={0};
#endif

const StringReaderConfig_t StringReaderConfig[] = {
    { 
        .num = STRING_READER_NUM_RTT,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .feedback_led = 2,
        .interface_if = { .interface_name = INTERFACE_NAME_SEGGER_RTT, .num = 1, },
        .name = "RTT",
        .fifo_heap = FifoData1,
        .fifo_heap_size = sizeof(FifoData1),
        .string = LineData1,
        .string_size = sizeof(LineData1),
        .callback = (handle_string_f)(cli_process_cmd),
    },
    
    { 
    .num = STRING_READER_NUM_UART1,
    .valid = true,
    .echo = true,
    .cli_num = 1,
    .interface_if =  {.interface_name = INTERFACE_NAME_UART, .num = 1,},
    //.if_num = 2,
    .name = "CLIin",
    .fifo_heap = FifoData1,
    .fifo_heap_size = sizeof(FifoData1),
    .string = LineData1,
    .string_size = sizeof(LineData1),
    .callback = (handle_string_f)(cli_process_cmd),
    .feedback_led = 2,
   },

#ifdef HAS_USB_SERIAL
    {
        .num = STRING_READER_NUM_USB_SERIAL,
        .feedback_led = 1,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .interface_if =  {.interface_name = INTERFACE_NAME_USB, .num = 1,},
        .name = "UsbSerial",
        .fifo_heap = FifoData2,
        .fifo_heap_size = sizeof(FifoData2),
        .string = LineData2,
        .string_size = sizeof(LineData2),
        .callback = (handle_string_f)(cli_process_cmd),
    },
#endif

};

StringReaderHandle_t StringReaderInstance[]={
    {.num = STRING_READER_NUM_UART1, .valid = true, },
    {.num = STRING_READER_NUM_RTT, .valid = true, },
#ifdef HAS_USB_SERIAL
    {.num = STRING_READER_NUM_USB_SERIAL, .valid = true, },
#endif

};

COMPONENT_GET_CNT(StringReader, string_reader)
