#include "distance_diag.h"

#include <stdio.h>
#include <string.h>

#include "distance_drv.h"
#include "log.h"

const char* DistanceState2Str(DistanceState_t state){
    const char* name="?";
    switch((uint8_t)state) {
        case DISTANCE_STATE_UNKNOWN:{ name="Lost"; }break;
        case DISTANCE_STATE_KNOWN:{ name="Ok!";}break;
    }
    return name;
}

const char* DistanceInPut2Str(DistanceInput_t input){
    const char* name="?";
    switch((uint8_t)input){
        case DISTANCE_INPUT_TIME_OUT: name="TimeOut"; break;
        case DISTANCE_INPUT_NEW_MEASUREMENT: name="NewMeas";break;
        case DISTANCE_INPUT_NONE: name="None";break;
    }
    return name;
}

const char* DistanceNode2Str(const DistanceHandle_t* const Node){
    static char str[90] = "";
    //strcpy(str,"");
    memset(str,0,sizeof(str));
    snprintf(str, sizeof(str), "DW:%u,State:%s,Input:%s, TTL:%d ms,Dist:%lf m",
            Node->decawave_num,
            DistanceState2Str(Node->state),
            DistanceInPut2Str(Node->input),
            Node->ttl_ms,
			Node->distance_m/*Should be last due to format corruption  Dist:%lf m*/
            );
    return str;
}

bool distance_diag(uint8_t num){
    bool res = false;
    DistanceHandle_t* Node = DistanceGetNode(num);
    if (Node) {
        LOG_INFO(DISTANCE,"%s",DistanceNode2Str(Node));
        LOG_INFO(DISTANCE,"Dist:%f m",Node->distance_m);
        LOG_INFO(DISTANCE,"Dist:%d m",((int32_t)Node->distance_m));
        LOG_INFO(DISTANCE,"Dist:%d cm",((int32_t)(100.0*Node->distance_m)));
        res = true;
    }
    return res;
}
