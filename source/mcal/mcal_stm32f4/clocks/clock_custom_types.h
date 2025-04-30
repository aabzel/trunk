#ifndef CLOCK_CUSTOM_TYPES_H
#define CLOCK_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "clock_custom_const.h"


#define CLOCK_CUSTOM_TYPES

//RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)
typedef union {
    uint32_t reg_val;
    struct{
        uint32_t gpioa :1;/*IO port A clock enable*/
        uint32_t gpiob :1;/*IO port B clock enable*/
        uint32_t gpioc :1;/*IO port C clock enable*/
        uint32_t gpiod :1;/*IO port D clock enable*/
        uint32_t gpioe :1;/*IO port E clock enable*/
        uint32_t gpiof :1;/*IO port F clock enable*/
        uint32_t gpiog :1;/*IO port G clock enable*/
        uint32_t gpioh :1;/*IO port H clock enable*/
        uint32_t res1  :4;/*Reserved,*/
        uint32_t crc :1;/*CRC clock enable*/
        uint32_t res2  :8;/*Reserved,*/
        uint32_t dma1:1;/*DMA1 clock enable*/
        uint32_t dma2:1;/*DMA2 clock enable*/
        uint32_t res3  :9;/*Reserved,*/
    };
}RccAhb1PeriphClkEnReg_t;


//RCC AHB2 peripheral clock enable register (RCC_AHB2ENR)
typedef union {
    uint32_t reg_val;
    struct{
        uint32_t res1  :6; /*Reserved,*/
        uint32_t rng   :1; /*RNG clock enable*/
        uint32_t otgfs :1; /*USB OTG FS clock enable*/
        uint32_t res2  :24;/*Reserved,*/
    };
}RccAhb2PeriphClkEnReg_t;



//RCC AHB3 peripheral clock enable register (RCC_AHB3ENR)
typedef union {
    uint32_t reg_val;
    struct{
        uint32_t fsmc   :1; /*Flexible memory controller module clock enable*/
        uint32_t qspi :1; /*QUADSPI memory controller module clock enable*/
        uint32_t res2  :30;/*Reserved,*/
    };
}RccAhb3PeriphClkEnReg_t;


//RCC APB1 peripheral clock enable register (RCC_APB1ENR)
typedef union {
    uint32_t reg_val;
    struct{
        uint32_t tim2   :1; /*TIM2 clock enable*/
        uint32_t tim3   :1; /*TIM3 clock enable*/
        uint32_t tim4   :1; /*TIM4 clock enable*/
        uint32_t tim5   :1; /*TIM5 clock enable*/
        uint32_t tim6   :1; /*TIM6 reset*/
        uint32_t tim7   :1; /*TIM7 reset*/
        uint32_t tim12   :1; /*TIM12 reset*/
        uint32_t tim13   :1; /*TIM13 reset*/
        uint32_t tim14   :1; /*TIM14 reset*/
        uint32_t lptimer1   :1; /*LPTimer 1 clock enable*/
        uint32_t rtcapb   :1; /*clock enable*/
        uint32_t wwdg   :1; /*Window watchdog clock enable*/
        uint32_t res1   :2; /*xxxxxxxxxxxxxxxx*/
        uint32_t spi2   :1; /*SPI2 clock enable*/
        uint32_t spi3   :1; /*SPI3 clock enable*/
        uint32_t res2   :1; /*xxxxxxxxxxxxxxxx*/
        uint32_t usart2   :1; /*USART2 clock enable*/
        uint32_t usart3   :1; /*USART3 clock enable*/
        uint32_t uart4   :1; /*UART 4 clock enable*/
        uint32_t uart5   :1; /*UART 5 clock enable*/
        uint32_t  i2c1   :1; /*I2C1 clock enable*/
        uint32_t i2c2   :1; /*I2C2 clock enable*/
        uint32_t i2c3   :1; /*I2C3 clock enable*/
        uint32_t i2cfmp1   :1; /*I2CFMP1 clock enable*/
        uint32_t can1   :1; /*CAN 1 clock enable*/
        uint32_t can2   :1; /*CAN 2 clock enable*/
        uint32_t can3   :1; /*CAN 3 clock enable*/
        uint32_t pwr   :1; /*Power interface clock enable*/
        uint32_t dac   :1; /*DAC clock enable*/
        uint32_t uart7   :1; /*UART7 clock enable*/
        uint32_t uart8   :1; /*UART8 clock enable*/
    };
}RccApb1PeriphClkEnReg_t;


//RCC APB2 peripheral clock enable register (RCC_APB2ENR)
typedef union {
    uint32_t reg_val;
    struct{
        uint32_t tim1   :1; /*TIM1 clock enable*/
        uint32_t tim8   :1; /*TIM8 clock enable*/
        uint32_t res1   :2; /*Reserved,*/
        uint32_t usart1   :1; /*USART1 clock enable*/
        uint32_t usart6   :1; /*USART6 clock enable*/
        uint32_t uart9   :1; /*UART9 clock enable*/
        uint32_t uart10   :1; /*UART10 clock enable*/
        uint32_t adc1   :1; /*ADC1 clock enable*/
        uint32_t res2   :2; /*res*/
        uint32_t sdio   :1; /*SDIO clock enable*/
        uint32_t spi1   :1; /*SPI1 clock enable*/
        uint32_t spi4   :1; /*SPI4 clock enable*/
        uint32_t syscfg   :1; /*System configuration controller clock enable*/
        uint32_t extit   :1; /*Extit Apb sysctrl pfree clock enable*/
        uint32_t tim9   :1; /*TIM9 clock enable*/
        uint32_t tim10   :1; /*TIM10 clock enable*/
        uint32_t tim11   :1; /*TIM11 clock enable*/
        uint32_t res3   :1; /*res*/
        uint32_t spi5   :1; /*SPI5 clock enable*/
        uint32_t res4   :1; /*Reserved,*/
        uint32_t sai1   :1; /*SAI 1 clock enable*/
        uint32_t res5   :1; /*Reserved,*/
        uint32_t dfsdm1   :1; /*DFSDM1 clock enable*/
        uint32_t dfsdm2   :1; /*DFSDM2 clock enable*/
        uint32_t res6   :6; /*Reserved,*/
    };
}RccApb2PeriphClkEnReg_t;



#ifdef __cplusplus
}
#endif

#endif // CLOCK_CUSTOM_TYPES_H
