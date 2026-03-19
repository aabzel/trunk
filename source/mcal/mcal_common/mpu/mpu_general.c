#include "mpu_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(Mpu, mpu)
COMPONENT_GET_CONFIG(Mpu, mpu)

/*ISO-26262 require verify configuration*/
_WEAK_FUN_
bool MpuIsValidConfig(const MpuConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(res) {
            if(Config->name) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(LG_MPU, "%u,NameErr", Config->num);
            }
        }
    }
    return res;
}

_WEAK_FUN_
bool mpu_init_custom(void) {
    bool res = false;
    LOG_INFO(LG_MPU, "Version:%s", MPU_VERSION);
    return res;
}

_WEAK_FUN_
bool mpu_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(LG_MPU, "Proc %u", i);
    MpuHandle_t* Node = MpuGetNode(i);
    if(Node) {
        if(Node->it_done) {
            LOG_WARNING(LG_MPU, "WasInt:%u", Node->it_cnt);
            Node->it_done = false;
            res = mpu_ctrl(i, true);
        }
        Node->spin++;
    }
    return res;
}

_WEAK_FUN_
bool mpu_init_common(const MpuConfig_t* const Config, MpuHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->interrupt_on = Config->interrupt_on;
            Node->Region = Config->Region;
            Node->region_cnt = Config->region_cnt;

            res = true;
        }
    }
    return res;
}

_WEAK_FUN_
bool mpu_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(LG_MPU, "MPU%u", num);
    const MpuConfig_t* Config = MpuGetConfig(num);
    if(Config) {
        res = MpuIsValidConfig(Config);
        if(res) {
#ifdef HAS_MPU_DIAG
            LOG_WARNING(LG_MPU, "%s", MpuConfigToStr(Config));
#endif
            MpuHandle_t* Node = MpuGetNode(num);
            if(Node) {
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(LG_MPU, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(LG_MPU, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(LG_MPU, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(LG_MPU, MPU, mpu)
COMPONENT_PROC_PATTERT(LG_MPU, MPU, mpu)
