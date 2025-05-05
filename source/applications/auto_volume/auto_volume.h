#ifndef AUTO_VOLUME_DRV_H
#define AUTO_VOLUME_DRV_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "auto_volume_config.h"
#include "auto_volume_types.h"

#ifdef HAS_MAX9860
Gain_t Dist2Max9860Attenuation(double dist_m);
#endif

int8_t Dist2Volume(double dist_m);
bool auto_volume_proc(void);
bool auto_volume_init(void);
bool auto_volume_init_one(const AutoVolumeConfig_t* const Config, AutoVolumeItem_t* const Node);
bool auto_volume_set(AutoVolumeItem_t* const Node, AutoVolumeCmd_t cmd);

#ifdef __cplusplus
}
#endif

#endif /* AUTO_VOLUME_DRV_H */
