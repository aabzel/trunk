#include "bpsk_diag.h"


#include <stdio.h>
#include <string.h>

#include "num_to_str.h"
#include "interfaces_diag.h"
#include "log.h"
#include "dsp_diag.h"
#include "quadrature_mixer.h"
#include "table_utils.h"
#include "writer_config.h"

const char* BpskConfigToStr(const  BpskConfig_t* const Config){
    static char text[300] = "?";
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sDDS:%u,", text, Config->dds_num);
        snprintf(text, sizeof(text), "%sDecimator:%u,", text, Config->decimator_num);
        snprintf(text, sizeof(text), "%sQM:%u,", text, Config->quadrature_mixer_num);
        snprintf(text, sizeof(text), "%sLoopFiltType:%s,", text, DspFilterTypeToStr(Config->filter_loop_type));
        snprintf(text, sizeof(text), "%sLoopFilt:%u,", text, Config->filter_loop_num);
        snprintf(text, sizeof(text), "%sLoopFirOrder:%u,", text, Config->filter_order);
        snprintf(text, sizeof(text), "%sRate:%u Bit/s,", text, Config->bit_rate);
        snprintf(text, sizeof(text), "%sAmp:%u PCM,", text, Config->amplitude);
        snprintf(text, sizeof(text), "%sBitOrder:%s,", text, IfBitOrderToStr(Config->bit_order));
        snprintf(text, sizeof(text), "%sFsam:%sHz,", text, DoubleToStr((double)Config->sampling_frequency_hz));
        snprintf(text, sizeof(text), "%sFcar:%sHz", text, DoubleToStr((double)Config->carrier_frequency_hz));
    }
    return text;
}

const char* BpskNodeToStr(const BpskHandle_t* const Node){
    static char text[300] = "?";
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sRate:%u Bit/s,", text, Node->bit_rate);
        snprintf(text, sizeof(text), "%sSam:%u Sam,", text, Node->sample_cnt);
        snprintf(text, sizeof(text), "%sCarrPer:%s s,", text, DoubleToStr(Node->carrier_period_s));
        snprintf(text, sizeof(text), "%sSamInChip:%u,", text, Node->sample_per_chip);
        snprintf(text, sizeof(text), "%sCarPerInChip:%u,", text, Node->carrier_periods_per_chip);
        snprintf(text, sizeof(text), "%sTsam:%s s,", text, DoubleToStr(Node->sample_time_s));
        snprintf(text, sizeof(text), "%sChipTime:%ss,", text, DoubleToStr(Node->chip_dutation_s));
        snprintf(text, sizeof(text), "%sDecimator:%u,", text, Node->decimator_num);
        snprintf(text, sizeof(text), "%sQM:%u,", text, Node->quadrature_mixer_num);
        snprintf(text, sizeof(text), "%sFirLoop:%u,", text, Node->filter_loop_num);
        snprintf(text, sizeof(text), "%sFirOrder:%u,", text, Node->filter_order);
        snprintf(text, sizeof(text), "%sAmp:%u PCM,", text, Node->amplitude);
        snprintf(text, sizeof(text), "%sBitOrder:%s,", text, IfBitOrderToStr(Node->bit_order));
        snprintf(text, sizeof(text), "%sFsam:%sHz,", text, DoubleToStr((double)Node->sampling_frequency_hz));
        snprintf(text, sizeof(text), "%sFcar:%sHz", text, DoubleToStr((double)Node->carrier_frequency_hz));
    }
    return text;
}

bool bpsk_print_samples(BpskHandle_t* Node) {
    bool res = false;
    LOG_WARNING(BPSK,"Print %u Samples", Node->sample_cnt);
    if(Node){
        static const table_col_t cols[] = {
                         {5, "No"}, {12, "UpTime"},  {12, "SampleDec"},  };
        double up_time_s = 0.0;
        LOG_INFO(BPSK, "SampleCnt: %u", Node->sample_cnt);
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        uint32_t s = 0;
        for(s = 0; s < Node->sample_cnt; s++) {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, s + 1);
            up_time_s = ((double)(s + 1))/((double)Node->sampling_frequency_hz);
            cli_printf(" %10.8f " TSEP, up_time_s);
            cli_printf(" %10d " TSEP, Node->samples[s]);
            cli_printf(" 0x%08x " TSEP, Node->samples[s]);

            cli_printf(CRLF);
            res = true;
        }

        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

bool BpskComposeLogLine(const BpskHandle_t* const Node, char* const text, uint32_t size){
    bool res = false;
    if(Node) {
        if(text) {
            if(size) {
                strcpy(text, "");
                QuadratureMixerHandle_t* QM=QuadratureMixerGetNode(1);
                snprintf(text, size, "%s%f,", text, Node->time_s); //CSV index:0
                snprintf(text, size, "%s%f,", text, QM->SdrI.AfterFilt);//CSV index:1
                snprintf(text, size, "%s%f,", text, QM->SdrQ.AfterFilt);//CSV index:2
                snprintf(text, size, "%s%f,", text, Node->lo_phase_rad);//CSV index:3
                snprintf(text, size, "%s%d,", text, Node->data);//CSV index:4
                snprintf(text, size, "%s%d,", text, Node->sample); //CSV index:5
                snprintf(text, size, "%s\n", text);//4
            }
        }
    }
    return res;
}

