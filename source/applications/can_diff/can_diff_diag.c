#include "can_diff_diag.h"

#include "num_to_str.h"
#include "array_diag.h"
#include "can_diff_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"
#include "can_diag.h"

const char* CanDiffConfigToStr(const CanDiffConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sCAN%u,", text, Config->can_num);
        snprintf(text, sizeof(text), "%sID:0x%08x,", text, Config->can_id);
        snprintf(text, sizeof(text), "%s%s,", text, CanIdTypeToStr(Config->id_type));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* CanDiffNodeToStr(const CanDiffHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}


static bool can_diff_diag_line(const CanDiffHandle_t* const Node) {
    bool res = false;
    Type64Union_t data;
    memcpy(data.u8, Node->diffData, 8);
    char temp[400] = { 0 };
    strcpy(temp, TSEP);
    snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, Node->num);
    snprintf(temp, sizeof(temp), "%s CAN%u " TSEP, temp, Node->can_num);
    snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, Node->can_id);
    snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanIdTypeToStr(Node->id_type));
    snprintf(temp, sizeof(temp), "%s %16s " TSEP, temp, ArrayToStr(Node->diffData, CAN_MAX_PAYLOAD_SIZE));
    snprintf(temp, sizeof(temp), "%s %16s " TSEP, temp, ArrayToStr(Node->MessageCur.data, CAN_MAX_PAYLOAD_SIZE));
    snprintf(temp, sizeof(temp), "%s %16s " TSEP, temp, Node->name );
    cli_printf("%s" CRLF, temp);
    res = true;

    return res;
}


bool can_diff_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {
            { 5, "N" },
            { 6, "CAN" },
            { 12, "ID" },
            { 5, "idT" },
            { 18, "DataDiff" },
            { 18, "LastMesg" },
            { 18, "Name" },
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = can_diff_get_cnt();
    for (num = 0; num <= cnt; num++) {
        CanDiffHandle_t *Node = CanDiffGetNode(num);
        if (Node) {
            res = true;
            can_diff_diag_line(Node );
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}


bool can_diff_diag_one(uint8_t num) {
    bool res = false;
    static const table_col_t cols[] = {
            { 5, "N" },
            { 6, "CAN" },
            { 12, "ID" },
            { 5, "idT" },
            { 18, "DataDiff" },
            { 64, "DataDiff" },
            { 18, "Name" },
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        CanDiffHandle_t *Node = CanDiffGetNode(num);
        if (Node) {
            res = true;
            can_diff_diag_line(Node );
        }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
