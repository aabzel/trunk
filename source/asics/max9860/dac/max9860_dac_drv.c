#include "max9860_dac_drv.h"

#include <string.h>

#include "common_diag.h"
#include "log.h"
#include "max9860_config.h"
#include "max9860_diag.h"
#include "max9860_drv.h"
#include "none_blocking_pause.h"
#include "proc_multimedia.h"
#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif

#ifdef HAS_I2S
#include "i2s_drv.h"
#ifdef HAS_I2S_TEST
#include "test_i2s.h"
#endif
#endif

bool max9860_dac_gain_set(Gain_t dac_gain) {
    bool res = false;
    LOG_DEBUG(MAX9860, "DacGainSet %d dB", dac_gain);
    Max9860Reg0BDacGainSidetone_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_DAC_GAIN_AND_SIDETONE, &Reg.byte);
    if(res) {
        Reg.dvg = dac_gain;
        res = max9860_reg_set(MAX9860_REG_DAC_GAIN_AND_SIDETONE, Reg.byte);
    }
    return res;
}

uint8_t DvaGain2Code(Gain_t gain) {
    uint8_t code = 0;
    if(3 < gain) {
        code = 0x00;
    } else if(gain < -90) {
        code = 0xBC;
    } else {
        code = 0x06 - gain * 2;
    }
    return code;
}

/* DAC Level Adjust.
 * Adjusts the digital audio level before being converted by the DAC. The least significant bit of DVA is always 0.
 * 0-3, 2-2, 4-1, 6-0 */
Gain_t DacLevelAttenuation2Gain(uint8_t dva_code) {
    Gain_t gain = 0;

    if(0xBC <= dva_code) {
        gain = INT8_MIN;
    } else {
        gain = 3 - dva_code / 2;
    }
    return gain;
}

Gain_t AdcSideToneCode2Gain(uint8_t dvst_code) {
    Gain_t gain = 0;
    if(1 <= dvst_code) {
        if(dvst_code <= DVST_MAX) {
            gain = -2 * ((int8_t)dvst_code) + 2;
        } else {
            LOG_ERROR(MAX9860, "InvalidDVST 0x%x", dvst_code);
        }
    }
    return gain;
}

bool is_valid_dva_gain(Gain_t gain) {
    bool res = false;
    if((-90 <= gain) && (gain <= 3)) {
        res = true;
    }
    return res;
}

/*DAC Attenuation*/
bool max9860_attenuation_set(Gain_t gain) {
    bool res = false;
    LOG_DEBUG(MAX9860, "DacAttenuationSet %d dB", gain);
    res = is_valid_dva_gain(gain);
    if(res) {
        uint8_t dva_code = DvaGain2Code(gain);
        res = max9860_reg_set(MAX9860_REG_DAC_ATTENUATION, dva_code);
    } else {
        LOG_ERROR(MAX9860, "DacAttenuationInvalidGain  %d dB ", gain);
    }
    return res;
}

Gain_t max9860_attenuation_get(void) {
    Gain_t gain = -100;
    bool res = false;
    uint8_t dva_code = 0;
    res = max9860_reg_get(MAX9860_REG_DAC_ATTENUATION, &dva_code);
    if(res) {
        gain = DacLevelAttenuation2Gain(dva_code);
    } else {
        LOG_ERROR(MAX9860, "ReadDigitalAudioLevelErr");
    }
    return gain;
}

Gain_t GvgCode2Gain(DacGainCode_t dvg) {
    Gain_t gain = 0;
    switch((uint8_t)dvg) {
    case DAC_GAIN_0:
        gain = 0;
        break;
    case DAC_GAIN_6:
        gain = 6;
        break;
    case DAC_GAIN_12:
        gain = 12;
        break;
    case DAC_GAIN_18:
        gain = 18;
        break;
    }
    return gain;
}

Gain_t max9860_dac_gain_get(void) {
    bool res = false;
    /*TODO*/
    Gain_t dac_gain = 0;
    Max9860Reg0BDacGainSidetone_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_DAC_GAIN_AND_SIDETONE, &Reg.byte);
    if(res) {
        dac_gain = GvgCode2Gain(Reg.dvg);
    }

    return dac_gain;
}

bool max9860_dac_set(bool on_off) {
    bool res = false;
    Max9860Reg10SysShutdown_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_SYSTEM_SHUTDOWN, &Reg.byte);
    if(res) {
        Reg.dacen = on_off;
        res = max9860_reg_set(MAX9860_REG_SYSTEM_SHUTDOWN, Reg.byte);
    }
    return res;
}

