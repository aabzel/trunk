#ifndef GPIO_CUSTOM_TYPES_H
#define GPIO_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "stm32fx_hal.h"
#include "gpio_custom_const.h"
#include "gpio_const.h"

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
    volatile uint32_t dword;
    struct{
        uint32_t AFR_LH_0_8 :4;
        uint32_t AFR_LH_1_9 :4;
        uint32_t AFR_LH_2_10 :4;
        uint32_t AFR_LH_3_11 :4;
        uint32_t AFR_LH_4_12 :4;
        uint32_t AFR_LH_5_13 :4;
        uint32_t AFR_LH_6_14 :4;
        uint32_t AFR_LH_7_15 :4;
    };
}GpioRegAFR_LH_t;

/*GPIO alternate function low register (GPIOx_AFRL) (x = A..I/J/K)*/
typedef union {
    volatile uint32_t dword;
    struct{
        uint32_t AFRL0 :4;
        uint32_t AFRL1 :4;
        uint32_t AFRL2 :4;
        uint32_t AFRL3 :4;
        uint32_t AFRL4 :4;
        uint32_t AFRL5 :4;
        uint32_t AFRL6 :4;
        uint32_t AFRL7 :4;
    };
}GpioRegAFRL_t;


/*8.4.10 GPIO alternate function high register (GPIOx_AFRH)(x = A..I/J)*/
typedef union {
    volatile uint32_t dword;
    struct{
        uint32_t AFRH8 :4;
        uint32_t AFRH9 :4;
        uint32_t AFRH10 :4;
        uint32_t AFRH11 :4;
        uint32_t AFRH12 :4;
        uint32_t AFRH13 :4;
        uint32_t AFRH14 :4;
        uint32_t AFRH15 :4;
    };
}GpioRegAFRH_t;



typedef union {
    volatile uint32_t dword;
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


/*8.4.1 GPIO port mode register (GPIOx_MODER) (x = A..I/J/K)*/
typedef union {
    volatile uint32_t dword;
    struct {
        volatile uint32_t pin0_mode :2;   /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin1_mode :2;   /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin2_mode :2;   /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin3_mode :2;   /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin4_mode :2;   /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin5_mode :2;   /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin6_mode :2;   /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin7_mode :2;   /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin8_mode :2;   /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin9_mode :2;   /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin10_mode :2;  /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin11_mode :2;  /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin12_mode :2;  /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin13_mode :2;  /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin14_mode :2;  /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
        volatile uint32_t pin15_mode :2;  /* Bits 2y:2y+1MODERy[1:0]: Port x configuration bits (y = 0..15) */
    };
}GpioRegMODE_t;


typedef struct {
    bool valid;
    GpioPort_t port;
    volatile GPIO_TypeDef* GPIOx;
}GpioPortInfo_t;



#ifdef __cplusplus
}
#endif

#endif /* GPIO_CUSTOM_TYPES_H  */
