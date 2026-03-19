#include "mpu_mcal.h"

#include "bit_utils.h"
#include "clock.h"
#include "code_generator.h"
#include "common_functions.h"
#include "cortex_mpu_const.h"
#include "data_utils.h"
#include "debug_info.h"
#include "interrupt_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "mpu_custom.h"
#include "mpu_custom_isr.h"
#include "stm32f4xx_hal_cortex.h"
#include "time_mcal.h"

static uint8_t MpuRegionOnOffToEnable(const bool on_off) {
    uint8_t enable = 0;
    enable = MPU_REGION_DISABLE;
    if(on_off) {
        enable = MPU_REGION_ENABLE;
    }
    return enable;
}

static uint8_t MpuPermissionToInstructionAccess(const MpuPermission_t permission) {
    uint8_t disable_exec = 0;
    switch(permission.execute) {
    case 0:
        disable_exec = MPU_INSTRUCTION_ACCESS_DISABLE;
        break;
    case 1:
        disable_exec = MPU_INSTRUCTION_ACCESS_ENABLE;
        break;
    default:
        disable_exec = MPU_INSTRUCTION_ACCESS_DISABLE;
        break;
    }
    return disable_exec;
}

/*
  prevent - to stop something from happening or someone from doing something:
 */
static uint8_t MpuPermissionToStm32Permission(const MpuPermission_t permission) {
    // CORTEX_MPU_Region_Permission_Attributes
    uint8_t stm32_perm = 0;

    uint8_t rw_code = 0x03 & permission.perm;
    switch(rw_code) {
    /*00*/ case 0:
        stm32_perm = MPU_REGION_NO_ACCESS;
        break;
    /*11*/ case 3:
        stm32_perm = MPU_REGION_FULL_ACCESS;
        break;
    /*01*/ case 1:
        stm32_perm = MPU_REGION_PRIV_RO_URO;
        break;
    /*10*/ case 2:
        stm32_perm = MPU_REGION_NO_ACCESS;
        break;

    /**/ default:
        break;
    }
    return stm32_perm;
}

#define MPU_INFO_ONE(NUM)                                                                                              \
    {                                                                                                                  \
        .num = NUM,                                                                                                    \
        .MPUx = MPU,                                                                                                   \
        .valid = true,                                                                                                 \
    },

#define MPU_INFO_ALL MPU_INFO_ONE(0)

static const MpuInfo_t MpuInfo[] = {MPU_INFO_ALL};

COMPONENT_GET_INFO(Mpu)

#if 0
const MpuInfo_t* MpuGetInfo(uint8_t num) {
    MpuInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(MpuInfo);
    for(i = 0; i < cnt; i++) {
        if(num == MpuInfo[i].num) {
            if(MpuInfo[i].valid) {
                Info = &MpuInfo[i];
                break;
            }
        }
    }
    return Info;
}
#endif

bool mpu_init_custom(void) {
    bool res = true;
    log_level_get_set(LG_MPU, LOG_LEVEL_INFO);
    LOG_PARN(LG_MPU, "MPU, Version:%u", MPU_VERSION);
    return res;
}

bool mpu_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    (void)num;

    if(on_off) {
        HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
    } else {
        HAL_MPU_Disable();
    }
    res = true;
    return res;
}

/*order matter!
  From small to big size
 */
static const MpuRegionSizeInfo_t SizeInfo[] = {
#if 0
        {.valid=true, .code=MPU_REGION_SIZE_32B,    .size=32,},
        {.valid=true, .code=MPU_REGION_SIZE_64B    , .size=64, },
        {.valid=true, .code=MPU_REGION_SIZE_128B   , .size=128, },
        {.valid=true, .code=MPU_REGION_SIZE_256B   , .size=256, },
        {.valid=true, .code=MPU_REGION_SIZE_512B   , .size=512, },
        {.valid=true, .code=MPU_REGION_SIZE_1KB    , .size=KBYTE_BYTE(1), },
        {.valid=true, .code=MPU_REGION_SIZE_2KB    , .size=KBYTE_BYTE(2), },
        {.valid=true, .code=MPU_REGION_SIZE_4KB    , .size=KBYTE_BYTE(4), },
        {.valid=true, .code=MPU_REGION_SIZE_8KB    , .size=KBYTE_BYTE(8), },
        {.valid=true, .code=MPU_REGION_SIZE_16KB   , .size=KBYTE_BYTE(16), },
        {.valid=true, .code=MPU_REGION_SIZE_32KB   , .size=KBYTE_BYTE(32), },
        {.valid=true, .code=MPU_REGION_SIZE_64KB   , .size=KBYTE_BYTE(64), },
        {.valid=true, .code=MPU_REGION_SIZE_128KB  , .size=KBYTE_BYTE(128), },
        {.valid=true, .code=MPU_REGION_SIZE_256KB  , .size=KBYTE_BYTE(256), },
        {.valid=true, .code=MPU_REGION_SIZE_512KB  , .size=KBYTE_BYTE(512), },
        {.valid=true, .code=MPU_REGION_SIZE_1MB    , .size= MBYTE_BYTE(1), },
        {.valid=true, .code=MPU_REGION_SIZE_2MB    , .size= MBYTE_BYTE(2), },
        {.valid=true, .code=MPU_REGION_SIZE_4MB    , .size= MBYTE_BYTE(4), },
        {.valid=true, .code=MPU_REGION_SIZE_8MB    , .size= MBYTE_BYTE(8), },
        {.valid=true, .code=MPU_REGION_SIZE_16MB   , .size= MBYTE_BYTE(16), },
        {.valid=true, .code=MPU_REGION_SIZE_32MB   , .size= MBYTE_BYTE(32), },
        {.valid=true, .code=MPU_REGION_SIZE_64MB   , .size= MBYTE_BYTE(64), },
        {.valid=true, .code=MPU_REGION_SIZE_128MB  , .size= MBYTE_BYTE(128), },
        {.valid=true, .code=MPU_REGION_SIZE_256MB  , .size= MBYTE_BYTE(256), },
        {.valid=true, .code=MPU_REGION_SIZE_512MB  , .size= MBYTE_BYTE(512), },
        {.valid=true, .code=MPU_REGION_SIZE_1GB    , .size=GBYTE_BYTE(1), },
        {.valid=true, .code=MPU_REGION_SIZE_2GB    , .size=GBYTE_BYTE(2), },
        {.valid=true, .code=MPU_REGION_SIZE_4GB    , .size=GBYTE_BYTE(4), },
#endif
};

