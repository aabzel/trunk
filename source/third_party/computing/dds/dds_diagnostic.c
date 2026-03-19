#include "dds_diagnostic.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "data_utils.h"
#include "dds.h"
#include "dds_configuration.h"
#include "debug_info.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_PCM_32_BIT
static bool DDS_PrintTrack32bitSample(U8 dac_num);
#endif
static bool DDS_PrintTrack16binSample(U8 dac_num);


bool DDS_ConfigurationDiag(const DDS_CONFIG* const Config)
{
    bool res = false;
    if (Config)
    {
        char temp_str[120] = { 0 };
        strcpy(temp_str, "");
        snprintf(temp_str, sizeof(temp_str), "%s%2u,", temp_str, Config->num);
        snprintf(
            temp_str, sizeof(temp_str), "%sMode:%5s,", temp_str, DDS_ModeToStr(Config->ddsSignal));
        snprintf(temp_str, sizeof(temp_str), "%sPha %5.0f ms,", temp_str, Config->phaseMs);
        snprintf(temp_str, sizeof(temp_str), "%sDuty:%3.1f,", temp_str, Config->dutyCycle);
        snprintf(temp_str, sizeof(temp_str), "%sFreq1:%6.1f Hz,", temp_str, Config->frequency);
        snprintf(
            temp_str, sizeof(temp_str), "%sAmp:%5u,", temp_str, (unsigned int)Config->amplitude);
        snprintf(temp_str, sizeof(temp_str), "%s%4u bit,", temp_str, Config->sampleBitness);
        snprintf(temp_str, sizeof(temp_str), "%s%4u,", temp_str, (unsigned int)Config->offset);
        snprintf(temp_str,
                 sizeof(temp_str),
                 "%sPatt:%4s,",
                 temp_str,
                 DDS_FramePatternToStr(Config->samplePattern));
        snprintf(temp_str, sizeof(temp_str), "%s%4s", temp_str, Config->name);
        LOG_INFO(DDS, "%s" CRLF, temp_str);
        res = TRUE;
    }
    return res;
}


bool DDS_Diagnostic(void)
{
    bool                     res = false;
    static const table_col_t cols[] = {
        { 5, "num" },     { 7, "mode" },   { 8, "freq" },    { 8, "amp" },
        { 6, "duty" },    { 6, "offset" }, { 9, "phaseMs" }, { 6, "init" },
        { 6, "samples" }, { 6, "name" },   { 6, "Play" },
    };
    char temp_str[120];

    table_header(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));
    U32 dac_cnt = DDS_GetCnt();
    U8  dac_num = 1;
    for (dac_num = 1; dac_num <= dac_cnt; dac_num++)
    {
        DDS_HANDLE*       Node = DDS_GetNode(dac_num);
        const DDS_CONFIG* Config = DDS_GetConfig(dac_num);
        if (Node && Config)
        {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %2u  " TSEP, temp_str, Node->num);
            snprintf(temp_str,
                     sizeof(temp_str),
                     "%s %5s " TSEP,
                     temp_str,
                     DDS_ModeToStr(Node->ddsSignal));
            snprintf(temp_str, sizeof(temp_str), "%s %6.1f " TSEP, temp_str, Node->frequency);
            snprintf(temp_str,
                     sizeof(temp_str),
                     "%s %5u  " TSEP,
                     temp_str,
                     (unsigned int)Node->amplitude);
            snprintf(temp_str, sizeof(temp_str), "%s %3.1f " TSEP, temp_str, Node->dutyCycle);
            snprintf(
                temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int)Node->offset);
            snprintf(temp_str, sizeof(temp_str), "%s %5.0f   " TSEP, temp_str, Node->phaseMs);
            snprintf(temp_str,
                     sizeof(temp_str),
                     "%s %4s " TSEP,
                     temp_str,
                     OnOffToStr((U8)Node->initDone));
            snprintf(temp_str,
                     sizeof(temp_str),
                     "%s %4u " TSEP,
                     temp_str,
                     (unsigned int)Node->sampleCnt);
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, Config->name);
            snprintf(temp_str,
                     sizeof(temp_str),
                     "%s %4s " TSEP,
                     temp_str,
                     DDS_PlayerToStr(Config->player));
            cli_printf("%s" CRLF, temp_str);
            res = TRUE;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));

    return res;
}

bool DDS_NodeDiag(const DDS_HANDLE* const Node)
{
    bool res = false;
    if (Node)
    {
        LOG_INFO(DDS, "%s", DDS_NodeToStr(Node));
        res = TRUE;
    }
    return res;
}

bool DDS_print_track(U8 num)
{
    bool res = false;
#ifdef HAS_PCM_16_BIT
    res = DDS_PrintTrack16binSample(num);
#endif

#ifdef HAS_PCM_32_BIT
    res = DDS_PrintTrack32bitSample(num);
#endif
    return res;
}


