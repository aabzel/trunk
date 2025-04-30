#include "i2s_custom_isr.h"

#include "gpio_mcal.h"
#include "i2s_mcal.h"
#include "microcontroller_const.h"

static size_t inc_index(size_t cur, size_t max, bool* const overflow) {
    cur++;
    if(cur < max) {
        // *overflow = false ;
    } else {
        cur = 0;
        *overflow = true;
    }
    return cur;
}

bool I2sIRQHandler(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        res = true;
        //  gpio_toggle(Node->PadDebug1.byte);

        flag_status ret = RESET;
        /* spi or i2s receive data buffer full flag */
        ret = spi_i2s_interrupt_flag_get(Node->I2Sx, SPI_I2S_RDBF_FLAG);
        if(SET == ret) {
            Node->rx_buff_full = true;
            Node->rx_buff_full_cnt++;
            if(Node->rec) {
                Node->Rx.cnt++;
                bool overflow = false;
                Node->Rx.index = inc_index(Node->Rx.index, Node->Rx.size, &overflow);
                Node->Rx.overflow += overflow;
                uint16_t word = spi_i2s_data_receive(Node->I2Sx);
                Node->Rx.array[Node->Rx.index] = (SampleType_t)word;
                spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_RDBF_INT, TRUE);
                if(overflow) {
                    if(I2S_STATE_IDLE == Node->state) {
                        Node->rec = false;
                    }
                }
            } else {
                spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_RDBF_INT, FALSE);
            }
        }

        /* i2s audio channel state flag */
        ret = spi_i2s_interrupt_flag_get(Node->I2Sx, I2S_ACS_FLAG);
        if(SET == ret) {
            spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_ERROR_INT, FALSE);
            spi_i2s_flag_clear(Node->I2Sx, I2S_ACS_FLAG);
        }

        /* spi or i2s busy flag */
        ret = spi_i2s_interrupt_flag_get(Node->I2Sx, SPI_I2S_BF_FLAG);
        if(SET == ret) {
            Node->busy = true;
            // spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_ERROR_INT, FALSE);
            spi_i2s_flag_clear(Node->I2Sx, SPI_I2S_BF_FLAG);
        }

        /* spi or i2s transmit data buffer empty flag */
        ret = spi_i2s_interrupt_flag_get(Node->I2Sx, SPI_I2S_TDBE_FLAG);
        if(SET == ret) {
            // gpio_toggle(Node->PadDebug2.byte);
            Node->tx_buff_empty = true; // 555
            Node->tx_buff_empty_cnt++;
            Node->Tx.cnt++;
            bool overflow = false;
            Node->Tx.index = inc_index(Node->Tx.index, Node->Tx.size, &overflow);
            Node->Tx.overflow += overflow;
            if(Node->Tx.array) {
                if(Node->play) {
                    spi_i2s_data_transmit(Node->I2Sx, Node->Tx.array[Node->Tx.index]);
                } else {
                    spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_TDBE_INT, FALSE);
                }
            } else {
                spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_TDBE_INT, FALSE);
            }
            spi_i2s_flag_clear(Node->I2Sx, SPI_I2S_TDBE_FLAG);
        }

        /* i2s transmitter underload error flag */
        ret = spi_i2s_interrupt_flag_get(Node->I2Sx, I2S_TUERR_FLAG);
        if(SET == ret) {
            Node->error_cnt++;
            res = false;
            spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_ERROR_INT, FALSE);
        }

        /* spi or i2s receiver overflow error flag */
        ret = spi_i2s_interrupt_flag_get(Node->I2Sx, SPI_I2S_ROERR_FLAG);
        if(SET == ret) {
            Node->error_cnt++;
            res = false;
            spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_ERROR_INT, FALSE);
        }
    }

    return res;
}
