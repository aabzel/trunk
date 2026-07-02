#include "wm8731_drv.h"

#include <stdint.h>
#include <string.h>

#include "bit_const.h"
#include "clock.h"
#include "code_generator.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "dds_drv.h"
#include "i2c_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "num_to_str.h"
#include "time_mcal.h"

//#include "c_defines_generated.h"

#ifdef HAS_ARRAY_DIAG
#include "array_diag.h"
#endif

#ifdef HAS_I2S
#include "i2s_mcal.h"

#ifdef HAS_TEST_I2S
#include "test_i2s.h"
#endif

#endif

#ifdef HAS_TEST_WM8731
#include "test_wm8731.h"
#endif

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

COMPONENT_GET_NODE(Wm8731, wm8731)
COMPONENT_GET_CONFIG(Wm8731, wm8731)

const Wm8731Reg_t Wm8731RegMap[] = {
    {
        .reg_addr = 0x00,
        .name = "LeftLineIn",
    },
    {
        .reg_addr = 0x02,
        .name = "LeftHeadphoneOut",
    },
    {
        .reg_addr = 0x03,
        .name = "RightHeadphoneOut",
    },
    {
        .reg_addr = 0x04,
        .name = "AnalogAudioPathControl",
    },
    {
        .reg_addr = 0x05,
        .name = "DigitalAudioPathControl",
    },
    {
        .reg_addr = 0x06,
        .name = "PowerDownControl",
    },
    {
        .reg_addr = 0x07,
        .name = "DigitalAudioInterfaceFormat",
    },
    {
        .reg_addr = 0x08,
        .name = "SamplingControl",
    },
    {
        .reg_addr = 0x09,
        .name = "ActiveControl",
    },
    {
        .reg_addr = 0x0A,
        .name = "R5",
    },
    {
        .reg_addr = 0x0C,
        .name = "R6",
    },
    {
        .reg_addr = 0x0E,
        .name = "R7",
    },
    {
        .reg_addr = 0x0F,
        .name = "ResetRegister",
    },
    {
        .reg_addr = 0x10,
        .name = "R8SamplingControl",
    },
    {
        .reg_addr = 0x12,
        .name = "Active",
    },
    {
        .reg_addr = 0x1E,
        .name = "ResetRegister",
    },
};

uint8_t wm8731_get_reg_cnt(void) {
    uint8_t cnt = ARRAY_SIZE(Wm8731RegMap);
    return cnt;
}

static bool Wm8731IsValidConfig(const Wm8731Config_t*const Config) {
    bool res = false;
    if(Config){
        bool lres = true;
        res = true;
        lres = dds_is_init(Config->dds_num);
        ifn(lres){
            LOG_ERROR(WM8731, "WM8731_%u,Cfg,Error,DssNotInit", Config->num);
            res = false ;
        }

        lres = i2c_is_init(Config->i2c_num);
        ifn(lres){
            LOG_ERROR(WM8731, "WM8731_%u,Cfg,Error,I2cNotInit", Config->num);
            res = false ;
        }

        lres = i2s_is_init(Config->i2s_tx_num);
        ifn(lres){
            LOG_ERROR(WM8731, "WM8731_%u,Cfg,Error,I2sTxNotInit", Config->num);
            res = false ;
        }

        ifn(Config->name){
            LOG_ERROR(WM8731, "WM8731_%u,Cfg,Error,Name", Config->num);
        }

        ifn(Config->RegArray){
            LOG_ERROR(WM8731, "WM8731_%u,Cfg,Error,RegArray", Config->num);
            res = false ;
        }

        ifn(1<Config->reg_cnt){
            LOG_ERROR(WM8731, "WM8731_%u,Cfg,Error,reg_cnt", Config->num);
            res = false ;
        }
    }
    return res;
}




bool wm8731_get_reg(uint8_t num, uint8_t reg_addr, uint8_t* reg_val) {
    bool res = false;
    Wm8731Handle_t* Node = Wm8731GetNode(num);
    if(Node) {
#if 0
        res = i2c_mcal_write(Node->i2c_num, WM8731_7BIT_ADDRESS  , &reg_addr,   1) ;
        if(res){
            res=  i2c_mcal_read( Node->i2c_num, WM8731_7BIT_ADDRESS  , reg_val,   1) ;
        }
#endif
    }

    return res;
}

