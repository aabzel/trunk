#ifndef ACCELEROMETER_NVRAM_H
#define ACCELEROMETER_NVRAM_H

#include "accelerometer_type.h"

#define NVRAM_IDS_ACCELEROMETER     \
    NVRAM_ID_ACCEL_CALIB1 = 94,     \
    NVRAM_ID_ACCEL_CALIB2 = 93,

#define NVRAM_ACCELEROMETER                                           \
    {                                                                 \
        .eepromAddress =  16,                                         \
        .id = NVRAM_ID_ACCEL_CALIB1,                                  \
        .type = STORAGE_TYPE_STRUCT,                                  \
        .len = sizeof(ACCEL_CALIB_DATA),                              \
        .defaultValue = "0",                                          \
        .name = "AccelCalib1"                                         \
    },                                                                \
    {                                                                 \
        .eepromAddress = 40,                                          \
        .id = NVRAM_ID_ACCEL_CALIB2,                                  \
        .type = STORAGE_TYPE_STRUCT,                                  \
        .len = sizeof(ACCEL_CALIB_DATA),                              \
        .defaultValue = "0",                                          \
        .name = "AccelCalib2"                                         \
    },


#endif /* ACCELEROMETER_NVRAM_H  */
