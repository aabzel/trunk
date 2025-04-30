#ifndef INTERRUPT_MCAL_H
#define INTERRUPT_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "interrupt_types.h"
#include "interrupt_config.h"

#ifdef HAS_INTERRUPT_DIAG
#include "interrupt_diag.h"
#endif

#ifndef CHECK_BIT_NUM
#define CHECK_BIT_NUM(VAL, BIT) ((1U << (BIT)) == ((VAL) & (1U << (BIT))))
#endif


const InterruptConfig_t* InterruptGetConfig(int16_t int_n);
uint32_t interrupt_get_isr_handler(int16_t irq_n);
bool interrupt_control(int16_t irq_n, bool on_off);
bool interrupt_control_all(bool on_off);
bool interrupt_set_priority(int16_t irq_n, uint8_t preempt_priority);
/*0-max prioruty 255-lowest proiryty*/
bool interrupt_get_priority(int16_t irq_n, uint8_t* const preempt_priority, uint8_t* const sub_priority);
bool interrupt_clear(void);
bool interrupt_is_valid_num(int16_t irq_n) ;
bool interrupt_is_active(int16_t irq_n);
bool interrupt_mcal_init(void);
bool interrupt_init_custom(void);
bool interrupt_enable(void);
bool interrupt_disable(void);
bool interrupt_is_valid_irq_num(int16_t irq_n);

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_MCAL_H  */
