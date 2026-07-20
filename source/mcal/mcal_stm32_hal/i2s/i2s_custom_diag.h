#ifndef I2S_STM_DIAG_H
#define I2S_STM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "i2s_types.h"
#include "stm32fx_hal.h"
#include "mcal_types.h"

extern const Reg32_t I2sRegs[];

const char* I2sOddToStr(uint8_t code);
const char* I2sBitToStr(uint8_t code);
const char* I2sRoleToStr(uint8_t code);
const char* SerialModeToStr(uint8_t code);
const char* I2sStdToStr(uint8_t code);
const char* I2sChlenToStr(uint8_t code);
const char* HalI2sStateToStr(HAL_I2S_StateTypeDef state);
const char* I2s_I2SMOD_ToStr(Stm32I2sMode_t i2smsel) ;
const char* I2s_I2SSTD_ToStr(Stm32I2sStd_t standart);
const char* I2s_PCMSYNC_ToStr(I2sPcmFrameSynchronization_t pcm_frame_sync);

uint8_t I2s_DATLEN_ToNum(const Stm32I2sDatLen_t dat_len) ;
bool I2sDiagReg_DR(const uint32_t reg_val);
bool I2sDiagReg_SR(const uint32_t reg_val);
bool I2sDiagReg_CR2(const uint32_t reg_val);
bool I2sDiagReg_I2SPR(const uint32_t reg_val);
bool I2sDiagReg_I2SCFGR(const uint32_t reg_val);
bool i2s_diag_low_level(const uint8_t num);
bool i2s_custom_diag_low_level(void);
bool i2s_custom_diag(void);
bool i2s_custom_diag_sample(void);
bool i2s_raw_reg_diag(uint8_t num);

uint32_t i2s_reg_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* I2S_STM_DIAG_H */
