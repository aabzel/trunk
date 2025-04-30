#include "i2s_isr.h"

#include <string.h>

#include "gpio_mcal.h"
#include "i2s_drv.h"
#include "i2s_types.h"
#include "led_config.h"
#include "utils_math.h"

/*That ISR is called for every N words where N is an argument of nrfx_i2s_start function
  if Fs= 50kHz ISR called with 25kHz T =2e-5s =2e-5e1e-1=20us Frame period 20us
  Toggle signal is 14.09kHz
  ISR freq is about 25kHz T=40us
  1 ISR every N frame(qwords)
  1 ISR every N/2 sample*/
static bool i2s_it_busy = false;

uint32_t it_busy_cnt = 0;

void NrfxI2s0DataHandler(nrfx_i2s_buffers_t const* p_released, uint32_t status) {
    if(false == i2s_it_busy) {
        i2s_it_busy = true;
        I2sHandle_t* Node = I2sGetNode(0);
        nrfx_err_t ret = 0;
        if(Node) {
#ifdef HAS_LED_MONO
            // led_mono_blink(Node->debug_led1_num);
#endif
            Node->it_cnt++;
            Node->tx_int = true;
            Node->tx_sample_cnt += Node->frames / 2;

            if(Node->stop_needed) {
                nrfx_i2s_stop();
                Node->total_stop_cnt++;
                Node->in_progress = false;
            }

            if(p_released) {
#if 0
                if(p_released->p_tx_buffer) {
                    Node->tx_cnt++;
                }

                if(p_released->p_rx_buffer) {
                    Node->rx_cnt++;
                }
#endif /*comment*/
            }
        }

        if(NRFX_I2S_STATUS_NEXT_BUFFERS_NEEDED == (NRFX_I2S_STATUS_NEXT_BUFFERS_NEEDED & status)) {
            Node->rx_tx_done = true;
            if(Node->switch_needed) {
                Node->prev_tx_track = toggle_val(Node->cur_tx_track);
                ret = nrfx_i2s_next_buffers_set((nrfx_i2s_buffers_t const*)&(Node->i2s_buffers[Node->cur_tx_track]));
                Node->cur_tx_track = toggle_val(Node->cur_tx_track);
                if(NRFX_SUCCESS != ret) {
                    Node->Err.rx_next++;
                    Node->Err.tx_next++;
                } else {
#ifdef HAS_LED_MONO
                    // led_mono_blink(Node->debug_led2_num);
#endif
                    Node->next = false;
                    Node->toggle_cnt++;
                    Node->need_new_data = true;
                }
#ifdef HAS_MEMCPY
                uint32_t i = 0;
                for(i = 0; i < Node->frames; i++) {
                    Node->TxBuffer[Node->cur_tx_track][i] = Node->RxBuffer[Node->cur_tx_track][i];
                }
                // memcpy(&Node->TxBuffer[Node->cur_tx_track][0],&Node->RxBuffer[Node->cur_tx_track][0],Node->frames*4);
#endif
            }
        }
        if(NRFX_I2S_STATUS_TRANSFER_STOPPED == (NRFX_I2S_STATUS_TRANSFER_STOPPED & status)) {
            Node->status_stop_cnt++;
            Node->in_progress = false;
        }
        i2s_it_busy = false;
    } else {
        it_busy_cnt++;
    }
}
