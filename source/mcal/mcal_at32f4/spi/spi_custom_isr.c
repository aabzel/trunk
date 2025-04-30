#include "spi_isr.h"

#include "gpio_mcal.h"
#include "microcontroller_const.h"
#include "spi_custom_drv.h"
#include "spi_mcal.h"

bool SpiIRQHandler(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        flag_status ret = 0;
        Node->it_cnt++;
        Node->it_done = true;

        // spi or i2s receive data buffer full flag

        ret = spi_i2s_interrupt_flag_get(Node->SPIx, SPI_I2S_RDBF_FLAG);
        if(SET == ret) {
            spi_i2s_flag_clear(Node->SPIx, SPI_I2S_RDBF_FLAG);
            // gpio_toggle(Node->GpioRxDebug.byte);
            Node->rx_buff_full = true;
            Node->rx_buff_full_cnt++;
            Node->rx_byte_cnt++;
            uint16_t word = spi_i2s_data_receive(Node->SPIx);
            if(0xFF != word) {
                res = false; // ??
            }
            Node->Rx.data[Node->Rx.cnt] = (SpiWordType_t)word;
            Node->Rx.cnt++;
            if(Node->Rx.cnt < Node->Rx.size) {
                spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_RDBF_INT, TRUE);
            } else {
                spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_RDBF_INT, false);
                Node->rx_done_cnt++;
                Node->rx_done = true;
                Node->state = spi_state_transition(Node->state, SPI_INPUT_RX_DONE);
                if(SPI_STATE_IDLE == Node->state) {
                    spi_enable(Node->SPIx, false);
                }
            }
        }

        // spi or i2s transmit data buffer empty flag
        ret = spi_i2s_interrupt_flag_get(Node->SPIx, SPI_I2S_TDBE_FLAG);
        if(SET == ret) {
            spi_i2s_flag_clear(Node->SPIx, SPI_I2S_TDBE_FLAG);
            Node->tx_buff_empty = true;
            Node->tx_buff_empty_cnt++;
            Node->tx_byte_cnt++;
            if(Node->Tx.data) {
                if(Node->Tx.cnt < Node->Tx.size) {
                    spi_i2s_data_transmit(Node->SPIx, (uint16_t)Node->Tx.data[Node->Tx.cnt]);
                } else {
                    spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_TDBE_INT, false);
                    Node->tx_done = true;
                    Node->tx_done_cnt++;
                    Node->state = spi_state_transition(Node->state, SPI_INPUT_TX_DONE);
                    if(SPI_STATE_IDLE == Node->state) {
                        spi_enable(Node->SPIx, false);
                    }
                }
            } else {
                spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_TDBE_INT, false);
            }
            Node->Tx.cnt++;
        }

        // spi crc calculation error flag
        ret = spi_i2s_interrupt_flag_get(Node->SPIx, SPI_CCERR_FLAG);
        if(SET == ret) {
            Node->crc_err_cnt++;
            spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_ERROR_INT, false); // error interrupt
            // spi_enable(Node->SPIx, false);
        }

        // i2s transmitter underload error flag
        ret = spi_i2s_interrupt_flag_get(Node->SPIx, I2S_TUERR_FLAG);
        if(SET == ret) {
            Node->error_cnt++;
            // error interrupt
            spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_ERROR_INT, false);
            // spi_enable(Node->SPIx, false);
        }

        // spi or i2s receiver overflow error flag
        ret = spi_i2s_interrupt_flag_get(Node->SPIx, SPI_I2S_ROERR_FLAG);
        if(SET == ret) {
            Node->error_cnt++;
            // error interrupt
            spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_ERROR_INT, false);
            // spi_enable(Node->SPIx, false);
        }

        // spi or i2s busy flag
        ret = spi_i2s_interrupt_flag_get(Node->SPIx, SPI_I2S_BF_FLAG);
        if(SET == ret) {
            Node->error_cnt++;
            // error interrupt
            spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_ERROR_INT, false);
            // spi_enable(Node->SPIx, false);
        }

        // i2s audio channel state flag
        ret = spi_i2s_interrupt_flag_get(Node->SPIx, I2S_ACS_FLAG);
        if(SET == ret) {
            Node->audio_ch_cnt++;
            // error interrupt
            spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_ERROR_INT, false);
            ////spi_enable(Node->SPIx, false);
        }

        // spi master mode error flag
        ret = spi_i2s_interrupt_flag_get(Node->SPIx, SPI_MMERR_FLAG);
        if(SET == ret) {
            Node->error_cnt++;
            // error interrupt
            spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_ERROR_INT, false);
            // spi_enable(Node->SPIx, false);
        }

        // spi cs pulse abnormal setting flag
        ret = spi_i2s_interrupt_flag_get(Node->SPIx, SPI_CSPAS_FLAG);
        if(SET == ret) {
            Node->error_cnt++;
            // error interrupt
            spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_ERROR_INT, false);
            // spi_enable(Node->SPIx, false);
        }

        res = true;
    }
    return res;
}
