#include "memory_manager_diagnostic.h"

#include <stdio.h>
#include <string.h>

#include "memory_manager.h"
#include "hal_diag.h"
#include "log.h"
#include "memory_manager_types.h"
#include "table_utils.h"
#include "writer_config.h"

#define MEMORY_MANAGER_BANK_INFO_ONE(NUM)                        \
        {                                                        \
         .baseAddress = MEMMAN_BANK_##NUM##_BASE_ADDRESS,        \
         .deviceNumber = MEMMAN_BANK_##NUM##_DEVICE_NUMBER,      \
         .permissions = MEMMAN_BANK_##NUM##_PERMISSIONS,         \
         .size = MEMMAN_BANK_##NUM##_SIZE,                       \
         .valid= TRUE,                                           \
        },

#define MEMORY_MANAGER_BANK_INFO_ALL                    \
    MEMORY_MANAGER_BANK_INFO_ONE(0)                     \
    MEMORY_MANAGER_BANK_INFO_ONE(1)                     \
    MEMORY_MANAGER_BANK_INFO_ONE(2)                     \
    MEMORY_MANAGER_BANK_INFO_ONE(3)                     \
    MEMORY_MANAGER_BANK_INFO_ONE(4)                     \
    MEMORY_MANAGER_BANK_INFO_ONE(5)                     \
    MEMORY_MANAGER_BANK_INFO_ONE(6)                     \
    MEMORY_MANAGER_BANK_INFO_ONE(7)                     \
    MEMORY_MANAGER_BANK_INFO_ONE(8)                     \
    MEMORY_MANAGER_BANK_INFO_ONE(9)                     \
    MEMORY_MANAGER_BANK_INFO_ONE(10)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(11)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(12)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(13)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(14)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(15)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(16)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(17)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(18)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(19)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(20)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(21)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(22)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(23)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(24)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(25)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(26)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(27)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(28)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(29)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(30)                    \
    MEMORY_MANAGER_BANK_INFO_ONE(31)

static const MEMORY_MANAGER_BANK_INFO MEMORY_MANAGER_BANK_Info[]={
    MEMORY_MANAGER_BANK_INFO_ALL
};

const MEMORY_MANAGER_BANK_INFO* MEMORY_MANAGER_GetBankInfo(U8 deviceNumber) {
    U8 b = 0;
    MEMORY_MANAGER_BANK_INFO* Info = NULL;
    U8 cnt = ARRAY_SIZE(MEMORY_MANAGER_BANK_Info);
    for(b=0; b<cnt; b++) {
        if(TRUE == MEMORY_MANAGER_BANK_Info[b].valid) {
            if(deviceNumber == MEMORY_MANAGER_BANK_Info[b].deviceNumber) {
                Info = &MEMORY_MANAGER_BANK_Info[b];
                break;
            }
        }
    }
    return Info;
}

const char* MemManPermissionsToStr(U8 permissions){
    static char text[5]= {0};
    MEMORY_MANAGER_PERMISSIONS Permission;
    Permission.byte = permissions;
    strcpy(text, "");

    if(Permission.read) {
        snprintf(text, sizeof(text), "%sR", text);
    }
    if(Permission.write) {
        snprintf(text, sizeof(text), "%sW", text);
    }
    if(Permission.erase) {
        snprintf(text, sizeof(text), "%sE", text);
    }
    return text;
}

STD_RESULT MEMORY_MANAGER_BankDiag(void){
    STD_RESULT ret = RESULT_NOT_OK;
    U8 cnt = ARRAY_SIZE(MEMORY_MANAGER_BANK_Info);
    LOG_INFO(MEMORY_MANAGER,"BankCnt:%u", cnt);
    static const table_col_t cols[] = {
        {5, "N"},
        {5, "devN"},
        {12, "BaseAddr"},
        {8, "Size"},
        {5, "Perm"},
        {5, "Perm"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t b = 0;
    char text[120] = {0};
    for(b = 0; b < cnt; b++) {
            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %3u " TSEP, text, b);
            snprintf(text, sizeof(text), "%s %3u " TSEP, text, MEMORY_MANAGER_BANK_Info[b].deviceNumber);
            snprintf(text, sizeof(text), "%s 0x%08x " TSEP, text, MEMORY_MANAGER_BANK_Info[b].baseAddress);
            snprintf(text, sizeof(text), "%s %6u " TSEP, text, MEMORY_MANAGER_BANK_Info[b].size);
            snprintf(text, sizeof(text), "%s %3u " TSEP, text, MEMORY_MANAGER_BANK_Info[b].permissions);
            snprintf(text, sizeof(text), "%s %3s " TSEP, text, MemManPermissionsToStr(MEMORY_MANAGER_BANK_Info[b].permissions));
            cli_printf("%s" CRLF, text);
            ret = RESULT_OK;
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return ret;
}


STD_RESULT MEMORY_MANAGER_Diag(U8 memoryBankCnt) {
    STD_RESULT ret = RESULT_OK;
    // Returns the last job result
    LOG_INFO(MEMORY_MANAGER,"BankCnt:%u", MEMMAN_MEMORY_BANKS_QTY);
    U8 JobResult = MEMMAN_GetJobResult( );
    LOG_INFO(MEMORY_MANAGER,"JobResult:%u=%s", JobResult, EhalRestToStr(JobResult));

    // Returns memory status mask of the specified memory bank
    U32 memoryStatus = 0;
    U8 memoryBank = 0;
    for(memoryBank = 0; memoryBank < memoryBankCnt; memoryBank++) {
        memoryStatus = MEMMAN_GetMemoryStatus(memoryBank);
        LOG_INFO(MEMORY_MANAGER,"Bank:%u,memoryStatus:%u=%s", memoryBank, memoryStatus, EhalRestToStr(memoryStatus));
    }

    return ret;
}
