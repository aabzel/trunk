#ifndef WRITER_CONFIG_H
#define WRITER_CONFIG_H

#include "writer_types.h"
#include "writer_stdout.h"

typedef enum{
    WRITER_NUM_STDIO ,
    WRITER_NUM_CNT,
}WriterLegalNums_t;

extern WriterHandle_t *curWriterPtr;
extern const WriterConfig_t WriterConfig[];
extern WriterHandle_t WriterInstance[];

uint32_t writer_get_cnt(void);

#endif /* WRITER_CONFIG_H */



