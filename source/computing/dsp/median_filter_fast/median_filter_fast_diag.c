#include "median_filter_fast_diag.h"

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "bin_heap_diag.h"
#include "circular_buffer_diag.h"
#include "common_diag.h"
#include "debug_info.h"
#include "hash_table_s8_diag.h"
#include "log.h"
#include "median_filter_fast.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "win_utils.h"
#include "writer_config.h"
#ifdef HAS_FILE_PC
#include "file_pc.h"
#endif

bool MedianFilterFastDiagCoefficient(uint8_t num) {
    bool res = false;
    MedianFilterFastHandle_t* Node = MedianFilterFastGetNode(num);
    if(Node) {
        static const table_col_t cols[] = {{5, "i"}, {10, "back"}, {10, "forward"}, {14, "a"}, {14, "b"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        uint32_t i = 0;
        for(i = 0; i < Node->size; i++) {
            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %3u " TSEP, text, i);
            cli_printf("%s" CRLF, text);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}

bool median_filter_fast_diag_one(uint8_t num) {
    bool res = false;
    const MedianFilterFastConfig_t* Config = MedianFilterFastGetConfig(num);
    if(Config) {
        LOG_INFO(MEDIAN_FILTER_FAST, "%s", MedianFilterFastConfigToStr(Config));
        MedianFilterFastHandle_t* Node = MedianFilterFastGetNode(num);
        if(Node) {
            LOG_INFO(MEDIAN_FILTER_FAST, "%s", MedianFilterFastNodeToStr(Node));
            res = MedianFilterFastDiagCoefficient(num);
        }
    }
    return res;
}

bool median_filter_fast_diag(void) {
    bool res = false;
    char temp_str[120];
    static const table_col_t cols[] = {
        {5, "num"},
        {5, "size"},
        {5, "cap"},
    };
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = median_filter_fast_get_cnt();
    uint8_t median_filter_fast_num = 0;
    for(median_filter_fast_num = 1; median_filter_fast_num <= cnt; median_filter_fast_num++) {
        MedianFilterFastHandle_t* Node = MedianFilterFastGetNode(median_filter_fast_num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %2u  " TSEP, temp_str, Node->num);
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOff2Str(Node->init));
            cli_printf("%s" CRLF, temp_str);
            num++;
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

const char* MedianFilterVirtSizeToStr(const  MedianFilterFastHandle_t* const Node){
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSmall:%u,", text, Node->small_size);
        snprintf(text, sizeof(text), "%sLarge:%u,", text, Node->large_size);
    }
    return text;
}

const char* MedianFilterFastNodeToStr(const MedianFilterFastHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sK:%u,", text, Node->size);

        snprintf(text, sizeof(text), "%sSsz:%u,", text, Node->small_size);
        snprintf(text, sizeof(text), "%sLsz:%u,", text, Node->large_size);

        snprintf(text, sizeof(text), "%sSmall:[%s],", text, BinHeapToStr(&Node->Small));
        snprintf(text, sizeof(text), "%sLarge:[%s],", text, BinHeapToStr(&Node->Large));
#ifdef HAS_MFF_HASH_TABLE
        snprintf(text, sizeof(text), "%sToDel:[%s],", text, HashTableS8NodeToStr(&Node->ToDelete));
#endif
        snprintf(text, sizeof(text), "%sProcnt:%u,", text, Node->proc_cnt);
        // snprintf(text, sizeof(text), "%sFsam:%s Hz,", text, DoubleToStr(Node->sample_rate_hz));
        snprintf(text, sizeof(text), "%sCbX:%s,", text, CircularBufferStateToStr(&Node->SlidingWindow.state));
    }
    return text;
}

const char* MedianFilterFastConfigToStr(const MedianFilterFastConfig_t* const Config) {
    static char lText[200] = {0};
    if(Config) {
        strcpy(lText, "CFG:");
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Config->num);
        snprintf(lText, sizeof(lText), "%s%s,", lText, Config->name);
        snprintf(lText, sizeof(lText), "%sM:%u", lText, Config->size);
        snprintf(lText, sizeof(lText), "%s/%u,", lText, Config->max_size);
        snprintf(lText, sizeof(lText), "%sFsam:%s Hz,", lText, DoubleToStr((double)Config->sample_rate_hz));
    }
    return lText;
}

#ifdef HAS_FILE_PC
bool median_filter_fast_calc_frequency_response_norm(uint8_t num) {
    bool res = false;
    char* file_name = "MEDIAN_FILTER_FASTFrequencyResponse.csv";
    file_pc_delete(file_name);
    MedianFilterFastHandle_t* Node = MedianFilterFastGetNode(num);
    if(Node) {
        LOG_INFO(MEDIAN_FILTER_FAST, "%s", MedianFilterFastNodeToStr(Node));
        float f_norm = 0;
        for(f_norm = 0; f_norm < (0.5);) {
            strcpy(text, "");
            snprintf(text, sizeof(text), "%s%f,", text, f_norm);
            res = file_pc_print_line(file_name, text, strlen(text));
            cli_printf("\r%s", ProgressRealToStr(f_norm, 1.0 / 2.0));
            if(f_norm < 0.01) {
                f_norm += 0.00001;
            } else {
                f_norm += 0.001;
            }
        }
        char command[300] = "";
        snprintf(command, sizeof(command), "python.exe plot_csv_file.py %s frequency Amplitude", file_name);
        res = win_cmd_run(command);
    }
    return res;
}
#endif

#ifdef HAS_FILE_PC
// 10000  1Hz
bool median_filter_fast_calc_frequency_response(uint8_t num) {
    bool res = false;
    char* file_name = "MEDIAN_FILTER_FASTF_requencyResponse.csv";
    file_pc_delete(file_name);
    MedianFilterFastHandle_t* Node = MedianFilterFastGetNode(num);
    if(Node) {
        LOG_INFO(MEDIAN_FILTER_FAST, "%s", MedianFilterFastNodeToStr(Node));
        float f_hz = 0;
        for(f_hz = 0; f_hz < (Node->sample_rate_hz / 2.0);) {
            float f_real_hz = (float)f_hz;

            strcpy(text, "");
            snprintf(text, sizeof(text), "%s%f,", text, f_real_hz);
            res = file_pc_print_line(file_name, text, strlen(text));
            if(0 == (((uint32_t)f_hz) % (((uint32_t)Node->sample_rate_hz) / 100))) {
                cli_printf("\r%s", ProgressToStr((uint32_t)f_hz, Node->sample_rate_hz / 2.0));
            }
            if(f_hz < 10.0) {
                f_hz += 0.1;
            } else {
                f_hz += 2.0;
            }
        }
        char command[300] = "";
        snprintf(command, sizeof(command), "python.exe plot_csv_file.py %s frequency Amplitude", file_name);
        res = win_cmd_run(command);
    }
    return res;
}
#endif

const char* DirToStr(const MedianFilterBalanceDir_t balance_dir) {
    char* name = "?";
    switch(balance_dir) {
    case MED_FILT_BALANCE_DIR_DOWN:
        name = "Down";
        break;
    case MED_FILT_BALANCE_DIR_UP:
        name = "Up";
        break;
    case MED_FILT_BALANCE_DIR_NONE:
        name = "None";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}
