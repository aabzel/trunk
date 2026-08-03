#include "correlator_naiv_s16.h"

#include <complex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "circular_buffer_index.h"
#include "code_generator.h"
#include "correlator_naiv_s16_diag.h"
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

COMPONENT_GET_NODE(CorrelatorNaivS16, correlator_naiv_s16)
COMPONENT_GET_CONFIG(CorrelatorNaivS16, correlator_naiv_s16)

static bool correlator_naiv_s16_push_ll(CorrelatorNaivS16Handle_t* Node, int16_t in) {
    bool res = true;
    LOG_DEBUG(CORRELATOR_NAIV_S16, "Push,Sample:%d,size:%u", in, Node->size);
    res = array_s16_add_front(Node->x, Node->size, in);
    return res;
}

bool correlator_naiv_s16_pull_ll(CorrelatorNaivS16Handle_t* Node, int16_t x0, int64_t* const out) {
    bool res = true;
    int64_t y = 0;
    int32_t i = 0;
    for(i = 0; i < Node->size; i++) {
        y += (int64_t)(((int32_t)Node->ReferenceSignal[i]) * ((int32_t)Node->x[i]));
    }

    LOG_DEBUG(CORRELATOR_NAIV_S16, "Pull,Sample:%lld, size:%u", y, Node->size);

    *out = y;
    return res;
}

bool correlator_naiv_s16_proc_in_out_ll(CorrelatorNaivS16Handle_t* Node, int16_t x, int64_t* const y) {
    bool res = false;
    res = correlator_naiv_s16_push_ll(Node, x);
    if(res) {
        res = correlator_naiv_s16_pull_ll(Node, x, y);
        Node->proc_cnt++;
    }
    LOG_DEBUG(CORRELATOR_NAIV_S16, "%u,%d->%lld", Node->proc_cnt, x, *y);

    return res;
}

bool correlator_naiv_s16_proc_in_out_array(uint8_t num, uint32_t size, const int16_t* const x, int64_t* const y) {
    bool res = false;
    CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
    uint32_t s = 0;
    for(s = 0; s < size; s++) {
        res = correlator_naiv_s16_push_ll(Node, x[s]);
        if(res) {
            res = correlator_naiv_s16_pull_ll(Node, x[s], &y[s]);
        }
    }
    return res;
}

bool correlator_naiv_s16_proc_in_out(uint8_t num, int16_t x, int64_t* const y) {
    bool res = false;
    CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
    if(Node) {
        /* if(Node)  can be commented to boost code execution */
        res = correlator_naiv_s16_proc_in_out_ll(Node, x, y);
    }
    return res;
}

int64_t correlator_naiv_s16_proc_in_out_short(uint8_t num, int16_t x) {
    int64_t out_val = 0;
    CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
    if(Node) {
        correlator_naiv_s16_proc_in_out_ll(Node, x, &out_val);
        // correlator_naiv_s16_diag_raw_mem(num);
    }
    return out_val;
}

static bool correlator_naiv_s16_init_common(const CorrelatorNaivS16Config_t* const Config,
                                            CorrelatorNaivS16Handle_t* const Node) {
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

int32_t correlator_naiv_s16_order_get(uint8_t num) {
    int32_t order = 0;
    CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
    if(Node) {
        order = Node->size;
    }
    return order;
}

static bool correlator_naiv_s16_init_custom(void) {
    bool res = true;
    LOG_WARNING(CORRELATOR_NAIV_S16, "CORRELATOR_NAIV_S16_VERSION:%u", CORRELATOR_NAIV_S16_VERSION);
    return res;
}

bool correlator_naiv_s16_reset_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(CORRELATOR_NAIV_S16, "CORRELATOR_NAIV_S16%u,ResetMem", num);
    CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
    if(Node) {
        if(Node->x) {
            LOG_INFO(CORRELATOR_NAIV_S16, "ZeroMem,%s", CorrelatorNaivS16NodeToStr(Node));
            uint32_t i = 0;
            for(i = 0; i < Node->size; i++) {
                Node->x[i] = 0.0;
                res = true;
            }
        }
    } else {
        LOG_ERROR(CORRELATOR_NAIV_S16, "NodeErr");
    }
    return res;
}

bool correlator_naiv_s16_write_ref_signal_ll(CorrelatorNaivS16Handle_t* Node, const int16_t* const ref_signal,
                                             const uint32_t size) {
    bool res = false;
    if(Node) {
        if(Node->ReferenceSignal) {
            if(size < Node->max_size) {
                Node->size = size;
                uint32_t i = 0;
                for(i = 0; i < Node->size; i++) {
                    Node->ReferenceSignal[Node->size - i - 1] = ref_signal[i];
                }
                res = true;
            } else {
                LOG_ERROR(CORRELATOR_NAIV_S16, "Size,Err");
            }
            LOG_INFO(CORRELATOR_NAIV_S16, "%s", CorrelatorNaivS16NodeToStr(Node));
        } else {
            LOG_ERROR(CORRELATOR_NAIV_S16, "ReferenceSignalMem,Err");
        }
    } else {
        LOG_ERROR(CORRELATOR_NAIV_S16, "NodeErr");
    }
    return res;
}

bool correlator_naiv_s16_write_ref_signal(uint8_t num, const int16_t* const ref_signal, const uint32_t size) {
    bool res = false;
    LOG_WARNING(CORRELATOR_NAIV_S16, "N:%u,LoadRef,Size:%u", num, size);
    CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
    if(Node) {
        res = correlator_naiv_s16_write_ref_signal_ll(Node, ref_signal, size);
    } else {
        LOG_ERROR(CORRELATOR_NAIV_S16, "NodeErr");
    }
    return res;
}

