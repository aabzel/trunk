#include "csv.h"

#ifdef HAS_PC
#include <stdio.h>
#endif
#include <string.h>

#include "convert.h"
#include "csv_diag.h"
#include "log.h"

bool csv_proc_fetch_value(CsvFsm_t* Node, uint32_t cur_index) {
    bool res = false;
    if(Node->fetch_index == cur_index) {
        if(Node->out_buff) {
            LOG_DEBUG(CSV, "Fetch [%s] Len %u Ok", Node->out_buff, Node->out_size);
            res = true;
        }
    } else {
        LOG_DEBUG(CSV, "Skip Cur:%u Need:%u", cur_index, Node->fetch_index);
    }
    return res;
}

static inline bool csv_add_letter(CsvFsm_t* const Node, uint32_t index, char letter, bool last_char) {
    bool res = true;
    if(Node->position == Node->fetch_index) {
        // Node->i = index;
        if(0 == index) {
            // LOG_DEBUG(CSV, "FetchVal!:Index:%u", Node->abs_index);
            Node->start_value_index = Node->abs_index;
            Node->fetch_index_done = true;
            res = true;
        }
        if(index < Node->out_size) {
            Node->out_buff[index] = letter; // Node->symbol;
            res = true;
            if(last_char) {
                Node->fetch_done = last_char;
                // LOG_PROTECTED(CSV, "CSV[%u]=[%s]", Node->position, Node->out_buff);
            }
        } else {
            Node->error_cnt++;
            res = true;
        }
    }
    return res;
}

static inline bool csv_cnt_init_proc(CsvFsm_t* Node) {
    bool res = false;
    // LOG_DEBUG(CSV, "ProcInit %c Input:%s", Node->symbol, CsvInput2Str(Node->input));
    if(Node) {
        switch(Node->input) {
        case CSV_INPUT_NOT_SEP: {
            Node->cnt++;
            Node->i = 0;
            res = csv_add_letter(Node, 0, Node->symbol, false);
            Node->state = CSV_STATE_ACCUMULATE;
        } break;
        case CSV_INPUT_SEP: {
            Node->i = 0;
            res = csv_add_letter(Node, 0, 0, true);
            Node->cnt++;
            Node->position++;
            Node->state = CSV_STATE_SEP;
        } break;
        case CSV_INPUT_END: {
            Node->state = CSV_STATE_END;
            Node->i = 0;
            res = csv_add_letter(Node, 0, 0, true);
            Node->cnt++;
        } break;
        default:
            break;
        }
    }
    return res;
}

static inline bool csv_cnt_acc_proc(CsvFsm_t* Node) {
    bool res = false;
    // LOG_DEBUG(CSV, "ProcAcc %c Input:%s", Node->symbol, CsvInput2Str(Node->input));
    if(Node) {
        switch(Node->input) {
        case CSV_INPUT_NOT_SEP: {
            /*SaveChar*/
            Node->state = CSV_STATE_ACCUMULATE;
            Node->i++;
            res = csv_add_letter(Node, Node->i, Node->symbol, false);
        } break;
        case CSV_INPUT_SEP: {
            Node->i++;
            res = csv_add_letter(Node, Node->i, 0, true);
            Node->i = 0;
            Node->position++;
            Node->state = CSV_STATE_SEP;
        } break;
        case CSV_INPUT_END: {
            Node->i++;
            res = csv_add_letter(Node, Node->i, 0x00, true);
            Node->state = CSV_STATE_END;
        } break;
        default:
            res = false;
            break;
        }
    }
    return res;
}

static inline bool csv_cnt_sep_proc(CsvFsm_t* Node) {
    bool res = false;
    // LOG_DEBUG(CSV, "ProcSep %c Input:%s", Node->symbol, CsvInput2Str(Node->input));
    if(Node) {
        switch(Node->input) {
        case CSV_INPUT_NOT_SEP: {
            Node->cnt++;
            res = csv_add_letter(Node, 0, Node->symbol, false);
            Node->state = CSV_STATE_ACCUMULATE;
        } break;
        case CSV_INPUT_SEP: {
            res = csv_add_letter(Node, 0, 0, true);
            Node->position++;
            Node->state = CSV_STATE_SEP;
            Node->cnt++;
        } break;
        case CSV_INPUT_END: {
            res = csv_add_letter(Node, 0, 0, false);
            Node->state = CSV_STATE_END;
            Node->cnt++;
        } break;
        default:
            break;
        }
    }
    return res;
}

