#include "sw_dac_diag.h"

#include <string.h>
#include <stdio.h>

#include "common_diag.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "sw_dac_drv.h"
#include "table_utils.h"
#include "writer_config.h"

const char* FramePattern2Str(FramePattern_t frame_pattern){
    const char *name = "?";
    switch (frame_pattern) {
    case CHANNEL_ONLY_RIGHT:
        name = "_X";
        break;
    case CHANNEL_ONLY_LEFT:
        name = "X_";
        break;
    case CHANNEL_BOTH:
        name = "XX";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

const char *SwDacMode2Str(SwDacMode_t mode) {
    const char *name = "?";
    switch (mode) {
    case DAC_MODE_STATIC:
        name = "STATIC";
        break;
    case DAC_MODE_PWM:
        name = "PWM";
        break;
    case DAC_MODE_SIN:
        name = "SIN";
        break;
    case DAC_MODE_SAW:
        name = "SAW";
        break;
    case DAC_MODE_FENCE:
        name = "FENCE";
        break;
    case DAC_MODE_CHIRP:
        name = "CHIRP";
        break;
#ifdef HAS_DTMF
    case DAC_MODE_DTMF:
        name = "DTMF";
        break;
#endif

    default:
        name = "??";
        break;
    }
    return name;
}

const char* SampleSize2Format(uint8_t sample_size){
    const char* name ="0x08x";
    switch(sample_size){
    case 2:name ="0x%04x"; break;
    case 4:name ="0x%08x"; break;
    default: break;
    }
    return name;
}

bool sw_dac_print_track_2byte(uint8_t dac_num) {
    bool res = false;
    SwDac_t* Node = SwDacGetNode(dac_num);
    if(Node) {
        uint32_t i = 0;
        uint32_t s = 0;
        static const table_col_t cols[] = {
            {5, "No"},
            {12, "UpTime"},
#ifdef HAS_REAL_SAMPLE_ARRAY
            {12, "SampleDec"},
            {8, "SampleHex"},
#endif
#ifdef HAS_DYNAMIC_SAMPLES
            {8, "RAM"}, {8, "Tx hex"},
            {12, "Tx dec"},
#endif
        };
        double up_time_s = 0.0;
        LOG_INFO(SW_DAC, "SampleCnt: %u, SampleSize %u bit, SizeOfSampleType %u byte", Node->sample_cnt,Node->sample_bitness, sizeof(SampleType_t));
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        for(s = 0, i = 0; s < Node->sample_cnt; s++, i += 2) {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, s + 1);
            up_time_s = ((double)(s + 1))/((double)Node->sample_per_second);
            cli_printf(" %10.8f " TSEP, up_time_s);
            res = true;
#ifdef HAS_REAL_SAMPLE_ARRAY
            if(&Node->real_sample_array[i]) {
                cli_printf(" %10d " TSEP,(SampleType_t)  Node->real_sample_array[s]);
                cli_printf(" 0x%04x " TSEP, (uint16_t) Node->real_sample_array[s]);
                /*+ binary form*/
            }
#endif

#ifdef HAS_DYNAMIC_SAMPLES
            if(&Node->tx_sample_array[i]) {
                cli_printf(" 0x");
                uint8_t sample_size = Node->sample_bitness/8;
                print_hex((uint8_t*)&Node->tx_sample_array[i], sample_size);
                cli_printf(" " TSEP);
                cli_printf(" 0x%04x " TSEP, (uint16_t) Node->tx_sample_array[i]);
                cli_printf(" %10d " TSEP, Node->tx_sample_array[i]);
            }
#endif
            cli_printf(CRLF);
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}


bool sw_dac_print_track_4byte(uint8_t dac_num) {
    bool res = false;
    SwDac_t* Node = SwDacGetNode(dac_num);
    if(Node) {
        uint32_t i = 0;
        uint32_t s = 0;
        static const table_col_t cols[] = {
            {5, "No"},
            {12, "UpTime"},
#ifdef HAS_REAL_SAMPLE_ARRAY
            {12, "SampleDec"},
            {12, "SampleHex"},
#endif

#ifdef HAS_DYNAMIC_SAMPLES
            {12, "RAM"}, {12, "Tx hex"},
            {12, "Tx dec"},
#endif
        };
        double up_time_s = 0.0;
        uint8_t sample_size = Node->sample_bitness/8;
        LOG_INFO(SW_DAC, "SampleCnt: %u, SampleSize %u, SizeOfSampleType %u byte", Node->sample_cnt,sample_size, sizeof(SampleType_t));
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        for(s = 0, i = 0; s < Node->sample_cnt; s++, i += 2) {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, s + 1);
            up_time_s = ((double)(s + 1))/((double)Node->sample_per_second);
            cli_printf(" %10.8f " TSEP, up_time_s);
            res = true;

#ifdef HAS_REAL_SAMPLE_ARRAY
            if(&Node->real_sample_array[s]) {
                cli_printf(" %10d " TSEP, Node->real_sample_array[s]);
                cli_printf(" 0x%08x "TSEP , (uint32_t) Node->real_sample_array[s]);
            }
#endif
#ifdef HAS_DYNAMIC_SAMPLES
            if(&Node->tx_sample_array[i]) {
                cli_printf(" 0x");
                uint8_t sample_size = Node->sample_bitness/8;
                print_hex((uint8_t*)&Node->tx_sample_array[i], sample_size);
                cli_printf(" " TSEP);
                cli_printf(" 0x%08x " TSEP,(uint32_t) Node->tx_sample_array[i]);
                cli_printf(" %10d " TSEP, Node->tx_sample_array[i]);
            }
#endif
            cli_printf(CRLF);
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}

bool sw_dac_print_track(uint8_t num) {
    bool res = false;
#ifdef HAS_PCM_16_BIT
    res = sw_dac_print_track_2byte(num) ;
#endif

#ifdef HAS_PCM_32_BIT
    res = sw_dac_print_track_4byte(num) ;
#endif
    return res;
}

#if 0
bool sw_dac_print_track(uint8_t dac_num) {
    bool res = false;
    SwDac_t* Node = SwDacGetNode(dac_num);
    if(Node) {
        uint32_t i = 0;
        uint32_t s = 0;
        static const table_col_t cols[] = {
            {5, "No"},
            {12, "UpTime"},
            {12, "SampleDec"},
            {12, "SampleHex"},
            {12, "RAM"}, {12, "Tx hex"},
            {12, "Tx dec"},
        };
        double up_time_s = 0.0;
        LOG_INFO(SW_DAC, "SampleCnt: %u, SampleSize %u, SizeOfSampleType %u byte", Node->sample_cnt,Node->sample_size, sizeof(SampleType_t));
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        for(s = 0, i = 0; s < Node->sample_cnt; s++, i += 2) {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, s + 1);
            up_time_s = ((double)(s + 1))/((double)Node->sample_per_second);
            cli_printf(" %10.8f " TSEP, up_time_s);
            res = true;
            char format[20] = "";
            sprintf(format," %s "TSEP, SampleSize2Format(Node->sample_size));
            if(&Node->real_sample_array[i]) {
                cli_printf(" %10d " TSEP, Node->real_sample_array[s]);
                cli_printf(format , (SampleType_t) Node->real_sample_array[s]);
            }
            if(&Node->tx_sample_array[i]) {
                cli_printf(" 0x");
                print_hex((uint8_t*)&Node->tx_sample_array[i], Node->sample_size);
                cli_printf(" " TSEP);
                cli_printf(format, Node->tx_sample_array[i]);
                cli_printf(" %10d " TSEP, Node->tx_sample_array[i]);
            }
            cli_printf(CRLF);
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}
#endif

bool sw_dac_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "num"},    {7, "mode"},    {8, "freq"}, {8, "amp"},     {6, "duty"},
        {6, "offset"}, {9, "phaseMs"}, {6, "init"}, {6, "samples"}, {6, "name"},
    };
    char temp_str[120];

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t dac_cnt = sw_dac_get_cnt();
    uint8_t dac_num = 1;
    for(dac_num = 1; dac_num <= dac_cnt; dac_num++) {
        SwDac_t* Node = SwDacGetNode(dac_num);
        const SwDacConfig_t* Config = SwDacGetConfig(dac_num);
        if(Node && Config) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %2u  " TSEP, temp_str, Node->num);
            snprintf(temp_str, sizeof(temp_str), "%s %5s " TSEP, temp_str, SwDacMode2Str(Node->dac_mode));
            snprintf(temp_str, sizeof(temp_str), "%s %6.1f " TSEP, temp_str, Node->frequency);
            snprintf(temp_str, sizeof(temp_str), "%s %5u  " TSEP, temp_str, (unsigned int)Node->amplitude);
            snprintf(temp_str, sizeof(temp_str), "%s %3.1f " TSEP, temp_str, Node->duty_cycle);
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int)Node->offset);
            snprintf(temp_str, sizeof(temp_str), "%s %5.0f   " TSEP, temp_str, Node->phase_ms);
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, OnOff2Str((uint8_t)Node->init));
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int)Node->sample_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, Config->name);
            cli_printf("%s" CRLF, temp_str);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool SwDacConfigDiag(const SwDacConfig_t* const Config){
    bool res = false;
    if(Config){
        char temp_str[120];
        strcpy(temp_str, "");
        snprintf(temp_str, sizeof(temp_str), "%s %2u," , temp_str, Config->num);
        snprintf(temp_str, sizeof(temp_str), "%s Mode:%5s," , temp_str, SwDacMode2Str(Config->dac_mode));
        snprintf(temp_str, sizeof(temp_str), "%s Pha %5.0f ms," , temp_str, Config->phase_ms);
        snprintf(temp_str, sizeof(temp_str), "%s Duty:%3.1f," , temp_str, Config->duty_cycle);
        snprintf(temp_str, sizeof(temp_str), "%s Freq1:%6.1f Hz," , temp_str, Config->frequency);
        snprintf(temp_str, sizeof(temp_str), "%s Amp:%5u," , temp_str, (unsigned int)Config->amplitude);
        snprintf(temp_str, sizeof(temp_str), "%s %4u bit," , temp_str, Config->sample_bitness);
        snprintf(temp_str, sizeof(temp_str), "%s %4u," , temp_str, (unsigned int)Config->offset);
        snprintf(temp_str, sizeof(temp_str), "%s Patt:%4s," , temp_str, FramePattern2Str(Config->frame_pattern));
        snprintf(temp_str, sizeof(temp_str), "%s %4s," , temp_str, Config->name);
        LOG_INFO(SW_DAC,"%s" CRLF, temp_str);
        res = true;
    }
    return res;
}

