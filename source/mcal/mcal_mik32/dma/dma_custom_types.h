#ifndef DMA_CUSTOM_TYPES_H
#define DMA_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dma_custom_const.h"
#include "mik32_hal.h"
#include "dma_const.h"

#define DMA_CUSTOM_TYPES           \
    DMA_TypeDef* DMAx;             \
    DMA_HandleTypeDef dma_h;

typedef struct {
    uint8_t feif :1;/*stream x FIFO error interrupt flag*/
    uint8_t dmeif :1;/*stream x direct mode error interrupt flag*/
    uint8_t teif  :1;/*stream x transfer error interrupt flag*/
    uint8_t htif  :1;/*stream x half transfer interrupt flag*/
    uint8_t tcif  :1;/*stream x transfer complete interrupt flag*/
}DmaStreamIntStatusReg_t;

#define DMA_STREAM_INT_STATUS_REG(NUM)                                \
       uint32_t feif##NUM  :1;/*stream x FIFO error interrupt flag*/   \
       uint32_t res##NUM   :1;                                         \
       uint32_t dmeif##NUM :1;/*stream x direct mode error interrupt flag*/ \
       uint32_t teif##NUM  :1;/*stream x transfer error interrupt flag*/ \
       uint32_t htif##NUM  :1;/*stream x half transfer interrupt flag*/ \
       uint32_t tcif##NUM  :1;/*stream x transfer complete interrupt flag*/


typedef union {
    uint32_t reg_val;
    struct{
        DMA_STREAM_INT_STATUS_REG(0)
        DMA_STREAM_INT_STATUS_REG(1)
        uint32_t res4 :4;
        DMA_STREAM_INT_STATUS_REG(2)
        DMA_STREAM_INT_STATUS_REG(3)
        uint32_t res5 :4;
    };
}DmaLowIntStatusReg_t;


typedef union {
    uint32_t reg_val;
    struct{
        DMA_STREAM_INT_STATUS_REG(4)
        DMA_STREAM_INT_STATUS_REG(5)
        uint32_t res8 :4;
        DMA_STREAM_INT_STATUS_REG(6)
        DMA_STREAM_INT_STATUS_REG(7)
        uint32_t res9 :4;
    };
}DmaHighIntStatusReg_t;


#define DMA_STREAM_INT_CLEAR_STATUS_REG(NUM)     \
       uint32_t cfeif##NUM  :1;/*stream x clear FIFO error interrupt flag*/ \
       uint32_t res##NUM   :1; /**/ \
       uint32_t cdmeif##NUM :1;/*stream x clear direct mode error interrupt flag*/ \
       uint32_t cteif##NUM  :1;/*Stream x clear transfer error interrupt flag*/ \
       uint32_t chtif##NUM  :1;/*stream x clear half transfer interrupt flag*/ \
       uint32_t ctcif##NUM  :1;/*stream x clear transfer complete interrupt flag*/


typedef struct {
       uint8_t cfeif  :1;/*stream x clear FIFO error interrupt flag*/
       uint8_t cdmeif :1;/*stream x clear direct mode error interrupt flag*/
       uint8_t cteif  :1;/*Stream x clear transfer error interrupt flag*/
       uint8_t chtif  :1;/*stream x clear half transfer interrupt flag*/
       uint8_t ctcif  :1;/*stream x clear transfer complete interrupt flag*/
}DmaStreamClearIntReg_t;

typedef union {
    uint32_t reg_val;
    struct{
        DMA_STREAM_INT_CLEAR_STATUS_REG(0)
        DMA_STREAM_INT_CLEAR_STATUS_REG(1)
        uint32_t res4 :4;
        DMA_STREAM_INT_CLEAR_STATUS_REG(2)
        DMA_STREAM_INT_CLEAR_STATUS_REG(3)
        uint32_t res5 :4;
    };
}DmaLowIntFlagClearReg_t;

typedef union {
    uint32_t reg_val;
    struct{
        DMA_STREAM_INT_CLEAR_STATUS_REG(4)
        DMA_STREAM_INT_CLEAR_STATUS_REG(5)
        uint32_t res8 :4;
        DMA_STREAM_INT_CLEAR_STATUS_REG(6)
        DMA_STREAM_INT_CLEAR_STATUS_REG(7)
        uint32_t res9 :4;
    };
}DmaHighIntFlagClearReg_t;


typedef union {
    uint32_t reg_val;
    struct{
        uint32_t en:1;/*stream enable*/
        uint32_t dmeie   :1; /*direct mode error interrupt enable*/
        uint32_t teie    :1; /*transfer error interrupt enable*/
        uint32_t htie    :1; /*half transfer interrupt enable*/
        uint32_t tcie    :1; /*transfer complete interrupt enable*/
        uint32_t pfctrl  :1; /*peripheral flow controller*/
        uint32_t dir     :2; /*data transfer direction*/
        uint32_t circ    :1; /*circular mode*/
        uint32_t pinc    :1; /*peripheral increment mode*/
        uint32_t minc    :1; /*memory increment mode*/
        uint32_t psize   :2; /*peripheral data size*/
        uint32_t msize   :2; /*memory data size*/
        uint32_t pincos  :1; /*peripheral increment offset size*/
        uint32_t pl      :2; /*priority level*/
        uint32_t dbm     :1; /*double-buffer mode*/
        uint32_t ct      :1; /*current target (only in double-buffer mode)*/
        uint32_t res1    :1; /*res*/
        uint32_t pburst  :2; /*peripheral burst transfer configuration*/
        uint32_t mburst  :2; /*memory burst transfer configuration*/
        uint32_t chsel   :4; /*channel selection*/
        uint32_t res2    :3; /*res*/
    };
}DmaStreamConfReg_t;

typedef struct {
    uint8_t dma_num; /*DMA num*/
    volatile DMA_TypeDef* DMAx;
    bool valid;
} DmaInfo_t;


typedef struct {
    DMA_Stream_TypeDef* DMA_STREAMx;
    DmaChannel_t channel;
    uint8_t dma_num;
    bool valid;
    IRQn_Type irq_n;
} DmaChannelInfo_t;



#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_TYPES_H  */
