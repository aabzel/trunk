#include "sw_nor_flash.h"

#include <string.h>

#include "array_diag.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(SwNorFlash, sw_nor_flash)
COMPONENT_GET_CONFIG(SwNorFlash, sw_nor_flash)

bool sw_nor_flash_is_valid_addr(uint8_t num, uint32_t phy_address) {
    bool res = false;
    SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
    if(Node) {
        if(phy_address < Node->size) {
            res = true;
        }
    }
    return res;
}

uint8_t sw_nor_flash_read_byte(uint8_t num, uint32_t phy_address) {
    uint8_t byte = 0;
    SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
    if(Node) {
        if(Node->memory) {
            byte = Node->memory[phy_address];
        }
    }
    return byte;
}

bool sw_nor_flash_is_spare(uint8_t num, uint32_t phy_address, uint32_t size) {
    bool res = false;
    res = sw_nor_flash_is_valid_addr(num, phy_address);
    if(res) {
        uint32_t i = 0;
        uint32_t ok_cnt = 0;
        uint8_t rx_byte = 0;
        for(i = 0; i < size; i++) {
            rx_byte = sw_nor_flash_read_byte(num, phy_address + i);
            if(0xFF == rx_byte) {
                ok_cnt++;
            }
        }
        if(ok_cnt == size) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

static bool sw_nor_flash_verify_zero(uint8_t num, uint32_t phy_address, uint32_t size) {
    bool res = false;
    res = sw_nor_flash_is_valid_addr(num, phy_address);
    if(res) {
        uint32_t i = 0;
        uint32_t ok_cnt = 0;
        uint8_t rx_byte = 0;
        for(i = 0; i < size; i++) {
            rx_byte = sw_nor_flash_read_byte(num, phy_address + i);
            if(0x00 == rx_byte) {
                ok_cnt++;
            }
        }
        if(ok_cnt == size) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

static bool sw_nor_flash_erase_verify(uint8_t num, uint32_t phy_address, uint32_t size) {
    bool res = true;
    SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
    if(Node) {
        uint32_t i = 0;
        uint32_t cnt = 0;
        for(i = 0; i < size; i++) {
            if(FLASH_ERASE_PATTERN == Node->memory[i]) {
                cnt++;
            }
        }

        if(cnt == size) {
            res = true;
        }
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool SwNorFlashIsValidConfig(const SwNorFlashConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(res) {
            if(Config->name) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(SW_NOR_FLASH, "%u,NameErr", Config->num);
            }
        }

        if(res) {
            if(Config->block_size) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(SW_NOR_FLASH, "%u,block_size,Err", Config->block_size);
            }
        }

        if(res) {
            if(Config->sector_size) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(SW_NOR_FLASH, "%u,SectorSize,Err", Config->sector_size);
            }
        }

        if(res) {
            if(Config->memory) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(SW_NOR_FLASH, "%u,memory,Err", Config->memory);
            }
        }

        if(res) {
            if(Config->page_size) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(SW_NOR_FLASH, "%u,page_size,Err", Config->page_size);
            }
        }

        if(res) {
            if(Config->size) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(SW_NOR_FLASH, "%u,size,Err", Config->size);
            }
        }
    }
    return res;
}

bool sw_nor_flash_erase_chip(uint8_t num) {
    bool res = true;
    LOG_WARNING(SW_NOR_FLASH, "Chip:%u,EraseAll", num);
    SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
    if(Node) {
        if(Node->memory) {
            LOG_WARNING(SW_NOR_FLASH, "Erase,%u byte", Node->size);
            memset(Node->memory, FLASH_ERASE_PATTERN, Node->size);
            res = sw_nor_flash_erase_verify(num, 0, Node->size);
            log_info_res(SW_NOR_FLASH, res, "EraveVerify");
        }
    } else {
        LOG_ERROR(SW_NOR_FLASH, "NodeError");
    }
    return res;
}

