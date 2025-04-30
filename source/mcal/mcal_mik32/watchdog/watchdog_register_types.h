#ifndef WATCHDOG_REGISTER_TYPES_H
#define WATCHDOG_REGISTER_TYPES_H

#include "std_includes.h"
#include "watchdog_custom_const.h"
#include "mik32_hal.h"


/*22.4.1 Key register (WATCHDOG_KR)*/
typedef union {
    uint8_t byte;
    struct{
    	uint8_t KEY;/*Key value*/
    };
}WatchDogRegKey_t;



/*22.4.3 Reload register (WATCHDOG_RLR)*/
typedef union {
    uint32_t dword;
    struct{
        uint32_t PRELOAD:12;  /* Initial value of the timer when starting or restarting*/
        uint32_t PRESCALE:3;  /* Input frequency divider (Fclk) for timer: */
        uint32_t RES:17;      /* */
    };
}WatchDogRegConfig_t;

/*Table 137 – STA Watchdog Timer Status Register Fields*/
typedef union {
    uint8_t byte;
    struct{
    	uint8_t TIMERENABLED:1;/*bit:0 Timer activity bit: */
        uint8_t TIMERLOADING:1;/*bit:1 Value Reload Bit*/
        uint8_t res:6;/*bit:7:2  Reserved*/
        uint8_t WATCHDOG_RST_FLAG:1;/*bit:8 Flag that indicates whether the watchdog timer has generated a reset.  */
    };
}WatchDogRegStatus_t;


typedef struct {
	uint8_t reserved1[131];
    volatile WatchDogRegConfig_t CON;  /*0x84=132....135 =*/
    uint8_t reserved2[21];
    union {
        volatile WatchDogRegKey_t KEY;     /*0x9C=156*/
        volatile WatchDogRegStatus_t STA;  /*0x9C=*/
    };
} __attribute__((__packed__)) WatchDogRegMap_t;





#endif /* WATCHDOG_REGISTER_TYPES_H  */
