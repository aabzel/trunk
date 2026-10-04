#ifndef WRITER_CONFIG_H
#define WRITER_CONFIG_H

#include "std_includes.h"
#include "writer_types.h"

#ifdef HAS_UART
#include "writer_uart.h"
#endif


typedef enum{

#ifdef HAS_UART1
    WRITER_NUM_UART1,
#endif

#ifdef HAS_UART2
    WRITER_NUM_UART2,
#endif

#ifdef HAS_UART6
    WRITER_NUM_UART6,
#endif

    WRITER_NUM_CNT
}WrilerLegalNums_t;

extern uint8_t DbgOutData[DBG_TX_ARRAY_SIZE] ;

extern WriterHandle_t* pDBGo ;

extern WriterHandle_t *curWriterPtr;
extern const WriterConfig_t WriterConfig[];
extern WriterHandle_t WriterInstance[];

uint32_t writer_get_cnt(void);

#endif /* WRITER_CONFIG_H */


