#include "nor_flash_api.h"

#include <string.h>

#include "log.h"
#include "nor_flash_drv.h"

#ifdef HAS_NOR_FLASH_SW
#include "sw_nor_flash_drv.h"
#endif

#ifdef HAS_FLASH_OFF_CHIP
#include "nor_flash_off_chip_api.h"
#endif

#ifdef HAS_FLASH_ON_CHIP
#include "flash_drv.h"
#endif

bool nor_flash_read(uint8_t flash_num, uint32_t phy_address, uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(NOR_FLASH, "Read Addr %u=0x%08x Size %u byte", phy_address, phy_address, size);
    NorFlashItem_t* Node = NorFlashGetNode(flash_num);
    if(Node) {
        if(data) {
            if(size) {
                res = true;
            }
        }
    }
    if(res) {
        res = nor_flash_is_valid_addr(flash_num, phy_address);
        if(res) {
            res = false;
            switch(Node->option) {
#ifdef HAS_NOR_FLASH_SW
            case NOR_FLASH_OPTION_SW:
                res = sw_nor_flash_read(flash_num, phy_address, data, size);
                break;
#endif /*HAS_NOR_FLASH_SW*/

#ifdef HAS_FLASH_ON_CHIP
            case NOR_FLASH_OPTION_ON_CHIP:
                res = flash_read(phy_address, data, size);
                break;
#endif /*HAS_FLASH_ON_CHIP*/

#ifdef HAS_FLASH_OFF_CHIP
            case NOR_FLASH_OPTION_OFF_CHIP:
                res = nor_flash_off_chip_read(phy_address, data, size);
                break;
#endif /*HAS_FLASH_OFF_CHIP*/
            default:
                LOG_ERROR(NOR_FLASH, "NOR_FLASH%u UndefNORFlashOption %u", flash_num, Node->option);
                break;
            }
        } else {
            LOG_ERROR(NOR_FLASH, "InvalidPhyAddress %u=0x%08x", phy_address, phy_address);
        }
    }

    return res;
}

bool nor_flash_erase_sector(uint8_t flash_num, uint32_t phy_address) {
    bool res = false;
    NorFlashItem_t* Node = NorFlashGetNode(flash_num);
    if(Node) {
        res = nor_flash_is_valid_addr(flash_num, phy_address);
        if(res) {
            res = false;
            switch(Node->option) {
#ifdef HAS_NOR_FLASH_SW
            case NOR_FLASH_OPTION_SW:
                res = sw_nor_flash_erase_sector(flash_num, phy_address);
                break;
#endif
#ifdef HAS_FLASH_ON_CHIP
            case NOR_FLASH_OPTION_ON_CHIP:
                res = flash_erase_page(phy_address);
                break;
#endif
#ifdef HAS_FLASH_OFF_CHIP
            case NOR_FLASH_OPTION_OFF_CHIP:
                res = nor_flash_off_chip_erase_sector(phy_address);
                break;
#endif
            default:
                LOG_ERROR(NOR_FLASH, "UndefNORFlashOption %u", Node->option);
                break;
            }
        }
    }
    return res;
}

bool nor_flash_erase_chip(uint8_t flash_num) {
    bool res = true;
    LOG_WARNING(NOR_FLASH, "ErraseAll");
    NorFlashItem_t* Node = NorFlashGetNode(flash_num);
    if(Node) {
        switch(Node->option) {
#ifdef HAS_NOR_FLASH_SW
        case NOR_FLASH_OPTION_SW:
            res = sw_nor_flash_erase_chip(flash_num);
            break;
#endif
#ifdef HAS_FLASH_ON_CHIP
        case NOR_FLASH_OPTION_ON_CHIP:
            res = flash_erase_all();
            break;
#endif
#ifdef HAS_FLASH_OFF_CHIP
        case NOR_FLASH_OPTION_OFF_CHIP:
            res = nor_flash_off_chip_erase_chip();
            break;
#endif
        default:
            LOG_ERROR(NOR_FLASH, "UndefNORFlashOption %u", Node->option);
            res = false;
            break;
        }
        if(res) {

            res = nor_flash_erase_verify(flash_num, Node->start, Node->size);
            if(res) {
                LOG_INFO(NOR_FLASH, "ErraseOk");
            } else {
                LOG_WARNING(NOR_FLASH, "ErraseError");
            }
        }
    }
    return res;
}

bool nor_flash_erase_block(uint8_t flash_num, uint32_t phy_address, uint32_t block_size) {
    bool res = false;
    LOG_INFO(NOR_FLASH, "Addr %u Erase Block %u byte", phy_address, block_size);
    NorFlashItem_t* Node = NorFlashGetNode(flash_num);
    if(Node) {
        switch(Node->option) {
#ifdef HAS_NOR_FLASH_SW
        case NOR_FLASH_OPTION_SW:
            res = sw_nor_flash_erase_block(flash_num, phy_address, block_size);
            break;
#endif
#ifdef HAS_FLASH_ON_CHIP
        case NOR_FLASH_OPTION_ON_CHIP:
            res = flash_erase_block(phy_address, block_size);
            break;
#endif
#ifdef HAS_FLASH_OFF_CHIP
        case NOR_FLASH_OPTION_OFF_CHIP:
            res = nor_flash_off_chip_erase_block(phy_address, block_size);
            break;
#endif
        default:
            LOG_ERROR(NOR_FLASH, "UndefNORFlashOption %u", Node->option);
            break;
        }
        res = nor_flash_is_valid_addr(flash_num, phy_address);
        if(res) {
            res = false;
        }
    }
    return res;
}

