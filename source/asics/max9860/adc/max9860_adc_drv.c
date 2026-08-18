#include "max9860_adc_drv.h"

#include <string.h>

#include "log.h"
#include "max9860_config.h"
#include "max9860_dep.h"
#include "max9860_drv.h"
#include "none_blocking_pause.h"
#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif

#ifdef HAS_I2S
#include "i2s_drv.h"
#endif

uint8_t Gain2DvstCode(Gain_t side_tone_gain) {
    uint8_t code = 0;
    if(side_tone_gain <= 0) {
        if(-60 <= side_tone_gain) {
            code = 1 - (side_tone_gain >> 1);
        } else {
            code = 0;
        }
    } else {
        code = 1;
    }
    return code;
}

bool max9860_sidetone_level_set(Gain_t gain) {
    bool res = false;
    LOG_INFO(MAX9860, "SideToneSet %d", gain);
    Max9860Reg0BDacGainSidetone_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_DAC_GAIN_AND_SIDETONE, &Reg.byte);
    if(res) {
        Reg.dvst = Gain2DvstCode(gain);
        res = max9860_reg_set(MAX9860_REG_DAC_GAIN_AND_SIDETONE, Reg.byte);
    }
    return res;
}

SideToneGain_t Code2SideToneGain(uint8_t code) {
    SideToneGain_t side_tone_gain = 0;
    if(1 <= code) {
        if(code <= 0x1f) {
            side_tone_gain = 2 - 2 * code;
        } else {
            side_tone_gain = INT8_MIN;
        }
    } else {
        side_tone_gain = INT8_MIN;
    }
    return side_tone_gain;
}

SideToneGain_t max9860_sidetone_level_get(void) {
    bool res = false;
    SideToneGain_t side_tone_gain = 0;
    Max9860Reg0BDacGainSidetone_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_DAC_GAIN_AND_SIDETONE, &Reg.byte);
    if(res) {
        side_tone_gain = Code2SideToneGain(Reg.dvst);
    }
    return side_tone_gain;
}

uint8_t AdcGain2Code(AdcGain_t adc_gain) {
    uint8_t code = 0;
    code = 3 - adc_gain;
    return code;
}

bool is_valid_adc_gain(AdcGain_t adc_gain) {
    bool res = false;
    if(-12 <= adc_gain && adc_gain <= 3) {
        res = true;
    }
    return res;
}

bool max9860_adc_output_level_set(MicChannel_t mic_channel, AdcGain_t adc_gain) {
    bool res = false;
    res = is_valid_adc_gain(adc_gain);
    if(res) {

        Max9860Reg0AAdcOutLevel_t Reg;

        Reg.byte = 0;
        res = max9860_reg_get(MAX9860_REG_ADC_OUTPUT_LEVELS, &Reg.byte);
        if(res) {
            switch(mic_channel) {
            case MIC_LEFT:
                Reg.adcll = AdcGain2Code(adc_gain);
                break;
            case MIC_RIGHT:
                Reg.adcrl = AdcGain2Code(adc_gain);
                break;
            default:
                break;
            }

            res = max9860_reg_set(MAX9860_REG_ADC_OUTPUT_LEVELS, Reg.byte);
        }
    }
    return res;
}

AdcGain_t AdcCode2Gain(uint8_t code) {
    AdcGain_t adc_gain = 0;
    adc_gain = 3 - code;
    return adc_gain;
}

AdcGain_t max9860_adc_output_level_get(MicChannel_t mic_channel) {
    bool res = false;
    AdcGain_t adc_gain = 0;
    Max9860Reg0AAdcOutLevel_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_ADC_OUTPUT_LEVELS, &Reg.byte);
    if(res) {
        switch(mic_channel) {
        case MIC_LEFT:
            adc_gain = AdcCode2Gain(Reg.adcll);
            break;
        case MIC_RIGHT:
            adc_gain = AdcCode2Gain(Reg.adcrl);
            break;
        default:
            break;
        }
    }
    return adc_gain;
}

#define DELTA 5
uint8_t Gain2PamCode(Gain_t gain) {
    bool res = false;
    uint8_t code = 0;

    res = is_around_int_val(0, gain, 10);
    if(res) {
        code = 1;
    }

    res = is_around_int_val(20, gain, DELTA);
    if(res) {
        code = 2;
    }

    res = is_around_int_val(30, gain, DELTA);
    if(res) {
        code = 3;
    }

    if(30 <= gain) {
        code = 3;
    }

    if(gain < 0) {
        code = 0;
    }
    return code;
}

