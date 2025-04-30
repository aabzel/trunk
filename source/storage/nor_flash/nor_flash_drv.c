#include "nor_flash_drv.h"

#include <string.h>

#ifdef HAS_CRC16
#include "crc16_ccitt.h"
#endif
#include "log.h"
#include "nor_flash_api.h"
#include "nor_flash_diag.h"

NorFlashItem_t* NorFlashGetNode(uint8_t num) {
    NorFlashItem_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = nor_flash_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == NorFlashItem[i].num) {
            if(NorFlashItem[i].valid) {
                Node = &NorFlashItem[i];
                break;
            }
        }
    }
    return Node;
}

const NorFlashConfig_t* NorFlashGetConfig(uint8_t num) {
    const NorFlashConfig_t* Config = NULL;
    uint32_t i = 0;
    uint32_t nor_flash_cnt = nor_flash_get_cnt();
    for(i = 0; i < nor_flash_cnt; i++) {
        if(num == NorFlashConfig[i].num) {
            if(NorFlashConfig[i].valid) {
                Config = &NorFlashConfig[i];
                break;
            }
        }
    }
    return Config;
}

bool nor_flash_is_valid_addr(uint8_t num, uint32_t phy_address) {
    bool res = false;
    const NorFlashConfig_t* Config = NorFlashGetConfig(num);
    if(Config) {
        if(Config->start <= phy_address) {
            if(phy_address < (Config->start + Config->size)) {
                res = true;
            }
        }
    }
    return res;
}

uint8_t nor_flash_read_byte(uint8_t flash_num, uint32_t phy_address) {
    uint8_t data = 0x00;
    bool res = nor_flash_is_valid_addr(flash_num, phy_address);
    if(res) {
        nor_flash_read(flash_num, phy_address, &data, 1);
    }
    return data;
}

uint16_t nor_flash_calc_crc16(uint8_t flash_num, uint32_t phy_address, uint32_t size) {
    bool res = false;
    res = nor_flash_is_valid_addr(flash_num, phy_address);
    uint16_t crc16f = INIT_VALUE;
    if(res) {

        uint32_t i = 0u;
        uint8_t rx_byte = 0;
        uint8_t tabInd = 0;
        for(i = 0u; i < size; i++) {
            rx_byte = nor_flash_read_byte(flash_num, phy_address + i);
            tabInd = (uint8_t)(crc16f >> 8U) ^ rx_byte;
            crc16f = ((uint16_t)(crc16f << 8U)) ^ crc16LookUpTable[tabInd];
        }
    }
    return crc16f;
}

bool nor_flash_verify(uint8_t flash_num, uint32_t phy_address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(NOR_FLASH, "Verify Addr:%u size:%u", phy_address, size);
    res = nor_flash_is_valid_addr(flash_num, phy_address);
    if(res) {

        uint32_t i = 0;
        uint32_t ok_cnt = 0;
        uint8_t byte_read = 0xFF;
        for(i = 0; i < size; i++) {
            res = nor_flash_read(flash_num, phy_address + i, &byte_read, 1);
            if(res) {
                if(data[i] == byte_read) {
                    ok_cnt++;
                } else {
                    LOG_ERROR(NOR_FLASH, "Verify i=%u Exp:0x%x Real:0x%x", i, data[i], byte_read);
                    break;
                }
            }
        }

        if(size == ok_cnt) {
            res = true;
        } else {
            LOG_ERROR(NOR_FLASH, "VerifyErrAt [%u]=0x%02x", i, data[i]);
            res = false;
        }
    }
    return res;
}

bool nor_flash_write_lazy(uint8_t flash_num, uint32_t phy_address, const uint8_t* const data, uint32_t size) {
    LOG_DEBUG(NOR_FLASH, "WriteLazy Addr:%u size:%u", phy_address, size);
    bool res = nor_flash_verify(flash_num, phy_address, data, size);
    if(false == res) {
        res = nor_flash_write(flash_num, phy_address, data, size);
    } else {
        LOG_DEBUG(NOR_FLASH, "AlreadyTheSame");
    }
    return res;
}

bool nor_flash_erase_verify(uint8_t flash_num, uint32_t phy_address, uint32_t size) {
    bool res = false;
    LOG_DEBUG(NOR_FLASH, "EraseVerify 0x%x size %u", phy_address, size);
    res = nor_flash_is_valid_addr(flash_num, phy_address);
    if(res) {
        uint32_t i = 0;
        uint32_t ok_cnt = 0;
        uint8_t read_data = 0;
        for(i = 0; i < size; i++) {
            res = nor_flash_read(flash_num, phy_address + i, &read_data, 1);
            if(res) {
                if(0xFF == read_data) {
                    ok_cnt++;
                } else {
                    LOG_ERROR(NOR_FLASH, "Byte %u, EraseVerifyError, Val:0x%02x", i, read_data);
                    res = false;
                    break;
                }
            }
        }

        if(ok_cnt == size) {
            res = true;
        } else {
            LOG_ERROR(NOR_FLASH, "EraseVerifyError");
            res = false;
        }
    }
    return res;
}

bool nor_flash_is_spare_chunk(uint8_t flash_num, uint32_t phy_address, uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    uint8_t read_data = 0;
    for(i = 0; i < size; i++) {
        read_data = 0;
        res = nor_flash_read(flash_num, phy_address + i, &read_data, 1);
        if(res) {
            if(0xFF == read_data) {
                ok_cnt++;
            }
        }
    }

    if(ok_cnt == size) {
        res = true;
    } else {
        res = true;
    }

    return res;
}

