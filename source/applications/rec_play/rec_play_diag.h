#ifndef REC_PLAY_DIAG_H
#define REC_PLAY_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "rec_play_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_REC_PLAY
#error "+HAS_REC_PLAY"
#endif

#ifndef HAS_REC_PLAY_DIAG
#error "+HAS_REC_PLAY_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool rec_play_diag(void);
bool rec_play_diag_one(uint8_t num);
bool rec_play_raw_reg_diag(uint8_t num);
const char* RecPlayConfigToStr(const RecPlayConfig_t* const Config);
const char* RecPlayNodeToStr(const RecPlayHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* REC_PLAY_DIAG_H  */
