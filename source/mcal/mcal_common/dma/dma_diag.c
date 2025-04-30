#include "dma_diag.h"

#include <stdio.h>
#include <string.h>

#include "data_utils.h"
#include "dma_custom_const.h"
#include "dma_mcal.h"
#include "table_utils.h"
#include "writer_config.h"

const char* DmaDirToStr(DmaDir_t dir) {
    const char* name = "?";

    switch((uint8_t)dir) {
    case DMA_MCAL_DIR_PERIPH_TO_MEMORY:
        name = "Per->Mem";
        break;
    case DMA_MCAL_DIR_MEMORY_TO_PERIPH:
        name = "Mem->Per";
        break;
    case DMA_MCAL_DIR_MEMORY_TO_MEMORY:
        name = "Mem->Mem";
        break;
    default:
        break;
    }
    return name;
}

const char* DmaMode2Str(DmaMode_t mode) {
    const char* name = "?";
    switch((uint8_t)mode) {
    case DMA_MODE_NORMAL:
        name = "Norm";
        break;
    case DMA_MODE_CIRCULAR:
        name = "Circ";
        break;
    default:
        break;
    }
    return name;
}

uint8_t DmaDataSizeBits2Str(DmaAligmant_t code) {
    uint8_t bit_num = 0;

    switch((uint8_t)code) {
    case DMA_ALIG_BYTE:
        bit_num = 8;
        break;
    case DMA_ALIG_HALF_WORD:
        bit_num = 16;
        break;
    case DMA_ALIG_WORD:
        bit_num = 32;
        break;
    default:
        break;
    }
    return bit_num;
}

const char* DmaIncr2Str(DmaInc_t code) {
    const char* name = "?";

    switch((uint8_t)code) {
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

const char* DmaPriority2Str(DmaPriority_t code) {
    const char* name = "?";

    switch((uint8_t)code) {
    case DMA_PRIOR_LOW:
        name = "Low";
        break;
    case DMA_PRIOR_MED:
        name = "Med";
        break;
    case DMA_PRIOR_HIGH:
        name = "Hi";
        break;
    case DMA_PRIOR_VERY_HIGH:
        name = "VerHi";
        break;
    default:
        break;
    }
    return name;
}

const char* DmaConfigToStr(const DmaConfig_t* const Config) {
    static char text[250] = "";
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sDMA:%u,", text, Config->dma_num);
    }
    return text;
}

const char* DmaPadToStr(DmaPad_t DmaPad) {
    static char text[30] = "";
    strcpy(text, "");
    snprintf(text, sizeof(text), "%sDMA:%u,", text, DmaPad.dma_num);
    snprintf(text, sizeof(text), "%sCH:%u", text, DmaPad.channel);
    return text;
}

const char* DmaChannelConfigToStr(const DmaChannelConfig_t* const Config) {
    static char text[250] = "";
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sDMA:%u,", text, Config->dma_num);
        snprintf(text, sizeof(text), "%sCH:%u,", text, Config->channel);
        snprintf(text, sizeof(text), "%sMux:%u,", text, Config->mux);
        snprintf(text, sizeof(text), "%sCH:%u,", text, Config->channel);
        snprintf(text, sizeof(text), "%sPbase:0x%x,", text, Config->peripheral_base_addr);
        snprintf(text, sizeof(text), "%sMbase:0x%x,", text, Config->memory_base_addr);
        snprintf(text, sizeof(text), "%sDir:%s,", text, DmaDirToStr(Config->dir));
        snprintf(text, sizeof(text), "%sBuffSZ:%u,", text, Config->buffer_size);
        snprintf(text, sizeof(text), "%sMode:%s,", text, DmaMode2Str(Config->mode));
        snprintf(text, sizeof(text), "%sMemInc:%s,", text, DmaIncr2Str(Config->mem_inc));
        snprintf(text, sizeof(text), "%sPerInc:%s,", text, DmaIncr2Str(Config->per_inc));
        snprintf(text, sizeof(text), "%sMemAli:%u Bit,", text, DmaDataSizeBits2Str(Config->aligment_per));
        snprintf(text, sizeof(text), "%sPerAli:%u Bit,", text, DmaDataSizeBits2Str(Config->aligment_mem));
        snprintf(text, sizeof(text), "%sPri:%s,", text, DmaPriority2Str(Config->priority));
    }
    return text;
}

bool dma_diag(void) {
    bool res = false;
    // flag_status ret=RESET;
    char log_line[120];
    uint32_t i = 0;
    uint32_t cnt = dma_get_cnt();
    static const table_col_t cols[] = {{5, "DMA"}, {12, "Addr"}, {10, "?"}};

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(i = 0; i <= cnt; i++) {
        DmaHandle_t* Node = DmaGetNode(i);
        if(Node) {
            // ret=dmamux_generator_interrupt_flag_get(Node->DMAx, uint32_t flag);
            // ret=dmamux_generator_flag_get(Node->DMAx, uint32_t flag);
            // ret=dmamux_sync_interrupt_flag_get(Node->DMAx, uint32_t flag);
            // ret=dmamux_sync_flag_get(Node->DMAx, uint32_t flag);
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s 0x%08x " TSEP, log_line, Node->DMAx);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    // ret = dma_flag_get(uint32_t dmax_flag);
    // ret = dma_interrupt_flag_get(uint32_t dmax_flag);
    return res;
}

bool dma_channel_diag(void) {
    bool res = false;
    uint16_t channel = 0;
    char log_line[120];
    static const table_col_t cols[] = {
        {5, "DMA"},  {5, "CHA"},     {10, "Dir"}, {10, "TxHalf"}, {10, "TxDone"},
        {10, "Err"}, {10, "Global"}, {5, "init"}, {5, "Mux"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint16_t d = 0;
    for(d = 0; d <= 2; d++) {
        for(channel = DMA_CHAN_0; channel < DMA_CHAN_15; channel++) {
            DmaChannelHandle_t* Node = DmaChannelGetNodeItem(d, (DmaChannel_t)channel);
            if(Node) {
                strcpy(log_line, TSEP);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->dma_num);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->channel);
                snprintf(log_line, sizeof(log_line), "%s %8s " TSEP, log_line, DmaDirToStr(Node->dir));
                snprintf(log_line, sizeof(log_line), "%s %8u " TSEP, log_line, Node->half_cnt);
                snprintf(log_line, sizeof(log_line), "%s %8u " TSEP, log_line, Node->done_cnt);
                snprintf(log_line, sizeof(log_line), "%s %8u " TSEP, log_line, Node->error_cnt);
                snprintf(log_line, sizeof(log_line), "%s %8u " TSEP, log_line, Node->global_cnt);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->init);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->mux);
                cli_printf("%s" CRLF, log_line);
                res = true;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
