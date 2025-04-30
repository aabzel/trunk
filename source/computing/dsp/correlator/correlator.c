#include "correlator.h"

#include <string.h>
#include <stdlib.h>

#include "circular_buffer_word.h"
#include "code_generator.h"
#include "log.h"

COMPONENT_GET_NODE(Correlator, correlator)
COMPONENT_GET_CONFIG(Correlator, correlator)

bool correlator_init_custom(void) {
    bool res = true;
    log_level_get_set(CORRELATOR, LOG_LEVEL_INFO);
    return res;
}

static bool CorrelatorIsValidConfig(const CorrelatorConfig_t* const Config) {
    bool res = false;
    if(Config) {
        if(res){
            if(Config->SignalA) {
                res = true;
            }else{
                res = false;
            }
        }

        if(res){
            if(Config->SignalB) {
                res = true;
            }else{
                res = false;
            }
        }

        if(res){
            if(0<Config->size) {
                res = true;
            }else{
                res = false;
            }
        }
    }
    return res;
}

bool correlator_s16_calc_diff_ll(int16_t* const arrayA,
		                         int16_t* const arrayB,
                                 uint32_t cnt,
						         int32_t* const correlation_out) {
    bool res = false;
    if(correlation_out) {
        if(cnt) {
            int32_t correlation_result = 0;
            int32_t i = 0;
            for(i=0; i<cnt; i++) {
            	int32_t sampl_a = (int32_t) arrayA[i] ;
                int32_t sampl_b = (int32_t) arrayB[i] ;
                int32_t diff_one =  sampl_a   -  sampl_b  ;
                correlation_result += abs(diff_one);
                //correlation_result += mult_one;
                res = true;
            }
            *correlation_out = correlation_result ;
        }
    }

    return res;
}

bool correlator_s16_calc_ll(int16_t* const arrayA,
		                    int16_t* const arrayB,
                            uint32_t cnt,
						    int32_t* const correlation_out) {
    bool res = false;
    if(correlation_out) {
        if(cnt) {
            int32_t correlation_result = 0;
            int32_t i = 0;
            for(i=0; i<cnt; i++) {
            	int32_t sampl_a = (int32_t) arrayA[i] ;
                int32_t sampl_b = (int32_t) arrayB[i] ;
                int32_t mult_one =  sampl_a   *  sampl_b  ;
                correlation_result += mult_one;
                //correlation_result += mult_one;
                res = true;
            }
            *correlation_out = correlation_result ;
        }
    }

    return res;
}

bool correlator_calc_ll(CircularBufferWord_t* const SignalA,
                        CircularBufferWord_t* const SignalB,
                        uint32_t cnt,
						int32_t* const correlation_out) {
    bool res = true;
    if(correlation_out) {
    	int32_t correlation_result = 0;
        int32_t i = 0;
        for(i=0; i<cnt; i++) {
            int16_t sampl_a = 0;
            res = circular_buffer_word_get(SignalA, -i, &sampl_a) ;
            if(res) {
                int16_t sampl_b = 0;
                res = circular_buffer_word_get(SignalB, -i, &sampl_b) ;
                if(res) {
                    int32_t mult_one = (  (int32_t)sampl_a  ) * (  (int32_t)sampl_b  );
                    //correlation_result += abs(mult_one);
                    correlation_result += mult_one;
                }
            }
        }
        *correlation_out = correlation_result ;
    }

    return res;
}

bool correlator_calc(uint8_t num, int32_t* const correlation_result) {
    bool res = false;
    CorrelatorHandle_t* Node = CorrelatorGetNode(num);
    if(Node) {
        Node->correlation_result = 0;
        res = correlator_calc_ll(Node->SignalA,
                                 Node->SignalB,
                                 Node->size,
                                 &Node->correlation_result);
        if(res) {
            *correlation_result = Node->correlation_result;
        }
    }
    return res;
}


bool correlator_init_one(uint8_t num) {
    LOG_WARNING(CORRELATOR, "Init:%u", num);
    bool res = false;
    const CorrelatorConfig_t* Config = CorrelatorGetConfig(num);
    if(Config) {
        LOG_WARNING(CORRELATOR, "%s", CorrelatorConfigToStr(Config));
        res = CorrelatorIsValidConfig(Config);
        if(res) {
            CorrelatorHandle_t* Node = CorrelatorGetNode(num);
            if(Node) {
                Node->SignalA = Config->SignalA;
                Node->SignalB = Config->SignalB;
                Node->name = Config->name;
                Node->num = Config->num;
                Node->size = Config->size;

                Node->valid = true;
                Node->init = true;
            }
        } else {
            LOG_ERROR(CORRELATOR, "ConfigErr:%u", num);
        }
    }
    return res;
}


COMPONENT_INIT_PATTERT(CORRELATOR, CORRELATOR, correlator)
