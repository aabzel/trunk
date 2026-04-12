#include "string_reader_config.h"

#include "cli_drv.h"
#include "data_utils.h"

#ifdef HAS_UART1
static uint8_t  FifoData1[100] = {0};
static uint8_t  LineData1[100] = {0};
#endif

#ifdef HAS_UART2
static uint8_t  FifoData2[100] = {0};
static uint8_t  LineData2[100] = {0};
#endif

#ifdef HAS_UART3
static uint8_t  FifoData3[100] = {0};
static uint8_t  LineData3[100] = {0};
#endif

const StringReaderConfig_t StringReaderConfig[] = {
#ifdef HAS_UART1
{
    .num = 1,
    .valid = true,
    .echo = true,
    .cli_num = 1,
    .core = 1,
    .interface_if = IF_UART1,
    .if_num = 1,
    .name = "UART1",
    .fifo_heap = FifoData1,
    .fifo_heap_size = sizeof(FifoData1),
    .string = LineData1,
    .string_size = sizeof(LineData1),
    .callback = (handle_string_f)(cli_process_cmd),
    .feedback_led = 4,
},
#endif

#ifdef HAS_UART2
{
    .num = 2,
    .core = 2,
    .valid = true,
    .echo = true,
    .cli_num = 2,
    .interface_if = IF_UART2,
    .if_num = 2,
    .name = "UART2",
    .fifo_heap = FifoData2,
    .fifo_heap_size = sizeof(FifoData2),
    .string = LineData2,
    .string_size = sizeof(LineData2),
    .callback = (handle_string_f)(cli_process_cmd),
    .feedback_led = 4,
},
#endif

#ifdef HAS_UART3
{
    .num = 3,
    .core = 3,
    .valid = true,
    .echo = true,
    .cli_num = 3,
    .interface_if = IF_UART3,
    .if_num = 3,
    .name = "UART3",
    .fifo_heap = FifoData3,
    .fifo_heap_size = sizeof(FifoData3),
    .string = LineData3,
    .string_size = sizeof(LineData3),
    .callback = (handle_string_f)(cli_process_cmd),
    .feedback_led = 4,
},
#endif
};

StringReaderHandle_t StringReaderInstance[] = {
#ifdef HAS_UART1
    {
        .num = 1,
        .valid = true,
    },
#endif

#ifdef HAS_UART2
    {
        .num = 2,
        .valid = true,
    },
#endif

#ifdef HAS_UART3
    {
        .num = 3,
        .valid = true,
    },
#endif
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
