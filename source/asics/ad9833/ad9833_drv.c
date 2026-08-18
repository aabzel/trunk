#include "ad9833_drv.h"

#include <math.h>

#include "ad9833_config.h"
#include "ad9833_const.h"
#include "ad9833_dep.h"
#include "ad9833_diag.h"
#include "bit_const.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "gpio_general_diag.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "spi_drv.h"

Ad9833Handle_t* Ad9833GetNode(uint8_t num) {
    Ad9833Handle_t* Ad9833Node = NULL;
    uint32_t i = 0;
    for(i = 0; i < ad9833_get_cnt(); i++) {
        if(num == Ad9833Instance[i].num) {
            if(Ad9833Instance[i].valid) {
                Ad9833Node = &Ad9833Instance[i];
                break;
            }
        }
    }
    return Ad9833Node;
}

const Ad9833Config_t* Ad9833GetConfNode(uint8_t num) {
    const Ad9833Config_t* Ad9833ConfNode = NULL;
    uint32_t i = 0;
    for(i = 0; i < ad9833_get_cnt(); i++) {
        if(num == Ad9833Config[i].num) {
            if(Ad9833Config[i].valid) {
                Ad9833ConfNode = &Ad9833Config[i];
                break;
            }
        }
    }
    return Ad9833ConfNode;
}

#define TRANSIENT_PAUSE_MS 0
bool ad9833_write(uint8_t num, uint16_t word) {
    bool res = false;
    LOG_INFO(AD9833, "%u Write Word:0x%04x", num, word);
    const Ad9833Config_t* ConfNode = Ad9833GetConfNode(num);
    if(ConfNode) {
        gpio_set_logic_level(ConfNode->chip_select.byte, 1);
        wait_ms(TRANSIENT_PAUSE_MS);
        gpio_set_logic_level(ConfNode->chip_select.byte, 0);
        wait_ms(TRANSIENT_PAUSE_MS);
        res = spi_write_word(ConfNode->spi_num, word);
        if(res) {
            LOG_DEBUG(AD9833, "SpiWriteOk");
        } else {
            LOG_ERROR(AD9833, "SpiWriteErr");
        }
        wait_ms(TRANSIENT_PAUSE_MS);
        gpio_set_logic_level(ConfNode->chip_select.byte, 1);
        wait_ms(TRANSIENT_PAUSE_MS);
    }
    return res;
}

Ad9833Write_t PhaseNum2ContentCode(RegNum_t reg_num) {
    Ad9833Write_t content = AD_WRITE_UNDEF;
    switch(reg_num) {
    case REG_NUM_0:
        content = AD_WRITE_PHASE0;
        break;
    case REG_NUM_1:
        content = AD_WRITE_PHASE1;
        break;
    default:
        break;
    }
    return content;
}

bool ad9833_reset(uint8_t num) {
    bool res = false;
    LOG_WARNING(AD9833, "%u ReSet", num);
    const Ad9833Config_t* ConfNode = Ad9833GetConfNode(num);
    if(ConfNode) {
        Ad9833Handle_t* Node = Ad9833GetNode(num);
        if(Node) {
            Node->Reg.word = 0;
            Node->Reg.reset = RST_REG;

            res = ad9833_write(num, Node->Reg.word);
            if(res) {
                LOG_INFO(AD9833, "WriteOk");
            } else {
                LOG_ERROR(AD9833, "WriteErr");
            }
        }
    }
    return res;
}

bool ad9833_set_form(uint8_t num, SignalForm_t signal_form) {
    bool res = false;
    LOG_INFO(AD9833, "%u SetSignal Form %s", num, SignalFormToStr(signal_form));
    const Ad9833Config_t* ConfNode = Ad9833GetConfNode(num);
    if(ConfNode) {
        Ad9833Handle_t* Node = Ad9833GetNode(num);
        if(Node) {
            Node->signal_form = signal_form;

            Node->Reg.word = 0;
            Node->Reg.cmd = AD_WRITE_CTRL;
            Node->Reg.reset = RST_DISABLE;
            Node->Reg.sleep12 = DAC_ACTIVE;
            Node->Reg.sleep1 = MCLK_ENABLED;

            /*Table 15. Outputs from the VOUT Pin*/
            switch(signal_form) {
            case SIGNAL_FORM_SQUARE: {
                Node->Reg.div2 = DIV2_MSB;
                Node->Reg.mode = SIGNAL_SIN;
                Node->Reg.opbiten = DAC_DISCONNECTED; /*DAC is connected to VOUT*/
            } break;
            case SIGNAL_FORM_SINUSOIDAL: {
                Node->Reg.opbiten = DAC_CONNECTED; /*DAC is connected to VOUT*/
                Node->Reg.mode = SIGNAL_SIN;
            } break;
            case SIGNAL_FORM_TRIANGULAR: {
                Node->Reg.opbiten = DAC_CONNECTED; /*DAC is connected to VOUT*/
                Node->Reg.mode = SIGNAL_NOT_SIN;
            } break;
            case SIGNAL_FORM_CONST: {
                Node->Reg.mode = SIGNAL_NOT_SIN;
            } break;
            default: {
            } break;
            }
            res = ad9833_write(num, Node->Reg.word);
            if(res) {
                LOG_INFO(AD9833, "WriteOk");
            } else {
                LOG_ERROR(AD9833, "WriteErr");
            }
        }
    }
    return res;
}

