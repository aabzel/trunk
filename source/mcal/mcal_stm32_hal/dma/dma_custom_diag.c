#include "dma_custom_diag.h"

#include "dma_mcal.h"
#include "dma_const.h"
#include "dma_custom_const.h"
#include "log.h"

const char* DmaHalStateToStr(const HAL_DMA_StateTypeDef state ){
    char* name = "?";
    switch(state) {
        case HAL_DMA_STATE_RESET:  name = "RESET"; break;
        case HAL_DMA_STATE_READY:  name = "READY"; break;
        case HAL_DMA_STATE_BUSY:   name = "BUSY";break;
        case HAL_DMA_STATE_TIMEOUT:name = "TIMEOUT"; break;
        case HAL_DMA_STATE_ERROR:  name = "ERROR"; break;
        case HAL_DMA_STATE_ABORT:  name = "ABORT"; break;
        default:name = "?"; break;
    }
    return name;
}

bool dma_custom_diag_one(uint8_t num) {
    bool res = false ;
    DmaHandle_t* Node = DmaGetNode(num);
    if(Node) {
#ifdef HAS_DMA_ROOT
        HAL_DMA_StateTypeDef state = HAL_DMA_GetState(&Node->dma_h);
        uint32_t cnt=__HAL_DMA_GET_COUNTER(&Node->dma_h);
        LOG_INFO(LG_DMA,"State:%u=%s",state,DmaHalStateToStr(state));
        LOG_INFO(LG_DMA,"CNT:%u",cnt);
#endif
        res = true;
    }
    return res;
}

bool dma_diag_low_level_diag(char* keyWord1, char* keyWord2){
    bool res = false;
    return res;
}

bool dma_custom_diag(void) {
    bool res = false;
    uint32_t cnt = dma_get_cnt();
    LOG_INFO(LG_DMA,"DMA:%u",cnt);
    static const table_col_t cols[] = {
            {6, "DMA"},
            {12, "Addr"},
            {10, "remaining"},
            {12, "ErrorCode"},
            {3, "St"},
            {9, "State"},
            {9, "fillLvl"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t i = 0;
    for(i = 0; i <= cnt; i++) {
        DmaHandle_t* Node = DmaGetNode(i);
        if(Node) {
            char log_line[120] = {0};
#ifdef HAS_DMA_ROOT
            HAL_DMA_StateTypeDef state = HAL_DMA_GetState(&Node->dma_h);
            uint32_t error_code = HAL_DMA_GetError(&Node->dma_h);
            uint32_t filled_level = __HAL_DMA_GET_FS(&Node->dma_h);
            uint32_t remaining = __HAL_DMA_GET_COUNTER(&Node->dma_h);
#endif
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s DMA%u " TSEP, log_line, Node->num);
            snprintf(log_line, sizeof(log_line), "%s 0x%08x " TSEP, log_line, Node->DMAx);
#ifdef HAS_DMA_ROOT
            snprintf(log_line, sizeof(log_line), "%s %8u " TSEP, log_line, remaining);
            snprintf(log_line, sizeof(log_line), "%s 0x%08x " TSEP, log_line, error_code);
            snprintf(log_line, sizeof(log_line), "%s %1u " TSEP, log_line, state);
            snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, DmaHalStateToStr(state));
            snprintf(log_line, sizeof(log_line), "%s %7u " TSEP, log_line, filled_level);
#endif

            cli_printf("%s" CRLF, log_line);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}


