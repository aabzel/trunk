#ifndef ACCELEROMETER_CONFIG_H
#define ACCELEROMETER_CONFIG_H


#include "std_includes.h"
#include "accelerometer_types.h"

extern const AccelerometerConfig_t AccelerometerConfig[ ];
extern AccelerometerHandle_t AccelerometerInstance[ ];

uint32_t accelerometer_get_cnt(void);

#endif /* ACCELEROMETER_CONFIG_H  */
