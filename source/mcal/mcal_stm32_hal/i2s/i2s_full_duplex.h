#ifndef I2S_FULL_DUPLEX_EXTENTION_H
#define I2S_FULL_DUPLEX_EXTENTION_H

#include "std_includes.h"

bool i2s_rx_dma_restart(uint8_t dma_node_num,
                        uint8_t i2s_num,
                        uint32_t DstAddress,
                        uint32_t DataLength ) ;

#endif /* I2S_FULL_DUPLEX_EXTENTION_H */
