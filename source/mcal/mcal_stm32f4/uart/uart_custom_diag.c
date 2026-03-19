#include "uart_custom_diag.h"

#include "array_diag.h"
#include "clock_diag.h"
#include "diag_inc.h"

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
#if 0
        snprintf(text, sizeof(text), "%sClockBus:%s,", text, ClockBusToStr(Info->clock_bus));
        snprintf(text, sizeof(text), "%sClkSrc:%s,", text, PCC_ClkSrcTypeToStr(Info->clk_src_type));
        snprintf(text, sizeof(text), "%sClkType:%u,", text, Info->clock_type);
        snprintf(text, sizeof(text), "%sinstance:%u,", text, Info->instance_type);
        snprintf(text, sizeof(text), "%sDmaSrcRx:%u,", text, Info->dma_trigger_src_rx);
        snprintf(text, sizeof(text), "%sDmaSrcTx:%u,", text, Info->dma_trigger_src_tx);
        snprintf(text, sizeof(text), "%sRxCallB:%p,", text, Info->RxCallBack);
        snprintf(text, sizeof(text), "%sTxEmpCallB:%p,", text, Info->TxEmptyCallBack);
        snprintf(text, sizeof(text), "%sTxDoneCallB:%p,", text, Info->TxCompleteCallBack);
        snprintf(text, sizeof(text), "%sErrCallB:%p,", text, Info->ErrorCallBack);
        snprintf(text, sizeof(text), "%sRxMesg:%s,", text, UartMesgToStr(&Info->RxMsg));
        snprintf(text, sizeof(text), "%sTxMesg:%s", text, UartMesgToStr(&Info->TxMsg));
#endif
    }
    return text;
}
