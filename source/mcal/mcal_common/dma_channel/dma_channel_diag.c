#include "dma_channel_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "dma_channel_mcal.h"
#include "dma_diag.h"
#include "microcontroller_const.h"
#include "table_utils.h"
#include "writer_config.h"

const char* DmaPadToStr(const DmaChannelPad_t DmaPad) {
    static char lText[20] = {0};
    strcpy(lText, "");
    snprintf(lText, sizeof(lText), "%sDMA%u_", lText, DmaPad.dma_num);
    snprintf(lText, sizeof(lText), "%sCH%u", lText, DmaPad.channel);
    return lText;
}

const char* DmaChannelConfigSrcToStr(const DmaChannelConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, DmaPadToStr(Config->DmaPad));
        snprintf(text, sizeof(text), "%s0x%08X->", text, Config->base_addr_source);
        // snprintf(text, sizeof(text), "%sAli:%u->", text, DmaDataSizeToBits(Config->aligment_source));
        // snprintf(text, sizeof(text), "%sInc:%s->", text, DmaIncrToStr(Config->inc_source));
        snprintf(text, sizeof(text), "%sDir:%s,", text, DmaDirToStr(Config->dir));
    }
    return text;
}

const char* DmaChannelConfigToStr(const DmaChannelConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, DmaPadToStr(Config->DmaPad));
        snprintf(text, sizeof(text), "%sMux:%u=", text, Config->mux);
        snprintf(text, sizeof(text), "%s%s,", text, DmaChannelMuxToStr(Config->mux));
        snprintf(text, sizeof(text), "%sAliPer:%u->", text, DmaDataSizeToBits(Config->aligment_per));
        snprintf(text, sizeof(text), "%sAliMem:%u Bit,", text, DmaDataSizeToBits(Config->aligment_mem));
        snprintf(text, sizeof(text), "%sIncMem:%s", text, DmaIncrToStr(Config->mem_inc));
        snprintf(text, sizeof(text), "%sIncPer:%s,", text, DmaIncrToStr(Config->per_inc));
        snprintf(text, sizeof(text), "%s0x%08X->", text, Config->base_addr_source);
        snprintf(text, sizeof(text), "%s0x%08X,", text, Config->base_addr_destination);
        snprintf(text, sizeof(text), "%sINT:%s,", text, OnOffToStr(Config->interrupt_on));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sDir:%s,", text, DmaDirToStr(Config->dir));
        snprintf(text, sizeof(text), "%sBlkSz:%u,", text, Config->block_size);
        snprintf(text, sizeof(text), "%sBlkCnt:%u,", text, Config->block_count);
        snprintf(text, sizeof(text), "%sMode:%s,", text, DmaModeToStr(Config->mode));
        snprintf(text, sizeof(text), "%sPri:%s,", text, DmaPriorityToStr(Config->priority));
    }
    return text;
}

const char* DmaChannelIsrInfo(const DmaChannelHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%s%s,", text, DmaPadToStr(Node->DmaPad));
        snprintf(text, sizeof(text), "%sMux:%u=", text, Node->mux);
        snprintf(text, sizeof(text), "%s%s,", text, DmaChannelMuxToStr(Node->mux));
        snprintf(text, sizeof(text), "%s%s,", text, Node->name);
    }
    return text;
}

const char* DmaChannelCtrlNodeToStr(const DmaChannelHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%s%s,", text, DmaPadToStr(Node->DmaPad));
        snprintf(text, sizeof(text), "%sMux:%u=", text, Node->mux);
        snprintf(text, sizeof(text), "%s%s,", text, DmaChannelMuxToStr(Node->mux));
        snprintf(text, sizeof(text), "%s0x%08X->", text, Node->base_addr_source);
        snprintf(text, sizeof(text), "%s0x%08X,", text, Node->base_addr_destination);
        snprintf(text, sizeof(text), "%sDir:%s,", text, DmaDirToStr(Node->dir));
        snprintf(text, sizeof(text), "%sBlkSZ:%u,", text, Node->block_size);
        snprintf(text, sizeof(text), "%sBlkCnt:%u,", text, Node->block_count);
        snprintf(text, sizeof(text), "%s%s,", text, Node->name);
    }
    return text;
}

