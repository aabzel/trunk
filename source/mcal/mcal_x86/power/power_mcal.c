#include "power_mcal.h"

#include "std_includes.h"
#include "code_generator.h"
#include "data_utils.h"
#include "log.h"
#include "power_custom_drv.h"
#include "microcontroller_const.h"
#include "power_manager.h"
#include "x86x_misc.h"

static const PowerInfo_t PowerInfo[] = {
    {
        .num = 1,
        .POWERx = (PCU_Type*) PCU,
        .valid = true,
    },
};

COMPONENT_GET_INFO(Power)

#if 0
const PowerInfo_t* PowerGetInfo(uint8_t num) {
    PowerInfo_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(PowerInfo);
    for(i = 0; i < cnt; i++) {
        if(num == PowerInfo[i].num) {
            if(PowerInfo[i].valid) {
                Node = &PowerInfo[i];
                break;
            }
        }
    }
    return Node;
}
#endif



bool power_init_custom(void) {
    bool res = true;
    log_level_get_set(POWER, LOG_LEVEL_INFO);
    return res;
}

bool power_proc_one(uint8_t num) {
    bool res = false;
    PowerHandle_t* Node = PowerGetNode(num);
    if(Node) {
    }
    return res;
}

bool power_init_one(uint8_t num) {
    bool res = false;
    log_level_get_set(POWER, LOG_LEVEL_DEBUG);
    const PowerConfig_t* Config = PowerGetConfig(num);
    if(Config) {
        res = PowerIsValidConfig(Config);
        if(res) {
#ifdef HAS_POWER_DIAG
            LOG_WARNING(POWER, "%s", PowerConfigToStr(Config));
#endif
            PowerHandle_t* Node = PowerGetNode(num);
            if(Node) {
                res = power_init_common(Config, Node);

                PowerInfo_t* Info = PowerGetInfo(num);
                if(Info) {
                    Node->POWERx = Info->POWERx;

                    static power_manager_user_config_t power_manager_user_config = {
                         .powerMode = POWER_MANAGER_RUN,
                         .sleepOnExitValue = false,
                    };

                    static power_manager_user_config_t *powerConfigsArr[] = {
                        &power_manager_user_config,
                    };

                    status_t ret;
                    ret = POWER_SYS_Init(&powerConfigsArr, 1, NULL, 0);
                    res = Fc7300xSdkStatusToRes(ret);

                    ret = POWER_SYS_SetMode( 0, POWER_MANAGER_POLICY_FORCIBLE);
                    res = Fc7300xSdkStatusToRes(ret) && res;

                } else {
                    LOG_ERROR(POWER, "POWER%u,InstErr", num);
                }
            } else {
                LOG_ERROR(POWER, "POWER%u NodeErr", num);
            }
        }
    } else {
        LOG_DEBUG(POWER, "POWER%u ConfErr", num);
    }
    log_level_get_set(POWER, LOG_LEVEL_INFO);
    return res;
}

