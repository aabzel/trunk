#ifndef LIGHT_SENSOR_MONO_CONST_H
#define LIGHT_SENSOR_MONO_CONST_H

#include <stdbool.h>
#include <stdint.h>

#include "light_sensor_dep.h"

#define LIGHT_SENSOR_NAME_SIZE 20

typedef enum{
	LI_SENS_PHOTORESISTOR = 1,
 	LI_SENS_BH1750=2,
	LI_SENS_LTR390_ALS=3,
	LI_SENS_LTR390_UVS=4,

	LI_SENS_UNDEF= 0,
}LightSensor_t;

#endif /* LIGHT_SENSOR_MONO_CONST_H  */
