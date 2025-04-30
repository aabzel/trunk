#include "fir.h"

#include <complex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "circular_buffer_index.h"
#include "code_generator.h"
#ifdef HAS_COMPLEX_DIAG
#include "complex_diag.h"
#endif
#include "fir_diag.h"
#include "float_utils.h"
#include "log.h"
#include "table_utils.h"
#include "utils_math.h"
#include "writer_config.h"
#include "debug_info.h"

#include "file_pc.h"
#include "csv.h"

COMPONENT_GET_NODE(Fir, fir)
COMPONENT_GET_CONFIG(Fir, fir)

//#define M_2PI (2.0*M_PI)

//#define MAX_ORDER 200

static FirSample_t fir_try_k(FirSample_t* h, uint32_t M, FirSample_t k) {
    FirSample_t sum = 0.0;
    uint32_t i = 0;
    for(i = 0; i < M; i++) {
        sum += k * h[i];
    }
    return sum;
}

/*Binary search k for FIR filter*/
static FirSample_t fir_find_k(FirSample_t* h, uint32_t M) {
    bool res = false;
    FirSample_t k_down = 0.0;
    FirSample_t k_up = 100.0;
    FirSample_t k_cur = 1.0;
    FirSample_t sum = 0.0;
    uint32_t iter = 0;
    while(1) {
        iter++;
        k_cur = 0.5 * (k_down + k_up);
        sum = fir_try_k(h, M, k_cur);
        res = is_double_equal_absolute(1.0, sum, EPSILONT);
        if(res) {
            LOG_INFO(FIR, "iter:%u,k:%f", iter, k_cur);
            break;
        } else if(1.0 < sum) {
            k_up = k_cur;

        } else if(sum < 1.0) {
            k_down = k_cur;
        }
        LOG_PARN(FIR, "iter:%u,k:%f,sum:%f", iter, k_cur, sum);

        res = is_double_equal_absolute(k_down, k_up, EPSILONT);
        if(res) {
            k_up = k_up * 2;
        }
    }

    return k_cur;
}

static FirSample_t fir_coef_calc(uint32_t i, uint32_t M, FirSample_t F_c, FirSample_t k) {
    FirSample_t h_i = 0.0;
    LOG_PARN(FIR, "SynThesize,i:%u,M:%u,Fcut:%f,SampleFreq:%f Hz,k:%f", i, M, F_c, k);
    FirSample_t argument = ((FirSample_t)i) - (((FirSample_t)M) / 2.0);
    FirSample_t blackman_window = (0.42 - 0.5 * cos(M_2PI * ((FirSample_t)i) / ((FirSample_t)M)) +
                                   0.08 * cos(4.0 * M_PI * ((FirSample_t)i) / ((FirSample_t)M)));
    FirSample_t sync = 0;
    if(i == (M / 2)) {
        sync = M_2PI * F_c;
    } else {
        sync = (sin(M_2PI * F_c * argument) / argument);
    }
    h_i = k * sync * blackman_window;

    LOG_PARN(FIR, "h[%u]=%7.3f" CRLF, i, h_i);
    return h_i;
}

static bool fir_synthesize_moving_average_ll(FirHandle_t* Node) {
    bool res = false;
    if(Node) {
        if(Node->size) {
            FirSample_t coefficient = 1.0 / ((FirSample_t)Node->size);
            LOG_WARNING(FIR, "Synthesize,Moving,Average,Num:%u,M:%u,k:%f", Node->num, Node->size, coefficient);
            uint32_t i = 0;
            for(i = 0; i < Node->size; i++) {
                Node->x[i] = 0.0;
                Node->b[i] = coefficient;
            }
            res = true;
        }
    }
    return res;
}






