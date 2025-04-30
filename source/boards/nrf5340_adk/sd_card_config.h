#ifndef SD_CARD_CONFIG_H
#define SD_CARD_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "sd_card_types.h"

#ifndef HAS_SD_CARD
#error "+HAS_SD_CARD"
#endif

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif

extern const SdCardConfig_t SdCardConfig;
extern SdCardHandle_t SdCardInstance;

#endif /* SD_CARD_CONFIG_H */
