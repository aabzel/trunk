#include "nrf_cores_drv.h"

#include <stdint.h>

#include "nrfx_config_standalone.h"
#include "nrf_reset.h"
#include "log.h"

bool nrf_core_network_set_state(bool status){
    if(status){
        LOG_INFO(CORE, "NetworkOn");
        nrf_reset_network_force_off(NRF_RESET, false);
    }else{
        LOG_INFO(CORE, "NetworkOff");
        nrf_reset_network_force_off(NRF_RESET, true);
    }
    return true;
}

bool nrf_cores_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(CORE, "Init");
#endif
    res = nrf_core_network_set_state(true);
  
    return res;
}
 
 
