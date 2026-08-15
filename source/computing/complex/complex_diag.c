#include "complex_diag.h"

#include <complex.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "file_pc.h"
#include "log.h"
#include "num_to_str.h"
#include "str_utils.h"
#include "table_utils.h"
#include "time_mcal.h"
#include "utils_math.h"
#include "vector_math.h"
#include "writer_config.h"

bool complex_array_print(const double complex* const X, uint32_t len, double period_s, uint32_t order) {
    bool res = false;
    double sample_rate_hz = 1.0 / period_s;
    double signal_duration_s = period_s * ((double)len);
    double half_sample_rate_hz = sample_rate_hz / 2.0;
    LOG_WARNING(COMPLEX, "Len:%u,T:%f s,SampleRate:%f Hz,Order:%u,SignalDuratin:%f s", len, period_s, sample_rate_hz,
                order, signal_duration_s);
    if(X) {
        if(len) {
            static const table_col_t cols[] = {
                {5, "Num"},  {10, "FreqHz"}, {10, "PeriodS"}, {14, "Real"},   {14, "Image"},
                {14, "Abs"}, {14, "ArgRad"}, {14, "ArgRad"},  {14, "ArgDeg"},
            };
            char lText[150] = {0};
            table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
            uint32_t k = 0;
            double freq_hz = 0.0;
            //(void)period_s;
            for(k = 0; k < len; k++) {
                freq_hz = ((double)k) / signal_duration_s;
                double cur_period_s = 0.0;
                cur_period_s = 1.0 / freq_hz;
                LOG_PARN(COMPLEX, "k=%u,CurFreq %8.2f Hz,Per:%8.2f s", k, freq_hz, cur_period_s);
                if(freq_hz < half_sample_rate_hz) {
                    if(0.0 < freq_hz) {
                        strcpy(lText, TSEP);
                        snprintf(lText, sizeof(lText), "%s %8.2f " TSEP, lText, freq_hz);                 // ok
                        snprintf(lText, sizeof(lText), "%s %8s " TSEP, lText, DoubleToStr(cur_period_s)); // ok
                        snprintf(lText, sizeof(lText), "%s %12s " TSEP, lText,
                                 str_limit(BigValToStr(creal(X[k])), 12)); // ok
                        snprintf(lText, sizeof(lText), "%s %12s " TSEP, lText, str_limit(BigValToStr(cimag(X[k])), 12));
                        snprintf(lText, sizeof(lText), "%s %12s " TSEP, lText, str_limit(BigValToStr(cabs(X[k])), 12));
                        snprintf(lText, sizeof(lText), "%s %12.4f " TSEP, lText, carg(X[k]));
                        snprintf(lText, sizeof(lText), "%s %12.4f " TSEP, lText,
                                 vector_bearings(creal(X[k]), cimag(X[k])));
                        snprintf(lText, sizeof(lText), "%s %12.4f " TSEP, lText, RAD_2_DEG(carg(X[k])));
#if 0
#endif
                        if(k < order) {
                            cli_printf(TSEP " %3u %s" CRLF, k, lText);
                            res = true;
                        } else {
                            LOG_PARN(COMPLEX, "CurFreq %f Hz, 0.5*Fs %f Hz", freq_hz, (sample_rate_hz / 2.0));
                        }
                    }
                } else {
                    LOG_DEBUG(COMPLEX, "CurFreq %f Hz, 0.5*Fs %f Hz", freq_hz, (sample_rate_hz / 2.0));
                }
            }
            table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        }
    }
    return res;
}

/*
 * sample_period_s -
 python plot_csv_file.py ComplexArray.csv 3 11

 python plot_csv_file.py ComplexArray.csv 3 13

  python plot_csv_file.py ComplexArray.csv 3 17
 * */
bool complex_array_print_csv(const double complex* const X, uint32_t len, double sample_period_s, uint32_t order) {
    double sample_rate_hz = 1.0 / sample_period_s;
    LOG_WARNING(COMPLEX, "T:%fs,SampleRate:%f Hz", sample_period_s, sample_rate_hz);
    bool res = false;
    res = file_pc_delete("ComplexArray.csv");
    uint32_t k = 0;
    for(k = 0; k < len; k++) {
        double freq_hz = ((double)k) / (sample_period_s * ((double)len));
        if(freq_hz < (sample_rate_hz / 2.0)) {
            char lText[220] = {0};
            strcpy(lText, "");
            snprintf(lText, sizeof(lText), "%sN,%u,", lText, k);
            snprintf(lText, sizeof(lText), "%sFreqHz,%f,", lText, freq_hz);
            snprintf(lText, sizeof(lText), "%sPeriods,%f,", lText, (1.0 / freq_hz));
            snprintf(lText, sizeof(lText), "%sReal,%f,", lText, creal(X[k]));
            snprintf(lText, sizeof(lText), "%sImage,%f,", lText, cimag(X[k]));
            snprintf(lText, sizeof(lText), "%sAbs,%f,", lText, cabs(X[k]));
            snprintf(lText, sizeof(lText), "%sArgRad,%f,", lText, carg(X[k]));
            snprintf(lText, sizeof(lText), "%sArgRad,%f,", lText, vector_bearings(creal(X[k]), cimag(X[k])));
            snprintf(lText, sizeof(lText), "%sArgDeg,%f,", lText, RAD_2_DEG(carg(X[k])));
            if(k < order) {
                res = file_pc_print_line("ComplexArray.csv", lText, strlen(lText));
            }
        }
    }
    return res;
}

const char* ComplexToStr(double complex ComplexNumber) {
    static char lText[250] = "";
    strcpy(lText, "");
    snprintf(lText, sizeof(lText), "%sRe:%s,", lText, DoubleToStr(creal(ComplexNumber)));
    snprintf(lText, sizeof(lText), "%sIm:%s,", lText, DoubleToStr(cimag(ComplexNumber)));
    snprintf(lText, sizeof(lText), "%sAbs:%s,", lText, DoubleToStr(cabs(ComplexNumber)));
    snprintf(lText, sizeof(lText), "%sArg:%s", lText, DoubleToStr(carg(ComplexNumber)));

    return lText;
}
