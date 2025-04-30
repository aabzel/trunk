#include "distance_drv.h"

#include "decawave.h"
#include "distance_diag.h"
#include "log.h"
#include "param_drv.h"
#include "time_mcal.h"
#include "code_generator.h"


COMPONENT_GET_NODE(Distance, distance)
#if 0
DistanceHandle_t* DistanceGetNode(uint8_t num) {
    DistanceHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = distance_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == DistanceInstance[i].num) {
            if(DistanceInstance[i].valid) {
                Node = &DistanceInstance[i];
                break;
            }
        }
    }
    return Node;
}
#endif

COMPONENT_GET_CONFIG(Distance, distance)
#if 0
const DistanceConfig_t* DistanceGetConfig(uint8_t num) {
    const DistanceConfig_t* Config = NULL;
    uint32_t i = 0;
    uint32_t cnt = distance_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == DistanceConfig[i].num) {
            if(DistanceConfig[i].valid) {
                Config = &DistanceConfig[i];
                break;
            }
        }
    }
    return Config;
}
#endif

static bool distance_action_nop(DistanceHandle_t* const Node) {
    bool res = false;
    if(Node){
        LOG_DEBUG(DISTANCE, "Nop");
        Node->distance_m = 300.0;
    	res = true;
    }
    return res;
}

static bool distance_action_new_measurement(DistanceHandle_t* const Node) {
    bool res = false;
    if(Node) {
        DecaWaveHandle_t* DecaWaveNode = DecaWaveGetNode(Node->decawave_num);
        if(DecaWaveNode) {
            LOG_INFO(DISTANCE, "NewMeasure %f m!", DecaWaveNode->final.distance_real_m);
            Node->distance_m = DecaWaveNode->final.distance_real_m;
            res = true;
        }
    }
    return res;
}

static bool distance_action_lost_distance(DistanceHandle_t* const Node) {
    bool res = false;
    if(Node) {
        DecaWaveHandle_t* DecaWaveNode = DecaWaveGetNode(Node->decawave_num);
        if(DecaWaveNode) {
            Node->distance_m = DISTANCE_INFINITY_M;
            LOG_WARNING(DISTANCE, "LostDistance! LastDist: %f m, TimeOut:%u ms",
            		DecaWaveNode->final.distance_real_m, DISTANCE_NO_UPDATE_TIME_OUT_MS);
            DecaWaveNode->final.distance_real_m = DISTANCE_INFINITY_M;
            DecaWaveNode->final.valid = false;
            res = true;
        }
    }
    return res;
}

static bool distance_action_continuous_measurement(DistanceHandle_t* const Node) {
    bool res = false;
    if(Node) {
        DecaWaveHandle_t* DecaWaveNode = DecaWaveGetNode(Node->decawave_num);
        if(DecaWaveNode) {
            LOG_INFO(DISTANCE, "ConMeasure %f m", DecaWaveNode->final.distance_real_m);
            Node->distance_m = DecaWaveNode->final.distance_real_m;
            res = true;
        }
    }
    return res;
}

static const DistanceActionHandler_t ActionLookUpTable[2][2] = {
    [DISTANCE_STATE_UNKNOWN][DISTANCE_INPUT_TIME_OUT] = distance_action_nop,
    [DISTANCE_STATE_UNKNOWN][DISTANCE_INPUT_NEW_MEASUREMENT] = distance_action_new_measurement,
    [DISTANCE_STATE_KNOWN][DISTANCE_INPUT_TIME_OUT] = distance_action_lost_distance,
    [DISTANCE_STATE_KNOWN][DISTANCE_INPUT_NEW_MEASUREMENT] = distance_action_continuous_measurement,
};

static const DistanceState_t StateLookUpTable[2][2] = {
    [DISTANCE_STATE_UNKNOWN][DISTANCE_INPUT_TIME_OUT] = DISTANCE_STATE_UNKNOWN,
    [DISTANCE_STATE_UNKNOWN][DISTANCE_INPUT_NEW_MEASUREMENT] = DISTANCE_STATE_KNOWN,
    [DISTANCE_STATE_KNOWN][DISTANCE_INPUT_TIME_OUT] = DISTANCE_STATE_UNKNOWN,
    [DISTANCE_STATE_KNOWN][DISTANCE_INPUT_NEW_MEASUREMENT] = DISTANCE_STATE_KNOWN,
};

