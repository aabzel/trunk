#include "multicore_mcal.h"

#include "log.h"
#include "microcontroller.h"
#include "std_includes.h"
#include "time_mcal.h"

#include "FC7300F8MDT_cpm_common_feature.h"
#include "FC7300F8MDT_rgm_common_feature.h"
#include "FC7300_rgm_common_feature.h"
#include "FC7300_scm_common_feature.h"
#include "core_cm7.h"
#include "core_driver.h"
#include "module_driver_rgm.h"
#include "module_rgm_regs.h"
#include "v_def.h"

bool multicore_release(uint8_t core_num) {
    bool res = false;
    LOG_WARNING(MULTICORE, "Release,Core:%u", core_num);
    switch(core_num) {
    case 1:
        res = false;
        break;
    case 2:
        RGM_ReleaseCPU1();
        break;
    case 3:
        RGM_ReleaseCPU2();
        break;
    default:
        break;
    }
    return res;
}

bool multicore_reset(uint8_t core_num) {
    bool res = false;
    LOG_WARNING(MULTICORE, "Reset,Core:%u", core_num);
    switch(core_num) {
    case 1:
        res = core_reboot();
        break;
    case 2:
        RGM_GenerateCpu1SwReset();
        break;
    case 3:
        RGM_GenerateCpu2SwReset();
        break;
    default:
        break;
    }
    return res;
}
/*
 SCM System Control Module
 RGM Reset Generate Module
 */

static bool multicore_access_ctrl(MiltiCoreWritePermission_t permission) {
    bool res = true;
    CORE_HOLD_t CoreHoldReg;
    CoreHoldReg.dword = SCM->CORE_HOLD;
    CoreHoldReg.WPB = permission;
    CoreHoldReg.WPB_LOCK = 0;
    SCM->CORE_HOLD = CoreHoldReg.dword;
    return res;
}

static bool multicore_ctrl_core2(bool on_off) {
    bool res = false;
#if 0
    volatile CPUxResetRegister_t* CPU1ResetReg = ( CPUxResetRegister_t* ) &(RGM->C1_RST);
    volatile CPUxVTOR_t* CPU1VTORReg = (CPUxVTOR_t*) &(SCM->CPU1VTOR);
    volatile CORE_HOLD_t* CORE_HOLDReg = (CORE_HOLD_t*) &( SCM->CORE_HOLD);
    volatile Cx_RLS_t* C1_RLSReg = (Cx_RLS_t*) &(RGM->C1_RLS );
    if(on_off){
        CPU1ResetReg->Cx_SWRST = Cx_SWRST_CPU_RESET;
        CPU1VTORReg->CPUx_INIT_VECTOR = CORE_1_VECTOR_ADDR & 0x0FFFFFF8U;
        CORE_HOLDReg->CPU1_CORE_HOLD = CPUx_CORE_NOT_HOLD_RELEASED; // hand on
        C1_RLSReg->Cx_RELEASE = Cx_RELEASE_RELEASE ;
    }else{
    	//CPU1ResetReg->Cx_SWRST = Cx_SWRST_CPU_RESET;
        CORE_HOLDReg->CPU1_CORE_HOLD = CPUx_CORE_HOLD_NOT_RUNNING;
    }
#endif

    multicore_access_ctrl(MC_WR_PERM_ALL_CPU);
#if 1
    if(on_off) {
        RGM->C1_RST |= (uint32)RGM_C1_RST_C1_SWRST_MASK;
        SCM->CPU1VTOR = ((uint32_t)(CORE_1_VECTOR_ADDR & 0x0FFFFFF8U)) >> 4; /* high 4 bits for WPB */
        SCM->CORE_HOLD &= ~((uint32)SCM_CORE_HOLD_MASK_CPU1_CORE_HOLD);
        RGM->C1_RLS |= (uint32)RGM_C1_RLS_C1_RELEASE_MASK;
        // delay(1000000U);
    } else {
        RGM->C1_RST |= (uint32)RGM_C1_RST_C1_SWRST_MASK;
        SCM->CORE_HOLD |= ((uint32)SCM_CORE_HOLD_MASK_CPU1_CORE_HOLD);
    }
#endif
    // bool time_delay_ms(uint32_t delay_in_ms)
    return res;
}

