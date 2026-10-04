#include "gd5f1gq5_mcal.h"

#include "array_diag.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "crc16_ibm.h"
#include "data_types.h"
#include "gpio_mcal.h"
#include "log.h"
#include "spi_mcal.h"
#include "time_mcal.h"

uint32_t gd5f1gq5_address_to_page_num(uint32_t address) {
    uint32_t page_num = 0;
    page_num = address / GD5F1GQ5_PAGE_SIZE;
    LOG_DEBUG(GD5F1GQ5, "address:%u->PageN:%u", address, page_num);
    return page_num;
}

uint32_t gd5f1gq5_page_to_block(const uint32_t page_num) {
    uint32_t block_num = 0;
    block_num = page_num / GD5F1GQ5_PAGES_PER_BLOCK;
    LOG_DEBUG(GD5F1GQ5, "PageN:%u->BlockN:%u", page_num, block_num);
    return block_num;
}

uint32_t gd5f1gq5_address_to_block_num(uint32_t address) {
    uint32_t page_num = gd5f1gq5_address_to_page_num(address);
    uint32_t block_num = gd5f1gq5_page_to_block(page_num);
    return block_num;
}

static bool gd5f1gq5_proc_status_c0(Gd5f1gq5Handle_t* const Node) {
    bool res = false;
    if(Node) {
        if(Node->StatusC0.E_FAIL) {
            LOG_ERROR(GD5F1GQ5, "N:%u,EraseFail", Node->num);
            Node->error_cnt++;
        }
        if(Node->StatusC0.P_FAIL) {
            LOG_ERROR(GD5F1GQ5, "N:%u,ProgramFail", Node->num);
            Node->error_cnt++;
        }

        if(Node->StatusC0.OIP) {
            LOG_WARNING(GD5F1GQ5, "N:%u,OperationInProgress", Node->num);
        }

        if(0 == Node->StatusC0.WEL) {
            LOG_WARNING(GD5F1GQ5, "N:%u,WriteDisable", Node->num);
        }

        LOG_DEBUG(GD5F1GQ5, "N:%u,ECC:%u", Node->num, Node->StatusC0.ECCS);
    }
    return res;
}

static Gd5f1gq5Command_t WriteONoffToOpCode(const bool on_off) {
    Gd5f1gq5Command_t op_code = GD5F_CMD_UNDEF;
    if(on_off) {
        op_code = GD5F_CMD_WRITE_ENABLE;
    } else {
        op_code = GD5F_CMD_WRITE_DISABLE;
    }
    return op_code;
}

#if 0

typedef bool (*CallBack_t)(void);
/* */
bool gd5f1gq5_chip_select_callback( Gd5f1gq5Handle_t* Node, const CallBack_t * const  CallBack) {
    bool res = false;
    if(Node){
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        wait_us(1);
        CallBack();
        wait_us(1);
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);

    }
    return res;
}
#endif

COMPONENT_GET_NODE(Gd5f1gq5, gd5f1gq5)
COMPONENT_GET_CONFIG(Gd5f1gq5, gd5f1gq5)

const Gd5f1gq5RegInfo_t Gd5f1gq5RegInfo[] = {
    {
        .valid = true,
        .regParserCallBack = Gd5f1gq5RegProtectionToStr,
        .reg_addr = 0xA0,
        .reg_name = "Protection",
    },
    {
        .valid = true,
        .regParserCallBack = Gd5f1gq5RegFeatureB0ToStr,
        .reg_addr = 0xB0,
        .reg_name = "FeatureB",
    },
    {
        .valid = true,
        .regParserCallBack = Gd5f1gq5RegStatusC0ToStr,
        .reg_addr = 0xC0,
        .reg_name = "StatusC",
    },
    {
        .valid = true,
        .regParserCallBack = Gd5f1gq5RegDriverStrengthToStr,
        .reg_addr = 0xD0,
        .reg_name = "FeatureD",
    },
    {
        .valid = true,
        .regParserCallBack = Gd5f1gq5RegStatusF0ToStr,
        .reg_addr = 0xF0,
        .reg_name = "StatusF",
    },
};

Gd5f1gq5RegInfo_t* Gd5f1gq5RegAddrToInfo(const uint8_t reg_addr) {
    uint32_t i = 0;
    Gd5f1gq5RegInfo_t* Info = NULL;
    uint32_t cnt = ARRAY_SIZE(Gd5f1gq5RegInfo);
    for(i = 0; i < cnt; i++) {
        if(reg_addr == Gd5f1gq5RegInfo[i].reg_addr) {
            if(Gd5f1gq5RegInfo[i].valid) {
                Info = &Gd5f1gq5RegInfo[i];
                break;
            }
        }
    }
    return Info;
}

