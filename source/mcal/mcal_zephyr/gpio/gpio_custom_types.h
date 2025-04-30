#ifndef GPIO_ZEPHYR_TYPES_H
#define GPIO_ZEPHYR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "gpio_custom_const.h"

#include "nrf5340_types.h"
#include "gpio_types.h"

#include <zephyr/dt-bindings/gpio/gpio.h>
#include <zephyr/drivers/gpio.h>


typedef struct{
	Port_t port_num;
	struct device* port;
}PortInfo_t;

typedef enum {
	ZEPHYR_PULL_AIR = 0,
	ZEPHYR_PULL_UP = GPIO_PULL_UP,
	ZEPHYR_PULL_DOWN = GPIO_PULL_DOWN,
} ZephyrPull_t;

typedef enum {
	ZEPHYR_INPUT = GPIO_INPUT,
	ZEPHYR_OUTPUT = GPIO_OUTPUT,
} ZephyrDir_t;

#ifdef __cplusplus
}
#endif

#endif /* GPIO_ZEPHYR_TYPES_H  */
