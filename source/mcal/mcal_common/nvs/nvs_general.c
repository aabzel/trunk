#include "nvs_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "flash_mcal.h"
#include "interval.h"
#include "log.h"

#ifdef HAS_CRC16
#include "crc16_ccitt.h"
#endif

COMPONENT_GET_NODE(Nvs, nvs)
COMPONENT_GET_CONFIG(Nvs, nvs)

bool is_nvs_addr_range(uint8_t num, uint32_t address, uint32_t size) {
    bool res = false;
    const NvsConfig_t *Config = NvsGetConfig(num);
    if (Config) {
        uint32_t nvs_end = Config->start + Config->size;
        IntervalE_t IntervalNvs = {.start = Config->start, .end = nvs_end};
        IntervalE_t IntervalData = {.start = address, .end = address + size};
        res = interval_is_a_in_b(&IntervalData, &IntervalNvs);
        if(false == res) {
            LOG_DEBUG(NVS, "Addr:0x%x,OutOfNvs,[0x%x...0x%x]", address, Config->start, nvs_end);
        }
    }
    return res;
}

#ifdef HAS_NVS_WRITE
_WEAK_FUN_
bool nvs_mcal_write(uint8_t num, const uint32_t addr, const uint8_t* const data, const uint32_t size) {
    bool res = false;
    LOG_DEBUG(NVS, "Write Addr:%x Size:%u", addr, size);
    res = is_nvs_addr_range(num, addr, size);
    if(res) {
        res = false;
#ifdef HAS_FLASH_WRITE
        res = flash_mcal_write(addr, data, size);
#else
        LOG_WARNING(LG_FLASH, "WriteProt");
#endif
        if(res) {
            LOG_DEBUG(NVS, "Write,%u,Ok", size);
        } else {
            LOG_ERROR(NVS, "WriteErr");
        }
    } else {
        LOG_ERROR(NVS, "OutOfMem Addr:%x Size: %u", addr, size);
    }
    return res;
}
#endif

#ifdef HAS_NVS_WRITE
_WEAK_FUN_
bool nvs_mcal_erase(uint8_t num, uint32_t addr, uint32_t size) {
    bool res = false;
    LOG_WARNING(NVS, "Errase Addr:%x Size:%u", addr, size);
    res = is_nvs_addr_range(num, addr, size);
    if(res) {
        res = false;
#ifdef HAS_FLASH_WRITE
        res = flash_mcal_erase(addr, size);
        if(res) {
            LOG_INFO(NVS, "ErraseOk Addr:%x Size: %u", addr, size);
        } else {
            LOG_ERROR(NVS, "ErraseErr Addr:%x Size: %u", addr, size);
        }
#endif /*HAS_FLASH_WRITE*/
    } else {
        LOG_ERROR(NVS, "OutOfMem Addr:%x Size: %u", addr, size);
    }
    /*TODO: verify errase (FFFFF)*/
    return res;
}
#endif /*HAS_NVS_WRITE*/

#ifdef HAS_NVS_WRITE
_WEAK_FUN_
bool nvs_errase_all(uint8_t num) {
    bool res = false;
    const NvsConfig_t* Config = NvsGetConfig(num);
    if(Config){
        res = nvs_mcal_erase(num, Config->start, Config->size);
    }
    return res;
}
#endif

_WEAK_FUN_
bool is_nvs_addr(uint8_t num, uint32_t address) {
    bool res = false;
    res = is_nvs_addr_range(num, address, 1);
    return res;
}

_WEAK_FUN_
bool nvs_mcal_read(uint8_t num, uint32_t address, uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(NVS, "Read,Addr:0x%x,Size:%u", address, size);
    res = is_nvs_addr_range(num, address, size);
    if(res) {
        res = flash_mcal_read(address, data, size);
        log_res(NVS, res, "Read");
    } else {
        LOG_ERROR(NVS, "OutOfMem Addr:0x%x,Size:%u", address, size);
    }
    return res;
}

_WEAK_FUN_
bool nvs_init_custom(void) {
    bool res = true;
    LOG_INFO(NVS, "Version:%s", NVS_VERSION);
    return res;
}

