#include "string_reader_config.h"

#include "cli_drv.h"
#include "data_utils.h"

#define SR_MAX_LINE 7000
static uint8_t FifoData[SR_MAX_LINE] = {0};
static uint8_t LineData[SR_MAX_LINE] = {0};

const StringReaderConfig_t StringReaderConfig[] = {
    {
    .num = 1,
    .valid = true,
    .echo = true,
    .core = 1,
    .cli_num = 1,
    .interface_if = {
                        .interface_name = INTERFACE_NAME_STDIO,
                        .num = 0,
                    },
    .name = "STDIN",
    .fifo_heap = FifoData,
    .fifo_heap_size = sizeof(FifoData),
    .string = LineData,
    .string_size = sizeof(LineData),
    .callback = (handle_string_f)(cli_process_cmd),
}};

StringReaderHandle_t StringReaderInstance[] = {
    {
    .num = 1,
    .valid = true,
    }
};


COMPONENT_GET_CNT(StringReader, string_reader)
