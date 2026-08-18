#include "nau8814_adc.h"

#include <string.h>

#include "log.h"
#include "nau8814_drv.h"
#include "none_blocking_pause.h"
#include "num_to_str.h"
#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif

#ifdef HAS_I2S
#include "i2s_mcal.h"
#endif

bool nau8814_adc_ctrl(uint8_t num, bool adc_on) {
    bool res = false;
    LOG_INFO(NAU8814, "ADCctrl:%u,%u", num, adc_on);
    Nau8814RegPowerManagement2_t Reg;
    Reg.word = 0;
    res = nau8814_reg_read(num, NAU8814_REG_POWER_MANAGEMENT_2, &Reg.word);
    if(res) {
        Reg.adcen = adc_on;
        res = nau8814_reg_write(num, NAU8814_REG_POWER_MANAGEMENT_2, Reg.word);
    }
    return res;
}

bool nau8814_adc_get(uint8_t num, bool* const adc_on) {
    bool res = false;
    Nau8814RegPowerManagement2_t Reg;
    Reg.word = 0;
    res = nau8814_reg_read(num, NAU8814_REG_POWER_MANAGEMENT_2, &Reg.word);
    if(res) {
        *adc_on = Reg.adcen;
    }
    return res;
}

static BoostGainCode_t NauGainToBoostGainCode(Gain_t p_mic_gain) {
    BoostGainCode_t code = BOOST_GAIN_CODE_DISCONNECTED;
    switch(p_mic_gain) {
    case -12:
        code = BOOST_GAIN_CODE_M12;
        break;
    case -9:
        code = BOOST_GAIN_CODE_M9;
        break;
    case -6:
        code = BOOST_GAIN_CODE_M6;
        break;
    case -3:
        code = BOOST_GAIN_CODE_M3;
        break;
    case 0:
        code = BOOST_GAIN_CODE_0;
        break;
    case 3:
        code = BOOST_GAIN_CODE_3;
        break;
    case 6:
        code = BOOST_GAIN_CODE_6;
        break;
    default:
        code = BOOST_GAIN_CODE_DISCONNECTED;
        break;
    }
    return code;
}

Gain_t BstGainCodeToValue(BoostGainCode_t code) {
    Gain_t gain = -99;
    switch((uint8_t)code) {
    case BOOST_GAIN_CODE_DISCONNECTED:
        gain = -99;
        break;
    case BOOST_GAIN_CODE_M12:
        gain = -12;
        break;
    case BOOST_GAIN_CODE_M9:
        gain = -9;
        break;
    case BOOST_GAIN_CODE_M6:
        gain = -6;
        break;
    case BOOST_GAIN_CODE_M3:
        gain = -3;
        break;
    case BOOST_GAIN_CODE_0:
        gain = 0;
        break;
    case BOOST_GAIN_CODE_3:
        gain = 3;
        break;
    case BOOST_GAIN_CODE_6:
        gain = 6;
        break;
    }
    return gain;
}

float PgaGainCodeToValue(uint8_t code) {
    float gain_val = 0.0;
    gain_val = 0.75 * ((float)code) - 12.0;
    return gain_val;
}

bool nau8814_pga_gain_get(uint8_t num, float* const pga_gain) {
    bool res = false;
    Nau8814RegPgaGain_t Reg;
    Reg.word = 0;
    res = nau8814_reg_read(num, NAU8814_REG_PGA_GAIN, &Reg.word);
    if(res) {
        *pga_gain = PgaGainCodeToValue(Reg.pgagain);
    }
    return res;
}

bool nau8814_aux_gain_get(uint8_t num, Gain_t* const aux_gain) {
    bool res = false;
    Nau8814RegAdcBoost_t Reg;
    Reg.word = 0;
    res = nau8814_reg_read(num, NAU8814_REG_ADC_BOOST, &Reg.word);
    if(res) {
        *aux_gain = BstGainCodeToValue(Reg.auxbstgain);
    }
    return res;
}

bool nau8814_p_mic_gain_get(uint8_t num, Gain_t* const p_mic_gain) {
    bool res = false;
    Nau8814RegAdcBoost_t Reg;
    Reg.word = 0;
    res = nau8814_reg_read(num, NAU8814_REG_ADC_BOOST, &Reg.word);
    if(res) {
        *p_mic_gain = BstGainCodeToValue(Reg.pmicbstgain);
    }
    return res;
}

bool nau8814_p_mic_gain_set(uint8_t num, Gain_t p_mic_gain) {
    bool res = false;
    LOG_INFO(NAU8814, "%u,pMicGain:%d Set", num, p_mic_gain);
    Nau8814RegAdcBoost_t Reg;
    Reg.word = 0;
    res = nau8814_reg_read(num, NAU8814_REG_ADC_BOOST, &Reg.word);
    if(res) {
        Reg.pmicbstgain = NauGainToBoostGainCode(p_mic_gain);
        res = nau8814_reg_write(num, NAU8814_REG_ADC_BOOST, Reg.word);
    }
    return res;
}

uint8_t NauGainToPgaGainCode(float gain) {
    uint8_t code = 0;
    code = ((uint8_t)((4.0 * gain) / 3.0)) + 16;
    return code;
}

bool nau8814_pga_gain_set(uint8_t num, float pga_gain) {
    bool res = false;
    LOG_INFO(NAU8814, "%u,PgaGain:%f set", num, pga_gain);
    Nau8814RegPgaGain_t Reg;
    Reg.word = 0;
    res = nau8814_reg_read(num, NAU8814_REG_PGA_GAIN, &Reg.word);
    if(res) {
        Reg.pgagain = NauGainToPgaGainCode(pga_gain);
        res = nau8814_reg_write(num, NAU8814_REG_PGA_GAIN, Reg.word);
    }
    return res;
}

bool nau8814_aux_gain_set(uint8_t num, Gain_t aux_gain) {
    bool res = false;
    LOG_INFO(NAU8814, "%u, AuxGain:%d set", num, aux_gain);
    Nau8814RegAdcBoost_t Reg;
    Reg.word = 0;
    res = nau8814_reg_read(num, NAU8814_REG_ADC_BOOST, &Reg.word);
    if(res) {
        Reg.auxbstgain = NauGainToBoostGainCode(aux_gain);
        res = nau8814_reg_write(num, NAU8814_REG_ADC_BOOST, Reg.word);
    }
    return res;
}

bool nau8814_init_adc(uint8_t num) {
    bool res = false;
    LOG_WARNING(NAU8814, "ADC Init:%u", num);
    const Nau8814Config_t* Config = Nau8814GetConfig(num);
    if(Config) {
        res = nau8814_adc_ctrl(num, Config->adc_on);
        res = nau8814_p_mic_gain_set(num, Config->p_mic_gain);
        res = nau8814_aux_gain_set(num, Config->aux_gain);
        res = nau8814_pga_gain_set(num, Config->pga_gain);
    }
    return res;
}

bool nau8814_listen(uint8_t num, uint32_t des_duration_ms) {
    bool res = false;
    const Nau8814Config_t* Config = Nau8814GetConfig(num);
    if(Config) {
        LOG_WARNING(NAU8814, "Listen:%u,Dur:%u ms", num, des_duration_ms);
#ifdef HAS_I2S
        res = i2s_listen(Config->i2s_num, des_duration_ms);
#endif /*HAS_I2S*/
    }

    return res;
}