bool wm8731_set_reg(uint8_t num, uint8_t reg_addr, uint8_t reg_val) {
    bool res = false;
    LOG_DEBUG(WM8731, "Set Reg:0x%02x Val:0x%02x", reg_addr, reg_val);
    Wm8731Handle_t* Node = Wm8731GetNode(num);
    if(Node) {
#ifdef HAS_I2C
        // res = true;
        uint8_t data[2] = {reg_addr << 1, reg_val};
        res = i2c_mcal_write(Node->i2c_num, WM8731_7BIT_ADDRESS, data, 2);
        if(res) {
            LOG_DEBUG(WM8731, "WrOk! Chip 0x%x", WM8731_7BIT_ADDRESS);
        } else {
            LOG_ERROR(WM8731, "SetErr I2C:%u Chip:0x%x Data 0x%02x%02x", Node->i2c_num, WM8731_7BIT_ADDRESS, reg_addr,
                      reg_val);
        }

#endif /*HAS_I2C*/
#if 0
        uint8_t wr_addr = i2c_compose_write_address(reg_addr);
        res = i2c_mcal_write_reg(Node->i2c_num, WM8731_7BIT_ADDRESS, wr_addr, reg_val);
        if(res) {
            LOG_DEBUG(WM8731, "WrOk! Chip 0x%x", wr_addr);
        } else {
            LOG_ERROR(WM8731, "SetErr I2C:%u Chip:0x%x Data 0x%02x%02x", Node->i2c_num, WM8731_7BIT_ADDRESS,
                      reg_addr, reg_val);
        }
#endif
    }
    return res;
}

bool wm8731_reset(uint8_t num) {
    bool res = true;
    res = wm8731_set_reg(num, WM8731_REG_RESET, 0x00);
    return res;
}

bool wm8731_check(uint8_t num) {
    bool res = true;
    Wm8731Handle_t* Node = Wm8731GetNode(num);
    if(Node) {
#ifdef HAS_I2C
        // res = i2c_check_addr(Node->i2c_num, WM8731_7BIT_ADDRESS);
        // if(false == res) {
        //    LOG_ERROR(WM8731, "LinkErr I2C:0x%x Chip:0x%x", Node->i2c_num, WM8731_7BIT_ADDRESS);
        //}
#endif
    }
    return res;
}

const Wm8731RegConfig_t* Wm8731GetRegConfig(uint8_t num, uint8_t reg_addr) {
    const Wm8731RegConfig_t* RegConfig = NULL;
    const Wm8731Config_t* Config = Wm8731GetConfig(num);
    if(Config) {
        uint32_t i = 0;
        for(i = 0; i < Config->reg_cnt; i++) {
            if(reg_addr == Config->RegArray[i].reg_addr) {
                RegConfig = &Config->RegArray[i];
                break;
            }
        }
    }
    return RegConfig;
}

#ifdef HAS_PARAM
static bool wm8731_load_params(uint8_t num, Wm8731RegConfig_t* const RegConfig) {
    bool out_res = true;
    Wm8731RegConfig_t* Wm8731RegConfig = (Wm8731RegConfig_t*)Wm8731GetRegConfig(num, WM8731_REG_IFACE);
    if(Wm8731RegConfig) {
        Wm8731BusRole_t bus_role = BUS_MODE_UNDEF;
        LOAD_PARAM_V2(WM8731, PAR_ID_WM8731_I2S_BUS_ROLE, bus_role);
        if(out_res) {
            Wm8731RegConfig->value.DigitalAudioIfCtrl.ms = bus_role;
        } else {
            LOG_ERROR(WM8731, "NoRoleInParams");
        }
    }
    return out_res;
}
#endif /*HAS_PARAM*/

