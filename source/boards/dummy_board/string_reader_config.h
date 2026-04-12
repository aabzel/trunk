#ifndef STRING_READER_CONFIG_H
#define STRING_READER_CONFIG_H

#include "string_reader_types.h"

extern const StringReaderConfig_t StringReaderConfig[];
extern StringReaderHandle_t StringReaderInstance[];

uint32_t string_reader_get_cnt(void);

#endif /*STRING_READER_CONFIG_H*/
