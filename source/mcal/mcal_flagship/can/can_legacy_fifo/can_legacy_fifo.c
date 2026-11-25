#include "can_legacy_fifo.h"

#include "can_misc.h"

bool can_init_rx_fifo_legacy_default(FLEXCAN_InitType* const pInit) {
    bool res = true;
    pInit->tRxFifoFilterCfg.tLegacyFifoCfg.bEnFifoDMA = 0U;
    pInit->tRxFifoFilterCfg.tLegacyFifoCfg.bDataAvaliableInt = 0U;
    pInit->tRxFifoFilterCfg.tLegacyFifoCfg.bWarningInt = 0U;
    pInit->tRxFifoFilterCfg.tLegacyFifoCfg.bOverflowInt = 0U;
    pInit->tRxFifoFilterCfg.tLegacyFifoCfg.u8RxFilterFifoCnt = 0U;
    pInit->tRxFifoFilterCfg.tLegacyFifoCfg.pRxFilterFifoList = NULL;
    return res;
}

bool can_config_legacy_fifo_init(const CanConfig_t* const Config, FLEXCAN_InitType* const Init) {
    bool res = false;
    if(Config) {
        if(Init) {
            Init->tRxFifoFilterCfg.bEnFifo = CanMacModeToEnableFifo(Config->mac_mode);
            /* legacy fifo is only used in non-FD mode */
            Init->tRxFifoFilterCfg.eFifoType = CanMacModeToFifoType(Config->mac_mode);

            /* if enable can fifo dma, set 1U, only fifo support    */
            Init->tRxFifoFilterCfg.tLegacyFifoCfg.bEnFifoDMA = 0U;
            /* if at least one message in fifo interrupt, can trigger dma */
            Init->tRxFifoFilterCfg.tLegacyFifoCfg.bDataAvaliableInt = 1U; /* legacy fifo data interrupt */
            /* more than 5 messages in fifo and data lost interrupt */
            Init->tRxFifoFilterCfg.tLegacyFifoCfg.bOverflowInt = 1U; /* legacy fifo full interrupt */
            /* increase from 4 to 5 messages in fifo interrupt      */
            Init->tRxFifoFilterCfg.tLegacyFifoCfg.bWarningInt = 1U; /* enhanced fifo will be full interrupt */

            /* rx id filter count, in fifo                          */
            Init->tRxFifoFilterCfg.tLegacyFifoCfg.u8RxFilterFifoCnt = 0; /* rx id filter count, in fifo    */
            /* rx id list in fifo                                   */
            Init->tRxFifoFilterCfg.tLegacyFifoCfg.pRxFilterFifoList = NULL; /* rx id list in fifo */
            res = true;
        }
    }
    return res;
}

bool can_legacy_fifo_id_check(const uint8_t num, const uint32_t can_id) {
    bool res = false;
    return res;
}

bool can_is_mode_legacy_fifo(const uint8_t num) {
    bool res = false;
    return res;
}
