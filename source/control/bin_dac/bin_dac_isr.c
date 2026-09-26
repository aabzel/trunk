#include "bin_dac_isr.h"

#include "bin_dac_mcal.h"
#include "bit_fifo_mcal.h"
#include "gpio_mcal.h"
#include "dma_channel_mcal.h"

bool bin_dac_tx_next_ll(BinDacHandle_t* const Node) {
    bool res = false;
    if(Node) {
        res = dma_channel_is_done(Node->DmaChPad) ;
        if(res) {
            res = false;
            int32_t count = bit_fifo_get_count(&Node->TxFifo);
            if(0 < count) {
                uint8_t bit_part[300] = { 0 };
                if(Node->part_size<=sizeof(bit_part)) {
                    uint32_t out_len = 0;
                    res = bit_fifo_pull_array(&Node->TxFifo, bit_part, Node->part_size, &out_len);
                    if(res) {
                        if(0 < out_len) {
                            res = bin_dac_sample_tx_ll(Node, bit_part, out_len);
                        }else{
                            res = false;
                        }
                    }else{
                        res = false;
                        Node->pull_error_cnt++;
                    }
                }else{
                    res = false;
                }
            }else{
                res = true;
            }
        } else {
            Node->busy_cnt++;
            res = true;
        }
    }
    return res;
}


bool bin_dac_tx_done(const uint8_t num) {
    bool res = false;
    BinDacHandle_t* Node = BinDacGetNode(num);
    if(Node) {
        Node->busy = false ;
        res = gpio_logic_level_set(Node->debugPad,GPIO_LVL_LOW);
        res = bin_dac_tx_next_ll(Node);
    }
    return res;
}
