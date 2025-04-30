
#include "board_monitor.h"

#include "log.h"

#ifdef HAS_I2S
#include "i2s_config.h"
#include "i2s_drv.h"
#endif

#ifdef HAS_BC127
#include "bc127_config.h"
#endif

#ifdef HAS_FDA801
#include "fda801_drv.h"
#endif

bool board_check(void) {
   bool res = true;
#if defined(HAS_I2S) && defined(HAS_BC127)
   const I2sConfig_t* I2sConfNode = I2sGetConfNode(I2S_BC127);
   if(I2sConfNode){
       if(BC127_I2SMODE_MASTER==Bc127Config.i2s_param.bus_mode){
           if(I2SMODE_MASTER_TX==I2sConfNode->mode || I2SMODE_MASTER_RX==I2sConfNode->mode ){
               res = false;
               LOG_ERROR(SYS,"BothMastersInI2S %u Bus",I2S_BC127);
           }
       }
   }
#endif

#if defined(HAS_I2S) && defined(HAS_FDA801)
   uint32_t i2s_sample_rate= i2s_get_sample_rate(I2S_FDA801);
   uint32_t fda801_sample_rate= fda801_get_sample_rate();
   if(fda801_sample_rate!=i2s_sample_rate){
       LOG_ERROR(SYS,"DiffSampleRate I2S %u Hz Fda801: %u Hz",i2s_sample_rate,fda801_sample_rate);
   }

#endif
   return res;
}
