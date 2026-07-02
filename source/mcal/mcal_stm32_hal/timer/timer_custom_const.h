#ifndef TIMER_STM32_CONST_H
#define TIMER_STM32_CONST_H

#define TIMER_PRESCALER_MAX 0xFFFF

/*TIMx control register 1 (TIMx_CR1)
  Bit 0 CEN: Counter enable */
typedef enum {
    TIMER_CEN_COUNTER_DISABLED = 0, /* 0: Counter disabled  */
    TIMER_CEN_COUNTER_ENABLED = 1, /*  1: Counter enabled */
} Stm32TimerControl_t;

/*CCxP: Capture/Compare x output polarity  */
typedef enum {
    STM32_TIMER_OCX_ACTIVE_HIGH   = 0,   /*           0: OC1 active high */
    STM32_TIMER_OCX_ACTIVE_LOW    = 1,   /*           1: OC1 active low */
} Stm32TimerPolarity_t;


/**
 * @brief Capture/Compare 1 Selection enumeration (Bits 1:0 of TIMx_CCMR1)
 *
 * According to Reference Manual RM0090 (STM32F407xx)
 * These bits define the direction and selection of channel 1:
 * - In output mode: CC1S bits select the output direction (00 only)
 * - In input mode: CC1S bits select which input is connected to capture/compare channel 1
 */
typedef enum {
    /* Output Compare Mode */
    TIM_CC1S_OUTPUT_COMPARE         = 0x0,  /*!< 00: Channel configured as output.
                                             *   CC1 channel is used as output compare mode.
                                             *   This is the only valid value for output mode */

    /* Input Capture Modes */
    TIM_CC1S_INPUT_TI1              = 0x1,  /*!< 01: Channel configured as input.
                                             *   IC1 is mapped on TI1 (Timer Input 1).
                                             *   Input capture on channel 1 from TI1 pin */

    TIM_CC1S_INPUT_TI2              = 0x2,  /*!< 10: Channel configured as input.
                                             *   IC1 is mapped on TI2 (Timer Input 2).
                                             *   Input capture on channel 1 from TI2 pin */

    TIM_CC1S_INPUT_TRC              = 0x3   /*!< 11: Channel configured as input.
                                             *   IC1 is mapped on TRC (Timer Input from Internal Trigger).
                                             *   Input capture on channel 1 from TRC signal.
                                             *   Typically used for connecting multiple timers */
} Stm32TimerCaptureCompareSelection_t;



/**
 * @brief Output Compare 1 Mode enumeration (Bits 6:4 of TIMx_CCMR1)
 *
 * According to Reference Manual RM0090 (STM32F407xx)
 * These bits define the behavior of the output compare channel 1
 * when the counter matches the value in TIMx_CCR1 register
 */
typedef enum {
    /* Basic Output Compare Modes */
    TIM_OC1_MODE_FROZEN              = 0x0,  /*  000: Frozen - The comparison between the output compare
                                                  register TIMx_CCR1 and the counter TIMx_CNT has no
                                                  effect on the outputs.
                                                  (this mode is used to generate a timing base). */

    TIM_OC1_MODE_ACTIVE_ON_MATCH     = 0x1,  /*001: Set channel 1 to active level on match.
                                               OC1REF signal is forced high when the counter
                                               TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1). */

    TIM_OC1_MODE_INACTIVE_ON_MATCH   = 0x2,  /*010: Set channel 1 to inactive level on match.
                                               OC1REF signal is forced low when the
                                               counter TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1). */

    TIM_OC1_MODE_TOGGLE_ON_MATCH     = 0x3,  /*011: Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1. */

    /* Force Output Modes */
    TIM_OC1_MODE_FORCE_INACTIVE      = 0x4,  /*100: Force inactive level - OC1REF is forced low. */

    TIM_OC1_MODE_FORCE_ACTIVE        = 0x5,  /*101: Force active level - OC1REF is forced high */

    /* PWM Modes */
    TIM_OC1_MODE_PWM1                = 0x6,  /*110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1
                                               else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0’) as long as
                                               TIMx_CNT>TIMx_CCR1 else active (OC1REF=’1’). */

    TIM_OC1_MODE_PWM2                = 0x7   /*111: PWM mode 2 - In upcounting, channel 1 is inactive as long
                                               as TIMx_CNT<TIMx_CCR1  else active.
                                               In downcounting, channel 1 is active as long as  TIMx_CNT>TIMx_CCR1 else inactive. */
} Stm32TimerOutputCompareMode_t;





#endif /* TIMER_STM32_CONST_H  */
