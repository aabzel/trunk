#ifndef WRITER_CONFIG_H
#define WRITER_CONFIG_H

#include "std_includes.h"
#include "writer_types.h"

#ifdef HAS_X86_64
#include "writer_stdout.h"
#endif /**/

extern WriterHandle_t *curWriterPtr;
extern const WriterConfig_t WriterConfig[];
extern WriterHandle_t WriterInstance[];

uint32_t writer_get_cnt(void);

#endif /* WRITER_CONFIG_H */

