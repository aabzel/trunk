#include "clock.h"

//#include "clock_mcal.h"

#include "log.h"
#include "microcontroller_const.h"
#include "std_includes.h"
#include "time_mcal.h"
#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif /**/
#include "clock_custom.h"
//#include "c_defines_generated.h"

#ifdef HAS_PLL_CALC
#include "pll_calc.h"
#endif

#ifdef HAS_SYSTICK
#include "systick_mcal.h"
#endif /**/

/*calibrate*/
#if 0
uint64_t pause_1ms(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 1397; in++) {
        cnt++;
    }
    return cnt;
}

uint64_t pause_1us(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 29700; in++) {
        cnt++;
    }
    return cnt;
}
#endif

uint64_t sw_pause_ms(uint32_t delay_in_ms) {
    uint64_t cnt = 0;
    // LOG_INFO(SYS, "SwPause %u ms", delay_in_ms); del
    uint32_t t = 0;
    for(t = 0; t < delay_in_ms; t++) {
        cnt += pause_1ms();
    }
    return cnt;
}

uint32_t clock_core_freq_get(void) {
    crm_clocks_freq_type clocks_struct = {0};
    crm_clocks_freq_get(&clocks_struct);
    return clocks_struct.sclk_freq;
}

#ifdef HAS_AT32F43X
crm_pll_fr_type ClockFrToArtery(uint32_t fr) {
    crm_pll_fr_type pll_fr = CRM_PLL_FR_32;
    switch(fr) {
    case 1:
        pll_fr = CRM_PLL_FR_1;
        break;
    case 2:
        pll_fr = CRM_PLL_FR_2;
        break;
    case 4:
        pll_fr = CRM_PLL_FR_4;
        break;
    case 8:
        pll_fr = CRM_PLL_FR_8;
        break;
    case 16:
        pll_fr = CRM_PLL_FR_16;
        break;
    case 32:
        pll_fr = CRM_PLL_FR_32;
        break;
    }

    return pll_fr;
}
#endif

#ifdef HAS_PLL_CALC
#ifdef HAS_AT32F43X
/**
 * @brief  select ldo output voltage.
 * @param  val: set the ldo output voltage.
 *         this parameter can be one of the following values:
 *         - PWC_LDO_OUTPUT_1V3: system clock up to 288MHz.
 *         - PWC_LDO_OUTPUT_1V2: system clock up to 240MHz.
 *         - PWC_LDO_OUTPUT_1V1: system clock up to 192MHz.
 *         - PWC_LDO_OUTPUT_1V0: system clock up to 144MHz.
 * @note   useage limited.
 *         PWC_LDO_OUTPUT_1V3: operation temperature range -40~85 degree, VDD must over 3.0V.
 */
static uint32_t ClockCoreFreqToLodVolt(uint32_t core_freq_hz) {
    uint32_t ldo_output_voltage = PWC_LDO_OUTPUT_1V0;
    if(288000000 <= core_freq_hz) {
        ldo_output_voltage = PWC_LDO_OUTPUT_1V3;
    } else {
        if(240000000 <= core_freq_hz) {
            ldo_output_voltage = PWC_LDO_OUTPUT_1V2;
        } else {
            if(192000000 <= core_freq_hz) {
                ldo_output_voltage = PWC_LDO_OUTPUT_1V1;
            } else {
                ldo_output_voltage = PWC_LDO_OUTPUT_1V0;
            }
        }
    }
    return ldo_output_voltage;
}
#endif
#endif

#ifdef HAS_PLL_CALC
#ifdef HAS_AT32F413X
static crm_pll_clock_source_type At32f413DivToSrcType(uint32_t pllhexdiv) {
    crm_pll_clock_source_type pll_clock_source_type = CRM_PLL_SOURCE_HEXT;
    switch(pllhexdiv) {
    case 1:
        pll_clock_source_type = CRM_PLL_SOURCE_HEXT;
        break;
    case 2:
        pll_clock_source_type = CRM_PLL_SOURCE_HEXT_DIV;
        break;
    default:
        break;
    }
    return pll_clock_source_type;
}

