#ifndef GPIO_CUSTOM_TYPES_H
#define GPIO_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "gpio_custom_const.h"

typedef union {
    uint8_t byte;
    struct {
        uint8_t pin  : 4; /*0....15*/
        uint8_t port : 4; /*A B C D E F G H*/
    };
}Pad_t;

typedef union {
    uint8_t byte;
    struct{
        uint8_t code :4;
        uint8_t res :4;
    };
}AltFunc_t;

typedef union {
    uint32_t reg_val;
    struct{
        uint32_t pin0_pull :2;
        uint32_t pin1_pull :2;
        uint32_t pin2_pull :2;
        uint32_t pin3_pull :2;
        uint32_t pin4_pull :2;
        uint32_t pin5_pull :2;
        uint32_t pin6_pull :2;
        uint32_t pin7_pull :2;
        uint32_t pin8_pull :2;
        uint32_t pin9_pull :2;
        uint32_t pin10_pull :2;
        uint32_t pin11_pull :2;
        uint32_t pin12_pull :2;
        uint32_t pin13_pull :2;
        uint32_t pin14_pull :2;
        uint32_t pin15_pull :2;
    };
}GpioRegPull_t;


typedef struct {
    bool valid;
    Port_t port;
    //crm_periph_clock_type clock_type;
    //scfg_port_source_type port_source;/*System configuration controller*/
    GPIO_TypeDef* GPIOx;
}GpioInfo_t;



#ifdef __cplusplus
}
#endif

#endif /* GPIO_CUSTOM_TYPES_H  */
