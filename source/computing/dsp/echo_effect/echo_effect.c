#include "echo_effect.h"

#include <string.h>

#include "circular_buffer_word.h"
#include "code_generator.h"
#include "gpio_mcal.h"
#include "log.h"

COMPONENT_GET_NODE(EchoEffect, echo_effect)
COMPONENT_GET_CONFIG(EchoEffect, echo_effect)

bool echo_effect_init_custom(void) {
    bool res = true;
    log_level_get_set(ECHO_EFFECT, LOG_LEVEL_INFO);
    return res;
}

static bool EchoEffectIsValidConfig(const EchoEffectConfig_t* const Config) {
    bool res = false;
    if(Config) {
        if(Config->scale < 1.0) {
            if(Config->capacity) {
                if(Config->inArray) {
                    res = true;
                }
            }
        }
    }
    return res;
}

bool echo_effect_factor_set(uint8_t num, double scale){
    bool res = false ;
    EchoEffectHandle_t* Node = EchoEffectGetNode(num);
    if(Node){
    	Node->scale = scale;
        Node->numerator = (int16_t)(10000.0 * Node->scale);
        Node->denominator = 10000;
        LOG_WARNING(ECHO_EFFECT, "%u,Set,scale:%f", num, scale);
    	res = true;
    }
    return res;
}

bool echo_effect_factor_get(uint8_t num, double* const scale) {
	bool res = false ;
    EchoEffectHandle_t* Node = EchoEffectGetNode(num);
    if (Node) {
        *scale =  Node->scale;
        LOG_DEBUG(ECHO_EFFECT, "%u,Set,scale:%f", num, Node->scale);
    	res = true;
    }
    return res;
}

bool echo_effect_reset(uint8_t num){
    bool res = false;
    LOG_WARNING(ECHO_EFFECT, "Reset:%u", num);
    EchoEffectHandle_t* Node = EchoEffectGetNode(num);
    if(Node) {
        memset(Node->inArray, 0, Node->capacity*2);
        res = true;
    }
    return res;
}

bool echo_effect_init_one(uint8_t num) {
    LOG_WARNING(ECHO_EFFECT, "Init:%u", num);
    bool res = false;
    const EchoEffectConfig_t* Config = EchoEffectGetConfig(num);
    if(Config) {
        LOG_WARNING(ECHO_EFFECT, "%s", EchoEffectConfigToStr(Config));
        res = EchoEffectIsValidConfig(Config);
        if(res) {
            EchoEffectHandle_t* Node = EchoEffectGetNode(num);
            if(Node) {
                Node->num = Config->num;
                Node->name = Config->name;
                Node->inArray = Config->inArray;
                Node->scale = Config->scale;
                Node->capacity = Config->capacity;

                res = echo_effect_reset(num);
                res = echo_effect_factor_set(num, Node->scale);
                res = circular_buffer_word_init(&Node->CircularBuffer, Config->inArray, Config->capacity);
                Node->valid = true;
                Node->init = true;
            }
        } else {
            LOG_ERROR(ECHO_EFFECT, "ConfigErr:%u", num);
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(ECHO_EFFECT, ECHO_EFFECT, echo_effect)
