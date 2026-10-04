#include "string_reader_config.h"

#include "data_utils.h"
#include "cli_drv.h"

static uint8_t FifoData1[100]={0};
static uint8_t LineData1[100]={0};

const StringReaderConfig_t StringReaderConfig[] = {
    { 
    .num = 1, 
    .valid = true,
    .echo = true,
    .cli_num = 1,
    .interface_if =  { .interface_name=INTERFACE_NAME_UART,  .num=2, } ,
    .name = "CLIin",
    .fifo_heap = FifoData1,
    .fifo_heap_size = sizeof(FifoData1),
    .string = LineData1,
    .string_size = sizeof(LineData1),
    .callback = (handle_string_f)(cli_process_cmd),
    .feedback_led = 1,
   },
};

StringReaderHandle_t StringReaderInstance[]={
    {
    	.num = 1, 
    .valid = true,
     },
};

COMPONENT_GET_CNT(StringReader, string_reader)
