#include "csv_diag.h"

#include <stdio.h>

#include "csv.h"
#include "log.h"
#include "shared_array.h"

const char* CsvState2Str(CsvState_t state) {
    const char* name = "?";
    switch((uint8_t)state) {
    case CSV_STATE_INIT:
        name = "Init";
        break;
    case CSV_STATE_ACCUMULATE:
        name = "Acc";
        break;
    case CSV_STATE_SEP:
        name = "LastSep";
        break;
    case CSV_STATE_END:
        name = "End";
        break;
    }
    return name;
}

const char* CsvInput2Str(CsvInput_t input) {
    const char* name = "?";
    switch((uint8_t)input) {
    case CSV_INPUT_NOT_SEP:
        name = "Letter";
        break;
    case CSV_INPUT_SEP:
        name = "Sep";
        break;
    case CSV_INPUT_END:
        name = "End";
        break;
    }
    return name;
}

const char* CsvNode2Str(CsvFsm_t* const Node) {
    sprintf(text, "%u:%u,%s,Proc:[%c],Input:%s,Pos:%u/%u,Need:%u,sep:[%c],StInx:%d,FetDone:%u", Node->abs_index,
            Node->i, CsvState2Str(Node->state), Node->symbol, CsvInput2Str(Node->input), Node->position, Node->cnt,
            Node->fetch_index, Node->separator, Node->start_value_index, Node->fetch_done);
    return text;
}

bool CsvNodeDiag(CsvFsm_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_DEBUG(CSV, "%s", CsvNode2Str(Node));
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
                switch((uint32_t)order) {
                case CSV_ORVER_REVERSE: {
                    res = csv_parse_text(in_text, separator, cnt - i - 1, name, sizeof(name));
                } break;
                case CSV_ORVER_FORWARD: {
                    res = csv_parse_text(in_text, separator, i, name, sizeof(name));
                } break;
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
