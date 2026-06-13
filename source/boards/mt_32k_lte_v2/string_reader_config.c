#include "string_reader_config.h"

#include "data_utils.h"
#include "cli_drv.h"


static uint8_t FifoDataRtt1[100]={0};
static uint8_t LineDataRtt1[100]={0};

static uint8_t FifoData4[100]={0};
static uint8_t LineData4[100]={0};

static uint8_t FifoData7[100]={0};
static uint8_t LineData7[100]={0};

static uint8_t FifoData8[100]={0};
static uint8_t LineData8[100]={0};

#ifdef HAS_USB_SERIAL
static uint8_t FifoDataUsbSerial[100]={0};
static uint8_t LineDataUsbSerial[100]={0};
#endif

#ifdef HAS_USB_KEYBOARD
static uint8_t FifoDataKeyBoard[100]={0};
static uint8_t LineDataKeyBoard[100]={0};
#endif

const StringReaderConfig_t StringReaderConfig[] = {
    { 
        .num = 1,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .feedback_led = 1,
        .interface_if = { .interface_name = INTERFACE_NAME_SEGGER_RTT, .num = 1, },
        .name = "RTT",
        .fifo_heap = FifoDataRtt1,
        .fifo_heap_size = sizeof(FifoDataRtt1),
        .string = LineDataRtt1,
        .string_size = sizeof(LineDataRtt1),
        .callback = (handle_string_f)(cli_process_cmd),
    },
    
    { 
        .num = 2,
        .feedback_led = 1,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .interface_if = { .interface_name = INTERFACE_NAME_UART, .num = 7,},
        .name = "UART7",
        .fifo_heap = FifoData7,
        .fifo_heap_size = sizeof(FifoData7),
        .string = LineData7,
        .string_size = sizeof(LineData7),
        .callback = (handle_string_f)(cli_process_cmd),
    },

    {
        .num = 3,
        .feedback_led = 1,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .interface_if = { .interface_name = INTERFACE_NAME_UART, .num = 4,},
        .name = "UART4",
        .fifo_heap = FifoData4,
        .fifo_heap_size = sizeof(FifoData4),
        .string = LineData4,
        .string_size = sizeof(LineData4),
        .callback = (handle_string_f)(cli_process_cmd),
    },

    {
        .num = 4,
        .feedback_led = 1,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .interface_if = { .interface_name = INTERFACE_NAME_UART, .num = 8,},
        .name = "UART8",
        .fifo_heap = FifoData8,
        .fifo_heap_size = sizeof(FifoData8),
        .string = LineData8,
        .string_size = sizeof(LineData8),
        .callback = (handle_string_f)(cli_process_cmd),
    },

#ifdef HAS_USB_SERIAL
    {
        .num = 5,
        .feedback_led = 1,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .interface_if =  {.interface_name = INTERFACE_NAME_USB, .num = 1,},
        .name = "UsbSerial",
        .fifo_heap = FifoDataUsbSerial,
        .fifo_heap_size = sizeof(FifoDataUsbSerial),
        .string = LineDataUsbSerial,
        .string_size = sizeof(LineDataUsbSerial),
        .callback = (handle_string_f)(cli_process_cmd),
    },
#endif

#ifdef HAS_USB_KEYBOARD
    {
        .num = 6,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .interface_if =  {.interface_name = INTERFACE_NAME_USB_HID, .num = 1,},
        .if_num = 3,
        .name = "USB_HOST_HID",
        .fifo_heap = FifoDataKeyBoard,
        .fifo_heap_size = sizeof(FifoDataKeyBoard),
        .string = LineDataKeyBoard,
        .string_size = sizeof(LineDataKeyBoard),
        .callback = (handle_string_f)(cli_process_cmd),
        .feedback_led = 1,
    },
#endif

};

StringReaderHandle_t StringReaderInstance[]={
    {.num = 1, .valid = true, },
    {.num = 2, .valid = true, },
    {.num = 3, .valid = true, },
    {.num = 4, .valid = true, },
    {.num = 5, .valid = true, },
    {.num = 6, .valid = true, },
    {.num = 7, .valid = true, },
};

COMPONENT_GET_CNT(StringReader, string_reader)
