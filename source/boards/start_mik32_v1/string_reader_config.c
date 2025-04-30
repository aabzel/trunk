#include "string_reader_config.h"

#include "data_utils.h"
#include "cli_drv.h"
//#include "c_defines_generated.h"

static char FifoData0[80]={0};
static char LineData0[80]={0};

#ifdef HAS_SR2
static char FifoData1[80]={0};
static char LineData1[80]={0};
#endif

const StringReaderConfig_t StringReaderConfig[] = {
    {
        .num = 1,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .interface_if = IF_UART0,
        .if_num = 0,
        .name = "UART0",
        .fifo_heap = FifoData0,
        .fifo_heap_size = sizeof(FifoData0),
        .string = LineData0,
        .string_size = sizeof(LineData0),
        .callback = (handle_string_f)(cli_process_cmd),
        .feedback_led = 2,
    },
#ifdef HAS_SR2
    { 
        .num = 2,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .interface_if = IF_UART1,
        .if_num = 1,
        .name = "UART1",
        .fifo_heap = FifoData1,
        .fifo_heap_size = sizeof(FifoData1),
        .string = LineData1,
        .string_size = sizeof(LineData1),
        .callback = (handle_string_f)(cli_process_cmd),
        .feedback_led = 2,
    },
#endif
};


StringReaderHandle_t StringReaderInstance[]={
    {.num=1, .valid=true, },
#ifdef HAS_SR2
    {.num=2, .valid=true, },
#endif
};

uint32_t string_reader_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(StringReaderInstance);
    cnt2 = ARRAY_SIZE(StringReaderConfig);
    if (cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