bool fir_synthesize(uint8_t num, uint32_t M, FirSample_t cutoff_frequency_hz, FirSample_t sampling_frequency_hz) {
    bool res = false;
    FirSample_t F_c = cutoff_frequency_hz / sampling_frequency_hz;
    LOG_INFO(FIR, "SynThesize,Num:%u,M:%u,Fcut:%f Hz,SampleFreq:%f Hz", num, M, cutoff_frequency_hz,
             sampling_frequency_hz);
    cli_printf(CRLF);
    FirHandle_t* Node = FirGetNode(num);

    if(Node) {
        switch(Node->mode){
        case FIR_MODE_MOVE_AVARAGE: {
            res = fir_synthesize_moving_average_ll(Node);
        }break;
        case FIR_MODE_INTEGRATION: {
            uint32_t i = 0;
            for(i = 0; i < M; i++) {
                Node->b[i] = 1.0;
            }
            res = true;
        }break;
        case FIR_MODE_CORRELATION: {
            res = true;
        }break;
        case FIR_MODE_CLASSIC: {
            if(M <= Node->max_size) {
                Node->size = M;
                uint32_t i = 0;
                FirSample_t k = 1.0;
                for(i = 0; i < M; i++) {
                    Node->b[i] = fir_coef_calc(i, M, F_c, k);
                    // cli_printf( "h[%u]=%7.3f" CRLF, i, Node->b[i]);
                }

                k = fir_find_k(Node->b, M);
                LOG_DEBUG(FIR, "K:%f", k);

                for(i = 0; i < M; i++) {
                    Node->b[i] = fir_coef_calc(i, M, F_c, k);
                    // cli_printf("h[%u]=%7.4f" CRLF, i, Node->b[i]);
                    res = true;
                }

            } else {
                LOG_ERROR(FIR, "FIR%u,OrderErr", num);
            }

        }break;
            default: {
                LOG_ERROR(FIR, "FIR%u,UndefMode:%u", num, Node->mode);
                res = false;
            } break;
        }
#ifdef HAS_GRAPHVIZ
        fir_generate_graphviz(num);
#endif


    } else {
        LOG_ERROR(FIR, "FIR%u NodeErr", num);
    }
    return res;
}

static bool fir_init_custom(void) {
    bool res = true;
    return res;
}

bool fir_reset_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(FIR, "FIR%u,ResetMem", num);
    FirHandle_t* Node = FirGetNode(num);
    if(Node) {
        if(Node->x) {
            LOG_INFO(FIR, "ZeroMem,%s", FirNodeToStr(Node));
            uint32_t i = 0;
            for(i = 0; i < Node->size; i++) {
                Node->x[i] = 0.0;
                res = true;
            }
        }
    } else {
        LOG_ERROR(FIR, "NodeErr");
    }
    return res;
}

static bool fir_is_valid_config(const FirConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    }

    if(res) {
        res = false;
        if(Config->size <= Config->max_size) {
            res = true;
        } else {
            LOG_ERROR(FIR, "SizeErr");
        }
    }

    if(res) {
        res = false;
        if(2 < Config->size) {
            res = true;
        } else {
            LOG_ERROR(FIR, "MinSizeErr");
        }
    }

    if(res) {
        res = false;
        if(Config->cut_off_freq_hz < (Config->sample_rate_hz/2.0)) {
            res = true;
        } else {
            LOG_ERROR(FIR, "CutOffTooBigErr %f Hz", Config->cut_off_freq_hz );
        }
    }

    if(res) {
    	double cut_off_period_s = 1.0/Config->cut_off_freq_hz;
    	double sample_per_s =  1.0/Config->sample_rate_hz;
    	double duration_of_analysis_s = Config->size * sample_per_s;
    	if(cut_off_period_s < duration_of_analysis_s) {
    	    res = true;
    	}else {
            LOG_ERROR(FIR, "TooSmallOrderErr");
        }
    }

    if(res) {
        res = false;
        if(0 < Config->mode) {
            res = true;
        } else {
            LOG_ERROR(FIR, "ModeErr");
        }
    }

    if(res) {
        res = false;
        if(0 < Config->sample_rate_hz) {
            res = true;
        } else {
            LOG_ERROR(FIR, "SampeReteErr");
        }
    }

    if(res) {
        res = false;
        if(Config->b) {
            res = true;
        } else {
            LOG_ERROR(FIR, "BErr");
        }
    }

    if(res) {
        res = false;
        if(Config->x) {
            res = true;
        } else {
            LOG_ERROR(FIR, "XErr");
        }
    }

    if(res) {
        res = false;
        if(Config->valid) {
            res = true;
        } else {
            LOG_ERROR(FIR, "ValidErr");
        }
    }

    if(res) {
        res = false;
        if(Config->name) {
            res = true;
        } else {
            LOG_ERROR(FIR, "NameErr");
        }
    }

    return res;
}

