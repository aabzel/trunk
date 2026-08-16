#include "m_seq_mcal.h"

#include <inttypes.h>
#include <stdlib.h>

#include "array.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "dsp_types.h"

#ifdef HAS_FILE_PC
#include "file_pc.h"
#endif
#include "float_diag.h"
#include "log.h"
#include "num_to_str.h"
#include "utils_math.h"

#ifdef HAS_CORRELATOR_NAIV_S16
#include "correlator_naiv_s16.h"
#endif

static bool is_valid_feed_back_val(uint8_t value) {
    bool res = false;
    switch(value) {
    case 0:
        res = true;
        break;
    case 1:
        res = true;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool is_valid_seed_val(uint8_t value) {
    bool res = false;
    switch(value) {
    case 0:
        res = true;
        break;
    case 1:
        res = true;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

static int16_t m_sec_code_to_signal(const int8_t m_sec_code) {
    int16_t signal = 0;
    switch(m_sec_code) {
    case 0:
        signal = -1;
        break;
    case 1:
        signal = 1;
        break;
    default:
        signal = 0;
        break;
    }
    return signal;
}

bool m_sec_to_signal(uint8_t* m_seq, int16_t* signal, uint32_t size) {
    bool res = false;
    if(m_seq) {
        if(signal) {
            if(size) {
                uint32_t i = 0;
                for (i = 0; i < size; i++) {
                    signal[i] = m_sec_code_to_signal(m_seq[i]);
                }
                res = true;
            }
        }
    }
    return res;
}

COMPONENT_IS_VALID(Mseq, m_seq)
COMPONENT_GET_NODE(Mseq, m_seq)
COMPONENT_GET_CONFIG(Mseq, m_seq)

bool m_seq_init_common(const MseqConfig_t* const Config, MseqHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->generated_code = Config->generated_code;
            Node->code_size = Config->code_size;
            Node->feedback = Config->feedback;
            Node->max_size = Config->max_size;
            Node->cur_size = Config->cur_size;
            Node->memory = Config->memory;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool MseqIsValidConfig(const MseqConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;

        ifn(1 < Config->code_size) {
            LOG_ERROR(M_SEQ, "M_SEQ_%u,code_size,Err", Config->num);
            res = false;
        }
        ifn(Config->name) {
            LOG_ERROR(M_SEQ, "M_SEQ_%u,Name,Err", Config->num);
            res = false;
        }

        ifn(Config->generated_code) {
            LOG_ERROR(M_SEQ, "M_SEQ_%u,generated_code,Err", Config->num);
            res = false;
        }

        ifn(Config->memory) {
            LOG_ERROR(M_SEQ, "M_SEQ_%u,memory,Err", Config->num);
            res = false;
        }

        ifn(Config->feedback) {
            LOG_ERROR(M_SEQ, "M_SEQ_%u,feedback,Err", Config->num);
            res = false;
        }

        ifn(1 < Config->cur_size) {
            LOG_ERROR(M_SEQ, "M_SEQ_%u,cur_size,Err", Config->num);
            res = false;
        }

        ifn(1 < Config->max_size) {
            LOG_ERROR(M_SEQ, "M_SEQ_%u,max_size,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool m_seq_init_custom(void) {
    bool res = false;
    LOG_INFO(M_SEQ, "Version:%u", M_SEQ_VERSION);
    return res;
}

uint32_t m_seq_get_len(uint32_t shift_reg_num) {
    uint32_t sequence_len = 0;
    sequence_len = ipow(2, shift_reg_num) - 1;
    return sequence_len;
}

bool m_seq_get_code(uint8_t num, int8_t* const code, uint32_t size, uint32_t* written) {
    bool res = false;
    if(code) {
        MseqHandle_t* Node = MseqGetNode(num);
        if(Node) {
            LOG_INFO(M_SEQ, "%s", MseqNodeToStr(Node));
            uint32_t code_len = m_seq_get_len(Node->cur_size);
            if(code_len <= size) {
                uint32_t one_cnt = 0;
                uint32_t zeros_cnt = 0;
                uint32_t i = 0;
                for(i = 0; i < code_len; i++) {
                    code[i] = m_seq_get_sample(num);
                    if(1 == code[i]) {
                        one_cnt++;
                    } else {
                        zeros_cnt++;
                    }
                }

                if((zeros_cnt + 1) == one_cnt) {
                    res = true;
                    if(written) {
                        *written = code_len;
                    }
                } else {
                    res = false;
                    LOG_ERROR(M_SEQ, "CodeError,0Cnt:%u,1Cnt:%u", zeros_cnt, one_cnt);
                }
            } else {
                res = false;
                LOG_ERROR(M_SEQ, "Size,Error,CodeLen:%u,Size:%u", code_len, size);
            }
        } else {
            res = false;
            LOG_ERROR(M_SEQ, "Node,Error");
        }
    } else {
        res = false;
        LOG_ERROR(M_SEQ, "CodeError");
    }
    return res;
}

bool m_seq_feedback(uint8_t num, uint8_t offset, uint8_t value) {
    bool res = false;
    MseqHandle_t* Node = MseqGetNode(num);
    if(Node) {
        if(offset < Node->cur_size) {
            res = is_valid_feed_back_val(value);
            if(res) {
                Node->feedback[offset] = value;
            }
        }
    }
    return res;
}

bool m_seq_seed_set(uint8_t num, uint8_t offset, uint8_t value) {
    bool res = false;
    MseqHandle_t* Node = MseqGetNode(num);
    if(Node) {
        if(offset < Node->cur_size) {
            res = is_valid_seed_val(value);
            if(res) {
                Node->memory[offset] = value;
            }
        }
    }
    return res;
}

bool m_seq_generate(uint8_t num) {
    bool res = false;
    MseqHandle_t* Node = MseqGetNode(num);
    if(Node) {
        log_level_t ll = log_level_get(M_SEQ);
        uint32_t i = 0;
        uint32_t ZeroCnt = 0;
        uint32_t OneCnt = 0;
        uint32_t m_seq_len = m_seq_get_len(Node->cur_size);
        LOG_DEBUG(M_SEQ, "%s", MseqNodeToStr(Node));

        if(m_seq_len <= Node->code_size) {
            for(i = 0; i < m_seq_len; i++) {
                Node->generated_code[i] = m_seq_get_sample(num);
                if(0 == Node->generated_code[i]) {
                    ZeroCnt++;
                }
                if(1 == Node->generated_code[i]) {
                    OneCnt++;
                }
                if(LOG_LEVEL_DEBUG == ll) {
                    cli_printf("%u", Node->generated_code[i]);
                }
            }

            // cli_printf(CRLF);
            if((ZeroCnt + 1) == OneCnt) {
                LOG_DEBUG(M_SEQ, "GenerateOk");
                Node->m_seq_len = m_seq_len;
                res = true;
            } else {
                res = false;
                LOG_DEBUG(M_SEQ, "GenerateError Ones:%u,Zeros:%u", OneCnt, ZeroCnt);
            }
        } else {
            LOG_ERROR(M_SEQ, "Error,SmallMem,Need:%u,Size:%u", Node->m_seq_len, Node->code_size);
        }
    } else {
        LOG_ERROR(M_SEQ, "Error,UnknownGenerator");
    }

    return res;
}

#ifdef HAS_CORRELATOR_NAIV_S16
static bool correlator_compose_line(char* temp, uint32_t size, const CorrelationInfo_t* const Info) {
    bool res = true;
    strcpy(temp, "");
    snprintf(temp, size, "%s s,%4d,", temp, Info->sample);
    snprintf(temp, size, "%s Cor,%" PRId64 ",", temp, Info->correlation);
    snprintf(temp, size, "%s AbsCor,%" PRId64 ",", temp, Info->abs_correlation);
    snprintf(temp, size, "%s CorLog,%f,", temp, Info->correlation_log);
    return res;
}
#endif

#ifdef HAS_CORRELATOR_NAIV_S16
static bool m_seq_calc_correlation(const int16_t* const in_signal, const uint32_t size, char* CorrelationFileName) {
    bool res = false;
    if(in_signal) {
        FILE* pFile;
        file_pc_delete(CorrelationFileName);
        pFile = fopen(CorrelationFileName, "w");
        if(pFile) {
            uint32_t i = 0;
            CorrelationInfo_t Cur = {0};
            for(i = 0; i < size; i++) {
                Cur.sample = i;
                Cur.correlation = correlator_naiv_s16_proc_in_out_short(CORRELATOR_NAIV_S16_MUN_M_SEC, in_signal[i]);
                Cur.abs_correlation = math_abs_s64(Cur.correlation);
                Cur.correlation_log = 0.0;
                if(0 < Cur.abs_correlation) {
                    Cur.correlation_log = (float)logf((float)Cur.abs_correlation);
                }

                char temp[200] = {0};
                res = correlator_compose_line(temp, sizeof(temp), &Cur);

                fprintf(pFile, "%s\n", temp);
            }

            fclose(pFile);
        }
    }
    return res;
}
#endif

#ifdef HAS_CORRELATOR_NAIV_S16
bool m_seq_calc_acf(uint8_t num, uint32_t shift_reg_num, char* CorrelationFileName) {
    bool res = false;
    LOG_INFO(M_SEQ, "CalcAutoCorrelation:%u", num);
    MseqHandle_t* Node = MseqGetNode(num);
    if(Node) {
        res = m_seq_reinit_one(num, shift_reg_num);
        if(res) {
            uint32_t code_len = m_seq_get_len(shift_reg_num);
            LOG_INFO(M_SEQ, "CodeLen:%u", code_len);
            int8_t* mSecCode = (int8_t*)malloc(code_len);
            if(mSecCode) {
                res = m_seq_get_code(num, mSecCode, code_len, NULL);
                if(res) {
                    LOG_INFO(M_SEQ, "Mseq:[%s]", ArrayU8ToStr(mSecCode, code_len));
                    int16_t* ref_signal = (int16_t*)malloc(sizeof(int16_t) * code_len);
                    if(ref_signal) {
                        uint32_t i = 0;
                        for(i = 0; i < code_len; i++) {
                            ref_signal[i] = m_sec_code_to_signal(mSecCode[i]);
                        }
                        LOG_INFO(M_SEQ, "RefSignal:[%s]", ArrayS16ToStr(ref_signal, code_len));
                        res = correlator_naiv_s16_write_ref_signal(CORRELATOR_NAIV_S16_MUN_M_SEC, ref_signal, code_len);

                        // correlator_naiv_s16_diag_raw_mem(CORRELATOR_NAIV_S16_MUN_M_SEC);

                        int16_t* in_signal = (int16_t*)malloc(sizeof(int16_t) * 4 * code_len);
                        if(in_signal) {
                            uint32_t k = 0;
                            for(k = 0; k < (code_len * 4); k++) {
                                in_signal[k] = 0;
                            }

                            for(k = 0; k < (code_len); k++) {
                                in_signal[k] = 0;
                                in_signal[code_len + k] = ref_signal[k];
                                in_signal[code_len * 2 + k] = 0;
                                in_signal[code_len * 3 + k] = 0;
                            }

                            LOG_INFO(M_SEQ, "InSignal:[%s]", ArrayS16ToStr(in_signal, 4 * code_len));

                            res = m_seq_calc_correlation(in_signal, code_len * 4, CorrelationFileName);
                        } else {
                            LOG_ERROR(M_SEQ, "MallocSignalErr");
                        }
                    } else {
                        LOG_ERROR(M_SEQ, "MallocRefErr");
                    }
                    free(mSecCode);
                } else {
                    LOG_ERROR(M_SEQ, "GetCodeErr");
                }
            } else {
                LOG_ERROR(M_SEQ, "MallocErr");
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_CORRELATOR_NAIV_S16
bool m_seq_calc_periodic_acf(uint8_t num, uint32_t shift_reg_num, char* CorrelationFileName) {
    bool res = false;
    LOG_INFO(M_SEQ, "CalcPeriodicAutoCorrelation:%u", num);
    MseqHandle_t* Node = MseqGetNode(num);
    if(Node) {
        res = m_seq_reinit_one(num, shift_reg_num);
        if(res) {

            uint32_t code_len = m_seq_get_len(shift_reg_num);

            LOG_INFO(M_SEQ, "CodeLen:%u", code_len);

            int8_t* mSecCode = (int8_t*)malloc(code_len);
            if(mSecCode) {
                res = m_seq_get_code(num, mSecCode, code_len, NULL);
                if(res) {

                    LOG_INFO(M_SEQ, "Mseq:[%s]", ArrayU8ToStr(mSecCode, code_len));
                    int16_t* ref_signal = (int16_t*)malloc(sizeof(int16_t) * code_len);
                    if(ref_signal) {
                        uint32_t i = 0;
                        for(i = 0; i < code_len; i++) {
                            ref_signal[i] = m_sec_code_to_signal(mSecCode[i]);
                        }
                        LOG_INFO(M_SEQ, "RefSignal:[%s]", ArrayS16ToStr(ref_signal, code_len));
                        res = correlator_naiv_s16_write_ref_signal(CORRELATOR_NAIV_S16_MUN_M_SEC, ref_signal, code_len);

                        // correlator_naiv_s16_diag_raw_mem(CORRELATOR_NAIV_S16_MUN_M_SEC);

                        int16_t* in_signal = (int16_t*)malloc(sizeof(int16_t) * 4 * code_len);
                        if(in_signal) {
                            // memset(in_signal,0,sizeof(sizeof(int16_t)*3*code_len));
                            uint32_t k = 0;
                            for(k = 0; k < (code_len * 4); k++) {
                                in_signal[k] = 0;
                            }
                            // memcpy(&in_signal[code_len],ref_signal,sizeof(sizeof(int16_t)*code_len));

                            for(k = 0; k < (code_len); k++) {
                                in_signal[k] = ref_signal[k];
                                in_signal[code_len + k] = ref_signal[k];
                                in_signal[code_len * 2 + k] = ref_signal[k];
                                in_signal[code_len * 3 + k] = ref_signal[k];
                            }

                            LOG_INFO(M_SEQ, "InSignal:[%s]", ArrayS16ToStr(in_signal, 4 * code_len));

                            res = m_seq_calc_correlation(in_signal, code_len * 4, CorrelationFileName);
                        }
                    }
                }
            }
        }
    }
    return res;
}
#endif

int8_t m_seq_get_sample(uint8_t num) {
    int8_t value = 0x55;
    MseqHandle_t* Node = MseqGetNode(num);
    if(Node) {
        uint32_t i = 0;
        int8_t new_val = 0;
        for(i = 0; i < Node->cur_size; i++) {
            new_val ^= Node->memory[i] * Node->feedback[i];
        }
        bool res = array_u8_add_front(Node->memory, Node->cur_size, new_val);
        if(res) {
            value = Node->memory[Node->cur_size - 1];
            LOG_PARN(M_SEQ, "M_SEQ_%u,Sample:%u", num, value);
            Node->spin++;
        }
    }
    return value;
}

bool m_seq_init_node(MseqHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->spin = 0;
        Node->valid = true;
        Node->memory[0] = 1;
        res = true;
    }
    return res;
}

float m_seq_signal_duration(uint8_t num, float carrier_frequency_hz, uint32_t periods_per_chip) {
    float signal_diration_s = -10.0f;
    MseqHandle_t* Node = MseqGetNode(num);
    if(Node) {
        if(0 < carrier_frequency_hz) {
            if(periods_per_chip) {
                float period_diration_s = 1.0f / carrier_frequency_hz;
                signal_diration_s = period_diration_s * ((float)(periods_per_chip * m_seq_get_len(Node->cur_size)));
            }
        }
    }
    return signal_diration_s;
}

bool m_seq_reinit_one(uint8_t num, uint32_t shift_reg_num) {
    bool res = false;
    MseqHandle_t* Node = MseqGetNode(num);
    if(Node) {
        if(shift_reg_num <= Node->max_size) {
            Node->cur_size = shift_reg_num;
            uint32_t i = 0;
            for(i = 0; i < Node->cur_size; i++) {
                Node->memory[i] = 0;
                // Node->feedback[i] = 0;
            }
            Node->memory[0] = 1;

            res = m_seq_find_first_feedback(num) ;
            LOG_INFO(M_SEQ, "M_SEQ_%u,%s", num, MseqNodeToStr(Node));
            res = true;
        } else {
            LOG_ERROR(M_SEQ, "M_SEQ_%u,%s", num, MseqNodeToStr(Node));
        }
    }
    return res;
}


#ifdef HAS_CORRELATOR_NAIV_S16
bool m_seq_calc_correlation_2(uint8_t* seq1, uint8_t* seq2, uint32_t size, char* CorrelationFileName) {
    bool res = false;

    if(seq1 && seq2) {
        LOG_INFO(M_SEQ, "Mseq1:[%s]", ArrayU8ToStr(seq1, size));
        LOG_INFO(M_SEQ, "Mseq2:[%s]", ArrayU8ToStr(seq2, size));
        int16_t* ref_signal = (int16_t*)malloc(sizeof(int16_t) * size);
        if(ref_signal) {
            res = m_sec_to_signal(seq1, ref_signal, size);
            LOG_INFO(M_SEQ, "RefSignal:[%s]", ArrayS16ToStr(ref_signal, size));
            res = correlator_naiv_s16_write_ref_signal(CORRELATOR_NAIV_S16_MUN_M_SEC, ref_signal, size);
            int16_t* in_signal = (int16_t*)malloc(sizeof(int16_t) * 4 * size);
            if(in_signal) {
                res = array_s16_zero(in_signal, 4 * size);
                res = m_sec_to_signal(seq2, &in_signal[size], size);

                LOG_INFO(M_SEQ, "Signal %s", ArrayS16ToStr(in_signal, size));
                // array_i16_print(in_signal,   size * 4, 0.1);
                res = m_seq_calc_correlation(in_signal, size * 4, CorrelationFileName);
                free(in_signal);
            }
            free(ref_signal);
        }
    }

    return res;
}
#endif

bool m_seq_find_feedback(uint8_t num) {
    bool out_res = false;
    MseqHandle_t* Node = MseqGetNode(num);
    if(Node) {
        uint32_t cnt = ipow(2, Node->cur_size);
        uint32_t ok_cnt = 0;
        uint32_t f = 0;
        for(f = 0; f < cnt; f++) {
            uint32_t bit = 0;
            for(bit = 0; bit < Node->cur_size; bit++) {
                m_seq_feedback(num, bit, CHECK_BIT_NUM(f, bit));
            }

            m_seq_seed_set(num, 0, 1);
            bool res = false;
            res = m_seq_generate(num);
            res = m_seq_generate(num) && res;
            res = m_seq_generate(num) && res;
            if(res) {
                LOG_WARNING(M_SEQ, "M_SEQ_%u,Spot,FeedBack:%u=%s,feed", num, f, utoa_bin32(f));
                ok_cnt++;
                out_res = true;
            }
        }
        LOG_INFO(M_SEQ, "M_SEQ_%u,Spot,OkCnt:%u", num, ok_cnt);
    }
    return out_res;
}


bool m_seq_find_first_feedback(uint8_t num) {
    bool out_res = false;
    MseqHandle_t* Node = MseqGetNode(num);
    if(Node) {
        uint32_t cnt = ipow(2, Node->cur_size);
        uint32_t ok_cnt = 0;
        uint32_t f = 0;
        for(f = 0; f < cnt; f++) {
            uint32_t bit = 0;
            for(bit = 0; bit < Node->cur_size; bit++) {
                m_seq_feedback(num, bit, CHECK_BIT_NUM(f, bit));
            }

            m_seq_seed_set(num, 0, 1);
            bool res = false;
            res = m_seq_generate(num);
            res = m_seq_generate(num) && res;
            res = m_seq_generate(num) && res;
            if(res) {
                LOG_WARNING(M_SEQ, "M_SEQ_%u,Spot,FeedBack:%u=%s,feed", num, f, utoa_bin32(f));
                ok_cnt++;
                out_res = true;
                break;
            }
        }

    }
    return out_res;
}

static int8_t m_seq_modilator(MseqHandle_t* Node, float time_s, float carrier_period_s, uint32_t periods_per_chip) {
    int8_t modulator = 0;
    if(0 < Node->m_seq_len) {
        LOG_PARN(M_SEQ, "CalcModutator,T:%f s,CarPer:%f s,PeriodsPerSec:%u", time_s, carrier_period_s,
                 periods_per_chip);
        float time_part_s = carrier_period_s * ((float)periods_per_chip);
        uint32_t part = (uint32_t)(time_s / time_part_s);
        if(part < Node->m_seq_len) {
            modulator = m_sec_code_to_signal(Node->generated_code[part]);
        } else {
            modulator = 0;
        }
        LOG_PARN(M_SEQ, "UpTime:%s,Part:%u,modulator:%d", FloatToStr(time_s, 1), part, modulator);
    } else {
        LOG_ERROR(M_SEQ, "CodeIsNotGenerated:%u",Node->num);
    }
    return modulator;
}

float m_seq_calc_sample(uint8_t num, float time_s, float amplitude, float carrier_frequency_hz,
                        uint32_t periods_per_chip) {
    float amplitude_scaled = 0.0f;
    LOG_PARN(M_SEQ, "MSEQ%u,CalcSample,%f,CarFre:%f Hz,PeriodsPerSec:%u", num, time_s, carrier_frequency_hz,
             periods_per_chip);
    MseqHandle_t* Node = MseqGetNode(num);
    if(Node) {
        float signal_diration_s = m_seq_signal_duration(num, carrier_frequency_hz, periods_per_chip);
        if(time_s <= signal_diration_s) {
            float signal = 0.0;
            float carrier_period_s = 1.0f / carrier_frequency_hz;
            float modulator = (float)m_seq_modilator(Node, time_s, carrier_period_s, periods_per_chip);
            float lineVal = (time_s)*carrier_frequency_hz; /*tune frequency*/
            float argument = 0.0;
            argument = 2.0f * M_PI * lineVal;
            signal = (float)sinf((float)argument);
            amplitude_scaled = amplitude * signal * modulator;
        } else {
            amplitude_scaled = 0.0;
        }
    } else {
        LOG_ERROR(M_SEQ, "Node,Err %u", num);
    }

    return amplitude_scaled;
}

bool m_seq_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(M_SEQ, "M_SEQ_%u", num);
    const MseqConfig_t* Config = MseqGetConfig(num);
    res = MseqIsValidConfig(Config);
    if(res) {
#ifdef HAS_M_SEQ_DIAG
        LOG_WARNING(M_SEQ, "%s", MseqConfigToStr(Config));
#endif
        MseqHandle_t* Node = MseqGetNode(num);
        if(Node) {
            res = m_seq_init_common(Config, Node);
            res = m_seq_init_node(Node);
            res = m_seq_reinit_one(num, Config->cur_size);
            Node->init = true;
            LOG_INFO(M_SEQ, "M_SEQ_%u,InitOk", num);
        } else {
            LOG_ERROR(M_SEQ, "NodeErr %u", num);
        }
    } else {
        LOG_ERROR(M_SEQ, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_ANY_PATTERT_CNT(M_SEQ, M_SEQ, m_seq, 3)
