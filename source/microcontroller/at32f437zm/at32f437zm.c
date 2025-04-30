#include "at32f437zm.h"

#include <stdint.h>

#include "data_utils.h"
#include "gpio_types.h"
#include "gpio_mcal.h"
#include "gpio_custom_const.h"

#ifdef HAS_PINS
const PinData_t PinConfig[] = {
//   {.mcu_pin=1,   .pad.port=PORT_E,    .pad.pin=2,      .name="", },
};
#endif

#ifdef HAS_PINS
uint16_t pin_get_cnt(void) {
    uint16_t cnt = 0;
    cnt = ARRAY_SIZE(PinConfig);
    return cnt;
}
#endif

__attribute__((weak))
void SystemInit (void){
#if defined (__FPU_USED) && (__FPU_USED == 1U)
  SCB->CPACR |= ((3U << 10U * 2U) |         /* set cp10 full access */
                 (3U << 11U * 2U)  );       /* set cp11 full access */
#endif

#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE  | VECT_TAB_OFFSET;  /* vector table relocation in internal sram. */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET;  /* vector table relocation in internal flash. */
#endif
}


bool mcu_init(void){
    bool res = true;
    return res;
}
