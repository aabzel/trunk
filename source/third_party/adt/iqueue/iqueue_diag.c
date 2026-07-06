#include "iqueue_diag.h"

#include "iqueue.h"
#include "interfaces_diag.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"
#include "storage_diag.h"

const char* iQueueStatusToStr(const i_status ret) {
    char *name = "?";
    switch (ret) {
    case I_OK:
        name = "Ok";
        break;
    case I_INVALID:
        name = "INVALID";
        break;
    case I_EXISTS:
        name = "I_EXISTS";
        break;
    case I_NOTEXISTS:
        name = "I_NOTEXISTS";
        break;
    case I_FAILED:
        name = "I_FAILED";
        break;
    case I_EXPIRED:
        name = "I_EXPIRED";
        break;
    case I_UNKNOWN:
        name = "I_UNKNOWN";
        break;
    case I_INPROGRESS:
        name = "I_INPROGRESS";
        break;
    case I_IDLE:
        name = "I_IDLE";
        break;
    case I_FULL:
        name = "I_FULL";
        break;
    case I_EMPTY:
        name = "I_EMPTY";
        break;
    case I_YES:
        name = "I_YES";
        break;
    case I_NO:
        name = "I_NO";
        break;
    case I_SKIP:
        name = "I_SKIP";
        break;
    case I_MEMUNALIGNED:
        name = "I_MEMUNALIGNED";
        break;
    case I_NOTIMPLEMENTED:
        name = "I_NOTIMPLEMENTED";
        break;
    case I_ERROR:
        name = "I_ERROR";
        break;
    case I_DEBUG_01:
        name = "I_DEBUG_01";
        break;
    case I_DEBUG_02:
        name = "Debug2";
        break;
    case I_DEBUG_03:
        name = "Debug3";
        break;
    case I_DEBUG_04:
        name = "Debug4";
        break;
    case I_DEBUG_05:
        name = "Debug5";
        break;
    case I_DEBUG_06:
        name = "Debug6";
        break;
    case I_DEBUG_07:
        name = "Debug7";
        break;
    case I_DEBUG_08:
        name = "Debug8";
        break;
    case I_DEBUG_09:
        name = "Debug9";
        break;
    case I_DEBUG_10:
        name = "Debug10";
        break;
    case I_DEBUG_11:
        name = "Debug11";
        break;
    case I_DEBUG_12:
        name = "Debug12";
        break;
    case I_DEBUG_13:
        name = "Debug13";
        break;
    case I_DEBUG_14:
        name = "Debug14";
        break;
    case I_DEBUG_15:
        name = "Debug15";
        break;
    case I_DEBUG_16:
        name = "Debug16";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* iQueueConfigToStr(const iQueueConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%spHandle:0x%p,", text, Config->pHandle);
        snprintf(text, sizeof(text), "%sMem:0x%p,", text, Config->storage);
        snprintf(text, sizeof(text), "%sCnt:%u,", text, Config->element_cnt);
        snprintf(text, sizeof(text), "%sElSz:%u Byte,", text, Config->element_size);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sIF:%s,", text, InterfaceTypeToStrShort(Config->Interface));
#if 0
        snprintf(text, sizeof(text), "%s Storage:%s,", text, StorageTypeToStr(Config->type));
#endif
    }
    return text;
}


const char* iQueueHandleToStr(const iqueue_t* const pHandle) {
    static char lText[200]={0};
    if(pHandle) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sMem:0x%x,", lText, pHandle->storage);
        snprintf(lText, sizeof(lText), "%sMaxElements:%u,", lText, pHandle->max_elements);
        snprintf(lText, sizeof(lText), "%sElmtSize:%u,", lText, pHandle->element_size);
        snprintf(lText, sizeof(lText), "%sFirst:%u,", lText, pHandle->first);
        snprintf(lText, sizeof(lText), "%sNext:%u,", lText, pHandle->next);
    }
    return text;
}

const char* iQueueNodeToStr(const iQueueHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sHandle:%s,", text, iQueueHandleToStr(Node->pHandle));
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool iqueue_diag(void) {
    bool res = false;
    const table_col_t cols[] = {
            { 5, "Num" },
            { 9, "Type" },
            { 8, "cnt" },
            { 6, "ElSZ" },
            { 11, "Name" },
            { 12, "Next" },
            { 5, "ret" },
            { 5, "ret" },
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t i = 0;
    uint32_t cnt = iqueue_get_cnt();
    for (i = 0; i <= cnt; i++) {
        iQueueHandle_t* Node = iQueueGetNode(i) ;
        if(Node) {
            size_t queue_cnt = 0;
            i_status ret = iqueue_size(Node->pHandle, &queue_cnt);
            void* nextPrt = iqueue_get_next_enqueue(Node->pHandle);

            char temp[200] = { 0 };
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, i);
#if 0
            snprintf(temp, sizeof(temp), "%s %7s " TSEP, temp, StorageTypeToStr(Node->type));
#endif
            snprintf(temp, sizeof(temp), "%s %6u " TSEP, temp, queue_cnt);
            snprintf(temp, sizeof(temp), "%s %4u " TSEP, temp, Node->element_size);
            snprintf(temp, sizeof(temp), "%s %9s " TSEP, temp, Node->name);
            snprintf(temp, sizeof(temp), "%s 0x%08p " TSEP, temp, nextPrt);
            snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, iQueueStatusToStr(ret));
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, ret);

            cli_printf("%s" CRLF, temp);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
