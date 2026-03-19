#include "iomux_commands.h"

#include <stdint.h>
//#include <stdio.h>
//#include <string.h>

#include "log.h"
//#include "common_diag.h"
#include "convert.h"
//#include "data_utils.h"
#include "gpio_mcal.h"
#include "iomux_mcal.h"
#ifdef HAS_IOMUX_CUSTOM
//#include "iomux_custom_diag.h"
//#include "iomux_custom_drv.h"
#endif
//#include "microcontroller_const.h"

bool iomux_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = iomux_mcal_init();
        if(res) {
            LOG_INFO(IO_MUX, "InitOk");
        } else {
            LOG_ERROR(IO_MUX, "InitErr");
        }
    }
    return res;
}

bool iomux_mux_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t mux = 0;
    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &mux);
        if(false == res) {
            LOG_ERROR(IO_MUX, "ParseErr Mux %s", argv[2]);
        }
    }

    if(res) {
        switch(argc) {
        case 2: {
            res = iomux_pin_mux_get(pad, &mux);
            if(res) {
                LOG_INFO(IO_MUX, "Get,%s,Mux:%u", GpioPadToStr(pad), mux);
            }
        } break;
        case 3: {
            LOG_INFO(IO_MUX, "Set,%s,Mux:%u", GpioPadToStr(pad), mux);
            res = iomux_pin_mux_set(pad, mux);
        } break;
        }
    } else {
        LOG_ERROR(IO_MUX, "Usage: gm iomux_port iomux_pin mux");
    }
    return res;
}
