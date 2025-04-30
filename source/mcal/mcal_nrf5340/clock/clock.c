#include "clock.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "clock_config.h"
#include "clock_custom.h"
#include "clock_isr.h"
#include "clock_types.h"
#include "hal_nrfx_diag.h"
#include "log.h"
#include "nrf_clock.h"
#include "nrf_gpio.h"
#include "nrf_reset.h"
#ifdef HAS_I2S
#include "i2s_nrf_const.h"
#endif

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif /*HAS_TIMER*/

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_SYSTICK
#include "systick_general.h"
#endif /**/

const ClockInfo_t ClockInfo[4] = {
    {
        .domain_nrf = NRF_CLOCK_DOMAIN_LFCLK,
        .domain_num = CLK_DOMAIN_LOW_FREQ,
        .name = "LFCLK",
    },
    {
        .domain_nrf = NRF_CLOCK_DOMAIN_HFCLK,
        .domain_num = CLK_DOMAIN_HI_FREQ,
        .name = "HFCLK",
    },
    {
        .domain_nrf = NRF_CLOCK_DOMAIN_HFCLK192M,
        .domain_num = CLK_DOMAIN_EXTRA_HI_FREQ,
        .name = "HFCLK192M",
    },
    {
        .domain_nrf = NRF_CLOCK_DOMAIN_HFCLKAUDIO,
        .domain_num = CLK_DOMAIN_AUDIO_FREQ,
        .name = "HFCLKAUDIO",
    },
};

/*TODO calibrate for nrf5340*/
uint64_t pause_1ms(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 1397; in++) {
        cnt++;
    }
    return cnt;
}

/*TODO calibrate for nrf5340*/
uint64_t pause_1us(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 29700; in++) {
        cnt++;
    }
    return cnt;
}

nrf_clock_domain_t ClockDomainToNrfxDomain(ClockDomain_t domain) {
    nrf_clock_domain_t nrfx_domain = 0;
    switch((uint8_t)domain) {
    case CLK_DOMAIN_HI_FREQ: {
        nrfx_domain = NRF_CLOCK_DOMAIN_HFCLK;
    } break;
    case CLK_DOMAIN_LOW_FREQ: {
        nrfx_domain = NRF_CLOCK_DOMAIN_LFCLK;
    } break;
    case CLK_DOMAIN_AUDIO_FREQ: {
        nrfx_domain = NRF_CLOCK_DOMAIN_HFCLKAUDIO;
    } break;
    case CLK_DOMAIN_EXTRA_HI_FREQ: {
        nrfx_domain = NRF_CLOCK_DOMAIN_HFCLK192M;
    } break;
    }
    return nrfx_domain;
}

ClockDomain_t ClockNrfDomain2Domain(nrf_clock_domain_t nrf_clock_domain) {
    ClockDomain_t clock_domain = CLK_DOMAIN_UNDEF;
    switch(nrf_clock_domain) {
    case NRF_CLOCK_DOMAIN_LFCLK:
        clock_domain = CLK_DOMAIN_LOW_FREQ;
        break;
    case NRF_CLOCK_DOMAIN_HFCLK:
        clock_domain = CLK_DOMAIN_HI_FREQ;
        break;
    case NRF_CLOCK_DOMAIN_HFCLK192M:
        clock_domain = CLK_DOMAIN_EXTRA_HI_FREQ;
        break;
    case NRF_CLOCK_DOMAIN_HFCLKAUDIO:
        clock_domain = CLK_DOMAIN_AUDIO_FREQ;
        break;
    }
    return clock_domain;
}

bool clock_control(ClockDomain_t domain, bool on_off) {
    bool res = false;
    nrf_clock_domain_t nrfx_domain = ClockDomainToNrfxDomain(domain);
    if(on_off) {
        nrfx_clock_start(nrfx_domain);
        res = true;
    } else {
        nrfx_clock_stop(nrfx_domain);
        res = true;
    }
    return res;
}

