#include "bc127_config.h"

#include "bc127_types.h"
#include "bc127_drv.h"
#include "data_utils.h"

const Bc127Config_t Bc127ConfigLut={
                                 .digital_rate = 32000,
                                 .digital_format=DFOR_I2S,
                                 .i2s_param.bits_per_sample=16,
                                 .i2s_param.bus_mode=BC127_I2SMODE_SLAVE,
                                 .i2s_param.justify_format=JUST_FMT_LEFT,
                                 .i2s_param.left_justify_delay=LEFT_JUST_DELAY_MSB_1ST_SCLK,
                                 .i2s_param.channel_polarity=CH_POL_LEFT_WS_HIGH,
                                 .i2s_param.justify_resolution=JUST_RES_16_BIT,
                                 .i2s_param.crop_enable=CROP_EN_17_TO_16_BIT,
                                 .i2s_param.start_rx_sampling=ST_SAM_LOW_WCLK_PHASE,
                                 .i2s_param.start_tx_sampling=ST_SAM_LOW_WCLK_PHASE,
                                 .i2s_param.scaling_factor=32, /*No more than 64!*/
                                 .i2s_param.audio_attenuation=0,
                                 .i2s_param.audio_attenuation_en=AUDIO_ATT_EN_17_TO_16_bit,
};

Bc127Config_t Bc127Config;

Bc127Handle_t Bc127Item={
                         .cur_line="",
                         .fix_line="",
                         .line_cnt=0,
                         .pos=0,
                         .digital_rate=0,
                         .digital_format=DFOR_UNDEF,
                         .param_1=0,
                         .Param2.reg_val=0,
};

