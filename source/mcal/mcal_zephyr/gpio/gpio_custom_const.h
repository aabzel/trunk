#ifndef GPIO_ZEPHYR_CONST_H
#define GPIO_ZEPHYR_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum  {
    BSP_GPIO_PULL_DOWN = 1,
	BSP_GPIO_PULL_UP = 2,
	BSP_GPIO_PULL_AIR = 3,
	BSP_GPIO_PULL_UNDEF = 4,
	BSP_GPIO_PULL_UP_DOWN = 5,
}BSPGpioPullMode_t;

#ifdef __cplusplus
}
#endif

#endif /* GPIO_ZEPHYR_CONST_H  */