/*
 8.3 Read From Cache (03H or 0BH)
 column_address - address of the byte
 */
bool gd5f1gq5_read_from_cache(const uint8_t num, const uint32_t column_address, uint8_t* const data,
                              const uint32_t size) {
    bool res = false;
    LOG_DEBUG(GD5F1GQ5, "ReadFormCache:N:%u,ColumnAddr:0x%06x,SZ:%u", num, column_address, size);
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        if(Node->init) {
            gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
            wait_us(1);
            Gd5f1gq5CacheAddress32_t Address32;
            Address32.dword = 0xFFFFFFFF;
            Address32.addr = column_address;
            uint8_t tx_array[4] = {GD5F_CMD_READ_FROM_CACHE, Address32.buff[2], Address32.buff[1], Address32.buff[0]};
            res = spi_mcal_write(Node->spi_num, tx_array, 4);
            res = spi_mcal_read(Node->spi_num, data, size);
            wait_us(1);
            gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
        }
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool Gd5f1gq5IsValidConfig(const Gd5f1gq5Config_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(GD5F1GQ5, "%u,Name,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool gd5f1gq5_init_custom(void) {
    bool res = false;
    LOG_INFO(GD5F1GQ5, "Version:%u", GD5F1GQ5_VERSION);
    LOG_INFO(GD5F1GQ5, "PAGE_SIZE:%u  Byte", GD5F1GQ5_PAGE_SIZE);
    LOG_INFO(GD5F1GQ5, "PAGES_PER_BLOCK:%u", GD5F1GQ5_PAGES_PER_BLOCK);
    LOG_INFO(GD5F1GQ5, "PAGE_COUNT:%u", GD5F1GQ5_PAGE_COUNT);
    LOG_INFO(GD5F1GQ5, "BLOCK_SIZE:%u Byte", GD5F1GQ5_BLOCK_SIZE);
    LOG_INFO(GD5F1GQ5, "TOTAL_SIZE:%u Byte", GD5F1GQ5_TOTAL_SIZE);
    return res;
}

bool gd5f1gq5_proc_one(const uint8_t num) {
    bool res = false;
    LOG_PARN(GD5F1GQ5, "Proc:%u", num);
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        Node->spin++;
        res = gd5f1gq5_get_features(num, GD5F1GQ5_REG_PROTECTION_A0H, &Node->Protection.byte);
        res = gd5f1gq5_get_features(num, GD5F1GQ5_REG_FEATURE_B0H, &Node->FeatureB0.byte);
        res = gd5f1gq5_get_features(num, GD5F1GQ5_REG_FEATURE_D0H, &Node->DriverStrength.byte);
        res = gd5f1gq5_get_features(num, GD5F1GQ5_REG_STATUS_F0H, &Node->StatusF0.byte);

        res = gd5f1gq5_get_features(num, GD5F1GQ5_REG_STATUS_C0H, &Node->StatusC0.byte);
        if(res) {
            res = gd5f1gq5_proc_status_c0(Node);
        }
    }
    return res;
}

bool gd5f1gq5_init_common(const Gd5f1gq5Config_t* const Config, Gd5f1gq5Handle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->spi_num = Config->spi_num;
            Node->chip_select = Config->chip_select;
            res = true;
        }
    }
    return res;
}

bool gd5f1gq5_init_node(Gd5f1gq5Handle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->valid = true;
        Node->init = true;
        res = true;
    }
    return res;
}

/* 8.9 Read ID (9FH)
Figure 8-8. Read ID Sequence Diagram */
bool gd5f1gq5_read_id(const uint8_t num, Gd5f1gq5ID_t* const pID) {
    bool res = false;
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        if(pID) {
            gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
            wait_us(1);
            uint8_t tx_array[2] = {GD5F_CMD_READ_ID, 0};
            res = spi_mcal_write(Node->spi_num, tx_array, 2);
            res = spi_mcal_read(Node->spi_num, pID->buff, 2) && res;
            wait_us(1);
            gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
            LOG_DEBUG(GD5F1GQ5, "%s", Gd5f1gq5IdToStr(pID));
        }
    }
    return res;
}

