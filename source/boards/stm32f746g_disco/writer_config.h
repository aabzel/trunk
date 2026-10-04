#ifndef WRITER_CONFIG_H
#define WRITER_CONFIG_H

#include "std_includes.h"
#include "writer_types.h"

#define DBG_TX_ARRAY_SIZE (200U)

typedef enum {
    WRITER_NUM_SEGGER_RTT1 = 1,
    WRITER_NUM_UART1 = 2,
    WRITER_NUM_ISO_TP1 = 3,
    WRITER_NUM_ISO_TP2 = 4,
    WRITER_NUM_UART3 = 5,
    WRITER_NUM_CNT = 6,
}WriterLegalNum_t;


extern WriterHandle_t dbg_o;

extern WriterHandle_t *curWriterPtr;
extern const WriterConfig_t WriterConfig[];
extern WriterHandle_t WriterInstance[];

uint32_t writer_get_cnt(void);

#endif /* WRITER_CONFIG_H */


