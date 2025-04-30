
#ifndef AXP192_DRV_H
#define AXP192_DRV_H

#include <stdbool.h>
#include <stdint.h>

bool axp192_init(void);
bool axp192_process(void);
bool axp192_i2c_read(uint8_t reg, uint8_t *value);
bool axp192_i2c_write(uint8_t reg, uint8_t value);

#endif /* AXP192_DRV_H  */
