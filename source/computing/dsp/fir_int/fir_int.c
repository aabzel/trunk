#include "fir_int.h"

#include <complex.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "array.h"
#include "circular_buffer_index.h"
#include "complex_diag.h"
#include "code_generator.h"
#include "table_utils.h"
#include "fir_int_diag.h"
#include "writer_config.h"
#include "float_utils.h"
#include "log.h"
#include "utils_math.h"

COMPONENT_GET_NODE(FirInt, fir_int)
COMPONENT_GET_CONFIG(FirInt, fir_int)

#define DOUBLE_PI (2.0*M_PI)

#define MAX_ORDER 200

static float fir_int_try_k(float *a_real, uint32_t M, float k) {
	float sum = 0.0;
    uint32_t i = 0;
    for (i = 0; i < M; i++) {
        sum += k * a_real[i];
    }
    return sum;
}

static float fir_int_find_k(float *a_real, uint32_t M) {
    bool res = false;
    float k_down = 0.0;
    float k_up = 100.0;
    float k_cur = 1.0;
    float sum = 0.0;
    uint32_t iter = 0;
    while (1) {
        iter++;
        k_cur = 0.5 * (k_down + k_up);
        sum = fir_int_try_k(a_real, M, k_cur);
        res = is_float_equal_absolute(1.0, sum, 0.001);
        if (res) {
            LOG_INFO(FIR_INT, "iter:%u,k:%f", iter, k_cur);
            break;
        } else if (1.0 < sum) {
            k_up = k_cur;

        } else if (sum < 1.0) {
            k_down = k_cur;
        }
        LOG_PARN(FIR_INT, "iter:%u,k:%f,sum:%f", iter, k_cur, sum);
    }

    return k_cur;
}

static float fir_int_coef_calc(uint32_t i, uint32_t M, float F_c,
		float k) {
	float a_i = 0.0;
    LOG_PARN(FIR_INT, "SynThes,i:%u,M:%u,Fcut:%f,SampleFreq:%f Hz,k:%f", i, M,
            F_c, k);
    float argument = ((FirIntSample_t) i) - (((FirIntSample_t) M) / 2.0);
    float blackman_window = (0.42
            - 0.5 * cos(DOUBLE_PI * ((float) i) / ((float) M))
            + 0.08 * cos(4.0 * M_PI * ((float) i) / ((float) M)));
    float sync = 0;
    if (i == (M / 2)) {
        sync = DOUBLE_PI * F_c;
    } else {
        sync = (sin(DOUBLE_PI * F_c * argument) / argument);
    }
    a_i = k * sync * blackman_window;

    LOG_PARN(FIR_INT, "h[%u]=%7.3f" CRLF, i, a_i);
    return a_i;
}