/*8.11 Read Parameter Page */
bool gd5f1gq5_read_parameter_page(const uint8_t num, uint8_t* const parameter_page) {
    bool res = false;
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        res = gd5f1gq5_otp_ctrl(num, true);
        bool otp_enable = gd5f1gq5_get_otp_enable(num);
        if(otp_enable) {
            res = gd5f1gq5_read_to_cache(num, 0x000004);
            wait_ms(1);
            res = gd5f1gq5_read_from_cache(num, 0x000000, parameter_page, 256);
        }
    }
    return res;
}

bool gd5f1gq5_unlock_all_blocks(const uint8_t num) {
    bool res = false;
    LOG_INFO(GD5F1GQ5, "UnLockAllBlocks,N:%u", num);
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        Gd5f1gq5RegProtection_t Protection;
        Protection.byte = 0;
        res = gd5f1gq5_get_features(num, GD5F1GQ5_REG_PROTECTION_A0H, &Protection.byte);
        if(res) {
            Protection.BRWD = 0; //
            Protection.BP = 0;   // TODO add enum
            res = gd5f1gq5_set_features(num, GD5F1GQ5_REG_PROTECTION_A0H, Protection.byte);
        }
    }
    return res;
}

bool gd5f1gq5_write_ctrl(const uint8_t num, const bool on_off) {
    bool res = false;
    LOG_DEBUG(GD5F1GQ5, "WriteCtrl,N:%u,WR:%u", num, on_off);
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        wait_us(1);
        res = spi_write_byte(Node->spi_num, WriteONoffToOpCode(on_off));
        wait_us(1);
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}

bool gd5f1gq5_soft_reset(const uint8_t num) {
    bool res = false;
    LOG_INFO(GD5F1GQ5, "SoftReset,N:%u", num);
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        wait_us(1);
        res = spi_write_byte(Node->spi_num, GD5F_CMD_SOFT_RESET);
        wait_us(1);
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}

bool gd5f1gq5_get_otp_enable(const uint8_t num) {
    bool res = false;
    Gd5f1gq5RegFeatureB0_t Feature;
    Feature.byte = 0;
    res = gd5f1gq5_get_features(num, GD5F1GQ5_REG_FEATURE_B0H, &Feature.byte);
    if(res) {
        res = Feature.OTP_EN;
        LOG_DEBUG(GD5F1GQ5, "Getotp,N:%u,En:%u", num, res);
    }

    return res;
}

/*
 9.4 Program Execute (PE) (10H)
 Figure 9-3. Program Execute Sequence Diagram
 */
static bool gd5f1gq5_program_execute(const uint8_t num, const uint32_t row_address) {
    bool res = false;
    Gd5f1gq5RowAddress_t RowAddress;
    RowAddress.row_address = row_address;
    LOG_DEBUG(GD5F1GQ5, "ProgramExecute:N:%u,Addr:[%s]", num, Gd5f1gq5RowAddressToStr(&RowAddress));
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        wait_us(1);
        uint8_t tx_array[4] = {GD5F_CMD_PROGRAM_EXECUTE, 0x00, RowAddress.buff[1], RowAddress.buff[0]};
        res = spi_mcal_write(Node->spi_num, tx_array, 4);
        wait_us(1);
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}

/*
9.2 Program Load (PL) (02H)
column_address-  The Program address should be in sequential order in a block.

Column Address (CA): 12-битный адрес. Он выбирает байт внутри страницы.
Так как страница имеет размер 2048 + 128 байт, 12 бит (что дает диапазон адресов 0...4095)
 более чем достаточно для покрытия всех байтов страницы (максимальный адрес 2175).

The data bytes are loaded into a cache register that is whole page long.
If more than one page data are loaded, then those additional bytes are ignored by the cache register.
 */
bool gd5f1gq5_program_load(const uint8_t num, const uint32_t column_address, const uint8_t* const data,
                           const uint32_t size) {
    bool res = false;
    LOG_DEBUG(GD5F1GQ5, "ProgramLoad,N:%u,ColumnAddress:0x%x,Size:%u,Data:[%s]", num, column_address, size,
              ArrayToStr(data, size));
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        if(data) {
            if(size <= GD5F1GQ5_PAGE_SIZE) {
                gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
                wait_us(1);
                Gd5f1gq5ProgramLoadAddress_t Address;
                Address.word = 0;
                Address.column_address = column_address;
                uint8_t tx_array[3] = {GD5F_CMD_PROGRAM_LOAD, Address.buff[1], Address.buff[0]};
                res = spi_mcal_write(Node->spi_num, tx_array, 3);
                res = spi_mcal_write(Node->spi_num, data, size);
                wait_us(1);
                gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
                wait_us(1);
            }
        }
    }
    return res;
}

