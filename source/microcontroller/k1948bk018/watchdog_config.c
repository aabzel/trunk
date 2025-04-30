#include "watchdog_config.h"

#include "clock_utils.h"

/*constant compile-time known settings in Flash*/
const WatchDogConfig_t WatchDogConfig = {
    .on = false,
    .valid = true,
    .timeout_s = 15.0,
    .base_freq_hz = 32768,
    .bitness = 12,              // up
};

WatchDogHandle_t WatchDogInstance = {
    .valid = true,
};
