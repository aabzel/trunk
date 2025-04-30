#include "stm32f415rg.h"

#include <stdint.h>

#include "data_utils.h"
#include "gpio_types.h"
#include "gpio_mcal.h"
#include "gpio_custom_const.h"

#ifdef HAS_PINS
const PinData_t PinConfig[] = {
   {.mcu_pin=1,   .pad.port=PORT_UNDEF, .pad.pin=0,     .name="Vbat", },
   {.mcu_pin=2,   .pad.port=PORT_C,     .pad.pin=13,    .name="", },
   {.mcu_pin=3,   .pad.port=PORT_C,     .pad.pin=14,    .name="OSC32_IN", },
   {.mcu_pin=4,   .pad.port=PORT_C,     .pad.pin=15,    .name="OSC32_OUT", },
   {.mcu_pin=5,   .pad.port=PORT_H,     .pad.pin=0,     .name="OSC_IN", },
   {.mcu_pin=6,   .pad.port=PORT_H,     .pad.pin=1,     .name="OSC_OUT", },
   {.mcu_pin=7,   .pad.port=PORT_UNDEF, .pad.pin=0,     .name="NRST", },
   {.mcu_pin=8,   .pad.port=PORT_C,     .pad.pin=0,     .name="", },
   {.mcu_pin=9,   .pad.port=PORT_C,     .pad.pin=1,     .name="", },
   {.mcu_pin=10,  .pad.port=PORT_C,     .pad.pin=2,     .name="", },
   {.mcu_pin=11,  .pad.port=PORT_C,     .pad.pin=3,     .name="", },
   {.mcu_pin=12,  .pad.port=PORT_UNDEF, .pad.pin=0,     .name="VSS", },
   {.mcu_pin=13,  .pad.port=PORT_UNDEF, .pad.pin=0,     .name="VDD", },
   {.mcu_pin=14,  .pad.port=PORT_A,     .pad.pin=0,     .name="", },
   {.mcu_pin=15,  .pad.port=PORT_A,     .pad.pin=1,     .name="", },
   {.mcu_pin=16,  .pad.port=PORT_A,     .pad.pin=2,     .name="", },
   {.mcu_pin=17,  .pad.port=PORT_A,     .pad.pin=3,     .name="", },
   {.mcu_pin=18,  .pad.port=PORT_UNDEF, .pad.pin=0,     .name="VSS", },
   {.mcu_pin=19,  .pad.port=PORT_UNDEF, .pad.pin=0,     .name="VDD", },
   {.mcu_pin=20,  .pad.port=PORT_A,     .pad.pin=4,     .name="", },
   {.mcu_pin=21,  .pad.port=PORT_A,     .pad.pin=4,     .name="", },
   {.mcu_pin=22,  .pad.port=PORT_A,     .pad.pin=6,     .name="", },
   {.mcu_pin=23,  .pad.port=PORT_A,     .pad.pin=7,     .name="", },
   {.mcu_pin=24,  .pad.port=PORT_C,     .pad.pin=4,     .name="", },
   {.mcu_pin=25,  .pad.port=PORT_C,     .pad.pin=5,     .name="", },
   {.mcu_pin=26,  .pad.port=PORT_B,     .pad.pin=0,     .name="BOOT1",  },
   {.mcu_pin=27,  .pad.port=PORT_B,     .pad.pin=1,     .name="",  },
   {.mcu_pin=28,  .pad.port=PORT_B,     .pad.pin=2,     .name="",  },
   {.mcu_pin=29,  .pad.port=PORT_B,     .pad.pin=10,    .name="",  },
   {.mcu_pin=30,  .pad.port=PORT_B,     .pad.pin=11,    .name="",  },
   {.mcu_pin=31,  .pad.port=PORT_UNDEF, .pad.pin=0,     .name="Vcap",  },
   {.mcu_pin=32,  .pad.port=PORT_UNDEF, .pad.pin=0,     .name="Vdd",  },
   {.mcu_pin=33,  .pad.port=PORT_B,     .pad.pin=12,    .name="",  },
   {.mcu_pin=34,  .pad.port=PORT_B,     .pad.pin=13,    .name="",  },
   {.mcu_pin=35,  .pad.port=PORT_B,     .pad.pin=14,    .name="",  },
   {.mcu_pin=36,  .pad.port=PORT_B,     .pad.pin=15,    .name="",  },
   {.mcu_pin=37,  .pad.port=PORT_C,     .pad.pin=6,     .name="",  },
   {.mcu_pin=38,  .pad.port=PORT_C,     .pad.pin=7,     .name="",  },
   {.mcu_pin=39,  .pad.port=PORT_C,     .pad.pin=8,     .name="",  },
   {.mcu_pin=40,  .pad.port=PORT_C,     .pad.pin=9,     .name="",  },
   {.mcu_pin=41,  .pad.port=PORT_A,     .pad.pin=8,     .name="",  },
   {.mcu_pin=42,  .pad.port=PORT_A,     .pad.pin=9,     .name="",  },
   {.mcu_pin=43,  .pad.port=PORT_A,     .pad.pin=10,    .name="",  },
   {.mcu_pin=44,  .pad.port=PORT_A,     .pad.pin=11,    .name="",  },
   {.mcu_pin=45,  .pad.port=PORT_A,     .pad.pin=12,    .name="",  },
   {.mcu_pin=46,  .pad.port=PORT_A,     .pad.pin=13,    .name="SWDIO",  },
   {.mcu_pin=47,  .pad.port=PORT_UNDEF, .pad.pin=0,     .name="Vcap",  },
   {.mcu_pin=48,  .pad.port=PORT_UNDEF, .pad.pin=0,     .name="Vdd",  },
   {.mcu_pin=49,  .pad.port=PORT_A,     .pad.pin=14,    .name="SWCLK",  },
   {.mcu_pin=50,  .pad.port=PORT_A,     .pad.pin=15,    .name="JTDI",  },
   {.mcu_pin=51,  .pad.port=PORT_C,     .pad.pin=10,    .name="",  },
   {.mcu_pin=52,  .pad.port=PORT_C,     .pad.pin=11,    .name="",  },
   {.mcu_pin=53,  .pad.port=PORT_C,     .pad.pin=12,    .name="",  },
   {.mcu_pin=54,  .pad.port=PORT_D,     .pad.pin=2,     .name="",  },
   {.mcu_pin=55,  .pad.port=PORT_B,     .pad.pin=3,     .name="JTDO",  },
   {.mcu_pin=56,  .pad.port=PORT_B,     .pad.pin=4,     .name="",  },
   {.mcu_pin=57,  .pad.port=PORT_B,     .pad.pin=5,     .name="",  },
   {.mcu_pin=58,  .pad.port=PORT_B,     .pad.pin=6,     .name="",  },
   {.mcu_pin=59,  .pad.port=PORT_B,     .pad.pin=7,     .name="",  },
   {.mcu_pin=60,  .pad.port=PORT_UNDEF, .pad.pin=0,     .name="BOOT0",  },
   {.mcu_pin=61,  .pad.port=PORT_B,     .pad.pin=8,     .name="",  },
   {.mcu_pin=62,  .pad.port=PORT_B,     .pad.pin=9,     .name="",  },
   {.mcu_pin=63,  .pad.port=PORT_UNDEF, .pad.pin=0,     .name="Vss",  },
   {.mcu_pin=64,  .pad.port=PORT_UNDEF, .pad.pin=0,     .name="Vdd",  },
 };
#endif

#ifdef HAS_PINS
uint16_t pin_get_cnt(void) {
    uint16_t cnt = 0;
    cnt = ARRAY_SIZE(PinConfig);
    return cnt;
}
#endif

bool mcu_init(void){
	bool res = true;
	return res;
}
