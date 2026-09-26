#include "multicore_custom_diag.h"

#include "log.h"
#include "microcontroller.h"

//#include "core_cm7.h"

#include "FC7300F8MDT_cpm_common_feature.h"
#include "FC7300F8MDT_rgm_common_feature.h"
#include "FC7300_rgm_common_feature.h"
#include "FC7300_scm_common_feature.h"
#include "module_rgm_regs.h"
#include "multicore_custom_drv.h"

/*see SCM_CORE_HOLD field descriptions*/
bool MultiCoreDiagCoreHoldReg(const CORE_HOLD_t* const CoreHoldReg) {
    bool res = false;
    if(CoreHoldReg) {
        LOG_WARNING(MULTICORE, "CORE_HOLD,Dword:0x%x", CoreHoldReg->dword);
        LOG_INFO(MULTICORE, "CPU1_CORE_HOLD:%u", CoreHoldReg->CPU1_CORE_HOLD);
        LOG_INFO(MULTICORE, "CPU2_CORE_HOLD:%u", CoreHoldReg->CPU2_CORE_HOLD);
        LOG_INFO(MULTICORE, "WPB:%u", CoreHoldReg->WPB);
        LOG_INFO(MULTICORE, "WPB_LOCK:%u", CoreHoldReg->WPB_LOCK);
        res = true;
    }
    return res;
}

/*see SCM_CORE_HOLD field descriptions*/
bool MultiCoreDiagCpu2VtorReg(const CPUxVTOR_t* const Reg, char* prefix) {
    bool res = false;
    if(Reg) {
        LOG_WARNING(MULTICORE, "CPU%sVTOR,Dword:0x%x", prefix, Reg->dword);
        LOG_INFO(MULTICORE, "CPU%s_INIT_VECTOR:0x%x", prefix, Reg->CPUx_INIT_VECTOR);
        LOG_INFO(MULTICORE, "WPB:%u", Reg->WPB);
        LOG_INFO(MULTICORE, "WPB_LOCK:%u", Reg->WPB_LOCK);
        res = true;
    }
    return res;
}

bool multicore_custom_diag(void) {
    bool res = false;

    uint8_t core_index = Cpm_HWA_GetCoreId();
    LOG_INFO(MULTICORE, "CoreID:%u", core_index);

    CORE_HOLD_t CoreHoldReg;
    CoreHoldReg.dword = SCM->CORE_HOLD;
    MultiCoreDiagCoreHoldReg(&CoreHoldReg);

    CPUxVTOR_t CPUxVTOR;
    CPUxVTOR.dword = SCM->CPU1VTOR;
    MultiCoreDiagCpu2VtorReg(&CPUxVTOR, "1");

    CPUxVTOR.dword = SCM->CPU2VTOR;
    MultiCoreDiagCpu2VtorReg(&CPUxVTOR, "2");

    return res;
}
