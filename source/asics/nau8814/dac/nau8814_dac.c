#include "nau8814_dac.h"

#include <string.h>

#include "common_diag.h"
#include "log.h"
#include "nau8814_drv.h"
#include "none_blocking_pause.h"
#include "num_to_str.h"

#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif

#ifdef HAS_I2S
#include "i2s_mcal.h"

#ifdef HAS_I2S_TEST
#include "test_i2s.h"
#endif

#endif

/*
  Speaker Gain
  sab -57 0 6 63
 * */
uint16_t NauSpkGainToCode(Gain_t gain) {
    uint16_t code = 0;
    code = gain + 57;
    return code;
}

/*
  Speaker Gain
  sab 0 -57 63 6
 * */
Gain_t NauSpkGainCodeToGain(uint8_t code) {
    Gain_t gain = 0;
    gain = code - 57;
    return gain;
}

/*sab -127 1 0 255

  :I [SOLVER] y=ax+b, y=(2)x+(255)
  :I [SOLVER] Y=(2)*X +(255)
*/

uint8_t NauGainToGainCode(fGain_t dac_gain) {
    uint16_t code = 0;
    if(-127.0 <= dac_gain) {
        if(dac_gain <= 0.0) {
            code = 2.0 * dac_gain + 255.0;
        } else {
            code = 0xFF;
        }
    } else {
        code = 0;
    }
    LOG_DEBUG(NAU8814, "Gain:%f dB->Code:%u=0x%04x=0b%s", dac_gain, code, code, utoa_bin8(code));
    return (uint8_t)code;
}

/*sab 1 -127 255 0

I [SOLVER] y=ax+b, y=(0.5)x+(-127.5)
I [SOLVER] Y=(0.5)*X +(-127.5)
*/
fGain_t NauDacGainCodeToGain(uint16_t code) {
    fGain_t dac_gain = 0;
    if(code) {
        dac_gain = (fGain_t)(0.5 * ((float)code) - 127.5);
    } else {
        dac_gain = -999.0;
    }
    LOG_DEBUG(NAU8814, "Code:%u=0x%04x=0b%s->Gain:%f dB", code, code, utoa_bin8(code), dac_gain);
    return dac_gain;
}

static bool nau8814_dac_gain_set_ll(Nau8814Handle_t* Node, fGain_t dac_gain) {
    bool res = false;
    LOG_WARNING(NAU8814, "SetGain:%f dB", dac_gain);
    Nau8814RegDacVolume_t Reg;
    Reg.word = 0;
    Reg.dacgain = NauGainToGainCode(dac_gain);
    res = nau8814_reg_write_ll(Node, NAU8814_REG_DAC_VOLUME, Reg.word);
    return res;
}

bool nau8814_dac_gain_set(uint8_t num, fGain_t dac_gain) {
    bool res = false;
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        res = nau8814_dac_gain_set_ll(Node, dac_gain);
    }
    return res;
}

static bool nau8814_spk_gain_set_ll(Nau8814Handle_t* Node, Gain_t gain) {
    bool res = false;
    LOG_WARNING(NAU8814, "SetSpkGain:%d dB", gain);
    Nau8814RegSpkOutVolume_t Reg;
    Reg.word = 0;
    res = nau8814_reg_read_ll(Node, NAU8814_REG_SPKOUT_VOLUME, &Reg.word);
    if(res) {
        Reg.spkgain = NauSpkGainToCode(gain);
        res = nau8814_reg_write_ll(Node, NAU8814_REG_SPKOUT_VOLUME, Reg.word);
    }
    return res;
}

bool nau8814_spk_gain_set(uint8_t num, Gain_t gain) {
    bool res = false;
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        res = nau8814_spk_gain_set_ll(Node, gain);
    }
    return res;
}

bool nau8814_dac_gain_get(uint8_t num, fGain_t* const dac_gain) {
    bool res = false;
    Nau8814RegDacVolume_t Reg;
    Reg.word = 0;
    res = nau8814_reg_read(num, NAU8814_REG_DAC_VOLUME, &Reg.word);
    if(res) {
        *dac_gain = NauDacGainCodeToGain(Reg.dacgain);
        LOG_INFO(NAU8814, "GetDacGain:%f dB", *dac_gain);
    }
    return res;
}

