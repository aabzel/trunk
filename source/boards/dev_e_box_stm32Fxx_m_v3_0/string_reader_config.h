#ifndef STRING_READER_CONFIG_H
#define STRING_READER_CONFIG_H

#include "string_reader_types.h"

typedef enum{
    STRING_READER_NUM_UNDEF=0,

#ifdef HAS_UART1
    STRING_READER_NUM_UART1,
#endif

#ifdef HAS_UART2
    STRING_READER_NUM_UART2,
#endif

#ifdef HAS_USB
    STRING_READER_NUM_USB,
#endif

    STRING_READER_NUM_CNT,

}StringReaderLeglNums_t;



extern const StringReaderConfig_t StringReaderConfig[];
extern StringReaderHandle_t StringReaderInstance[];

uint32_t string_reader_get_cnt(void);

#endif /*STRING_READER_CONFIG_H*/
