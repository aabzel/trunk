#include "iomux_diag.h"

#include <stdio.h>
#include <string.h>

#include "gpio_diag.h"
#include "log.h"

const char* IoMuxConfToStr(const IoMuxConfig_t* Config) {
    static char name[120];
    if(Config) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%s%s,", name, GpioPadToStr(Config->pad));
        snprintf(name, sizeof(name), "%s%s,", name, Config->function);
        snprintf(name, sizeof(name), "%sMux:%u,", name, Config->mux);
    }
    return name;
}

bool IoMuxConfigDiag(const IoMuxConfig_t* const Config) {
    bool res = false;
    LOG_WARNING(IO_MUX, "%s", IoMuxConfToStr(Config));
    return res;
}