bool wm8731_set_sidetone(uint8_t num, bool state) {
    bool res = false;

    Wm8731Handle_t* Node = Wm8731GetNode(num);
    if(Node) {
        const Wm8731RegConfig_t* RegConfig = Wm8731GetRegConfig(num, WM8731_REG_APANA);
        if(RegConfig) {
            Wm8731RegAnalogAudioPathCtrl_t AnalogAudioPathCtrl; //
            AnalogAudioPathCtrl.reg_val = RegConfig->value.reg_val;
            if(state) {
                AnalogAudioPathCtrl.side_tone = SIDE_TONE_ON;
            } else {
                AnalogAudioPathCtrl.side_tone = SIDE_TONE_OFF;
            }
            res = wm8731_set_reg(num, WM8731_REG_APANA, AnalogAudioPathCtrl.reg_val);
        }
    }

    return res;
}

bool wm8731_is_valid_volume(int8_t vol_db) {
    bool res = false;
    if(WM_MIN_VOL_DB <= vol_db) {
        if(vol_db <= WM_MAX_VOL_DB) {
            res = true;
        }
    } else {
        LOG_ERROR(WM8731, "VolumeOutOfRange %d dB", vol_db);
    }
    return res;
}

int8_t wm8731_volume_limiter(int8_t vol_db) {
    int8_t out_vol = vol_db;
    if(WM_MAX_VOL_DB < vol_db) {
        LOG_WARNING(WM8731, "VolumeOverflow Need:%d Max:%ddB", vol_db, WM_MAX_VOL_DB);
        out_vol = WM_MAX_VOL_DB;
    } else if(vol_db < WM_MIN_VOL_DB) {
        LOG_WARNING(WM8731, "VolumeUnderflow Need:%d Min:%ddB", vol_db, WM_MIN_VOL_DB);
        out_vol = WM_MIN_VOL_DB;
    } else {
        LOG_DEBUG(WM8731, "Volume Ok Need:%d", vol_db);
        out_vol = vol_db;
    }
    return out_vol;
}

uint8_t wm8731_vol_code(int8_t vol) {
    uint16_t code = 48;
    int8_t cur_vol = -73;
    for(code = 48, cur_vol = -73; code <= 127; code++, cur_vol++) {
        if(cur_vol == vol) {
            break;
        }
    }
    return (uint8_t)(MASK_7BIT & code);
}

#define WM_SET_VOLUME(REG_TYPE, VOL_CODE, REG_ADDR, FIELD, DIR_NAME)                                                   \
    do {                                                                                                               \
        res_##VOL_CODE = false;                                                                                        \
        Node->VOL_CODE = VOL_CODE;                                                                                     \
        int8_t set_vol_code = wm8731_volume_limiter(VOL_CODE);                                                         \
        Config = Wm8731GetRegConfig(num, REG_ADDR);                                                                    \
        if(Config) {                                                                                                   \
            REG_TYPE Reg;                                                                                              \
            Reg.reg_val = Config->value.reg_val;                                                                       \
            Reg.FIELD = wm8731_vol_code(set_vol_code);                                                                 \
            res_##VOL_CODE = wm8731_set_reg(num, REG_ADDR, Reg.reg_val);                                               \
            if(res_##VOL_CODE) {                                                                                       \
                LOG_DEBUG(WM8731, "SetVolume" DIR_NAME "Ok");                                                          \
            } else {                                                                                                   \
                LOG_ERROR(WM8731, "SetVolume" DIR_NAME "Err");                                                         \
            }                                                                                                          \
        } else {                                                                                                       \
            LOG_ERROR(WM8731, "ConfErr");                                                                              \
        }                                                                                                              \
    } while(0);

bool wm8731_set_volume(uint8_t num, int8_t left, int8_t right) {
    bool res = false;

    Wm8731Handle_t* Node = Wm8731GetNode(num);
    if(Node) {

#if 1
        LOG_DEBUG(WM8731, "TrySetVolume L:%d R:%d", left, right);
#if 0
        res = wm8731_is_valid_volume(  left);
        if(res){
        }
        res = wm8731_is_valid_volume(  right);
        if(res){

        }
#endif
        Wm8731RegConfig_t* Config = NULL;
        bool res_left = false;
        bool res_right = false;

        if(Node->left != left) {
            WM_SET_VOLUME(Wm8731RegLeftHeadOutCtrl_t, left, WM8731_REG_LOUT1V, lhpvol, "Left");
        } else {
            res_left = true;
        }

        if(Node->right != right) {
            WM_SET_VOLUME(Wm8731RegRightHeadOutCtrl_t, right, WM8731_REG_ROUT1V, rhpvol, "Right");
        } else {
            res_right = true;
        }

        if(res_left) {
            LOG_DEBUG(WM8731, "SetLVolOk L:%d dB", left);
            res = true;
        } else {
            LOG_ERROR(WM8731, "SetLVolErr");
        }

        if(res_right) {
            LOG_DEBUG(WM8731, "SetRVolOk R:%d dB", right);
            res = true;
        } else {
            LOG_ERROR(WM8731, "SetRVolErr");
        }

#endif
    }
    return res;
}

