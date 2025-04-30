
#ifndef GPIO_NRF5340_MCU_CONFIG_H
#define GPIO_NRF5340_MCU_CONFIG_H

typedef enum  {
    PORT_0 = 0,
    PORT_1 = 1,

    PORT_UNDEF = 8,
} Port_t;

#define GPIO_PORT_MAX 1

#endif /* GPIO_NRF5340_MCU_CONFIG_H */
