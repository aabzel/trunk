#ifndef WATCH_DOG_TYPES_H
#define WATCH_DOG_TYPES_H

#include "watchdog_const.h"

#ifdef HAS_WATCHDOG_CUSTOM
#include "watchdog_custom_types.h"
#else
#define WATCHDOG_CUSTOM_VARIABLE
#endif

#define WATCHDOG_COMMON_VARIABLE   \
    bool valid;                    \
    bool on;                       \
    uint8_t bitness;               \
    uint32_t base_freq_hz;         \
    float timeout_s;

typedef struct  {
    WATCHDOG_COMMON_VARIABLE
} WatchDogConfig_t;

typedef struct  {
    WATCHDOG_COMMON_VARIABLE
    WATCHDOG_CUSTOM_VARIABLE
    bool init;
} WatchDogHandle_t;


#endif /* WATCH_DOG_TYPES_H */
