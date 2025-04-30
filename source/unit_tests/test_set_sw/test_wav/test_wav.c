#include "test_wav.h"

#include <string.h>

#include "log.h"
#include "unit_test_check.h"
#include "utils_math.h"
#include "wav.h"

bool test_wav_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    set_log_level(WAV, LOG_LEVEL_DEBUG);

    ASSERT_EQ(44, sizeof(WavHeader_t));
    ASSERT_EQ(4, sizeof(WavSample16_t));

    set_log_level(WAV, LOG_LEVEL_INFO);
    return true;
}