static MpuRegionSizeInfo_t* MpuSizeToRegionSizeInfo(const uint32_t size) {
    MpuRegionSizeInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(SizeInfo);
    for(i = 0; i < cnt; i++) {
        if(size <= SizeInfo[i].size) {
            Info = &SizeInfo[i];
            break;
        }
    }
    return Info;
}

uint8_t MpuSizeToCortexRegionSize(const uint32_t size) {
    uint8_t cortex_reg_size = MPU_REGION_SIZE_32B;

    MpuRegionSizeInfo_t* Info = MpuSizeToRegionSizeInfo(size);
    if(Info) {
        cortex_reg_size = Info->code;
    }

    return cortex_reg_size;
}

static bool MpuIsValidRegion(const MpuRegionConfig_t* const Region) {
    bool res = false;
    if(Region) {
        res = true;
#if 0
        if(Region->num<=MPU_REGION_NUMBER15){
        } else {
            res = false;
            LOG_ERROR(LG_MPU, "TooBigRegionNumber:%u,Max:%u", Region->num,MPU_REGION_NUMBER15);
        }
#endif

        if(Region->size) {
        } else {
            res = false;
            LOG_ERROR(LG_MPU, "SizeNullErr:%u", Region->num);
        }

        if(Region->valid) {
        } else {
            res = false;
            LOG_ERROR(LG_MPU, "InValidErr:%u", Region->num);
        }

        if(Region->name) {
        } else {
            LOG_WARNING(LG_MPU, "NoName:%u", Region->num);
        }
    }
    return res;
}

static bool mpu_init_region(const MpuRegionConfig_t* const Region) {
    bool res = false;
    res = MpuIsValidRegion(Region);
    if(res) {
        LOG_INFO(LG_MPU, "%s", MpuRegionToStr(Region));
        MpuRegionSizeInfo_t* RegionSizeInfo = MpuSizeToRegionSizeInfo(Region->size);
        if(RegionSizeInfo) {
            LOG_INFO(LG_MPU, "%s", MpuRegionSizeInfoToStr(RegionSizeInfo));
            MPU_Region_InitTypeDef InitStruct = {0};

            InitStruct.AccessPermission = MpuPermissionToStm32Permission(Region->permission);
            InitStruct.Number = Region->num;

            InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
            InitStruct.BaseAddress = Region->start;
            InitStruct.Size = RegionSizeInfo->code;
            InitStruct.Enable = MpuRegionOnOffToEnable(Region->on_off);
            InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
            InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
            InitStruct.TypeExtField = MPU_TEX_LEVEL0;
            InitStruct.SubRegionDisable = 0x0;
            InitStruct.DisableExec = MpuPermissionToInstructionAccess(Region->permission);

            HAL_MPU_ConfigRegion(&InitStruct);
            res = true;
        }
    } else {
        LOG_ERROR(LG_MPU, "InvalidRegionErr");
    }
    return res;
}

static bool mpu_init_regions(const MpuHandle_t* const Node) {
    bool res = false;
    res = mpu_ctrl(Node->num, false);
    uint32_t cnt_ok = 0;
    uint32_t i = 0;
    for(i = 0; i < Node->region_cnt; i++) {
        res = mpu_init_region(&Node->Region[i]);
        log_res(LG_MPU, res, "InitRegion");
        cnt_ok = ok_cnt_update(cnt_ok, res);
    }

    if(cnt_ok == Node->region_cnt) {
        res = true;
    } else {
        res = false;
    }
    res = mpu_ctrl(Node->num, true);
    return res;
}

bool mpu_init_one(uint8_t num) {
    bool res = false;
    LOG_INFO(LG_MPU, "MPU%u,Init", num);
    const MpuConfig_t* Config = MpuGetConfig(num);
    if(Config) {
        log_level_get_set(LG_MPU, LOG_LEVEL_DEBUG);
        res = MpuIsValidConfig(Config);
        if(res) {
            LOG_WARNING(LG_MPU, "%s", MpuConfigToStr(Config));
            MpuHandle_t* Node = MpuGetNode(num);
            if(Node) {
                res = mpu_init_common(Config, Node);
                MpuInfo_t* Info = (MpuInfo_t*)MpuGetInfo(num);
                if(Info) {
                    LOG_INFO(LG_MPU, "Info:[%s]", MpuInfoToStr(Info));
                    Node->MPUx = Info->MPUx;
                    res = mpu_init_regions(Node);
                    log_res(LG_MPU, res, "InitRegions");
                    if(res) {
                        LOG_INFO(LG_MPU, "InitOk");
                        Node->init = true;
                    }
                } else {
                    LOG_ERROR(LG_MPU, "MPU%u,InstErr", num);
                }
            } else {
                LOG_ERROR(LG_MPU, "MPU%u,NodeErr", num);
            }
        }
    } else {
        LOG_DEBUG(LG_MPU, "MPU%u,ConfErr", num);
    }
    log_level_get_set(LG_MPU, LOG_LEVEL_INFO);
    return res;
}