/*
Figure 12-1. Get Features Sequence Diagram
 */
bool gd5f1gq5_get_features(const uint8_t num, const uint8_t reg_addr, uint8_t* const data) {
    bool res = false;
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        if(Node->init) {
            if(data) {
                gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
                wait_us(1);
                uint8_t tx_array[2] = {GD5F_CMD_GET_FEATURES, reg_addr};
                res = spi_mcal_write(Node->spi_num, tx_array, 2);
                *data = spi_read_byte(Node->spi_num);
                wait_us(1);
                gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
                LOG_DEBUG(GD5F1GQ5, "GetReg,N:%u,Addr:0x%02x,Data:0x%02x", num, reg_addr, *data);
            }
        }
    }
    return res;
}

bool gd5f1gq5_set_features(const uint8_t num, const uint8_t addr, const uint8_t data) {
    bool res = false;
    LOG_INFO(GD5F1GQ5, "SetReg,N:%u,Addr:0x%02x,Data:0x%02x", num, addr, data);
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        if(Node->init) {
            gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
            wait_us(1);
            uint8_t tx_array[3] = {GD5F_CMD_SET_FEATURES, addr, data};
            res = spi_mcal_write(Node->spi_num, tx_array, 3);
            wait_us(1);
            gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
        }
    }
    return res;
}

/*  Figure 10. Block Erase Sequence Diagram
    row_address- RA: Row Address.
                     RA<5:0>selects a page inside a block, and
                     RA<15:6>selects a block.
 */
static bool gd5f1gq5_block_erase_cmd(const uint8_t num, const uint32_t row_address) {
    bool res = false;
    Gd5f1gq5RowAddress_t RowAddress = {0};
    RowAddress.row_address = row_address;
    LOG_INFO(GD5F1GQ5, "EraseBlock,N:%u,RowAddr:[%s]", num, Gd5f1gq5RowAddressToStr(&RowAddress));
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        if(Node->init) {
            gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
            wait_us(1);
            uint8_t tx_array[4] = {GD5F_CMD_BLOCK_ERASE, 0x00, RowAddress.buff[1], RowAddress.buff[0]};
            res = spi_mcal_write(Node->spi_num, tx_array, 4);
            wait_us(1);
            gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
        }
    }
    return res;
}

bool gd5f1gq5_wait_ready(const uint8_t num, const uint32_t timeout_ms) {
    bool res = false;
    bool loop = true;
    uint32_t start_ms = time_get_ms32();
    while(loop) {
        loop = time_wait_timeout(start_ms, timeout_ms);
        if(!loop) {
            res = loop;
        }

        Gd5f1gq5RegStatusC0_t Status;
        Status.byte = 0;
        res = gd5f1gq5_get_features(num, GD5F1GQ5_REG_STATUS_C0H, (uint8_t*)&Status.byte);
        if(res) {
            if(GD5F1GQ5_STATUS_OIP_READY == Status.OIP) {
                res = true;
                loop = false;
                break;
            }
        }
    }
    return res;
}

uint32_t gd5f1gq5_phy_address_to_row_address(const uint32_t phy_address) {
    Gd5f1gq5PhyAddress_t PhyAddress;
    PhyAddress.phy_address = phy_address;
    LOG_DEBUG(GD5F1GQ5, "phyAddress,0x%08x,RawAddr:0x%x", phy_address, PhyAddress.row_address);
    return PhyAddress.row_address;
}

/*
 see 8.1 Page Read
 page_address - page address */
bool gd5f1gq5_read_page(const uint8_t num, const uint32_t phy_address, uint8_t* const data, const uint32_t size) {
    bool res = false;
    Gd5f1gq5PhyAddress_t PhyAddress;
    PhyAddress.phy_address = phy_address;
    LOG_DEBUG(GD5F1GQ5, "ReadPage,N:%u,PhyAddr:%s,size:%u", num, Gd5f1gq5PhyAddrToStr(&PhyAddress), size);
    if(size <= GD5F1GQ5_PAGE_SIZE) {
        res = gd5f1gq5_read_to_cache(num, PhyAddress.row_address);
        if(res) {
            res = gd5f1gq5_wait_ready(num, 3);
            res = gd5f1gq5_read_from_cache(num, PhyAddress.column_address, data, size);
            if(res) {
                LOG_DEBUG(GD5F1GQ5, "Mem:[%s]", ArrayToStr(data, size));
            }
        }
    }
    return res;
}

