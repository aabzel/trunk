#include "adc_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "adc_config.h"
#include "adc_drv.h"
#include "log.h"
#include "nrf_saadc.h"
#include "table_utils.h"
#include "writer_config.h"

const char* NrfResolution2Str(nrf_saadc_resolution_t code) {
    const char* name = "?";
    switch(code) {
    case NRF_SAADC_RESOLUTION_8BIT:
        name = "8";
        break;
    case NRF_SAADC_RESOLUTION_10BIT:
        name = "10";
        break;
    case NRF_SAADC_RESOLUTION_12BIT:
        name = "12";
        break;
    case NRF_SAADC_RESOLUTION_14BIT:
        name = "14";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* NrfInput2Str(nrf_saadc_input_t code) {
    const char* name = "?";
    switch(code) {
    case NRF_SAADC_INPUT_DISABLED:
        name = "NC";
        break;
    case NRF_SAADC_INPUT_AIN0:
        name = "AIN0";
        break;
    case NRF_SAADC_INPUT_AIN1:
        name = "AIN1";
        break;
    case NRF_SAADC_INPUT_AIN2:
        name = "AIN2";
        break;
    case NRF_SAADC_INPUT_AIN3:
        name = "AIN3";
        break;
    case NRF_SAADC_INPUT_AIN4:
        name = "AIN4";
        break;
    case NRF_SAADC_INPUT_AIN5:
        name = "AIN5";
        break;
    case NRF_SAADC_INPUT_AIN6:
        name = "AIN6";
        break;
    case NRF_SAADC_INPUT_AIN7:
        name = "AIN7";
        break;
    case NRF_SAADC_INPUT_VDD:
        name = "VDD";
        break;
    case NRF_SAADC_INPUT_VDDHDIV5:
        name = "VDDH/5";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* NrfOversample2Str(nrf_saadc_oversample_t code) {
    const char* name = "?";
    switch(code) {
    case NRF_SAADC_OVERSAMPLE_DISABLED:
        name = "dis";
        break;
    case NRF_SAADC_OVERSAMPLE_2X:
        name = "2x";
        break;
    case NRF_SAADC_OVERSAMPLE_4X:
        name = "4x";
        break;
    case NRF_SAADC_OVERSAMPLE_8X:
        name = "8x";
        break;
    case NRF_SAADC_OVERSAMPLE_16X:
        name = "16x";
        break;
    case NRF_SAADC_OVERSAMPLE_32X:
        name = "32x";
        break;
    case NRF_SAADC_OVERSAMPLE_64X:
        name = "64x";
        break;
    case NRF_SAADC_OVERSAMPLE_128X:
        name = "128x";
        break;
    case NRF_SAADC_OVERSAMPLE_256X:
        name = "256x";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* NrfResistor2Str(nrf_saadc_resistor_t code) {
    const char* name = "?";
    switch(code) {
    case NRF_SAADC_RESISTOR_DISABLED:
        name = "Disable";
        break;
    case NRF_SAADC_RESISTOR_PULLDOWN:
        name = "Down";
        break;
    case NRF_SAADC_RESISTOR_PULLUP:
        name = "Up";
        break;
    case NRF_SAADC_RESISTOR_VDD1_2:
        name = "VDD/2";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* NrfGain2Str(nrf_saadc_gain_t code) {
    const char* name = "?";
    switch(code) {
    case NRF_SAADC_GAIN1_6:
        name = "1/6";
        break;
    case NRF_SAADC_GAIN1_5:
        name = "1/5";
        break;
    case NRF_SAADC_GAIN1_4:
        name = "1/4";
        break;
    case NRF_SAADC_GAIN1_3:
        name = "1/3";
        break;
    case NRF_SAADC_GAIN1_2:
        name = "1/2";
        break;
    case NRF_SAADC_GAIN1:
        name = "1";
        break;
    case NRF_SAADC_GAIN2:
        name = "2";
        break;
    case NRF_SAADC_GAIN4:
        name = "4";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* NrfRef2Str(nrf_saadc_reference_t code) {
    const char* name = "?";
    switch(code) {
    case NRF_SAADC_REFERENCE_INTERNAL:
        name = "0.6";
        break;
    case NRF_SAADC_REFERENCE_VDD4:
        name = "VDD/4";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* NrfTAck2Str(nrf_saadc_acqtime_t code) {
    const char* name = "?";
    switch(code) {
    case NRF_SAADC_ACQTIME_3US:
        name = "3";
        break;
    case NRF_SAADC_ACQTIME_5US:
        name = "5";
        break;
    case NRF_SAADC_ACQTIME_10US:
        name = "10";
        break;
    case NRF_SAADC_ACQTIME_15US:
        name = "15";
        break;
    case NRF_SAADC_ACQTIME_20US:
        name = "20";
        break;
    case NRF_SAADC_ACQTIME_40US:
        name = "40";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* NrfMode2Str(nrf_saadc_mode_t code) {
    const char* name = "?";
    switch(code) {
    case NRF_SAADC_MODE_SINGLE_ENDED:
        name = "Single";
        break;
    case NRF_SAADC_MODE_DIFFERENTIAL:
        name = "Diff";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* NrfBurst2Str(nrf_saadc_burst_t code) {
    const char* name = "?";
    switch(code) {
    case NRF_SAADC_BURST_DISABLED:
        name = "off";
        break;
    case NRF_SAADC_BURST_ENABLED:
        name = "en";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

bool adc_custom_diag(const char* const keyWord1, const char* const keyWord2) {
    bool res = false;
    AdcHandle_t* AdcNode = AdcGetNode(1);
    if(AdcNode) {
        LOG_INFO(LG_ADC, "VrefCode: %u", AdcNode->ref_code);
        LOG_INFO(LG_ADC, "VrefCode: %u", AdcNode->code_at_vref);
        LOG_INFO(LG_ADC, "Vref: %f Ref", AdcNode->v_ref_voltage);
        LOG_INFO(LG_ADC, "ErrCnt: %u", AdcNode->err_cnt);
        const AdcConfig_t* AdcConfigNode = AdcGetConfigNode(1);
        if(AdcConfigNode) {
            LOG_INFO(LG_ADC, "Resolution: %u", AdcConfigNode->resolution);
            LOG_INFO(LG_ADC, "IRQ priority: %u", AdcConfigNode->irq_priority);
        }
        LOG_INFO(LG_ADC, "IRQevent: %s", (AdcNode->event_handler != NULL) ? "en" : "dis");
        LOG_INFO(LG_ADC, "OverSample: %s", NrfOversample2Str(AdcNode->oversampling));
        LOG_INFO(LG_ADC, "IT Cnt: %u", AdcNode->it_cnt);

        static const table_col_t cols[] = {
            {5, "Adc"},  {4, "Ch"},   {6, "PinP"},  {6, "PinN"}, {6, "Gain"}, {6, "Ref"},
            {6, "Tack"}, {8, "Mode"}, {7, "Burst"}, {9, "ResP"}, {9, "ResN"},
        };

        uint16_t num = 0;
        uint32_t chan_cnt = adc_channel_get_cnt();
        cli_printf("ChanCnt: %u" CRLF, chan_cnt);
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        char log_line[120];

        uint8_t i = 0;
        for(i = 0; i < chan_cnt; i++) {
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, AdcChannels[i].num);
            snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, AdcChannels[i].channel);
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, NrfInput2Str(AdcNode->ch_cfgs[i].pin_p));
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, NrfInput2Str(AdcNode->ch_cfgs[i].pin_n));
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line,
                     NrfGain2Str(AdcNode->ch_cfgs[i].channel_config.gain));
            snprintf(log_line, sizeof(log_line), "%s %3s V " TSEP, log_line,
                     NrfRef2Str(AdcNode->ch_cfgs[i].channel_config.reference));
            snprintf(log_line, sizeof(log_line), "%s %2s us " TSEP, log_line,
                     NrfTAck2Str(AdcNode->ch_cfgs[i].channel_config.acq_time));
            snprintf(log_line, sizeof(log_line), "%s %6s " TSEP, log_line,
                     NrfMode2Str(AdcNode->ch_cfgs[i].channel_config.mode));
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line,
                     NrfBurst2Str(AdcNode->ch_cfgs[i].channel_config.burst));
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line,
                     NrfResistor2Str(AdcNode->ch_cfgs[i].channel_config.resistor_p));
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line,
                     NrfResistor2Str(AdcNode->ch_cfgs[i].channel_config.resistor_n));
            cli_printf("%s" CRLF, log_line);
            num++;
        }
        res = true;
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}
