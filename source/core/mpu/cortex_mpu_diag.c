#include "cortex_mpu_diag.h"

#include "common_diag.h"
#include "control_diag.h"
#include "cortex_mpu_const.h"
#include "cortex_mpu_mcal.h"
#include "debugger.h"
#include "diag_inc.h"
#include "mcal_diag.h"
#include "mpu_diag.h"
#include "num_to_str.h"

/*
  MPU base address : 0xE000ED90
  Register Overview - MPU
 */
const Reg32_t MpuReg[] = {
    {
        .name = "TYPE",
        .offset = 0x0,
        .access = ACCESS_READ_ONLY,
        .valid = true,
    },
    {
        .name = "CTRL",
        .offset = 0x4,
        .access = ACCESS_READ_WRITE,
        .valid = true,
    },
    {
        .name = "RNR",
        .offset = 0x8,
        .access = ACCESS_READ_WRITE,
        .valid = true,
    },
    {
        .name = "RBAR",
        .offset = 0xC,
        .access = ACCESS_READ_WRITE,
        .valid = true,
    },
    {
        .name = "RASR",
        .offset = 0x10,
        .access = ACCESS_READ_WRITE,
        .valid = true,
    },
    {
        .name = "RBAR_A1",
        .offset = 0x14,
        .access = ACCESS_READ_WRITE,
        .valid = true,
    },
    {
        .name = "RASR_A1",
        .offset = 0x18,
        .access = ACCESS_READ_WRITE,
        .valid = true,
    },
    {
        .name = "RBAR_A2",
        .offset = 0x1C,
        .access = ACCESS_READ_WRITE,
        .valid = true,
    },
    {
        .name = "RASR_A2",
        .offset = 0x20,
        .access = ACCESS_READ_WRITE,
        .valid = true,
    },
    {
        .name = "RBAR_A3",
        .offset = 0x24,
        .access = ACCESS_READ_WRITE,
        .valid = true,
    },
    {
        .name = "RASR_A3",
        .offset = 0x28,
        .access = ACCESS_READ_WRITE,
        .valid = true,
    },
};

static uint32_t mpu_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(MpuReg);
    return cnt;
}

bool mpu_raw_reg_diag(void) {
    bool res = false;
    LOG_WARNING(LG_MPU, "Base:0x%p", MPU);
    uint32_t reg_cnt = mpu_reg_cnt();
    res = debug_raw_reg_diag(LG_MPU, (uint32_t)MPU, MpuReg, reg_cnt);

    return res;
}

bool CortexMpuRegsDiag(const MPU_Type* const Base) {
    bool res = false;
    if(Base) {
        LOG_INFO(LG_MPU, "   TYPE:0x%08X", Base->TYPE);
        LOG_INFO(LG_MPU, "   CTRL:0x%08X", Base->CTRL);
        LOG_INFO(LG_MPU, "    RNR:0x%08X", Base->RNR);
        LOG_INFO(LG_MPU, "   RBAR:0x%08X", Base->RBAR);
        LOG_INFO(LG_MPU, "   RASR:0x%08X", Base->RASR);
        LOG_INFO(LG_MPU, "RASR_A1:0x%08X", Base->RASR_A1);
        LOG_INFO(LG_MPU, "RBAR_A1:0x%08X", Base->RBAR_A1);
        LOG_INFO(LG_MPU, "RBAR_A2:0x%08X", Base->RBAR_A2);
        LOG_INFO(LG_MPU, "RASR_A2:0x%08X", Base->RASR_A2);
        LOG_INFO(LG_MPU, "RBAR_A3:0x%08X", Base->RBAR_A3);
        LOG_INFO(LG_MPU, "RASR_A3:0x%08X", Base->RASR_A3);
        res = true;
    }
    return res;
}

static bool CortexMpuRegsDiagTYPE_LL(const MpuRegType_t* const Node) {
    bool res = false;
    RegisterDiag(Node->dword, "Type");

    LOG_INFO(LG_MPU, "SEPARATE:%u", Node->SEPARATE);
    LOG_INFO(LG_MPU, "DREGION:%u", Node->DREGION);
    LOG_INFO(LG_MPU, "IREGION:%u", Node->IREGION);
    return res;
}

