#include "flash_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>


bool flash_init(void) {
    bool res = true;
    return res;
}

bool flash_read(uint32_t in_flash_addr, uint8_t* rx_array, uint32_t array_len) {
    bool res = false;
    return res;
}

bool flash_scan(uint8_t* base, uint32_t size, float* usage_pec, uint32_t* spare, uint32_t* busy) {
    bool res = false;
    return res;
}

bool flash_mcal_write(uint32_t flash_addr, uint8_t* wr_array, uint32_t array_len) {
    bool res = false;
    return res;
}

bool is_errased(uint32_t addr, uint32_t size) {
    bool res = false;
    return res;
}

bool flash_mcal_erasesector(uint32_t sector_address) {
    bool res = false;
    return res;
}

bool is_flash_addr(uint32_t flash_addr) {
    bool res = false;
    return res;
}

bool is_addr_protected(uint32_t flash_addr) {
    bool res = false;
    return res;
}

/*
 Is there a continuously free block of given size starting at the flash_addr
 */
bool is_flash_spare(uint32_t flash_addr, uint32_t size) {
    return false;
}

uint32_t flash_get_first_spare_page(void) {
    return 0xFFFFFFFF;
}

/*
 * find the first address of spare continuous block of given size
 * returns the start address
 * */
bool flash_find_spare_region(uint32_t* out_addr, uint32_t size) {
    bool res = false;
    return res;
}

uint32_t flash_page2addr(uint8_t page) {
    uint32_t address = 0;
    return address;
}

bool flash_mcal_erasepages(uint8_t page_start, uint8_t page_end) {
    bool res = false;
    return res;
}
