#include "clock_out_commands.h"

#include "clock_out_mcal.h"
#include "convert.h"
#include "log.h"

bool clock_out_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = clock_out_mcal_init();
    return res;
}

bool clock_out_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool clock_out_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    ClockOutChannel_t ch = 1;
    uint8_t freq_src = 0;
    uint8_t divider = 0;

    if(2 <= argc) {
        res = try_str2uint8(argv[0], &freq_src);
        if(res) {
            LOG_INFO(CLK, "ParseOk %u=%s", freq_src, ClockOutBusToStr(freq_src));
        } else {
            LOG_ERROR(CLK, "ParseErr %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[1], &divider);
        if(res) {
            LOG_INFO(CLK, "ParseDiv %u Ok", divider);
        } else {
            LOG_ERROR(CLK, "ParseErr %s", argv[2]);
        }
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[2], &ch);
        if(res) {
            LOG_INFO(CLK, "ParseOk CLOCK_OUT_%u", ch);
        } else {
            LOG_ERROR(CLK, "ParseErr %s", argv[0]);
        }
    }

    if(res) {
        switch(argc) {
        case 1: {
            uint32_t freq_hz = 0;
            res = clock_out_get(ch, (ClockOutBus_t)freq_src, &freq_hz);
            LOG_INFO(CLK, "Get,Src:%u,Freq:%u Hz", freq_src, freq_hz);
        } break;
        case 2: {
            res = clock_out_set(ch, (ClockOutBus_t)freq_src, divider);
        } break;
        case 3: {
            res = clock_out_set(ch, (ClockOutBus_t)freq_src, divider);

        } break;
        default: {

        } break;
        }
    } else {
        LOG_ERROR(CLK, "Usage: coc Freq Div Chan");
    }
    return res;
}