/*
9.1 Page Program
The PAGE PROGRAM operation sequence programs 1 byte to whole page bytes of data within a page.
The page program  sequence is as follows:
 02H (PROGRAM LOAD)
 06H (WRITE ENABLE)
 10H (PROGRAM EXECUTE)
 */
bool gd5f1gq5_page_program(const uint8_t num, const uint32_t phy_address, const uint8_t* const data,
                           const uint32_t size) {
    bool res = false;
    Gd5f1gq5PhyAddress_t PhyAddress;
    PhyAddress.phy_address = phy_address;
    LOG_DEBUG(GD5F1GQ5, "PageProgram,N:%u,PhyAddr:%s,Size:%u,Data:[%s]", num, Gd5f1gq5PhyAddrToStr(&PhyAddress), size,
              ArrayToStr(data, size));
    res = gd5f1gq5_program_load(num, PhyAddress.column_address, data, size);
    if(res) {
        res = gd5f1gq5_write_ctrl(num, true);
        if(res) {
            res = gd5f1gq5_program_execute(num, PhyAddress.row_address);
            if(res) {
                res = gd5f1gq5_wait_ready(num, 3);
            }
        }
    }

    return res;
}

// Row Address
bool gd5f1gq5_erase_block(const uint8_t num, const uint32_t phy_address) {
    bool res = false;
    Gd5f1gq5PhyAddress_t PhyAddress = {0};
    PhyAddress.phy_address = phy_address;
    LOG_INFO(GD5F1GQ5, "EraseBlock,N:%u,PhyAddr:[%s]", num, Gd5f1gq5PhyAddressToStr(phy_address));
    res = gd5f1gq5_write_ctrl(num, true);
    if(res) {
        res = gd5f1gq5_block_erase_cmd(num, PhyAddress.row_address);
        if(res) {
            res = gd5f1gq5_wait_ready(num, 15);
        }
    }
    return res;
}

/* see 8.2 Page (2048 byte) Read to Cache (13H)  */
bool gd5f1gq5_read_to_cache(const uint8_t num, const uint32_t row_address) {
    bool res = false;
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        if(Node->init) {
            LOG_DEBUG(GD5F1GQ5, "ReadToCache,N:%u,RowAddr:0x%06x", num, row_address);
            gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
            wait_us(1);
            U32_bit_t uAddr;
            uAddr.u32 = row_address;
            uint8_t tx_array[4] = {GD5F_CMD_PAGE_READ_TO_CACHE, uAddr.u8[2], uAddr.u8[1], uAddr.u8[0]};
            res = spi_mcal_write(Node->spi_num, tx_array, 4);
            wait_us(1);
            gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
        }
    }
    return res;
}

bool gd5f1gq5_otp_ctrl(const uint8_t num, const bool enable) {
    bool res = false;
    LOG_DEBUG(GD5F1GQ5, "OTP,N:%u,En:%u", num, enable);
    Gd5f1gq5RegFeatureB0_t Feature;
    Feature.byte = 0;
    res = gd5f1gq5_get_features(num, GD5F1GQ5_REG_FEATURE_B0H, &Feature.byte);
    if(res) {
        Feature.OTP_EN = enable;
        res = gd5f1gq5_set_features(num, GD5F1GQ5_REG_FEATURE_B0H, Feature.byte);
    }
    return res;
}

/* Figure 8-9. Read Unique ID to cache and Get Feature command Sequence Diagram one
   Read Unique ID */
bool gd5f1gq5_read_uid(uint8_t num, uint8_t* const uid) {
    bool res = false;
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        if(Node->init) {
            res = gd5f1gq5_otp_ctrl(num, true);
            Gd5f1gq5RegFeatureB0_t Feature;
            Feature.byte = 0;
            res = gd5f1gq5_get_features(num, GD5F1GQ5_REG_FEATURE_B0H, &Feature.byte);
            if(res) {
                if(Feature.OTP_EN) {
                    res = gd5f1gq5_read_to_cache(num, 0x000006);
                    res = gd5f1gq5_read_from_cache(num, 0x000000, uid, 16);
                }
            }
            res = gd5f1gq5_otp_ctrl(num, false);
        }
    }
    return res;
}

bool gd5f1gq5_get_write_enable(const uint8_t num) {
    bool res = false;
    Gd5f1gq5RegStatusC0_t StatusC0;
    StatusC0.byte = 0;
    res = gd5f1gq5_get_features(num, 0xC0, &StatusC0.byte);
    if(res) {
        res = (bool)StatusC0.WEL;
    }
    return res;
}

