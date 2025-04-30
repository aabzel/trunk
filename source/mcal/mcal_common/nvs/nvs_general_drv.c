#include "nvs_drv.h"

#include "compiler_const.h"
#include "flash_mcal.h"
#include "interval.h"
#include "log.h"

#ifdef HAS_CRC16
#include "crc16_ccitt.h"
#endif

bool is_nvs_addr_range(uint32_t address, uint32_t size) {
    bool res = false;
    uint32_t nvs_end = NvsConfig.start + NvsConfig.size;
    IntervalE_t IntervalNvs = {.start = NvsConfig.start, .end = nvs_end};
    IntervalE_t IntervalData = {.start = address, .end = address + size};
    res = intervals_overlaps(&IntervalNvs, &IntervalData);
    return res;
}

#ifdef HAS_NVS_WRITE
_WEAK_FUN_
bool nvs_mcal_write(const uint32_t addr, const uint8_t* const data, const uint32_t size) {
    bool res = false;
    LOG_DEBUG(NVS, "Write Addr:%x Size:%u", addr, size);
    res = is_nvs_addr_range(addr, size);
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
bool nvs_erase(uint32_t addr, uint32_t size) {
    bool res = false;
    LOG_WARNING(NVS, "Errase Addr:%x Size:%u", addr, size);
    res = is_nvs_addr_range(addr, size);
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
bool nvs_errase_all(void) {
    bool res = false;
    res = nvs_erase(NvsConfig.start, NvsConfig.size);
    return res;
}
#endif

_WEAK_FUN_
bool nvs_mcal_read(uint32_t addr, uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(NVS, "Read,Addr:%x,Size:%u", addr, size);
    res = is_nvs_addr_range(addr, size);
    if(res) {
        res = flash_mcal_read(addr, data, size);
        log_res(NVS, res, "Read");
    } else {
        LOG_ERROR(NVS, "OutOfMem Addr:%x Size: %u", addr, size);
    }
    return res;
}

_WEAK_FUN_
bool is_nvs_addr(uint32_t address) {
    bool res = false;
    uint32_t nvs_end = NvsConfig.start + NvsConfig.size;
    if(NvsConfig.start <= address) {
        if(address < nvs_end) {
            res = true;
        }
    }
    if(false == res) {
        LOG_ERROR(NVS, "Addr:0x%x OutOfNvs [0x%x...0x%x]", address, NvsConfig.start, nvs_end);
    }
    return res;
}

_WEAK_FUN_
uint16_t nvs_calc_crc16(void) {
    uint16_t crc16_data = 0;
    crc16_data = calc_crc16_ccitt_false((uint8_t*)NvsConfig.start, NvsConfig.size);
    return crc16_data;
}

_WEAK_FUN_
bool nvs_init(void) {
    LOG_WARNING(NVS, "Init");
    bool res = false;
#ifdef HAS_NVS_DIAG
    res = nvs_diag();
#endif

    NvsItem.start = NvsConfig.start;
    NvsItem.size = NvsConfig.size;
    NvsItem.valid = true;

    if(FlashInstance.start < (FlashInstance.start + FlashInstance.size)) {
        LOG_INFO(NVS, "StartEndOk");
        IntervalE_t IntervalFlash = {.start = FlashInstance.start, .end = FlashInstance.start + FlashInstance.size};
        uint32_t nvs_end = NvsConfig.start + NvsConfig.size;
        IntervalE_t IntervalNvs = {.start = NvsConfig.start, .end = nvs_end};
        res = intervals_overlaps(&IntervalNvs, &IntervalFlash);
        if(res) {
#ifdef HAS_CRC16
            uint16_t crc16_data = calc_crc16_ccitt_false((uint8_t*)NvsConfig.start, NvsConfig.size);
            LOG_INFO(NVS, "NSVinSideOnChipFlash CRC16: 0x%04x", crc16_data);
#endif
        } else {
            LOG_ERROR(NVS, "NSVoutSideOnChipFlash");
        }
    }

    return res;
}
