#include "auto_volume_config.h"

#include "auto_volume_types.h"

const AutoVolumeConfig_t AutoVolumeConfig = {
#ifdef HAS_AUDIO
    .on_gain = -10,
    .off_gain = -80,
    .max_gain = 3,
    .min_gain = -90,
#endif /*HAS_AUDIO*/
    .schmitt_trigger_num = 1,
    .dist_num = 1,
    .valid = true,
    .num = 1,
    .name = "AutoVol",
    // .led_num = 3,
};

AutoVolumeItem_t AutoVolumeItem = {
    .valid = true,
};