_WEAK_FUN_
uint16_t nvs_calc_crc16(uint8_t num) {
    uint16_t crc16_data = 0;
    const NvsConfig_t* Config = NvsGetConfig(num);
    if(Config) {
        crc16_data = calc_crc16_ccitt_false((uint8_t*)Config->start, Config->size);
    }
    return crc16_data;
}

static bool NvsIsValidConfig(const NvsConfig_t* const Config) {
    bool res = true;

    if(res) {
        if(Config) {
            res = true;
        } else {
            res = false;
        }


#if 0
        ifn(0 < Config->sector_size) {
            LOG_ERROR(NVS, "SectorSizeErr");
            res = false;
        }
#endif

        ifn(0 < Config->size) {
            LOG_ERROR(NVS, "SizeErr");
            res = false;
        }


        ifn(Config->name) {
            res = false;
            LOG_ERROR(NVS, "NVS%u NameErr", Config->num);
        }
        
        if (res) {
            res = is_flash_address_range(Config->start, Config->size);
            log_res(NVS, res, "CheckRange");
        }
    }

    return res;
}


bool nvs_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(NVS, "NVS_%u,Proc", num);
    NvsHandle_t* Node = NvsGetNode(num);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool nvs_init_common(const NvsConfig_t* const Config, NvsHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->start = Config->start;
            Node->size = Config->size;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}


_WEAK_FUN_
bool nvs_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(NVS, "NVS_%u", num);
    const NvsConfig_t* Config = NvsGetConfig(num);
    if(Config) {
        LOG_WARNING(NVS, "NVS%u", num);
        res = NvsIsValidConfig(Config);
        if(res) {
#ifdef HAS_NVS_DIAG
            LOG_WARNING(NVS, "%s", NvsConfigToStr(Config));
#endif
            NvsHandle_t* Node = NvsGetNode(num);
            if(Node) {
                res = nvs_init_common(Config, Node);
                Node->valid = true;
                Node->init = true;
#ifdef HAS_CRC16
                uint16_t crc16 = calc_crc16_ccitt_false((uint8_t*)Config->start, Config->size);
                LOG_INFO(NVS, "inSideOnChipFlash CRC16: 0x%04x", crc16);
#endif
                Node->spin = 0;
                LOG_INFO(NVS, "NVS%u,InitOk", num);
                res = true;
            } else {
                LOG_ERROR(NVS, "NVS%u,NodeErr", num);
            }
        } else {
            LOG_ERROR(NVS, "NVS%u,ConfigErr", num);
        }
    } else {
        LOG_PARN(NVS, "NVS%u,ConfigErr", num);
    }
    return res;
}



#if 0
_WEAK_FUN_
bool nvs_init(void) {
    LOG_WARNING(NVS, "Init");
    bool res = false;
    res = nvs_init_ll(&NvsConfig, &NvsItem);
    return res;
}
bool nvs_init(void) {
    LOG_WARNING(NVS, "Init");
    bool res = false;
#ifdef HAS_NVS_DIAG
    res = nvs_diag();
#endif

    NvsItem.start = Config->start;
    NvsItem.size = Config->size;
    NvsItem.valid = true;

    if(FlashInstance.start < (FlashInstance.start + FlashInstance.size)) {
        LOG_INFO(NVS, "StartEndOk");
        IntervalE_t IntervalFlash = {.start = FlashInstance.start, .end = FlashInstance.start + FlashInstance.size};
        uint32_t nvs_end = Config->start + Config->size;
        IntervalE_t IntervalNvs = {.start = Config->start, .end = nvs_end};
        res = intervals_overlaps(&IntervalNvs, &IntervalFlash);
        if(res) {
#ifdef HAS_CRC16
            uint16_t crc16_data = calc_crc16_ccitt_false((uint8_t*)Config->start, Config->size);
            LOG_INFO(NVS, "NSVinSideOnChipFlash CRC16: 0x%04x", crc16_data);
#endif
        } else {
            LOG_ERROR(NVS, "NSVoutSideOnChipFlash");
        }
    }

    return res;
}
#endif

COMPONENT_INIT_PATTERT(NVS, NVS, nvs)
COMPONENT_PROC_PATTERT(NVS, NVS, nvs)