static bool Gd5f1gq5ParameterPageIsReservedValid(const Gd5f1gq5ParameterPage_t* const ParamPage) {
    bool res = true;
    // 4. Reserved fields 8-9 should be 0x0000
    if(ParamPage->reserved_8_9 != 0x0000) {
        LOG_ERROR(GD5F1GQ5, "reserved_8_9");
        res = false;
    }

    // 10. Check reserved area 67-79 is all zeros
    for(int i = 0; i < 13; i++) {
        if(ParamPage->reserved_67_79[i] != 0x00) {
            LOG_ERROR(GD5F1GQ5, "reserved_67_79");
            res = false;
        }
    }

    // 12. Byte 101 is reserved and should be 0
    if(ParamPage->reserved_101 != 0x00) {
        LOG_ERROR(GD5F1GQ5, "reserved_101");
        res = false;
    }

    // 23. Check reserved area 115-127 is all zeros
    for(int i = 0; i < 13; i++) {
        if(ParamPage->reserved_115_127[i] != 0x00) {
            LOG_ERROR(GD5F1GQ5, "reserved_115_127");
            res = false;
        }
    }

    // 30. Reserved 139-140: 0x0000
    if(ParamPage->reserved_139_140 != 0x0000) {
        LOG_ERROR(GD5F1GQ5, "reserved_139_140");
        res = false;
    }

    // 31. Check reserved area 141-163 is all zeros
    for(int i = 0; i < 23; i++) {
        if(ParamPage->reserved_141_163[i] != 0x00) {
            LOG_ERROR(GD5F1GQ5, "reserved_141_163");
            res = false;
        }
    }

    // 5. Check reserved area 10-31 is all zeros
    for(int i = 0; i < 22; i++) {
        if(ParamPage->reserved_10_31[i] != 0x00) {
            LOG_ERROR(GD5F1GQ5, "reserved_10_31");
            res = false;
        }
    }

    // 26. Reserved 131-132: 0x0000
    if(ParamPage->reserved_131_132 != 0x0000) {
        LOG_ERROR(GD5F1GQ5, "reserved_131_132");
        res = false;
    }
    return res;
}

static bool Gd5f1gq5ParameterPageIsCrc16Valid(const Gd5f1gq5ParameterPage_t* const ParamPage) {
    bool res = true;
    // 33. Check CRC16 for bytes 0-255
    //    For GD5F1GQ5U model: expected CRC = 0xF358 (58H/F3H in datasheet)
    uint16_t calculated_crc = crc16_ibm_calc(ParamPage->buff, 254); // CRC is at bytes 254-255
    if(ParamPage->crc16 == calculated_crc) {
        LOG_INFO(GD5F1GQ5, "CRC16:0x%04x,Ok", calculated_crc);
    } else {
        LOG_ERROR(GD5F1GQ5, "CRC16,Err,Read:0x%04x,Calc:0x%04x", ParamPage->crc16, calculated_crc);
    }
    return res;
}

bool Gd5f1gq5ParameterPageIsValidTokens(const Gd5f1gq5ParameterPage_t* const ParamPage) {
    bool res = true;
    // 1. Check signature "ONFI" (bytes 0-3)
    if(ParamPage->signature != 0x49464E4F) { // 'O','N','F','I' in little-endian
        LOG_ERROR(GD5F1GQ5, "signature");
        res = false;
    }

    // 7. Device model should start with "GD5F1GQ5" for 1Gbit device
    const uint8_t expected_model_prefix[8] = {'G', 'D', '5', 'F', '1', 'G', 'Q', '5'};

    if(memcmp(ParamPage->device_model, expected_model_prefix, 8) != 0) {
        LOG_ERROR(GD5F1GQ5, "device_model");
        res = false;
    }

    // 6. Manufacturer string should be "GIGADEVICE  " (12 bytes)
    const uint8_t expected_manufacturer[12] = {'G', 'I', 'G', 'A', 'D', 'E', 'V', 'I', 'C', 'E', ' ', ' '};
    if(memcmp(ParamPage->manufacturer, expected_manufacturer, 12) != 0) {
        LOG_ERROR(GD5F1GQ5, "manufacturer");
        res = false;
    }

    // 8. Check model suffix: 'U' for 3.3V or 'R' for 1.8V
    // For GD5F1GQ5UEYIGR it should be 'U' (3.3V version)
    uint8_t model_voltage_char = ParamPage->device_model[8];
    if(model_voltage_char != 'U' && model_voltage_char != 'R') {
        LOG_ERROR(GD5F1GQ5, "model_voltage_char");
        res = false;
    }

    // 2. Revision number should be 0x0000 (reserved)
    if(ParamPage->revision != 0x0000) {
        LOG_ERROR(GD5F1GQ5, "revision");
        res = false;
    }

    // 3. Features supported should be 0x0000 (reserved)
    if(ParamPage->features_supported != 0x0000) {
        LOG_ERROR(GD5F1GQ5, "features_supported");
        res = false;
    }

    // 9. JEDEC manufacturer ID should be 0xC8 for GigaDevice
    if(ParamPage->jedec_manufacturer_id != 0xC8) {
        LOG_ERROR(GD5F1GQ5, "jedec_manufacturer_id");
        res = false;
    }
    return res;
}