bool nor_flash_write(uint8_t flash_num, uint32_t phy_address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(NOR_FLASH, "Write Addr 0x%08x=%u Size: %u Byte", phy_address, phy_address, size);
    NorFlashItem_t* Node = NorFlashGetNode(flash_num);
    if(Node) {
        if(size) {
            if(data) {
                res = nor_flash_is_valid_addr(flash_num, phy_address);
            }
        }
    }

    if(res) {
        switch(Node->option) {
#ifdef HAS_NOR_FLASH_SW
        case NOR_FLASH_OPTION_SW:
            res = sw_nor_flash_write(flash_num, phy_address, data, size);
            break;
#endif
#ifdef HAS_FLASH_ON_CHIP
        case NOR_FLASH_OPTION_ON_CHIP:
            res = flash_wr(phy_address, data, size);
            break;
#endif
#ifdef HAS_FLASH_OFF_CHIP
        case NOR_FLASH_OPTION_OFF_CHIP:
            res = nor_flash_off_chip_write(phy_address, data, size);
            break;
#endif
        default:
            LOG_ERROR(NOR_FLASH, "UndefNORFlashOption %u", Node->option);
            break;
        }
        res = nor_flash_verify(flash_num, phy_address, data, size);
        if(false == res) {
            LOG_ERROR(NOR_FLASH, "VeryfyError");
        }
    }
    return res;
}

bool nor_flash_zero(uint8_t flash_num, uint32_t phy_address, uint32_t size) {
    bool res = false;
    LOG_INFO(NOR_FLASH, "Zero 0x%08x=%u Size: %u Byte", phy_address, phy_address, size);
    NorFlashItem_t* Node = NorFlashGetNode(flash_num);
    if(Node) {
        switch(Node->option) {
#ifdef HAS_NOR_FLASH_SW
        case NOR_FLASH_OPTION_SW:
            res = sw_nor_flash_zero(flash_num, phy_address, size);
            break;
#endif

#ifdef HAS_FLASH_ON_CHIP
        case NOR_FLASH_OPTION_ON_CHIP:
            res = flash_zero(phy_address, size);
            break;
#endif

#ifdef HAS_FLASH_OFF_CHIP
        case NOR_FLASH_OPTION_OFF_CHIP:
            res = nor_flash_off_chip_zero(phy_address, size);
            break;
#endif
        default:
            LOG_ERROR(NOR_FLASH, "UndefNORFlashOption %u", Node->option);
            break;
        }
        res = nor_flash_is_valid_addr(flash_num, phy_address);
        if(res) {
            res = false;
            res = nor_flash_verify_zero(flash_num, phy_address, size);
        }
    }
    return res;
}

bool nor_flash_reset(uint8_t flash_num) {
    bool res = false;
    LOG_INFO(NOR_FLASH, "Reset");
    return res;
}

bool nor_flash_erase_mem(uint8_t flash_num, uint32_t phy_address, uint32_t size) {
    bool res = false;
    LOG_WARNING(NOR_FLASH, "Errase 0x%x...0x%x Size %u...", phy_address, phy_address + size, size);
    res = nor_flash_erase_verify(flash_num, phy_address, size);
    if(false == res) {
        NorFlashItem_t* Node = NorFlashGetNode(flash_num);
        if(Node) {
            switch(Node->option) {
#ifdef HAS_NOR_FLASH_SW
            case NOR_FLASH_OPTION_SW:
                res = sw_nor_flash_erase_mem(flash_num, phy_address, size);
                break;
#endif

#ifdef HAS_FLASH_ON_CHIP
            case NOR_FLASH_OPTION_ON_CHIP:
                res = flash_erase_mem(phy_address, size);
                break;
#endif

#ifdef HAS_FLASH_OFF_CHIP
            case NOR_FLASH_OPTION_OFF_CHIP:
                res = nor_flash_off_chip_erase_mem(phy_address, size);
                break;
#endif
            default:
                LOG_ERROR(NOR_FLASH, "UndefNORFlashOption %u", Node->option);
                break;
            }
            if(res) {
                res = nor_flash_erase_verify(flash_num, phy_address, size);
                if(res) {
                    LOG_WARNING(NOR_FLASH, "Errase 0x%x...0x%x Size %u Ok", phy_address, phy_address + size, size);
                } else {
                    LOG_ERROR(NOR_FLASH, "Errase 0x%x...0x%x Size %u Err", phy_address, phy_address + size, size);
                }
            }
        }
    } else {
        LOG_WARNING(NOR_FLASH, "AlreadyErrased 0x%x...0x%x Size %u Ok", phy_address, phy_address + size, size);
    }
    return res;
}