nrf_clock_hfclk_div_t ClockDividerToNrfDivider(uint8_t divider) {
    nrf_clock_hfclk_div_t nrf_divider = 0;
    switch(divider) {
    case 1:
        nrf_divider = NRF_CLOCK_HFCLK_DIV_1;
        break; /**< Divide HFCLK/HFCLK192M by 1 */
    case 2:
        nrf_divider = NRF_CLOCK_HFCLK_DIV_2;
        break; /**< Divide HFCLK/HFCLK192M by 1 */
    case 4:
        nrf_divider = NRF_CLOCK_HFCLK_DIV_4;
        break; /**< Divide HFCLK192M by 4 */
    default:
        nrf_divider = NRF_CLOCK_HFCLK_DIV_1;
        break;
    }
    return nrf_divider;
}

uint32_t NrfDiv2Div(nrf_clock_hfclk_div_t nrf_clock_div) {
    uint32_t div = 1;
    switch(nrf_clock_div) {
    case NRF_CLOCK_HFCLK_DIV_1: {
        div = 1;
    } break;
    case NRF_CLOCK_HFCLK_DIV_2: {
        div = 2;
    } break;
    case NRF_CLOCK_HFCLK_DIV_4: {
        div = 4;
    } break;
    }
    return div;
}

bool clock_low_freq_init(void) {
    bool res = true;
    LOG_WARNING(CLK, "LowClk Init..");
    nrf_clock_lf_src_set(NRF_CLOCK_S, NRF_CLOCK_LFCLK_Xtal);
    nrfx_clock_lfclk_start();
    return res;
}

bool clock_nrfx_sleep(void) {
    bool res = true;

    nrfx_err_t ret = NRFX_ERROR_NULL;
    ret = nrfx_clock_divider_set(NRF_CLOCK_DOMAIN_LFCLK, NRF_CLOCK_HFCLK_DIV_2);
    if(NRFX_SUCCESS == ret) {
        LOG_INFO(CLK, "LFCLK DivSetOk");
    } else {
        LOG_ERROR(CLK, "LFCLK DivSetErr");
    }
    ret = nrfx_clock_divider_set(NRF_CLOCK_DOMAIN_HFCLK, NRF_CLOCK_HFCLK_DIV_2);
    if(NRFX_SUCCESS == ret) {
        LOG_INFO(CLK, "HFCLK DivSetOk");
    } else {
        LOG_ERROR(CLK, "HFCLK DivSetErr");
    }

    ret = nrfx_clock_divider_set(NRF_CLOCK_DOMAIN_HFCLK192M, NRF_CLOCK_HFCLK_DIV_4);
    if(NRFX_SUCCESS == ret) {
        LOG_INFO(CLK, "HFCLK192M DivSetOk");
    } else {
        LOG_ERROR(CLK, "HFCLK192M DivSetErr");
    }

    ret = nrfx_clock_divider_set(NRF_CLOCK_DOMAIN_HFCLKAUDIO, NRF_CLOCK_HFCLK_DIV_2);
    if(NRFX_SUCCESS == ret) {
        LOG_INFO(CLK, "HFCLKAUDIO DivSetOk");
    } else {
        LOG_ERROR(CLK, "HFCLKAUDIO DivSetErr");
    }
    // nrfx_clock_stop(NRF_CLOCK_DOMAIN_HFCLKAUDIO);
    // nrfx_clock_stop(NRF_CLOCK_DOMAIN_HFCLK192M);
    return res;
}

