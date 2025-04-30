#include "timer_custom_isr.h"

#include <stddef.h>

#ifdef HAS_PWM
#include "pwm_isr.h"
#endif /*HAS_PWM*/
#include "artery_at32f4xx.h"

bool ArteryTimerOverflowIRQHandler(uint8_t num) {
    bool res = false;
    //__disable_irq();
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(num);
    if(Node) {
        flag_status ret = RESET;
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_OVF_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_OVF_FLAG);
            res = TimerPeriodElapsedCallback(Node);
#ifdef HAS_PWM
            res = PwmPeriodElapsedCallback(num);
#endif /*HAS_PWM*/
        }

        /* flag channel 1 */
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_C1_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_C1_FLAG);
            Node->comparator++;
#ifdef HAS_PWM
            res = PwmPulseFinishedCallback(num, 1);
#endif /*HAS_PWM*/
        }

        /* flag channel 2 */
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_C2_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_C2_FLAG);
            Node->comparator++;
#ifdef HAS_PWM
            res = PwmPulseFinishedCallback(num, 2);
#endif /*HAS_PWM*/
        }

        /* flag channel 3 */
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_C3_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_C3_FLAG);
            Node->comparator++;
#ifdef HAS_PWM
            res = PwmPulseFinishedCallback(num, 3);
#endif /*HAS_PWM*/
        }

        /* flag channel 4 */
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_C4_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_C4_FLAG);
            Node->comparator++;
#ifdef HAS_PWM
            res = PwmPulseFinishedCallback(num, 4);
#endif /*HAS_PWM*/
        }

#ifdef HAS_AT32F43X
        /* flag channel 5 */
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_C5_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_C5_FLAG);
            Node->comparator++;
#ifdef HAS_PWM
            res = PwmPulseFinishedCallback(num, 5);
#endif /*HAS_PWM*/
        }
#endif // HAS_AT32F43X

        /* flag hall */
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_HALL_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_HALL_FLAG);
        }

        /* flag trigger */
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_TRIGGER_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_TRIGGER_FLAG);
        }

        /* flag brake */
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_BRK_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_BRK_FLAG);
        }

        /* flag channel 1 recapture */
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_C1_RECAPTURE_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_C1_RECAPTURE_FLAG);
        }

        /* flag channel 2 recapture */
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_C2_RECAPTURE_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_C2_RECAPTURE_FLAG);
        }

        /* flag channel 3 recapture */
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_C3_RECAPTURE_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_C3_RECAPTURE_FLAG);
        }

        /* flag channel 4 recapture */
        ret = tmr_interrupt_flag_get(Node->TMRx, TMR_C4_RECAPTURE_FLAG);
        if(SET == ret) {
            tmr_flag_clear(Node->TMRx, TMR_C4_RECAPTURE_FLAG);
        }
    }
    //__enable_irq();
    return res;
}
