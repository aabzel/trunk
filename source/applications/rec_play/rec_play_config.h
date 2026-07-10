#ifndef REC_PLAY_CONFIG_H
#define REC_PLAY_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "rec_play_types.h"
#include "rec_play_dep.h"

extern const RecPlayConfig_t RecPlayConfig[];
extern RecPlayHandle_t RecPlayInstance[];

uint32_t rec_play_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* REC_PLAY_CONFIG_H */
