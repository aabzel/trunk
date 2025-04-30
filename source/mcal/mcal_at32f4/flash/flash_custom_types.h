#ifndef FLASH_AT32_TYPES_H
#define FLASH_AT32_TYPES_H


#include "std_includes.h"
#include "flash_custom_const.h"
#include "clock_const.h"
//#include "at32f435_437.h"
#include "mcal_types.h"


typedef struct {
    uint8_t num;
    bool valid;
    volatile struct flash_type* FLASHx;
    ClockBus_t clockBus;
    uint32_t clockType;
    Reg32_t* RegArray;
    uint32_t regCnt;
    int16_t irqNn; // IRQn_Type
}FlashInfo_t;


#define FLASH_CUSTOM_TYPES                     \
    volatile struct flash_type* FLASHx;



#endif /* FLASH_AT32_TYPES_H  */
