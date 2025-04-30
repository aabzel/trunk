
#include "board_monitor.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_I2S
#include "i2s_config.h"
#include "i2s_drv.h"
#endif

#ifdef HAS_BC127
#include "bc127_config.h"
#endif

bool board_check(void){
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
   return res;
}
