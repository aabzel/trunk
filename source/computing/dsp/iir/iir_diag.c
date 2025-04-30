#include "iir_diag.h"

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "circular_buffer_diag.h"
#include "common_diag.h"
#include "debug_info.h"
#include "file_pc.h"
#include "iir.h"
#include "log.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "win_utils.h"
#include "writer_config.h"

bool IirDiagCoefficient(uint8_t num) {
    bool res = false;
    IirHandle_t* Node = IirGetNode(num);
    if(Node) {
        static const table_col_t cols[] = {{5, "i"}, {10, "back"}, {10, "forward"}, {14, "a"}, {14, "b"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        char text[300] = "?";
        uint32_t i = 0;
        for(i = 0; i < Node->size; i++) {
            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %3u " TSEP, text, i);
            snprintf(text, sizeof(text), "%s %8s " TSEP, text, DoubleToStr(Node->a[i]));
            snprintf(text, sizeof(text), "%s %8s " TSEP, text, DoubleToStr(Node->b[i]));
            snprintf(text, sizeof(text), "%s %10.9f " TSEP, text, Node->a[i]);
            snprintf(text, sizeof(text), "%s %10.9f " TSEP, text, Node->b[i]);
            cli_printf("%s" CRLF, text);
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
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOff2Str(Node->init));
            cli_printf("%s" CRLF, temp_str);
            num++;
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

const char* IirNodeToStr(const IirHandle_t* const Node) {
    static char text[300] = "?";
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sProcnt:%u,", text, Node->proc_cnt);
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sInit:%u,", text, Node->init);
        snprintf(text, sizeof(text), "%sM:%u,", text, Node->size);
        snprintf(text, sizeof(text), "%s/%u,", text, Node->max_size);
        snprintf(text, sizeof(text), "%sFsam:%s Hz,", text, DoubleToStr(Node->sample_rate_hz));
        snprintf(text, sizeof(text), "%sFcut:%s Hz,", text, DoubleToStr(Node->cut_off_freq_hz));
        snprintf(text, sizeof(text), "%sCbX:%s,", text, CircularBufferStateToStr(&Node->xIndexer));
        snprintf(text, sizeof(text), "%sCbY:%s,", text, CircularBufferStateToStr(&Node->xIndexer));
    }
    return text;
}

const char* IirConfigToStr(const IirConfig_t* const Config) {
    static char text[300] = "?";
    if(Config) {
        strcpy(text, "CFG:");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sM:%u", text, Config->size);
        snprintf(text, sizeof(text), "%s/%u,", text, Config->max_size);
        snprintf(text, sizeof(text), "%sFsam:%s Hz,", text, DoubleToStr(Config->sample_rate_hz));
        snprintf(text, sizeof(text), "%sFcut:%s Hz,", text, DoubleToStr(Config->cut_off_freq_hz));
    }
    return text;
}

static double complex filter_delay_link(uint32_t n, double F_hz, double F_sam, bool is_norm_freq) {
    double complex exp = 0.0;
    double omega = 0;
    double T_a = 0;
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

static double complex iir_calc_feed_forward_ll(IirHandle_t* Node, double f_hz, bool is_norm_freq) {
    double complex numerator = 0.0;
    uint32_t n = 0;
    for(n = 0; n < Node->size; n++) {
        numerator += Node->b[n] * filter_delay_link(n, f_hz, Node->sample_rate_hz, is_norm_freq);
    }
    return numerator;
}

static double complex iir_calc_feed_back_ll(IirHandle_t* Node, double f_hz, bool is_norm_freq) {
    double complex denominator = 1.0;
    uint32_t n = 0;
    for(n = 1; n < Node->size; n++) {
        denominator += Node->a[n] * filter_delay_link(n, f_hz, Node->sample_rate_hz, is_norm_freq);
    }
    return denominator;
}

bool iir_calc_frequency_response_norm(uint8_t num) {
    bool res = false;
    char* file_name = "IIRFrequencyResponse.csv";
    file_pc_delete(file_name);
    IirHandle_t* Node = IirGetNode(num);
    if(Node) {
        LOG_INFO(IIR, "%s", IirNodeToStr(Node));
        double f_norm = 0;
        for(f_norm = 0; f_norm < (0.5);) {
            double complex numerator = iir_calc_feed_forward_ll(Node, f_norm, true);
            double complex denominator = iir_calc_feed_back_ll(Node, f_norm, true);
            double complex Amplitude = numerator / denominator;
            char text[300] = "?";
            strcpy(text, "");
            snprintf(text, sizeof(text), "%s%f,", text, f_norm);
            snprintf(text, sizeof(text), "%s%f", text, cabs(Amplitude));
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

// 10000  1Hz
bool iir_calc_frequency_response(uint8_t num) {
    bool res = false;
    char* file_name = "IIRFrequencyResponse.csv";
    file_pc_delete(file_name);
    IirHandle_t* Node = IirGetNode(num);
    if(Node) {
        LOG_INFO(IIR, "%s", IirNodeToStr(Node));
        double f_hz = 0;
        for(f_hz = 0; f_hz < (Node->sample_rate_hz / 2.0);) {
            double f_real_hz = (double)f_hz;
            double complex numerator = iir_calc_feed_forward_ll(Node, f_real_hz, false);
            double complex denominator = iir_calc_feed_back_ll(Node, f_real_hz, false);
            double complex Amplitude = numerator / denominator;

            char text[300] = "?";
            strcpy(text, "");
            snprintf(text, sizeof(text), "%s%f,", text, f_real_hz);
            snprintf(text, sizeof(text), "%s%f", text, cabs(Amplitude));
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
