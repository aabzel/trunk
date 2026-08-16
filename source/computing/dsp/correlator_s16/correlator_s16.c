#include "correlator_s16.h"

#include <complex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "circular_buffer_index.h"
#include "code_generator.h"
#include "correlator_s16_diag.h"
#include "csv.h"
#include "debug_info.h"
#include "float_utils.h"
#include "log.h"
#include "table_utils.h"
#include "utils_math.h"
#include "writer_config.h"

#ifdef HAS_COMPLEX_DIAG
#include "complex_diag.h"
#endif

#ifdef HAS_FILE_PC
#include "file_pc.h"
#endif

COMPONENT_GET_NODE(CorrelatorS16, correlator_s16)
COMPONENT_GET_CONFIG(CorrelatorS16, correlator_s16)

static bool correlator_s16_init_common(const CorrelatorS16Config_t* const Config, CorrelatorS16Handle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->file_name_out = Config->file_name_out;
            Node->file_name_in = Config->file_name_in;
            Node->max_size = Config->max_size;
            Node->size = Config->size;
            Node->x = Config->x;
            Node->ReferenceSignal = Config->ReferenceSignal;
            Node->sample_rate_hz = Config->sample_rate_hz;
            Node->size = Config->size;
            res = true;
        }
    }
    return res;
}

int32_t correlator_s16_order_get(uint8_t num) {
    int32_t order = 0;
    CorrelatorS16Handle_t* Node = CorrelatorS16GetNode(num);
    if(Node) {
        order = Node->size;
    }
    return order;
}

static bool correlator_s16_init_custom(void) {
    bool res = true;
    LOG_WARNING(CORRELATOR_S16, "CORRELATOR_S16_VERSION:%u", CORRELATOR_S16_VERSION);
    return res;
}

bool correlator_s16_reset_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(CORRELATOR_S16, "CORRELATOR_S16%u,ResetMem", num);
    CorrelatorS16Handle_t* Node = CorrelatorS16GetNode(num);
    if(Node) {
        if(Node->x) {
            LOG_INFO(CORRELATOR_S16, "ZeroMem,%s", CorrelatorS16NodeToStr(Node));
            uint32_t i = 0;
            for(i = 0; i < Node->size; i++) {
                Node->x[i] = 0.0;
                res = true;
            }
        }
    } else {
        LOG_ERROR(CORRELATOR_S16, "NodeErr");
    }
    return res;
}

static bool correlator_s16_is_valid_config(const CorrelatorS16Config_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            res = false;
            LOG_ERROR(CORRELATOR_S16, "Name,Err%u", Config->num);
        }

        ifn(Config->file_name_out) {
            res = false;
            LOG_ERROR(CORRELATOR_S16, "file_name_out,Err,%s", Config->name);
        }

        ifn(Config->file_name_in) {
            LOG_ERROR(CORRELATOR_S16, "inFileName,Err,%s", Config->name);
            res = false;
        }

        ifn(Config->size <= Config->max_size) {
            res = false;
            LOG_ERROR(CORRELATOR_S16, "Size,Err,%s Size:%u,MaxSize:%u", Config->name, Config->size, Config->max_size);
        }

        ifn(0 < Config->size) {
            res = false;
            LOG_ERROR(CORRELATOR_S16, "MinSize,Err,%s", Config->name);
        }

        ifn(0 < Config->sample_rate_hz) {
            res = false;
            LOG_ERROR(CORRELATOR_S16, "SampeRete,Err,%s", Config->name);
        }

        ifn(Config->ReferenceSignal) {
            res = false;
            LOG_ERROR(CORRELATOR_S16, "B,Err,%s", Config->name);
        }

        ifn(Config->x) {
            res = false;
            LOG_ERROR(CORRELATOR_S16, "X,Err,%s", Config->name);
        }

        ifn(Config->valid) {
            res = false;
            LOG_ERROR(CORRELATOR_S16, "Valid,Err,%s", Config->name);
        }
    }

    return res;
}

static bool correlator_s16_push_ll(CorrelatorS16Handle_t* Node, int16_t in) {
    bool res = true;
    uint32_t index = circular_buffer_index_add(&Node->indexer);
    Node->x[index] = in;
    return res;
}

bool correlator_s16_pop_ll(CorrelatorS16Handle_t* Node, int16_t x0, int64_t* const out) {
    bool res = true;
    int64_t y = 0;
    uint32_t cb_i = 0;

    y += ((int64_t)x0) * ((int64_t)Node->ReferenceSignal[0]);
    int32_t i = 0;
    for(i = 1; i < (Node->size); i++) {
        cb_i = circular_buffer_index_get_i(&Node->indexer, -i);
        y += ((int64_t)Node->ReferenceSignal[i]) * ((int64_t)Node->x[cb_i]);
    }

    *out = y;
    return res;
}

