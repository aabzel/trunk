#ifndef M_SEQ_CONFIG_H
#define M_SEQ_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "m_seq_types.h"
#include "m_seq_dep.h"

extern const MseqConfig_t MseqConfig[];
extern MseqHandle_t MseqInstance[];

uint32_t m_seq_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* M_SEQ_CONFIG_H */