bool ad9833_set_phase(uint8_t num, RegNum_t reg_num, double phase) {
    bool res = false;
    LOG_INFO(AD9833, "%u SetPhase%u %f Rad", num, reg_num, phase);
    const Ad9833Config_t* ConfNode = Ad9833GetConfNode(num);
    if(ConfNode) {
        Ad9833Handle_t* Node = Ad9833GetNode(num);
        if(Node) {
            LOG_INFO(AD9833, "%u SetPhase%uCode 0x%08x", num, reg_num, Node->Regs[reg_num].phase);
            Node->Reg.phase_register_select = PhaseNum2ContentCode(reg_num);
            Node->Regs[reg_num].phase = (phase * ((double)TWO_POW_12)) / ((double)2.0 * M_PI);
            Node->Reg.phase_register_select = MASK_12BIT & Node->Regs[reg_num].phase;
            res = ad9833_write(num, Node->Reg.word);
        }
    }
    return res;
}

Ad9833Write_t FreqNum2ContentCode(RegNum_t reg_num) {
    Ad9833Write_t content = AD_WRITE_UNDEF;
    switch(reg_num) {
    case REG_NUM_0:
        content = AD_WRITE_FREQ0;
        break;
    case REG_NUM_1:
        content = AD_WRITE_FREQ1;
        break;
    default:
        break;
    }
    return content;
}

bool ad9833_set_freq(uint8_t num, RegNum_t reg_num, double freq_hz) {
    bool res = false;
    LOG_WARNING(AD9833, "%u SetFreq%u %f Hz", num, reg_num, freq_hz);
    const Ad9833Config_t* ConfNode = Ad9833GetConfNode(num);
    if(ConfNode) {
        Ad9833Handle_t* Node = Ad9833GetNode(num);
        if(Node) {
            Node->Regs[reg_num].freq = (freq_hz * ((double)TWO_POW_28)) / ((double)FMCLK_HZ);
            LOG_INFO(AD9833, "%u SetFreq%uCode 0x%08x", num, reg_num, Node->Regs[reg_num].freq);
#if 1
            Node->Reg.word = 0;
            Node->Reg.b28 = 1;
            res = ad9833_write(num, Node->Reg.word);
#endif

            /*Frequency Register N LSB*/
            Node->Reg.word = 0;
            Node->Reg.content = FreqNum2ContentCode(reg_num);
            Node->Reg.freq_code14bit = MASK_14BIT & Node->Regs[reg_num].freq;
            res = ad9833_write(num, Node->Reg.word);

            /*Frequency Register N MSB*/
            Node->Reg.word = 0;
            Node->Reg.content = FreqNum2ContentCode(reg_num);
            Node->Reg.freq_code14bit = (MASK_14BIT & (Node->Regs[reg_num].freq >> 14));
            res = ad9833_write(num, Node->Reg.word);
#if 1
            Node->Reg.word = 0;
            Node->Reg.b28 = 1;
            Node->Reg.reset = 0;
            res = ad9833_write(num, Node->Reg.word);
#endif
            res = ad9833_set_form(num, Node->signal_form);
        }
    }
    return res;
}

bool ad9833_set_signal(uint8_t num, SignalForm_t signal_form, double freq, double phase) {
    bool res = false;
    LOG_WARNING(AD9833, "%u SetSignal Form %s Freq %f Hz Phase %f", num, SignalFormToStr(signal_form), freq, phase);
    const Ad9833Config_t* ConfNode = Ad9833GetConfNode(num);
    if(ConfNode) {
        Ad9833Handle_t* Node = Ad9833GetNode(num);
        if(Node) {
            res = ad9833_set_freq(num, REG_NUM_0, freq);
            res = ad9833_set_freq(num, REG_NUM_1, freq);

            res = ad9833_set_phase(num, REG_NUM_0, phase);
            res = ad9833_set_phase(num, REG_NUM_1, phase);

            res = ad9833_set_form(num, signal_form);
        }
    }
    return res;
}

bool ad9833_gpio_init_ll(const Ad9833Config_t* const ConfNode) {
    bool res = false;
    if(ConfNode) {
        res = true;
        LOG_INFO(AD9833, "GpioInit %s", GpioPadToStr(ConfNode->chip_select.byte));
        res = gpio_set_dir(ConfNode->chip_select.byte, GPIO_DIR_INOUT) && res;
        res = gpio_set_pull(ConfNode->chip_select.byte, GPIO__PULL_AIR) && res;
        res = gpio_set_logic_level(ConfNode->chip_select.byte, 1) && res;
    }
    return res;
}

bool ad9833_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(AD9833, "Init %u", num);
    const Ad9833Config_t* ConfNode = Ad9833GetConfNode(num);
    if(ConfNode) {
        res = ad9833_reset(num);
        // res = ad9833_gpio_init_ll(ConfNode);
        res = ad9833_set_signal(num, ConfNode->signal_form, ConfNode->freq_hz, ConfNode->phase);
        if(res) {
            LOG_INFO(AD9833, "SetSignalOk %u", num);
        } else {
            LOG_ERROR(AD9833, "SetSignalErr %u", num);
        }
    }
    return res;
}

bool ad9833_init(void) {
    bool res = false;
    uint8_t i = 0;
    uint8_t ok_cnt = 0;
    uint8_t cnt = ad9833_get_cnt();
    LOG_WARNING(AD9833, "Init Cnt %u", cnt);
    for(i = 0; i <= cnt; i++) {
        res = ad9833_init_one(i);
        if(res) {
            ok_cnt++;
        }
    }

    if(cnt == ok_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