static inline bool csv_cnt_end_proc(CsvFsm_t* const Node) {
    bool res = false;
#ifdef HAS_CSV_DIAG
    LOG_DEBUG(CSV, "ProcEnd %c Input:%s", Node->symbol, CsvInput2Str(Node->input));
#endif
    if(Node) {
        switch(Node->input) {
        case CSV_INPUT_NOT_SEP: {
            res = false;
            Node->i = 0;
            Node->out_buff[0] = 0x00;
            Node->state = CSV_STATE_END;
        } break;
        case CSV_INPUT_SEP: {
            res = false;
            Node->i = 0;
            Node->out_buff[0] = 0x00;
            Node->state = CSV_STATE_END;
        } break;
        case CSV_INPUT_END: {
            res = false;
            Node->i = 0;
            Node->out_buff[0] = 0x00;
            Node->state = CSV_STATE_END;
        } break;
        default:
            break;
        }
    }
    return res;
}

static CsvInput_t csv_symbol_2_input(CsvFsm_t* Node, char symbol) {
    if(symbol == Node->separator) {
        Node->input = CSV_INPUT_SEP;
    } else {
        Node->input = CSV_INPUT_NOT_SEP;
    }
    return Node->input;
}

static inline bool csv_cnt_proc(CsvFsm_t* const Node, char symbol) {
    bool res = false;
    if(Node) {
        Node->symbol = symbol;
        if(CSV_INPUT_UNDEF == Node->input) {
            csv_symbol_2_input(Node, symbol);
        }
#ifdef HAS_CSV_DIAG
        CsvNodeDiag(Node);
#endif

        switch(Node->state) {
        case CSV_STATE_INIT:
            res = csv_cnt_init_proc(Node);
            if(false == res) {
                LOG_ERROR(CSV, "InitProcErr %c", symbol);
            }

            break;

        case CSV_STATE_ACCUMULATE:
            res = csv_cnt_acc_proc(Node);
            if(false == res) {
                LOG_ERROR(CSV, "AccProcErr %c", symbol);
            }
            break;

        case CSV_STATE_SEP:
            res = csv_cnt_sep_proc(Node);
            if(false == res) {
                LOG_ERROR(CSV, "SepProcErr %c", symbol);
            }
            break;

        case CSV_STATE_END:
            res = csv_cnt_end_proc(Node);
            if(false == res) {
                LOG_ERROR(CSV, "EndProcErr %c", symbol);
            }
            break;
        default:
            LOG_ERROR(CSV, "UndefStateErr %u", Node->state);
            break;
        }
        Node->prev_char = symbol;
        Node->abs_index++;
    } else {
        LOG_ERROR(CSV, "NodeErr");
    }
    return res;
}

static inline bool csv_init(CsvFsm_t* Node, char separator, int32_t fetch_index, char* const out_text, uint32_t size) {
    bool res = false;
    /* out_text can bee NULL in csv_cnt() */
    // LOG_DEBUG(CSV, "Init: Separator:%c", separator);
    if(Node) {
        Node->start_value_index = -1; /*result array in place start index*/
        Node->separator = separator;
        Node->init_done = true;
        Node->fetch_done = false;
        Node->prev_char = 0x00;
        Node->error_cnt = 0;
        Node->state = CSV_STATE_INIT;
        Node->input = CSV_INPUT_UNDEF;
        Node->cnt = 0;
        Node->position = 0;
        Node->abs_index = 0;
        Node->i = 0;
        Node->out_buff = out_text;
        Node->out_size = size;
        Node->fetch_index = fetch_index;
        // LOG_DEBUG(CSV, "ValMaxSize:%u byte FetchIndex: %d", size, fetch_index);
        res = true;
    }
    return res;
}