bool correlator_s16_proc_in_out_array(uint8_t num, uint32_t size, const int16_t* const x, int64_t* const y) {
    bool res = false;
    CorrelatorS16Handle_t* Node = CorrelatorS16GetNode(num);
    uint32_t s = 0;
    for(s = 0; s < size; s++) {
        res = correlator_s16_pop_ll(Node, x[s], &y[s]);
        if(res) {
            res = correlator_s16_push_ll(Node, x[s]);
        }
    }
    return res;
}

bool correlator_s16_proc_in_out_ll(CorrelatorS16Handle_t* Node, int16_t x, int64_t* const y) {
    bool res = false;
    res = correlator_s16_pop_ll(Node, x, y);
    if(res) {
        res = correlator_s16_push_ll(Node, x);
        Node->proc_cnt++;
    }
    LOG_DEBUG(CORRELATOR_S16, "%d->%d", x, *y);
    return res;
}

bool correlator_s16_proc_in_out(uint8_t num, int16_t x, int64_t* const y) {
    bool res = false;
    CorrelatorS16Handle_t* Node = CorrelatorS16GetNode(num);
    if(Node) {
        /* if(Node)  can be commented to boost code execution */
        res = correlator_s16_proc_in_out_ll(Node, x, y);
    }
    return res;
}

int64_t correlator_s16_proc_in_out_short(uint8_t num, int16_t x0) {
    int64_t out_sam = 0;
    correlator_s16_proc_in_out(num, x0, &out_sam);
    return out_sam;
}

bool correlator_s16_write_ref_signal(uint8_t num, const int16_t* const ref_signal, const uint32_t size) {
    bool res = false;
    LOG_WARNING(CORRELATOR_S16, "N:%u,LoadRef,Size:%u", num, size);
    CorrelatorS16Handle_t* Node = CorrelatorS16GetNode(num);
    if(Node) {
        if(Node->ReferenceSignal) {
            if(size < Node->max_size) {
                Node->size = size;
                uint32_t i = 0;
                for(i = 0; i < Node->size; i++) {
                    Node->ReferenceSignal[Node->size - i - 1] = ref_signal[i];
                }
                res = true;
            }else {
                LOG_ERROR(CORRELATOR_S16, "CORR_%u,ReferenceSignal,Error,Need:%u,MaxSize:%u", num,size,Node->max_size);
            }

            LOG_INFO(CORRELATOR_S16, "%s", CorrelatorS16NodeToStr(Node));
        }else {
            LOG_ERROR(CORRELATOR_S16, "CORR_%u,ReferenceSignal,Error", num);
        }
    } else {
        LOG_ERROR(CORRELATOR_S16, "%u,NodeErr", num);
    }
    return res;
}

bool correlator_s16_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(CORRELATOR_S16, "%u,Init", num);
    const CorrelatorS16Config_t* Config = NULL;
    Config = CorrelatorS16GetConfig(num);
    res = correlator_s16_is_valid_config(Config);
    if(res) {
#ifdef HAS_CORRELATOR_S16_DIAG
        LOG_WARNING(CORRELATOR_S16, "%s", CorrelatorS16ConfigToStr(Config));
#endif
        CorrelatorS16Handle_t* Node = CorrelatorS16GetNode(num);
        if(Node) {
            LOG_INFO(CORRELATOR_S16, "Spot,Node");
            res = correlator_s16_init_common(Config, Node);
            Node->valid = true;
            res = circular_buffer_index_init(&Node->indexer, Config->size - 1);
        } else {
            LOG_ERROR(CORRELATOR_S16, "NodeErr");
        }
    } else {
        LOG_ERROR(CORRELATOR_S16, "ConfNodeErr");
    }

    return res;
}

static double complex calc_frequency_response_one_ll(CorrelatorS16Handle_t* const Node, double freq_hz) {
    double complex TransferFunction = 0 + 0 * I;
    uint32_t k = 0;
    for(k = 0; k < Node->size; k++) {
        double F = freq_hz / Node->sample_rate_hz;
        double argument = M_2PI * F * ((double)k);
        TransferFunction += ((double)Node->ReferenceSignal[k]) * (cos(argument) - sin(argument) * I);
    }
    return TransferFunction;
}