const char* DDS_ConfigurationToStr(const DDS_CONFIG* const Config)
{
    static char temp_str[120] = { 0 };
    if (Config)
    {
        strcpy(temp_str, "");
        snprintf(temp_str, sizeof(temp_str), "%s%u,", temp_str, Config->num);
        snprintf(temp_str, sizeof(temp_str), "%s%s,", temp_str, Config->name);
        snprintf(temp_str, sizeof(temp_str), "%sMode:%s,", temp_str, DDS_ModeToStr(Config->ddsSignal));
        snprintf(temp_str, sizeof(temp_str), "%sPha %5.0f ms,", temp_str, Config->phaseMs);
        snprintf(temp_str, sizeof(temp_str), "%sDuty:%3.1f,", temp_str, Config->dutyCycle);
        snprintf(temp_str, sizeof(temp_str), "%sFreq:%6.1f Hz,", temp_str, Config->frequency);
        snprintf(
            temp_str, sizeof(temp_str), "%sAmp:%u,", temp_str, (unsigned int)Config->amplitude);
        snprintf(temp_str, sizeof(temp_str), "%sFps: %u Hz,", temp_str, Config->framePerSec);
        snprintf(temp_str, sizeof(temp_str), "%s%u bit,", temp_str, Config->sampleBitness);
        snprintf(temp_str, sizeof(temp_str), "%s%u,", temp_str, (unsigned int)Config->offset);
        snprintf(temp_str,
                 sizeof(temp_str),
                 "%sPatt:%s,",
                 temp_str,
                 DDS_FramePatternToStr(Config->samplePattern));

#ifdef DDS_DTMF_IN_USE
        snprintf(temp_str, sizeof(temp_str), "%sFreq2:%6.1f Hz,", temp_str, Config->frequency2);
#endif
    }
    return temp_str;
}

const char* DDS_FramePatternToStr(DDS_SAMPLE_PATTERN samplePattern)
{
    const char* name = "?";
    switch (samplePattern)
    {
    case DDS_CHANNEL_ONLY_RIGHT:
        name = "_X";
        break;
    case DDS_CHANNEL_ONLY_LEFT:
        name = "X_";
        break;
    case DDS_CHANNEL_BOTH:
        name = "XX";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

const char* DDS_ModeToStr(DDS_SIGNAL mode)
{
    const char* name = "?";
    switch (mode)
    {
    case DDS_SIGNAL_STATIC:
        name = "STATIC";
        break;
    case DDS_SIGNAL_PWM:
        name = "PWM";
        break;
    case DDS_SIGNAL_SIN:
        name = "SIN";
        break;
    case DDS_SIGNAL_SAW:
        name = "SAW";
        break;
    case DDS_SIGNAL_FENCE:
        name = "FENCE";
        break;
    case DDS_SIGNAL_CHIRP:
        name = "CHIRP";
        break;
#ifdef DDS_DTMF_IN_USE
    case DDS_SIGNAL_DTMF:
        name = "DTMF";
        break;
#endif

    default:
        name = "??";
        break;
    }
    return name;
}

#ifdef HAS_PCM_32_BIT
static bool DDS_PrintTrack32bitSample(U8 dac_num)
{
    bool        res = false;
    DDS_HANDLE* Node = DDS_GetNode(dac_num);
    if (Node)
    {
        U32                      i = 0;
        U32                      s = 0;
        static const table_col_t cols[] = {
            { 5, "No" },
            { 12, "UpTime" },

        };
        FLOAT32 up_time_s = 0.0;
        U8      sample_size = Node->sampleBitness / 8;
        LOG_INFO(DDS,
                 "SampleCnt: %u, SampleSize %u, SizeOfSampleType %u byte",
                 Node->sampleCnt,
                 sample_size,
                 sizeof(DDS_SAMPLE_TYPE));
        table_header(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));
        for (s = 0, i = 0; s < Node->sampleCnt; s++, i += 2)
        {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, s + 1);
            up_time_s = ((FLOAT32)(s + 1)) / ((FLOAT32)Node->framePerSec);
            cli_printf(" %10.8f " TSEP, up_time_s);
            res = TRUE;


            cli_printf(CRLF);
        }
        table_row_bottom(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));
    }
    return res;
}
#endif



const char* DDS_NodeToStr(const DDS_HANDLE* const Node)
{
    static char temp_str[120] = { 0 };
    if (Node)
    {
        strcpy(temp_str, "");
        snprintf(temp_str, sizeof(temp_str), "%s%u,", temp_str, Node->num);
        snprintf(
            temp_str, sizeof(temp_str), "%sMode:%s,", temp_str, DDS_ModeToStr(Node->ddsSignal));
        snprintf(temp_str, sizeof(temp_str), "%sPlay:%s,", temp_str, DDS_PlayerToStr(Node->player));
        snprintf(temp_str, sizeof(temp_str), "%sPha %5.0f ms,", temp_str, Node->phaseMs);
        snprintf(temp_str, sizeof(temp_str), "%sDuty:%3.1f,", temp_str, Node->dutyCycle);
        snprintf(temp_str, sizeof(temp_str), "%sFreq:%6.1f Hz,", temp_str, Node->frequency);
#ifdef DDS_DTMF_IN_USE
        snprintf(temp_str, sizeof(temp_str), "%sFreq2:%6.1f Hz,", temp_str, Node->frequency2);
#endif
        snprintf(temp_str, sizeof(temp_str), "%sAmp:%u,", temp_str, (unsigned int)Node->amplitude);
        snprintf(temp_str, sizeof(temp_str), "%s%u bit,", temp_str, Node->sampleBitness);
        snprintf(temp_str, sizeof(temp_str), "%s%u,", temp_str, (unsigned int)Node->offset);
        snprintf(temp_str, sizeof(temp_str), "%sFps: %u Hz,", temp_str, Node->framePerSec);
        snprintf(temp_str,
                 sizeof(temp_str),
                 "%sPatt:%s",
                 temp_str,
                 DDS_FramePatternToStr(Node->samplePattern));
    }
    return temp_str;
}