uint32_t csv_cnt(const char* const in_text, char separator) {
    bool res = false;
    uint32_t len = strlen(in_text);
    // LOG_DEBUG(CSV, "Text:[%s] Size:%u byte Separator:%c", text, len, separator);

    CsvFsm_t Item = {0};
    if(0 == len) {
        Item.cnt = 1;
    } else {
        res = csv_init(&Item, separator, -1, NULL, 0);
        if(res) {
            uint32_t i = 0;
            for(i = 0; i < len; i++) {
                Item.input = CSV_INPUT_UNDEF;
                res = csv_cnt_proc(&Item, in_text[i]);
                // if(false == res) {
                // LOG_ERROR(CSV, "ProcErr[%u]=%c", i, in_text[i]);
                //}
            }
            Item.input = CSV_INPUT_END;
            res = csv_cnt_proc(&Item, 0x00);
        } else {
            // LOG_ERROR(CSV, "InitErr");
        }
    }

    return Item.cnt;
}

uint32_t csv_count_node(const char* const in_text, char separator, const char* const name) {
    uint32_t cnt = 0;
    uint32_t num = csv_cnt(in_text, separator);
    if(num) {
        uint32_t i = 0;
        for(i = 0; i < num; i++) {
            char cur_name[100] = {0};
            bool res = false;
            res = csv_parse_text(in_text, separator, i, cur_name, sizeof(cur_name));
            if(res) {
                int ret = 0;
                ret = strcmp(cur_name, name);
                if(0 == ret) {
                    cnt++;
                }
            }
        }
    }
    return cnt;
}

uint32_t csv_del_node_front(const char* const in_text, char separator, const char* const name) {

    bool res = false;
    uint32_t num = csv_cnt(in_text, separator);
    if(num) {
        uint32_t i = 0;
        for(i = 0; i < num; i++) {
            char cur_name[100] = {0};
            res = csv_parse_text(in_text, separator, i, cur_name, sizeof(cur_name));
            if(res) {
                int ret = 0;
                ret = strcmp(cur_name, name);
                if(0 == ret) {
                    // TODO
                }
            }
        }
    }
    return res;
}

/*returns pointer at in_text
 * separator can be 0x00
 * */
bool csv_fetch_text(const char* const in_text, uint32_t size, char separator, uint32_t index, uint32_t* const offset) {
    bool res = false;
    if(in_text) {
        if(offset) {
            if(size) {
                LOG_DEBUG(CSV, "InText:[%s] Size:%u Sep:%c Index:%u", in_text, size, separator, index);

                CsvFsm_t Item = {0};
                csv_init(&Item, separator, index, NULL, 0);
                uint32_t i = 0;
                for(i = 0; i < size; i++) {
                    Item.input = CSV_INPUT_UNDEF;
                    res = csv_cnt_proc(&Item, in_text[i]);
                }
                Item.input = CSV_INPUT_END;
                res = csv_cnt_proc(&Item, ' '); /*Here we can put any char. It will be ignored*/

                res = false;

                LOG_DEBUG(CSV, "StartValueIndex:%d", Item.start_value_index);
                res = true;
                if(0 <= Item.start_value_index) {
                    if(Item.start_value_index < size) {
                        *offset = Item.start_value_index;
                        LOG_DEBUG(CSV, "SpotSubVal [%s]", in_text + Item.start_value_index);
                        LOG_DEBUG(CSV, "Spot!");
                    }
                } else {
                    LOG_ERROR(CSV, "fetch_doneErr");
                }

            } else {
                LOG_DEBUG(CSV, "InTextSezeErr");
                res = false;
            }
        } else {
            LOG_ERROR(CSV, "OutTextErr");
        }
    } else {
        LOG_ERROR(CSV, "InTextErr");
    }
    return res;
}

#ifdef HAS_PC
bool csv_add_back(char* const in_text, char separator, char* const suffix) {
    bool res = false;
    uint32_t cnt = csv_cnt(in_text, separator);
    if(0 == cnt) {
        sprintf(in_text, "%s", suffix);
    } else {
        sprintf(in_text, "%s%c%s", in_text, separator, suffix);
    }
    return res;
}
#endif

/*
 * in_text - CSV str
 * separator - separator [,] [;] [.] [ ]
 * index- 0; 1; 2; 3; ...
 * size - out size
 * out_text - out storage
 */
