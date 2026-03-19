#ifndef I2S_MCAL_DIAG_H
#define I2S_MCAL_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "i2s_types.h"
#include "i2s_custom_diag.h"

#ifndef HAS_I2S_DIAG
#error "+ HAS_I2S_DIAG"
#endif /*HAS_I2S_DIAG*/

#ifndef HAS_DIAG
#error "+ HAS_DIAG"
#endif /*HAS_DIAG*/


#ifdef HAS_I2S_VOLUME
const char* I2sState2Str(I2sState_t state);
#endif

const char* I2sFullDuplex2Str(FullDuplex_t full_duplex) ;
const char* I2sModeToStr(I2sMode_t mode) ;
const char* I2sClockSource2Str(I2sClockSource_t clock_source) ;
const char* I2sState2Str(I2sState_t state);
const char* I2sStandard2Str(Standard_t standard);
const char* I2sAudioFreq2Str(AudioFreq_t freq);
const char* I2sDftInfoToStr(const I2sHandle_t* const Node );
const char* I2sConfigToStr(const I2sConfig_t* const Config);
const char* I2sResolution2Str(I2sDataFormat_t code);
const char* I2sBusRole2Str(I2sDirRole_t code);
const char* I2sSampleMode2Str(SampleMode_t sample_mode) ;
const char* I2sFsmDiag2Str(const I2sHandle_t* const Node );

bool i2s_rec_reverse_byte_order(uint8_t num);
bool i2s_print_rx_ll(const I2sHandle_t* const Node );
bool i2s_print_rx(uint8_t num);
bool I2sDiagConfig(const I2sConfig_t* const Config  );
bool i2s_stream_diag(uint8_t num);
bool i2s_diag_all(void);
bool i2s_diag_one(uint8_t num);
bool i2s_diag_config(void);
bool i2s_diag_errors(void);
bool i2s_diag_rx(void);
bool i2s_diag_sample(void) ;
bool i2s_diag_tx(void);

#endif /* I2S_MCAL_DIAG_H */
