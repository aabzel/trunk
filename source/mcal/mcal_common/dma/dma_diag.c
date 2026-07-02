#include "dma_diag.h"

#include <stdio.h>
#include <string.h>

#include "dma_mcal.h"
#include "dma_config.h"
#include "table_utils.h"
#include "writer_config.h"
#include "data_utils.h"

#ifdef HAS_DMA_CUSTOM
#include "dma_custom_const.h"
#endif

const char* DmaDirToStr(DmaDir_t dir) {
    const char* name = "?";

    switch(dir) {
        case DMA_MCAL_DIR_PERIPH_TO_MEMORY:        name = "Per->Mem";        break;
        case DMA_MCAL_DIR_MEMORY_TO_PERIPH:        name = "Mem->Per";        break;
        case DMA_MCAL_DIR_MEMORY_TO_MEMORY:        name = "Mem->Mem";        break;
        default:   name = "?";          break;
    }
    return name;
}

const char* DmaModeToStr(DmaMode_t mode) {
    const char* name = "?";
    switch( mode) {
    case DMA_MODE_NORMAL:        name = "Norm";        break;
    case DMA_MODE_CIRCULAR:        name = "Circ";        break;
    default:        break;
    }
    return name;
}

uint8_t DmaDataSizeToBits(const DmaAligmant_t code) {
    uint8_t bit_num = 0;
    switch(code) {
    case DMA_ALIGNMENT_BYTE:        bit_num = 8;        break;
    case DMA_ALIGNMENT_WORD:        bit_num = 16;        break;
    case DMA_ALIGNMENT_DWORD:        bit_num = 32;        break;
    default:        break;
    }
    return bit_num;
}

const char* DmaIncrToStr(DmaInc_t code) {
    const char* name = "?";

    switch(code) {
    case DMA_INC_OFF:
        name = "Off";
        break;
    case DMA_INC_ON:
        name = "On";
        break;
    default:
        break;
    }
    return name;
}

const char* DmaPriorityToStr(DmaPriority_t code) {
    const char* name = "?";

    switch( code) {
    case DMA_PRIOR_LOW:        name = "Low";        break;
    case DMA_PRIOR_MED:        name = "Med";        break;
    case DMA_PRIOR_HIGH:        name = "Hi";        break;
    case DMA_PRIOR_VERY_HIGH:        name = "VerHi";        break;
    default:        break;
    }
    return name;
}

const char* DmaConfigToStr(const DmaConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sDMA:%u,", text, Config->dma_num);
    }
    return text;
}


bool dma_diag(void) {
    bool res = false;
    // flag_status ret=RESET;
    uint32_t i = 0;
    uint32_t cnt = dma_get_cnt();
    static const table_col_t cols[] = {{5, "DMA"}, {12, "Addr"}};

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(i = 0; i <= cnt; i++) {
        DmaHandle_t* Node = DmaGetNode(i);
        if(Node) {
            // ret=dmamux_generator_interrupt_flag_get(Node->DMAx, uint32_t flag);
            // ret=dmamux_generator_flag_get(Node->DMAx, uint32_t flag);
            // ret=dmamux_sync_interrupt_flag_get(Node->DMAx, uint32_t flag);
            // ret=dmamux_sync_flag_get(Node->DMAx, uint32_t flag);
            char log_line[120]={0};
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
#ifdef HAS_DMA_CUSTOM
            snprintf(log_line, sizeof(log_line), "%s 0x%08x " TSEP, log_line, Node->DMAx);
#endif
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    // ret = dma_flag_get(uint32_t dmax_flag);
    // ret = dma_interrupt_flag_get(uint32_t dmax_flag);
    return res;
}

