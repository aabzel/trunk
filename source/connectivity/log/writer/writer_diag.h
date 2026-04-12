#ifndef WRITER_DIAG_H
#define WRITER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "writer_types.h"

bool writer_diag(void);
const char* WriterConfigToStr(const WriterConfig_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* WRITER_DIAG_H */
