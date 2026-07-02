#include "string_reader_config.h"

#include "data_utils.h"
#include "cli_drv.h"


#ifdef HAS_UART1
static uint8_t FifoData1[100] = {0};
static uint8_t LineData1[100] = {0};
#endif

#ifdef HAS_UART2
static uint8_t FifoData2[100] = {0};
static uint8_t LineData2[100] = {0};
#endif


#ifdef HAS_USB
static uint8_t FifoData3[100] = {0};
static uint8_t LineData3[100] = {0};
#endif

const StringReaderConfig_t StringReaderConfig[] = {
#ifdef HAS_UART1
    { 
        .num = STRING_READER_NUM_UART1,
        .interface_if = {.interface_name = INTERFACE_NAME_UART, .num = 1, } ,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .name= "CLI",
        .fifo_heap = FifoData1,
        .fifo_heap_size=sizeof(FifoData1),
        .string=LineData1,
        .string_size= sizeof(LineData1),
        .callback =(handle_string_f)(cli_process_cmd),
        .feedback_led=1,
    },
#endif

#ifdef HAS_UART2
    {
        .num = STRING_READER_NUM_UART2,
        .interface_if = {.interface_name = INTERFACE_NAME_UART, .num = 2, } ,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .name= "CLI",
        .fifo_heap = FifoData2,
        .fifo_heap_size=sizeof(FifoData2),
        .string=LineData2,
        .string_size= sizeof(LineData2),
        .callback =(handle_string_f)(cli_process_cmd),
        .feedback_led=1,
    },
#endif

#ifdef HAS_USB
    {
        .num = STRING_READER_NUM_USB,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .interface_if = IF_USB_HID,
        .if_num = 3,
        .name = "USB_HOST_HID",
        .fifo_heap = FifoData3,
        .fifo_heap_size = sizeof(FifoData3),
        .string = LineData3,
        .string_size = sizeof(LineData3),
        .callback = (handle_string_f)(cli_process_cmd),
        .feedback_led = 1,
    },
#endif
};

StringReaderHandle_t StringReaderInstance[]={
#ifdef HAS_UART1
    {.num=STRING_READER_NUM_UART1,
     .valid=true, },
#endif

#ifdef HAS_UART2
    {.num=STRING_READER_NUM_UART2,
     .valid=true, },
#endif

#ifdef HAS_USB
    {.num=STRING_READER_NUM_USB,
     .valid=true, },
#endif
};

COMPONENT_GET_CNT(StringReader, string_reader)
