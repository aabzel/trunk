#ifndef MIK32_HAL_SCR1_TIMER_TYPES_H
#define MIK32_HAL_SCR1_TIMER_TYPES_H

#include "mik32_hal_scr1_timer_const.h"

#include "scr1_timer.h"

typedef struct
{
    SCR1_TIMER_TypeDef *Instance;       /* Р вЂ�Р В°Р В·Р С•Р Р†РЎвЂ№Р в„– Р В°Р Т‘РЎР‚Р ВµРЎРѓ РЎР‚Р ВµР С–Р С‘РЎРѓРЎвЂљРЎР‚Р С•Р Р† SCR1_TIMER */

    uint8_t ClockSource;    /* Р пїЅРЎРѓРЎвЂљР С•РЎвЂЎР Р…Р С‘Р С” РЎвЂљР В°Р С”РЎвЂљР С‘РЎР‚Р С•Р Р†Р В°Р Р…Р С‘РЎРЏ */
    uint16_t Divider;       /* Р вЂќР ВµР В»Р С‘РЎвЂљР ВµР В»РЎРЉ РЎвЂЎР В°РЎРѓРЎвЂљР С•РЎвЂљРЎвЂ№ 10-Р В±Р С‘РЎвЂљР Р…Р С•Р Вµ РЎвЂЎР С‘РЎРѓР В»Р С• */
    
} SCR1_TIMER_HandleTypeDef;


#endif

