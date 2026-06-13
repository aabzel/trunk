#ifndef PHOTO_RESISTOR_CONFIG_GENERAL_H
#define PHOTO_RESISTOR_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "photoresistor_types.h"

extern const PhotoResistorConfig_t PhotoResistorConfig[];
extern PhotoResistorHandle_t PhotoResistorInstance[];

uint32_t photo_resistor_get_cnt(void);

#endif /* PHOTO_RESISTOR_CONFIG_GENERAL_H  */