bool nor_flash_memmove(uint8_t flash_num, uint32_t from_phy_address, uint32_t to_phy_address, uint32_t size) {
    bool res = false;
    LOG_INFO(NOR_FLASH, "MemMobe FromAddr 0x%08x->ToAddr 0x%08x Size: %u Byte", from_phy_address, to_phy_address, size);
    res = nor_flash_is_spare_chunk(flash_num, to_phy_address, size);
    if(res) {
        uint8_t buff[128];
        memset(buff, 0xFF, sizeof(buff));
        uint32_t cnt_block = size / sizeof(buff);
        uint32_t remainder = size % sizeof(buff);
        uint32_t move_cnt = 0;

        uint32_t i = 0;
        for(i = 0; i < cnt_block; i++) {
            res = nor_flash_read(flash_num, from_phy_address + i * sizeof(buff), buff, sizeof(buff));
            if(res) {
                res = nor_flash_write(flash_num, to_phy_address + i * sizeof(buff), buff, sizeof(buff));
                if(res) {
                    move_cnt += sizeof(buff);
                }
            }
        }

        if(remainder) {
            res = nor_flash_read(flash_num, from_phy_address + cnt_block * sizeof(buff), buff, remainder);
            if(res) {
                res = nor_flash_write(flash_num, to_phy_address + cnt_block * sizeof(buff), buff, remainder);
                if(res) {
                    move_cnt += remainder;
                }
            }
        }

        if(move_cnt == size) {
            res = true;
        } else {
            res = true;
        }
    } else {
        LOG_ERROR(NOR_FLASH, "NotFreeFlashChanj Addr 0x%08x Size: %u Byte", to_phy_address, size);
    }
    return res;
}

bool nor_flash_verify_zero(uint8_t flash_num, uint32_t phy_address, uint32_t size) {
    bool res = false;
    res = nor_flash_is_valid_addr(flash_num, phy_address);
    if(res) {
        uint32_t i = 0;
        uint32_t ok_cnt = 0;
        uint8_t rx_byte = 0;
        for(i = 0; i < size; i++) {
            rx_byte = nor_flash_read_byte(flash_num, phy_address + i);
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

bool nor_flash_scan(uint8_t flash_num, uint32_t phy_address, uint32_t size, double* usage_pec, uint32_t* spare,
                    uint32_t* busy) {
    bool res = false;
    uint8_t buff[256];
    if(usage_pec && spare && busy) {
        res = true;
        uint32_t i = 0;
        *spare = 0;
        *busy = 0;

        uint32_t chunk = size / sizeof(buff);
        uint32_t rem = size % sizeof(buff);
        uint32_t c = 0;
        for(c = 0; c < chunk; c++) {
            res = nor_flash_read(flash_num, phy_address + c * sizeof(buff), buff, sizeof(buff));
            if(res) {
                for(i = 0; i < sizeof(buff); i++) {

                    if(0xFF == buff[i]) {
                        (*spare)++;
                    } else {
                        (*busy)++;
                    }
                }
            }
        }

        res = nor_flash_read(flash_num, phy_address + chunk * sizeof(buff), buff, rem);
        if(res) {
            for(i = 0; i < rem; i++) {
                if(0xFF == buff[i]) {
                    (*spare)++;
                } else {
                    (*busy)++;
                }
            }
        }

        *usage_pec = (double)(((double)(100U * (*busy))) / ((double)size));
    }
    return res;
}

bool nor_flash_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(NOR_FLASH, "Init One %u", num);
    const NorFlashConfig_t* Config = NorFlashGetConfig(num);
    if(Config) {
        NorFlashItem_t* Node = NorFlashGetNode(num);
        if(Node) {
            LOG_INFO(NOR_FLASH, "%u->%s", num, NorFlashOption2Str(Config->option));
            LOG_INFO(NOR_FLASH, "%u 0x%08x....0x%08x Size:%u byte", num, Config->start, Config->start + Config->size,
                     Config->size);
            Node->valid = true;
            Node->option = Config->option;
            Node->start = Config->start;
            Node->size = Config->size;
            Node->valid = Config->valid;
            Node->num = Config->num;
            Node->memory = Config->memory;
            if(Config->CustomInit) {
                res = Config->CustomInit(num);
                if(res) {
                    Node->init = true;
                }
            } else {
                res = true;
            }
        }
    }

    return res;
}

bool nor_flash_init(void) {
    bool res = false;
    set_log_level(NOR_FLASH, LOG_LEVEL_INFO);
    uint32_t cnt = nor_flash_get_cnt();
    LOG_WARNING(NOR_FLASH, "Init Cnt:%u", cnt);
    uint32_t i = 0;
    uint32_t ok_cnt = 0;

    for(i = 0; i <= cnt; i++) {
        res = nor_flash_init_one(i);
        if(res) {
            ok_cnt++;
        }
    }

    if(ok_cnt) {
        res = true;
        LOG_INFO(NOR_FLASH, "InitOk Cnt:%u", ok_cnt);
    } else {
        res = false;
        LOG_ERROR(NOR_FLASH, "InitErr");
    }

    set_log_level(NOR_FLASH, LOG_LEVEL_INFO);
    return res;
}