#if 0
bool DDS_print_track(U8 dac_num) {
    bool res = false;
    DDS_HANDLE* Node = DDS_GetNode(dac_num);
    if(Node) {
        U32 i = 0;
        U32 s = 0;
        static const table_col_t cols[] = {
            {5, "No"},
            {12, "UpTime"},
            {12, "SampleDec"},
            {12, "SampleHex"},
            {12, "RAM"}, {12, "Tx hex"},
            {12, "Tx dec"},
        };
        FLOAT32 up_time_s = 0.0;
        LOG_INFO(DDS, "SampleCnt: %u, SampleSize %u, SizeOfSampleType %u byte", Node->sampleCnt,Node->sample_size, sizeof(DDS_SAMPLE_TYPE));
        table_header(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));
        for(s = 0, i = 0; s < Node->sampleCnt; s++, i += 2) {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, s + 1);
            up_time_s = ((FLOAT32)(s + 1))/((FLOAT32)Node->framePerSec);
            cli_printf(" %10.8f " TSEP, up_time_s);
            res = TRUE;
            char format[20] = "";
            sprintf(format," %s "TSEP, DDS_SampleSizeToFormat(Node->sample_size));
            if(&Node->real_sample_array[i]) {
                cli_printf(" %10d " TSEP, Node->real_sample_array[s]);
                cli_printf(format , (DDS_SAMPLE_TYPE) Node->real_sample_array[s]);
            }
            if(&Node->tx_sample_array[i]) {
                cli_printf(" 0x");
                print_hex((U8*)&Node->tx_sample_array[i], Node->sample_size);
                cli_printf(" " TSEP);
                cli_printf(format, Node->tx_sample_array[i]);
                cli_printf(" %10d " TSEP, Node->tx_sample_array[i]);
            }
            cli_printf(CRLF);
        }
        table_row_bottom(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));
    }
    return res;
}
#endif
const char* DDS_PlayerToStr(DDS_PLAYER player)
{
    const char* name = "?";
    switch (player)
    {
    case DDS_PLAY_ON_I2S0:
        name = "I2S0";
        break;
    case DDS_PLAY_ON_I2S1:
        name = "I2S1";
        break;
    case DDS_PLAY_ON_I2S2:
        name = "I2S2";
        break;
    case DDS_PLAY_ON_I2S3:
        name = "I2S3";
        break;
    case DDS_PLAY_ON_I2S4:
        name = "I2S4";
        break;
    case DDS_PLAY_ON_I2S5:
        name = "I2S5";
        break;

    case DDS_PLAY_ON_I2S6:
        name = "I2S6";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

static bool DDS_PrintTrack16binSample(U8 dac_num)
{
    bool        res = false;
    DDS_HANDLE* Node = DDS_GetNode(dac_num);
    if (Node)
    {
        U32                      i = 0;
        U32                      s = 0;
        static const table_col_t cols[] = {
            { 5, "No" },         { 12, "UpTime" },
            { 12, "SampleDec" }, { 8, "SampleHex" },

#ifdef HAS_DYNAMIC_SAMPLES
            { 8, "RAM" },        { 8, "Tx hex" },    { 12, "Tx dec" },
#endif
        };
        FLOAT32 up_time_s = 0.0;
        LOG_INFO(DDS,
                 "SampleCnt: %u, SampleSize %u bit, SizeOfSampleType %u byte",
                 Node->sampleCnt,
                 Node->sampleBitness,
                 sizeof(DDS_SAMPLE_TYPE));
        table_header(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));
        for (s = 0, i = 0; s < Node->sampleCnt; s++, i += 2)
        {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, s + 1);
            up_time_s = ((FLOAT32)(s + 1)) / ((FLOAT32)Node->framePerSec);
            cli_printf(" %10.8f " TSEP, up_time_s);
            res = TRUE;
            cli_printf(" %10d " TSEP, (DDS_SAMPLE_TYPE)Node->txSampleArray[i]);
            cli_printf(" 0x%04x " TSEP, (uint16_t)Node->txSampleArray[i]);
                /*+ binary form*/



            cli_printf(CRLF);
        }
        table_row_bottom(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));
    }
    return res;
}



const char* DDS_SampleSizeToFormat(U8 sample_size)
{
    const char* name = "0x08x";
    switch (sample_size)
    {
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