static bool Gd5f1gq5ParameterPageIsRelabilityValid(const Gd5f1gq5ParameterPage_t* const ParamPage) {
    bool res = true;
    // 14. Max bad blocks: 0x0014 = 20
    if(ParamPage->max_bad_blocks != 0x0014) {
        LOG_ERROR(GD5F1GQ5, "max_bad_blocks");
        res = false;
    }

    // 15. Block endurance: 0x0105 = 261 (represents 100K cycles)
    if(ParamPage->block_endurance != 0x0501) {
        LOG_ERROR(GD5F1GQ5, "block_endurance");
        res = false;
    }

    // 16. Guaranteed valid blocks: 0x01
    if(ParamPage->guaranteed_valid_blocks != 0x01) {
        LOG_ERROR(GD5F1GQ5, "guaranteed_valid_blocks");
        res = false;
    }

    // 17. Block endurance for guaranteed blocks: 0x0000
    if(ParamPage->endurance_guaranteed_blocks != 0x0000) {
        LOG_ERROR(GD5F1GQ5, "endurance_guaranteed_blocks");
        res = false;
    }

    return res;
}

static bool Gd5f1gq5ParameterPageIsCapasityValid(const Gd5f1gq5ParameterPage_t* const ParamPage) {
    bool res = true;
    // 11. Memory organization checks
    if(ParamPage->bytes_per_page != 2048) { // 2KB per page
        LOG_ERROR(GD5F1GQ5, "bytes_per_page");
        res = false;
    }
    if(ParamPage->spare_bytes_per_page != 128) { // 128 bytes spare
        LOG_ERROR(GD5F1GQ5, "spare_bytes_per_page");
        res = false;
    }
    if(ParamPage->data_bytes_per_partial_page != 512) { // 512 bytes partial
        LOG_ERROR(GD5F1GQ5, "data_bytes_per_partial_page");
        res = false;
    }

    if(ParamPage->spare_bytes_per_partial_page != 32) { // 32 bytes spare partial
        LOG_ERROR(GD5F1GQ5, "spare_bytes_per_partial_page");
        res = false;
    }
    if(ParamPage->pages_per_block != 64) { // 64 pages per block
        LOG_ERROR(GD5F1GQ5, "pages_per_block");
        res = false;
    }
    if(ParamPage->blocks_per_lun != 1024) { // 1024 blocks per LUN
        LOG_ERROR(GD5F1GQ5, "blocks_per_lun");
        res = false;
    }
    if(ParamPage->num_luns != 1) { // 1 LUN
        LOG_ERROR(GD5F1GQ5, "num_luns");
        res = false;
    }
    // 13. Bits per cell: 0x01 = SLC
    if(ParamPage->bits_per_cell != 0x01) {
        LOG_ERROR(GD5F1GQ5, "bits_per_cell");
        res = false;
    }

    // 18. Programs per page: 0x04
    if(ParamPage->programs_per_page != 0x04) {
        LOG_ERROR(GD5F1GQ5, "programs_per_page");
        res = false;
    }
    // 19. Partial programming attributes: 0x00
    if(ParamPage->partial_program_attrs != 0x00) {
        LOG_ERROR(GD5F1GQ5, "partial_program_attrs");
        res = false;
    }
    return res;
}

