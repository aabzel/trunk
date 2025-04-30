#include "watchdog_config.h"

#include "clock_utils.h"

/*constant compile-time known settings in Flash*/
const WatchDogConfig_t WatchDogConfig = {
    .on = true,
    .valid = true,
    .timeout_ms = 15000,
    .base_address = IWDG_BASE, // 0x40003000 - 0x4000 33FF Watchdog timer (WDT)
    .base_freq_hz = 40000,      // LICK Figure 4-1 AT32F435/437 clock tree
    .bitness = 12,              // downcounter
};

WatchDogHandle_t WatchDogInstance = {
    .valid = true,

};
