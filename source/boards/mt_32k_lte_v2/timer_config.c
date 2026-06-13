#include "timer_config.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif

#include "gpio_mcal.h"
#include "data_utils.h"

#ifdef HAS_DAC_CHANNEL
#include "dac_channel_mcal.h"
#endif

#ifdef HAS_LASER_SIGHT
#include "laser_sight_mcal.h"
#endif

#ifdef HAS_TIMER2
static bool timer2_overflov(void) {
    bool res = false ;
#ifdef HAS_DAC_CHANNEL
    Pad_t Pad = {.port = PORT_D,  .pin = 15, };
    res = gpio_toggle(Pad);
    DacChannelHandle_t* DacCh = DacChannelGetNodeV2(1, 1);
    if(DacCh) {
        res = dac_channel_proc_from_fifo(DacCh);
    }
#endif
    return res;
}
#endif

#ifdef HAS_TIMER3
static bool LaserTxNextBit(void){
    bool res = false;
#ifdef HAS_LASER_SIGHT
    LaserSightHandle_t* Node=LaserSightGetNode(1);
    if(Node) {
        if(0==    (    Node->carr_period_overflow%(Node->carrier_periods_per_chirp)   )   ){
            res = laser_sight_tx_bit_ll(Node);
        }
        Node->carr_period_overflow++;
    }
#endif
    return res;
}
#endif

#ifdef HAS_TIMER2
static bool timer2_comparator(void){
    bool res = false ;
    return res;
}
#endif

const TimerConfig_t TimerConfig[] = {
#ifdef HAS_TIMER3
    { .num = TIMER_NUM_LASER,
      .dir = TIMER_CNT_DIR_UP,
      .interrupt_on = true,
      .cnt_period_ns = 500,
      .period_s = (1.0f/250.0f),
      .name = "LaserCarruer",
      .ComparatorHandler = NULL,
      .PeriodDoneHandler = LaserTxNextBit,
      .valid = true,
      .on_off = true,
      .role = TIMER_ROLE_SINGLE,
      .master_out_trigger = TIMER_MASTER_OUT_TRG_RESET,
    },
#endif

#ifdef HAS_TIMER2
    { .num = TIMER_NUM_ADC1_TRIG,
      .period_s = 1.0f/1000.0f , /* T=1ms */
      /* 0.000125 s  8kHz  */
      .ComparatorHandler = timer2_comparator,
      .PeriodDoneHandler = timer2_overflov,
      .interrupt_on = false,
      .cnt_period_ns = 200,
      .name = "ADC1sam",
      .valid = true,
      .on_off = true,
      .dir = TIMER_CNT_DIR_UP,
      .role = TIMER_ROLE_MASTER,
      .master_out_trigger = TIMER_MASTER_OUT_TRG_UPDATE,
    },
#endif

#ifdef HAS_TIMER8
    { .num = TIMER_NUM_LO_BASE,
      .interrupt_on = false,
      .cnt_period_ns = 100,
      .period_s = 1.0f/1000.0f,
      .name = "LoBase",
      .valid = true,
      .ComparatorHandler = NULL,
      .PeriodDoneHandler = NULL,
      .on_off = true,
      .dir = TIMER_CNT_DIR_UP,
      .role = TIMER_ROLE_MASTER,
      .master_out_trigger = TIMER_MASTER_OUT_TRG_OC1,
    },
#endif

#ifdef HAS_TIMER4
    { .num = TIMER_NUM_LO,
      .slave_input_trigger = TIMER_SLAVE_IN_TRIG_INTERNAL_TRIGGER_3,
      .slave_mode = TIMER_SLAVE_MODE_RESET,//TIMER_SLAVE_MODE_GATED,// TIMER_SLAVE_MODE_RESET,//TIMER_SLAVE_MODE_TRIGGER,//TIMER_SLAVE_MODE_GATED,
      .role = TIMER_ROLE_SLAVE, //TIMER_ROLE_MASTER,//TIMER_ROLE_SLAVE,
      .dir = TIMER_CNT_DIR_UP,
      .interrupt_on = false,
      .cnt_period_ns = 100,
      .period_s = 1.0f/1000.0f,
      .ComparatorHandler = NULL,
      .PeriodDoneHandler = NULL,
      .name = "LO",
      .valid = true,
      .on_off = true,
      .slave_trigger_polarity = TIMER_SLAVE_TRIGGER_POLARITY_INVERTED, //TIMER_SLAVE_TRIGGER_POLARITY_RISING,//TIMER_SLAVE_TRIGGER_POLARITY_RISING  ,
      .slave_trigger_prescaler = 1,
      .slave_trigger_filter = 1,
    },
#endif

    { .num = TIMER_NUM_MS, .interrupt_on = true, .cnt_period_ns = 10000000, .period_s = 4294000.0,
      .name = "TimeStampMs", .valid = true, .on_off = true, .dir = TIMER_CNT_DIR_UP,
      .role=TIMER_ROLE_SINGLE,
      .ComparatorHandler = NULL,
      .PeriodDoneHandler = NULL,
      .master_out_trigger = TIMER_MASTER_OUT_TRG_RESET,
    },
};

TimerHandle_t TimerInstance[] = {
#ifdef HAS_TIMER2
        { .num = TIMER_NUM_ADC1_TRIG, .valid = true, },
#endif
        { .num = TIMER_NUM_MS, .valid = true, },
#ifdef HAS_TIMER3
        { .num = TIMER_NUM_LASER, .valid = true, },
#endif

#ifdef HAS_TIMER8
        { .num = TIMER_NUM_LO_BASE, .valid = true, },
#endif

#ifdef HAS_TIMER4
        { .num = TIMER_NUM_LO, .valid = true, },
#endif
};

COMPONENT_GET_CNT(Timer, timer)


