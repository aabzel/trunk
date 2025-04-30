#include "at32f413rc.h"

#include <stdint.h>

#include "data_utils.h"
#include "log.h"
#include "gpio_types.h"
#include "gpio_mcal.h"
#include "clock.h"
#include "gpio_custom_const.h"
#include "microcontroller.h"

#ifdef HAS_PINS
const PinData_t PinConfig[] = {
   {.mcu_pin=1, .pad={.port=PORT_E, .pin=2}, .name="", },
   {.mcu_pin=2, .pad={.port=PORT_E, .pin=3}, .name="", },
   {.mcu_pin=3, .pad={.port=PORT_E, .pin=4}, .name="", },
   {.mcu_pin=4, .pad={.port=PORT_E, .pin=5}, .name="", },
   {.mcu_pin=5, .pad={.port=PORT_E, .pin=6}, .name="", },
   {.mcu_pin=7, .pad={.port=PORT_C, .pin=13}, .name="", },
   {.mcu_pin=8, .pad={.port=PORT_C, .pin=14}, .name="", },
   {.mcu_pin=9, .pad={.port=PORT_C, .pin=15}, .name="", },
   {.mcu_pin=10, .pad={.port=PORT_F, .pin=0}, .name="", },
   {.mcu_pin=11, .pad={.port=PORT_F, .pin=1}, .name="", },
   {.mcu_pin=12, .pad={.port=PORT_F, .pin=2}, .name="", },
   {.mcu_pin=13, .pad={.port=PORT_F, .pin=3}, .name="", },
   {.mcu_pin=14, .pad={.port=PORT_F, .pin=4}, .name="", },
   {.mcu_pin=15, .pad={.port=PORT_F, .pin=5}, .name="", },
   {.mcu_pin=18, .pad={.port=PORT_F, .pin=6}, .name="", },
   {.mcu_pin=19, .pad={.port=PORT_F, .pin=7}, .name="", },
   {.mcu_pin=20, .pad={.port=PORT_F, .pin=8}, .name="", },
   {.mcu_pin=21, .pad={.port=PORT_F, .pin=9}, .name="", },
   {.mcu_pin=22, .pad={.port=PORT_D, .pin=10}, .name="", },
   {.mcu_pin=23, .pad={.port=PORT_H, .pin=0}, .name="", },
   {.mcu_pin=24, .pad={.port=PORT_H, .pin=1}, .name="", },
   {.mcu_pin=25, .pad={.port=PORT_UNDEF, .pin=0}, .name="NRST", },
   {.mcu_pin=26, .pad={.port=PORT_C, .pin=0}, .name="", },
   {.mcu_pin=27, .pad={.port=PORT_C, .pin=1}, .name="", },
   {.mcu_pin=28, .pad={.port=PORT_C, .pin=2}, .name="", },
   {.mcu_pin=29, .pad={.port=PORT_C, .pin=3}, .name="", },
   {.mcu_pin=30, .pad={.port=PORT_UNDEF, .pin=0}, .name="NC", },
   {.mcu_pin=31, .pad={.port=PORT_UNDEF, .pin=0}, .name="VSSA", },
   {.mcu_pin=32, .pad={.port=PORT_UNDEF, .pin=0}, .name="VREF", },
   {.mcu_pin=33, .pad={.port=PORT_UNDEF, .pin=0}, .name="VDDA", },
   {.mcu_pin=34, .pad={.port=PORT_A, .pin=0}, .name="", },
   {.mcu_pin=35, .pad={.port=PORT_A, .pin=1}, .name="", },
   {.mcu_pin=36, .pad={.port=PORT_A, .pin=2}, .name="", },
   {.mcu_pin=37, .pad={.port=PORT_A, .pin=3}, .name="", },
   {.mcu_pin=38, .pad={.port=PORT_A, .pin=15}, .name="Vss", },
   {.mcu_pin=39, .pad={.port=PORT_A, .pin=15}, .name="Vdd", },
   {.mcu_pin=40, .pad={.port=PORT_A, .pin=4}, .name="", },
   {.mcu_pin=41, .pad={.port=PORT_A, .pin=5}, .name="", },
   {.mcu_pin=42, .pad={.port=PORT_A, .pin=6}, .name="", },
   {.mcu_pin=43, .pad={.port=PORT_A, .pin=7}, .name="", },
   {.mcu_pin=44, .pad={.port=PORT_C, .pin=4}, .name="", },
   {.mcu_pin=45, .pad={.port=PORT_C, .pin=5}, .name="", },
   {.mcu_pin=46, .pad={.port=PORT_B, .pin=0}, .name="", },
   {.mcu_pin=47, .pad={.port=PORT_B, .pin=1}, .name="", },
   {.mcu_pin=48, .pad={.port=PORT_B, .pin=2}, .name="", },
   {.mcu_pin=49, .pad={.port=PORT_F, .pin=11}, .name="", },
   {.mcu_pin=50, .pad={.port=PORT_F, .pin=12}, .name="", },
   {.mcu_pin=51, .pad={.port=PORT_UNDEF, .pin=0}, .name="Vss", },
   {.mcu_pin=52, .pad={.port=PORT_UNDEF, .pin=0}, .name="Vdd", },
   {.mcu_pin=53, .pad={.port=PORT_F, .pin=13}, .name="", },
   {.mcu_pin=54, .pad={.port=PORT_F, .pin=14}, .name="", },
   {.mcu_pin=55, .pad={.port=PORT_F, .pin=15}, .name="", },
   {.mcu_pin=56, .pad={.port=PORT_G, .pin=0}, .name="", },
   {.mcu_pin=57, .pad={.port=PORT_G, .pin=1}, .name="", },
   {.mcu_pin=58, .pad={.port=PORT_E, .pin=7}, .name="", },
   {.mcu_pin=59, .pad={.port=PORT_E, .pin=8}, .name="", },
   {.mcu_pin=60, .pad={.port=PORT_E, .pin=9}, .name="", },
   {.mcu_pin=61, .pad={.port=PORT_UNDEF, .pin=0}, .name="Vss", },
   {.mcu_pin=62, .pad={.port=PORT_UNDEF, .pin=0}, .name="Vdd", },
   {.mcu_pin=63, .pad={.port=PORT_E, .pin=10}, .name="", },
   {.mcu_pin=64, .pad={.port=PORT_E, .pin=11}, .name="", },
   {.mcu_pin=65, .pad={.port=PORT_E, .pin=12}, .name="", },
   {.mcu_pin=66, .pad={.port=PORT_E, .pin=13}, .name="", },
   {.mcu_pin=67, .pad={.port=PORT_E, .pin=14}, .name="", },
   {.mcu_pin=68, .pad={.port=PORT_E, .pin=15}, .name="", },
   {.mcu_pin=69, .pad={.port=PORT_B, .pin=10}, .name="", },
   {.mcu_pin=70, .pad={.port=PORT_B, .pin=11}, .name="", },
   {.mcu_pin=71, .pad={.port=PORT_H, .pin=3}, .name="", },
   {.mcu_pin=72, .pad={.port=PORT_UNDEF, .pin=0}, .name="Vdd", },
   {.mcu_pin=73, .pad={.port=PORT_B, .pin=12}, .name="", },
   {.mcu_pin=74, .pad={.port=PORT_B, .pin=13}, .name="", },
   {.mcu_pin=75, .pad={.port=PORT_B, .pin=14}, .name="", },
   {.mcu_pin=76, .pad={.port=PORT_B, .pin=15}, .name="", },
   {.mcu_pin=77, .pad={.port=PORT_B, .pin=8}, .name="", },
   {.mcu_pin=78, .pad={.port=PORT_D, .pin=9}, .name="", },
   {.mcu_pin=79, .pad={.port=PORT_D, .pin=10}, .name="", },
   {.mcu_pin=80, .pad={.port=PORT_D, .pin=11}, .name="", },
   {.mcu_pin=81, .pad={.port=PORT_D, .pin=12}, .name="", },
   {.mcu_pin=82, .pad={.port=PORT_D, .pin=13}, .name="", },
   {.mcu_pin=83, .pad={.port=PORT_UNDEF, .pin=0}, .name="Vss", },
   {.mcu_pin=84, .pad={.port=PORT_UNDEF, .pin=0}, .name="Vdd", },
   {.mcu_pin=85, .pad={.port=PORT_D, .pin=14}, .name="", },
};
#endif

#ifdef HAS_PINS
uint16_t pin_get_cnt(void) {
    uint16_t cnt = 0;
    cnt = ARRAY_SIZE(PinConfig);
    return cnt;
}
#endif

__attribute__((weak)) void SystemInit (void) {
#ifdef HAS_CMSIS

#if defined (__FPU_USED) && (__FPU_USED == 1U)
  SCB->CPACR |= ((3U << 10U * 2U) |         /* set cp10 full access */
                 (3U << 11U * 2U)  );       /* set cp11 full access */
#endif

#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE  | VECT_TAB_OFFSET;  /* vector table relocation in internal sram. */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET;  /* vector table relocation in internal flash. */
#endif

#endif
}


bool mcu_init(void) {
    bool res = true;
#ifdef HAS_MCU_UID
    res = mcu_uid_show();
#endif

    uint32_t core_freq = clock_core_freq_get();
    LOG_INFO(MICROCONTROLLER,"CPU:%u Hz",core_freq);
    return res;
}
