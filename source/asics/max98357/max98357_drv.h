
#ifndef MAX98357_DRV_H
#define MAX98357_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "max98357_types.h"
#include "max98357_config.h"

#ifndef HAS_MAX98357
#error "+HAS_MAX98357"
#endif

#ifndef HAS_I2S
#warning "+HAS_I2S"
#endif

bool max98357_init_one(uint8_t num);
const Max98357Config_t* Max98357GetConfig(uint8_t num);
Max98357Handle_t* Max98357GetNode(uint8_t num);
bool max98357_play_1kHz_tone(uint8_t num, double amplitude, double phase_ms) ;

bool max98357_init(void);

#endif /* MAX98357_DRV_H */
