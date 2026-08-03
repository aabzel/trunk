#include "test_correlator_s16.h"

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

#include "array.h"
#include "correlator_naiv_s16.h"
#include "correlator_s16.h"
#include "time_mcal.h"
#include "trng_mcal.h"
#include "unit_test_check.h"
#include "utils_math.h"

#define TEXT_SIGNAL_LEN 100
#define SAMPLE_PERIOD_US SEC_2_USEC(0.02)
#define TEST_DUTY_CYCLE 10.0
#define TEST_FREQ_HZ 0.1

bool test_correlator_s16_proc(void) {
    LOG_INFO(CORRELATOR_S16, "%s():", __FUNCTION__);
    bool res = true;
    log_level_set(CORRELATOR_S16, LOG_LEVEL_DEBUG);
    uint32_t i = 0;
    int16_t x[TEXT_SIGNAL_LEN];
    int64_t y[TEXT_SIGNAL_LEN];

    for(i = 0; i < TEXT_SIGNAL_LEN; i++) {
        x[i] = calc_pwm_sample(SAMPLE_PERIOD_US * i, TEST_FREQ_HZ, 0.0, 10, TEST_DUTY_CYCLE, 0);
        ASSERT_TRUE(correlator_s16_proc_in_out(1, x[i], &y[i]));
    }
#ifdef HAS_PC
    ASSERT_TRUE(csv_save_two_double(TEST_FILE_NAME, TEXT_SIGNAL_LEN, (double*)x, (double*)y));
    // ASSERT_TRUE( win_cmd_run("python Plot2.py"TEST_FILE_NAME));
#endif

    log_level_set(CORRELATOR_S16, LOG_LEVEL_INFO);
    return res;
}

bool test_correlator_s16_types(void) {
    bool res = true;
    LOG_INFO(CORRELATOR_S16, "%s():", __FUNCTION__);
    return res;
}

static bool test_correlator_s16_performance_one(uint8_t num, uint32_t sample_rate_hz, uint32_t sample_cnt) {
    bool res = true;
    cli_printf(CRLF);
    LOG_INFO(CORRELATOR_S16, "%s():CORRELATOR_S16:%u,SamFreq:%u Hz,Sam:%u", __FUNCTION__, num, sample_rate_hz,
             sample_cnt);

    uint32_t i = 0;

    int16_t x = 1.0;
    int64_t y = 0;

    uint64_t time_start_us = time_get_us();
    for(i = 0; i < sample_cnt; i++) {
        ASSERT_TRUE(correlator_s16_proc_in_out(num, x, &y));
    }

    uint64_t time_end_us = time_get_us();
    double sample_time_s = 1.0 / ((double)sample_rate_hz);
    double total_duratuin_us = ((double)time_end_us) - ((double)time_start_us);
    double real_sample_total_duratuin_us = ((double)total_duratuin_us) / ((double)sample_cnt);
    uint64_t allowable_sample_time_us = SEC_2_USEC(sample_time_s);
    LOG_INFO(CORRELATOR_S16, "duratuin:%f us", total_duratuin_us);
    LOG_INFO(CORRELATOR_S16, "SampleTime:%f s", sample_time_s);
    LOG_INFO(CORRELATOR_S16, "SamplePtocAllowTime:%llu us", allowable_sample_time_us);
    LOG_INFO(CORRELATOR_S16, "SamplePtocRealTime:%f us", real_sample_total_duratuin_us);
    ASSERT_GR(real_sample_total_duratuin_us, allowable_sample_time_us);

    return res;
}

bool test_correlator_s16_performance(void) {
    bool res = true;
    LOG_INFO(CORRELATOR_S16, "%s():", __FUNCTION__);

    ASSERT_TRUE(test_correlator_s16_performance_one(1, 48000, 4096));
    ASSERT_TRUE(test_correlator_s16_performance_one(2, 48000, 4096));

    return res;
}

#define CORR_S16_NUM 0
bool test_correlator_s16_equal(void) {
    bool res = true;
    uint32_t i = 0;

    uint16_t reference_signal[1000] = {0};
    res = array_u16_rand(reference_signal, ARRAY_SIZE(reference_signal), -1000, 1000);
    ASSERT_TRUE(res);

    res = correlator_s16_write_ref_signal(CORR_S16_NUM, reference_signal, ARRAY_SIZE(reference_signal));
    ASSERT_TRUE(res);

    res = correlator_naiv_s16_write_ref_signal(CORR_S16_NUM, reference_signal, ARRAY_SIZE(reference_signal));
    ASSERT_TRUE(res);

    for(i = 0; i < 1000; i++) {
        int16_t sample = 0;
        res = trng_get_word(&sample);
        ASSERT_TRUE(res);
        int64_t fast = correlator_s16_proc_in_out_short(CORR_S16_NUM, sample);
        int64_t slow = correlator_naiv_s16_proc_in_out_short(CORR_S16_NUM, sample);
        ASSERT_EQ(slow, fast);
    }
    return res;
}
