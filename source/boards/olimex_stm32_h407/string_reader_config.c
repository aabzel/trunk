#include "string_reader_config.h"

#include "data_utils.h"
#include "cli_drv.h"
//#include "c_defines_generated.h"

static char FifoData1[100]={0};
static char LineData1[100]={0};
#ifdef HAS_USB
static char FifoData2[100]={0};
static char LineData2[100]={0};
#endif

const StringReaderConfig_t StringReaderConfig[] = {
    { 
        .num = 1,
        .valid = true,
        .echo = true,
        .cli_num= 1,
        .interface_if = IF_UART3,
        .if_num = 3,
        .name= "UART3",
        .fifo_heap = FifoData1,
        .fifo_heap_size=sizeof(FifoData1),
        .string=LineData1,
        .string_size= sizeof(LineData1),
        .callback =(handle_string_f)(cli_process_cmd),
        .feedback_led=1,
    },

#ifdef HAS_USB
    {
        .num = 2,
        .valid = true,
        .echo = true,
        .cli_num = 1,
        .interface_if = IF_USB_HID,
        .if_num = 3,
        .name = "USB_HOST_HID",
        .fifo_heap = FifoData2,
        .fifo_heap_size = sizeof(FifoData2),
        .string = LineData2,
        .string_size = sizeof(LineData2),
        .callback = (handle_string_f)(cli_process_cmd),
        .feedback_led = 1,
    },
#endif
};

StringReaderHandle_t StringReaderInstance[]={
    {.num=1, .valid=true, },
#ifdef HAS_USB
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
