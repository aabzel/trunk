#include "bt1026_config.h"

#include "bt1026_drv.h"
#include "bt1026_types.h"
#include "data_utils.h"

#if defined(HAS_BT1026_I2S_SLAVE) && defined(HAS_BT1026_I2S_MASTER)
#error "Config contradiction"
#endif

const Bt1026Config_t Bt1026Config = {
    .valid = true,
    .uart_num = 2,
    .i2s_num = 0,
    .sys_ctrl={ .port=2, .pin=2,}, /*DummyPin*/
    .reset={.port=0, .pin=27,},
#ifdef HAS_BT1026_I2S_SLAVE
    .i2s_role = I2SMODE_SLAVE,
#endif /*HAS_BT1026_I2S_SLAVE*/
#ifdef HAS_BT1026_I2S_MASTER
    .i2s_role = I2SMODE_MASTER,
#endif /*HAS_BT1026_I2S_MASTER*/
    .audio_freq = I2S_AUDIO_FREQ_48K,
    .digital_format = I2S_DATA_FORMAT_16B,
};

Bt1026Handle_t Bt1026Item = {
    .cur_line = "",
    .fix_line = "",
    .line_cnt = 0,
    .ok_cnt = 0,
    .pos = 0,
};
