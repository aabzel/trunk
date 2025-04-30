#include "uwb_if.h"

#include "log.h"

#ifdef HAS_DWM1000_DRV
#include "dwm1000_drv.h"
#endif

#ifdef HAS_DWM3000
#include "dwm3000_drv.h"
#endif

#ifdef HAS_DECADRIVER
#include "decadriver.h"
#endif

bool uwb_send(const uint8_t* const buff, uint32_t size) {
    bool res = false;

#ifdef HAS_PC
    LOG_WARNING(UWB,"ImaginarySend");
    res = true;
#endif

#ifdef HAS_DECADRIVER
    res = decadriver_tx(buff, size);
    if(false==res){
        LOG_ERROR(UWB,"DecaSendErr");
    }
#endif

#ifdef HAS_DWM1000_DRV
    res = dwm1000_transmit(buff, size+2);
#endif

#ifdef HAS_DWM3000
    res = dwm3000_transmit(buff, size);
#endif

    if(res){

    }else{
        LOG_ERROR(UWB,"NoUWB_PHY");
    }
    return res;
}

bool uwb_is_vaild_distance(double distance_m) {
    bool res = false;
    if(distance_m < 300.0) {
        res = true;
    }
    if(distance_m<0.0) {
        LOG_DEBUG(UWB,"NegativeDist %6.2f m",distance_m);
    }
    return res;
}
