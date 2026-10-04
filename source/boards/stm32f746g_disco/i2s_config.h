#ifndef I2S_CONFIG_H
#define I2S_CONFIG_H

#include "i2s_types.h"
#include "sys_config.h"

#ifdef HAS_RELEASE
#ifndef HAS_I2S1
#error "+ HAS_I2S1"
#endif /*HAS_I2S1*/
#ifndef HAS_I2S2
#error "+ HAS_I2S2"
#endif /*HAS_I2S2*/
#ifndef HAS_I2S4
#error "+ HAS_I2S4"
#endif /*HAS_I2S4*/
#endif /*HAS_RELEASE*/

#ifndef HAS_I2S
#error "+ HAS_I2S"
#endif

#ifdef HAS_BC127
#define I2S_BC127 1
#endif

#ifdef HAS_WM8731
#define I2S_WM8731 2
#endif

#ifdef HAS_FDA801
#define I2S_FDA801 4
#endif

extern const I2sConfig_t I2sConfigLuT[];
/*TODO: Move I2sConfig to Stack*/
extern I2sConfig_t I2sConfig[]; /*For Mux config between NorFlash Or FlashFs*/
extern I2sHandle_t I2sInstance[];

uint32_t i2s_get_cnt(void);

#endif /* I2S_CONFIG_H  */
