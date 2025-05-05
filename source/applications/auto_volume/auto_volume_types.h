#ifndef AUTO_VOLUME__TYPES_H
#define AUTO_VOLUME__TYPES_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
#include <stdint.h>

#include "auto_volume_const.h"
#include "auto_volume_dep.h"

#ifdef HAS_AUDIO

#include "audio_types.h"
#define AUDIO_VARIABLES               \
    Gain_t off_gain;                  \
    Gain_t max_gain;                  \
    Gain_t min_gain;                  \
    Gain_t on_gain;

#else
#define AUDIO_VARIABLES
#endif

#ifdef HAS_MAX9860
#include "max9860_types.h"
#endif /*HAS_MAX9860*/

#define AUTO_VOLUME_COMMON_VAR        \
    AUDIO_VARIABLES                   \
    uint8_t num;                      \
    uint8_t dist_num;                 \
    uint8_t schmitt_trigger_num;      \
    bool valid;

typedef struct {
    AUTO_VOLUME_COMMON_VAR
   char* name;
} AutoVolumeConfig_t;

typedef struct {
    AUTO_VOLUME_COMMON_VAR
    bool init;
    uint32_t err_cnt;
    bool on;
    double distance_m;
} AutoVolumeItem_t;

#ifdef __cplusplus
}
#endif

#endif /* AUTO_VOLUME__TYPES_H */
