#include "csv_diag.h"

#include <stdio.h>

#include "csv.h"
#include "diag_inc.h"
#include "log.h"
#include "shared_array.h"

const char* CsvInputToStr(const CsvInput_t input) {
    const char* name = "?";
    switch(input) {
        case CSV_INPUT_NOT_SEP:        name = "Letter";        break;
        case CSV_INPUT_SEP:        name = "Sep";        break;
        case CSV_INPUT_END:        name = "End";        break;
        default:        name = "?";        break;
    }
    return name;
}

const char* CsvStateToStr(const CsvState_t state) {
    const char* name = "?";
    switch(state) {
        case CSV_STATE_INIT:        name = "Init";        break;
        case CSV_STATE_ACCUMULATE:        name = "Acc";        break;
        case CSV_STATE_SEP:        name = "LastSep";        break;
        case CSV_STATE_END:        name = "End";        break;
        default:        name = "?";        break;
    }
    return name;
}


const char* CsvNodeToStr(const CsvFsm_t* const Node) {
    if(Node) {
        strcpy(text, "Proc:");
        snprintf(text, sizeof(text), "%sSep:[%c],", text, Node->separator);
        snprintf(text, sizeof(text), "%sT[%u]=", text, Node->i);
        snprintf(text, sizeof(text), "%s%c,", text, Node->symbol);
        snprintf(text, sizeof(text), "%sST:%s,", text, CsvStateToStr(Node->state));
        snprintf(text, sizeof(text), "%sIN:%s,", text, CsvInputToStr(Node->input));
        snprintf(text, sizeof(text), "%sOutBuff:%p,", text, Node->out_buff);
        snprintf(text, sizeof(text), "%sStInx:%d,", text, Node->start_value_index);
        snprintf(text, sizeof(text), "%sNeed:%d,", text, Node->fetch_index);
        snprintf(text, sizeof(text), "%sPos:%u,", text, Node->position);
        snprintf(text, sizeof(text), "%sAbs:%u,", text, Node->abs_index);
        snprintf(text, sizeof(text), "%s/%u,", text, Node->cnt);
        snprintf(text, sizeof(text), "%sOutSZ:%u,", text, Node->out_size);
        snprintf(text, sizeof(text), "%sFetDone:%u,", text, Node->fetch_done);
    }
    return text;
}

bool CsvNodeDiag(CsvFsm_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_DEBUG(CSV, "%s", CsvNodeToStr(Node));
        res = true;
    }
    return res;
}

bool csv_print(char* const in_text, char separator, Order_t order) {
    bool res = false;
    uint32_t i = 0;
    if(in_text) {
        uint32_t cnt = csv_cnt(in_text, separator);
        if(cnt) {
            cli_printf("Cnt:%u", cnt);
            res = true;
            for(i = 0; i < cnt; i++) {
                char name[100] = {0};
                switch(order) {
                case CSV_ORVER_REVERSE: {
                    res = csv_parse_text(in_text, separator, cnt - i - 1, name, sizeof(name));
                } break;
                case CSV_ORVER_FORWARD: {
                    res = csv_parse_text(in_text, separator, i, name, sizeof(name));
                } break;
                default:
                    res = false;
                    break;
                } // switch

                if(res) {
                    if(0 == i) {
                        cli_printf("%s", name);
                    } else {
                        cli_printf(",%s", name);
                    }
                }
            }
            cli_printf(CRLF);
        }
    }
    return res;
}
