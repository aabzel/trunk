#include "led_rgb_diag.h"

#include "led_general_const.h"

#if 0
const char* LedMode2Str(LedMode_t mode){
	const char* name="?";
	switch(mode){
        case LED_MODE_NONE: name="None"; break;
        case LED_MODE_PWM:  name="PWM";  break;
        case LED_MODE_ON:   name="On";   break;
        case LED_MODE_OFF:  name="Off";  break;
        case LED_MODE_BLINK:name="Blink";break;
    }
	return name;
}
#endif
