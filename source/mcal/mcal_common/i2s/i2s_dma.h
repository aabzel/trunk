#ifndef I2S_DMA_ISR_H
#define I2S_DMA_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2s_types.h"
#include "i2s_custom_isr.h"


/*tx*/
bool I2sDmaCallBackTxHalf(uint8_t num);
bool I2sDmaCallBackTxDone(uint8_t num);
bool I2sDmaTxHalfCallback(I2sHandle_t* const Node);
bool I2sDmaTxDoneCallback(I2sHandle_t* const Node) ;

/*Rx*/
bool I2sDmaCallBackRxHalf(uint8_t num);
bool I2sDmaCallBackRxDone(uint8_t num);
bool I2sDmaRxHalfCallback(I2sHandle_t* const Node);
bool I2sDmaRxDoneCallback(I2sHandle_t* const Node);

/*Err*/
bool I2sErrorCallback(I2sHandle_t* const Node) ;

/*RxTx*/
bool I2sDmaTxRxHalfCallback(I2sHandle_t* const Node);
bool I2sDmaTxRxDoneCallback(I2sHandle_t* const Node) ;


#ifdef HAS_I2S1
bool I2s1DmaCallBackTxHalf(void) ;
bool I2s1DmaCallBackTxDone(void) ;
bool I2s1DmaCallBackRxDone(void) ;
bool I2s1DmaCallBackRxHalf(void) ;
#endif

#ifdef HAS_I2S2
bool I2s2DmaCallBackTxHalf(void) ;
bool I2s2DmaCallBackTxDone(void) ;
bool I2s2DmaCallBackRxDone(void) ;
bool I2s2DmaCallBackRxHalf(void) ;
#endif

#ifdef HAS_I2S3
bool I2s3DmaCallBackTxHalf(void) ;
bool I2s3DmaCallBackTxDone(void) ;
bool I2s3DmaCallBackRxDone(void) ;
bool I2s3DmaCallBackRxHalf(void) ;
#endif

#ifdef HAS_I2S4
bool I2s4DmaCallBackTxHalf(void) ;
bool I2s4DmaCallBackTxDone(void) ;
bool I2s4DmaCallBackRxDone(void) ;
bool I2s4DmaCallBackRxHalf(void) ;
#endif


#ifdef HAS_I2S5
bool I2s5DmaCallBackTxHalf(void) ;
bool I2s5DmaCallBackTxDone(void) ;
bool I2s5DmaCallBackRxDone(void) ;
bool I2s5DmaCallBackRxHalf(void) ;
#endif

#ifdef HAS_I2S6
bool I2s6DmaCallBackTxHalf(void) ;
bool I2s6DmaCallBackTxDone(void) ;
bool I2s6DmaCallBackRxDone(void) ;
bool I2s6DmaCallBackRxHalf(void) ;
#endif

#ifdef __cplusplus
}
#endif

#endif /* I2S_DMA_ISR_H */
