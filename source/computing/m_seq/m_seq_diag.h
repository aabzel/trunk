#ifndef M_SEQ_DIAG_H
#define M_SEQ_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "m_seq_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_M_SEQ
#error "+HAS_M_SEQ"
#endif

#ifndef HAS_M_SEQ_DIAG
#error "+HAS_M_SEQ_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool m_seq_diag(void);
bool m_seq_diag_one(uint8_t num);
bool m_seq_raw_reg_diag(uint8_t num);
const char* MseqConfigToStr(const MseqConfig_t* const Config);
const char* MseqNodeToStr(const MseqHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* M_SEQ_DIAG_H  */
