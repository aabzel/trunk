#include "flash_drv.h"

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/zephyr.h>

#include "flash_diag.h"
#include "flash_types.h"
#include "log.h"
#include "zephyr_diag.h"

#ifdef HAS_FLASH_WRITE

bool flash_mcal_write(uint32_t addr, uint8_t* data, uint32_t size) {
    bool res = false;
    int ret = 0;
    LOG_DEBUG(LG_FLASH, "Write Addr:0x%x Size:%u", addr, size);
    if(FlashInstance.dev) {
        ret = flash_mcal_writeite(FlashInstance.dev, (off_t)addr, (const void*)data, size);
        if(0 == ret) {
            LOG_DEBUG(LG_FLASH, "WriteOk");
            res = true;
        } else {
            if(EINVAL == ret) {
                res = true;
            } else {
                LOG_ERROR(LG_FLASH, "WriteError %d=[%s]", ret, ErrNo2Str(ret));
                LOG_ERROR(LG_FLASH, "Addr:0x%x Size:%u", addr, size);
                res = false;
            }
        }
    } else {
        LOG_ERROR(LG_FLASH, "DevError");
    }
    /*Add read after write*/
    return res;
}

bool flash_mcal_writeite_dword(uint32_t addr, uint32_t* data, size_t size) {
    bool res = false;
    res = flash_mcal_write(addr, (uint8_t*)data, size);
    return res;
}

bool flash_mcal_erasepages(uint8_t page_start, uint8_t page_end) {
    bool res = false;
    LOG_ERROR(LG_FLASH, "%s", __FUNCTION__);
    return res;
}

bool flash_mcal_erasepage(uint32_t addr) {
    bool res = false;
    LOG_ERROR(LG_FLASH, "%s", __FUNCTION__);
    return res;
}

bool flash_mcal_eraseall(void) {
    bool res = false;
    LOG_ERROR(LG_FLASH, "%s", __FUNCTION__);
    return res;
}

bool flash_mcal_eraseblock(uint32_t phy_address, uint32_t block_size) {
    bool res = false;
    LOG_ERROR(LG_FLASH, "%s", __FUNCTION__);
    return res;
}

bool flash_mcal_erase(uint32_t addr, uint32_t size) {
    bool res = false;
    LOG_WARNING(LG_FLASH, "Erase Addr:0x%x Size:%u", addr, size);
    int ret = 0;
    if(FlashInstance.dev) {
        ret = flash_erase(FlashInstance.dev, (off_t)addr, (size_t)size);
        if(0 == ret) {
            LOG_DEBUG(LG_FLASH, "EraseOk");
            res = true;
        } else {
            LOG_ERROR(LG_FLASH, "EraseErr %d=[%s]", ret, ErrNo2Str(ret));
            LOG_ERROR(LG_FLASH, "Addr:0x%x Size:%u", addr, size);
            res = false;
        }
    }
    return res;
}
#endif /*HAS_FLASH_WRITE*/

bool flash_init(void) {
    bool res = false;
    LOG_WARNING(LG_FLASH, "Init..");

    FlashInstance.start = ROM_START;
    FlashInstance.size = ROM_SIZE;
    FlashInstance.end = ROM_END;
    FlashInstance.page_size = ON_CHIP_NOR_FLASH_APP_PAGE_SIZE;
    FlashInstance.page_cnt = ROM_SIZE / ON_CHIP_NOR_FLASH_APP_PAGE_SIZE;
    FlashInstance.crc16 = 0;

    FlashDiagNode(&FlashInstance);

    FlashInstance.dev = NULL;
    FlashInstance.dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_flash_controller));

    res = device_is_ready(FlashInstance.dev);
    if(res) {
        LOG_INFO(LG_FLASH, "Flash device [%s] ready", FlashInstance.dev->name);
        res = true;
        FlashInstance.init = true;
    } else {
        if(FlashInstance.dev->name) {
            LOG_ERROR(LG_FLASH, "Flash device [%s]  not ready", FlashInstance.dev->name);
        } else {
            LOG_ERROR(LG_FLASH, "Flash device not ready");
        }
        res = false;
    }

    return res;
}
