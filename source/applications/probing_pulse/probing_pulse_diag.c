#include "probing_pulse_diag.h"

#include "probing_pulse_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"
#include "float_diag.h"

const char* ProbingPulseToStr(ProbingPulseType_t probing_pulse) {
    const char* name ="?";
    switch( probing_pulse) {
        case PROBING_PULSE_TYPE_MONO: name ="Mono"; break;
        case PROBING_PULSE_TYPE_M_SEQ: name ="M_SEQ"; break;
        case PROBING_PULSE_TYPE_BAKER13: name ="BAKER13"; break;
        case PROBING_PULSE_TYPE_CHIRP: name ="CHIRP"; break;
        default : name ="?"; break;
    }
    return name;
}

const char* ProbingPulseConfigToStr(const ProbingPulseConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sFst:%f Hz,", text, Config->frequency1);
        snprintf(text, sizeof(text), "%sFend:%f Hz,", text, Config->frequency2);
        snprintf(text, sizeof(text), "%sdT:%f s,", text, Config->signal_duration_s);
        snprintf(text, sizeof(text), "%sAmp:%f,", text, Config->amplitude);
        snprintf(text, sizeof(text), "%sPerPerChip:%u,", text, Config->periods_per_chip);
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sFile:%s,", text, Config->sonar_signal_wav_name);
        snprintf(text, sizeof(text), "%sSignal:%s,", text, ProbingPulseToStr(Config->zonding_impulse_type));
    }
    return text;
}

const char* ProbingPulseNodeToStr(const ProbingPulseHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sTxCnt:%u,", text, Node->tx_cnt);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool probing_pulse_diag_one(uint8_t num) {
    bool res = false;
    const ProbingPulseConfig_t *Config = ProbingPulseGetConfig(num);
    if(Config) {
        LOG_INFO(PROBING_PULSE, "%s", ProbingPulseConfigToStr(Config));
        ProbingPulseHandle_t *Node = ProbingPulseGetNode(num);
        if(Node) {
            LOG_INFO(PROBING_PULSE, "%s", ProbingPulseNodeToStr(Node));
            res = true;
        }
    }

    return res;
}

bool probing_pulse_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
            { 5, "No" },
            { 15,  "Type" } ,
            { 7, "TxCnt" },
            { 7, "name" },
            { 6, "perPerChip" },
            { 15,  "Amp" } ,
            { 15,  "F1" } ,
            { 15,  "F2" } ,
            { 15,  "SigDur" },
            { 6, "WAV" },
        };


    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    uint16_t probing_pulse_cnt = probing_pulse_get_cnt();
    for (i = 0; i < probing_pulse_cnt; i++) {
        ProbingPulseHandle_t* Node=ProbingPulseGetNode(i);
        if(Node) {
            char temp[150] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, Node->num);
            snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, ProbingPulseToStr(Node->zonding_impulse_type));
            snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, Node->tx_cnt);
            snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, Node->name);
            snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, Node->periods_per_chip);
            snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, FloatToStr(Node->amplitude,2));
            snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, FloatToStr(Node->frequency1,2));
            snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, FloatToStr(Node->frequency2,2));
            snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, FloatToStr(Node->signal_duration_s,2));
            snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, Node->sonar_signal_wav_name);
            cli_printf("%s" CRLF, temp);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}


