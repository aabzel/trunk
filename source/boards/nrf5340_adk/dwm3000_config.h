
#ifndef DWM3000_CONFIG_H
#define DWM3000_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "dwm3000_types.h"

#ifndef HAS_DWM3000
#error " +HAS_DWM3000"
#endif

#ifndef HAS_GPIO
#error " +HAS_GPIO"
#endif

#ifndef HAS_SPI
#error " +HAS_SPI"
#endif

#define DWM3000_MAIN 1
#define DWM3000_SPI_NUM 4

extern const Dwm3000Config_t Dwm3000Config;
extern Dwm3000Handle_t Dwm3000Instance;

#endif /* DWM3000_CONFIG_H */
