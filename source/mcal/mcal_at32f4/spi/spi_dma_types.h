//**************************************************************************************************
// @Module  I2S DMA Driver
//! \file   i2s_dma_types.h
//! \brief  AT32F43x platform dependent code
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 21.08.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef I2S_DMA_DRV_TYPES_H
#define I2S_DMA_DRV_TYPES_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "general.h"
#include "dma_drv_const.h"

//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! Values of control DMA channel multiplexers for I2S
typedef struct
{
    //! Number of I2S node
    U8 num;
    //! DMA channel multiplexer value for reception
    U8 rxDmaMux;
    //! DMA channel multiplexer value for sending data
    U8 txDmaMux;
    //! Flag that the data is correct
    U8 valid;
} I2S_DMA_INFO;

//! DMA ISR HANDLER
typedef U8 (*I2S_DMA_ISR_HANDLER)(void);

//! EHAL I2S DMA COMMON VARIABLES
#define I2S_DMA_COMMON_VARIABLES     \
    DMA_PAD         Dma;                  \
    I2S_DMA_ISR_HANDLER CallBackTxHalf;   \
    I2S_DMA_ISR_HANDLER CallBackTxDone;   \
    I2S_DMA_ISR_HANDLER CallBackRxHalf;   \
    I2S_DMA_ISR_HANDLER CallBackRxDone;

//! EHAL I2S DMA RX ISR VARIABLES
#define I2S_DMA_RX_ISR_VARIABLES \
    volatile U8  rxHalf;              \
    volatile U8  rxDone;              \
    volatile U32 rxHalfCnt;           \
    volatile U32 rxDoneCnt;

//! EHAL I2S DMA TX ISR VARIABLES
#define I2S_DMA_TX_ISR_VARIABLES \
    volatile U8  txHalf;              \
    volatile U8  txDone;              \
    volatile U32 txHalfCnt;           \
    volatile U32 txDoneCnt;


//! EHAL I2S DMA ISR VARIABLES
#define I2S_DMA_ISR_VARIABLES \
    I2S_DMA_RX_ISR_VARIABLES  \
    I2S_DMA_TX_ISR_VARIABLES


#endif // #ifndef I2S_DMA_DRV_TYPES_H
//******************************** end of file *****************************************************
