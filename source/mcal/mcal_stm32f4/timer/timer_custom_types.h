#ifndef TIMER_VENDOR_CUSTOM_TYPES_H
#define TIMER_VENDOR_CUSTOM_TYPES_H

#include "std_includes.h"
#include "stm32f4xx_hal.h"
#include "timer_custom_const.h"
#include "timer_types.h"
#include "clock_types.h"
#include "clock_custom_const.h"
#include "gpio_types.h"

#define TIMER_CUSTOM_VARIABLES     \
    TIM_HandleTypeDef Handle;      \
    TIM_TypeDef* TIMx;

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

#endif /* TIMER_VENDOR_CUSTOM_TYPES_H  */
