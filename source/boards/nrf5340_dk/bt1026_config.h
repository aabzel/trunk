
#ifndef BT1026_CONFIG_H
#define BT1026_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "bt1026_types.h"

#ifndef HAS_BT1026
#error "+HAS_BT1026"
#endif

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_UART
#error "+HAS_UART"
#endif

#ifndef HAS_I2S
#error "+HAS_I2S"
#endif

extern const Bt1026Config_t Bt1026Config;
extern Bt1026Handle_t Bt1026Item;

#endif /* BT1026_CONFIG_H */
