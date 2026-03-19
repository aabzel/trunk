#include "trng_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(tRng, trng)
COMPONENT_GET_CONFIG(tRng, trng)

/*ISO-26262 require verify configuration*/
_WEAK_FUN_
bool tRngIsValidConfig(const tRngConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(TRNG, "%u,NameErr", Config->num);
            res = false;
        }
    }
    return res;
}

_WEAK_FUN_
bool trng_init_custom(void) {
    bool res = false;
    LOG_INFO(TRNG, "Version:%s", TRNG_VERSION);
    return res;
}

_WEAK_FUN_
bool trng_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(TRNG, "Proc %u", i);
    tRngHandle_t* Node = tRngGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool trng_init_common(const tRngConfig_t* const Config, tRngHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->interrupt_on = Config->interrupt_on;
            res = true;
        }
    }
    return res;
}

uint32_t trng_static_get_rand(void) {
    static uint32_t Z; // No init val deliberately
    if(Z & 1) {
        Z = (Z >> 1);
    } else {
        Z = (Z >> 1) ^ 0x7FFFF159;
    }
    return Z;
}

bool trng_init_node(tRngHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->valid = true;
        res = true;
    }
    return res;
}

_WEAK_FUN_
bool trng_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(TRNG, "TRNG%u", num);
    const tRngConfig_t* Config = tRngGetConfig(num);
    if(Config) {
        res = tRngIsValidConfig(Config);
        if(res) {
#ifdef HAS_TRNG_DIAG
            LOG_WARNING(TRNG, "%s", tRngConfigToStr(Config));
#endif
            tRngHandle_t* Node = tRngGetNode(num);
            if(Node) {
                res = trng_init_common(Config, Node);
                res = trng_init_node(Node);
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(TRNG, "TRNG%u,Node,Err", num);
            }
        } else {
            LOG_ERROR(TRNG, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(TRNG, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(TRNG, TRNG, trng)
COMPONENT_PROC_PATTERT(TRNG, TRNG, trng)
