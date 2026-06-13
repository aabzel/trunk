#ifndef WRITER_CONFIG_H
#define WRITER_CONFIG_H

#include "std_includes.h"
#include "writer_types.h"

#ifdef HAS_UART
#include "writer_uart.h"
#endif

typedef enum {
#ifdef HAS_SEGGER_RTT
    WRITER_NUM_SEGGER_RTT1  ,
#endif

#ifdef HAS_USB_SERIAL
    WRITER_NUM_USB_SERIAL  ,
#endif

#ifdef HAS_ISO_TP
    WRITER_NUM_ISO_TP1  ,
    WRITER_NUM_ISO_TP2  ,
    WRITER_NUM_ISO_TP3  ,
#endif

#ifdef HAS_UART1
    WRITER_NUM_UART1,
#endif

#ifdef HAS_UART2
    WRITER_NUM_UART2  ,
#endif

#ifdef HAS_UART3
    WRITER_NUM_UART3  ,
#endif

#ifdef HAS_UART4
    WRITER_NUM_UART4  ,
#endif

#ifdef HAS_UART7
    WRITER_NUM_UART7  ,
#endif

#ifdef HAS_UART6
    WRITER_NUM_UART6  ,
#endif

#ifdef HAS_UART8
    WRITER_NUM_UART8  ,
#endif

#ifdef HAS_ESP_01
    WRITER_NUM_ESP_01  ,
#endif

    WRITER_NUM_CNT  ,
}WriterLegalNum_t;


extern WriterHandle_t dbg_o;

extern WriterHandle_t *curWriterPtr;
extern const WriterConfig_t WriterConfig[];
extern WriterHandle_t WriterInstance[6];

uint32_t writer_get_cnt(void);

#endif /* WRITER_CONFIG_H */