static bool fir_init_common(const FirConfig_t* const Config, FirHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->file_name_out = Config->file_name_out;
            Node->file_name_in = Config->file_name_in;
            Node->mode = Config->mode;
            Node->max_size = Config->max_size;
            Node->size = Config->size;
            Node->x = Config->x;
            Node->b = Config->b;
            Node->sample_rate_hz = Config->sample_rate_hz;
            Node->cut_off_freq_hz = Config->cut_off_freq_hz;
            Node->size = Config->size;
            res = true;
        }
    }
    return res;
}

bool fir_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(FIR, "%u,Init", num);
    const FirConfig_t* Config = NULL;
    Config = FirGetConfig(num);
    if(Config) {
#ifdef HAS_FIR_DIAG
        LOG_WARNING(FIR, "%s", FirConfigToStr(Config));
#endif
        res = fir_is_valid_config(Config);
        if(res) {
            FirHandle_t* Node = FirGetNode(num);
            if(Node) {
                LOG_INFO(FIR, "Spot,Node");
                res = fir_init_common(Config, Node);
                Node->valid = true;

                res = circular_buffer_index_init(&Node->indexer, Config->size - 1);

                res = fir_synthesize(num, Config->size, Config->cut_off_freq_hz, Config->sample_rate_hz);
                if(res) {
                    LOG_INFO(FIR, "SynthesizeOk");
                } else {
                    LOG_ERROR(FIR, "FIR%u,SynthesizeErr",num);
                }

            } else {
                LOG_ERROR(FIR, "NodeErr");
            }
        } else {
            LOG_ERROR(FIR, "AbsurdConfigErr");
        }
    } else {
        LOG_ERROR(FIR, "ConfNodeErr");
    }

    return res;
}

static double complex calc_frequency_response_one_ll(FirHandle_t* const Node, double freq_hz) {
    double complex TransferFunction = 0 + 0 * I;
    uint32_t k = 0;
    for(k = 0; k < Node->size; k++) {
        double F = freq_hz / Node->sample_rate_hz;
        double argument = M_2PI * F * ((double)k);
        TransferFunction += ((double)Node->b[k]) * (cos(argument) - sin(argument) * I);
    }
    return TransferFunction;
}