bool clock_init(void) {
    LOG_WARNING(CLK, "Init..");
    bool res = false;
#ifdef HAS_I2S
    res = clock_audio_freq_set(12288000);
    res = clock_control(CLK_DOMAIN_AUDIO_FREQ, true);
#endif

#ifdef HAS_CORE_APP
    nrf_reset_network_force_off(NRF_RESET, false);
#endif
#ifdef HAS_CORE_NET
    // nrf_clock_hfclk_div_set(NRF_CLOCK, NRF_CLOCK_HFCLK_DIV_1);
#endif

#ifdef HAS_NORTOS
    LOG_WARNING(CLK, "sizeof(NrfxClkSrc_t) %u", sizeof(NrfxClkSrc_t));
    if(ClockInstance.init_done) {
        LOG_WARNING(CLK, "UnInit");
        nrfx_clock_uninit();
    }

    ClockInstance.event_handler = NrfxClockEventHandler;
    nrfx_err_t ret = nrfx_clock_init(ClockInstance.event_handler);
    if(NRFX_SUCCESS == ret) {
        LOG_INFO(CLK, "InitOk");
        ClockInstance.init_done = true;
        LOG_WARNING(CLK, "SetExternalXtall");
        nrf_clock_hf_src_set(NRF_CLOCK_S, NRF_CLOCK_HFCLK_HIGH_ACCURACY);
        LOG_WARNING(CLK, "StartXtall");
        nrf_clock_hfclk_div_set(NRF_CLOCK_S, NRF_CLOCK_HFCLK_DIV_1);
        nrfx_clock_hfclk_start();

        res = clock_low_freq_init();
        res = true;
    } else {
        LOG_ERROR(CLK, "InitErr %u=%s", ret, HalStatus2Str(ret));
    }
#endif

    return res;
}

uint32_t NrfClockLfClk2Hz(nrf_clock_lfclk_t lf_clk_src) {
    uint32_t freq_hz = 0;
    switch(lf_clk_src) {
#if defined(CLOCK_LFCLKSRC_SRC_LFULP) || defined(__NRFX_DOXYGEN__)
    case NRF_CLOCK_LFCLK_LFULP:
        freq_hz = 32000;
        break; /**< Internal 32 kHz Ultra-low power oscillator. */
#endif
#if defined(CLOCK_LFCLKSRC_SRC_RC) || defined(__NRFX_DOXYGEN__)
    case NRF_CLOCK_LFCLK_RC:
        freq_hz = 32000;
        break; /**< Internal 32 kHz RC oscillator. */
#else
    case NRF_CLOCK_LFCLK_RC:
        freq_hz = 32000;
        break; /**< Internal 32 kHz RC oscillator. */
#endif
#if defined(CLOCK_LFCLKSRC_SRC_Xtal) || defined(__NRFX_DOXYGEN__)
    case NRF_CLOCK_LFCLK_Xtal:
        freq_hz = 32000;
        break; /**< External 32 kHz crystal. */
#else
    case NRF_CLOCK_LFCLK_Xtal:
        freq_hz = 32000;
        break; /**< External 32 kHz crystal. */
#endif

#if defined(CLOCK_LFCLKSRC_SRC_Synth) || defined(__NRFX_DOXYGEN__)
    case NRF_CLOCK_LFCLK_Synth:
        freq_hz = 32000;
        break; /**< Internal 32 kHz synthesizer from HFCLK system clock. */
#endif
#if defined(NRF_CLOCK_USE_EXTERNAL_LFCLK_SOURCES) || defined(__NRFX_DOXYGEN__)

    case NRF_CLOCK_LFCLK_Xtal_Low_Swing:
        freq_hz = 32000;
        break;

    case NRF_CLOCK_LFCLK_Xtal_Full_Swing:
        freq_hz = 0;
        break;
#endif // defined(NRF_CLOCK_USE_EXTERNAL_LFCLK_SOURCES) || defined(__NRFX_DOXYGEN__)
    }
    return freq_hz;
}

