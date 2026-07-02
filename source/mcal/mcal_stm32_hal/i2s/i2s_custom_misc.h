#ifndef I2S_CUSTOM_MISC_H
#define I2S_CUSTOM_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2s_types.h"

int8_t get_i2s_index(SPI_TypeDef* I2Sx) ;
uint8_t I2sSampleBitness2bytes(Stm32I2sDatLen_t code) ;
uint32_t I2sBus2Code(ClockBus_t CurBus) ;
uint32_t I2sParseFullDuplexMode(I2sFullDuplex_t full_duplex) ;
uint32_t I2sParseDataFormat(I2sDataFormat_t data_format) ;
uint32_t I2sParseCPol(I2sCpol_t cpol) ;
uint32_t I2sParseClockSource(I2sClockSource_t clock_source) ;
uint32_t I2sParseAudioFreq(AudioFreq_t audio_freq) ;
uint32_t I2sDirRoleToMode(I2sDirAndBusRole_t mode);
uint32_t I2sParseMCLKOutput(const I2sMclkOut_t mclk_out) ;
uint32_t I2sParseStandard(I2sStandard_t standard) ;
uint32_t I2sSampleRate2Hz(AudioFreq_t code) ;
SPI_TypeDef* I2sGetBaseAddr(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* I2S_CUSTOM_MISC_H */
