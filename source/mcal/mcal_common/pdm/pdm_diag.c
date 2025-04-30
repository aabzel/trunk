#include "pdm_diag.h"

#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "common_diag.h"
#ifdef HAS_COMPLEX_DIAG
#include "complex_diag.h"
#endif
#ifdef HAS_DFT
#include "dft.h"
#endif
#include "gpio_diag.h"
#include "log.h"
#include "pdm_custom_diag.h"
#include "pdm_drv.h"
#include "table_utils.h"
#include "time_mcal.h"
#include "writer_config.h"

const char* PdmEdge2Str(PdmEdge_t edge) {
    const char* name = "?";
    switch((uint8_t)edge) {
    case PDM_EDGE_LEFT_FALLING:
        name = "Falling";
        break;
    case PDM_EDGE_LEFT_RISING:
        name = "Rising";
        break;
    }
    return name;
}

const char* PdmMode2Str(PdmMode_t pdm_mode) {
    const char* name = "?";
    switch((uint8_t)pdm_mode) {
    case PDM_MODE_STEREO:
        name = "Stereo";
        break;
    case PDM_MODE_MONO:
        name = "Mono";
        break;
    }
    return name;
}

const char* MasterClk2Str(PdmMasterClk_t master_clk) {
    const char* name = "?";
    switch((uint8_t)master_clk) {
    case PDM_MASTER_CLK_CPU_PLL:
        name = "CpuPll";
        break;
    case PDM_MASTER_CLK_AUDIO_PLL:
        name = "AudioPll";
        break;
    }
    return name;
}

const char* MicMode2Str(MicMode_t mode) {
    const char* name = "?";
    switch((uint8_t)mode) {
    case MIC_MODE_SINGLE:
        name = "Single";
        break;
    case MIC_MODE_CONTINUOUS:
        name = "Continuous";
        break;
    }
    return name;
}

bool pdm_print_sample(uint8_t num) {
    bool res = false;
    PdmHandle_t* Node = PdmGetNode(num);
    if(Node) {
        LOG_INFO(PDM, "PDM%u, Print %u Samples", num, Node->samples_cnt);
        double step = 1.0 / ((double)Node->sample_rate_hz);
        if(Node->buf_toogle) {
            array_i16_print((const int16_t* const)Node->buf + Node->samples_cnt, Node->samples_cnt, step);
            array_i16_print((const int16_t* const)Node->buf, Node->samples_cnt, step);
        } else {
            array_i16_print((const int16_t* const)Node->buf, Node->samples_cnt, step);
            array_i16_print((const int16_t* const)Node->buf + Node->samples_cnt, Node->samples_cnt, step);
        }
        res = true;
    } else {
        LOG_ERROR(PDM, "PDM%u NodeErr", num);
    }
    return res;
}

bool PdmDiagConfig(const PdmConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(PDM, "Config");
        LOG_INFO(PDM, "Clk:%s", GpioPadToStr(Config->PadClk));
        LOG_INFO(PDM, "Din:%s", GpioPadToStr(Config->PadDin));
        LOG_INFO(PDM, "Edge:%s", PdmEdge2Str(Config->edge));
        LOG_INFO(PDM, "Mode:%s", PdmMode2Str(Config->pdm_mode));
        LOG_INFO(PDM, "MicMode:%s", MicMode2Str(Config->mic_mode));
        LOG_INFO(PDM, "Freq:%u Hz", Config->frequency_hz);
        LOG_INFO(PDM, "IrqPri:%u", Config->irq_priority);
        LOG_INFO(PDM, "MasterClk:%s", MasterClk2Str(Config->master_clk));
        LOG_INFO(PDM, "Bitness:%u bit", Config->pcm_bit);
        LOG_INFO(PDM, "SamplesCnt:%u", Config->samples_cnt);
        LOG_INFO(PDM, "SampleRate:%u Hz", Config->sample_rate_hz);
        LOG_INFO(PDM, "GainLeft: %d", (int8_t)Config->Gain.left);
        LOG_INFO(PDM, "GainRight: %d", (int8_t)Config->Gain.right);
        LOG_INFO(PDM, "Ratio: %u", Config->ratio);
        LOG_INFO(PDM, "Name: %s", Config->name);
        res = true;
    }
    return res;
}

static bool PdmDiagNode(const PdmHandle_t* const Node) {
    bool res = false;
    if(Node) {
        res = true;
        char log_line[150];
        static const table_col_t cols[] = {
            {3, "Num"}, {5, "init"}, {12, "ItCnt"}, {7, "Start"}, {7, "Stop"}, {5, "Idx"}, {12, "Error"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %1u " TSEP, log_line, Node->num);
        snprintf(log_line, sizeof(log_line), "%s %s " TSEP, log_line, YesNo2Str(Node->init_done));
        snprintf(log_line, sizeof(log_line), "%s %10u " TSEP, log_line, Node->int_cnt);
        snprintf(log_line, sizeof(log_line), "%s %10u " TSEP, log_line, Node->rx_sample_cnt);
        snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->start_cnt);
        snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->stop_cnt);
        snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->buf_toogle);
        snprintf(log_line, sizeof(log_line), "%s %10u " TSEP, log_line, Node->error_cnt);
        cli_printf("%s" CRLF, log_line);

        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}

bool pdm_diag_one(uint8_t num) {
    bool res = false;
    const PdmStaticInfo_t* StaticNode = PdmGetStaticNode(num);
    if(StaticNode) {
        PdmStaticInfoDiag(StaticNode);
        const PdmConfig_t* Config = PdmGetConfig(num);
        if(Config) {
            PdmDiagConfig(Config);
            PdmHandle_t* Node = PdmGetNode(num);
            if(Node) {
                res = PdmDiagNode(Node);
            }
        }
    }

    return res;
}

bool pdm_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {3, "Num"}, {5, "init"}, {12, "ItCnt"}, {12, "RxSample"}, {7, "Start"}, {7, "Stop"}, {5, "Idx"}, {12, "Error"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint16_t pdm_cnt = pdm_get_cnt();
    uint8_t i = 0;
    for(i = 0; i < pdm_cnt; i++) {
        PdmHandle_t* Node = PdmGetNode(i);
        if(Node) {
            char log_line[150];
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %1u " TSEP, log_line, Node->num);
            snprintf(log_line, sizeof(log_line), "%s %s " TSEP, log_line, YesNo2Str(Node->init_done));
            snprintf(log_line, sizeof(log_line), "%s %10u " TSEP, log_line, Node->int_cnt);
            snprintf(log_line, sizeof(log_line), "%s %10u " TSEP, log_line, Node->rx_sample_cnt);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->start_cnt);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->stop_cnt);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->buf_toogle);
            snprintf(log_line, sizeof(log_line), "%s %10u " TSEP, log_line, Node->error_cnt);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
