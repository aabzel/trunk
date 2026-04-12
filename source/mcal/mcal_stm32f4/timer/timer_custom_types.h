#ifndef TIMER_CUSTOM_TYPES_H
#define TIMER_CUSTOM_TYPES_H

#include "std_includes.h"
#include "stm32f4xx_hal.h"
#include "timer_custom_const.h"
#include "clock_types.h"
#include "clock_custom_const.h"
#include "gpio_types.h"



#define TIMER_CUSTOM_VARIABLES      \
    TIM_TypeDef* TIMx;              \
    TIM_HandleTypeDef Handle;


/*
18.4.7 TIMx capture/compare mode register 1 (TIMx_CCMR1)
  */
typedef union {
    uint8_t byte;
    struct {
        uint32_t CCxS: 2   ;  /* Bits 1:0 CCxS:  Capture/Compare 1 selection*/
        uint32_t OCxFE: 1  ;  /* Bit 2    OCxFE: Output compare 1 fast enable    */
        uint32_t OCxPE: 1  ;  /* Bit 3    OCxPE: Output compare 1 preload enable   */
        uint32_t OCxM: 3   ;  /* Bits 6:4 OCxM:  Output compare 1 mode   */
        uint32_t OCxCE: 1  ;  /* Bit 7    OCxCE: Output compare 1 clear enable   */
    };
} TimerRegCCMR_t;



/*
18.4.7 TIMx capture/compare mode register 1 (TIMx_CCMR1)
  */
typedef union {
    uint32_t dword;
    struct {
        TimerRegCCMR_t CH1;
        TimerRegCCMR_t CH2;
        uint32_t RES1: 16  ;          /*         */
    };
} TimerRegCCMR1_t;

/*
 TIMx capture/compare mode register 1 (TIMx_CCMR2)
  */
typedef union {
    uint32_t dword;
    struct {
        TimerRegCCMR_t CH3;
        TimerRegCCMR_t CH4;
        uint32_t RES1: 16  ;          /*         */
    };
} TimerRegCCMR2_t;




/* TIM1 and TIM8 control register 1 (TIMx_CR1)   */
typedef union {
    volatile uint32_t dword;  /*  */
    struct {
        volatile uint32_t CEN      : 1;  /*  Bit 0 CEN: Counter enable */
        volatile uint32_t UDIS     : 1;  /*  Bit 1 UDIS: Update disable */
        volatile uint32_t URS      : 1;  /*  Bit 2 URS: Update request source */
        volatile uint32_t OPM      : 1;  /*  Bit 3 OPM: One-pulse mode */
        volatile uint32_t DIR      : 1;  /*  Bit 4 DIR: Direction */
        volatile uint32_t CMS      : 2;  /*  Bits 6:5 CMS: Center-aligned mode selection */
        volatile uint32_t ARPE     : 1;  /*  Bit 7 ARPE: Auto-reload preload enable */
        volatile uint32_t CKD      : 2;  /*  Bits 9:8 CKD: Clock division */
        volatile uint32_t RES      : 22;  /* 31:10 Reserved bit  */
    } ;
}TimerRegCR1_t;



/**
 * @brief Union for TIMx_CCER (Capture/Compare Enable Register)
 * According to Reference Manual RM0090 (STM32F407xx)
 * Register offset: 0x20 from timer base address
 * This register controls the enable, polarity, and output state of capture/compare channels
 */
typedef union {
    volatile uint32_t dword;  /*!< Full register access */
    struct {
        /* Channel 1 Configuration (bits 0-3) */
        volatile uint32_t CC1E   : 1;  /*!< Bit 0:  Capture/Compare 1 output enable
                                        *         0: Capture/Compare channel 1 disabled
                                        *         1: Capture/Compare channel 1 enabled */

        volatile uint32_t CC1P   : 1;  /*!< Bit 1:  Capture/Compare 1 output polarity
                                        *         0: Active high (output mode) / Rising edge (input mode)
                                        *         1: Active low (output mode) / Falling edge (input mode) */

        volatile uint32_t CC1NE  : 1;  /*!< Bit 2:  Capture/Compare 1 complementary output enable
                                        *         (for advanced timers TIM1 and TIM8 only)
                                        *         0: Complementary output disabled
                                        *         1: Complementary output enabled */

        volatile uint32_t CC1NP  : 1;  /*!< Bit 3:  Capture/Compare 1 complementary output polarity
                                        *         (for advanced timers TIM1 and TIM8 only)
                                        *         0: Active high (output mode) / Rising edge (input mode)
                                        *         1: Active low (output mode) / Falling edge (input mode) */

        /* Channel 2 Configuration (bits 4-7) */
        volatile uint32_t CC2E   : 1;  /*!< Bit 4:  Capture/Compare 2 output enable */
        volatile uint32_t CC2P   : 1;  /*!< Bit 5:  Capture/Compare 2 output polarity */
        volatile uint32_t CC2NE  : 1;  /*!< Bit 6:  Capture/Compare 2 complementary output enable */
        volatile uint32_t CC2NP  : 1;  /*!< Bit 7:  Capture/Compare 2 complementary output polarity */

        /* Channel 3 Configuration (bits 8-11) */
        volatile uint32_t CC3E   : 1;  /*!< Bit 8:  Capture/Compare 3 output enable */
        volatile uint32_t CC3P   : 1;  /*!< Bit 9:  Capture/Compare 3 output polarity */
        volatile uint32_t CC3NE  : 1;  /*!< Bit 10: Capture/Compare 3 complementary output enable */
        volatile uint32_t CC3NP  : 1;  /*!< Bit 11: Capture/Compare 3 complementary output polarity */

        /* Channel 4 Configuration (bits 12-15) */
        volatile uint32_t CC4E   : 1;  /*!< Bit 12: Capture/Compare 4 output enable */
        volatile uint32_t CC4P   : 1;  /*!< Bit 13: Capture/Compare 4 output polarity */
        volatile uint32_t  RES1      : 1;  /*!< Bit 14: Reserved (CC4NE not available) */
        volatile uint32_t CC4NP  : 1;  /*!< Bit 15: Capture/Compare 4 complementary output polarity */

        /* Reserved bits 16-31 */
        volatile uint32_t  RES2      : 16; /*!< Bits 16-31: Reserved, must be kept at reset value */
    } ;
} TimerRegCCER_t;




typedef union {
    uint8_t byte;
    struct {
        uint8_t compare0 :1;
        uint8_t compare1 :1;
        uint8_t compare2 :1;
        uint8_t compare3 :1;
        uint8_t compare4 :1;
        uint8_t res :3;
    };
} TimerComparatorAvailability_t;

typedef struct {
    uint8_t num;
    uint8_t bitness;
    TIM_TypeDef* TIMx;
    ClockBus_t clock_bus;
    int32_t* irq_n;
    uint32_t irq_cnt;
    bool valid;
    TimerComparatorAvailability_t Comparators;
} TimerInfo_t;

#endif /* TIMER_CUSTOM_TYPES_H  */