bool csv_parse_text(const char* const in_text, char separator, uint32_t index, char* const out_text,
                    uint32_t out_size) {
    bool res = false;
    if(in_text && out_text) {
        uint32_t len = strlen(in_text);
        LOG_DEBUG(CSV, "InText:[%s],Size:%u,Sep:[%c],Index:%u", in_text, len, separator, index);
        CsvFsm_t Item = {0};
        csv_init(&Item, separator, index, out_text, out_size);
        uint32_t i = 0;
        for(i = 0; i < len; i++) {
            Item.input = CSV_INPUT_UNDEF;
            res = csv_cnt_proc(&Item, in_text[i]);
        }
        Item.input = CSV_INPUT_END;
        res = csv_cnt_proc(&Item, 0x00);

        res = false;
        if(Item.fetch_done) {
            if(0 == Item.error_cnt) {
                res = true;
            }
        }
    }
    return res;
}

/*
 * http://all-ht.ru/inf/prog/c/func/strchr.html
 */
bool csv_parse_double(const char* const in_text, uint32_t index, double* const value) {
    bool res = false;
    if(in_text) {
        uint32_t len = strlen(in_text);
        LOG_DEBUG(CSV, "Text:[%s] Size:%u byte Index:%u", in_text, len, index);
        if(value) {
            char local_data[60] = {0};
            res = csv_parse_text(in_text, ',', index, local_data, sizeof(local_data));
            LOG_DEBUG(CSV, "TryParseDoubleIn[%s]", local_data);
            res = false;
#ifdef HAS_STR2_DOUBLE
            res = try_str2double(local_data, value);
#endif
            if(res) {
                LOG_DEBUG(CSV, "ParseDoubleOk[%s]->%f", local_data, *value);
            } else {
                LOG_ERROR(CSV, "ParseDoubleErr [%s]->%f", local_data, *value);
                LOG_ERROR(CSV, "Text [%s],i:%u", in_text, index);
            }
        }
    }
    return res;
}

#ifdef HAS_PC

bool csv_save_to_end(char* file_name, double x, double y) {
    bool res = false;
    LOG_DEBUG(CSV, "Save,File[%s]", file_name);
    FILE* file_prt = NULL;
    file_prt = fopen(file_name, "a");
    if(file_prt) {
        LOG_DEBUG(CSV, "File,[%s],Open,Ok", file_name);
        uint32_t ok = 0;
        int ret;
        ret = fprintf(file_prt, "%f,%f\n", x, y);
        if(0 < ret) {
            ok++;
        }

        fclose(file_prt);
        if(ok == 1) {
            res = true;
        } else {
            res = false;
        }
    } else {
        LOG_ERROR(CSV, "File [%s] OpenErr", file_name);
    }
    return res;
}

bool csv_save_two_double(char* file_name, uint32_t size, double* x, double* y) {
    bool res = false;
    LOG_DEBUG(CSV, "Save File[%s] Size:%u", file_name, size);
    FILE* file_prt = NULL;
    file_prt = fopen(file_name, "w");
    if(file_prt) {
        LOG_INFO(CSV, "File [%s] OpenOk", file_name);
        uint32_t t = 0;
        uint32_t ok = 0;
        int ret;
        for(t = 0; t < size; t++) {
            ret = fprintf(file_prt, "%u,%f,%f\n", t, x[t], y[t]);
            if(0 < ret) {
                ok++;
            }
        }
        fclose(file_prt);
        if(ok == size) {
            res = true;

        } else {
            res = false;
        }
    } else {
        LOG_ERROR(CSV, "File [%s] OpenErr", file_name);
    }
    return res;
}
#endif

// out_size
bool csv_parse_last_text(const char* const in_text, char separator, char* const out_text, uint32_t out_size) {
    bool res = false;
    if(in_text) {
        LOG_DEBUG(CSV, "In[%s]", in_text);
        uint32_t cnt = csv_cnt(in_text, separator);
        if(cnt) {
            LOG_DEBUG(CSV, "Cnt:%u", cnt);
            res = csv_parse_text(in_text, separator, cnt - 1, out_text, out_size);
        }
    }
    return res;
}
