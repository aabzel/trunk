#include "pwm_diag.h"

#include <stdio.h>

#include "gpio_diag.h"
#include "log.h"

const char* PwmConfig2Str(const PwmConfig_t* const Config) {
    char text[80] = "";
    if(Config) {
        snprintf(text, sizeof(text), "Freq:%f Hz, Phase %u us, Duty %f %%, Ch:%u, Pad0:%s", Config->frequency_hz,
                 Config->phase_us, Config->duty, Config->Channel, GpioPadToStr(Config->pad[0]));
    }
    return text;
}

bool PwmDiagConfig(const PwmConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(PWM, "%s", PwmConfig2Str(Config));
        res = true;
    }
    return res;
}
