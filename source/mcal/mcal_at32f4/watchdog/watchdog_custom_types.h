#ifndef WDT_TYPES_H
#define WDT_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "watchdog_custom_const.h"
#include "artery_at32f4xx.h"


typedef struct {
	wdt_division_type code;
	uint16_t divider;
}WdtDivisionInfo_t;


/*22.4.1 Key register (IWDG_KR)*/
typedef union {
    uint32_t qword;
    struct{
        uint16_t cmd;/*Key value*/
        uint16_t res;/*Reserved*/
    };
}WdtRegCmd_t;

/*22.4.2 Prescaler register (IWDG_PR)*/
typedef union {
    uint32_t qword;
    struct{
        uint32_t div:3;/*Prescaler divider*/
        uint32_t res:29;/*Reserved*/
    };
}WdtRegDiv_t;


/*22.4.3 Reload register (IWDG_RLR)*/
typedef union {
    uint32_t qword;
    struct{
        uint32_t rldf:12;/*Reload value*/
        uint32_t res:20;/*Reserved Kept at its default value*/
    };
}WdtRegRld_t;

/*22.4.4 Status register (IWDG_SR)*/
typedef union {
    uint32_t qword;
    struct{
        uint32_t divf:1;/*Division value update complete flag */
        uint32_t rldf:1;/*Reload value update complete flag*/
        uint32_t res:30;/*Reserved*/
    };
}WdtRegSts_t;

/*16.5.5 Window register (WDT_WIN)*/
typedef union {
    uint32_t qword;
    struct{
        uint32_t win:12;/*Window value */
        uint32_t res:20;/*Reserved*/
    };
}WdtRegWin_t;

//Table 16-2 WDT register and reset value
typedef struct {
    volatile WdtRegCmd_t Cmd;//0x00
    volatile WdtRegDiv_t Div;
    volatile WdtRegRld_t Rld;
    volatile WdtRegSts_t Sts;
    volatile WdtRegWin_t Win;
}WdtRegMap_t;

typedef struct  {
    bool is_on;
    uint32_t period_ms;
    volatile WdtRegMap_t* RegMapPtr;
} WatchDog_t;

#endif /* WDT_TYPES_H  */