static bool correlator_naiv_s16_is_valid_config(const CorrelatorNaivS16Config_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            res = false;
            LOG_ERROR(CORRELATOR_NAIV_S16, "Name,Err%u", Config->num);
        }

        ifn(Config->file_name_out) {
            res = false;
            LOG_ERROR(CORRELATOR_NAIV_S16, "file_name_out,Err,%s", Config->name);
        }

        ifn(Config->file_name_in) {
            LOG_ERROR(CORRELATOR_NAIV_S16, "inFileName,Err,%s", Config->name);
            res = false;
        }

        ifn(Config->size <= Config->max_size) {
            res = false;
            LOG_ERROR(CORRELATOR_NAIV_S16, "Size,Err,%s Size:%u,MaxSize:%u", Config->name, Config->size,
                      Config->max_size);
        }

        ifn(0 < Config->size) {
            res = false;
            LOG_ERROR(CORRELATOR_NAIV_S16, "MinSize,Err,%s", Config->name);
        }

        ifn(0 < Config->sample_rate_hz) {
            res = false;
            LOG_ERROR(CORRELATOR_NAIV_S16, "SampeRete,Err,%s", Config->name);
        }

        ifn(Config->ReferenceSignal) {
            res = false;
            LOG_ERROR(CORRELATOR_NAIV_S16, "B,Err,%s", Config->name);
        }

        ifn(Config->x) {
            res = false;
            LOG_ERROR(CORRELATOR_NAIV_S16, "X,Err,%s", Config->name);
        }

        ifn(Config->valid) {
            res = false;
            LOG_ERROR(CORRELATOR_NAIV_S16, "Valid,Err,%s", Config->name);
        }
    }

    return res;
}

bool correlator_naiv_s16_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(CORRELATOR_NAIV_S16, "%u,Init", num);
    const CorrelatorNaivS16Config_t* Config = NULL;
    Config = CorrelatorNaivS16GetConfig(num);
    res = correlator_naiv_s16_is_valid_config(Config);
    if(res) {
#ifdef HAS_CORRELATOR_NAIV_S16_DIAG
        LOG_WARNING(CORRELATOR_NAIV_S16, "%s", CorrelatorNaivS16ConfigToStr(Config));
#endif
        CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
        if(Node) {
            LOG_INFO(CORRELATOR_NAIV_S16, "Spot,Node");
            res = correlator_naiv_s16_init_common(Config, Node);
            Node->valid = true;
            Node->init = true;
        } else {
            LOG_ERROR(CORRELATOR_NAIV_S16, "NodeErr");
        }
    } else {
        LOG_ERROR(CORRELATOR_NAIV_S16, "ConfNodeErr");
    }

    return res;
}

#ifdef HAS_FILE_PC
bool correlator_naiv_s16_save_csv_line(char* file_name_out, double value_x, double value_y) {
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
bool correlator_naiv_s16_proc_file(uint8_t num, char* file_name, uint16_t column_x, uint16_t column_y) {
    bool res = false;
    LOG_WARNING(CORRELATOR_NAIV_S16, "CORRELATOR_NAIV_S16%u,File:[%s],ColX:%u,ColY:%u", num, file_name, column_x,
                column_y);
    int32_t line_cnt = file_pc_line_cnt(file_name);
    if(line_cnt) {
        LOG_INFO(CORRELATOR_NAIV_S16, "File:[%s],Lines:%u", file_name, line_cnt);
        CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
        if(Node) {
            res = file_pc_delete(Node->file_name_out);
            int32_t cnt = 1;
            FILE* file_prt = NULL;
            file_prt = fopen(file_name, "r");
            if(file_prt) {
                LOG_INFO(CORRELATOR_NAIV_S16, "File [%s] OpenOk", file_name);
                char csv_line[500] = {0};
                strcpy(csv_line, "");
                while(NULL != fgets(csv_line, sizeof(csv_line), file_prt)) {
                    LOG_PARN(CORRELATOR_NAIV_S16, "%u:[%s]", cnt, csv_line);
                    double value_x = 0.0;
                    res = csv_parse_double(csv_line, column_x, &value_x);
                    if(res) {
                        double value_y = 0.0;
                        res = csv_parse_double(csv_line, column_y, &value_y);
                        if(res) {
                            int16_t sample_in = (int16_t)value_y;
                            int64_t sample_out = 0;
                            res = correlator_naiv_s16_proc_in_out(num, sample_in, &sample_out);
                            if(res) {
                                res = correlator_naiv_s16_save_csv_line(Node->file_name_out, value_x, sample_out);
                            }
                        } else {
                            LOG_ERROR(CORRELATOR_NAIV_S16, "ParseXErrX:%f", value_x);
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
                LOG_INFO(CORRELATOR_NAIV_S16, "File:[%s]:CloseOk", file_name);
            }
        }
    } else {
        LOG_ERROR(CORRELATOR_NAIV_S16, "File [%s] OpenErr", file_name);
    }
    return res;
}
#endif

COMPONENT_INIT_ANY_PATTERT_CNT(CORRELATOR_NAIV_S16, CORRELATOR_NAIV_S16, correlator_naiv_s16,
                               CORRELATOR_NAIV_S16_MUN_CNT)
