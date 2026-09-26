#ifndef STRING_READER_CONFIG_H
#define STRING_READER_CONFIG_H

#include "string_reader_types.h"

typedef enum{
    STRING_READER_NUM_UART1,
    STRING_READER_NUM_RTT,
#ifdef HAS_USB_SERIAL
    STRING_READER_NUM_USB_SERIAL,
#endif
    STRING_READER_NUM_CNT,
}tringReaderLegalNum_t;

extern const StringReaderConfig_t StringReaderConfig[];
extern StringReaderHandle_t StringReaderInstance[];

uint32_t string_reader_get_cnt(void);

#endif /*STRING_READER_CONFIG_H*/
