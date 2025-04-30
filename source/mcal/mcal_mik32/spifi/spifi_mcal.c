#include "spifi_mcal.h"

#include <stddef.h>

#include "interrupt_mcal.h"
#include "mik32_hal_spifi.h"

#ifdef HAS_LED
#include "led_drv.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_MISCELLANEOUS
#include "data_utils.h"
#endif

#include "spifi_custom_drv.h"

#ifdef HAS_W25Q32JV
#include "mik32_hal_spifi_w25.h"
#include "w25q32jv_const.h"
#include "w25q32jv_registers_types.h"
#endif

#ifdef HAS_SPIFI_EXT

HAL_SPIFI_CacheEnableTypeDef SpiFiCacheCtrlToCacheEnable(bool cache_on_off) {
    HAL_SPIFI_CacheEnableTypeDef cache_enable = GPIO_PIN_LOW;
    switch((uint8_t)cache_on_off) {
    case false:
        cache_enable = SPIFI_CACHE_DISABLE;
        break;
    case true:
        cache_enable = SPIFI_CACHE_ENABLE;
        break;
    default:
        break;
    }
    return cache_enable;
}
#endif

static const SpiFiInfo_t SpiFiInfo[] = {
    {
        .num = 0,
        .irq_n = INT_NUM_SPIFI,
        .SPIFIx = SPIFI_CONFIG,
        .valid = true,
    },
};

SpiFiInfo_t* SpiFiGetInfo(uint8_t num) {
    SpiFiInfo_t* Node = NULL;
    uint32_t cnt = ARRAY_SIZE(SpiFiInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(num == SpiFiInfo[i].num) {
            if(SpiFiInfo[i].valid) {
                Node = &SpiFiInfo[i];
                break;
            }
        }
    }
    return Node;
}

static bool spifi_wait_intr_q(SPIFI_CONFIG_TypeDef* const SPIFIx, const uint32_t timeout_ms) {
    bool res = false;
    bool loop = true;
#ifdef HAS_TIME
    uint32_t start_ms = time_get_ms32();
#endif
    while(loop) {
        if(SPIFIx->STAT.intrq) {
            res = true;
            loop = false;
        } else {
#ifdef HAS_TIME
            loop = time_wait_timeout(start_ms, timeout_ms);
#endif
        }
    }
    return res;
}

bool spifi_read_reg(uint8_t num, uint8_t reg_code, uint8_t* const read_sreg) {
    bool res = false;
    // interrupt_disable();
    SpiFiHandle_t* Node = SpiFiGetNode(num);
    if(Node) {
        Node->SPIFIx->CTRL.inten = 1;
        Node->SPIFIx->STAT.intrq = SPIFI_STAT_INTRQ_RESET_QUERY; // Hang On here

        Node->SPIFIx->CMD.opcode = reg_code; // 0x05
        Node->SPIFIx->CMD.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_NOADDR;
        Node->SPIFIx->CMD.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
        Node->SPIFIx->CMD.datalen = 1;
        Node->SPIFIx->CMD.intlen = 0;
        // Node->SPIFIx->CMD.dout = SPIFI_CMD_DOUT_FLASH_READ;

        res = spifi_wait_intr_q(Node->SPIFIx, 10000);
        if(res) {
            *read_sreg = Node->SPIFIx->DATA.data8[0];
        }
    }
    // interrupt_enable();
    return res;
}

#ifdef HAS_SPIFI_EXT
/*see page 208 in datasheet*/
bool spifi_read(uint8_t num, uint32_t address, uint8_t* const data, uint32_t size) {
    bool res = false;
    SpiFiHandle_t* Node = SpiFiGetNode(num);
    if(Node) {
        Node->SPIFIx->ADDR = address;
        Node->SPIFIx->IDATA = 0;

        Node->SPIFIx->STAT.intrq = SPIFI_STAT_INTRQ_RESET_QUERY;

        Node->SPIFIx->CMD.intlen = 0; // ???
        Node->SPIFIx->CMD.opcode = W25Q32JV_READ_DATA;
        Node->SPIFIx->CMD.poll = SPIFI_CMD_POLL_NO;
        Node->SPIFIx->CMD.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_3ADDR;
        Node->SPIFIx->CMD.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
        Node->SPIFIx->CMD.dout = SPIFI_CMD_DOUT_FLASH_READ;
        Node->SPIFIx->CMD.datalen = size;
        // TODO Do It need pause?
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
            data[i] = Node->SPIFIx->DATA.data8[0];
            res = true;
        }
    }
    return res;
}
#endif

#ifdef HAS_SPIFI_WRITE

bool spifi_write(uint8_t num, uint32_t address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    SpiFiHandle_t* Node = SpiFiGetNode(num);
    if(Node) {
    }
    return res;
}
#endif

#ifdef HAS_SPIFI_WRITE
bool spifi_write_ctrl(const uint8_t num, bool on_off) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_SPIFI_WRITE
bool spifi_erase_sector(const uint8_t num, const uint32_t address) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_SPIFI_WRITE
bool spifi_write_enable(const uint8_t num) {
    bool res = false;
    SpiFiHandle_t* Node = SpiFiGetNode(num);
    if(Node) {
#ifdef HAS_LOG
        LOG_INFO(SPIFI, "SPIFI%u WriteEnable", num);
#endif

        Node->SPIFIx->STAT.intrq = SPIFI_STAT_INTRQ_RESET_QUERY;
        Node->SPIFIx->CMD.opcode = W25Q32JV_WRITE_ENABLE;
        Node->SPIFIx->CMD.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
        Node->SPIFIx->CMD.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_NOADDR;

        Node->SPIFIx->CMD.dout = SPIFI_CMD_DOUT_FLASH_WRITE;

        res = spifi_wait_intr_q(Node->SPIFIx, 2000);
    }
    return res;
}
#endif

