#include "string_reader_config.h"

#include "cli_drv.h"
#include "data_utils.h"

static char FifoData[500] = {0};
static char LineData[500] = {0};

const StringReaderConfig_t StringReaderConfig[] = {
    {
    .num = 1,
    .valid = true,
    .echo = true,
    .cli_num = 1,
    .interface_if = IF_STDIO,
    .if_num = 0,
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

uint32_t string_reader_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(StringReaderInstance);
    cnt2 = ARRAY_SIZE(StringReaderConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