bool max9860_dac_get(void) {
    bool res = false;
    Max9860Reg10SysShutdown_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_SYSTEM_SHUTDOWN, &Reg.byte);
    if(res) {
        res = Reg.dacen;
    }
    return res;
}

bool max9860_volume_set(Gain_t volume) {
    bool res = false;
    LOG_DEBUG(MAX9860, "VoluneSet %d db", volume);
    res = max9860_attenuation_set(volume);
    if(res) {
        LOG_DEBUG(MAX9860, "VoluneSet %d dB Ok", volume);
    } else {
        LOG_ERROR(MAX9860, "VoluneSet %d dB Err", volume);
    }

    return res;
}

Gain_t max9860_volume_get(void) {
    Gain_t gain = max9860_attenuation_get();
    LOG_DEBUG(MAX9860, "VoluneGet %d dB", gain);
    return gain;
}

bool max9860_play_infinite(double freq, int16_t amp) {
    LOG_INFO(MAX9860, "PlayInfinit Freq: %f Hz Amp: %d ", freq, amp);
    bool res = false;
#ifdef HAS_TEST_I2S
    res = test_i2s_play_freq_com(Max9860Config.i2s_num, freq, amp);
#endif
    if(res) {
        LOG_INFO(MAX9860, "PlayStart Freq:%f Hz Amp:%d Ok", freq, amp);
    } else {
        LOG_ERROR(MAX9860, "PlayStart Freq:%f Hz Amp:%d  Err", freq, amp);
    }
    return res;
}

bool max9860_stereo_get(void) {
    bool res = false;
    Max9860Reg07If2_t RegIf;
    RegIf.byte = 0;
    res = max9860_reg_get(MAX9860_REG_INTERFACE2, &RegIf.byte);
    if(res) {
        LOG_INFO(MAX9860, "Stereo %s", Max9860StereoToStr(RegIf.st));
    }

    return res;
}

MaxStereo_t Stereo2Code(bool on_off) {
    MaxStereo_t code = MAX_STEREO_UNDEF;
    if(on_off) {
        code = MAX_STEREO_ON;
    } else {
        code = MAX_STEREO_OFF;
    }
    return code;
}

bool max9860_stereo_set(bool on_off) {
    bool res = false;
    LOG_INFO(MAX9860, "SetStereo %s", OnOffToStr(on_off));

    Max9860Reg07If2_t RegIf;
    RegIf.byte = 0;
    res = max9860_reg_get(MAX9860_REG_INTERFACE2, &RegIf.byte);
    if(res) {
        RegIf.st = Stereo2Code(on_off);
        res = max9860_reg_set(MAX9860_REG_INTERFACE2, RegIf.byte);
    }

    return res;
}

bool max9860_play_1kHz_tone(double amplitude, double phase_ms) {
    bool res = false;
    LOG_INFO(MAX9860, "Play Freq:1kHz, Amp:%f, Phase:%f ms", amplitude, phase_ms);
#ifdef HAS_I2S
    res = i2s_dma_stop(Max9860Config.i2s_num);
#endif
    res = play_1kHz_tone(Max9860Config.i2s_num, 1, amplitude, phase_ms);
    if(res) {
        LOG_INFO(MAX9860, "Play1kHzOk");
    } else {
        LOG_ERROR(MAX9860, "Play1kHzErr");
    }
    return res;
}

bool max9860_play_1kHz_tone_limited(double amplitude, double phase_ms, uint32_t duratin_ms) {
    bool res = false;
    LOG_INFO(MAX9860, "Play Freq:1kHz, Amp:%f, Phase:%f ms, Duration %u ms", amplitude, phase_ms, duratin_ms);
    res = i2s_dma_stop(Max9860Config.i2s_num);
    res = max9860_play_1kHz_tone(amplitude, phase_ms);
    if(res) {
        res = wait_ms(duratin_ms);
        if(res) {
            LOG_INFO(MAX9860, "Wait :%u ms Ok", duratin_ms);
        } else {
            LOG_ERROR(MAX9860, "Wait :%u ms Err", duratin_ms);
        }
        res = i2s_dma_stop(Max9860Config.i2s_num);
    } else {
        LOG_ERROR(MAX9860, "Play1kHzErr");
    }
    return res;
}