bool fir_impulse_response(uint8_t num) {
    bool res = false;
    LOG_WARNING(FIR, "FIR%u,CalcImpulseResponse:Step:%f Hz" CRLF, num);
    res = fir_reset_one(num);
    FirHandle_t* Node = FirGetNode(num);
    if(Node) {

        char text[150] = {0};
        LOG_INFO(FIR, "%s", FirNodeToStr(Node));

        static const table_col_t cols[] = {
            {8, "sample"},
            {8, "time"},
            {8, "in"},
            {8, "out"},
        };

        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t s = 0;
        FirSample_t sample_in = 0.0;
        FirSample_t sample_out = 0.0;
        for(s = 0; s < (Node->size + 2); s++) {
            double t_s = ((double)s) / Node->sample_rate_hz;

            if(1 == s) {
                sample_in = 1.0;
            } else {
                sample_in = 0.0;
            }
            res = fir_proc_in_out(num, sample_in, &sample_out);

            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %6u " TSEP, text, s);
            snprintf(text, sizeof(text), "%s %6.4f " TSEP, text, t_s);
            snprintf(text, sizeof(text), "%s %6.3f " TSEP, text, sample_in);
            snprintf(text, sizeof(text), "%s %6.3f " TSEP, text, sample_out);

            cli_printf("%s" CRLF, text);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    cli_printf(CRLF);

    return res;
}

bool fir_set_mode(uint8_t num, FirMode_t mode){
    bool res = false ;
    FirHandle_t* Node=FirGetNode(num);
    if(Node){
        Node->mode = mode;
        res = true;
    }
    return res;
}

bool fir_calc_frequency_response(uint8_t num, double f_step) {
    bool res = false;
    LOG_WARNING(FIR, "FIR%u,CalcFrequencyResponse:Step:%f Hz" CRLF, num, f_step);

    FirHandle_t* Node = FirGetNode(num);
    if(Node) {
        char text[150] = {0};
        LOG_INFO(FIR, "%s", FirNodeToStr(Node));

        static const table_col_t cols[] = {
            {9, "Freq"},
            {6, "ABS"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        double f_cur = 0;
        for(f_cur = 0.0; f_cur < Node->sample_rate_hz / 2.0; f_cur += f_step) {
            double complex TransferFunction = 0 + 0 * I;
            TransferFunction = calc_frequency_response_one_ll(Node, f_cur);

            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %7.1f " TSEP, text, f_cur);
            snprintf(text, sizeof(text), "%s %3.2f " TSEP, text, cabs(TransferFunction));

            cli_printf("%s" CRLF, text);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    cli_printf(CRLF);

    return res;
}

int32_t fir_order_get(uint8_t num) {
    int32_t order = 0;
    FirHandle_t* Node = FirGetNode(num);
    if(Node) {
        order = Node->size;
    }
    return order;
}

bool fir_save_csv_line(char* file_name_out, double value_x, double value_y) {
    bool res = false;
    if(file_name_out) {
        char text[500]={0};
        snprintf(text,sizeof(text),"%f,%f",value_x,value_y);
        res=file_pc_print_line(file_name_out, text, strlen(text));
    }
    return res;
}

bool fir_proc_file(uint8_t num, char* file_name, uint16_t column_x, uint16_t column_y) {
    bool res = false;
    LOG_WARNING(FIR, "FIR%u,File:[%s],ColX:%u,ColY:%u", num, file_name, column_x, column_y);
    int32_t line_cnt = file_pc_line_cnt(file_name);
    if(line_cnt) {
        LOG_INFO(FIR, "File:[%s],Lines:%u", file_name, line_cnt);
        FirHandle_t* Node=FirGetNode(  num);
        if(Node) {
            res = file_pc_delete(Node->file_name_out);
            int32_t cnt = 1;
            FILE* file_prt = NULL;
            file_prt = fopen(file_name, "r");
            if(file_prt) {
                LOG_INFO(FIR, "File [%s] OpenOk", file_name);
                char csv_line[500]={0};
                strcpy(csv_line, "");
                while(NULL != fgets(csv_line, sizeof(csv_line), file_prt)) {
                    LOG_PARN(FIR, "%u:[%s]", cnt, csv_line);
                    double value_x = 0.0;
                    res = csv_parse_double(csv_line, column_x, &value_x);
                    if(res) {
                        double value_y = 0.0;
                        res = csv_parse_double(csv_line, column_y, &value_y);
                        if(res) {
                            FirSample_t sample_in=(FirSample_t) value_y;
                            FirSample_t sample_out = 0.0;
                            res = fir_proc_in_out(num, sample_in, &sample_out);
                            if(res) {
                                res = fir_save_csv_line(Node->file_name_out, value_x, sample_out);
                            }
                        } else {
                            LOG_ERROR(FIR, "ParseXErr X:%f", value_x);
                        }
                    }
                    cnt++;
                    res = true;
                    if(0==   ((cnt)%(line_cnt/400))    ) {
                        cli_printf("\r%s",  ProgressToStr( (uint32_t) cnt, (uint32_t) line_cnt));
                    }
                    strcpy(csv_line, "");
                }
                fclose(file_prt);
                LOG_INFO(FIR, "File:[%s]:CloseOk", file_name);
            }
        }
    }else {
        LOG_ERROR(FIR, "File [%s] OpenErr", file_name);
    }
    return res;
}



COMPONENT_INIT_PATTERT(FIR, FIR, fir)