bool sw_nor_flash_read(uint8_t num, uint32_t phy_address, uint8_t* const data, uint32_t size) {
    bool res = false;
    SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
    if(data) {
        if(size) {
            res = sw_nor_flash_is_valid_addr(num, phy_address);
            if(res) {
                if(Node) {
                    if(Node->memory) {
                        memcpy(data, &Node->memory[phy_address], size);
                        res = true;
                        // ArrayToStr(data, size)
                        LOG_DEBUG(SW_NOR_FLASH, "ReadAddr:0x%08X,%u,Size:%4u,byte,%s", phy_address, phy_address, size,
                                  ArrayToStr(data, size));
                    }
                } else {
                    LOG_ERROR(SW_NOR_FLASH, "%u,NodeErr", num);
                }
            } else {
                LOG_ERROR(SW_NOR_FLASH, "InvalidPhyAddress,%u=0x%08x", phy_address, phy_address);
            }
        }
    }

    if(res) {
        memcpy(data, &Node->memory[phy_address], size);
        res = true;
    }

    return res;
}
_WEAK_FUN_
bool sw_nor_flash_init_custom(void) {
    bool res = false;
    LOG_INFO(SW_NOR_FLASH, "Version:%s", SW_NOR_FLASH_VERSION);
    return res;
}

_WEAK_FUN_
bool sw_nor_flash_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(SW_NOR_FLASH, "Proc %u", i);
    SwNorFlashHandle_t* Node = SwNorFlashGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

_WEAK_FUN_
bool sw_nor_flash_init_common(const SwNorFlashConfig_t* const Config, SwNorFlashHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool sw_nor_flash_zero(uint8_t num, uint32_t phy_address, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SW_NOR_FLASH, "Zero,0x%08x=%u,Size:%u Byte", phy_address, phy_address, size);
    res = sw_nor_flash_is_valid_addr(num, phy_address);
    if(res) {
        SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
        if(Node) {
            if(Node->memory) {
                memset(&Node->memory[phy_address], 0, size);
                res = sw_nor_flash_verify_zero(num, phy_address, size);
            }
        }
    }
    return res;
}

bool sw_nor_flash_verify(uint8_t num, uint32_t phy_address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(NOR_FLASH, "Verify,Addr:%u,Size:%u", phy_address, size);
    res = sw_nor_flash_is_valid_addr(num, phy_address);
    if(res) {
        uint32_t ok_cnt = 0;
        uint8_t byte_read = 0xFF;
        SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
            byte_read = Node->memory[phy_address + i];
            if(byte_read == data[i]) {
                ok_cnt++;
            } else {
                LOG_ERROR(NOR_FLASH, "Verify,i=%u,Exp:0x%02x,Real:0x%02x", i, data[i], byte_read);
                break;
            }
        }

        if(size == ok_cnt) {
            res = true;
        } else {
            LOG_ERROR(NOR_FLASH, "VerifyErrAt,[%u]=0x%02x", i, data[i]);
            res = false;
        }
    }
    return res;
}

bool sw_nor_flash_write(uint8_t num, uint32_t phy_address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_NOTICE(SW_NOR_FLASH, "WriteAddr:0x%08x=%u,Size:%u Byte,Data:[%s]", phy_address, phy_address, size,
               ArrayToStr(data, size));
    res = sw_nor_flash_is_valid_addr(num, phy_address);
    if(res) {
        res = sw_nor_flash_is_spare(num, phy_address, size);
        if(res) {
        } else {
            LOG_ERROR(SW_NOR_FLASH, "NotSpare");
        }

        res = false;
        SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
        if(Node) {
            uint32_t i = 0;
            for(i = 0; i < size; i++) {
                Node->memory[phy_address + i] = data[i] & Node->memory[phy_address + i];
                res = true;
            }
            res = sw_nor_flash_verify(num, phy_address, data, size);
            if(false == res) {
                LOG_ERROR(SW_NOR_FLASH, "VeryfyError:0x%X,Size:%u", phy_address, size);
            } else {
                LOG_DEBUG(SW_NOR_FLASH, "VeryfyOk:0x%X,Size:%u", phy_address, size);
            }
        } else {
            LOG_ERROR(SW_NOR_FLASH, "NodeError");
        }
    }
    return res;
}

