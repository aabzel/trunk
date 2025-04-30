#include "dds_diag.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "array_diag.h"
#include "common_diag.h"
#include "physics_const.h"
#include "data_utils.h"
#include "dds_drv.h"
#include "debug_info.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

const char* FramePatternToStr(FramePattern_t frame_pattern) {
    const char* name = "?";
    switch(frame_pattern) {
    case CHANNEL_ONLY_RIGHT:
        name = "_X";
        break;
    case CHANNEL_ONLY_LEFT:
        name = "X_";
        break;
    case CHANNEL_BOTH:
        name = "XX";
        break;
    case CHANNEL_MONO:
        name = "X";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

const char* DdsMode2Str(DdsMode_t mode) {
    const char* name = "?";
    switch(mode) {
    case DDS_MODE_STATIC:
        name = "STATIC";
        break;
    case DDS_MODE_PWM:
        name = "PWM";
        break;
    case DDS_MODE_SIN:
        name = "SIN";
        break;
    case DDS_MODE_SAW:
        name = "SAW";
        break;
    case DDS_MODE_FENCE:
        name = "FENCE";
        break;
    case DDS_MODE_CHIRP:
        name = "CHIRP";
        break;
    case DDS_MODE_BPSK:
        name = "BPSK";
        break;
#ifdef HAS_DTMF
    case DDS_MODE_DTMF:
        name = "DTMF";
        break;
#endif

    default:
        name = "??";
        break;
    }
    return name;
}

const char* DdsPlayerToStr(DdsPlayer_t player) {
    const char* name = "?";
    switch(player) {
    case DDS_PLAYER_I2S0:
        name = "I2S0";
        break;
    case DDS_PLAYER_I2S1:
        name = "I2S1";
        break;
    case DDS_PLAYER_I2S2:
        name = "I2S2";
        break;
    case DDS_PLAYER_I2S3:
        name = "I2S3";
        break;
    case DDS_PLAYER_I2S4:
        name = "I2S4";
        break;
    case DDS_PLAYER_I2S5:
        name = "I2S5";
        break;

    case DDS_PLAYER_I2S6:
        name = "I2S6";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

const char* SampleSize2Format(uint8_t sample_size) {
    const char* name = "0x08x";
    switch(sample_size) {
    case 2:
        name = "0x%04x";
        break;
    case 4:
        name = "0x%08x";
        break;
    default:
        break;
    }
    return name;
}

bool dds_print_track_2byte(uint8_t dds_num) {
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(dds_num);
    if(Node) {
        uint32_t i = 0;
        uint32_t s = 0;
        static const table_col_t cols[] = {
            {5, "No"},         {12, "UpTime"},
#ifdef HAS_REAL_SAMPLE_ARRAY
            {12, "SampleDec"}, {8, "SampleHex"},
#endif
#ifdef HAS_DYNAMIC_SAMPLES
            {8, "RAM"},        {8, "Tx hex"},    {12, "Tx dec"},
#endif
        };
        double up_time_s = 0.0;
        LOG_INFO(DDS, "SampleCnt: %u, SampleSize %u bit, SizeOfSampleType %u byte", Node->sample_cnt,
                 Node->sample_bitness, sizeof(SampleType_t));
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        for(s = 0, i = 0; s < Node->sample_cnt; s++, i += 2) {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, s + 1);
            up_time_s = ((double)(s + 1)) / ((double)Node->sample_per_second);
            cli_printf(" %10.8f " TSEP, up_time_s);
            res = true;
#ifdef HAS_REAL_SAMPLE_ARRAY
            if(&Node->real_sample_array[i]) {
                cli_printf(" %10d " TSEP, (SampleType_t)Node->real_sample_array[s]);
                cli_printf(" 0x%04x " TSEP, (uint16_t)Node->real_sample_array[s]);
                /*+ binary form*/
            }
#endif

#ifdef HAS_DYNAMIC_SAMPLES
            if(&Node->sample_array[i]) {
                cli_printf(" 0x");
                uint8_t sample_size = Node->sample_bitness / 8;
                print_hex((uint8_t*)&Node->sample_array[i], sample_size);
                cli_printf(" " TSEP);
                cli_printf(" 0x%04x " TSEP, (uint16_t)Node->sample_array[i]);
                cli_printf(" %10d " TSEP, Node->sample_array[i]);
            }
#endif
            cli_printf(CRLF);
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}

bool dds_print_track_4byte(uint8_t dds_num) {
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(dds_num);
    if(Node) {
        uint32_t i = 0;
        uint32_t s = 0;
        static const table_col_t cols[] = {
            {5, "No"},         {12, "UpTime"},
#ifdef HAS_REAL_SAMPLE_ARRAY
            {12, "SampleDec"}, {12, "SampleHex"},
#endif

#ifdef HAS_DYNAMIC_SAMPLES
            {12, "RAM"},       {12, "Tx hex"},    {12, "Tx dec"},
#endif
        };
        double up_time_s = 0.0;
        uint8_t sample_size = Node->sample_bitness / 8;
        LOG_INFO(DDS, "SampleCnt: %u, SampleSize %u, SizeOfSampleType %u byte", Node->sample_cnt, sample_size,
                 sizeof(SampleType_t));
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        for(s = 0, i = 0; s < Node->sample_cnt; s++, i += 2) {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, s + 1);
            up_time_s = ((double)(s + 1)) / ((double)Node->sample_per_second);
            cli_printf(" %10.8f " TSEP, up_time_s);
            res = true;

#ifdef HAS_REAL_SAMPLE_ARRAY
            if(&Node->real_sample_array[s]) {
                cli_printf(" %10d " TSEP, Node->real_sample_array[s]);
                cli_printf(" 0x%08x " TSEP, (uint32_t)Node->real_sample_array[s]);
            }
#endif
#ifdef HAS_DYNAMIC_SAMPLES
            if(&Node->sample_array[i]) {
                cli_printf(" 0x");
                uint8_t sample_size = Node->sample_bitness / 8;
                print_hex((uint8_t*)&Node->sample_array[i], sample_size);
                cli_printf(" " TSEP);
                cli_printf(" 0x%08x " TSEP, (uint32_t)Node->sample_array[i]);
                cli_printf(" %10d " TSEP, Node->sample_array[i]);
            }
#endif
            cli_printf(CRLF);
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}

bool dds_print_track(uint8_t num) {
    bool res = false;
#ifdef HAS_PCM_16_BIT
    res = dds_print_track_2byte(num);
#endif

#ifdef HAS_PCM_32_BIT
    res = dds_print_track_4byte(num);
#endif
    return res;
}

#if 0
bool dds_print_track(uint8_t dds_num) {
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(dds_num);
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
        LOG_INFO(DDS, "SampleCnt: %u, SampleSize %u, SizeOfSampleType %u byte", Node->sample_cnt,Node->sample_size, sizeof(SampleType_t));
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
            if(&Node->sample_array[i]) {
                cli_printf(" 0x");
                print_hex((uint8_t*)&Node->sample_array[i], Node->sample_size);
                cli_printf(" " TSEP);
                cli_printf(format, Node->sample_array[i]);
                cli_printf(" %10d " TSEP, Node->sample_array[i]);
            }
            cli_printf(CRLF);
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}
#endif

bool dds_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "num"},    {7, "mode"},    {8, "freq"}, {8, "amp"},     {6, "duty"},
        {6, "offset"}, {9, "phaseMs"}, {6, "init"}, {6, "samples"}, {6, "name"},
    };
    char temp_str[120];

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t dds_cnt = dds_get_cnt();
    uint8_t dds_num = 1;
    for(dds_num = 1; dds_num <= dds_cnt; dds_num++) {
        DdsHandle_t* Node = DdsGetNode(dds_num);
        const DdsConfig_t* Config = DdsGetConfig(dds_num);
        if(Node && Config) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %2u  " TSEP, temp_str, Node->num);
            snprintf(temp_str, sizeof(temp_str), "%s %5s " TSEP, temp_str, DdsMode2Str(Node->dds_mode));
            snprintf(temp_str, sizeof(temp_str), "%s %6.1f " TSEP, temp_str, Node->frequency);
            snprintf(temp_str, sizeof(temp_str), "%s %5u  " TSEP, temp_str, (unsigned int)Node->amplitude);
            snprintf(temp_str, sizeof(temp_str), "%s %3.1f " TSEP, temp_str, Node->duty_cycle);
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int)Node->offset);
            snprintf(temp_str, sizeof(temp_str), "%s %5.0f   " TSEP, temp_str, Node->phase_ms);
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, OnOffToStr((uint8_t)Node->init));
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int)Node->sample_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, Config->name);
            cli_printf("%s" CRLF, temp_str);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool DdsConfigDiag(const DdsConfig_t* const Config) {
    bool res = false;
    if(Config) {
        char temp_str[120] = {0};
        strcpy(temp_str, "");
        snprintf(temp_str, sizeof(temp_str), "%s %2u,", temp_str, Config->num);
        snprintf(temp_str, sizeof(temp_str), "%s Mode:%5s,", temp_str, DdsMode2Str(Config->dds_mode));
        snprintf(temp_str, sizeof(temp_str), "%s Pha %5.0f ms,", temp_str, Config->phase_ms);
        snprintf(temp_str, sizeof(temp_str), "%s Duty:%3.1f,", temp_str, Config->duty_cycle);
        snprintf(temp_str, sizeof(temp_str), "%s Freq1:%6.1f Hz,", temp_str, Config->frequency);
        snprintf(temp_str, sizeof(temp_str), "%s Amp:%5u,", temp_str, (unsigned int)Config->amplitude);
        snprintf(temp_str, sizeof(temp_str), "%s %4u bit,", temp_str, Config->sample_bitness);
        snprintf(temp_str, sizeof(temp_str), "%s %4u,", temp_str, (unsigned int)Config->offset);
        snprintf(temp_str, sizeof(temp_str), "%s Patt:%4s,", temp_str, FramePatternToStr(Config->frame_pattern));
        snprintf(temp_str, sizeof(temp_str), "%s %4s,", temp_str, Config->name);
        LOG_INFO(DDS, "%s" CRLF, temp_str);
        res = true;
    }
    return res;
}

