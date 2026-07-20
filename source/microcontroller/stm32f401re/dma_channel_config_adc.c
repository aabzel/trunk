#include "dma_channel_config_adc.h"

#include "data_utils.h"
#include "microcontroller_const.h"
#include "adc_mcal.h"
#include "gpio_mcal.h"

bool CallBackHalfAdc1(void) {
    bool res = false;
    Pad_t Pad = { .port = PORT_D, .pin = 13, };
    gpio_toggle(Pad);
    return res;
}

bool CallBackDoneAdc1(void) {
    bool res = false;
    Pad_t Pad = { .port = PORT_D, .pin = 11, };
    gpio_toggle(Pad);
    return res;
}





