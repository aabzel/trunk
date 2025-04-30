#include "test_fir.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef HAS_PC
#include "win_utils.h"
#endif

#include "log.h"
#ifdef HAS_CSV
#include "csv.h"

#define TEST_FILE_NAME "OutFileTwoSignals.csv"
#endif
#include "fir.h"
#include "time_mcal.h"
#include "unit_test_check.h"
#include "utils_math.h"

#define TEXT_SIGNAL_LEN 100
#define SAMPLE_PERIOD_US SEC_2_USEC(0.02)
#define TEST_DUTY_CYCLE 10.0
#define TEST_FREQ_HZ 0.1

bool test_fir_proc(void) {
    LOG_INFO(FIR, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(FIR, LOG_LEVEL_DEBUG);
    uint32_t i = 0;
    FirSample_t x[TEXT_SIGNAL_LEN];
    FirSample_t y[TEXT_SIGNAL_LEN];

    for(i = 0; i < TEXT_SIGNAL_LEN; i++) {
        x[i] = calc_pwm_sample(SAMPLE_PERIOD_US * i, TEST_FREQ_HZ, 0.0, 10, TEST_DUTY_CYCLE, 0);
        ASSERT_TRUE(fir_proc_in_out(1, x[i], &y[i]));
    }
#ifdef HAS_PC
    ASSERT_TRUE(csv_save_two_double(TEST_FILE_NAME, TEXT_SIGNAL_LEN, (double*)x, (double*)y));
    // ASSERT_TRUE( win_cmd_run("python Plot2.py"TEST_FILE_NAME));
#endif

    set_log_level(FIR, LOG_LEVEL_INFO);
    return res;
}

bool test_fir_types(void) {
    bool res = true;
    LOG_INFO(FIR, "%s():", __FUNCTION__);
    set_log_level(FIR, LOG_LEVEL_DEBUG);
    set_log_level(FIR, LOG_LEVEL_INFO);
    return res;
}

bool test_fir_impulse_response(void) {
    bool res = true;
    LOG_INFO(FIR, "%s():", __FUNCTION__);
    set_log_level(FIR, LOG_LEVEL_DEBUG);

    uint32_t i = 0;
    FirSample_t x[TEXT_SIGNAL_LEN];
    memset(x, 0, sizeof(x));
    FirSample_t y[TEXT_SIGNAL_LEN];
    x[TEXT_SIGNAL_LEN / 4] = 1.0;

    for(i = 0; i < TEXT_SIGNAL_LEN; i++) {
        ASSERT_TRUE(fir_proc_in_out(1, x[i], &y[i]));
    }
#ifdef HAS_PC
#ifdef HAS_CSV
    ASSERT_TRUE(csv_save_two_double(TEST_FILE_NAME, TEXT_SIGNAL_LEN, (double*)x, (double*)y));
    ASSERT_TRUE(win_cmd_run("start python Plot2.py " TEST_FILE_NAME));
#endif
#endif

    set_log_level(FIR, LOG_LEVEL_INFO);
    return res;
}

static bool test_fir_performance_one(uint8_t num, uint32_t sample_rate_hz, uint32_t sample_cnt) {
    bool res = true;
    cli_printf(CRLF);
    LOG_INFO(FIR, "%s():FIR:%u,SamFreq:%u Hz,Sam:%u", __FUNCTION__, num, sample_rate_hz, sample_cnt);

    uint32_t i = 0;

    FirSample_t x = 1.0;
    FirSample_t y = 0.0;

    uint64_t time_start_us = time_get_us();
    for(i = 0; i < sample_cnt; i++) {
        ASSERT_TRUE(fir_proc_in_out(num, x, &y));
    }

    uint64_t time_end_us = time_get_us();
    double sample_time_s = 1.0 / ((double)sample_rate_hz);
    double total_duratuin_us = ((double)time_end_us) - ((double)time_start_us);
    double real_sample_total_duratuin_us = ((double)total_duratuin_us) / ((double)sample_cnt);
    uint64_t allowable_sample_time_us = SEC_2_USEC(sample_time_s);
    LOG_INFO(FIR, "duratuin:%f us", total_duratuin_us);
    LOG_INFO(FIR, "SampleTime:%f s", sample_time_s);
    LOG_INFO(FIR, "SamplePtocAllowTime:%llu us", allowable_sample_time_us);
    LOG_INFO(FIR, "SamplePtocRealTime:%f us", real_sample_total_duratuin_us);
    ASSERT_GR(real_sample_total_duratuin_us, allowable_sample_time_us);

    return res;
}

bool test_fir_performance(void) {
    bool res = true;
    LOG_INFO(FIR, "%s():", __FUNCTION__);

    ASSERT_TRUE(test_fir_performance_one(1, 48000, 4096));
    ASSERT_TRUE(test_fir_performance_one(2, 48000, 4096));

    return res;
}
