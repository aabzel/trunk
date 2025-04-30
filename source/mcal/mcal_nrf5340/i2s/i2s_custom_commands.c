#include "i2s_custom_commands.h"

#include "convert.h"
#include "i2s_drv.h"

#ifdef HAS_I2S_ISR
#include "i2s_isr.h"
#endif

#include "i2s_types.h"
#include "log.h"

bool i2s_nrf_echo_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t i2s_num = 0;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum [1-%u]", I2S_COUNT);
        }
    }
    I2sHandle_t* I2sNode = I2sGetNode(i2s_num);
    if(I2sNode) {
        I2sNode->cur_tx_track = 1;
        I2sNode->cur_rx_track = 0;

        memset((void*)&I2sNode->TxBuffer[0][0], 0x55, I2S_BUFFER_SIZE * 4);
        memset((void*)&I2sNode->TxBuffer[1][0], 0x55, I2S_BUFFER_SIZE * 4);
        memset((void*)&I2sNode->RxBuffer[0][0], 0x8F, I2S_BUFFER_SIZE * 4);
        memset((void*)&I2sNode->RxBuffer[1][0], 0x8F, I2S_BUFFER_SIZE * 4);
        I2sNode->i2s_buffers[0].p_rx_buffer = (uint32_t*)&I2sNode->RxBuffer[0][0];
        I2sNode->i2s_buffers[0].p_tx_buffer = (uint32_t*)&I2sNode->RxBuffer[1][0];

        I2sNode->i2s_buffers[1].p_rx_buffer = (uint32_t*)&I2sNode->RxBuffer[1][0];
        I2sNode->i2s_buffers[1].p_tx_buffer = (uint32_t*)&I2sNode->RxBuffer[0][0];
        res = i2s_api_start(i2s_num, I2S_BUFFER_SIZE);
    }
    return res;
}

bool i2s_nrf_diag_command(int32_t argc, char* argv[]) {
    uint8_t i2s_num = 0;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum");
        }
    }
    if(res) {
#ifdef HAS_I2S_ISR
        LOG_INFO(I2S, "NrfxI2sHandler 0x%p", NrfxI2s0DataHandler);
#endif /*HAS_I2S_ISR*/
        I2sHandle_t* I2sNode = I2sGetNode(i2s_num);
        if(I2sNode) {
#ifdef HAS_I2S_ISR
            LOG_INFO(I2S, "ItBusyCnt: %u", it_busy_cnt);
#endif /*HAS_I2S_ISR*/

#ifdef HAS_NORTOS
            LOG_INFO(I2S, "I2S0_IRQHandler: 0x%p", I2S0_IRQHandler);
#endif /*HAS_NORTOS*/
            uint8_t i = 0;
            for(i = 0; i < I2S_ARRAY_CNT; i++) {
                LOG_INFO(I2S, "TxBuffer[%u]: 0x%p", i, I2sNode->i2s_buffers[i].p_tx_buffer);
                LOG_INFO(I2S, "RxBuffer[%u]: 0x%p", i, I2sNode->i2s_buffers[i].p_rx_buffer);
            }
            res = true;
        }
    }
    return res;
}
