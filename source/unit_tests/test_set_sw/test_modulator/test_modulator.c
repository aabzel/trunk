#include "test_modulator.h"

#include <complex.h>

#include "modulator.h"
#include "data_utils.h"
#include "unit_test_check.h"
#include "dds_config.h"

#define SAMPLING_FREQUENCY_HZ 32000
/*We are not allowed to set SignalFreq More than (sampling freq /2) */
#define SIGNAL_AMPLITUDE 1000.0

bool test_modulator(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;

    Modulator_t Modulator;
//    Modulator.modulation;
    Modulator.sampling_frequency_hz = SAMPLING_FREQUENCY_HZ;
    Modulator.tone_duration_ms = 10.0;
    Modulator.freq_step_hz = 400.0;
    Modulator.amplitude = SIGNAL_AMPLITUDE;
    Modulator.dac_num = DAC_MODULATOR_NUM;
    uint8_t raw_data[8] = {0x91,0xA2,0xB3,0xC4,0xD5,0xE6,0xF7,0x08};

    EXPECT_TRUE(modulator_modulate(&Modulator, raw_data, 4) );

    return res;
}
