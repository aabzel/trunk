#include "spi_custom_diag.h"

#include "mcal_types.h"
#include "diag_inc.h"
#include "clock_diag.h"

const Reg32_t SpiRegs[]={

};

uint32_t spi_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(SpiRegs);
    return cnt;
}

const char* SpiInfoToStr(const SpiInfo_t* const Info) {
    memset(text, 0, sizeof(text));
    strcpy(text, "");
    if(Info) {
        sprintf(text, "SPI%u,", Info->num);
        snprintf(text, sizeof(text), "%sSPIx:0x%p,", text, Info->SPIx);
        snprintf(text, sizeof(text), "%seClock:%s,", text, ClockBusToStr(Info->clock_bus));
        snprintf(text, sizeof(text), "%sIrq:%d,", text, Info->irq_n);
        //snprintf(text, sizeof(text), "%sEnd:0x%p,", text, Info->TansferEndNotification);
        //snprintf(text, sizeof(text), "%sStart:0x%p,", text, Info->TansferStartNotification);
        //snprintf(text, sizeof(text), "%sInts:%u,", text, Info->e_instance);
        //snprintf(text, sizeof(text), "%sReg:0x%p,", text, Info->Regs);
#ifdef HAS_SPI_DMA
        snprintf(text, sizeof(text), "%seDmaTx:%u,", text, Info->dma_trigger_src_tx);
        snprintf(text, sizeof(text), "%seDmaRx:%u,", text, Info->dma_trigger_src_rx);
#endif
    }
    return text;
}
