#include "stm32f407vg.h"

#include <stdint.h>

#include "data_utils.h"
#include "gpio_types.h"
#include "gpio_mcal.h"
#include "interrupt_types.h"
#include "gpio_custom_const.h"

#ifdef HAS_PINS
const PinData_t PinConfig[] = {
   {.mcu_pin=1,   .pad.port=PORT_E,    .pad.pin=2,      .name="", },
   {.mcu_pin=2,   .pad.port=PORT_E,    .pad.pin=3,      .name="", },
   {.mcu_pin=3,   .pad.port=PORT_E,    .pad.pin=4,      .name="", },
   {.mcu_pin=4,   .pad.port=PORT_E,    .pad.pin=5,      .name="", },
   {.mcu_pin=5,   .pad.port=PORT_E,    .pad.pin=6,      .name="", },
   {.mcu_pin=6,   .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VBAT", },
   {.mcu_pin=7,   .pad.port=PORT_C,    .pad.pin=13,     .name="", },
   {.mcu_pin=8,   .pad.port=PORT_C,    .pad.pin=14,     .name="OSC32_IN", },
   {.mcu_pin=9,   .pad.port=PORT_C,    .pad.pin=15,     .name="OSC32_OUT", },
   {.mcu_pin=10,  .pad.port=PORT_F,    .pad.pin=0,      .name="", },
   {.mcu_pin=11,  .pad.port=PORT_F,    .pad.pin=1,      .name="", },
   {.mcu_pin=12,  .pad.port=PORT_F,    .pad.pin=2,      .name="", },
   {.mcu_pin=13,  .pad.port=PORT_F,    .pad.pin=3,      .name="", },
   {.mcu_pin=14,  .pad.port=PORT_F,    .pad.pin=4,      .name="", },
   {.mcu_pin=15,  .pad.port=PORT_F,    .pad.pin=5,      .name="", },
   {.mcu_pin=16,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VSS", },
   {.mcu_pin=17,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VDD", },
   {.mcu_pin=18,  .pad.port=PORT_F,    .pad.pin=6,      .name="", },
   {.mcu_pin=19,  .pad.port=PORT_F,    .pad.pin=7,      .name="", },
   {.mcu_pin=20,  .pad.port=PORT_F,    .pad.pin=8,      .name="", },
   {.mcu_pin=21,  .pad.port=PORT_F,    .pad.pin=9,      .name="", },
   {.mcu_pin=22,  .pad.port=PORT_F,    .pad.pin=10,     .name="", },
   {.mcu_pin=23,  .pad.port=PORT_H,    .pad.pin=0,      .name="OSC_IN", },
   {.mcu_pin=24,  .pad.port=PORT_H,    .pad.pin=1,      .name="OSC_OUT", },
   {.mcu_pin=25,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="NRST", },
   {.mcu_pin=26,  .pad.port=PORT_C,    .pad.pin=0,      .name="",  },
   {.mcu_pin=27,  .pad.port=PORT_C,    .pad.pin=1,      .name="",  },
   {.mcu_pin=28,  .pad.port=PORT_C,    .pad.pin=2,      .name="",  },
   {.mcu_pin=29,  .pad.port=PORT_C,    .pad.pin=3,      .name="",  },
   {.mcu_pin=30,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VDD",  },
   {.mcu_pin=31,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VSSA",  },
   {.mcu_pin=32,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VREF+",  },
   {.mcu_pin=33,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VDDA",  },
   {.mcu_pin=34,  .pad.port=PORT_A,    .pad.pin=0,      .name="",  },
   {.mcu_pin=35,  .pad.port=PORT_A,    .pad.pin=1,      .name="",  },
   {.mcu_pin=36,  .pad.port=PORT_A,    .pad.pin=2,      .name="",  },
   {.mcu_pin=37,  .pad.port=PORT_A,    .pad.pin=3,      .name="",  },
   {.mcu_pin=38,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VSS",  },
   {.mcu_pin=39,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VDD",  },
   {.mcu_pin=40,  .pad.port=PORT_A,    .pad.pin=4,      .name="",  },
   {.mcu_pin=41,  .pad.port=PORT_A,    .pad.pin=5,      .name="",  },
   {.mcu_pin=42,  .pad.port=PORT_A,    .pad.pin=6,      .name="",  },
   {.mcu_pin=43,  .pad.port=PORT_A,    .pad.pin=7,      .name="",  },
   {.mcu_pin=44,  .pad.port=PORT_C,    .pad.pin=4,      .name="",  },
   {.mcu_pin=45,  .pad.port=PORT_C,    .pad.pin=5,      .name="",  },
   {.mcu_pin=46,  .pad.port=PORT_B,    .pad.pin=0,      .name="",  },
   {.mcu_pin=47,  .pad.port=PORT_B,    .pad.pin=1,      .name="",  },
   {.mcu_pin=48,  .pad.port=PORT_B,    .pad.pin=2,      .name="",  },
   {.mcu_pin=49,  .pad.port=PORT_F,    .pad.pin=11,     .name="",  },
   {.mcu_pin=50,  .pad.port=PORT_F,    .pad.pin=12,     .name="",  },
   {.mcu_pin=51,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VSS",  },
   {.mcu_pin=52,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VDD",  },
   {.mcu_pin=53,  .pad.port=PORT_F,    .pad.pin=13,     .name="",  },
   {.mcu_pin=54,  .pad.port=PORT_F,    .pad.pin=14,     .name="",  },
   {.mcu_pin=55,  .pad.port=PORT_F,    .pad.pin=15,     .name="",  },
   {.mcu_pin=56,  .pad.port=PORT_G,    .pad.pin=0,      .name="",  },
   {.mcu_pin=57,  .pad.port=PORT_G,    .pad.pin=1,      .name="",  },
   {.mcu_pin=58,  .pad.port=PORT_E,    .pad.pin=7,      .name="",  },
   {.mcu_pin=59,  .pad.port=PORT_E,    .pad.pin=8,      .name="",  },
   {.mcu_pin=60,  .pad.port=PORT_E,    .pad.pin=9,      .name="",  },
   {.mcu_pin=61,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VSS",  },
   {.mcu_pin=62,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VDD",  },
   {.mcu_pin=63,  .pad.port=PORT_E,    .pad.pin=10,     .name="",  },
   {.mcu_pin=64,  .pad.port=PORT_E,    .pad.pin=11,     .name="",  },
   {.mcu_pin=65,  .pad.port=PORT_E,    .pad.pin=12,     .name="",  },
   {.mcu_pin=66,  .pad.port=PORT_E,    .pad.pin=13,     .name="",  },
   {.mcu_pin=67,  .pad.port=PORT_E,    .pad.pin=14,     .name="",  },
   {.mcu_pin=68,  .pad.port=PORT_E,    .pad.pin=15,     .name="",  },
   {.mcu_pin=69,  .pad.port=PORT_B,    .pad.pin=10,     .name="",  },
   {.mcu_pin=70,  .pad.port=PORT_B,    .pad.pin=11,     .name="",  },
   {.mcu_pin=71,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VCAP_1",  },
   {.mcu_pin=72,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VDD",  },
   {.mcu_pin=73,  .pad.port=PORT_B,    .pad.pin=12,     .name="",  },
   {.mcu_pin=74,  .pad.port=PORT_B,    .pad.pin=13,     .name="",  },
   {.mcu_pin=75,  .pad.port=PORT_B,    .pad.pin=14,     .name="",  },
   {.mcu_pin=76,  .pad.port=PORT_B,    .pad.pin=15,     .name="",  },
   {.mcu_pin=77,  .pad.port=PORT_D,    .pad.pin=8,      .name="",  },
   {.mcu_pin=78,  .pad.port=PORT_D,    .pad.pin=9,      .name="",  },
   {.mcu_pin=79,  .pad.port=PORT_D,    .pad.pin=10,     .name="",  },
   {.mcu_pin=80,  .pad.port=PORT_D,    .pad.pin=11,     .name="",  },
   {.mcu_pin=81,  .pad.port=PORT_D,    .pad.pin=12,     .name="",  },
   {.mcu_pin=82,  .pad.port=PORT_D,    .pad.pin=13,     .name="",  },
   {.mcu_pin=83,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VSS",  },
   {.mcu_pin=84,  .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VDD",  },
   {.mcu_pin=85,  .pad.port=PORT_D,    .pad.pin=14,     .name="",  },
   {.mcu_pin=86,  .pad.port=PORT_D,    .pad.pin=15,     .name="",  },
   {.mcu_pin=87,  .pad.port=PORT_G,    .pad.pin=2,      .name="",  },
   {.mcu_pin=88,  .pad.port=PORT_G,    .pad.pin=3,      .name="",  },
   {.mcu_pin=89,  .pad.port=PORT_G,    .pad.pin=4,      .name="",  },
   {.mcu_pin=90, .pad.port=PORT_G,     .pad.pin=5,      .name="",  },
   {.mcu_pin=91, .pad.port=PORT_G,     .pad.pin=6,      .name="",  },
   {.mcu_pin=92, .pad.port=PORT_G,     .pad.pin=7,      .name="",  },
   {.mcu_pin=93, .pad.port=PORT_G,     .pad.pin=8,      .name="",  },
   {.mcu_pin=94, .pad.port=PORT_UNDEF, .pad.pin=0,      .name="VSS",  },
   {.mcu_pin=95, .pad.port=PORT_UNDEF, .pad.pin=0,      .name="VDDUSB",  },
   {.mcu_pin=96, .pad.port=PORT_G,     .pad.pin=6,      .name="",  },
   {.mcu_pin=97, .pad.port=PORT_C,     .pad.pin=7,      .name="",  },
   {.mcu_pin=98, .pad.port=PORT_C,     .pad.pin=8,      .name="",  },
   {.mcu_pin=99, .pad.port=PORT_C,     .pad.pin=9,      .name="",  },
   {.mcu_pin=100, .pad.port=PORT_A,    .pad.pin=8,      .name="",  },
   {.mcu_pin=101, .pad.port=PORT_A,    .pad.pin=9,      .name="",  },
   {.mcu_pin=102, .pad.port=PORT_A,    .pad.pin=10,     .name="",  },
   {.mcu_pin=103, .pad.port=PORT_A,    .pad.pin=11,     .name="",  },
   {.mcu_pin=104, .pad.port=PORT_A,    .pad.pin=12,     .name="",  },
   {.mcu_pin=105, .pad.port=PORT_A,    .pad.pin=13,     .name="",  },
   {.mcu_pin=106, .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VCAP_2",  },
   {.mcu_pin=107, .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VSS",  },
   {.mcu_pin=108, .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VDD",  },
   {.mcu_pin=109, .pad.port=PORT_A,    .pad.pin=14,     .name="",  },
   {.mcu_pin=110, .pad.port=PORT_A,    .pad.pin=15,     .name="",  },
   {.mcu_pin=111, .pad.port=PORT_C,    .pad.pin=10,     .name="",  },
   {.mcu_pin=112, .pad.port=PORT_C,    .pad.pin=11,     .name="",  },
   {.mcu_pin=113, .pad.port=PORT_C,    .pad.pin=12,     .name="",  },
   {.mcu_pin=114, .pad.port=PORT_D,    .pad.pin=0,      .name="",  },
   {.mcu_pin=115, .pad.port=PORT_D,    .pad.pin=1,      .name="",  },
   {.mcu_pin=116, .pad.port=PORT_D,    .pad.pin=2,      .name="",  },
   {.mcu_pin=117, .pad.port=PORT_D,    .pad.pin=3,      .name="",  },
   {.mcu_pin=118, .pad.port=PORT_D,    .pad.pin=4,      .name="",  },
   {.mcu_pin=119, .pad.port=PORT_D,    .pad.pin=5,      .name="",  },
   {.mcu_pin=120, .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VSS",  },
   {.mcu_pin=121, .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VDD",  },
   {.mcu_pin=122, .pad.port=PORT_D,    .pad.pin=6,      .name="",  },
   {.mcu_pin=123, .pad.port=PORT_D,    .pad.pin=7,      .name="",  },
   {.mcu_pin=124, .pad.port=PORT_G,    .pad.pin=9,      .name="",  },
   {.mcu_pin=125, .pad.port=PORT_G,    .pad.pin=10,     .name="",  },
   {.mcu_pin=126, .pad.port=PORT_G,    .pad.pin=11,     .name="",  },
   {.mcu_pin=127, .pad.port=PORT_G,    .pad.pin=12,     .name="",  },
   {.mcu_pin=128, .pad.port=PORT_G,    .pad.pin=13,     .name="",  },
   {.mcu_pin=129, .pad.port=PORT_G,    .pad.pin=14,     .name="",  },
   {.mcu_pin=130, .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VSS",  },
   {.mcu_pin=131, .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VDD",  },
   {.mcu_pin=132, .pad.port=PORT_G,    .pad.pin=15,     .name="",  },
   {.mcu_pin=133, .pad.port=PORT_B,    .pad.pin=3,      .name="",  },
   {.mcu_pin=134, .pad.port=PORT_B,    .pad.pin=4,      .name="",  },
   {.mcu_pin=135, .pad.port=PORT_B,    .pad.pin=5,      .name="",  },
   {.mcu_pin=136, .pad.port=PORT_B,    .pad.pin=6,      .name="",  },
   {.mcu_pin=137, .pad.port=PORT_B,    .pad.pin=7,      .name="",  },
   {.mcu_pin=138, .pad.port=PORT_UNDEF,.pad.pin=0,      .name="BOOT0",  },
   {.mcu_pin=139, .pad.port=PORT_B,    .pad.pin=8,      .name="",  },
   {.mcu_pin=140, .pad.port=PORT_B,    .pad.pin=9,      .name="",  },
   {.mcu_pin=141, .pad.port=PORT_E,    .pad.pin=0,      .name="",  },
   {.mcu_pin=142, .pad.port=PORT_E,    .pad.pin=1,      .name="",  },
   {.mcu_pin=143, .pad.port=PORT_UNDEF,.pad.pin=0,      .name="PDR_ON",  },
   {.mcu_pin=144, .pad.port=PORT_UNDEF,.pad.pin=0,      .name="VDD",  },
};
#endif

#ifdef HAS_PINS
uint16_t pin_get_cnt(void) {
    uint16_t cnt = 0;
    cnt = ARRAY_SIZE(PinConfig);
    return cnt;
}
#endif


static const IntNumInfo_t InterruptsNameDiag[]={
};


const char* InterruptNumToStr(int16_t int_n) {
    const char* name = "?";
    uint32_t i = 0;
    for(i=0; i<ARRAY_SIZE(InterruptsNameDiag); i++) {
        if(int_n==InterruptsNameDiag[i].int_n){
            name=InterruptsNameDiag[i].name;
			break;
        }
    }
    return name;
}

bool mcu_init(void){
	bool res = true;
	return res;
}
