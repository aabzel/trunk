#include "uart_custom_diag.h"

#include "array_diag.h"
#include "clock_diag.h"
#include "diag_inc.h"

#ifdef HAS_DMA_CHANNEL_DIAG
#include "dma_channel_diag.h"
#endif

const Reg32_t UartRegs[] = {
    {
        .name = "UART_?",
        .offset = 0x00,
        .access = ACCESS_UNDEF,
        .valid = true,
    },
};

uint32_t uart_reg_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(UartRegs);
    return cnt;
}

const char* UartInfoToStr(const UartInfo_t* const Info) {
    if(Info) {
        memset(text, 0, sizeof(text));
        sprintf(text, "UART%u,", Info->num);
        snprintf(text, sizeof(text), "%sBase:%s,", text, Info->UARTx);
        snprintf(text, sizeof(text), "%sIRQn:%u,", text, Info->irq_n);
        snprintf(text, sizeof(text), "%sClockBus:%s,", text, ClockBusToStr(Info->clock_bus));
#ifdef HAS_DMA_CHANNEL_DIAG
        snprintf(text, sizeof(text), "%sTx:%s,", text, DmaInfoPadToStr(&Info->DmaPadTx));
        snprintf(text, sizeof(text), "%sRx:%s,", text, DmaInfoPadToStr(&Info->DmaPadRx));
#endif
    }
    return text;
}
