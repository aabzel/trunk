#ifndef WATCHDOG_TYPES_H
#define WATCHDOG_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "iwdg_const.h"
#include "stm32f4xx_hal.h"


/*22.4.1 Key register (IWDG_KR)*/
typedef union uWdgRegKey_t{
    uint32_t reg_val;
    struct{
        uint16_t key;/*Key value*/
        uint16_t res;/*Reserved*/
    };
}iWdgRegKey_t;

/*22.4.2 Prescaler register (IWDG_PR)*/
typedef union uWdgRegPrescaler_t{
    uint32_t reg_val;
    struct{
        uint32_t pr:3;/*Prescaler divider*/
        uint32_t res:29;/*Reserved*/
    };
}iWdgRegPrescaler_t;


/*22.4.3 Reload register (IWDG_RLR)*/
typedef union uWdgRegReload_t{
    uint32_t reg_val;
    struct{
        uint32_t rl:12;/*Watchdog counter reload value*/
        uint32_t res:20;/*Reserved*/
    };
}iWdgRegReload_t;

/*22.4.4 Status register (IWDG_SR)*/
typedef union uWdgRegStatus_t{
    uint32_t reg_val;
    struct{
        uint32_t pvu:1;/*Watchdog counter reload value update*/
        uint32_t rvu:1;/*Watchdog prescaler value update*/
        uint32_t res:30;/*Reserved*/
    };
}iWdgRegStatus_t;

typedef struct xWdgRegMap_t{
    volatile iWdgRegKey_t Key;
    volatile iWdgRegPrescaler_t Prescaler;
    volatile iWdgRegReload_t Reload;
    volatile iWdgRegStatus_t Status;
}iWdgRegMap_t;

typedef struct xWatchDog_t {
    bool is_on;
    uint32_t period_ms;
    IWDG_HandleTypeDef hiwdg;
    volatile iWdgRegMap_t* RegMapPtr;
} WatchDog_t;

#endif /* WATCHDOG_TYPES_H  */
