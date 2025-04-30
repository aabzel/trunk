#include "timer_calc_commands.h"

#include "convert.h"
#include "log.h"
#include "num_to_str.h"
#include "timer_calc.h"
#include "timer_calc_diag.h"
/*
 * tca 100M 500 16
 * */
bool timer_calc_artery_command(int32_t argc, char* argv[]) {
    bool res = false;
    double freq_apb_hz = 100000000;
    double freq_signal_hz = 1000;
    uint8_t resolition_bit = 16;

    if(1 <= argc) {
        res = try_str2number(argv[0], &freq_apb_hz);
        if(false == res) {
            LOG_ERROR(TIMER_CALC, "ParseErr [%s]", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2number(argv[1], &freq_signal_hz);
        if(false == res) {
            LOG_ERROR(TIMER_CALC, "ParseErr [%s]", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &resolition_bit);
        if(false == res) {
            LOG_ERROR(TIMER_CALC, "ParseErr [%s]", argv[2]);
        }
    }

    if(res) {
        TimerArtety_t TimerArtety = {0};
        res = timer_calc_artery(freq_apb_hz, freq_signal_hz, resolition_bit, &TimerArtety);
        if(res) {
            LOG_INFO(TIMER_CALC, "%s", TimerArtetyToStr(&TimerArtety));
            double tick_s = ((double)TimerArtety.prescaler) / freq_apb_hz;
            LOG_INFO(TIMER_CALC, "TickTime:%s s", DoubleToStr(tick_s));
        } else {
            LOG_ERROR(TIMER_CALC, "NoValues");
        }
    } else {
        LOG_ERROR(TIMER_CALC, "Usage: tca ApbFreqHz SignalFreqHz bit");
    }
    return res;
}