ClockSource_t NrfClkHiFreq2ClkSrc(nrf_clock_hfclk_t hfclk) {
    ClockSource_t src = CLOCK_SRC_UNDEF;
    switch(hfclk) {
    case NRF_CLOCK_HFCLK_LOW_ACCURACY:
        src = CLOCK_SRC_INTERNAL;
        break; /**< Internal 16 MHz RC oscillator. */
    case NRF_CLOCK_HFCLK_HIGH_ACCURACY:
        src = CLOCK_SRC_EXTERNAL;
        break; /**< External 32 MHz crystal oscillator. */
    default:
        src = CLOCK_SRC_UNDEF;
        break;
    }
    return src;
}

ClockSource_t NrfClkLoFreq2ClkSrc(nrf_clock_lfclk_t lfclk) {
    ClockSource_t src = CLOCK_SRC_UNDEF;
    switch(lfclk) {
    case NRF_CLOCK_LFCLK_LFULP:
        src = CLOCK_SRC_INTERNAL;
        break; /**< Internal 32 kHz Ultra-low power oscillator. */
    case NRF_CLOCK_LFCLK_RC:
        src = CLOCK_SRC_INTERNAL;
        break; /**< Internal 32 kHz RC oscillator. */
    case NRF_CLOCK_LFCLK_Xtal:
        src = CLOCK_SRC_EXTERNAL;
        break; /**< External 32 kHz crystal. */
    default:
        src = CLOCK_SRC_UNDEF;
        break;
    }
    return src;
}

uint32_t NrfClockHfClk2Hz(nrf_clock_hfclk_t clk_src) {
    uint32_t freq_hz = 0;
    switch(clk_src) {
    case NRF_CLOCK_HFCLK_LOW_ACCURACY: {
        freq_hz = 16000000;
    } break;
    case NRF_CLOCK_HFCLK_HIGH_ACCURACY: {
        freq_hz = 32000000;
    } break;
    default: {
        LOG_DEBUG(CLK, "UndefClkSrc:%u", clk_src);
        freq_hz = 1;
    } break;
    }
    return freq_hz;
}

ClockSource_t clock_nrf_src_get(nrf_clock_domain_t domain_nrf) {
    ClockSource_t src = CLOCK_SRC_UNDEF;

    NrfxClkSrc_t NrfxClkSrc;
    NrfxClkSrc.byte = 0;
    bool is_running = nrfx_clock_is_running(domain_nrf, (void*)&NrfxClkSrc.byte);
    (void)is_running;

    switch((uint8_t)domain_nrf) {
    case NRF_CLOCK_DOMAIN_LFCLK: {
        src = NrfClkLoFreq2ClkSrc((nrf_clock_lfclk_t)NrfxClkSrc.lfclk);
    } break;
    case NRF_CLOCK_DOMAIN_HFCLK: {
        src = NrfClkHiFreq2ClkSrc((nrf_clock_hfclk_t)NrfxClkSrc.hfclk);
    } break;
    case NRF_CLOCK_DOMAIN_HFCLK192M: {
        src = NrfClkHiFreq2ClkSrc((nrf_clock_hfclk_t)NrfxClkSrc.hfclk);
    } break;
    case NRF_CLOCK_DOMAIN_HFCLKAUDIO: {
        src = CLOCK_SRC_UNDEF;
    } break;
    }
    return src;
}

uint32_t clock_audio_freq_get(void) {
    uint32_t audio_freq_hz = 0;
    uint16_t freq_value = nrfx_clock_hfclkaudio_config_get();
    double audio_clock_hz = clock_audio_calc(freq_value);
    audio_freq_hz = (uint32_t)audio_clock_hz;
    return audio_freq_hz;
}