static crm_pll_mult_type At32f413MultToSrcType(uint32_t pllmult) {
    crm_pll_mult_type mult_value = CRM_PLL_MULT_2;
    switch(pllmult) {
    case 2:
        mult_value = CRM_PLL_MULT_2;
        break;
    case 3:
        mult_value = CRM_PLL_MULT_3;
        break;
    case 4:
        mult_value = CRM_PLL_MULT_4;
        break;
    case 5:
        mult_value = CRM_PLL_MULT_5;
        break;
    case 6:
        mult_value = CRM_PLL_MULT_6;
        break; // pll multiplication factor 6
    case 7:
        mult_value = CRM_PLL_MULT_7;
        break; // pll multiplication factor 7
    case 8:
        mult_value = CRM_PLL_MULT_8;
        break; // pll multiplication factor 8
    case 9:
        mult_value = CRM_PLL_MULT_9;
        break; // pll multiplication factor 9
    case 10:
        mult_value = CRM_PLL_MULT_10;
        break; // pll multiplication factor 10
    case 11:
        mult_value = CRM_PLL_MULT_11;
        break; // pll multiplication factor 11
    case 12:
        mult_value = CRM_PLL_MULT_12;
        break; // pll multiplication factor 12
    case 13:
        mult_value = CRM_PLL_MULT_13;
        break; // pll multiplication factor 13
    case 14:
        mult_value = CRM_PLL_MULT_14;
        break; // pll multiplication factor 14
    case 15:
        mult_value = CRM_PLL_MULT_15;
        break; // pll multiplication factor 15
    case 16:
        mult_value = CRM_PLL_MULT_16;
        break; // pll multiplication factor 16
    case 17:
        mult_value = CRM_PLL_MULT_17;
        break; // pll multiplication factor 17
    case 18:
        mult_value = CRM_PLL_MULT_18;
        break; // pll multiplication factor 18
    case 19:
        mult_value = CRM_PLL_MULT_19;
        break; // pll multiplication factor 19
    case 20:
        mult_value = CRM_PLL_MULT_20;
        break; // pll multiplication factor 20
    case 21:
        mult_value = CRM_PLL_MULT_21;
        break; // pll multiplication factor 21
    case 22:
        mult_value = CRM_PLL_MULT_22;
        break; // pll multiplication factor 22
    case 23:
        mult_value = CRM_PLL_MULT_23;
        break; // pll multiplication factor 23
    case 24:
        mult_value = CRM_PLL_MULT_24;
        break; // pll multiplication factor 24
    case 25:
        mult_value = CRM_PLL_MULT_25;
        break; // pll multiplication factor 25
    case 26:
        mult_value = CRM_PLL_MULT_26;
        break; // pll multiplication factor 26
    case 27:
        mult_value = CRM_PLL_MULT_27;
        break; // pll multiplication factor 27
    case 28:
        mult_value = CRM_PLL_MULT_28;
        break; // pll multiplication factor 28
    case 29:
        mult_value = CRM_PLL_MULT_29;
        break; // pll multiplication factor 29
    case 30:
        mult_value = CRM_PLL_MULT_30;
        break; // pll multiplication factor 30
    case 31:
        mult_value = CRM_PLL_MULT_31;
        break; // pll multiplication factor 31
    case 32:
        mult_value = CRM_PLL_MULT_32;
        break; // pll multiplication factor 32
    case 33:
        mult_value = CRM_PLL_MULT_33;
        break; // pll multiplication factor 33
    case 34:
        mult_value = CRM_PLL_MULT_34;
        break; // pll multiplication factor 34
    case 35:
        mult_value = CRM_PLL_MULT_35;
        break; // pll multiplication factor 35
    case 36:
        mult_value = CRM_PLL_MULT_36;
        break; // pll multiplication factor 36
    case 37:
        mult_value = CRM_PLL_MULT_37;
        break; // pll multiplication factor 37
    case 38:
        mult_value = CRM_PLL_MULT_38;
        break; // pll multiplication factor 38
    case 39:
        mult_value = CRM_PLL_MULT_39;
        break; // pll multiplication factor 39
    case 40:
        mult_value = CRM_PLL_MULT_40;
        break; // pll multiplication factor 40
    case 41:
        mult_value = CRM_PLL_MULT_41;
        break; // pll multiplication factor 41
    case 42:
        mult_value = CRM_PLL_MULT_42;
        break; // pll multiplication factor 42
    case 43:
        mult_value = CRM_PLL_MULT_43;
        break; // pll multiplication factor 43
    case 44:
        mult_value = CRM_PLL_MULT_44;
        break; // pll multiplication factor 44
    case 45:
        mult_value = CRM_PLL_MULT_45;
        break; // pll multiplication factor 45
    case 46:
        mult_value = CRM_PLL_MULT_46;
        break; // pll multiplication factor 46
    case 47:
        mult_value = CRM_PLL_MULT_47;
        break; // pll multiplication factor 47
    case 48:
        mult_value = CRM_PLL_MULT_48;
        break; // pll multiplication factor 48
    case 49:
        mult_value = CRM_PLL_MULT_49;
        break; // pll multiplication factor 49
    case 50:
        mult_value = CRM_PLL_MULT_50;
        break; // pll multiplication factor 50
    case 51:
        mult_value = CRM_PLL_MULT_51;
        break; // pll multiplication factor 51
    case 52:
        mult_value = CRM_PLL_MULT_52;
        break; // pll multiplication factor 52
    case 53:
        mult_value = CRM_PLL_MULT_53;
        break; // pll multiplication factor 53
    case 54:
        mult_value = CRM_PLL_MULT_54;
        break; // pll multiplication factor 54
    case 55:
        mult_value = CRM_PLL_MULT_55;
        break; // pll multiplication factor 55
    case 56:
        mult_value = CRM_PLL_MULT_56;
        break; // pll multiplication factor 56
    case 57:
        mult_value = CRM_PLL_MULT_57;
        break; // pll multiplication factor 57
    case 58:
        mult_value = CRM_PLL_MULT_58;
        break; // pll multiplication factor 58
    case 59:
        mult_value = CRM_PLL_MULT_59;
        break; // pll multiplication factor 59
    case 60:
        mult_value = CRM_PLL_MULT_60;
        break; // pll multiplication factor 60
    case 61:
        mult_value = CRM_PLL_MULT_61;
        break; // pll multiplication factor 61
    case 62:
        mult_value = CRM_PLL_MULT_62;
        break; // pll multiplication factor 62
    case 63:
        mult_value = CRM_PLL_MULT_63;
        break; // pll multiplication factor 63
    case 64:
        mult_value = CRM_PLL_MULT_64;
        break; // pll multiplication factor 64

    default:
        break;
    }
    return mult_value;
}

