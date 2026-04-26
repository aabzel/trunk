#ifndef TIMER_CONST_H
#define TIMER_CONST_H

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif

//#include "microcontroller_const.h"

#include "timer_dep.h"

typedef enum {
    TIMER_POLARITY_LOW = 1,
    TIMER_POLARITY_HIGH = 2,
    TIMER_POLARITY_UNDEF = 0,
} TimerPolarity_t;

typedef enum {
    TIMER_ROLE_MASTER = 1,
    TIMER_ROLE_SLAVE = 2,
    TIMER_ROLE_SINGLE  = 3,
    TIMER_ROLE_UNDEF = 0,
} TimerRole_t;


typedef enum {
    TIMER_SLAVE_IN_TRIG_INTERNAL_TRIGGER_0  = 1,
    TIMER_SLAVE_IN_TRIG_INTERNAL_TRIGGER_1  = 2,
    TIMER_SLAVE_IN_TRIG_INTERNAL_TRIGGER_2  = 3,
    TIMER_SLAVE_IN_TRIG_INTERNAL_TRIGGER_3  = 4,
    TIMER_SLAVE_IN_TRIG_TI1_EDGE_DETECTOR  = 5,
    TIMER_SLAVE_IN_TRIG_FILTERED_TIMER_INPUT_1 = 6,
    TIMER_SLAVE_IN_TRIG_FILTERED_TIMER_INPUT_2 = 7,
    TIMER_SLAVE_IN_TRIG_FILTERED_EXTERNAL_TRIGGER_INPUT = 8,
    TIMER_SLAVE_IN_TRIG_NO_TRIGGER_SELECTED = 9,
    TIMER_SLAVE_IN_TRIG_UNDEF = 0,
} TimerSlaveInTrigger_t;

typedef enum {
    TIMER_SLAVE_TRIGGER_POLARITY_INVERTED     = 1,   /* Polarity for ETRx trigger sources             */
    TIMER_SLAVE_TRIGGER_POLARITY_NONINVERTED  = 2,   /* Polarity for ETRx trigger sources             */
    TIMER_SLAVE_TRIGGER_POLARITY_RISING       = 3,   /* Polarity for TIxFPx or TI1_ED trigger sources */
    TIMER_SLAVE_TRIGGER_POLARITY_FALLING      = 4,   /* Polarity for TIxFPx or TI1_ED trigger sources */
    TIMER_SLAVE_TRIGGER_POLARITY_BOTHEDGE     = 5,   /* Polarity for TIxFPx or TI1_ED trigger sources */
    TIMER_SLAVE_TRIGGER_POLARITY_UNDEF = 0,
}TimerSlaveTriggerPolarity_t;

typedef enum {
    TIMER_SLAVE_MODE_DISABLE = 1,

/*100: Reset Mode - Rising edge of the selected trigger input (TRGI) reinitializes the counter
and generates an update of the registers.*/
    TIMER_SLAVE_MODE_RESET = 2,

/*
101: Gated Mode - The counter clock is enabled when the trigger input (TRGI) is high.
The counter stops (but is not reset) as soon as the trigger becomes low.
Both start and stop of the counter are controlled. */
    TIMER_SLAVE_MODE_GATED = 3,

/*110: Trigger Mode - The counter starts at a rising edge of the trigger TRGI (but it is not
reset). Only the start of the counter is controlled.*/
    TIMER_SLAVE_MODE_TRIGGER = 4,

    /**/
    TIMER_SLAVE_MODE_EXTERNAL1 = 5,

    /**/
    TIMER_SLAVE_MODE_UNDEF = 0,
} TimerSlaveMode_t;

//#define TIMER_CLOCK_HZ SYS_FREQ
//#define TIMER_CLOCK_HZ 16000000

typedef enum {
    TIMER_CNT_DIR_DOWN = 1,
    TIMER_CNT_DIR_UP = 2,
    TIMER_CNT_DIR_UP_DOWN = 3,
    TIMER_CNT_DIR_UNDEF = 0,
} TimerDir_t;

typedef enum {
    TIMER_MASTER_OUT_TRG_RESET    = 1, /*   TIMx_EGR.UG bit is used as trigger output (TRGO)              */
    TIMER_MASTER_OUT_TRG_ENABLE   = 2, /*   TIMx_CR1.CEN bit is used as trigger output (TRGO)             */
    TIMER_MASTER_OUT_TRG_UPDATE   = 3, /*   Update event is used as trigger output (TRGO)                 */
    TIMER_MASTER_OUT_TRG_OC1      = 4, /*   Capture or a compare match 1 is used as trigger output (TRGO) */
    TIMER_MASTER_OUT_TRG_OC1REF   = 5, /*   OC1REF signal is used as trigger output (TRGO)                */
    TIMER_MASTER_OUT_TRG_OC2REF   = 6, /*   OC2REF signal is used as trigger output(TRGO)                 */
    TIMER_MASTER_OUT_TRG_OC3REF   = 7, /*   OC3REF signal is used as trigger output(TRGO)                 */
    TIMER_MASTER_OUT_TRG_OC4REF   = 8, /*   OC4REF signal is used as trigger output(TRGO)                 */
    TIMER_MASTER_OUT_TRG_UNDEF    = 0, /*   OC4REF signal is used as trigger output(TRGO)                 */
} TimerMasterOutTrigger_t;



typedef enum {
    TIMER_OUT_CHANNEL_0 = 0,
    TIMER_OUT_CHANNEL_1 = 1,
    TIMER_OUT_CHANNEL_2 = 2,
    TIMER_OUT_CHANNEL_3 = 3,
    TIMER_OUT_CHANNEL_4 = 4,
    TIMER_OUT_CHANNEL_5 = 5,
    TIMER_OUT_CHANNEL_ALL = 6,
    TIMER_OUT_CHANNEL_UNDEF = 7,
} TimerOutChannel_t;

#endif /* TIMER_CONST_H */