static bool CortexMpuRegsDiagCTRL_LL(const MpuRegCtrl_t* const Node) {
    bool res = false;
    RegisterDiag(Node->dword, "Ctrl");

    LOG_INFO(LG_MPU, "ENABLE:%u", Node->ENABLE);
    LOG_INFO(LG_MPU, "HFNMIENA:%u", Node->HFNMIENA);
    LOG_INFO(LG_MPU, "PRIVDEFENA:%u", Node->PRIVDEFENA);
    return res;
}

static bool CortexMpuRegsDiagRNR_LL(const MpuRegRnr_t* const Node) {
    bool res = false;
    RegisterDiag(Node->dword, "Rnr");

    LOG_INFO(LG_MPU, "REGION:%u", Node->REGION);
    return res;
}

static bool CortexMpuRegsDiagRBAR_LL(const MpuRegRbar_t* const Node) {
    bool res = false;
    RegisterDiag(Node->dword, "Rbar");

    LOG_INFO(LG_MPU, "REGION:%u", Node->REGION);
    LOG_INFO(LG_MPU, "VALID:%u", Node->VALID);
    LOG_INFO(LG_MPU, "ADDR:%u", Node->ADDR);
    return res;
}

static bool CortexMpuRegsDiagRASR_LL(const MpuRegRasr_t* const Node) {
    bool res = false;
    RegisterDiag(Node->dword, "Rasr");
    LOG_INFO(LG_MPU, "ENABLE:%u", Node->ENABLE);
    LOG_INFO(LG_MPU, "SIZE:%u", Node->SIZE);
    LOG_INFO(LG_MPU, "SRD:%u", Node->SRD);
    LOG_INFO(LG_MPU, "B:%u", Node->B);
    LOG_INFO(LG_MPU, "C:%u", Node->C);
    LOG_INFO(LG_MPU, "S:%u", Node->S);
    LOG_INFO(LG_MPU, "TEX:%u", Node->TEX);
    LOG_INFO(LG_MPU, "AP:%u", Node->AP);
    LOG_INFO(LG_MPU, "XP:%u", Node->XP);
    return res;
}

bool CortexMpuRegsDiagLL(const MpuRegMap_t* const PHY) {
    bool res = false;
    if(PHY) {
        res = CortexMpuRegsDiagTYPE_LL(&PHY->MPU_TYPE);
        res = CortexMpuRegsDiagCTRL_LL(&PHY->MPU_CTRL);
        res = CortexMpuRegsDiagRNR_LL(&PHY->MPU_RNR);
        res = CortexMpuRegsDiagRBAR_LL(&PHY->MPU_RBAR);
        res = CortexMpuRegsDiagRASR_LL(&PHY->MPU_RASR);

        RegisterDiag(PHY->MPU_RASR_A1, "RASR_A1");
        RegisterDiag(PHY->MPU_RBAR_A1, "RBAR_A1");
        RegisterDiag(PHY->MPU_RBAR_A2, "RBAR_A2");
        RegisterDiag(PHY->MPU_RASR_A2, "RASR_A2");
        RegisterDiag(PHY->MPU_RBAR_A3, "RBAR_A3");
        RegisterDiag(PHY->MPU_RASR_A3, "RASR_A3");
    }
    return res;
}

bool cortex_mpu_diag(void) {
    bool res = true;
    MpuRegMap_t* PHY = (MpuRegMap_t*)MPU;
    //  res=CortexMpuRegsDiag(MPU);
    res = CortexMpuRegsDiagLL(PHY);

    return res;
}

bool cortex_mpu_region(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Region"},
        {12, "BaseAddr"},
        {8, "Size"},
        {12, "Access"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = mpu_get_region_cnt();
    uint32_t r = 0;
    for(r = 0; r < cnt; r++) {
        uint32_t base_address = 0;
        uint32_t size = 0;
        ControlPermission_t Permission = {0};
        res = cortex_mpu_get_base_addr(r, &base_address);
        res = cortex_mpu_get_size(r, &size);
        res = cortex_mpu_get_access(r, &Permission);

        char temp[120] = {0};
        strcpy(temp, TSEP);
        snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, r);
        snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, base_address);
        snprintf(temp, sizeof(temp), "%s %6u " TSEP, temp, size);
        snprintf(temp, sizeof(temp), "%s %6s " TSEP, temp, ControlPermissionToStr(Permission));
        cli_printf("%s" CRLF, temp);
        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