const char* DdsNodeToStr(const DdsHandle_t* const Node) {
    static char temp_str[120] = {0};
    if(Node) {
    	double signalPeriod = 1.0/Node->frequency;
        strcpy(temp_str, "");
        snprintf(temp_str, sizeof(temp_str), "%s%u,", temp_str, Node->num);
        snprintf(temp_str, sizeof(temp_str), "%sMode:%s,", temp_str, DdsMode2Str(Node->dds_mode));
        snprintf(temp_str, sizeof(temp_str), "%sFreq:%6.1f Hz,", temp_str, Node->frequency);
        if(DDS_MODE_CHIRP==Node->dds_mode) {
        	double bw = fabs(Node->frequency2-Node->frequency);
            double resolution_m = V_SOUND_M_PES_SEC/(2.0*bw);
            snprintf(temp_str, sizeof(temp_str), "%sFreq2:%6.1f Hz,", temp_str, Node->frequency2);
            snprintf(temp_str, sizeof(temp_str), "%sBW:%6.1f Hz,", temp_str, bw);
            snprintf(temp_str, sizeof(temp_str), "%sResol:%sm,", temp_str, BigVal2Str(resolution_m));
        }
        snprintf(temp_str, sizeof(temp_str), "%sPha %5.0f ms,", temp_str, Node->phase_ms);
        snprintf(temp_str, sizeof(temp_str), "%sDuty:%3.1f,", temp_str, Node->duty_cycle);
        snprintf(temp_str, sizeof(temp_str), "%sSignalPer:%ss,", temp_str, BigVal2Str(signalPeriod));
#ifdef HAS_DTMF
        snprintf(temp_str, sizeof(temp_str), "%sFreq2:%6.1f Hz,", temp_str, Node->frequency2);
#endif
        snprintf(temp_str, sizeof(temp_str), "%sAmp:%u,", temp_str, (unsigned int)Node->amplitude);
        snprintf(temp_str, sizeof(temp_str), "%s%u bit,", temp_str, Node->sample_bitness);
        snprintf(temp_str, sizeof(temp_str), "%s%u,", temp_str, (unsigned int)Node->offset);
        snprintf(temp_str, sizeof(temp_str), "%sFps: %u Hz,", temp_str, Node->sample_per_second);
        snprintf(temp_str, sizeof(temp_str), "%sPatt:%s,", temp_str, FramePatternToStr(Node->frame_pattern));
    }
    return temp_str;
}

