#include "sw_component.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(SwComponent, sw_component)
COMPONENT_GET_CONFIG(SwComponent, sw_component)

#ifdef HAS_SW_COMPONENT_CUSTOM
static const SwComponentInfo_t SwComponentInfo[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
};

COMPONENT_GET_INFO(SwComponent)
#endif

/*ISO-26262 require verify configuration*/
_WEAK_FUN_
bool SwComponentIsValidConfig(const SwComponentConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(res) {
            if(Config->name) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(SW_COMPONENT, "%u,NameErr", Config->num);
            }
        }
    }
    return res;
}

_WEAK_FUN_
bool sw_component_init_custom(void) {
    bool res = false;
    LOG_INFO(SW_COMPONENT, "Version:%s", SW_COMPONENT_VERSION);
    return res;
}

_WEAK_FUN_
bool sw_component_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(SW_COMPONENT, "Proc %u", i);
    SwComponentHandle_t* Node = SwComponentGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

_WEAK_FUN_
bool sw_component_init_common(const SwComponentConfig_t* const Config, SwComponentHandle_t* const Node) {
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

_WEAK_FUN_
bool sw_component_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SW_COMPONENT, "SW_COMPONENT%u", num);
    const SwComponentConfig_t* Config = SwComponentGetConfig(num);
    if(Config) {
        res = SwComponentIsValidConfig(Config);
        if(res) {
#ifdef HAS_SW_COMPONENT_DIAG
            LOG_WARNING(SW_COMPONENT, "%s", SwComponentConfigToStr(Config));
#endif
            SwComponentHandle_t* Node = SwComponentGetNode(num);
            if(Node) {
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(SW_COMPONENT, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(SW_COMPONENT, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(SW_COMPONENT, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(SW_COMPONENT, SW_COMPONENT, sw_component)
COMPONENT_PROC_PATTERT(SW_COMPONENT, SW_COMPONENT, sw_component)
