#include "power_isr.h"

#include "gpio_mcal.h"
#include "power_custom_drv.h"
#include "power_mcal.h"
#include "microcontroller_const.h"

bool PowerIRQHandler(uint8_t num) {
    bool res = false;
    PowerHandle_t* Node = PowerGetNode(num);
    if(Node) {
        flag_status ret = 0;
        Node->it_cnt++;
        Node->it_done = true;

        // power or i2s receive data buffer full flag

        ret = power_i2s_interrupt_flag_get(Node->POWERx, POWER_I2S_RDBF_FLAG);
        if(SET == ret) {
            power_i2s_flag_clear(Node->POWERx, POWER_I2S_RDBF_FLAG);
            //gpio_toggle(Node->GpioRxDebug.byte);
            Node->rx_buff_full = true;
            Node->rx_buff_full_cnt++;
            Node->rx_byte_cnt++;
            uint16_t word = power_i2s_data_receive(Node->POWERx);
            if(0xFF!=word) {
                res = false; // ??
            }
            Node->Rx.data[Node->Rx.cnt] = (PowerWordType_t)word;
            Node->Rx.cnt++;
            if(Node->Rx.cnt < Node->Rx.size) {
                power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_RDBF_INT, TRUE);
            } else {
                power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_RDBF_INT, false);
                Node->rx_done_cnt++;
                Node->rx_done = true;
                Node->state = power_state_transition(  Node->state, POWER_INPUT_RX_DONE);
                if(POWER_STATE_IDLE==Node->state) {
                    power_enable(Node->POWERx, false);
                }
            }
        }

        // power or i2s transmit data buffer empty flag
        ret = power_i2s_interrupt_flag_get(Node->POWERx, POWER_I2S_TDBE_FLAG);
        if(SET == ret) {
            power_i2s_flag_clear(Node->POWERx, POWER_I2S_TDBE_FLAG);
            Node->tx_buff_empty = true;
            Node->tx_buff_empty_cnt++;
            Node->tx_byte_cnt++;
            if(Node->Tx.data) {
                if(Node->Tx.cnt < Node->Tx.size) {
                    power_i2s_data_transmit(Node->POWERx, (uint16_t)Node->Tx.data[Node->Tx.cnt]);
                } else {
                    power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_TDBE_INT, false);
                    Node->tx_done = true;
                    Node->tx_done_cnt++;
                    Node->state= power_state_transition(  Node->state, POWER_INPUT_TX_DONE);
                    if(POWER_STATE_IDLE==Node->state){
                        power_enable(Node->POWERx, false);
                    }
                }
            } else {
                power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_TDBE_INT, false);
            }
            Node->Tx.cnt++;
        }

        // power crc calculation error flag
        ret = power_i2s_interrupt_flag_get(Node->POWERx, POWER_CCERR_FLAG);
        if(SET == ret) {
            Node->crc_err_cnt++;
            power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_ERROR_INT, false); // error interrupt
            // power_enable(Node->POWERx, false);
        }

        // i2s transmitter underload error flag
        ret = power_i2s_interrupt_flag_get(Node->POWERx, I2S_TUERR_FLAG);
        if(SET == ret) {
            Node->error_cnt++;
            // error interrupt
            power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_ERROR_INT, false);
            // power_enable(Node->POWERx, false);
        }

        // power or i2s receiver overflow error flag
        ret = power_i2s_interrupt_flag_get(Node->POWERx, POWER_I2S_ROERR_FLAG);
        if(SET == ret) {
            Node->error_cnt++;
            // error interrupt
            power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_ERROR_INT, false);
            // power_enable(Node->POWERx, false);
        }

        // power or i2s busy flag
        ret = power_i2s_interrupt_flag_get(Node->POWERx, POWER_I2S_BF_FLAG);
        if(SET == ret) {
            Node->error_cnt++;
            // error interrupt
            power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_ERROR_INT, false);
            // power_enable(Node->POWERx, false);
        }

        // i2s audio channel state flag
        ret = power_i2s_interrupt_flag_get(Node->POWERx, I2S_ACS_FLAG);
        if(SET == ret) {
            Node->audio_ch_cnt++;
            // error interrupt
            power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_ERROR_INT, false);
            ////power_enable(Node->POWERx, false);
        }

        // power master mode error flag
        ret = power_i2s_interrupt_flag_get(Node->POWERx, POWER_MMERR_FLAG);
        if(SET == ret) {
            Node->error_cnt++;
            // error interrupt
            power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_ERROR_INT, false);
            // power_enable(Node->POWERx, false);
        }

        // power cs pulse abnormal setting flag
        ret = power_i2s_interrupt_flag_get(Node->POWERx, POWER_CSPAS_FLAG);
        if(SET == ret) {
            Node->error_cnt++;
            // error interrupt
            power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_ERROR_INT, false);
            // power_enable(Node->POWERx, false);
        }

        res = true;
    }
    return res;
}
