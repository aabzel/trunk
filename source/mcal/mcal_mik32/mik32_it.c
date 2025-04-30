#include "mik32_it.h"

#include "mcal_common.h"
#include "mik32_hal_irq.h"
#ifdef HAS_LED
#include "led_drv.h"
#endif

uint32_t int_cnt = 0;

void trap_handler(void) {
    int_cnt++;
#ifdef HAS_INTERRUPT_EXT
    interrupt_control_all(false);
#endif

#ifdef HAS_LED_MONO
    //led_mono_toggle(2); // hang-un in optimisation
#endif

    bool res = false;
#ifdef HAS_UART
    res = uart_irq_proc();
#endif
    (void)res;
    HAL_EPIC_Clear(0xFFFFFFFF);
#ifdef HAS_INTERRUPT_EXT
    interrupt_control_all(true);
#endif
}
