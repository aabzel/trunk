#ifndef SOFTWARE_TIMER_H
#define SOFTWARE_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "software_timer_isr.h"
#include "software_timer_types.h"
#include "sw_timer_config.h"

#ifndef HAS_TIMER
#warning "+HAS_TIMER"
#endif /*HAS_TIMER*/

bool sw_timer_add_new(uint32_t period_s);
bool sw_timer_init(void);
bool sw_timer_set_handler(uint32_t sw_tim_num, uint32_t handler_address);
bool sw_timer_ctrl(uint32_t sw_tim_num, uint32_t period, uint32_t phase, SwTimerMode_t mode, SwTimerCntDir_t dir,
                   bool on_off);

bool sw_timer_poll(void);
bool sw_timer_fast_ctrl(uint32_t sw_tim_num, bool on_off);
const SoftwareTimerConfig_t* SwTimerGetConfigNode(uint8_t sw_tim_num);
uint32_t sw_timer_get_spare(void);
SoftwareTimer_t* SwTimerGetNode(uint8_t sw_tim_num);

#ifdef __cplusplus
}
#endif

#endif /* SOFTWARE_TIMER_H */
