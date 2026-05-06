#include "iir_diag.h"

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "circular_buffer_diag.h"
#include "common_diag.h"
#include "debug_info.h"
#include "iir.h"
#include "log.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_WIN
#include "win_utils.h"
#endif

#ifdef HAS_FILE_PC
#include "file_pc.h"
#endif

bool IirDiagCoefficient(uint8_t num) {
    bool res = false;
    IirHandle_t* Node = IirGetNode(num);
    if(Node) {
        static const table_col_t cols[] = {{5, "i"}, {10, "back"}, {10, "forward"}, {14, "a"}, {14, "b"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        char temp[300] = "?";
        uint32_t i = 0;
        for(i = 0; i < Node->size; i++) {
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, i);
            snprintf(temp, sizeof(temp), "%s %8s " TSEP, temp, DoubleToStr(Node->a[i]));
            snprintf(temp, sizeof(temp), "%s %8s " TSEP, temp, DoubleToStr(Node->b[i]));
            snprintf(temp, sizeof(temp), "%s %10.9f " TSEP, temp, Node->a[i]);
            snprintf(temp, sizeof(temp), "%s %10.9f " TSEP, temp, Node->b[i]);
            cli_printf("%s" CRLF, temp);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}

bool iir_diag_one(uint8_t num) {
    bool res = false;
    const IirConfig_t* Config = IirGetConfig(num);
    if(Config) {
        LOG_INFO(IIR, "%s", IirConfigToStr(Config));
        IirHandle_t* Node = IirGetNode(num);
        if(Node) {
            LOG_INFO(IIR, "%s", IirNodeToStr(Node));
            res = IirDiagCoefficient(num);
        }
    }
    return res;
}

bool iir_diag(void) {
    bool res = false;
    char temp_str[120];
    static const table_col_t cols[] = {
        {5, "num"},
        {5, "size"},
        {5, "cap"},
    };
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = iir_get_cnt();
    uint8_t iir_num = 0;
    for(iir_num = 1; iir_num <= cnt; iir_num++) {
        IirHandle_t* Node = IirGetNode(iir_num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %2u  " TSEP, temp_str, Node->num);
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOffToStr(Node->init));
            cli_printf("%s" CRLF, temp_str);
            num++;
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

const char* IirNodeToStr(const IirHandle_t* const Node) {
    static char temp[300] = "?";
    if(Node) {
        strcpy(temp, "");
        snprintf(temp, sizeof(temp), "%sProcnt:%u,", temp, Node->proc_cnt);
        snprintf(temp, sizeof(temp), "%sN:%u,", temp, Node->num);
        snprintf(temp, sizeof(temp), "%sInit:%u,", temp, Node->init);
        snprintf(temp, sizeof(temp), "%sM:%u,", temp, Node->size);
        snprintf(temp, sizeof(temp), "%s/%u,", temp, Node->max_size);
        snprintf(temp, sizeof(temp), "%sFsam:%s Hz,", temp, DoubleToStr(Node->sample_rate_hz));
        snprintf(temp, sizeof(temp), "%sFcut:%s Hz,", temp, DoubleToStr(Node->cut_off_freq_hz));
        snprintf(temp, sizeof(temp), "%sCbX:%s,", temp, CircularBufferStateToStr(&Node->xIndexer));
        snprintf(temp, sizeof(temp), "%sCbY:%s,", temp, CircularBufferStateToStr(&Node->xIndexer));
    }
    return temp;
}

const char* IirConfigToStr(const IirConfig_t* const Config) {
    static char temp[300] = "?";
    if(Config) {
        strcpy(temp, "CFG:");
        snprintf(temp, sizeof(temp), "%sN:%u,", temp, Config->num);
        snprintf(temp, sizeof(temp), "%s%s,", temp, Config->name);
        snprintf(temp, sizeof(temp), "%sM:%u", temp, Config->size);
        snprintf(temp, sizeof(temp), "%s/%u,", temp, Config->max_size);
        snprintf(temp, sizeof(temp), "%sFsam:%s Hz,", temp, DoubleToStr(Config->sample_rate_hz));
        snprintf(temp, sizeof(temp), "%sFcut:%s Hz,", temp, DoubleToStr(Config->cut_off_freq_hz));
    }
    return temp;
}

static float complex filter_delay_link(uint32_t n, float F_hz, float F_sam, bool is_norm_freq) {
    float complex exp = 0.0;
    float omega = 0;
    float T_a = 0;
    if(is_norm_freq) {
        T_a = 1.0;
        omega = 2.0 * M_PI * F_hz;
    } else {
        T_a = 1.0 / F_sam;
        omega = 2.0 * M_PI * F_hz;
    }
    exp = cos(n * omega * T_a) - I * sin(n * omega * T_a);
    return exp;
}

static float complex iir_calc_feed_forward_ll(IirHandle_t* Node, float f_hz, bool is_norm_freq) {
    float complex numerator = 0.0;
    uint32_t n = 0;
    for(n = 0; n < Node->size; n++) {
        numerator += Node->b[n] * filter_delay_link(n, f_hz, Node->sample_rate_hz, is_norm_freq);
    }
    return numerator;
}

static float complex iir_calc_feed_back_ll(IirHandle_t* Node, float f_hz, bool is_norm_freq) {
    float complex denominator = 1.0;
    uint32_t n = 0;
    for(n = 1; n < Node->size; n++) {
        denominator += Node->a[n] * filter_delay_link(n, f_hz, Node->sample_rate_hz, is_norm_freq);
    }
    return denominator;
}

bool iir_calc_frequency_response_norm(uint8_t num) {
    bool res = false;
    char* file_name = "IIRFrequencyResponse.csv";
#ifdef HAS_FILE_PC
    file_pc_delete(file_name);
#endif
    IirHandle_t* Node = IirGetNode(num);
    if(Node) {
        LOG_INFO(IIR, "%s", IirNodeToStr(Node));
        float f_norm = 0;
        for(f_norm = 0; f_norm < (0.5);) {
            float complex numerator = iir_calc_feed_forward_ll(Node, f_norm, true);
            float complex denominator = iir_calc_feed_back_ll(Node, f_norm, true);
            float complex Amplitude = numerator / denominator;
            char temp[300] = "?";
            strcpy(temp, "");
            snprintf(temp, sizeof(temp), "%s%f,", temp, f_norm);
            snprintf(temp, sizeof(temp), "%s%f", temp, cabs(Amplitude));
#ifdef HAS_FILE_PC
            res = file_pc_print_line(file_name, temp, strlen(temp));
#endif
            cli_printf("\r%s", ProgressRealToStr(f_norm, 1.0 / 2.0));
            if(f_norm < 0.01) {
                f_norm += 0.00001;
            } else {
                f_norm += 0.001;
            }
        }
#ifdef HAS_FILE_PC
        char command[300] = "";
        snprintf(command, sizeof(command), "python.exe plot_csv_file.py %s frequency Amplitude", file_name);
        res = win_cmd_run(command);
#endif
    }
    return res;
}

// 10000  1Hz
bool iir_calc_frequency_response(uint8_t num) {
    bool res = false;
    char* file_name = "IIRFrequencyResponse.csv";
#ifdef HAS_FILE_PC
    file_pc_delete(file_name);
#endif
    IirHandle_t* Node = IirGetNode(num);
    if(Node) {
        LOG_INFO(IIR, "%s", IirNodeToStr(Node));
        float f_hz = 0;
        for(f_hz = 0; f_hz < (Node->sample_rate_hz / 2.0);) {
            float f_real_hz = (float)f_hz;
            float complex numerator = iir_calc_feed_forward_ll(Node, f_real_hz, false);
            float complex denominator = iir_calc_feed_back_ll(Node, f_real_hz, false);
            float complex Amplitude = numerator / denominator;

            char temp[300] = "?";
            strcpy(temp, "");
            snprintf(temp, sizeof(temp), "%s%f,", temp, f_real_hz);
            snprintf(temp, sizeof(temp), "%s%f", temp, cabs(Amplitude));
#ifdef HAS_FILE_PC
            res = file_pc_print_line(file_name, temp, strlen(temp));
#endif
            if(0 == (((uint32_t)f_hz) % (((uint32_t)Node->sample_rate_hz) / 100))) {
                cli_printf("\r%s", ProgressToStr((uint32_t)f_hz, Node->sample_rate_hz / 2.0));
            }
            if(f_hz < 10.0) {
                f_hz += 0.1;
            } else {
                f_hz += 2.0;
            }
        }
#ifdef HAS_FILE_PC
        char command[300] = "";
        snprintf(command, sizeof(command), "python.exe plot_csv_file.py %s frequency Amplitude", file_name);
        res = win_cmd_run(command);
#endif
    }
    return res;
}
