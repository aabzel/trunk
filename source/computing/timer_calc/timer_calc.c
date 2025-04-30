#include "timer_calc.h"

#include "float_utils.h"
#include "log.h"
#include "num_to_str.h"
#include "utils_math.h"

static double timer_calc_real_period_s(double bus_clock, uint32_t prescaler, uint32_t laod) {
    double calc_period_s = 0.0;
    double cpu_period = 1.0 / ((double)bus_clock);
    calc_period_s = cpu_period * ((double)((prescaler + 1U) * ((double)laod)));
    return calc_period_s;
}

static bool timer_calc_regs(double des_period_s, double bus_clock, uint32_t prescaler, uint32_t* out_load,
                            uint32_t max_val) {
    bool res = true;
    if(max_val) {
        LOG_PARN(TIMER_CALC, "Max:%u,", max_val);
        if(prescaler) {
            if(bus_clock) {
                LOG_DEBUG(TIMER_CALC, "Per:%s s,BusFreq:%u Hz,Psc %u", DoubleToStr(des_period_s), bus_clock, prescaler);

                uint32_t load = 0;
                double bus_period_s = 1.0 / ((double)bus_clock);
                double calc_period_s = 0.0;
                double tick_s = bus_period_s * ((double)prescaler);

                load = (uint32_t)(des_period_s / tick_s);
                if(max_val < load) {
                    LOG_ERROR(TIMER_CALC, "Max:%u,NotEnoughBitDepth:Need:%u", max_val, load);
                    res = false;
                } else {
                    res = true;
                }
                if(res) {
                    calc_period_s = timer_calc_real_period_s(bus_clock, prescaler, (uint32_t)load);
                    double err = bus_period_s * 10000.0;
                    res = is_double_equal_absolute(calc_period_s, des_period_s, err);
                    if(false == res) {
                        LOG_DEBUG(TIMER_CALC, "PeriodsDifferent des [%f] calc [%f] s Err[%f]", des_period_s,
                                  calc_period_s, err);
                        res = false;
                    } else {
                    }
                    res = true;
                    (*out_load) = (uint32_t)load;
                } else {
                    *out_load = 0xFFFF - 1;
                    res = false;
                }
            }
        }
    }

    return res;
}

bool timer_calc_artery(double base_freq_hz, double freq_sinal_hz, uint8_t resolution_bit, TimerArtety_t* const Node) {
    bool res = false;

    uint32_t period_max_val = (uint32_t)(ipow(2, (uint32_t)resolution_bit) - 1);
    LOG_INFO(TIMER_CALC, "FreqXtal:%f Hz,FreqSys:%f Hz, Resol:%u bit,MaxVal:%u", base_freq_hz, freq_sinal_hz,
             resolution_bit, period_max_val);

    uint32_t ok_cnt = 0;
    double bus_period_s = 1.0 / base_freq_hz;
    double des_period_s = 1.0 / freq_sinal_hz;
    LOG_INFO(TIMER_CALC, "ClockPeriod:%s s", DoubleToStr(bus_period_s));
    LOG_INFO(TIMER_CALC, "IsrPeriod:%s s", DoubleToStr(des_period_s));

    cli_printf(" [(%f Hz)/(%f Hz)] = PSC*PER" CRLF, base_freq_hz, freq_sinal_hz);
    if(Node) {
        int32_t prescaler = 0;
        for(prescaler = 0x00FFFF; 0 < prescaler; prescaler--) {
            uint32_t out_period = 0;
            res = timer_calc_regs(des_period_s, base_freq_hz, prescaler, &out_period, period_max_val);
            if(res) {
                Node->period = out_period;
                Node->prescaler = prescaler;
#if 0
                    double tick_s = ((double)(prescaler))/base_freq_hz;
                    cli_printf("PSC:%6u,PER:%6u,APB:%f Hz,SIGNAL:%f Hz,Tick:%s s" CRLF, prescaler, out_period,base_freq_hz,freq_sinal_hz, DoubleToStr(tick_s));
#endif
                res = true;
                ok_cnt++;
            }
        }
    }
    if(ok_cnt) {
        LOG_INFO(TIMER_CALC, "Spot %u Solutions for Timer Vals!", ok_cnt);
        res = true;
    } else {
        LOG_ERROR(TIMER_CALC, "NoTimerVals!");
        res = false;
    }
    return res;
}
