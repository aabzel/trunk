/**
 * NorFlash Memory manager
 * This file contains implementation of key-val(file) map in Nor-Flash with
 * uniform deterioration of Nor Flash memory
 *
 */
#include "flash_fs_ll.h"

#include <string.h>

#include "flash_fs.h"
#include "log.h"
#include "nvs_const.h"
#include "nvs_drv.h"
#include "std_includes.h"

/*
      write specified number of bytes to the flash (4 bytes aligned only)

      address    address - destination address, where data should be placed
      size   number of bytes that should be written (must be 4 bytes aligned)
      @retval   true-ok false-error
 */
#ifdef HAS_FLASH_FS_WRITE
bool flash_fs_write(const uint32_t address, const uint8_t* const data, const uint32_t size) {
    bool res = true;
    LOG_DEBUG(FLASH_FS, "Write Addr:0x%08x,Size:%u", address, size);
    res = nvs_mcal_write(address, data, size);
    if(false == res) {
        LOG_ERROR(NVS, "WriewErrAddr:0x%08x,Size:%u Byte", address, size);
    }
    return res;
}
#endif

#ifdef HAS_FLASH_FS_WRITE
#define MAX_FLASH_ZERO_SIZE 256
bool flash_fs_zero(uint32_t address, uint32_t len) {
    bool res = false;
    LOG_DEBUG(FLASH_FS, "Zero 0x%x Size:%u", address, len);
    uint8_t zeroArray[MAX_FLASH_ZERO_SIZE];
    if(len <= MAX_FLASH_ZERO_SIZE) {
        memset(zeroArray, 00, len);
        res = nvs_mcal_write(address, (uint8_t*)zeroArray, len);
    }
    return res;
}
#endif
