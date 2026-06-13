#ifndef WRITER_CONFIG_H
#define WRITER_CONFIG_H

#include "std_includes.h"
#include "writer_types.h"

#ifdef HAS_UART
#include "writer_uart.h"
#endif

typedef enum {
#ifdef HAS_UART1
    WRITER_NUM_UART1,
#endif

#ifdef HAS_SEGGER_RTT
    WRITER_NUM_SEGGER_RTT1  ,
#endif

#ifdef HAS_ISO_TP
    WRITER_NUM_ISO_TP1  ,
#endif

#ifdef HAS_USB_SERIAL
    WRITER_NUM_USB_SERIAL  ,
#endif

#ifdef HAS_UART2
    WRITER_NUM_UART2  ,
#endif
    WRITER_NUM_CNT  ,
}WriterLegalNum_t;

extern WriterHandle_t dbg_o;

extern WriterHandle_t *curWriterPtr;
extern const WriterConfig_t WriterConfig[6];
extern WriterHandle_t WriterInstance[6];

uint32_t writer_get_cnt(void);

#endif /* WRITER_CONFIG_H */