bool sw_nor_flash_erase_block(uint8_t num, uint32_t phy_address) {
    bool res = false;
    LOG_DEBUG(SW_NOR_FLASH, "EraseBlock,Addr:0x%x", phy_address);
    res = sw_nor_flash_is_valid_addr(num, phy_address);
    if(res) {
        res = false;
        SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
        if(Node) {
            if(Node->memory) {
                memset(&Node->memory[phy_address], FLASH_ERASE_PATTERN, Node->block_size);
                res = true;
            }
        } else {
            LOG_ERROR(SW_NOR_FLASH, "NodeError");
        }
    }
    return res;
}

bool sw_nor_flash_erase_sector(uint8_t num, uint32_t phy_address) {
    bool res = false;
    res = sw_nor_flash_is_valid_addr(num, phy_address);
    if(res) {
        res = false;
        SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
        if(res) {
            if(Node->memory) {
                memset(&Node->memory[phy_address], FLASH_ERASE_PATTERN, Node->sector_size);
                res = true;
            }
        }
    }
    return res;
}
/*
  Page Program (PP)
  (page 28 )Figure 12. Program/Erase flow with read array data
 * */
bool sw_nor_flash_page_program(uint8_t num, uint32_t phy_address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SW_NOR_FLASH, "PageProg,Addr:0x%08X,%4u byte", phy_address, size);
    res = sw_nor_flash_is_valid_addr(num, phy_address);
    if(res) {
        res = sw_nor_flash_is_spare(num, phy_address, size);
        if(res) {
            res = false;
            SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
            if(Node) {
                uint32_t i = 0;
                for(i = 0; i < size; i++) {
                    Node->memory[phy_address + i] = data[i] & Node->memory[phy_address + i];
                    res = true;
                }
            } else {
                LOG_ERROR(SW_NOR_FLASH, "NodeError");
            }
        } else {
            LOG_ERROR(SW_NOR_FLASH, "ReFriteError");
        }
    }
    return res;
}

bool sw_nor_flash_erase_mem(uint8_t num, uint32_t phy_address, uint32_t size) {
    bool res = false;
    uint32_t end = phy_address + size;
    LOG_WARNING(SW_NOR_FLASH, "Errase:[0x%08X;0x%08X],Size:%u Byte", phy_address, end, size);
    res = sw_nor_flash_is_valid_addr(num, phy_address);
    if(res) {
        res = false;
        SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
        if(Node) {
            if(Node->memory) {
                memset(&Node->memory[phy_address], FLASH_ERASE_PATTERN, size);
                res = true;
            }
        }
    }
    return res;
}

bool sw_nor_flash_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SW_NOR_FLASH, "Init:%u", num);
    const SwNorFlashConfig_t* Config = SwNorFlashGetConfig(num);
    if(Config) {
        res = SwNorFlashIsValidConfig(Config);
        if(res) {
#ifdef HAS_SW_NOR_FLASH_DIAG
            LOG_WARNING(SW_NOR_FLASH, "%s", SwNorFlashConfigToStr(Config));
#endif
            SwNorFlashHandle_t* Node = SwNorFlashGetNode(num);
            if(Node) {
                Node->re_record = Config->re_record;
                Node->name = Config->name;
                Node->sector_size = Config->sector_size;
                Node->page_size = Config->page_size;
                Node->block_size = Config->block_size;
                Node->memory = Config->memory;
                Node->size = Config->size;

                Node->valid = true;
                Node->init = true;
                res = sw_nor_flash_erase_chip(num);
            } else {
                LOG_ERROR(SW_NOR_FLASH, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(SW_NOR_FLASH, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(SW_NOR_FLASH, "ConfigErr %u", num);
    }
    set_log_level(SW_NOR_FLASH, LOG_LEVEL_INFO);
    return res;
}

COMPONENT_INIT_PATTERT(SW_NOR_FLASH, SW_NOR_FLASH, sw_nor_flash)
COMPONENT_PROC_PATTERT(SW_NOR_FLASH, SW_NOR_FLASH, sw_nor_flash)
