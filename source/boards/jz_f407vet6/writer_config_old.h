#ifndef WRITER_CONFIG_H
#define WRITER_CONFIG_H

#include "std_includes.h"
#include "writer_types.h"

#ifdef HAS_UART
#include "writer_uart.h"
#endif

typedef enum {
    WRITER_NUM_SEGGER_RTT1 = 1,
    WRITER_NUM_ISO_TP1 = 2,
    WRITER_NUM_UART1 = 3,
    WRITER_NUM_UART2 = 4,
    WRITER_NUM_USB_SERIAL = 5,
    WRITER_NUM_ESP_01 = 6,
}WriterLegalNum_t;

extern WriterHandle_t dbg_o;

extern WriterHandle_t *curWriterPtr;
extern const WriterConfig_t WriterConfig[];
extern WriterHandle_t WriterInstance[5];

uint32_t writer_get_cnt(void);

#endif /* WRITER_CONFIG_H */


