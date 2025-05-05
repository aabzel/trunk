#ifndef AUTO_VOLUME_DIAG_H
#define AUTO_VOLUME_DIAG_H

#include <stdbool.h>

#include "auto_volume_types.h"
#include "auto_volume_config.h"

bool auto_volume_diag(void);
bool AutoVolumeDiagNode(const AutoVolumeItem_t* const Node);
bool AutoVolumeDiagConfig(const AutoVolumeConfig_t* const Config);
const char* VolumeCmd2Str(AutoVolumeCmd_t cmd);

#endif /* AUTO_VOLUME_DIAG_H */
