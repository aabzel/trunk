#ifndef DMA_CHANNEL_GENERAL_TYPES_H
#define DMA_CHANNEL_GENERAL_TYPES_H

#include <stdint.h>


/*
 { .dma_num=dma_num,      .channel=channel, }
 */
typedef union {
    uint8_t byte;
    struct{
        uint8_t dma_num:2; // 0[1,2]..3
        uint8_t channel:6; // 0,[1...7]...63
    };
}DmaChannelPad_t;


#endif /* DMA_CHANNEL_GENERAL_TYPES_H */
