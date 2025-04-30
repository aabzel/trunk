
#ifndef NRF5340_H
#define NRF5340_H

#include <stdbool.h>

#include "macro_utils.h"
#include "nrf5340_types.h"

#ifdef HAS_FLASH_CUSTOM
#include "flash_custom_const.h"
#endif

#if defined(HAS_GPIO) && defined(HAS_PINS)
#include "gpio_types.h"
#include "pin_config.h"
#endif

Port_t PortLetter2PortNum(char port);

bool nrf5340_get_id(uint64_t* const dev_id);
bool mcu_init(void);

#endif /* NRF5340_H */