static crm_pll_output_range_type At32f413MultToRangeType(uint32_t core_freq_hz) {
    crm_pll_output_range_type range_type = CRM_PLL_OUTPUT_RANGE_LE72MHZ;
    if(core_freq_hz < 72000000) {
        range_type = CRM_PLL_OUTPUT_RANGE_LE72MHZ;
    } else {
        range_type = CRM_PLL_OUTPUT_RANGE_GT72MHZ;
    }
    return range_type;
}

static bool clock_f413_pll_set(const PllArtety_t* const PllConfig) {
    bool res = true;
    /* reset crm */
    crm_reset();

    /* enable hext */
    crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

    /* wait till hext is ready */
    while(crm_hext_stable_wait() == ERROR) {
    }

    crm_pll_clock_source_type clock_source = At32f413DivToSrcType(PllConfig->pllhexdiv);
    crm_pll_mult_type mult_value = At32f413MultToSrcType(PllConfig->pllmult);
    crm_pll_output_range_type pll_range = At32f413MultToRangeType(PllConfig->core_freq_hz);

    /* config pll clock resource */
    crm_pll_config(clock_source, mult_value, pll_range);

    /* enable pll */
    crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

    /* wait till pll is ready */
    while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET) {
    }

    /* config ahbclk */
    crm_ahb_div_set(CRM_AHB_DIV_1);

    /* config apb2clk */
    crm_apb2_div_set(CRM_APB2_DIV_2);

    /* config apb1clk */
    crm_apb1_div_set(CRM_APB1_DIV_2);

    /* select pll as system clock source */
    crm_sysclk_switch(CRM_SCLK_PLL);

    /* wait till pll is used as system clock source */
    while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL) {
    }

    /* update system_core_clock global variable */
    system_core_clock_update();

    return res;
}
#endif
#endif

