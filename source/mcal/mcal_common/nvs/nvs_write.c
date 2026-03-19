#include "nvs_write.h"

#include "compiler_const.h"
#include "flash_mcal.h"
#include "log.h"
#include "nvs_mcal.h"

_WEAK_FUN_
bool nvs_mcal_write(uint8_t num, const uint32_t addr, const uint8_t* const data, const uint32_t size) {
    bool res = false;
    LOG_DEBUG(NVS, "Write,Addr:0x%x,Size:%u", addr, size);
    res = is_nvs_addr_range(num, addr, size);
    if(res) {
        res = false;
#ifdef HAS_FLASH_WRITE
        res = flash_mcal_write(addr, data, size);
#else
        LOG_WARNING(LG_FLASH, "WriteProtected");
#endif
        if(res) {
            LOG_DEBUG(NVS, "Write,%u,Ok", size);
        } else {
            LOG_ERROR(NVS, "WriteErr");
        }
    } else {
        LOG_ERROR(NVS, "OutOfMem,Addr:0x%x,Size:%u", addr, size);
    }
    return res;
}

/*
  num - NVS instance number
  addr - physical address in microcontroller
  size - size to be cleaned
 */
_WEAK_FUN_
bool nvs_mcal_erase(uint8_t num, uint32_t address, uint32_t size) {
    bool res = false;
    const NvsConfig_t* Config = NvsGetConfig(num);
    if(Config) {
      //  if(size == Config->sector_size) {
            LOG_WARNING(NVS, "Errase,Addr:0x%x,Size:%u", address, size);
            res = is_nvs_addr_range(num, address, size);
            if(res) {
                res = false;
#ifdef HAS_FLASH_WRITE
                res = flash_mcal_erase(address, size);
                if(res) {
                    LOG_INFO(NVS, "ErraseOk,Addr:0x%x,Size:%u", address, size);
                } else {
                    LOG_ERROR(NVS, "ErraseErr,Addr:0x%x,Size:%u", address, size);
                }
#endif /**/
            } else {
                LOG_ERROR(NVS, "OutOfMem Addr:0x%x,Size:%u", address, size);
            }
            /*TODO: verify errase (FFFFF)*/
       // }
    }
    return res;
}

_WEAK_FUN_
bool nvs_errase_all(uint8_t num) {
    bool res = false;
    const NvsConfig_t* Config = NvsGetConfig(num);
    if(Config) {
        res = nvs_mcal_erase(num, Config->start, Config->size);
    }
    return res;
}
