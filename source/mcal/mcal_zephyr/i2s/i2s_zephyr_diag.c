#include "i2s_zephyr_diag.h"

#include "i2s_types.h"
#include "i2s_zephyr_drv.h"
#include "log.h"

#include <stdint.h>
#include <zephyr/drivers/i2s.h>

bool i2s_diag(uint8_t i2s_num) {
    bool res = false;
    struct device* I2sDev = I2sNumToI2sDevPtr((I2sNum_t)i2s_num);
    if(I2sDev) {
        enum i2s_dir dir = I2S_DIR_TX;
        const struct i2s_config* config = i2s_config_get(I2sDev, dir);
        if(config) {
            LOG_INFO(I2S, "WordSize %u byte", config->word_size);
            LOG_INFO(I2S, "Channels %u", config->channels);
            LOG_INFO(I2S, "Format %u", config->format);
            LOG_INFO(I2S, "Options %u", config->options);
            LOG_INFO(I2S, "FrameClk_freq %u", config->frame_clk_freq);
            LOG_INFO(I2S, "BlockSize %u byte", config->block_size);
            LOG_INFO(I2S, "TimeOut %u ms", config->timeout);
            res = true;
        }
    }
    return res;
}