bool wm8731_bypass(uint8_t num) {
    bool res = false;

    Wm8731Handle_t* Node = Wm8731GetNode(num);
    if(Node) {
        Wm8731RegAnalogAudioPathCtrl_t Reg;
        Reg.mic_boost = MIC_IN_BOOST_OFF; /* Microphone Input Level Boost        */
        Reg.mute_mic = MIC_MUTE_ON;       /* Mic Input Mute to ADC               */
        Reg.insel = ADC_IN_SEL_MIC;       /* Microphone/Line Input Select to ADC */
        Reg.by_pass = BYPASS_SW_ON;       /* Bypass Switch                       */
        Reg.dac_sel = DAC_SEL_OFF;        /* DAC Select                          */
        Reg.side_tone = SIDE_TONE_ON;     /* Side Tone Switch                    */
        Reg.sideatt = 0;                  /* Side Tone Attenuation               */

        res = wm8731_set_reg(num, WM8731_REG_APANA, Reg.reg_val);
    }

    return res;
}

bool wm8731_listen(uint8_t num, uint32_t des_duration_ms) {
    bool res = false;
    LOG_INFO(WM8731, "%u,Listen,Duration:%u ms", num, des_duration_ms);
    Wm8731Handle_t* Node = Wm8731GetNode(num);
    if(Node) {
#ifdef HAS_I2S
        // res = i2s_listen(Config->i2s_tx_num, des_duration_ms);
        res = i2s_listen(Node->i2s_rx_num, des_duration_ms);
#endif /*HAS_I2S*/
        Node->state = WM8731_STATE_RECORD;
        Node->rec_off_time_stamp_ms = time_get_ms32() + des_duration_ms;
    }
    return res;
}

#if 0
static bool wm8731_init_cache(Wm8731Handle_t* const Node, const Wm8731Config_t* const Config) {
    bool res = true;
    if(Config) {
        if(Node) {
            Node->i2s_tx_num = Config->i2s_tx_num;
            Node->i2s_rx_num = Config->i2s_rx_num;
            Node->i2c_num = Config->i2c_num;
            Node->right = Config->right;
            Node->left = Config->left;
            res = true;
        }
    }
    return res;
}
#endif

bool wm8731_play_1khz_con(uint8_t num, SampleType_t amplitude) {
    LOG_INFO(WM8731, "Wm8731Play 1kHz Amplitude: %u", amplitude);
    bool res = false;
    Wm8731Handle_t* Node = Wm8731GetNode(num);
    if(Node) {
        if(0 < amplitude) {
            res = wm8731_set_volume(num, 5, 5);
#ifdef HAS_I2S
            res = i2s_play_1khz(Node->i2s_tx_num, 1, amplitude, 0);
            log_info_res(WM8731, res, "Play1kHz");
#endif /*HAS_I2S*/
            Node->state = WM8731_STATE_PLAY;
        } else {
            LOG_ERROR(TEST, "AmpTooHi Cur:%d Max:%d", amplitude, WM8731_MAX_AMP);
        }
    }

    return res;
}

bool wm8731_mute(uint8_t num) {
    LOG_INFO(WM8731, "Mute");
    bool res = false;

    Wm8731Handle_t* Node = Wm8731GetNode(num);
    if(Node) {
        res = wm8731_set_volume(num, -70, -70);
        I2sConfig_t* Config = I2sGetConfig(Node->i2s_tx_num);
        if(Config) {
            res = gpio_init_one(&Config->GpioSdOut);
        }
        if(res) {
            LOG_INFO(WM8731, "MuteOk");
        } else {
            LOG_ERROR(WM8731, "MuteErr");
        }
    }

    return res;
}