#ifdef HAS_SPIFI_WRITE
/*
 Page Program (02h)
 num - instane of spifi (mainly 1)
 address= 24-bit address (A23-A0)
 wr_data - data to write
 size - in bytes
 */
bool spifi_page_program(const uint8_t num, const uint32_t address, const uint8_t* const wr_data, const uint32_t size) {
    bool res = false;
    SpiFiHandle_t* Node = SpiFiGetNode(num);
    if(Node) {
        if(size <= W25Q32JV_PAGE_SIZE) {
            Node->SPIFIx->STAT.intrq = SPIFI_STAT_INTRQ_RESET_QUERY;
            Node->SPIFIx->ADDR = address;
            Node->SPIFIx->IDATA = 0x00;
            Node->SPIFIx->CLIMIT = 0x00000000;

            Node->SPIFIx->CMD.opcode = W25Q32JV_PAGE_PROGRAM;
            Node->SPIFIx->CMD.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_3ADDR;
            Node->SPIFIx->CMD.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
            Node->SPIFIx->CMD.dout = SPIFI_CMD_DOUT_FLASH_WRITE;
            Node->SPIFIx->CMD.poll = SPIFI_CMD_POLL_NO;
            Node->SPIFIx->CMD.intlen = 0;
            Node->SPIFIx->CMD.datalen = size;

            uint32_t i = 0;
            uint32_t end_addr = address + size;
            for(i = address; i < end_addr; i++) {
                Node->SPIFIx->DATA.data8[0] = wr_data[i];
            }

            Node->SPIFIx->STAT.intrq = SPIFI_STAT_INTRQ_RESET_QUERY;
            res = true;
        }
    }
    return res;
}
#endif

bool spifi_reset(uint8_t num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(SPIFI, "%u Reset", num);
#endif
    SpiFiHandle_t* Node = SpiFiGetNode(num);
    if(Node) {
        Node->SPIFIx->STAT.reset = 1;
        res = true;
    }
    return res;
}

#ifdef HAS_SPIFI_EXT
bool spifi_chip_erase(uint8_t num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(SPIFI, "%u Start erase", num);
#endif
    SpiFiHandle_t* Node = SpiFiGetNode(num);
    if(Node) {
        Node->SPIFIx->STAT.intrq = SPIFI_STAT_INTRQ_RESET_QUERY;
        Node->SPIFIx->CMD.opcode = W25Q32JV_CHIP_ERASE_2;
        Node->SPIFIx->CMD.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_NOADDR;
        Node->SPIFIx->CMD.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
        res = spifi_wait_intr_q(Node->SPIFIx, 5000);
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_SPIFI_EXT
bool spifi_proc_one(uint8_t num) {
    bool res = false;
    SpiFiHandle_t* Node = SpiFiGetNode(num);
    if(Node) {
        if(!Node->SPIFIx) {
#ifdef HAS_LOG
            LOG_ERROR(SPIFI, "%u SPIFIxNull", num);
#endif
        }

        SpiFiRegStat_t Stat;
        Stat.dword = Node->SPIFIx->STAT.dword;
        if(Stat.cmd) {
#ifdef HAS_LOG
            LOG_INFO(SPIFI, "%u CmdRegWrOK", num);
#endif
        }

#ifdef HAS_W25Q32JV
        W25q32jvRegStatus_t RegStatus;
        RegStatus.byte = 0;
        res = spifi_read_reg(num, W25Q32JV_READ_SREG1, &RegStatus.byte);
        if(res) {
            if(RegStatus.busy) {
#ifdef HAS_LOG
                LOG_INFO(SPIFI, "%u busy", num);
#endif
            }
        }
#endif
    }
    return res;
}
#endif

#ifdef HAS_SPIFI_EXT
bool spifi_is_address(const uint32_t phy_address) {
    bool res = false;
    if(EXT_ROM_START <= phy_address) {
        if(phy_address < EXT_ROM_END) {
            res = true;
        }
    }
    return res;
}
#endif

#ifdef HAS_SPIFI_EXT
bool SpiFiIsValidConfig(const SpiFiConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(Config->cache_on_off) {
            if(Config->cache_limit) {
                res = true;
            } else {
                res = false;
            }
        }
    }
    return res;
}
#endif

bool spifi_init_one(uint8_t num) {
    bool res = false;
    // PM->CLK_AHB_SET.dword = PM_CLOCK_AHB_SPIFI_M;
    //	led_mono_ctrl(  2, true);
    const SpiFiConfig_t* Config = SpiFiGetConfig(num);
    if(Config) {
    	res = true;
#ifdef HAS_SPIFI_EXT
        res = SpiFiIsValidConfig(Config);
#endif
        if(res) {
            SpiFiInfo_t* Info = SpiFiGetInfo(num);
            if(Info) {
                SpiFiHandle_t* Node = SpiFiGetNode(num);
                if(Node) {
                    Node->SPIFIx = Info->SPIFIx;
                    Node->Handle.Instance = Info->SPIFIx;
                    Node->irq_n = Info->irq_n;

                    // HAL_SPIFI_MspInit();
                    HAL_SPIFI_Reset(&Node->Handle);

                } else {
#ifdef HAS_LOG
                    LOG_ERROR(SPIFI, "%u NodeErr", num);
#endif
                }
            }
        }
    } else {
#ifdef HAS_LOG
        LOG_DEBUG(SPIFI, "%u ConfErr", num);
#endif
    }
    return res;
}
