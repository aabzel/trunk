#ifndef WATCHDOG_PARAMS_H
#define WATCHDOG_PARAMS_H

#include "storage_types.h"

#define PARAMS_WATCHDOG                                           \
    {.facility = WATCHDOG,                                        \
     .id = PAR_ID_WATCHDOG_BOOTLOADER_ON,                         \
     .default_value = "0",                                        \
     .len = 1,                                                    \
     .type = TYPE_UINT8,                                          \
     .parser = U8DecToStr,                                        \
     .Units = STORAGE_UNITS_NO_UNIT,                              \
     .Scale = STORAGE_SCALE_ONES,                                 \
     .physical_quantity = STORAGE_PHYSICAL_QUANTITY_NO,           \
     .name = "WatchDogBootLoaderOn" ,                             \
    },                                                            \
    {                                                             \
     .facility = WATCHDOG,                                        \
     .id = PAR_ID_WATCHDOG_GENERIC_ON,                            \
     .default_value = "0",                                        \
     .len = 1,                                                    \
     .type = TYPE_UINT8,                                          \
     .parser = U8DecToStr,                                        \
     .Units = STORAGE_UNITS_NO_UNIT,                              \
     .Scale = STORAGE_SCALE_ONES,                                 \
     .physical_quantity = STORAGE_PHYSICAL_QUANTITY_NO,           \
     .name = "WatchDogGenericOn",                                 \
    },                                                            \
    {                                                             \
     .facility = WATCHDOG,                                        \
     .id = PAR_ID_WATCHDOG_TIME_OUT_MS,                           \
     .default_value = "14000",                                    \
     .len = 4,                                                    \
     .type = TYPE_UINT32,                                         \
     .parser = U32DecToStr,                                       \
     .Units = STORAGE_UNITS_SECOND,                               \
     .Scale = STORAGE_SCALE_MILLI,                                \
     .physical_quantity = STORAGE_PHYSICAL_QUANTITY_TIME,         \
     .name = "WatchDogTimeOutMs",                                 \
},


#endif /* WATCHDOG_PARAMS_H  */