bool max9860_microphone_preamp_set(Gain_t gain) {
    bool res = false;
    Max9860Reg0CMicrophoneGain_t Reg;
    Reg.byte = 0;

    res = max9860_reg_get(MAX9860_REG_MICROPHONE_GAIN, &Reg.byte);
    if(res) {
        Reg.pam = Gain2PamCode(gain);
        res = max9860_reg_set(MAX9860_REG_MICROPHONE_GAIN, Reg.byte);
    }
    return res;
}

Gain_t PamCode2Gain(uint8_t pam_code) {
    Gain_t gain;
    switch(pam_code) {
    case 0:
        gain = INT8_MIN;
        break;
    case 1:
        gain = 0;
        break;
    case 2:
        gain = 20;
        break;
    case 3:
        gain = 30;
        break;
    }

    return gain;
}

Gain_t max9860_microphone_preamp_get(void) {
    bool res = false;
    Gain_t gain = 0;
    Max9860Reg0CMicrophoneGain_t Reg;
    Reg.byte = 0;

    res = max9860_reg_get(MAX9860_REG_MICROPHONE_GAIN, &Reg.byte);
    if(res) {
        gain = PamCode2Gain(Reg.pam);
    }
    return gain;
}

uint8_t Gain2PgamCode(Gain_t gain) {
    uint8_t pgam_code = 0;

    if(0 <= gain) {
        if(gain <= 20) {
            pgam_code = 20 - gain;
        } else {
            pgam_code = 0;
        }
    } else {
        pgam_code = 0x14;
    }
    return pgam_code;
}

bool max9860_microphone_programmable_gain_amplifier_set(Gain_t gain) {
    bool res = false;
    Max9860Reg0CMicrophoneGain_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_MICROPHONE_GAIN, &Reg.byte);
    if(res) {
        Reg.pgam = Gain2PgamCode(gain);
        res = max9860_reg_set(MAX9860_REG_MICROPHONE_GAIN, Reg.byte);
    }
    return res;
}

Gain_t PgamCode2Gain(uint8_t pgam_code) {
    Gain_t gain = 0;
    if(pgam_code <= 0x13) {
        gain = 20 - pgam_code;
    } else {
        gain = 0;
    }
    return gain;
}

Gain_t max9860_microphone_programmable_gain_amplifier_get(void) {
    bool res = false;
    Gain_t gain = 0;
    Max9860Reg0CMicrophoneGain_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_MICROPHONE_GAIN, &Reg.byte);
    if(res) {
        gain = PgamCode2Gain(Reg.pgam);
    }
    return gain;
}

bool max9860_sidetone_set(bool on_off) {
    bool res = false;
    if(on_off) {
        res = max9860_sidetone_level_set(0);
    } else {
        res = max9860_sidetone_level_set(INT8_MIN);
    }
    return res;
}

bool max9860_adc_set(MicChannel_t mic_channel, bool on_off) {
    bool res = false;
    Max9860Reg10SysShutdown_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_SYSTEM_SHUTDOWN, &Reg.byte);
    if(res) {
        switch((uint8_t)mic_channel) {
        case MIC_LEFT:
            Reg.adclen = on_off;
            break;
        case MIC_RIGHT:
            Reg.adcren = on_off;
            break;
        }
        res = max9860_reg_set(MAX9860_REG_SYSTEM_SHUTDOWN, Reg.byte);
    }
    return res;
}

bool max9860_adc_get(MicChannel_t mic_channel) {
    bool res = false;
    Max9860Reg10SysShutdown_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_SYSTEM_SHUTDOWN, &Reg.byte);
    if(res) {
        switch((uint8_t)mic_channel) {
        case MIC_LEFT:
            res = Reg.adclen;
            break;
        case MIC_RIGHT:
            res = Reg.adcren;
            break;
        }
    }
    return res;
}

Gain_t MicrophoneProgrammableGainAmplifierCode2Gain(uint8_t pga) {
    Gain_t gain = 0;
    gain = -((int8_t)pga) + 20;
    return gain;
}

/*ADC Output Levels, Left and Right ADC Output Level (Reg 0x0A)
 *Table 8. Digital Level Control Registers
 *That is GAIN after Digital filter
 **/
Gain_t AdcOutputLevel2Gain(uint8_t adc_out_lev) {
    Gain_t gain = 0;
    if(adc_out_lev < 15) {
        gain = -((int8_t)adc_out_lev) + 3;
    } else {
        LOG_ERROR(MAX9860, "ValErr ADC Output Level %u", adc_out_lev);
    }
    return gain;
}
