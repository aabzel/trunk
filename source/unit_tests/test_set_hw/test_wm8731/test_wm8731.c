#include "test_wm8731.h"

#include "unit_test_check.h"

#ifdef HAS_I2S
#include "i2s_drv.h"

#ifdef HAS_TEST_I2S
#include "test_i2s.h"
#endif /*HAS_TEST_I2S*/

#endif /*HAS_I2S*/

#include "none_blocking_pause.h"
#include "wm8731_config.h"
#include "wm8731_drv.h"

// 60 - too loudly
#define TEST_DAC_NUM 1
bool test_wm8731_play_freq(double freq, SampleType_t amplitude, uint32_t duration_ms) {
    LOG_INFO(TEST, CRLF CRLF "Wm8731Play Freq: %f Hz Amplitude: %u", freq, amplitude);
    bool res = true;
    // set_log_level(WM8731, LOG_LEVEL_DEBUG);

    ASSERT_GR(0, amplitude);
    ASSERT_GR(0, freq);
    ASSERT_GR(0, duration_ms);
    EXPECT_TRUE(wm8731_set_volume(5, 5));
#ifdef HAS_TEST_I2S
    ASSERT_TRUE(test_i2s_play_freq(Wm8731Config.i2s_num, freq, amplitude, duration_ms));
#else  /*HAS_TEST_I2S*/
    LOG_ERROR(TEST, "LackOfI2STestCode");
    res = false;
#endif /*HAS_I2S*/
    set_log_level(WM8731, LOG_LEVEL_INFO);
    return res;
}

bool test_wm8731_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(WM8731, LOG_LEVEL_DEBUG);
    bool res = true;
    ASSERT_EQ(1, sizeof(Wm8731RegLeftLineInCtrl_t));
    ASSERT_EQ(1, sizeof(Wm8731RegRightLineInCtrl_t));
    ASSERT_EQ(1, sizeof(Wm8731RegLeftHeadOutCtrl_t));
    ASSERT_EQ(1, sizeof(Wm8731RegRightHeadOutCtrl_t));
    ASSERT_EQ(1, sizeof(Wm8731RegAnalogAudioPathCtrl_t));
    ASSERT_EQ(1, sizeof(Wm8731RegDigitalAudioPathCtrl_t));
    ASSERT_EQ(1, sizeof(Wm8731RegPowerDownCtrl_t));
    ASSERT_EQ(1, sizeof(Wm8731RegDigitalAudioIfCtrl_t));
    ASSERT_EQ(1, sizeof(Wm8731RegSamplingCtrl_t));
    ASSERT_EQ(1, sizeof(Wm8731RegActiveCtrl_t));
    ASSERT_EQ(1, sizeof(Wm8731RegResetCtrl_t));

    ASSERT_EQ(1, sizeof(Wm8731RegGeneral_t));

    ASSERT_EQ(2, sizeof(Wm8731RegConfig_t));
    set_log_level(WM8731, LOG_LEVEL_INFO);
    return res;
}

bool test_wm8731_hashset(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(WM8731, LOG_LEVEL_DEBUG);
    bool res = true;

    ASSERT_EQ(0x00000A00, wm8731_pcm_2_32bit_sample(10));
    ASSERT_EQ(0xFFFFFE00, wm8731_pcm_2_32bit_sample(-2));
    ASSERT_EQ(0xFFFFFF00, wm8731_pcm_2_32bit_sample(-1));

    set_log_level(WM8731, LOG_LEVEL_INFO);
    return res;
}

bool test_wm8731_play(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(WM8731, LOG_LEVEL_DEBUG);
    bool res = true;
    ASSERT_TRUE(test_wm8731_play_freq(1000.0, 30000, 2000));
    ASSERT_TRUE(test_wm8731_play_freq(2000.0, 40000, 2000));
    ASSERT_TRUE(test_wm8731_play_freq(3000.0, 60000, 2000));
    set_log_level(WM8731, LOG_LEVEL_INFO);
    return res;
}

bool test_wm8731_set_vol(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    set_log_level(WM8731, LOG_LEVEL_DEBUG);
    set_log_level(I2C, LOG_LEVEL_DEBUG);
    ASSERT_EQ(0x7F, wm8731_vol_code(6));
    ASSERT_EQ(0x30, wm8731_vol_code(-73));

    ASSERT_TRUE(wm8731_set_volume(5, 5));
    ASSERT_TRUE(wm8731_set_volume(7, 7));     /*Overflow*/
    ASSERT_TRUE(wm8731_set_volume(-80, -80)); /*Underflow*/

    set_log_level(WM8731, LOG_LEVEL_INFO);
    set_log_level(I2C, LOG_LEVEL_INFO);
    return res;
}

bool test_wm8731_sidetone(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(WM8731, LOG_LEVEL_DEBUG);
    bool res = true;
    ASSERT_TRUE(wm8731_set_sidetone(true));
    ASSERT_TRUE(wait_in_loop_ms(4000));
    ASSERT_TRUE(wm8731_set_sidetone(false));
    set_log_level(WM8731, LOG_LEVEL_INFO);
    return res;
}

bool test_wm8731_reinit(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(WM8731, LOG_LEVEL_DEBUG);
    bool res = true;
    ASSERT_TRUE(wm8731_init());
    set_log_level(WM8731, LOG_LEVEL_INFO);
    return res;
}
