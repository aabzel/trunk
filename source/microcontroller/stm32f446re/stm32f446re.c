#include "stm32f446re.h"

#include <stdint.h>

#include "data_utils.h"
#include "gpio_types.h"
#include "gpio_mcal.h"
#include "gpio_custom_const.h"

const PinData_t PinConfig[] = {
   {.mcu_pin=1,  .pad.port=PORT_UNDEF, .pad.pin=0,  .name="VBAT/VLCD", },
   {.mcu_pin=2,  .pad.port=PORT_C,     .pad.pin=13, .name="PC13", },
   {.mcu_pin=3,  .pad.port=PORT_C,     .pad.pin=14, .name="PC14", },
   {.mcu_pin=4,  .pad.port=PORT_C,     .pad.pin=15, .name="PC15", },
   {.mcu_pin=5,  .pad.port=PORT_F,     .pad.pin=0,  .name="PF0",  },
   {.mcu_pin=6,  .pad.port=PORT_F,     .pad.pin=1,  .name="PF1",  },
   {.mcu_pin=7,  .pad.port=PORT_UNDEF, .pad.pin=0,  .name="NRST", },
   {.mcu_pin=8,  .pad.port=PORT_C,     .pad.pin=0,  .name="PC0",  },
   {.mcu_pin=9,  .pad.port=PORT_C,     .pad.pin=1,  .name="PC1",  },
   {.mcu_pin=10, .pad.port=PORT_C,     .pad.pin=2,  .name="PC2",  },
   {.mcu_pin=11, .pad.port=PORT_C,     .pad.pin=3,  .name="PC3",  },
   {.mcu_pin=12, .pad.port=PORT_UNDEF, .pad.pin=0,  .name="AGND", },
   {.mcu_pin=13, .pad.port=PORT_UNDEF, .pad.pin=0,  .name="AVDD", },
   {.mcu_pin=14, .pad.port=PORT_A,     .pad.pin=0,  .name="PA0",  },
   {.mcu_pin=15, .pad.port=PORT_A,     .pad.pin=1,  .name="PA1",  },
   {.mcu_pin=16, .pad.port=PORT_A,     .pad.pin=2,  .name="PA2",  },
   {.mcu_pin=17, .pad.port=PORT_A,     .pad.pin=3,  .name="PA3",  },
   {.mcu_pin=18, .pad.port=PORT_UNDEF, .pad.pin=0,  .name="GND",  },
   {.mcu_pin=19, .pad.port=PORT_UNDEF, .pad.pin=0,  .name="VDD",  },
   {.mcu_pin=20, .pad.port=PORT_A,     .pad.pin=4,  .name="PA4",  },
   {.mcu_pin=21, .pad.port=PORT_A,     .pad.pin=5,  .name="PA5",  },
   {.mcu_pin=22, .pad.port=PORT_A,     .pad.pin=6,  .name="PA6",  },
   {.mcu_pin=23, .pad.port=PORT_A,     .pad.pin=7,  .name="PA7",  },
   {.mcu_pin=24, .pad.port=PORT_C,     .pad.pin=4,  .name="PC4",  },
   {.mcu_pin=25, .pad.port=PORT_C,     .pad.pin=5,  .name="PC5",  },
   {.mcu_pin=26, .pad.port=PORT_B,     .pad.pin=0,  .name="PB0",  },
   {.mcu_pin=27, .pad.port=PORT_B,     .pad.pin=1,  .name="PB1",  },
   {.mcu_pin=28, .pad.port=PORT_B,     .pad.pin=2,  .name="PB2",  },
   {.mcu_pin=29, .pad.port=PORT_B,     .pad.pin=10, .name="PB10", },
   {.mcu_pin=30, .pad.port=PORT_B,     .pad.pin=11, .name="PB11", },
   {.mcu_pin=31, .pad.port=PORT_UNDEF, .pad.pin=0,  .name="GND",  },
   {.mcu_pin=32, .pad.port=PORT_UNDEF, .pad.pin=0,  .name="VDD",  },
   {.mcu_pin=33, .pad.port=PORT_B,     .pad.pin=12, .name="PB12", },
   {.mcu_pin=34, .pad.port=PORT_B,     .pad.pin=14, .name="PB14", },
   {.mcu_pin=35, .pad.port=PORT_B,     .pad.pin=15, .name="PB15", },
   {.mcu_pin=36, .pad.port=PORT_D,     .pad.pin=8,  .name="PD8",  },
   {.mcu_pin=37, .pad.port=PORT_C,     .pad.pin=6,  .name="PC6",  },
   {.mcu_pin=38, .pad.port=PORT_C,     .pad.pin=7,  .name="PC7",  },
   {.mcu_pin=39, .pad.port=PORT_C,     .pad.pin=8,  .name="PC8",  },
   {.mcu_pin=40, .pad.port=PORT_C,     .pad.pin=9,  .name="PC9",  },
   {.mcu_pin=41, .pad.port=PORT_A,     .pad.pin=8,  .name="PA8",  },
   {.mcu_pin=42, .pad.port=PORT_A,     .pad.pin=9,  .name="PA9",  },
   {.mcu_pin=43, .pad.port=PORT_A,     .pad.pin=10, .name="PA10", },
   {.mcu_pin=44, .pad.port=PORT_A,     .pad.pin=11, .name="PA11", },
   {.mcu_pin=45, .pad.port=PORT_A,     .pad.pin=12, .name="PA12", },
   {.mcu_pin=46, .pad.port=PORT_A,     .pad.pin=13, .name="PA13", },
   {.mcu_pin=47, .pad.port=PORT_UNDEF, .pad.pin=0,  .name="GND",  },
   {.mcu_pin=48, .pad.port=PORT_UNDEF, .pad.pin=0,  .name="VDD",  },
   {.mcu_pin=49, .pad.port=PORT_A,     .pad.pin=14, .name="PA14", },
   {.mcu_pin=50, .pad.port=PORT_A,     .pad.pin=15, .name="PA15", },
   {.mcu_pin=51, .pad.port=PORT_C,     .pad.pin=10, .name="PC10", },
   {.mcu_pin=52, .pad.port=PORT_C,     .pad.pin=11, .name="PC11", },
   {.mcu_pin=53, .pad.port=PORT_C,     .pad.pin=12, .name="PC12", },
   {.mcu_pin=54, .pad.port=PORT_D,     .pad.pin=2,  .name="PD2",  },
   {.mcu_pin=55, .pad.port=PORT_B,     .pad.pin=3,  .name="PB3",  },
   {.mcu_pin=56, .pad.port=PORT_B,     .pad.pin=4,  .name="PB4",  },
   {.mcu_pin=57, .pad.port=PORT_B,     .pad.pin=5,  .name="PB5",  },
   {.mcu_pin=58, .pad.port=PORT_B,     .pad.pin=6,  .name="PB6",  },
   {.mcu_pin=59, .pad.port=PORT_B,     .pad.pin=7,  .name="PB7",  },
   {.mcu_pin=60, .pad.port=PORT_UNDEF, .pad.pin=0,  .name="BOOT0",},
   {.mcu_pin=61, .pad.port=PORT_B,     .pad.pin=8,  .name="PB8",  },
   {.mcu_pin=62, .pad.port=PORT_B,     .pad.pin=9,  .name="PB9",  },
   {.mcu_pin=63, .pad.port=PORT_UNDEF, .pad.pin=0,  .name="GND",  },
   {.mcu_pin=64, .pad.port=PORT_UNDEF, .pad.pin=0,  .name="VDD",  },
};

uint16_t pin_get_cnt(void) {
    uint16_t cnt = 0;
    cnt = ARRAY_SIZE(PinConfig);
    return cnt;
}

bool mcu_init(void){
	bool res = true;
	return res;
}

