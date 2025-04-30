#include "dma_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "dma_const.h"
#include "dma_custom_const.h"
#include "dma_custom_drv.h"
#include "dma_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "table_utils.h"
#include "writer_config.h"

bool dma_diag_custom(uint8_t num) {
    bool res = false;
    // flag_status ret=RESET;
    char log_line[120];
    uint32_t i = 0;
    uint32_t cnt = dma_get_cnt();
    static const table_col_t cols[] = {{5, "DMA"}, {5, "?"}, {10, "??"}};

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

const char* DmaReqSelToStr(uint8_t reqsel) {
    const char* name = "?";
    const DmaMuxInfo_t* MuxInfo = DmaMuxToInfo(reqsel);
    if(MuxInfo) {
        name = MuxInfo->name;
    }
    return name;
}

bool dma_channel_diag_custom(void) {
    bool res = false;

    uint16_t progress = 0;
    uint16_t channel = 0;
    uint16_t dma_num = 0;
    char log_line[120];
    static const table_col_t cols[] = {
        {5, "DMA"},    {5, "CHA"},    {10, "Tx"}, {5, "Mux"}, {12, "Mux"},
#ifdef HAS_AT32F43X
        {7, "EVTGEN"}, {7, "REQCNT"},
#endif // HAS_AT32F43X
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(dma_num = 0; dma_num <= 2; dma_num++) {
        for(channel = DMA_CHAN_0; channel < DMA_CHAN_15; channel++) {
            DmaChannelInfo_t* Info = DmaChannelGetInfo(dma_num, (DmaChannel_t)channel);
            if(Info) {

                uint8_t reqsel = 0;
                res = dma_mux_get(dma_num, channel, &reqsel);

                progress = dma_data_number_get(Info->dmax_channely);
                strcpy(log_line, TSEP);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Info->dma_num);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Info->channel);
                snprintf(log_line, sizeof(log_line), "%s %8u " TSEP, log_line, progress);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, reqsel);
                snprintf(log_line, sizeof(log_line), "%s %10s " TSEP, log_line, DmaReqSelToStr(reqsel));
#ifdef HAS_AT32F43X
                snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line,
                         Info->dmamux_channelx->muxctrl_bit.evtgen);
                snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line,
                         Info->dmamux_channelx->muxctrl_bit.reqcnt);
#endif // HAS_AT32F43X

                cli_printf("%s" CRLF, log_line);
                res = true;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
