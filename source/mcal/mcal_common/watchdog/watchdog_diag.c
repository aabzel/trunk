#include "watchdog_diag.h"

#include <stdio.h>
#include <string.h>

#include "shared_array.h"
#include "float_diag.h"

const char* WatchDogConfigToStr( const WatchDogConfig_t* const Config){
    if(Config){
        memset(text,0,SHARED_ARRAY_SIZE);
        snprintf(text,sizeof(text),"%sEN:%u,", text,Config->on);
        snprintf(text,sizeof(text),"%s%u Bit,", text,Config->bitness);
        snprintf(text,sizeof(text),"%sBaseFreq:%u Hz,", text,Config->base_freq_hz);
       // snprintf(text,sizeof(text),"%sBase:0x%08x,", text,Config->base_address);
        snprintf(text,sizeof(text),"%sTimeOut:%s s", text, FloatToStr(Config->timeout_s,1));
    }
    return text;
}