bool fir_int_synthesize(uint8_t num, uint32_t M, float cutoff_frequency_hz,
        float sampling_frequency_hz) {
    bool res = false;
    float F_c = cutoff_frequency_hz / sampling_frequency_hz;
    LOG_INFO(FIR_INT, "SynThesize,Num:%u,M:%u,Fcut:%f Hz,SampleFreq:%f Hz", num, M,
            cutoff_frequency_hz, sampling_frequency_hz);
    cli_printf( CRLF);
    FirIntHandle_t *Node = FirIntGetNode(num);

    if (Node) {
        if (M <= Node->max_size) {
            Node->size = M;
            uint32_t i = 0;
            float k = 1.0;
            for (i = 0; i < M; i++) {
                Node->a_real[i] = fir_int_coef_calc(i, M, F_c, k);
                Node->a_numerator[i] = Node->a_real[i]*((float)Node->denominator);
                //cli_printf( "h[%u]=%7.3f" CRLF, i, Node->a[i]);
            }

            k = fir_int_find_k(Node->a_real, M);
            LOG_DEBUG(FIR_INT, "K:%f", k);

            for (i = 0; i < M; i++) {
                Node->a_real[i] = fir_int_coef_calc(i, M, F_c, k);
                Node->a_numerator[i] = (FirIntSample_t) (((float)Node->a_real[i])*((float)Node->denominator));
                cli_printf("a[%u]=%7.4f,%d" CRLF, i, Node->a_real[i],Node->a_numerator[i]);
                res = true;
            }
#ifdef HAS_PC
        fir_int_generate_graphviz( num);
#endif

        } else {
            LOG_ERROR(FIR_INT, "FIR%u,OrderErr", num);
        }
    } else {
        LOG_ERROR(FIR_INT, "FIR%u NodeErr", num);
    }
    return res;
}
// ISR
bool fir_int_push(uint8_t num, FirIntSample_t in) {
    bool res = false;
    FirIntHandle_t *Node = FirIntGetNode(num);
    if (Node) {
        CircularBufferIndex_t index = circular_buffer_index_add(&Node->indexer);
        //LOG_DEBUG(FIR_INT, "Puth RawX[%u]=%f", index, in);
        Node->x[index] = in;
        res = true;
    } else {
        //LOG_ERROR(FIR_INT, "FIR%u NodeErr", num);
    }
    return res;
}
// ISR
bool fir_int_pop(uint8_t num, FirIntSample_t in, FirIntSample_t *const out) {
    bool res = false;
    FirIntSample_t y = 0;
    FirIntSample_t xi = 0;
    CircularBufferIndex_t cb_i = 0;
    FirIntHandle_t *Node = FirIntGetNode(num);
    if (Node) {
        Node->pop_cnt++;
        y += in * Node->a_numerator[0]/Node->denominator;
        uint32_t i = 0;
        for (i = 1; i < (Node->size); i++) {
            cb_i = circular_buffer_index_get_i(&Node->indexer, i);
            //LOG_DEBUG(FIR_INT, "X[%u]->x[%u]=%f", i, cb_i, Node->x[cb_i]);
            xi = Node->x[cb_i];
            y += (Node->a_numerator[i] * xi)/Node->denominator;
        }

        if (out) {
            *out = y;
            res = true;
        }
    } else {
        //LOG_ERROR(FIR_INT, "FIR%u NodeErr", num);
    }
    return res;
}
// ISR
bool fir_int_proc_in_out(uint8_t num, FirIntSample_t in, FirIntSample_t *const out) {
    bool res = false;
    //LOG_DEBUG(FIR_INT, "FIR_%u,Proc,Push:%f", num, in);
    res = fir_int_pop(num, in, out);
    if (res) {
        //LOG_DEBUG(FIR_INT, "FIR_%u,Out:%f,Ok", num, *out);
        res = fir_int_push(num, in);
        if (res) {
            //LOG_DEBUG(FIR_INT, "FIR_%u,Push:%f,Ok", num, in);
        } else {
            //LOG_ERROR(FIR_INT, "FIR_%u,PushErr", num);
        }
    } else {
        //LOG_ERROR(FIR_INT, "FIR_%u,PopErr", num);
    }
    return res;
}

bool fir_int_init_custom(void) {
    bool res = true;
    return res;
}

bool fir_int_reset_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(FIR_INT, "FIR%u,ResetMem", num);
    FirIntHandle_t *Node = FirIntGetNode(num);
    if (Node) {
        if (Node->x) {
            LOG_INFO(FIR_INT, "ZeroMem,%s", FirIntNodeToStr(Node));
            uint32_t i = 0;
            for (i = 0; i < Node->size; i++) {
                Node->x[i] = 0.0;
                res = true;
            }
        }
    } else {
        LOG_ERROR(FIR_INT, "NodeErr");
    }
    return res;
}


