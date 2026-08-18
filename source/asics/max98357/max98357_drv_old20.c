#include "max98357_drv.h"

#include <stdint.h>
#include <string.h>

#include "bit_const.h"
#include "clocks.h"
#include "log.h"
#ifdef HAS_I2S
#include "test_i2s.h"
#endif
#include "max98357_const.h"
#include "max98357_config.h"


bool max98357_init(void) {
    bool res = true;
    LOG_INFO(MAX98357,"Init"),
    set_log_level(MAX98357, LOG_LEVEL_DEBUG);

#ifdef HAS_I2S
    res = test_i2s_play_freq(MAX98357_I2S_NUM,(double)1000.0, (SampleType_t)20000, 20000);
#endif
    set_log_level(MAX98357, LOG_LEVEL_INFO);

    return res;
}
