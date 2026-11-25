#include "can_tx_planner_diag.h"

#include "array_diag.h"
#include "can_tx_planner_mcal.h"
#include "common_diag.h"
#include "can_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* CanTxPlannerConfigToStr(const CanTxPlannerConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sEn:%u,", text, Config->on);
        snprintf(text, sizeof(text), "%sTxPeriod:%u Ms,", text, Config->tx_period_ms);
        snprintf(text, sizeof(text), "%sTxMesg:%s,", text, CanMessageToStr(&Config->TxMessage));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}


const char* CanTxPlannerNodeToStr(const CanTxPlannerHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool can_tx_planner_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {
        {4, "N"},
        {7, "TxCnt"},
        {9, "TxPeSMs"},
        {9, "TxPeRMs"},
        {5, "En"},
        {5, "CAN"},
        {12, "ID"},
        {4, "DLC"},
        {5, "idT"},
        {5, "Fra"},
        {18, "Data"},
        {9, "spin"},
        {8, "name"},
        {8, "TxTim"},
        {10, "TxNextMs"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = can_tx_planner_get_cnt();

    for(num = 0; num <= cnt; num++) {
        CanTxPlannerHandle_t* Node = CanTxPlannerGetNode(num);
        if(Node) {
            char temp[400] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, num);
            snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, Node->tx_cnt);
            snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, Node->tx_period_ms);
            snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, Node->tx_period_real_ms);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, Node->on);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, Node->TxMessage.can_bus_num);
            snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, Node->TxMessage.identifier.extended);
            snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, Node->TxMessage.size);
            snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanIdTypeToStr(Node->TxMessage.id_type));
            snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanFrameTypeToStr(Node->TxMessage.frame_type));
            snprintf(temp, sizeof(temp), "%s %16s " TSEP, temp, ArrayToStr(Node->TxMessage.data, Node->TxMessage.size));
            snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, Node->spin);
            snprintf(temp, sizeof(temp), "%s %4s " TSEP, temp, Node->name);
            snprintf(temp, sizeof(temp), "%s %6u " TSEP, temp, Node->TxMessage.time_stamp);
            snprintf(temp, sizeof(temp), "%s %8u " TSEP, temp, Node->tx_next_ms);

            cli_printf("%s" CRLF, temp);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool can_tx_planner_diag_one(uint8_t can_num) {
    bool res = false;
    static const table_col_t cols[] = {
        {7, "N"},
        {7, "TxCnt"},
        {9, "TxPeSMs"},
        {5, "CAN"},
        {12, "ID"},
        {4, "DLC"},
        {5, "idT"},
        {5, "Fra"},
        {18, "Data"},
        {10, "TxTim"},
        {10, "TxNextMs"},
        {5, "En"},
        {9, "TxPeRMs"},
       // {9, "spin"},
        {8, "name"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = can_tx_planner_get_cnt();
    uint32_t cells= can_tx_planner_get_cells();
    uint8_t num = 0;
    for(num = 0; num <= cnt; num++) {
        CanTxPlannerHandle_t* Node = CanTxPlannerGetNode(num);
        if(Node) {
            if(can_num == Node->TxMessage.can_bus_num) {
                char temp[400] = {0};
                strcpy(temp, TSEP);
                snprintf(temp, sizeof(temp), "%s %2u/%2u " TSEP, temp, num,cells);
                snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, Node->tx_cnt);
                snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, Node->tx_period_ms);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, Node->TxMessage.can_bus_num);
                snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, Node->TxMessage.identifier.extended);
                snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, Node->TxMessage.size);
                snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanIdTypeToStr(Node->TxMessage.id_type));
                snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanFrameTypeToStr(Node->TxMessage.frame_type));
                snprintf(temp, sizeof(temp), "%s %16s " TSEP, temp, ArrayToStr(Node->TxMessage.data, Node->TxMessage.size));
                snprintf(temp, sizeof(temp), "%s %8u " TSEP, temp, Node->TxMessage.time_stamp);
                snprintf(temp, sizeof(temp), "%s %8u " TSEP, temp, Node->tx_next_ms);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, Node->on);
                snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, Node->tx_period_real_ms);
                //snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, Node->spin);
                snprintf(temp, sizeof(temp), "%s %4s " TSEP, temp, Node->name);

                cli_printf("%s" CRLF, temp);
                res = true;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
