#include "string_reader_config.h"

#include "data_utils.h"
#include "cli_drv.h"

static uint8_t FifoData1[100]={0};
static uint8_t LineData1[100]={0};

static uint8_t FifoData2[100]={0};
static uint8_t LineData2[100]={0};


const StringReaderConfig_t StringReaderConfig[] = {
    { 
        .num = 1,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .feedback_led = 1,
        .interface_if = { .interface_name = INTERFACE_NAME_SEGGER_RTT, .num = 1, },
        .name = "RTT",
        .fifo_heap = FifoData1,
        .fifo_heap_size = sizeof(FifoData1),
        .string = LineData1,
        .string_size = sizeof(LineData1),
        .callback = (handle_string_f)(cli_process_cmd),
    },

    { 
        .num = 2,
        .feedback_led = 1,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .interface_if = { .interface_name = INTERFACE_NAME_UART, .num = 2,},
        .name = "UART2",
        .fifo_heap = FifoData2,
        .fifo_heap_size = sizeof(FifoData2),
        .string = LineData2,
        .string_size = sizeof(LineData2),
        .callback = (handle_string_f)(cli_process_cmd),
    },
};

StringReaderHandle_t StringReaderInstance[]={
    {.num=1, .valid=true, },
    {.num=2, .valid=true, },
};

COMPONENT_GET_CNT(StringReader, string_reader)
