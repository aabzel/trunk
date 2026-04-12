#ifndef WRITER_CONFIG_H
#define WRITER_CONFIG_H

#include "std_includes.h"
#include "writer_types.h"

#ifdef HAS_UART
#include "writer_uart.h"
#endif

typedef enum{
    WRITER_NUM_UART1,
    WRITER_NUM_SEGGER_RTT1  ,
    WRITER_NUM_ISO_TP1  ,
    WRITER_NUM_USB_SERIAL  ,
    WRITER_NUM_UART2  ,
}WriterLegalNum_t;

//extern uint8_t DbgOutData[DBG_TX_ARRAY_SIZE] ;
extern WriterHandle_t dbg_o;

extern WriterHandle_t *curWriterPtr;
extern const WriterConfig_t WriterConfig[];
extern WriterHandle_t WriterInstance[6];

uint32_t writer_get_cnt(void);

#endif /* WRITER_CONFIG_H */


