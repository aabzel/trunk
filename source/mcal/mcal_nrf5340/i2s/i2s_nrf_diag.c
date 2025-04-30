#include "i2s_diag.h"

#include <stdbool.h>

#include "i2s_nrf_drv.h"
#include "i2s_drv.h"
#include "i2s_types.h"

#ifdef HAS_I2S_ISR
#include "i2s_isr.h"
#endif

#include "log.h"


bool i2s_diag_one(uint8_t i2s_num) {
	bool res = false;
    I2sHandle_t* I2sNode = I2sGetNode(i2s_num);
    if(I2sNode) {
#ifdef HAS_NORTOS
        LOG_INFO(I2S, "I2S0_IRQHandler: 0x%p", I2S0_IRQHandler);
        LOG_INFO(I2S, "nrfx_i2s_irq_handler: 0x%p", nrfx_i2s_irq_handler);
#endif
        uint8_t i=0;
        for(i=0;i<2;i++){
            LOG_INFO(I2S, "TxBuff: 0x%p", I2sNode->i2s_buffers[i].p_tx_buffer);
            LOG_INFO(I2S, "RxBuff: 0x%p", I2sNode->i2s_buffers[i].p_rx_buffer);
        }
        LOG_INFO(I2S, "ItCnt: %u", I2sNode->it_cnt);
        LOG_INFO(I2S, "TxCnt: %u", I2sNode->tx_cnt);
        LOG_INFO(I2S, "RxCnt: %u", I2sNode->rx_cnt);
        res = true;
    }

    return res;
}