bool nau8814_spk_gain_get(uint8_t num, Gain_t* const gain) {
    bool res = false;
    Nau8814RegSpkOutVolume_t Reg;
    Reg.word = 0;
    res = nau8814_reg_read(num, NAU8814_REG_SPKOUT_VOLUME, &Reg.word);
    if(res) {
        *gain = NauSpkGainCodeToGain(Reg.spkgain);
        LOG_INFO(NAU8814, "GetSpkGain:%f dB", *gain);
    }
    return res;
}

#if 0
bool nau8814_play_1kHz_tone(uint8_t num, SampleType_t amplitude, uint32_t phase_ms) {
    bool res = false;
    res = nau8814_play_1khz_con(num, amplitude);
    return res;
}
#endif

bool nau8814_play_tone(uint8_t num, double freq_hz, SampleType_t amplitude, uint32_t duration_ms) {
    bool res = false;
    if(0.0 < freq_hz) {
        if(0 < amplitude) {
            LOG_INFO(NAU8814, "Play Amplitude:%d,Freq:%f Hz,Duration:%u ms", amplitude, freq_hz, duration_ms);
            Nau8814Handle_t* Node = Nau8814GetNode(num);
            if(Node) {
#ifdef HAS_I2S
                res = i2s_play_tone(Node->i2s_num, Node->dac_num, freq_hz, amplitude, duration_ms);
                if(res) {
                    LOG_INFO(NAU8814, "I2sPlayOk");
                } else {
                    LOG_ERROR(NAU8814, "I2sPlayErr");
                }
#endif
            }
        }
    }
    return res;
}

bool nau8814_play_1khz_con(uint8_t num, SampleType_t amplitude) {
    LOG_INFO(NAU8814, "Play 1kHz Amplitude: %u", amplitude);
    bool res = false;
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        // res = nau8814_set_volume(5, 5);
#ifdef HAS_I2S
        res = i2s_play_1khz(Node->i2s_num, 1, amplitude, 0);
        if(res) {
            LOG_DEBUG(NAU8814, "I2sPlay1kOk"); // hang on
            res = true;
        } else {
            LOG_ERROR(NAU8814, "I2sPlay1kErr");
            res = false;
        }

#endif /*HAS_I2S*/
    } else {
        LOG_ERROR(NAU8814, "NodeErr");
    }
    return res;
}

bool nau8814_mute(uint8_t num) {
    bool res = false;
    LOG_INFO(NAU8814, "%u Mute", num);
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        res = nau8814_dac_gain_set_ll(Node, -128.0);
    }
    return res;
}

bool nau8814_play_1khz(uint8_t num, SampleType_t amplitude, uint32_t duratin_ms) {
    bool res = false;
    LOG_INFO(NAU8814, "Play1kHz,Amplitude:%d,Dur:%u ms", amplitude, duratin_ms);
    if(duratin_ms) {
        Nau8814Handle_t* Node = Nau8814GetNode(num);
        if(Node) {
            res = nau8814_play_1khz_con(num, amplitude);
            if(res) {
                res = false;
#ifdef HAS_I2S
                I2sHandle_t* I2sNode = I2sGetNode(Node->i2s_num);
                if(I2sNode) {
                    res = true;
                    uint32_t up_time = time_get_ms32();
                    I2sNode->play_off_time_stamp_ms = up_time + duratin_ms;
                    LOG_INFO(NAU8814, "OffTime:%u ms", I2sNode->play_off_time_stamp_ms);
                } else {
                    res = false;
                    LOG_ERROR(NAU8814, "I2sNodeErr");
                }
                LOG_INFO(NAU8814, "Play1kConOk");
#endif
            } else {
                LOG_ERROR(NAU8814, "PlayConErr");
            }
        } else {
            LOG_ERROR(NAU8814, "NodeErr");
        }
    } else {
        LOG_ERROR(NAU8814, "DurationErr");
    }

    return res;
}

bool nau8814_init_dac(uint8_t num) {
    bool res = true;
    LOG_WARNING(NAU8814, "DAC Init");

    const Nau8814Config_t* Config = Nau8814GetConfig(num);
    if(Config) {
        res = nau8814_dac_gain_set(num, Config->dac_gain);
        res = nau8814_spk_gain_set(num, Config->spk_gain);
    }

    return res;
}