bool correlator_s16_impulse_response(uint8_t num) {
    bool res = false;
    LOG_WARNING(CORRELATOR_S16, "CORRELATOR_S16%u,CalcImpulseResponse:Step:%f Hz" CRLF, num);
    res = correlator_s16_reset_one(num);
    CorrelatorS16Handle_t* Node = CorrelatorS16GetNode(num);
    if(Node) {

        char lText[150] = {0};
        LOG_INFO(CORRELATOR_S16, "%s", CorrelatorS16NodeToStr(Node));

        static const table_col_t cols[] = {
            {8, "sample"},
            {8, "time"},
            {8, "in"},
            {8, "out"},
        };

        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t s = 0;
        int16_t sample_in = 0;
        int64_t sample_out = 0;
        for(s = 0; s < (Node->size + 2); s++) {
            double t_s = ((double)s) / Node->sample_rate_hz;

            if(1 == s) {
                sample_in = 1.0;
            } else {
                sample_in = 0.0;
            }
            res = correlator_s16_proc_in_out(num, sample_in, &sample_out);

            strcpy(lText, TSEP);
            snprintf(lText, sizeof(lText), "%s %6u " TSEP, lText, s);
            snprintf(lText, sizeof(lText), "%s %6.4f " TSEP, lText, t_s);
            snprintf(lText, sizeof(lText), "%s %6.3f " TSEP, lText, sample_in);
            snprintf(lText, sizeof(lText), "%s %6.3f " TSEP, lText, sample_out);

            cli_printf("%s" CRLF, lText);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    cli_printf(CRLF);

    return res;
}

bool correlator_s16_calc_frequency_response(uint8_t num, double f_step) {
    bool res = false;
    LOG_WARNING(CORRELATOR_S16, "CORRELATOR_S16%u,CalcFrequencyResponse:Step:%f Hz" CRLF, num, f_step);

    CorrelatorS16Handle_t* Node = CorrelatorS16GetNode(num);
    if(Node) {
        char lText[150] = {0};
        LOG_INFO(CORRELATOR_S16, "%s", CorrelatorS16NodeToStr(Node));

        static const table_col_t cols[] = {
            {9, "Freq"},
            {6, "ABS"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        double f_cur = 0;
        for(f_cur = 0.0; f_cur < Node->sample_rate_hz / 2.0; f_cur += f_step) {
            double complex TransferFunction = 0 + 0 * I;
            TransferFunction = calc_frequency_response_one_ll(Node, f_cur);

            strcpy(lText, TSEP);
            snprintf(lText, sizeof(lText), "%s %7.1f " TSEP, lText, f_cur);
            snprintf(lText, sizeof(lText), "%s %3.2f " TSEP, lText, cabs(TransferFunction));

            cli_printf("%s" CRLF, lText);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    cli_printf(CRLF);

    return res;
}

#ifdef HAS_FILE_PC
bool correlator_s16_save_csv_line(char* file_name_out, double value_x, double value_y) {
    bool res = false;
    if(file_name_out) {
        char lText[500] = {0};
        snprintf(lText, sizeof(lText), "%f,%f", value_x, value_y);
        res = file_pc_print_line(file_name_out, lText, strlen(lText));
    }
    return res;
}
#endif

#ifdef HAS_FILE_PC
bool correlator_s16_proc_file(uint8_t num, char* file_name, uint16_t column_x, uint16_t column_y) {
    bool res = false;
    LOG_WARNING(CORRELATOR_S16, "CORRELATOR_S16%u,File:[%s],ColX:%u,ColY:%u", num, file_name, column_x, column_y);
    int32_t line_cnt = file_pc_line_cnt(file_name);
    if(line_cnt) {
        LOG_INFO(CORRELATOR_S16, "File:[%s],Lines:%u", file_name, line_cnt);
        CorrelatorS16Handle_t* Node = CorrelatorS16GetNode(num);
        if(Node) {
            res = file_pc_delete(Node->file_name_out);
            int32_t cnt = 1;
            FILE* file_prt = NULL;
            file_prt = fopen(file_name, "r");
            if(file_prt) {
                LOG_INFO(CORRELATOR_S16, "File [%s] OpenOk", file_name);
                char csv_line[500] = {0};
                strcpy(csv_line, "");
                while(NULL != fgets(csv_line, sizeof(csv_line), file_prt)) {
                    LOG_PARN(CORRELATOR_S16, "%u:[%s]", cnt, csv_line);
                    double value_x = 0.0;
                    res = csv_parse_double(csv_line, column_x, &value_x);
                    if(res) {
                        double value_y = 0.0;
                        res = csv_parse_double(csv_line, column_y, &value_y);
                        if(res) {
                            int16_t sample_in = (int16_t)value_y;
                            int64_t sample_out = 0;
                            res = correlator_s16_proc_in_out(num, sample_in, &sample_out);
                            if(res) {
                                res = correlator_s16_save_csv_line(Node->file_name_out, value_x, sample_out);
                            }
                        } else {
                            LOG_ERROR(CORRELATOR_S16, "ParseXErrX:%f", value_x);
                        }
                    }
                    cnt++;
                    res = true;
                    if(0 == ((cnt) % (line_cnt / 400))) {
                        cli_printf("\r%s", ProgressToStr((uint32_t)cnt, (uint32_t)line_cnt));
                    }
                    strcpy(csv_line, "");
                }
                fclose(file_prt);
                LOG_INFO(CORRELATOR_S16, "File:[%s]:CloseOk", file_name);
            }
        }
    } else {
        LOG_ERROR(CORRELATOR_S16, "File [%s] OpenErr", file_name);
    }
    return res;
}
#endif

COMPONENT_INIT_ANY_PATTERT_CNT(CORRELATOR_S16, CORRELATOR_S16, correlator_s16, CORRELATOR_S16_MUN_CNT)
// COMPONENT_INIT_ANY_PATTERT(CORRELATOR_S16, CORRELATOR_S16, correlator_s16)