static bool distance_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(DISTANCE, "Proc %u", num);

    DistanceHandle_t* Node = DistanceGetNode(num);
    if(Node) {
        res = true;
        if(DISTANCE_INPUT_NONE != Node->input) {
        	if(Node->state<2) {
        		if(Node->input<2) {
                    DistanceActionHandler_t ActionHandler = NULL;
                    DistanceState_t new_state = StateLookUpTable[Node->state][Node->input];
                    ActionHandler = ActionLookUpTable[Node->state][Node->input];
                    if(ActionHandler) {
                        res = ActionHandler(Node);
                        if(res){
                        	LOG_PARN(DISTANCE, "%u TransferOk", num);
                        }else{
                        	LOG_ERROR(DISTANCE, "%u TransferErr", num);
                        }
                    }else {
                    	LOG_ERROR(DISTANCE, "%u HandlerErr", num);
                    }

                    Node->state = new_state;
                    Node->input = DISTANCE_INPUT_NONE;
        		}
        	}
        }

        switch((uint8_t)Node->state){
            case DISTANCE_STATE_UNKNOWN: {
                Node->distance_m = DISTANCE_INFINITY_M;
                LOG_DEBUG(DISTANCE, "DistInf");
                } break;
            case DISTANCE_STATE_KNOWN: {

                }break;
            default: {

                }break;
        }

        uint32_t cur_up_time_ms = time_get_ms32();
        uint32_t diff_ms = cur_up_time_ms - Node->new_dist_time_stamp_ms;
        Node->ttl_ms = DISTANCE_NO_UPDATE_TIME_OUT_MS-diff_ms;
        LOG_PARN(DISTANCE, "Diff %u ms", diff_ms);
        if(DISTANCE_NO_UPDATE_TIME_OUT_MS < diff_ms) {
            LOG_NOTICE(DISTANCE, "NoDistanseUpdateTimeOut %u ms, max %u ms", diff_ms, DISTANCE_NO_UPDATE_TIME_OUT_MS);
            Node->input = DISTANCE_INPUT_TIME_OUT;
            Node->distance_m = DISTANCE_INFINITY_M;
            Node->new_dist_time_stamp_ms = cur_up_time_ms;
        }
#ifdef HAS_DISTANCE_DIAG
        LOG_DEBUG(DISTANCE,"%s", DistanceNode2Str(Node));
#endif
    } else {
        LOG_PARN(DISTANCE, "%u NodeErr", num);
    }

    return res;
}


COMPONENT_PROC_PATTERT(DISTANCE, DISTANCE, distance)
#if 0
bool distance_proc(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    uint32_t cnt = distance_get_cnt();
    LOG_PARN(DISTANCE, "Proc %u cnt", cnt);
    for(i = 1; i <= cnt; i++) {
        res = distance_proc_one(i);
        if(res) {
            ok++;
        }
    }

    if(ok) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
#endif

bool distance_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(DISTANCE, "Init %u", num);
    const DistanceConfig_t* Config = DistanceGetConfig(num);
    if(Config) {
        LOG_WARNING(DISTANCE, "SpotConfig %u", num);
        DistanceHandle_t* Node = DistanceGetNode(num);
        if(Node) {
            LOG_WARNING(DISTANCE, "SpotItem %u", num);
            Node->decawave_num = Config->decawave_num;
            Node->debug_led_num = Config->debug_led_num;

            Node->state = DISTANCE_STATE_UNKNOWN;
            Node->input = DISTANCE_INPUT_TIME_OUT;
            Node->new_dist_time_stamp_ms = 0;
            Node->distance_m = DISTANCE_INFINITY_M;
#ifdef HAS_DISTANCE_DIAG
            LOG_WARNING(DISTANCE, "%s", DistanceNode2Str(Node));
#endif
            res = true;
        } else {
            LOG_ERROR(DISTANCE, "%u NodeErr", num);
        }
    } else {
        LOG_ERROR(DISTANCE, "%u ConfErr", num);
    }
    return res;
}



COMPONENT_INIT_PATTERT(DISTANCE, DISTANCE, distance)

#if 0
bool distance_init(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    uint32_t cnt = distance_get_cnt();
    LOG_WARNING(DISTANCE, "Init %u cnt", cnt);
    for(i = 1; i <= cnt; i++) {
        res = distance_init_one(i);
        if(res) {
            ok++;
        }
    }

    if(ok) {
        res = true;
    } else {
        res = false;
    }

    return res;
}

#endif
