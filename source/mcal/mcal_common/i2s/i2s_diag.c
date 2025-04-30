#include "i2s_diag.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "i2s_mcal.h"
#include "i2s_types.h"
#include "log.h"
#include "num_to_str.h"
#ifdef HAS_I2S_DMA
#include "dma_diag.h"
#endif
#include "byte_utils.h"
#include "sys_config.h"
#include "table_utils.h"
#include "writer_config.h"

static char name[80] = {0};

const char* I2sAudioFreq2Str(AudioFreq_t freq) {
    snprintf(name, sizeof(name), "%u Hz", freq);
    return name;
}

const char* I2sResolution2Str(I2sDataFormat_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case I2S_DATA_FORMAT_8B:
        name = "8";
        break;
    case I2S_DATA_FORMAT_16B:
        name = "16";
        break;
    case I2S_DATA_FORMAT_16B_EXTENDED:
        name = "16";
        break;
    case I2S_DATA_FORMAT_24B:
        name = "24";
        break;
    case I2S_DATA_FORMAT_32B:
        name = "32";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

const char* I2sBusRole2Str(I2sRole_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case I2SMODE_SLAVE:
        name = "Slave";
        break;
    case I2SMODE_SLAVE_RX:
        name = "SlaveRx";
        break;
    case I2SMODE_SLAVE_TX:
        name = "SlaveTx";
        break;
    case I2SMODE_MASTER:
        name = "Master";
        break;
    case I2SMODE_MASTER_TX:
        name = "MasterTx";
        break;
    case I2SMODE_MASTER_RX:
        name = "MasterRx";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* I2sSampleMode2Str(SampleMode_t sample_mode) {
    const char* name = "?";
    switch((uint8_t)sample_mode) {
    case SAMPLE_MODE_MONO:
        name = "Mono";
        break;
    case SAMPLE_MODE_STEREO:
        name = "Stereo";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

const char* I2sStandard2Str(Standard_t standard) {
    const char* name = "?";
    switch((uint8_t)standard) {
    case I2S_STD_PHILIPS:
        name = "Philips";
        break;
    case I2S_STD_MSB:
        name = "MSB";
        break;
    case I2S_STD_LSB:
        name = "LSB";
        break;
    case I2S_STD_PCM_SHORT:
        name = "PCM_SHORT";
        break;
    case I2S_STD_PCM_LONG:
        name = "PCM_LONG";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

const char* I2sClockSource2Str(I2sClockSource_t clock_source) {
    const char* name = "?";
    switch((uint8_t)clock_source) {
    case I2S_CLK_PLL:
        name = "PLL";
        break;
    case I2S_CLK_EXT:
        name = "Exp";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

const char* I2sFullDuplex2Str(FullDuplex_t full_duplex) {
    const char* name = "?";
    switch((uint8_t)full_duplex) {
    case FULL_DUPLEX_OFF:
        name = "Simplex";
        break;
    case FULL_DUPLEX_ON:
        name = "FullDuplex";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

const char* I2sState2Str(I2sState_t state) {
    const char* name = "?";
    switch((uint8_t)state) {
    case I2S_STATE_OFF:
        name = "Off";
        break;
    case I2S_STATE_AMP:
        name = "Amp";
        break;
    case I2S_STATE_RUN:
        name = "Run";
        break;
    case I2S_STATE_DEC:
        name = "Dec";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

const char* I2sModeToStr(I2sMode_t mode) {
    const char* name = "?";
    switch((uint8_t)mode) {
    case I2S_MODE_INTERRUPT:
        name = "Int";
        break;
    case I2S_MODE_DMA:
        name = "Dma";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

const char* I2sConfigToStr(const I2sConfig_t* const Config) {
    static char text[200] = "";
    strncpy(text, "", sizeof(text) - 1);

    if(Config) {
        snprintf(text, sizeof(text), "%sI2S_%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sMode:%s,", text, I2sModeToStr(Config->mode));
#ifdef HAS_I2S_DMA
        snprintf(text, sizeof(text), "%s%s,", text, DmaPadToStr(Config->Dma));
#endif
        snprintf(text, sizeof(text), "%sSampleRate:%u Hz,", text, Config->audio_freq_hz);
        snprintf(text, sizeof(text), "%sRxBuff:%u Sample,", text, Config->samples_cnt);
        snprintf(text, sizeof(text), "%sBusRole:%s,", text, I2sBusRole2Str(Config->bus_role));
        snprintf(text, sizeof(text), "%sDataFormat:%u bit,", text, Config->data_format);
        snprintf(text, sizeof(text), "%sSckFreq:%u Hz,", text, Config->sck_freq_hz);
        snprintf(text, sizeof(text), "%sClock:%s", text, I2sClockSource2Str(Config->clock_source));
        snprintf(text, sizeof(text), "%sStd:%s,", text, I2sStandard2Str(Config->standard));
        snprintf(text, sizeof(text), "%sMclkOut:%s,", text, OnOffToStr(Config->mclk_out));
        snprintf(text, sizeof(text), "%sSampleMode:%s,", text, I2sSampleMode2Str(Config->sample_mode));
        snprintf(text, sizeof(text), "%sIrqPri:%u,", text, Config->irq_priority);
        snprintf(text, sizeof(text), "%sFullDuplex:%s,", text, I2sFullDuplex2Str(Config->full_duplex));
    }
    return text;
}

bool I2sDiagConfig(const I2sConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(I2S, "%s", I2sConfigToStr(Config));
        res = true;
    }

    return res;
}

#ifdef HAS_I2S_VOLUME
const char* I2sFsmDiag2Str(const I2sHandle_t* const Node) {
    static char text[120] = "";
    if(Node) {
        strncpy(text, "", sizeof(text) - 1);
        snprintf(text, sizeof(text), "%s State %s,", text, I2sState2Str(Node->state));
        snprintf(text, sizeof(text), "%s PCMmaxSet %d,", text, Node->pcm_max_set);
        snprintf(text, sizeof(text), "%s PCMmaxGet %d,", text, Node->pcm_max_get);
    }

    return text;
}
#endif

bool i2s_diag_sample(void) {
    bool res = false;
    static const table_col_t cols0[] = {
        {9, ""},
        {35, "left"},
        {35, "right"},
        {8, ""},
    };

    static const table_col_t cols[] = {
        {5, "No"}, {3, "#"},  {8, "Rx"},    {8, "Tx"},    {8, "RxFix"}, {8, "TxFix"},
        {8, "Rx"}, {8, "Tx"}, {8, "RxFix"}, {8, "TxFix"}, {8, "name"},
    };
    uint16_t cnt = 0;
    table_cap(&(curWriterPtr->stream), cols0, ARRAY_SIZE(cols0));
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t num = 0;
    // HAL_I2S_StateTypeDef state;
    char text[120];
    for(num = 1; num <= I2S_COUNT; num++) {
        I2sHandle_t* Node = I2sGetNode(num);
        if(Node) {
            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %u " TSEP, text, Node->num);
            snprintf(text, sizeof(text), "%s 0x%08x " TSEP, text, (unsigned int)(Node->rx_sample.u32[0]));
            snprintf(text, sizeof(text), "%s 0x%08x " TSEP, text, (unsigned int)(Node->tx_sample.u32[0]));
            snprintf(text, sizeof(text), "%s 0x%08x " TSEP, text, (unsigned int)(Node->rx_sample_fixed.u32[0]));
            snprintf(text, sizeof(text), "%s 0x%08x " TSEP, text, (unsigned int)(Node->tx_sample_fixed.u32[0]));

            snprintf(text, sizeof(text), "%s 0x%08x " TSEP, text, (unsigned int)(Node->rx_sample.u32[1]));
            snprintf(text, sizeof(text), "%s 0x%08x " TSEP, text, (unsigned int)(Node->tx_sample.u32[1]));
            snprintf(text, sizeof(text), "%s 0x%08x " TSEP, text, (unsigned int)(Node->rx_sample_fixed.u32[1]));
            snprintf(text, sizeof(text), "%s 0x%08x " TSEP, text, (unsigned int)(Node->tx_sample_fixed.u32[1]));
            const I2sConfig_t* I2sConfNode = I2sGetConfig(num);
            if(I2sConfNode) {
                snprintf(text, sizeof(text), "%s %6s " TSEP, text, I2sConfNode->name);
            }

            cli_printf(TSEP " %3u ", cnt);
            cli_printf("%s" CRLF, text);
            cnt++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2s_diag_errors(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},       {5, "num"},       {6, "Err"},       {6, "WrireErr"}, {6, "ReadErr"},
        {6, "StartErr"}, {6, "TxNextErr"}, {6, "RxNextErr"}, {6, "stop"},     {8, "name"},
    };
    uint16_t cnt = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t num = 0;
    char text[120];
    for(num = 0; num <= I2S_COUNT; num++) {

        I2sHandle_t* Node = I2sGetNode(num);
        if(Node) {
            uint32_t err = i2s_err_total(&(Node->Err));
            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %1u   " TSEP, text, Node->num);
            snprintf(text, sizeof(text), "%s %4u " TSEP, text, (unsigned int)err);
            snprintf(text, sizeof(text), "%s %4u " TSEP, text, (unsigned int)Node->Err.write);
            snprintf(text, sizeof(text), "%s %4u " TSEP, text, (unsigned int)Node->Err.read);
            snprintf(text, sizeof(text), "%s %4u " TSEP, text, (unsigned int)Node->Err.start);
            snprintf(text, sizeof(text), "%s %4u " TSEP, text, (unsigned int)Node->Err.tx_next);
            snprintf(text, sizeof(text), "%s %4u " TSEP, text, (unsigned int)Node->Err.rx_next);
            snprintf(text, sizeof(text), "%s %4u " TSEP, text, (unsigned int)Node->total_stop_cnt);
            const I2sConfig_t* I2sConfNode = I2sGetConfig(num);
            if(I2sConfNode) {
                snprintf(text, sizeof(text), "%s %6s " TSEP, text, I2sConfNode->name);
            }
            cli_printf(TSEP " %3u ", cnt);
            cli_printf("%s" CRLF, text);
            cnt++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2s_diag_config(void) {
    bool res = false;

    static const table_col_t cols[] = {
        {4, "No"}, {8, "SampSz"}, {9, "SamFreq"}, {10, "Role"}, {9, "DataFmt"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t num = 0;
    char text[200];
    for(num = 0; num <= I2S_COUNT; num++) {

        I2sHandle_t* Node = I2sGetNode(num);
        if(Node) {
            I2sDataFormat_t data_format = I2S_DATA_FORMAT_UNDEF;
            uint32_t audio_freq_hz = 0;
            I2sRole_t bus_role = I2SMODE_UNDEF;
            uint8_t sample_size = i2s_sample_size_get(num);
            res = i2s_bus_role_get(num, &bus_role);
            res = i2s_data_format_get(num, &data_format);
            res = i2s_sample_freq_get(num, &audio_freq_hz);
            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %2u " TSEP, text, Node->num);
            snprintf(text, sizeof(text), "%s %6u " TSEP, text, sample_size);
            snprintf(text, sizeof(text), "%s %7u " TSEP, text, audio_freq_hz);
            snprintf(text, sizeof(text), "%s %8s " TSEP, text, I2sBusRole2Str(bus_role));
            snprintf(text, sizeof(text), "%s %7s " TSEP, text, I2sResolution2Str(data_format));
            cli_printf("%s" CRLF, text);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2s_diag_all(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},        {5, "num"},           {9, "TxSampleCnt"}, {9, "ToggleCnt"}, {9, "ItCnt"},
        {9, "StopCnt"},   {9, "StatusStopCnt"},
#ifdef HAS_DDS
        {5, "Dac"},
#endif
        {6, "echo"},      {6, "loop"},          {6, "iir"},         {6, "Err"},       {9, "rxHalfCnt"},
        {9, "txHalfCnt"}, {9, "rxCnt"},         {9, "txCnt"},       {8, "name"},
    };
    uint16_t cnt = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t num = 0;
    char text[200];
    for(num = 0; num <= I2S_COUNT; num++) {

        I2sHandle_t* Node = I2sGetNode(num);
        // TODO: get bittness
        if(Node) {
            uint32_t err = i2s_err_total(&(Node->Err));
            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %1u   " TSEP, text, Node->num);
            snprintf(text, sizeof(text), "%s %7s " TSEP, text, u32val2Str(Node->tx_sample_cnt));
            snprintf(text, sizeof(text), "%s %7s " TSEP, text, u32val2Str(Node->toggle_cnt));
            snprintf(text, sizeof(text), "%s %7s " TSEP, text, u32val2Str(Node->it_cnt));
            snprintf(text, sizeof(text), "%s %7s " TSEP, text, u32val2Str(Node->total_stop_cnt));
            snprintf(text, sizeof(text), "%s %7s " TSEP, text, u32val2Str(Node->status_stop_cnt));
#ifdef HAS_DDS
            snprintf(text, sizeof(text), "%s %3u " TSEP, text, Node->dac_num);
#endif
            snprintf(text, sizeof(text), "%s %3s  " TSEP, text, OnOffToStr(Node->echo));
            snprintf(text, sizeof(text), "%s %3s  " TSEP, text, OnOffToStr(Node->loopback));
            snprintf(text, sizeof(text), "%s %3s  " TSEP, text, OnOffToStr(Node->iir));
            snprintf(text, sizeof(text), "%s %4u " TSEP, text, (unsigned int)err);
            snprintf(text, sizeof(text), "%s %7s " TSEP, text, u32val2Str(Node->rx_half_cnt));
            snprintf(text, sizeof(text), "%s %7s " TSEP, text, u32val2Str(Node->tx_half_cnt));
            snprintf(text, sizeof(text), "%s %7s " TSEP, text, u32val2Str(Node->rx_done_cnt));
            snprintf(text, sizeof(text), "%s %7s " TSEP, text, u32val2Str(Node->tx_done_cnt));
            const I2sConfig_t* I2sConfNode = I2sGetConfig(num);
            if(I2sConfNode) {
                snprintf(text, sizeof(text), "%s %6s " TSEP, text, I2sConfNode->name);
            }
            cli_printf(TSEP " %3u ", cnt);
            cli_printf("%s" CRLF, text);
            cnt++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

static bool stream_diag(uint8_t num, char const* prefix, SampleStream_t* const Node) {
    bool res = false;
    if(Node) {
        char text[200] = "";
        strcpy(text, TSEP);
        snprintf(text, sizeof(text), "%s %3u " TSEP, text, num);
        snprintf(text, sizeof(text), "%s %3s " TSEP, text, prefix);
        snprintf(text, sizeof(text), "%s %7u " TSEP, text, Node->cnt);
        snprintf(text, sizeof(text), "%s %7u " TSEP, text, Node->overflow);
        snprintf(text, sizeof(text), "%s %7u " TSEP, text, Node->index);
        snprintf(text, sizeof(text), "%s %7u " TSEP, text, Node->size);
        snprintf(text, sizeof(text), "%s %p " TSEP, text, Node->array);
        cli_printf("%s" CRLF, text);
        res = false;
    }
    return res;
}

bool i2s_stream_diag(uint8_t num) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "num"}, {5, "Src"}, {9, "cnt"}, {9, "overflow"}, {9, "idx"}, {9, "size"}, {9, "array"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        stream_diag(num, "Rx", &Node->Rx);
        stream_diag(num, "Tx", &Node->Tx);
        res = true;
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2s_rec_reverse_byte_order(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        LOG_INFO(I2S, "SampleSize:%u byte", sizeof(SampleType_t));
        uint32_t w = 0;
        for(w = 0; w < I2S_BUFFER_SIZE; w++) {
            if(2 == sizeof(SampleType_t)) {
                Node->RxBuffer[w] = reverse_byte_order_uint16(Node->RxBuffer[w]);
            }
            res = true;
        }
    }
    return res;
}

bool i2s_print_rx_ll(const I2sHandle_t* const Node) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "#"}, {8, "t"}, {6, "offset"}, {8, "RxLeft"}, {8, "RxRight"}, {8, "RxLeft"}, {8, "RxRight"},
    };

    uint32_t t = 0;
    uint32_t offset = 0;
    double t_step = 1.0 / ((double)Node->audio_freq_hz);
    double up_time = 0.0;
    LOG_INFO(I2S, "AudioFreq:%u Hz,Step:%s s", Node->audio_freq_hz, DoubleToStr(t_step));
    uint32_t rx_size = sizeof(Node->RxBuffer);
    uint32_t double_sample_size = 2 * sizeof(SampleType_t);
    uint32_t i2s_sample_cnt = rx_size / double_sample_size;
    LOG_INFO(I2S, "RxBuff,%u byte,SamSize:%u Byte,I2Ssam:%u Sam", rx_size, sizeof(SampleType_t), i2s_sample_cnt);
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(t = 0; t < i2s_sample_cnt; t++) {
        char text[200] = "";
        strcpy(text, TSEP);
        up_time = ((double)t) * t_step;
        offset = t * double_sample_size;
        I2sSampleType_t I2sSampleType = {0};
        /// I2sSampleType_t* I2sSamplePtr= (I2sSampleType_t*)    ( ((void*)Node->RxBuffer)+ offset);
        memcpy(&I2sSampleType, (void*)((void*)Node->RxBuffer) + offset, sizeof(I2sSampleType_t));
        snprintf(text, sizeof(text), "%s %3u " TSEP, text, t);
        snprintf(text, sizeof(text), "%s %4u " TSEP, text, offset);
        snprintf(text, sizeof(text), "%s %6s " TSEP, text, DoubleToStr(up_time));
        snprintf(text, sizeof(text), "%s %6d " TSEP, text, I2sSampleType.left);
        snprintf(text, sizeof(text), "%s %6d " TSEP, text, I2sSampleType.right);
        snprintf(text, sizeof(text), "%s 0x%04x " TSEP, text, (uint16_t)I2sSampleType.left);
        snprintf(text, sizeof(text), "%s 0x%04x " TSEP, text, (uint16_t)I2sSampleType.right);

        cli_printf("%s" CRLF, text);
        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool i2s_print_rx(uint8_t num) {
    bool res;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        res = i2s_print_rx_ll(Node);
    }
    return res;
}

#ifdef HAS_DFT
const char* I2sDftInfoToStr(const I2sHandle_t* const Node) {
    static char text[120] = "";
    if(Node) {
        strcpy(text, "");
        double freq_err_hz = Node->exp_freq_hz - Node->max_freq_hz;
        snprintf(text, sizeof(text), "%sExp:%6.1f Hz,", text, Node->exp_freq_hz);
        snprintf(text, sizeof(text), "%sReal:%6.1f Hz,", text, Node->max_freq_hz);
        snprintf(text, sizeof(text), "%sErr:%6.1f Hz", text, freq_err_hz);
    }

    return text;
}
#endif
