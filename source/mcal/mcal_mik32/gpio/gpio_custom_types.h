#ifndef GPIO_CUSTOM_TYPES_H
#define GPIO_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

//#include "mik32_hal.h"

#include "gpio.h"
#include "gpio_custom_const.h"

typedef union {
    uint8_t byte;
    struct {
        uint8_t pin  : 4; /*0....15*/
        uint8_t port : 4; /*A B C D E F G H*/
    };
}Pad_t;



typedef union {
    uint32_t dword;
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

// see Table 97 – Fields of the PADx_CFG registers for controlling the output function
typedef union {
    uint32_t dword;
    struct{
        uint32_t pin_mux_0 :2;
        uint32_t pin_mux_1 :2;
        uint32_t pin_mux_2 :2;
        uint32_t pin_mux_3 :2;
        uint32_t pin_mux_4 :2;
        uint32_t pin_mux_5 :2;
        uint32_t pin_mux_6 :2;
        uint32_t pin_mux_7 :2;
        uint32_t pin_mux_8 :2;
        uint32_t pin_mux_9 :2;
        uint32_t pin_mux_10 :2;
        uint32_t pin_mux_11 :2;
        uint32_t pin_mux_12 :2;
        uint32_t pin_mux_13 :2;
        uint32_t pin_mux_14 :2;
        uint32_t pin_mux_15 :2;
    };
}Mik32PinMuxRegCfg_t;

// see Table 98 – Fields of the PADx_DS registers for controlling the load capacity of the outputs
typedef union {
    uint32_t dword;
    struct{
        uint32_t ds_0 :2;
        uint32_t ds_1 :2;
        uint32_t ds_2 :2;
        uint32_t ds_3 :2;
        uint32_t ds_4 :2;
        uint32_t ds_5 :2;
        uint32_t ds_6 :2;
        uint32_t ds_7 :2;
        uint32_t ds_8 :2;
        uint32_t ds_9 :2;
        uint32_t ds_10 :2;
        uint32_t ds_11 :2;
        uint32_t ds_12 :2;
        uint32_t ds_13 :2;
        uint32_t ds_14 :2;
        uint32_t ds_15 :2;
    };
}Mik32PinMuxRegDrive_t;


// see Table 99 – Fields of the PADx_PUPD registers for pull-up resistor control
typedef union {
    uint32_t dword;
    struct{
        uint32_t pin_0 :2;
        uint32_t pin_1 :2;
        uint32_t pin_2 :2;
        uint32_t pin_3 :2;
        uint32_t pin_4 :2;
        uint32_t pin_5 :2;
        uint32_t pin_6 :2;
        uint32_t pin_7 :2;
        uint32_t pin_8 :2;
        uint32_t pin_9 :2;
        uint32_t pin_10 :2;
        uint32_t pin_11 :2;
        uint32_t pin_12 :2;
        uint32_t pin_13 :2;
        uint32_t pin_14 :2;
        uint32_t pin_15 :2;
    };
}Mik32PinMuxRegPull_t;

typedef struct {
    volatile Mik32PinMuxRegCfg_t PAD0_CFG;     /*  00 */
    volatile Mik32PinMuxRegDrive_t PAD0_DS;    /*  */
    volatile Mik32PinMuxRegPull_t PAD0_PUPD;    /*  */
    volatile Mik32PinMuxRegCfg_t PAD1_CFG;    /*  */
    volatile Mik32PinMuxRegDrive_t PAD1_DS;    /*  */
    volatile Mik32PinMuxRegPull_t PAD1_PUPD;    /*  */
    volatile Mik32PinMuxRegCfg_t PAD2_CFG;    /*  */
    volatile Mik32PinMuxRegDrive_t PAD2_DS;    /*  */
    volatile Mik32PinMuxRegPull_t PAD2_PUPD;    /*  */
} Mik32PinMux_t;

#ifdef __cplusplus
}
#endif

#endif /* GPIO_CUSTOM_TYPES_H  */