const char* DdsConfigToStr(const DdsConfig_t* const Config) {
    static char temp_str[220] = {0};
    if(Config) {
        strcpy(temp_str, "");
        snprintf(temp_str, sizeof(temp_str), "%s%u,", temp_str, Config->num);
        if(DDS_MODE_CHIRP==Config->dds_mode){
        	double bw = fabs(Config->frequency2-Config->frequency);
            double resolution_m = V_SOUND_M_PES_SEC/2.0*bw;
            snprintf(temp_str, sizeof(temp_str), "%sResol:%sm,", temp_str, BigVal2Str(resolution_m));
        }
        snprintf(temp_str, sizeof(temp_str), "%sSamCnt:%u,", temp_str, Config->array_size);
        snprintf(temp_str, sizeof(temp_str), "%s%s,", temp_str, Config->name);
        snprintf(temp_str, sizeof(temp_str), "%sMode:%s,", temp_str, DdsMode2Str(Config->dds_mode));
        snprintf(temp_str, sizeof(temp_str), "%sPlay:%s,", temp_str, DdsPlayerToStr(Config->player));
        snprintf(temp_str, sizeof(temp_str), "%sPha %5.0f ms,", temp_str, Config->phase_ms);
        snprintf(temp_str, sizeof(temp_str), "%sSigDur:%f,", temp_str, Config->signal_diration_s);
        snprintf(temp_str, sizeof(temp_str), "%sDuty:%3.1f,", temp_str, Config->duty_cycle);
        snprintf(temp_str, sizeof(temp_str), "%sFreq:%6.1f Hz,", temp_str, Config->frequency);
        snprintf(temp_str, sizeof(temp_str), "%sFreq2:%6.1f Hz,", temp_str, Config->frequency2);
        snprintf(temp_str, sizeof(temp_str), "%sAmp:%u,", temp_str, (unsigned int)Config->amplitude);
        snprintf(temp_str, sizeof(temp_str), "%sFps: %u Hz,", temp_str, Config->sample_per_second);
        snprintf(temp_str, sizeof(temp_str), "%sData: %p,", temp_str, Config->sample_array);
        snprintf(temp_str, sizeof(temp_str), "%s%u bit,", temp_str, Config->sample_bitness);
        snprintf(temp_str, sizeof(temp_str), "%s%u,", temp_str, (unsigned int)Config->offset);
        snprintf(temp_str, sizeof(temp_str), "%sPatt:%s,", temp_str, FramePatternToStr(Config->frame_pattern));
    }
    return temp_str;
}


bool DdsNodeDiag(const DdsHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(DDS, "%s", DdsNodeToStr(Node));
        res = true;
    }
    return res;
}

const char* DdsSampleToStr(const DdsHandle_t* const Node,uint32_t s) {
    static char temp_str[120] = {0};
    if(Node) {
    	double sample_period_s = 1.0/Node->sample_per_second;
    	double up_time_s = ((double)s) * sample_period_s;
        strcpy(temp_str, "");
        snprintf(temp_str, sizeof(temp_str), "%s[%3u/", temp_str, s);
        snprintf(temp_str, sizeof(temp_str), "%s%3u],", temp_str, Node->sample_cnt);
        snprintf(temp_str, sizeof(temp_str), "%sUpTime:%.5f,", temp_str, up_time_s);
        snprintf(temp_str, sizeof(temp_str), "%sTxSample:%7.1f,", temp_str, Node->tx_sample_d);
        snprintf(temp_str, sizeof(temp_str), "%sTxSample:%d,", temp_str, Node->tx_sample);

    }
    return temp_str;
}