bool wm8731_play_1khz(uint8_t num, SampleType_t amplitude, int32_t des_duration_ms) {
    LOG_INFO(WM8731, "Wm8731Play 1kHz Amplitude: %u", amplitude);
    bool res = false;

    Wm8731Handle_t* Node = Wm8731GetNode(num);
    if(Node) {
        res = wm8731_play_1khz_con(num, amplitude);
        if(res) {
#ifdef HAS_I2S
            I2sHandle_t* I2s = I2sGetNode(Node->i2s_tx_num);
            if(I2s) {
                res = true;
                I2s->play_off_time_stamp_ms = time_get_ms32() + des_duration_ms;
                LOG_INFO(WM8731, "OffTime:%u ms", I2s->play_off_time_stamp_ms);
            } else {
                res = false;
                LOG_ERROR(WM8731, "I2sErr");
            }
            LOG_INFO(WM8731, "Play1kConOk");
#endif /*HAS_I2S*/

            Node->state = WM8731_STATE_PLAY;
            Node->play_off_time_stamp_ms = time_get_ms32() + des_duration_ms;
        }
    }

    return res;
}

static inline bool wm8731_init_common(const Wm8731Config_t* const Config, Wm8731Handle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->chip_addr = Config->chip_addr;
            Node->i2s_rx_num = Config->i2s_rx_num;
            Node->i2s_tx_num = Config->i2s_tx_num;
            Node->RegArray = Config->RegArray;
            Node->reg_cnt = Config->reg_cnt;
            Node->dds_num = Config->dds_num;
            Node->i2c_num = Config->i2c_num;
            Node->left = Config->left;
            Node->right = Config->right;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

static bool wm8731_log_level_set(log_level_t level) {
    bool res = true;
#ifdef HAS_I2S
    set_log_level(I2S, level);
#endif

#ifdef HAS_I2C
    set_log_level(I2C, level);
#endif
    set_log_level(WM8731, level);
    return res;
}

static inline bool wm8731_set_deafault_config(Wm8731Handle_t* Node) {
    bool res = true;
    LOG_DEBUG(WM8731, "SetDefConfigs");
    LOG_DEBUG(WM8731, "%u,CfgRegCnt:%u", Node->num, Node->reg_cnt);
    uint32_t ok = 0;
    uint32_t i = 0;
    uint32_t t = 0;
    Wm8731RegConfig_t TempRegConfig[10] = {0};
    for(i = 0; i < Node->reg_cnt; i++) {
        TempRegConfig[i].reg_addr = Node->RegArray[i].reg_addr;
        TempRegConfig[i].value.reg_val = Node->RegArray[i].value.reg_val;
    }
#ifdef HAS_PARAM
    res = wm8731_load_params(Node->num, TempRegConfig);
#endif
    if(Node->reg_cnt == ARRAY_SIZE(TempRegConfig)) {
        for(i = 0; i < Node->reg_cnt; i++) {
            for(t = 0; t < 3; t++) {
                // delay_ms(200); // 200 works
                res = wm8731_set_reg(Node->num, TempRegConfig[i].reg_addr, TempRegConfig[i].value.reg_val);
                if(res) {
                    t = 200;
                    LOG_INFO(WM8731, "Set,Ok,Addr[0x%02x]=0x%02x", TempRegConfig[i].reg_addr,
                             TempRegConfig[i].value.reg_val);
                } else {
                    LOG_ERROR(WM8731, "Set,Err,Addr[0x%02x]=0x%02x,try: %u", TempRegConfig[i].reg_addr,
                              TempRegConfig[i].value.reg_val, t);
                }
            }

            if(res) {
                ok++;
            }
        }
    }
    return res;
}

bool wm8731_init_one(uint8_t num) {
    bool res = false;
    wm8731_log_level_set(LOG_LEVEL_DEBUG);
    const Wm8731Config_t* Config = Wm8731GetConfig(num);
    res = Wm8731IsValidConfig(Config);
    if(res) {
        LOG_WARNING(WM8731, "Init,%s", Wm8731ConfigToStr(Config));
        Wm8731Handle_t* Node = Wm8731GetNode(num);
        if(Node) {
            res = wm8731_init_common(Config, Node);
            res = wm8731_set_deafault_config(Node);
            Node->state = WM8731_STATE_IDLE;
            wm8731_set_sidetone(num, false);
            if(res) {
                res = wm8731_set_volume(num, Node->left, Node->right);
#ifdef HAS_WM8731_VERIFY
                LOG_INFO(WM8731, "VerifySound");
                res = wm8731_play_1khz(num, (SampleType_t)WM8731_VERIFY_AMP, WM8731_VERIFY_DURATION_MS);
#endif /**/
                res = true;
            }
        }
    }

    wm8731_log_level_set(LOG_LEVEL_INFO);
    return res;
}

bool wm8731_play_freq(uint8_t num, double freq, SampleType_t amplitude) {
    LOG_INFO(WM8731, "Wm8731Play Freq: %f Hz Amplitude: %u endlessly", freq, amplitude);
    bool res = false;
    Wm8731Handle_t* Node = Wm8731GetNode(num);
    if(Node) {
        if(0.0 < freq) {
            if(0<amplitude ) {
                res = wm8731_set_volume(num, 5, 5);
#ifdef HAS_TEST_I2S
                res = test_i2s_play_freq_com(Node->i2s_tx_num, freq, amplitude);
                Node->state = WM8731_STATE_PLAY;
#else  /*HAS_TEST_I2S*/
                LOG_ERROR(TEST, "LackOfI2STestCode");
                res = false;
#endif /*HAS_I2S*/
            } else {
                LOG_ERROR(TEST, "AmpTooHi Cur:%d Max:%d", amplitude, WM8731_MAX_AMP);
            }
        }
    }

    return res;
}

uint32_t wm8731_pcm_2_32bit_sample(int32_t pcm_sample) {
    uint32_t tx_sample = (uint32_t)pcm_sample;
    tx_sample = tx_sample << 8;
    LOG_DEBUG(WM8731, "Sample:%d->32Bit:0x%08x", pcm_sample, tx_sample);
    return tx_sample;
}

uint16_t wm8731_pcm_2_16bit_sample(int32_t pcm_sample) {
    uint32_t tx_sample32 = (uint32_t)pcm_sample;
    uint16_t tx_sample16 = tx_sample32;
    LOG_DEBUG(WM8731, "Sample:%d->32Bit:0x%08x->16Bit:0x%04x", pcm_sample, tx_sample32, tx_sample16);
    return tx_sample16;
}

static bool wm8731_init_custom(void) {
    bool res = true;

#ifdef HAS_I2C
    set_log_level(I2C, LOG_LEVEL_INFO);
#endif /**/

#ifdef HAS_I2S
    set_log_level(I2S, LOG_LEVEL_INFO);
#endif /**/
    set_log_level(WM8731, LOG_LEVEL_INFO);
    return res;
}

bool wm8731_proc_one(uint8_t num) {
    bool res = false;
    Wm8731Handle_t* Node = Wm8731GetNode(num);
    if(Node) {
        LOG_PARN(WM8731, "Proc:%u", num);
        uint32_t up_time = time_get_ms32();
        switch((uint32_t)Node->state) {
        case WM8731_STATE_PLAY: {
            if(Node->play_off_time_stamp_ms < up_time) {
                res = i2s_stop(Node->i2s_tx_num);
                Node->state = WM8731_STATE_IDLE;
                LOG_INFO(WM8731, "StopPlay");
            }
        } break;
        case WM8731_STATE_RECORD: {
            if(Node->rec_off_time_stamp_ms < up_time) {
                res = i2s_stop(Node->i2s_rx_num);
                Node->state = WM8731_STATE_IDLE;
                LOG_INFO(WM8731, "StopRec");
            }
        } break;
        default: {

        } break;
        } // switch
    }
    return res;
}

COMPONENT_INIT_PATTERT(WM8731, WM8731, wm8731)
COMPONENT_PROC_PATTERT(WM8731, WM8731, wm8731)
