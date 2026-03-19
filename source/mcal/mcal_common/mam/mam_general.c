#include "mam_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(Mam, mam)
COMPONENT_GET_CONFIG(Mam, mam)

/*ISO-26262 require verify configuration*/
_WEAK_FUN_
bool MamIsValidConfig(const MamConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(res) {
            if(Config->name) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(MAM, "%u,NameErr", Config->num);
            }
        }
    }
    return res;
}

_WEAK_FUN_
bool mam_init_custom(void) {
    bool res = false;
    LOG_INFO(MAM, "Version:%s", MAM_VERSION);
    return res;
}

_WEAK_FUN_
bool mam_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(MAM, "Proc %u", i);
    MamHandle_t* Node = MamGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

_WEAK_FUN_
bool mam_init_common(const MamConfig_t* const Config, MamHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->region_cnt = Config->region_cnt;
            Node->region = Config->region;
            Node->name = Config->name;
            Node->interrupt_on = Config->interrupt_on;
            res = true;
        }
    }
    return res;
}

_WEAK_FUN_
bool mam_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(MAM, "MAM%u", num);
    const MamConfig_t* Config = MamGetConfig(num);
    if(Config) {
        res = MamIsValidConfig(Config);
        if(res) {
#ifdef HAS_MAM_DIAG
            LOG_WARNING(MAM, "%s", MamConfigToStr(Config));
#endif
            MamHandle_t* Node = MamGetNode(num);
            if(Node) {
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(MAM, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(MAM, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(MAM, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(MAM, MAM, mam)
COMPONENT_PROC_PATTERT(MAM, MAM, mam)