bool fir_int_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(FIR_INT, "%u,Init", num);
    const FirIntConfig_t *Config = NULL;
    Config = FirIntGetConfig(num);
    if (Config) {
        LOG_INFO(FIR_INT, "SpotConfig Order:%u", Config->size);
#ifdef HAS_FIR_DIAG
        FirIntDiagConfig(Config);
#endif
        if (1 <= Config->size) {
            FirIntHandle_t *Node = FirIntGetNode(num);
            if (Node) {
                LOG_INFO(FIR_INT, "SpotNode");
                Node->num = Config->num;
                Node->max_size = Config->max_size;
                Node->size = Config->size;
                Node->denominator = Config->denominator;
                Node->sample_rate_hz = Config->sample_rate_hz;
                Node->cut_off_freq_hz = Config->cut_off_freq_hz;
                Node->size = Config->size;
                Node->a_real = Config->a_real;
                Node->a_numerator = Config->a_numerator;
                Node->x = Config->x;
                Node->valid= true;

                res = circular_buffer_index_init(&Node->indexer, Config->size);
                if (Node->x) {
                    LOG_WARNING(FIR_INT, "StaticallyAllocatedX");
                } else {
                    LOG_ERROR(FIR_INT, "ErrorX");
                    res = false;
                }

                if (res) {
                    if (Node->a_numerator) {
                        LOG_WARNING(FIR_INT, "StaticallyAllocatedA");
                    } else {
                        LOG_ERROR(FIR_INT, "ErrorAnumerator");
                        res = false;
                    }
                }

                if (res) {
                    if (Node->a_real) {
                        LOG_WARNING(FIR_INT, "StaticallyAllocatedA");
                    } else {
                        LOG_ERROR(FIR_INT, "ErrorAReal");
                        res = false;
                    }
                }

                if (res) {
                    res = fir_int_synthesize(num,
                    		                 Config->size,
							                 Config->cut_off_freq_hz,
                    		                 Config->sample_rate_hz);
                    if (res) {
                        LOG_INFO(FIR_INT, "SynthesizeOk");
                    } else {
                        LOG_ERROR(FIR_INT, "SynthesizeErr");
                    }
                }

            } else {
                LOG_ERROR(FIR_INT, "NodeErr");
            }
        } else {
            LOG_ERROR(FIR_INT, "SizeErr");
        }
    } else {
        LOG_ERROR(FIR_INT, "ConfNodeErr");
    }

    return res;
}

static double complex calc_frequency_response_one_ll(FirIntHandle_t* const Node,
        double freq_hz){
    double complex TransferFunction = 0 + 0 * I;
    uint32_t k = 0;
    for(k=0; k<Node->size; k++) {
        double F = freq_hz/Node->sample_rate_hz;
        double argument = M_2PI*F*((double)k);
        TransferFunction +=((double )Node->a_numerator[k]/((double )Node->denominator))* (cos(argument)-sin(argument)*I );
    }
    return TransferFunction;
}

bool fir_int_impulse_response(uint8_t num){
    bool res = false;
    LOG_WARNING(FIR_INT, "FIR%u,CalcImpulseResponse:Step:%f Hz"CRLF, num);
    res = fir_int_reset_one(num);
    FirIntHandle_t* Node = FirIntGetNode(num);
    if(Node){

        char text[150] = {0};
        LOG_INFO(FIR_INT, "%s", FirIntNodeToStr(Node));

        static const table_col_t cols[] = {
                 {8, "sample"},  {8, "time"},  {8, "in"},  {8, "out"},
        };

        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t s  = 0;
        FirIntSample_t sample_in = 0;
        FirIntSample_t sample_out = 0;
        for(s = 0; s < (Node->size+2); s++) {
            double t_s = ((double)s)/Node->sample_rate_hz;

            if (1==s) {
                sample_in = 1000;
            } else {
                sample_in = 0;
            }
            res = fir_int_proc_in_out(num, sample_in, &sample_out);

            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %6u "TSEP, text, s);
            snprintf(text, sizeof(text), "%s %6.4f "TSEP, text, t_s);
            snprintf(text, sizeof(text), "%s %6d "TSEP, text, sample_in);
            snprintf(text, sizeof(text), "%s %6d "TSEP, text, sample_out);

            cli_printf("%s" CRLF,  text);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    cli_printf(CRLF);

    return res;
}

bool fir_int_calc_frequency_response(uint8_t num, double f_step) {
    bool res = false;
    LOG_WARNING(FIR_INT, "FIR%u,CalcFrequencyResponse:Step:%f Hz"CRLF, num,f_step);

    FirIntHandle_t* Node=FirIntGetNode(num);
    if(Node){
        char text[150] = {0};
        LOG_INFO(FIR_INT, "%s", FirIntNodeToStr(Node));

        static const table_col_t cols[] = {
            {9, "Freq"},  {6, "ABS"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        double f_cur  =  0 ;
        for(f_cur = 0.0; f_cur < Node->sample_rate_hz/2.0; f_cur+=f_step){
            double complex TransferFunction= 0+0*I;
            TransferFunction = calc_frequency_response_one_ll(Node, f_cur);

            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %7.1f "TSEP, text, f_cur);
            snprintf(text, sizeof(text), "%s %3.2f "TSEP, text, cabs(TransferFunction));

            cli_printf("%s" CRLF,  text);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    cli_printf(CRLF);

    return res;
}

COMPONENT_INIT_PATTERT(FIR_INT, FIR_INT, fir_int)
