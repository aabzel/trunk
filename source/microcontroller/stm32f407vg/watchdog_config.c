#include "watchdog_config.h"

#include "clock_utils.h"

/*constant compile-time known settings in Flash*/
const WatchDogConfig_t SECTION_CFG_DATA WatchDogConfig = {
    .on = true,
    .valid = true,
    .timeout_s = 15.0f,
    .base_address = IWDG_BASE, // 0x40003000 - 0x4000 33FF Watchdog timer (WDT)
    .base_freq_hz = 40000,
    .bitness = 12,              // downcounter
    // 0x40003000 - 0x4000 33FF Watchdog timer (WDT)
};

WatchDogHandle_t WatchDogInstance = {
    .valid = true,

};
