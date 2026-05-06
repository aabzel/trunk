#include "bpsk_4fs_diag.h"


#include <stdio.h>
#include <string.h>

#include "num_to_str.h"
#include "interfaces_diag.h"
#include "log.h"
#include "bpsk_4fs_mcal.h"
#include "dsp_diag.h"
#include "quad_mix_4fs.h"
#include "float_diag.h"
#include "table_utils.h"
#include "writer_config.h"

static char temp[300] = "?";

const char* Bpsk4fsConfigToStr(const  Bpsk4fsConfig_t* const Config){
    if(Config) {
        strcpy(temp, "");
        snprintf(temp, sizeof(temp), "%sN:%u,", temp, Config->num);
        snprintf(temp, sizeof(temp), "%sDDS:%u,", temp, Config->dds_num);
        snprintf(temp, sizeof(temp), "%sDecimator:%u,", temp, Config->decimator_num);
        snprintf(temp, sizeof(temp), "%sQM:%u,", temp, Config->quad_mix_4fs_num);
        snprintf(temp, sizeof(temp), "%sLoopFiltType:%s,", temp, DspFilterTypeToStr(Config->filter_loop_type));
        snprintf(temp, sizeof(temp), "%sLoopFilt:%u,", temp, Config->filter_loop_num);
        snprintf(temp, sizeof(temp), "%sLoopFirOrder:%u,", temp, Config->filter_order);
        snprintf(temp, sizeof(temp), "%sRate:%u Bit/s,", temp, Config->bit_rate);
        snprintf(temp, sizeof(temp), "%sAmp:%u PCM,", temp, Config->amplitude);
        snprintf(temp, sizeof(temp), "%sBitOrder:%s,", temp, IfBitOrderToStr(Config->bit_order));
        snprintf(temp, sizeof(temp), "%sFsam:%sHz,", temp, FloatToStr((float)Config->sampling_frequency_hz,2));
        snprintf(temp, sizeof(temp), "%sFcar:%sHz", temp, FloatToStr((float)Config->carrier_frequency_hz,2));
    }
    return temp;
}

const char* Bpsk4fsNodeToStr(const Bpsk4fsHandle_t* const Node){
    strcpy(temp, "");
    if(Node) {
        snprintf(temp, sizeof(temp), "%sN:%u,", temp, Node->num);
        snprintf(temp, sizeof(temp), "%sRxErr:%u,", temp, Node->error_cnt);
        snprintf(temp, sizeof(temp), "%sSamN:%u Sam,", temp, Node->sam_n);
        snprintf(temp, sizeof(temp), "%sHalfCnt:%u,", temp, Node->half_cplt_done_cnt_prev);
        snprintf(temp, sizeof(temp), "%sEndCnt:%u,", temp, Node->chan_conv_end_cnt_prev);
        snprintf(temp, sizeof(temp), "%sLost:%u,", temp, Node->lost_block);

        snprintf(temp, sizeof(temp), "%sSam:%u Sam,", temp, Node->sample_cnt);
        //snprintf(temp, sizeof(temp), "%sRate:%u Bit/s,", temp, Node->bit_rate);
        snprintf(temp, sizeof(temp), "%sCarrPer:%s s,", temp, FloatToStr(Node->carrier_period_s,2));
        snprintf(temp, sizeof(temp), "%sSamInChip:%u,", temp, Node->sample_per_chip);
        snprintf(temp, sizeof(temp), "%sCarPerInChip:%u,", temp, Node->carrier_periods_per_chip);
        snprintf(temp, sizeof(temp), "%sTsam:%s s,", temp, FloatToStr(Node->sample_time_s,2));
        snprintf(temp, sizeof(temp), "%sChipTime:%ss,", temp, FloatToStr(Node->chip_dutation_s,2));
        //snprintf(temp, sizeof(temp), "%sDecimator:%u,", temp, Node->decimator_num);
        //snprintf(temp, sizeof(temp), "%sQM:%u,", temp, Node->quad_mix_4fs_num);
        //snprintf(temp, sizeof(temp), "%sFirLoop:%u,", temp, Node->filter_loop_num);
        //snprintf(temp, sizeof(temp), "%sFirOrder:%u,", temp, Node->filter_order);
        snprintf(temp, sizeof(temp), "%sAmp:%u PCM,", temp, Node->amplitude);
        snprintf(temp, sizeof(temp), "%sBitOrder:%s,", temp, IfBitOrderToStr(Node->bit_order));
        snprintf(temp, sizeof(temp), "%sFsam:%sHz,", temp, FloatToStr((float)Node->sampling_frequency_hz,2));
        snprintf(temp, sizeof(temp), "%sFcar:%sHz", temp, FloatToStr((float)Node->carrier_frequency_hz,2));
    }
    return temp;
}

bool bpsk_4fs_print_samples(Bpsk4fsHandle_t* Node) {
    bool res = false;
    LOG_WARNING(BPSK_4FS,"Print %u Samples", Node->sample_cnt);
    if(Node){
        static const table_col_t cols[] = {
                         {5, "No"}, {12, "UpTime"},  {12, "SampleDec"},  };
        float up_time_s = 0.0;
        LOG_INFO(BPSK_4FS, "SampleCnt: %u", Node->sample_cnt);
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        uint32_t s = 0;
        for(s = 0; s < Node->sample_cnt; s++) {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, s + 1);
            up_time_s = ((float)(s + 1))/((float)Node->sampling_frequency_hz);
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

bool Bpsk4fsComposeLogLine(const Bpsk4fsHandle_t* const Node, char* const in_temp, uint32_t size) {
    bool res = false;
    if (Node) {
        if (in_temp) {
            if (size) {
                strcpy(in_temp, "");
                QuadMix4fsHandle_t *QM = QuadMix4fsGetNode(1);
                snprintf(in_temp, size, "%s%f,", in_temp, Node->time_s); //CSV index:0
                snprintf(in_temp, size, "%s%f,", in_temp, QM->SdrI.AfterFilt); //CSV index:1
                snprintf(in_temp, size, "%s%f,", in_temp, QM->SdrQ.AfterFilt); //CSV index:2
                snprintf(in_temp, size, "%s%d,", in_temp, Node->data); //CSV index:4
                snprintf(in_temp, size, "%s%d,", in_temp, Node->sample); //CSV index:5
                snprintf(in_temp, size, "%s\n", in_temp); //4
            }
        }
    }
    return res;
}

bool bpsk_4fs_diag(uint8_t num) {
    bool res = false;
    Bpsk4fsHandle_t* Node=Bpsk4fsGetNode(num);
    if(Node) {
        LOG_INFO(BPSK_4FS,"%s",Bpsk4fsNodeToStr(Node));
        res = true;
    }

    Bpsk4fsConfig_t* Config=Bpsk4fsGetConfig(num);
    if(Config) {
        LOG_INFO(BPSK_4FS,"%s",Bpsk4fsConfigToStr(Config));
        res = true;
    }
    return res;
}