uint32_t clock_freq_get(nrf_clock_domain_t domain_nrf) {
    uint32_t core_freq_hz = 0;
    nrf_clock_hfclk_div_t nfr_div = nrfx_clock_divider_get(domain_nrf);
    uint32_t divider = NrfDiv2Div(nfr_div);
    uint8_t byte = 0;
    uint32_t base_clock_hz = 0;
    LOG_DEBUG(CLK, "ClockDomain:%u,Div:%u", domain_nrf, divider);
    bool is_running = false;
    NrfxClkSrc_t NrfxClkSrc;
    NrfxClkSrc.byte = 0;
    is_running = nrfx_clock_is_running(domain_nrf, (void*)&NrfxClkSrc.byte);
    if(is_running) {
        LOG_DEBUG(CLK, "ClockDomain %u is running, ClkSrc:%u", domain_nrf, byte);
        switch(domain_nrf) {
        case NRF_CLOCK_DOMAIN_LFCLK: {
            base_clock_hz = NrfClockLfClk2Hz((nrf_clock_lfclk_t)NrfxClkSrc.lfclk);
        } break;

        case NRF_CLOCK_DOMAIN_HFCLK: {
            base_clock_hz = NrfClockHfClk2Hz((nrf_clock_hfclk_t)NrfxClkSrc.hfclk);
        } break;

        case NRF_CLOCK_DOMAIN_HFCLK192M: {
            base_clock_hz = NrfClockHfClk2Hz((nrf_clock_hfclk_t)NrfxClkSrc.hfclk);
        } break;

        case NRF_CLOCK_DOMAIN_HFCLKAUDIO: {
            base_clock_hz = clock_audio_freq_get();
        } break;
        } // switch
        core_freq_hz = base_clock_hz;
        LOG_DEBUG(CLK, "BaseClock %u Hz,%u Hz", base_clock_hz, core_freq_hz);
    } else {
        // base_clock_hz = 0;
    }
    // core_freq_hz = (uint32_t)  (              (  (double)base_clock_hz)   /    ((double)div)     );

    switch(divider) {
    case 1:
        core_freq_hz = base_clock_hz;
        break;
    case 2:
        core_freq_hz = base_clock_hz >> 1;
        break;
    case 4:
        core_freq_hz = base_clock_hz >> 2;
        break;
    default:
        LOG_ERROR(CLK, "UndefDiv %u", divider);
        break;
    }

    // core_freq_hz =                base_clock_hz   /    divider; /*Compiler unable to divide integers*/
    LOG_DEBUG(CLK, "Freq %u Hz", core_freq_hz);

    return core_freq_hz;
}

uint32_t clock_core_freq_get(void) {
    uint32_t core_freq_hz = 0;
    /*TODO*/
    return core_freq_hz;
}

bool clock_core_freq_set(uint32_t core_freq_hz) {
    bool res = false;
    /*TODO*/
    return res;
}

/*
  >>> 128.0*(3.0*12288000.0-32000000.0)/15625.0
   39845.888
  >>> hex(39845)
   '0x9ba5'
*/
static uint16_t clock_audio_calc_code(uint32_t freq_audio_hz) {
    uint16_t freq_value = 0;
    freq_value = (128 * (3 * freq_audio_hz - 32000000) / 15625);
    LOG_DEBUG(CLK, "CaclAudioCode:Freq:%u Hz,Code:%u=0x%04x", freq_audio_hz, freq_value, freq_value);
    return freq_value;
}

/*
 *  >>> (32000000.0 * (4.0 + 39854.0 * (2.0**(-16.0)) )) /12.0
 *  12288330.078125
 * */
double clock_audio_calc(uint16_t freq_value) {
    double freq_audio_hz = (32000000.0 * (4.0 + ((double)freq_value) * pow(2.0, -16.0))) / 12.0;
    LOG_DEBUG(CLK, "FreqValue:Code:%u,Freq:%f Hz", freq_value, freq_audio_hz);
    return freq_audio_hz;
}

bool clock_audio_freq_set(uint32_t freq_audio_hz) {
    bool res = false;
    uint16_t freq_value = 0;
    freq_value = clock_audio_calc_code(freq_audio_hz);
    nrfx_clock_hfclkaudio_config_set(freq_value);
    LOG_INFO(CLK, "AudioFreq:%u Hz,Code:%u=0x%x", freq_audio_hz, freq_value, freq_value);
    return res;
}
