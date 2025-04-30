#ifndef FLASH_CONFIG_GENERAL_H
#define FLASH_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "flash_types.h"

#ifndef HAS_FLASHER
#error "Add HAS_FLASHER"
#endif /*HAS_FLASHER*/

extern const FlashConfig_t FlashConfig;

#endif /* FLASH_CONFIG_GENERAL_H  */
