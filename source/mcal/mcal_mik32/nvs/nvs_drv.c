#include "nvs_drv.h"

#include <stddef.h>
#include <stdint.h>

#include "array_diag.h"
#include "bit_utils.h"
#include "data_utils.h"
#include "eeprom_mcal.h"
#include "flash_mcal.h"
#include "log.h"

bool nvs_erase_page(uint32_t flash_addr) {
    bool res = false;
    res = eeprom_bytes_erase(NvsConfig.start, NvsConfig.size);
    return res;
}

bool nvs_erase(uint32_t phy_addr, uint32_t size) {
    bool res = false;
    LOG_WARNING(NVS, "ErraseAddr:0x%08x,Size:%u", phy_addr, size);
    res = is_nvs_addr_range(phy_addr, size);
    if(res) {
        res = eeprom_bytes_erase(phy_addr, size);
        log_res(NVS, res, "EepromErase");
    } else {
        LOG_ERROR(NVS, "OutOfMem,Addr:%x,Size:%u", phy_addr, size);
    }
    /*TODO: verify errase (FFFFF)*/
    return res;
}

bool nvs_mcal_write(const uint32_t phy_addr, const uint8_t* const data, const uint32_t size) {
    bool res = false;
    // print_hex(data,size);
    res = is_nvs_addr_range(phy_addr, size);
    if(res) {
        res = eeprom_bytes_write(phy_addr, data, size);
        log_res(NVS, res, "EepromWrite");
    } else {
        LOG_ERROR(NVS, "OutOfMemAddr:%x,Size:%u", phy_addr, size);
    }
    return res;
}

bool nvs_mcal_read(uint32_t phy_addr, uint8_t* const array, uint32_t size) {
    bool res = false;
    LOG_DEBUG(NVS, "Read,Addr:%x,Size:%u", phy_addr, size);
    res = is_nvs_addr_range(phy_addr, size);
    if(res) {
        res = eeprom_bytes_read(phy_addr, array, size);
        log_res(NVS, res, "EepromRead");
    } else {
        LOG_ERROR(NVS, "OutOfMem,Addr:%x,Size:%u", phy_addr, size);
    }
    return res;
}
