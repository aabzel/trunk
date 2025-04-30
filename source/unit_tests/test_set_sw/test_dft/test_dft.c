#include "test_dft.h"

#include <complex.h>

#include "complex_diag.h"
#include "data_utils.h"
#include "dft.h"
#include "dsp.h"
#include "float_utils.h"
#include "unit_test_check.h"
#ifdef HAS_DDS
#include "dds_drv.h"
#endif

#define DFT_SAMPLING_FREQUENCY_HZ 32000

#define SIGNAL_AMPLITUDE 1000.0

/*We are not allowed to set SignalFreq More than (SAMPLING_FREQUENCY_HZ /2)
 * See Nyquist–Shannon sampling theorem
 *  */
static bool test_dft_sine_one(double frequency_hz) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    DdsHandle_t* Node = DdsGetNode(DDS_DFT_TEST_NUM);
    ASSERT_NE(NULL, Node);
    double sampling_period_s = (1.0 / DFT_SAMPLING_FREQUENCY_HZ);
    ASSERT_TRUE(dds_set_fps(DDS_DFT_TEST_NUM, DFT_SAMPLING_FREQUENCY_HZ));
    ASSERT_TRUE(dds_set_sin(DDS_DFT_TEST_NUM, frequency_hz, SIGNAL_AMPLITUDE, 0.0, 0.0));
    ASSERT_TRUE(dds_set_array(DDS_DFT_TEST_NUM, 1, 0));
    ASSERT_TRUE(dds_print_track(DDS_DFT_TEST_NUM));
    double complex Spectrum[200] = {0};

    ASSERT_TRUE(
        dft_calc(Node->sample_array, Node->sample_cnt, (double complex* const) & Spectrum, sampling_period_s));

    ASSERT_TRUE(complex_array_print((const double complex* const) & Spectrum, Node->sample_cnt, sampling_period_s,
                                    Node->sample_cnt));

    Spectr_t maxFreq = {0};
    uint32_t g = ft_find_freq((double complex*)&Spectrum, Node->sample_cnt, sampling_period_s, &maxFreq);
    LOG_WARNING(TEST, "MaxGarmonic:%s", ComplexToStr(Spectrum[g]));
    LOG_WARNING(TEST, "CalcDone,SignalFreq:%s,OriginalSignalFreq:%f Hz", DftMaxFreqToStr(&maxFreq), frequency_hz);
    res = is_double_equal_absolute(frequency_hz, maxFreq.frequency_hz, 0.05 * frequency_hz);
    ASSERT_TRUE(res);
    return res;
}

bool test_dft_500(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = test_dft_sine_one(500.0);
    ASSERT_TRUE(res);
    return true;
}

bool test_dft_1000(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    bool res = test_dft_sine_one(1000.0);
    ASSERT_TRUE(res);
    return true;
}

bool test_dft_2000(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = test_dft_sine_one(2000.0);
    ASSERT_TRUE(res);
    return true;
}
