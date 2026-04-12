#include "median_filter_diag.h"

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "circular_buffer_diag.h"
#include "common_diag.h"
#include "debug_info.h"
#include "log.h"
#include "median_filter.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "win_utils.h"
#include "writer_config.h"
#ifdef HAS_FILE_PC
#include "file_pc.h"
#endif

bool MedianFilterDiagCoefficient(uint8_t num) {
    bool res = false;
    MedianFilterHandle_t* Node = MedianFilterGetNode(num);
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

bool median_filter_diag_one(uint8_t num) {
    bool res = false;
    const MedianFilterConfig_t* Config = MedianFilterGetConfig(num);
    if(Config) {
        LOG_INFO(MEDIAN_FILTER, "%s", MedianFilterConfigToStr(Config));
        MedianFilterHandle_t* Node = MedianFilterGetNode(num);
        if(Node) {
            LOG_INFO(MEDIAN_FILTER, "%s", MedianFilterNodeToStr(Node));
            res = MedianFilterDiagCoefficient(num);
        }
    }
    return res;
}

bool median_filter_diag(void) {
    bool res = false;
    char temp_str[120];
    static const table_col_t cols[] = {
        {5, "num"},
        {5, "size"},
        {5, "cap"},
    };
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = median_filter_get_cnt();
    uint8_t median_filter_num = 0;
    for(median_filter_num = 1; median_filter_num <= cnt; median_filter_num++) {
        MedianFilterHandle_t* Node = MedianFilterGetNode(median_filter_num);
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

const char* MedianFilterNodeToStr(const MedianFilterHandle_t* const Node) {

    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sProcnt:%u,", text, Node->proc_cnt);
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sInit:%u,", text, Node->init);
        snprintf(text, sizeof(text), "%sM:%u,", text, Node->size);
        snprintf(text, sizeof(text), "%s/%u,", text, Node->max_size);
        snprintf(text, sizeof(text), "%sFsam:%s Hz,", text, DoubleToStr(Node->sample_rate_hz));
        snprintf(text, sizeof(text), "%sCbX:%s,", text, CircularBufferStateToStr(&Node->CircularBuffer.state));
    }
    return text;
}

const char* MedianFilterConfigToStr(const MedianFilterConfig_t* const Config) {
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
bool median_filter_calc_frequency_response_norm(uint8_t num) {
    bool res = false;
    char* file_name = "MEDIAN_FILTERFrequencyResponse.csv";
    file_pc_delete(file_name);
    MedianFilterHandle_t* Node = MedianFilterGetNode(num);
    if(Node) {
        LOG_INFO(MEDIAN_FILTER, "%s", MedianFilterNodeToStr(Node));
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
bool median_filter_calc_frequency_response(uint8_t num) {
    bool res = false;
    char* file_name = "MEDIAN_FILTERF_requencyResponse.csv";
    file_pc_delete(file_name);
    MedianFilterHandle_t* Node = MedianFilterGetNode(num);
    if(Node) {
        LOG_INFO(MEDIAN_FILTER, "%s", MedianFilterNodeToStr(Node));
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
