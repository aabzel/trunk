#include "can_rx_hist_diag.h"

#include "can_rx_hist_mcal.h"
#include "can_diag.h"
#include "array_diag.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* CanRxHistConfigToStr(const CanRxHistConfig_t *const Config) {
    strcpy(text, "");
    if (Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sCAN%u,", text, Config->can_num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sHistSize:%u,", text, Config->rx_mesg_array_cnt);
        snprintf(text, sizeof(text), "%sMem:0x%p,", text, Config->RxMesgArray);
    }
    return text;
}

const char* CanRxHistNodeToStr(const CanRxHistHandle_t *const Node) {
    strcpy(text, "");
    if (Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

static bool can_rx_hist_diag_line(uint8_t num, uint32_t i, CanRxHistHandle_t *Node) {
    bool res = false;
    if (Node->RxMesgArray[i].rx_cnt) {
        char temp[400] = { 0 };
        strcpy(temp, TSEP);
        snprintf(temp, sizeof(temp), "%s %2u/%u " TSEP, temp, 1+i, Node->rx_mesg_array_cnt);
        snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, Node->RxMesgArray[i].rx_cnt);
        snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, Node->RxMesgArray[i].rx_period_ms);
        snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, Node->RxMesgArray[i].Message.can_bus_num);
        snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, Node->RxMesgArray[i].Message.identifier.extended);
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, Node->RxMesgArray[i].Message.size);
        snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanIdTypeToStr(Node->RxMesgArray[i].Message.id_type));
        snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanFrameTypeToStr(Node->RxMesgArray[i].Message.frame_type));
        snprintf(temp, sizeof(temp), "%s %16s " TSEP, temp,
                ArrayToStr(Node->RxMesgArray[i].Message.data, Node->RxMesgArray[i].Message.size));
        snprintf(temp, sizeof(temp), "%s %8u " TSEP, temp, Node->RxMesgArray[i].Message.time_stamp);
        cli_printf("%s" CRLF, temp);
        res = true;
    }
    return res;
}

bool can_rx_hist_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {
            { 7, "RxCnt" },            {8, "RxPeSMs" },            { 5, "CAN" },
            { 12, "ID" },            { 4,            "DLC" },            { 5, "idT" },
            { 5, "Fra" },            { 18, "Data" },            { 10, "RxTimeMs" },
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = can_rx_hist_get_cnt();

    for (num = 0; num <= cnt; num++) {
        CanRxHistHandle_t *Node = CanRxHistGetNode(num);
        if (Node) {
            res = true;
            uint32_t i = 0;
            uint32_t h_cnt = Node->rx_mesg_array_cnt;
            for (i = 0; i < h_cnt; i++) {
                can_rx_hist_diag_line(num,i, Node );
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool can_rx_hist_diag_one(uint8_t can_num) {
    bool res = false;

    static const table_col_t cols[] = {
            { 7, "N" },
            { 7, "RxCnt" },
            { 9, "RxPeSMs" },
            { 5, "CAN" },
            { 12, "ID" },
            { 4, "DLC" },
            { 5, "idT" },
            { 5, "Fra" },
            { 18, "Data" },
            { 10, "RxTimeMs" }, };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    CanRxHistHandle_t *Node = CanRxHistCanNumToNode(can_num);
    if (Node) {
        uint32_t i = 0;
        uint32_t h_cnt = Node->rx_mesg_array_cnt;
        for (i = 0; i < h_cnt; i++) {
            res = can_rx_hist_diag_line(can_num, i, Node) ;
        }
    }

   // table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
