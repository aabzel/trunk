#include "nor_flash_off_chip_api.h"

#include <string.h>

#include "data_types.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "time_mcal.h"
#include "utils_math.h"

#ifdef HAS_MX25R6435F
#include "mx25r6435f_drv.h"
#endif /*HAS_MX25R6435F*/

bool nor_flash_off_chip_read(uint32_t address, uint8_t* const data, uint32_t size) {
    bool res = false;
    if(data) {
        if(size) {
#ifdef HAS_MX25R6435F
            res = mx25r6435f_read(address, data, size);
#endif /*HAS_MX25R6435F*/
        }
    }

    return res;
}

bool nor_flash_off_chip_erase_chip(void) {
    bool res = false;
#ifdef HAS_MX25R6435F
    res = mx25r6435f_erase_chip();
#endif /*HAS_MX25R6435F*/
    return res;
}

bool nor_flash_off_chip_erase_block(uint32_t address, NorFlashBlockSize_t block_size) {
    bool res = false;
    if(block_size) {
#ifdef HAS_MX25R6435F
        res = mx25r6435f_erase_block(address, (Mx25BlockSize_t)block_size);
#endif /*HAS_MX25R6435F*/
    }
    return res;
}

bool nor_flash_off_chip_write(uint32_t address, const uint8_t* const data, uint32_t size) {
    bool res = false;

    if(data) {
        if(size) {
#ifdef HAS_MX25R6435F
            res = mx25r6435f_write(address, data, size);
#endif /*HAS_MX25R6435F*/
        }
    }

    return res;
}

bool nor_flash_off_chip_zero(uint32_t address, uint32_t size) {
    bool res = false;
    if(size) {
#ifdef HAS_MX25R6435F
        res = mx25r6435f_zero(address, size);
#endif /*HAS_MX25R6435F*/
    }
    return res;
}

bool nor_flash_off_chip_erase_mem(uint32_t address, uint32_t size) {
    bool res = false;
    if(size) {
#ifdef HAS_MX25R6435F
        res = mx25r6435f_erase_mem(address, size);
#endif /*HAS_MX25R6435F*/
    }
    return res;
}