#ifdef HAS_PLL_CALC
#ifdef HAS_AT32F43X
static bool clock_f43x_pll_set(const PllArtety_t* const PllConfig) {
    bool res = false;
    if(PllConfig) {
        /* reset crm */
        crm_reset();

        /* enable pwc periph clock */
        crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);

        /* config ldo voltage */
        uint32_t ldo_output_voltage = ClockCoreFreqToLodVolt(PllConfig->core_freq_hz);
        pwc_ldo_output_voltage_set(ldo_output_voltage);

        /* set the flash clock divider */
        flash_clock_divider_set(FLASH_CLOCK_DIV_2);

        /* enable hext */
        crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

        /* wait till hext is ready */
        while(crm_hext_stable_wait() == ERROR) {
        }

        /* config pll clock resource
         common frequency config list: pll source selected  hick or hext(8mhz)
         _________________________________________________________________________________________________
         |        |         |         |         |         |         |         |         |        |        |
         |pll(mhz)|   288   |   252   |   216   |   192   |   180   |   144   |   108   |   72   |   36   |
         |________|_________|_________|_________|_________|_________|_________|_________|_________________|
         |        |         |         |         |         |         |         |         |        |        |
         |pll_ns  |   144   |   126   |   108   |   96    |   90    |   72    |   108   |   72   |   72   |
         |        |         |         |         |         |         |         |         |        |        |
         |pll_ms  |   1     |   1     |   1     |   1     |   1     |   1     |   1     |   1    |   1    |
         |        |         |         |         |         |         |         |         |        |        |
         |pll_fr  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_8  |   FR_8 |   FR_16|
         |________|_________|_________|_________|_________|_________|_________|_________|________|________|

         if pll clock source selects hext with other frequency values, or configure pll to other
         frequency values, please use the at32 new clock  configuration tool for configuration.  */

        crm_pll_fr_type pll_fr = ClockFrToArtery(PllConfig->fr);

        crm_pll_config(CRM_PLL_SOURCE_HEXT, (uint16_t)PllConfig->ns, (uint16_t)PllConfig->ms, pll_fr);

        /* enable pll */
        crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

        /* wait till pll is ready */
        while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET) {
        }

        /* config ahbclk */
        crm_ahb_div_set(CRM_AHB_DIV_1);

        /* config apb2clk */
        crm_apb2_div_set(CRM_APB2_DIV_2);

        /* config apb1clk */
        crm_apb1_div_set(CRM_APB1_DIV_4);

        /* enable auto step mode */
        // crm_auto_step_mode_enable(TRUE);

        /* select pll as system clock source */
        crm_sysclk_switch(CRM_SCLK_PLL);

        /* wait till pll is used as system clock source */
        while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL) {
        }

        /* disable auto step mode */
        // crm_auto_step_mode_enable(FALSE);

        /* update system_core_clock global variable */
        system_core_clock_update();
        res = true;
    }
    return res;
}
#endif // HAS_AT32F43X
#endif // HAS_PLL_CALC

#ifdef HAS_PLL_CALC
#ifdef HAS_CLOCK_RUN_TIME_CTRL
static bool clock_pll_set(const PllArtety_t* const PllConfig) {
    bool res = false;
#ifdef HAS_AT32F413
    res = clock_f413_pll_set(PllConfig);
#endif // HAS_AT32F413

#ifdef HAS_AT32F43X
    res = clock_f43x_pll_set(PllConfig);
#endif // HAS_AT32F43X
    return res;
}
#endif // HAS_CLOCK_RUN_TIME_CTRL
#endif // HAS_PLL_CALC

#ifdef HAS_CLOCK_RUN_TIME_CTRL
bool clock_core_freq_set(uint32_t core_freq_hz) {
    bool res = false;
    LOG_WARNING(SYS, "Set,Freq:%uHz", core_freq_hz);
#ifdef HAS_PLL_CALC
    PllArtety_t PllArtety = {0};
    PllArtety.core_freq_hz = core_freq_hz;
    res = pll_calc_artery(ClockConfig.hf_source, core_freq_hz, &PllArtety);
#endif // HAS_PLL_CALC
    if(res) {
#ifdef HAS_PLL_CALC_DIAG
        LOG_INFO(SYS, "Pll:%s", PllArtetyToStr(&PllArtety));
#endif

#ifdef HAS_PLL_CALC
        res = clock_pll_set(&PllArtety);
        if(res) {
            LOG_INFO(SYS, "SetOk,Freq:%u Hz", core_freq_hz);
        } else {
            LOG_ERROR(SYS, "SetErr,Freq:%u Hz", core_freq_hz);
        }
#endif // HAS_PLL_CALC
    } else {
        LOG_ERROR(SYS, "impossible");
    }
    return res;
}
#endif