bool SwDacNodeDiag(const SwDac_t* const Node) {
    bool res = false;
    if(Node) {
        char temp_str[120];
        strcpy(temp_str, "");
        snprintf(temp_str, sizeof(temp_str), "%s %2u," , temp_str, Node->num);
        snprintf(temp_str, sizeof(temp_str), "%s Mode:%5s," , temp_str, SwDacMode2Str(Node->dac_mode));
        snprintf(temp_str, sizeof(temp_str), "%s Pha %5.0f ms," , temp_str, Node->phase_ms);
        snprintf(temp_str, sizeof(temp_str), "%s Duty:%3.1f," , temp_str, Node->duty_cycle);
        snprintf(temp_str, sizeof(temp_str), "%s Freq:%6.1f Hz," , temp_str, Node->frequency);
#ifdef HAS_DTMF
        snprintf(temp_str, sizeof(temp_str), "%s Freq2:%6.1f Hz," , temp_str, Node->frequency2);
#endif
        snprintf(temp_str, sizeof(temp_str), "%s Amp:%5u," , temp_str, (unsigned int)Node->amplitude);
        snprintf(temp_str, sizeof(temp_str), "%s %4u bit," , temp_str, Node->sample_bitness);
        snprintf(temp_str, sizeof(temp_str), "%s %4u," , temp_str, (unsigned int)Node->offset);
        snprintf(temp_str, sizeof(temp_str), "%s Fps: %4u Hz," , temp_str, Node->sample_per_second);
        snprintf(temp_str, sizeof(temp_str), "%s Patt:%4s," , temp_str, FramePattern2Str(Node->frame_pattern));

        LOG_INFO(SW_DAC,"%s", temp_str);
        res = true;
    }
    return res;
}
