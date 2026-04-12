#include "writer_config.h"

#include "data_utils.h"
#include "writer_stdout.h"
#include "writer_types.h"

static uint8_t WriterArray[4000] = {0};

const WriterConfig_t WriterConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "STDIO",
        .inter_face =
            {
                .interface_name = INTERFACE_NAME_STDIO,
                .num = 0,
            },
        .TxArray = WriterArray,
        .tx_array_size = ARRAY_SIZE(WriterArray),
        .f_putch = stdout_putc,
        .f_putstr = stdout_puts,
        .f_transmit = stdout_writer_transmit,
    },
};

WriterHandle_t WriterInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

WriterHandle_t* curWriterPtr = &WriterInstance[0];

uint32_t writer_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(WriterInstance);
    cnt2 = ARRAY_SIZE(WriterConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
