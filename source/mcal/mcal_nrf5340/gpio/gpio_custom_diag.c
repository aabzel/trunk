#include "gpio_custom_diag.h"

#include <stdint.h>

#include "nrf_gpio.h"

const char* McuSel2Str(nrf_gpio_pin_mcusel_t mcusel){
	const char* name = "?";
	switch(mcusel){
    case NRF_GPIO_PIN_MCUSEL_APP:name = "App"; break;
    case NRF_GPIO_PIN_MCUSEL_NETWORK: name = "Net";break;
    case NRF_GPIO_PIN_MCUSEL_TND: name = "Trace";break;
    }
    return name;
}

const char* PinCoreSel2Str(GpioPinMcuSel_t core_sel){
	const char* name = "?";
	switch((uint8_t)core_sel) {
        case NRF_GPIO_PIN_MUX_APP:name = "App"; break;
        case NRF_GPIO_PIN_MUX_NET: name = "Net";break;
        case NRF_GPIO_PIN_MUX_TRACE: name = "Trace";break;
    }
    return name;
}

const char* GpioPort2Str(uint8_t port){
	const char* name="";
	return name;
}

