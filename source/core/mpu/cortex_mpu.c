#include "cortex_mpu_mcal.h"

#include <stdlib.h>

#include "bit_const.h"
#include "clock_mcal.h"
#include "clock_utils.h"
#include "common_functions.h"
#include "compiler_const.h"
#include "mpu_mcal.h"
#include "std_includes.h"
#ifdef HAS_DIAG
#include "common_diag.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

static uint8_t MpuApToIsRead(const uint8_t ac_code) {
    uint8_t read = 0;
    switch(ac_code) {
    case MPU_ACCESS_PERM_NO_ACCESS:
        read = 0;
        break;
    case MPU_ACCESS_PERM_FULL_ACCESS:
        read = 1;
        break;
    case MPU_ACCESS_PERM_READONLY:
        read = 1;
        break;
    case MPU_ACCESS_PERM_READONLY2:
        read = 1;
        break;
    default:
        break;
    }
    return read;
}

static uint8_t MpuApToIsWrite(const uint8_t ac_code) {
    uint8_t write = 0;
    switch(ac_code) {
    case MPU_ACCESS_PERM_FULL_ACCESS:
        write = 1;
        break;
    case MPU_ACCESS_PERM_NO_ACCESS:
        write = 0;
        break;
    case MPU_ACCESS_PERM_READONLY:
        write = 0;
        break;
    case MPU_ACCESS_PERM_READONLY2:
        write = 0;
        break;
    default:
        write = 0;
        break;
    }
    return write;
}

uint32_t mpu_get_region_cnt(void) {
    MpuRegMap_t* PHY = (MpuRegMap_t*)MPU;
    uint32_t regions = PHY->MPU_TYPE.DREGION;
    return regions;
}

bool mpu_is_supported(void) {
    bool res = false;
    uint32_t regions = mpu_get_region_cnt();
    if(regions) {
        res = true;
    }
    return res;
}

bool cortex_mpu_get_base_addr(const uint8_t region, uint32_t* const base_address) {
    bool res = false;
    if(base_address) {
        cortex_mpu_select_region(region);

        MpuRegRbar_t RegMpuRBAR;
        MpuRegMap_t* PHY = (MpuRegMap_t*)MPU;
        RegMpuRBAR.dword = PHY->MPU_RBAR.dword;
        uint32_t get_region = RegMpuRBAR.REGION;
        RegMpuRBAR.REGION = 0;
        RegMpuRBAR.VALID = 0;

        *base_address = RegMpuRBAR.dword;

        if(region == get_region) {
            res = true;
        } else {
            LOG_ERROR(LG_MPU, "regUnMatch,get %u!=%u set", get_region, region);
        }
    }
    return res;
}

bool cortex_mpu_select_region(const uint8_t region) {
    bool res = true;
    MpuRegRnr_t RegRnr;
    RegRnr.dword = 0;
    RegRnr.REGION = region;

    MpuRegMap_t* PHY = (MpuRegMap_t*)MPU;
    PHY->MPU_RNR.dword = RegRnr.dword;
    return res;
}

static bool MpuApToPermission(const MpuRegRasr_t* const Rasr, ControlPermission_t* const Permission) {
    bool res = false;
    if(Rasr) {
        if(Permission) {
            Permission->shareable = Rasr->S;
            Permission->bufferable = Rasr->B;
            Permission->cached = Rasr->C;
            Permission->execute = !Rasr->XP;
            Permission->read = MpuApToIsRead(Rasr->AP);
            Permission->write = MpuApToIsWrite(Rasr->AP);
            res = true;
        }
    }
    return res;
}

bool cortex_mpu_get_access(const uint8_t region, ControlPermission_t* const Permission) {
    bool res = true;
    cortex_mpu_select_region(region);
    MpuRegMap_t* PHY = (MpuRegMap_t*)MPU;
    MpuRegRasr_t RegRasr;
    RegRasr.dword = PHY->MPU_RASR.dword;
    res = MpuApToPermission(&RegRasr, Permission);

    return res;
}

bool cortex_mpu_get_size(const uint8_t region, uint32_t* const size) {
    bool res = false;
    if(size) {
        cortex_mpu_select_region(region);
        MpuRegMap_t* PHY = (MpuRegMap_t*)MPU;
        MpuRegRasr_t RegMPU_RASR = {0};
        RegMPU_RASR.dword = PHY->MPU_RASR.dword;
        *size = int_pow(2, RegMPU_RASR.SIZE + 1);
        res = true;
    }
    return res;
}

static bool cortex_mpu_init_custom(void) {
    bool res = true;
    res = mpu_is_supported();
    return res;
}

static bool cortex_mpu_proc_one(uint8_t num) {
    bool res = true;
    MpuHandle_t* Node = MpuGetNode(num);
    if(Node) {
        if(Node->it_done) {
            LOG_WARNING(LG_MPU, "WasInt:%u", Node->it_cnt);
            Node->it_done = false;
        }
    }
    return res;
}

#ifdef HAS_SYSTIC_INT
/*if call every 1ms 32bit overflows after 49 days*/
#endif /*HAS_CORTEX_MPU_INT*/

static bool cortex_mpu_init_one(uint8_t num) {
    bool res = false;
    const MpuConfig_t* Config = MpuGetConfig(num);
    if(Config) {
        MpuHandle_t* Node = MpuGetNode(num);
        if(Node) {
        }
    }
    return res;
}

bool cortex_mpu_mcal_init(void) {
    bool res = true;
    res = cortex_mpu_init_custom();
    uint32_t ok = 0;
    uint32_t cnt = mpu_get_cnt();
    uint32_t num = 0;
    for(num = 0; num <= cnt; num++) {
        res = cortex_mpu_init_one(num);
        ok = ok_cnt_update(ok, res);
    }
    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool cortex_mpu_proc(void) {
    bool res = true;
    uint32_t ok = 0;
    uint32_t cnt = mpu_get_cnt();
    (void)cnt;
    uint32_t num = 0;
    for(num = 0; num <= cnt; num++) {
        res = cortex_mpu_proc_one(num);
        ok = ok_cnt_update(ok, res);
    }
    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
