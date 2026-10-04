#include "writer_config.h"

#include "data_utils.h"
#include "writer_stdout.h"
#include "writer_types.h"

static uint8_t WriterArray[4000] = {0};

const WriterConfig_t WriterConfig[] = {
    {
        .num = WRITER_NUM_STDIO,
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
        .num = WRITER_NUM_STDIO,
        .valid = true,
    },
};

WriterHandle_t* curWriterPtr = &WriterInstance[0];

COMPONENT_GET_CNT(Writer, writer)
