#ifndef ESP_01_CONFIG_H
#define ESP_01_CONFIG_H

#include "std_includes.h"
#include "esp_01_types.h"

#ifndef HAS_ESP_01
#error "+HAS_ESP_01"
#endif

extern const Esp01Config_t Esp01Config[];
extern Esp01Handle_t Esp01Instance[];

uint32_t esp_01_get_cnt(void);

#endif /* ESP_01_CONFIG_H */
