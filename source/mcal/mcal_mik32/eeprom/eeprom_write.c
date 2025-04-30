#include "eeprom_write.h"

#include "bit_const.h"
#include "crc32.h"
#include "eeprom_custom_drv.h"
#include "eeprom_mcal.h"
#include "flash_custom_const.h"
#include "hal_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "mik32_hal_eeprom.h"
#include "time_mcal.h"

/*
https://mik32-amur.ru/EEPROM/index.html
*/

bool eeprom_dword_erase(const uint32_t phy_addr) {
    bool res = false;
    HAL_StatusTypeDef ret = HAL_ERROR;
    EepromHandle_t* Node = EepromGetNode(0);
    if(Node) {
        if(0 == (MASK_2BIT & phy_addr)) {
            LOG_DEBUG(EEPROM, "EraseDW,Addr:0x%08X", phy_addr);
            uint32_t eeprom_byte_address = (phy_addr - ROM_START);
            uint16_t eeprom_dword_address = eeprom_byte_address >> 2;
            ret = HAL_EEPROM_Erase(&(Node->handle), eeprom_dword_address, 1, HAL_EEPROM_WRITE_SINGLE,
                                   EEPROM_OPERATION_TIMEOUT);

            res = MIK32_HalRetToRes(ret);
        } else {
            LOG_DEBUG(EEPROM, "UalignedAddress,Addr:0x%08X", phy_addr);
        }
    }
    return res;
}

bool eeprom_mcal_erase(uint32_t phy_addr, uint32_t size) {
    bool res = false;
    EepromHandle_t* Node = EepromGetNode(0);
    res = eeprom_is_address_range(phy_addr, size);
    if(res) {
        LOG_DEBUG(EEPROM, "Erase:Addr:0x%08x,Size:%u", phy_addr, size);
        uint32_t eeprom_byte_address = (phy_addr - ROM_START);
        uint8_t erased_words_count = (uint8_t)size;
        uint16_t eeprom_dword_address = eeprom_byte_address >> 2;
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_EEPROM_Erase(&(Node->handle), eeprom_dword_address, erased_words_count, HAL_EEPROM_WRITE_SINGLE,
                               EEPROM_OPERATION_TIMEOUT);

        res = MIK32_HalRetToRes(ret);
    } else {
        LOG_ERROR(EEPROM, "ErrAddr:0x%08x", phy_addr);
    }
    return res;
}

bool eeprom_wait_bysy(const EEPROM_REGS_TypeDef* const EEPROMx) {
    bool res = false;
    bool loop = true;
    uint32_t start_ms = time_get_ms32();
    while(loop) {
        if(EEPROM_EESTA_BSY_IN_PROCCESS == EEPROMx->EESTA.BSY) {
            loop = false;
            res = true;
        } else {
            loop = time_wait_timeout(start_ms, 5000);
        }
    }
    return res;
}

#define DWORD_SIZE 4

bool eeprom_mcal_write(uint32_t phy_addr, uint8_t* wr_array, uint32_t size) {
    bool res = false;
    LOG_DEBUG(EEPROM, "Write:Addr:0x%08x,Size:%u", phy_addr, size);
    res = eeprom_is_address_range(phy_addr, size);
    if(res) {
        uint32_t eeprom_byte_address = (phy_addr - ROM_START);
        EepromHandle_t* Node = EepromGetNode(0);
        if(Node) {
            uint32_t dword_cnt = size / QWORD_LEN;
#if 0
            Node->EEPROMx->EECON.WRBEH = EEPROM_EECON_WRBEH_ORDINARY_ERASE ;
            Node->EEPROMx->EECON.BWE = EEPROM_EECON_BWE_BUFFER_WRITE_ENABLE;
            Node->EEPROMx->EECON.APBNWS  = 0 ;

            uint32_t i = 0;
            uint32_t* pDwords = (uint32_t* ) wr_array;
            for(i=0; i<cnt; i++) {
                Node->EEPROMx->EEA.ADDR = eeprom_address + i*DWORD_SIZE;
                Node->EEPROMx->EEDAT.DATA = pDwords[i];
            }

            Node->EEPROMx->EECON.OP = EEPROM_EECON_OPERATION_PROGRAM;
            Node->EEPROMx->EECON.WRBEH = EEPROM_EECON_WRBEH_ORDINARY_ERASE;
            Node->EEPROMx->EECON.EX = 1;
            res = eeprom_wait_bysy(Node->EEPROMx);

#endif
#if 1
            uint16_t eeprom_dword_address = eeprom_byte_address >> 2;
            HAL_StatusTypeDef ret = HAL_ERROR;
            ret = HAL_EEPROM_Write(&(Node->handle), eeprom_dword_address, (uint32_t*)wr_array, dword_cnt,
                                   HAL_EEPROM_WRITE_SINGLE, EEPROM_OPERATION_TIMEOUT);
            res = MIK32_HalRetToRes(ret);
#endif
        }
    } else {
        LOG_ERROR(EEPROM, "ErrAddr:0x%08x", phy_addr);
    }
    return res;
}

