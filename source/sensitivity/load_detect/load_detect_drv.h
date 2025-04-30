#ifndef LOAD_DETECT_DRIVER_H
#define LOAD_DETECT_DRIVER_H

#include <stdbool.h>
#include <stdint.h>

#include "gpio_types.h"
#include "load_detect_config.h"
#include "load_detect_dep.h"
#include "load_detect_types.h"

LoadDetectHandle_t* LoadDetectGetNode(uint8_t num);
const LoadDetectConfig_t* LoadDetectGetConfNode(uint8_t num);

LoadDetectPinInfo_t* LoadDetectGetPinNode(uint8_t pin_num);
bool load_detect_enable(uint8_t num, bool enable);
bool load_detect_enable_pad(uint8_t num, Pad_t pad, bool enable);
bool load_detect_init(void);
bool load_detect_init_one(uint8_t num);
bool load_detect_proc(void);

#endif /* LOAD_DETECT_DRIVER_H  */
