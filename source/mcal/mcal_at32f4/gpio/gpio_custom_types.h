#ifndef GPIO_CUSTOM_TYPES_H
#define GPIO_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "artery_at32f4xx.h"
#include "gpio_custom_const.h"

typedef union {
    uint8_t byte;
    struct {
        uint8_t pin  : 4; /*0....15*/
        uint8_t port : 4; /*A B C D E F G H*/
    };
}Pad_t;

typedef struct {
    bool valid;
    Port_t port;
    crm_periph_clock_type clock_type;
#ifdef HAS_AT32F43X
    scfg_port_source_type port_source;/*System configuration controller*/
#else
    uint8_t port_source;/*System configuration controller*/
#endif
    gpio_type* GPIOx ;
}GpioInfo_t;


typedef struct {
    GpioPinFunction_t func;
    GpioApiMode_t mode;
    GpioDir_t dir;
   // GpioType_t type;
    GpioAt32F413OutIOFCy_t IOFCy;
    GpioAt32F413_IOMCy_t IOMCy;
}GpioAt32F413ModeInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* GPIO_CUSTOM_TYPES_H  */