bool eeprom_dword_write(const uint32_t phy_addr, const uint32_t dword) {
    bool res = false;
    LOG_DEBUG(EEPROM, "WriteDword:Addr:0x%08x,Dword:0x%08x", phy_addr, dword);
    res = eeprom_is_address_range(phy_addr, QWORD_LEN);
    if(res) {
        EepromHandle_t* Node = EepromGetNode(0);
        if(Node) {
            uint32_t eeprom_byte_address = (phy_addr - ROM_START);
            uint16_t eeprom_dword_address = eeprom_byte_address >> 2;
            HAL_StatusTypeDef ret = HAL_ERROR;
            ret = HAL_EEPROM_Write(&(Node->handle), eeprom_dword_address, &dword, 1, HAL_EEPROM_WRITE_SINGLE,
                                   EEPROM_OPERATION_TIMEOUT);
            res = MIK32_HalRetToRes(ret);

            /*Errata for MIK32 SoC*/
            uint32_t rd_dword = 0;
            eeprom_dword_read(phy_addr + 4, &rd_dword);
        }
    } else {
        LOG_ERROR(EEPROM, "ErrAddr:0x%08x", phy_addr);
    }
    return res;
}

bool eeprom_dwords_write(uint32_t phy_addr, uint32_t* wr_array, uint32_t size) {
    bool res = false;
    LOG_DEBUG(EEPROM, "Write:Addr:0x%08x,Size:%u", phy_addr, size);
    res = eeprom_is_address_range(phy_addr, size);
    if(res) {
        EepromHandle_t* Node = EepromGetNode(0);
        if(Node) {
            uint32_t eeprom_byte_address = (phy_addr - ROM_START);
            uint16_t eeprom_dword_address = eeprom_byte_address >> 2;
            HAL_StatusTypeDef ret = HAL_ERROR;
            ret = HAL_EEPROM_Write(&(Node->handle), eeprom_dword_address, wr_array, size, HAL_EEPROM_WRITE_SINGLE,
                                   EEPROM_OPERATION_TIMEOUT);
            res = MIK32_HalRetToRes(ret);

            /*Errata for MIK32 SoC*/
            uint32_t rd_dword = 0;
            eeprom_dword_read(phy_addr + 4, &rd_dword);
        }
    } else {
        LOG_ERROR(EEPROM, "ErrAddr:0x%08x", phy_addr);
    }
    return res;
}

/*
  offset - relative address from start of EEPROM (0 means 0x01000000)
  data - data to write
  byte_size - size in bytes (4 .......1000)
  read_crc32 - read crc32
 */
bool eeprom_write_relative(const uint32_t offset, const uint8_t* const data, uint32_t byte_size, uint32_t read_crc32) {
    bool res = true;

    if(res) {
        if(data) {
            res = true;
        } else {
            LOG_ERROR(EEPROM, "NullData");
            res = false;
        }
    }

    if(res) {
        if(byte_size < 1000) {
            res = true;
        } else {
            LOG_ERROR(EEPROM, "ToBigSize");
            res = false;
        }
    }

    if(res) {
        if(byte_size) {
            res = true;
        } else {
            LOG_ERROR(EEPROM, "ZeroSize");
            res = false;
        }
    }

    if(res) {
        if(offset < (ROM_SIZE - byte_size)) {
            res = true;
        } else {
            LOG_ERROR(EEPROM, "TooBigOffSet,offset:%u", offset);
            res = false;
        }
    }

    if(res) {
        if(0 == (byte_size % 4)) {
            res = true;
        } else {
            LOG_ERROR(EEPROM, "UnAlignedSize,Size:%u", byte_size);
            res = false;
        }
    }

    if(res) {
        if(0 == (offset % 4)) {
            res = true;
        } else {
            LOG_ERROR(EEPROM, "UnAlignedAddress,Offset:0x%x", offset);
            res = false;
        }
    }

    if(res) {
        uint32_t calc_crc32 = crc32_calc(data, byte_size);
        if(calc_crc32 == read_crc32) {
            res = true;
        } else {
            LOG_ERROR(EEPROM, "ErrCRC:Calc:0x%08x,Read:0x%08x", calc_crc32, read_crc32);
            res = false;
        }
    }

    if(res) {
        EepromHandle_t* Node = EepromGetNode(0);
        if(Node) {
            uint32_t eeprom_byte_address = (offset + ROM_START);
            uint16_t eeprom_dword_address = eeprom_byte_address >> 2;
            uint8_t word_size = byte_size / 4;
            HAL_StatusTypeDef ret = HAL_ERROR;
            ret = HAL_EEPROM_Write(&(Node->handle), eeprom_dword_address, (uint32_t*)data, word_size,
                                   HAL_EEPROM_WRITE_SINGLE, EEPROM_OPERATION_TIMEOUT);
            res = MIK32_HalRetToRes(ret);
        }
    }
    return res;
}