const char* DmaChannelNodeToStr(const DmaChannelHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));

        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%s%s,", text, DmaPadToStr(Node->DmaPad));
        snprintf(text, sizeof(text), "%sMux:%u=", text, Node->mux);
        snprintf(text, sizeof(text), "%s%s,", text, DmaChannelMuxToStr(Node->mux));
        snprintf(text, sizeof(text), "%sAliMem:%u Bit", text, DmaDataSizeToBits(Node->aligment_per));
        snprintf(text, sizeof(text), "%sAliPer:%u Bit,", text, DmaDataSizeToBits(Node->aligment_mem));
        snprintf(text, sizeof(text), "%sIncPer:%s", text, DmaIncrToStr(Node->per_inc));
        snprintf(text, sizeof(text), "%sMemInc:%s,", text, DmaIncrToStr(Node->mem_inc));
        snprintf(text, sizeof(text), "%s0x%08X->", text, Node->base_addr_source);
        snprintf(text, sizeof(text), "%s0x%08X,", text, Node->base_addr_destination);
        snprintf(text, sizeof(text), "%sINT:%s,", text, OnOffToStr(Node->interrupt_on));
        snprintf(text, sizeof(text), "%s%s,", text, Node->name);
        snprintf(text, sizeof(text), "%sDir:%s,", text, DmaDirToStr(Node->dir));
        snprintf(text, sizeof(text), "%sBlkSZ:%u,", text, Node->block_size);
        snprintf(text, sizeof(text), "%sBlkCnt:%u,", text, Node->block_count);
        snprintf(text, sizeof(text), "%sMode:%s,", text, DmaModeToStr(Node->mode));
        snprintf(text, sizeof(text), "%sPri:%s,", text, DmaPriorityToStr(Node->priority));
    }
    return text;
}

const char* DmaChannelMuxToStr(uint8_t mux) {
    char* name = "";
    return name;
}

bool dma_channel_diag(void) {
    bool res = false;
    uint16_t channel = 0;
    static const table_col_t cols[] = {
        {5, "DMA"},  {5, "CH"},      {10, "Dir"}, {10, "TxHalf"}, {10, "TxDone"},
        {10, "Err"}, {10, "Global"}, {5, "init"}, {5, "Mux"},     {9, "Mux"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint16_t d = 0;
    for(d = 0; d <= 2; d++) {
        for(channel = DMA_CHANNEL_0; channel <= DMA_CHANNEL_COUNT; channel++) {
            DmaChannelPad_t DmaPad = {
                .dma_num = d,
                .channel = channel,
            };
            DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
            if(Node) {
                uint8_t mux = 0;
                res = dma_channel_mux_get(DmaPad, &mux);

                char log_line[120] = {0};
                strcpy(log_line, TSEP);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->DmaPad.dma_num);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->DmaPad.channel);
                snprintf(log_line, sizeof(log_line), "%s %8s " TSEP, log_line, DmaDirToStr(Node->dir));
                snprintf(log_line, sizeof(log_line), "%s %8u " TSEP, log_line, Node->half_cnt);
                snprintf(log_line, sizeof(log_line), "%s %8u " TSEP, log_line, Node->done_cnt);
                snprintf(log_line, sizeof(log_line), "%s %8u " TSEP, log_line, Node->error_cnt);
                snprintf(log_line, sizeof(log_line), "%s %8u " TSEP, log_line, Node->global_cnt);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->init);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, mux);
                snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, DmaChannelMuxToStr(mux));
                cli_printf("%s" CRLF, log_line);
                res = true;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