static bool Gd5f1gq5ParameterPageIsElectricalValid(const Gd5f1gq5ParameterPage_t* const ParamPage) {
    bool res = true;
    // 24. I/O capacitance: 0x08 = 8pF
    if(ParamPage->io_capacitance != 0x08) {
        LOG_ERROR(GD5F1GQ5, "io_capacitance");
        res = false;
    }
    // 25. IO clock support: 0x0000
    if(ParamPage->io_clock_support != 0x0000) {
        LOG_ERROR(GD5F1GQ5, "io_clock_support");
        res = false;
    }
    // 27. tPROG max: 0x0258 = 600us
    if(ParamPage->tPROG_max_us != 0x0258) {
        LOG_ERROR(GD5F1GQ5, "tPROG_max_us");
        res = false;
    }

    // 28. tBERS max: 0x2710 = 10000us = 10ms
    if(ParamPage->tBERS_max_us != 0x2710) {
        LOG_ERROR(GD5F1GQ5, "tBERS_max_us");
        res = false;
    }

    // 29. tR max: 0x003C = 60us
    if(ParamPage->tR_max_us != 0x003C) {
        LOG_ERROR(GD5F1GQ5, "tR_max_us");
        res = false;
    }
    // 32. Vendor revision: 0x0000
    if(ParamPage->vendor_revision != 0x0000) {
        LOG_ERROR(GD5F1GQ5, "vendorRevision");
        res = false;
    }
    return res;
}

bool Gd5f1gq5ParameterPageIsValid(const Gd5f1gq5ParameterPage_t* const ParamPage) {
    bool res = true;
    if(ParamPage) {
        res = true;
        res = Gd5f1gq5ParameterPageIsCrc16Valid(ParamPage);
        log_debug_res(GD5F1GQ5, res, "Crc16");

        res = Gd5f1gq5ParameterPageIsReservedValid(ParamPage);
        log_debug_res(GD5F1GQ5, res, "Reserved");

        res = Gd5f1gq5ParameterPageIsValidTokens(ParamPage);
        log_debug_res(GD5F1GQ5, res, "Tokens");

        res = Gd5f1gq5ParameterPageIsCapasityValid(ParamPage);
        log_debug_res(GD5F1GQ5, res, "Capasity");

        res = Gd5f1gq5ParameterPageIsRelabilityValid(ParamPage);
        log_debug_res(GD5F1GQ5, res, "Relability");

        res = Gd5f1gq5ParameterPageIsElectricalValid(ParamPage);
        log_debug_res(GD5F1GQ5, res, "Electrical");

#if 0
    // 20. ECC correctability: 0x00 (means use default 4 bits/528 bytes)
    if(ParamPage->ecc_correctability_bits != 0x00) {
        res = false;
    }

    // 21. Interleaved address bits: 0x00
    if (ParamPage->interleaved_addr_bits != 0x00) {
        res=false;
    }
    // 22. Interleaved attributes: 0x00
    if (ParamPage->interleaved_attrs != 0x00) {
        res=false;
    }
#endif
    }
    return res;
}

bool gd5f1gq5_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(GD5F1GQ5, "GD5F1GQ5%u", num);
    const Gd5f1gq5Config_t* Config = Gd5f1gq5GetConfig(num);
    if(Config) {
        res = Gd5f1gq5IsValidConfig(Config);
        if(res) {
#ifdef HAS_GD5F1GQ5_DIAG
            LOG_WARNING(GD5F1GQ5, "Config:%s", Gd5f1gq5ConfigToStr(Config));
#endif
            Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
            if(Node) {
                res = gd5f1gq5_init_common(Config, Node);
                res = gd5f1gq5_init_node(Node);

                res = gpio_init_out(Config->chip_select);
                res = gpio_pull_set(Config->chip_select, GPIO__PULL_UP);

                res = gd5f1gq5_soft_reset(num);

                res = gd5f1gq5_otp_ctrl(num, false);
                res = gd5f1gq5_write_ctrl(num, true);
                res = gd5f1gq5_unlock_all_blocks(num);

                uint8_t uid[16] = {0};
                memset(uid, 0, sizeof(16));
                res = gd5f1gq5_read_uid(num, uid);
                if(res) {
                    LOG_INFO(GD5F1GQ5, "UID:%s", ArrayToStr(uid, 16));
                }

                Node->valid = true;
                Node->init = true;
                LOG_INFO(GD5F1GQ5, "Init,Ok,%u", num);
            } else {
                LOG_ERROR(GD5F1GQ5, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(GD5F1GQ5, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(GD5F1GQ5, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(GD5F1GQ5, GD5F1GQ5, gd5f1gq5)
COMPONENT_PROC_PATTERT(GD5F1GQ5, GD5F1GQ5, gd5f1gq5)