static bool multicore_ctrl_core3(bool on_off) {
    bool res = false;
#if 0
    volatile CPUxResetRegister_t* CPU2ResetReg = ( CPUxResetRegister_t* ) &(RGM->C2_RST);
    volatile CPUxVTOR_t* CPU2VTORReg = (CPUxVTOR_t*) &(SCM->CPU2VTOR);
    volatile CORE_HOLD_t* CORE_HOLDReg = (CORE_HOLD_t*) &( SCM->CORE_HOLD);
    volatile Cx_RLS_t* C2_RLSReg = (Cx_RLS_t*) &(RGM->C2_RLS );
    if(on_off){
        CPU2ResetReg->Cx_SWRST = Cx_SWRST_CPU_RESET;
        CPU2VTORReg->CPUx_INIT_VECTOR = CORE_2_VECTOR_ADDR;
        CORE_HOLDReg->CPU2_CORE_HOLD = CPUx_CORE_NOT_HOLD_RELEASED;
        C2_RLSReg->Cx_RELEASE = Cx_RELEASE_RELEASE ;
    }else{
        CORE_HOLDReg->CPU2_CORE_HOLD = CPUx_CORE_HOLD_NOT_RUNNING;
    }
#endif
    multicore_access_ctrl(MC_WR_PERM_ALL_CPU);
#if 1
    if(on_off) {
        RGM->C2_RST |= (uint32)RGM_C2_RST_C2_SWRST_MASK;
        SCM->CPU2VTOR = ((uint32_t)(CORE_2_VECTOR_ADDR & 0x0FFFFFF8U)) >> 4; /* high 4 bits for WPB */
        SCM->CORE_HOLD &= ~((uint32)SCM_CORE_HOLD_MASK_CPU2_CORE_HOLD);
        RGM->C2_RLS |= (uint32)RGM_C2_RLS_C2_RELEASE_MASK;
    } else {
        RGM->C2_RST |= (uint32)RGM_C2_RST_C2_SWRST_MASK;
        SCM->CORE_HOLD |= ((uint32)SCM_CORE_HOLD_MASK_CPU2_CORE_HOLD);
    }

    // delay(1000000U);
#endif
    return res;
}

bool multicore_control(uint8_t num, bool on_off) {
    bool res = false;
    LOG_WARNING(MULTICORE, "Ctrl:%u,EN:%u", num, on_off);

    switch(num) {
    case 1:
        res = true;
        break;
    case 2:
        res = multicore_ctrl_core2(on_off);
        break;
    case 3:
        res = multicore_ctrl_core3(on_off);
        break;
    default:
        res = false;
        break;
    }

    time_delay_ms(1000);
    return res;
}

int8_t multicore_get_core_num(void) {
    int8_t core_num = -1;
    uint8_t core_index = Cpm_HWA_GetCoreId();
    switch(core_index) {
    case CPM_CPU_ID_CORE0:
        core_num = 0;
        break;
    case CPM_CPU_ID_CORE1:
        core_num = 1;
        break;
    case CPM_CPU_ID_CORE2:
        core_num = 2;
        break;
    default:
        break;
    }
    return core_num;
}

bool multicore_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(MULTICORE, "Init:%u", num);
    const MultiCoreConfig_t* Config = MultiCoreGetConfig(num);
    if(Config) {
        MultiCoreHandle_t* Node = MultiCoreGetNode(num);
        if(Node) {
            uint32_t core_id = 0;
            core_id = Cpm_HWA_GetCoreId();
            LOG_INFO(MULTICORE, "%u,Init:CoreId:%u", num, core_id);
            Node->init = true;
            res = true;
        } else {
            LOG_ERROR(MULTICORE, "NoNode");
        }
    } else {
        LOG_ERROR(MULTICORE, "NoConfig");
    }

    return res;
}
