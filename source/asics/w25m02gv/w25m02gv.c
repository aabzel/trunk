#include "w25m02gv.h"


#include <string.h>

//#include "c_defines_generated.h"
#include "array_diag.h"
#include "code_generator.h"
#include "data_utils.h"
#include "byte_utils.h"
#include "gpio_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"

#ifdef HAS_SPI
#include "spi_mcal.h"
#endif


COMPONENT_GET_NODE(W25m02gv, w25m02gv)
COMPONENT_GET_CONFIG(W25m02gv, w25m02gv)

const W25m02gvRegInfo_t W25mRegInfo[] = {
    {
        .valid = true,
        .addr = 0 ,
        .name = "xxxx",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = 0 ,
        .name = "xxxx",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = 0 ,
        .name = "xxx",
        .access = ACCESS_READ_WRITE,
    },
};

uint32_t w25m02gv_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(W25mRegInfo);
    return cnt;
}

#if 0
static bool w25m02gv_register_read_ll(W25m02gvHandle_t* Node, W25m02gvRegAddr_t addr, uint8_t* const byte) {
    bool res = false;
    if(Node) {
    }
    return res;
}

bool w25m02gv_register_read_all(uint8_t num) {
    bool res = false;
    const W25m02gvConfig_t* Config = W25m02gvGetConfig(num);
    if(Config) {
        uint8_t i = 0;
        uint8_t ok_cnt = 0;
        for(i = 0; i < W25M02GV_REG_CNT; i++) {
            // res = w25m02gv_register_read(W25m02gvRegVal[i].addr, &W25m02gvRegVal[i].value.byte);
            if(res) {
                ok_cnt++;
            } else {
                // LOG_ERROR(SPI, "Read Reg:0x%02x Err", W25m02gvRegVal[i].addr);
            }
        }

        if(ok_cnt == W25M02GV_REG_CNT) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}
#endif

bool w25m02gv_is_connected(uint8_t num) {
    bool res = false;
    JedecInfo_t JedecInfo={0};
    res = w25m02gv_jedec_id_read(num, &JedecInfo);
    if(res) {
        if(JEDEC_ID_MFR_ID_WINBOND==JedecInfo.mfr_id){
            LOG_DEBUG(W25M02GV, "%u,SPI,Link,Ok", num);
            res = true;
        } else {
            LOG_ERROR(W25M02GV, "%u,UndefMfrId:0x%x", num, JedecInfo.mfr_id);
        	res = false;
        }
    }

    return res;
}


bool w25m02gv_reg_write_verify(uint8_t num, W25m02gvRegAddr_t addr, uint8_t set_byte) {
    bool res = false;
    cli_printf(CRLF);
    LOG_INFO(W25M02GV, "SetVerify Reg:0x%02x Val:0x%02x", addr, set_byte);

	W25m02gvRegUniversal_t RegWr = {0};
	RegWr.byte = set_byte;
    res = w25m02gv_register_write(num, addr, RegWr);
    if(res) {
    	W25m02gvRegUniversal_t Reg = {0};
        res = w25m02gv_register_read(num, addr, &Reg);
        if(Reg.byte == set_byte) {
            res = true;
            LOG_INFO(W25M02GV, "SetVerifyReg:0x%02x,Val:0x%02x,Ok", addr, set_byte);
        } else {
            LOG_ERROR(W25M02GV, "VerifyErrReg:0x%02x,Set:0x%02x!=Get:0x%02x", addr, set_byte, Reg.byte);
            res = false;
        }
    }

    return res;
}

//8.2.2 Device Reset (FFh)
bool w25m02gv_reset(uint8_t num) {
    bool res = false;
    W25m02gvHandle_t* Node = W25m02gvGetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_LOW);
    	res = spi_write_byte(Node->spi_num, W25_CMD_DEVICE_RESET);
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_HI);
    }
    return res;
}

bool w25m02gv_is_valid_addr(uint8_t addr) {
    bool res = false;
    const W25m02gvRegInfo_t* Node = W25m02gvRegAddrToInfo(addr);
    if(Node) {
        res = true;
    }

    return res;
}



bool w25m02gv_init_custom(void) {
    log_level_get_set(W25M02GV, LOG_LEVEL_INFO);
    return true;
}

static bool w25m02gv_init_common(const W25m02gvConfig_t* const Config, W25m02gvHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->ChipSelect = Config->ChipSelect;
            Node->spi_num = Config->spi_num;
            Node->num = Config->num;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}


static bool W25m02gvIsValidConfig(const W25m02gvConfig_t* const Config){
    bool res = false;
    if(Config){
        res = gpio_is_valid_pad(Config->Hold.byte);
        if(false==res){
            LOG_ERROR(W25M02GV, "HoldPadErr");
        }

        res = gpio_is_valid_pad(Config->ChipSelect.byte);
        if(false==res){
            LOG_ERROR(W25M02GV, "ChipSelectPadErr");
        }

        res = gpio_is_valid_pad(Config->WriteProtect.byte);
        if(false==res){
            LOG_ERROR(W25M02GV, "WriteProtectPadErr");
        }

        if(SPI_COUNT < Config->spi_num ){
            LOG_ERROR(W25M02GV, "SpiNumErr");
        }
    }
    return res;
}

bool w25m02gv_init_one(uint8_t num) {
    bool res = false;
    const W25m02gvConfig_t* Config = W25m02gvGetConfig(num);
    if(Config) {
        res = W25m02gvIsValidConfig(Config);
        if(res) {
            LOG_WARNING(W25M02GV, "Init:%s", W25m02gvConfigToStr(Config));
            W25m02gvHandle_t* Node = W25m02gvGetNode(num);
            if(Node) {
                log_level_get_set(SPI, LOG_LEVEL_DEBUG);
                log_level_get_set(W25M02GV, LOG_LEVEL_DEBUG);

                res = w25m02gv_init_common(Config, Node);

                res = w25m02gv_is_connected(num);
                if(res) {
                    LOG_INFO(W25M02GV, "SPILinkOk");
                } else {
                    LOG_ERROR(W25M02GV, "SPILinkErr");
                }

                log_level_get_set(SPI, LOG_LEVEL_INFO);
                log_level_get_set(W25M02GV, LOG_LEVEL_INFO);
            } else {
                LOG_ERROR(W25M02GV, "NodeErr");
            }
        }
    }
    return res;
}

const W25m02gvRegInfo_t* W25m02gvRegAddrToInfo(W25m02gvRegAddr_t addr) {
    W25m02gvRegInfo_t* Info = NULL;
    uint32_t cnt = ARRAY_SIZE(W25mRegInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(W25mRegInfo[i].valid) {
            if(addr == W25mRegInfo[i].addr) {
                Info = &W25mRegInfo[i];
            }
        }
    }
    return Info;
}

bool w25m02gv_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(W25M02GV, "Proc:%u", num);
    const W25m02gvConfig_t* Config = W25m02gvGetConfig(num);
    if(Config) {
        W25m02gvHandle_t* Node = W25m02gvGetNode(num);
        if(Node) {
            //res = w25m02gv_is_connected(num);
            //if(res) {


            //} else {
            //    LOG_WARNING(W25M02GV, "%u,SpiLinkErr", num);
            //}
        } else {
            LOG_ERROR(W25M02GV, "NodeErr %u", num);
        }
    }
    return res;
}

//8.2.17 Fast Read (0Bh)
bool w25m02gv_fast_read_buffer_mode(uint8_t num, uint16_t colomn_addr, uint8_t* const data, uint32_t size){
    bool res = false;
    W25m02gvHandle_t* Node = W25m02gvGetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_LOW);
        uint8_t buff[4] = {0xFF};
        buff[0] = W25_CMD_FAST_READ;
        uint16_t colomn_addr_be = reverse_byte_order_uint16(colomn_addr);
        memcpy(&buff[1], &colomn_addr_be, 2);
        res = spi_api_write(Node->spi_num, buff, 4);
        if(res) {
            res = spi_api_read(Node->spi_num, data,   size);
        }
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_HI);
    }
    return res;
}

// 8.2.16 Read Data (03h)
bool w25m02gv_read(uint8_t num, uint16_t colomn_addr, uint8_t* const data, uint32_t size){
    bool res = false;
    W25m02gvHandle_t* Node = W25m02gvGetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_LOW);
        uint8_t buff[4] = {0xFF};
        buff[0] = W25_CMD_READ;
        uint16_t colomn_addr_be = reverse_byte_order_uint16(colomn_addr);
        memcpy(&buff[1], &colomn_addr_be, 2);
        res = spi_api_write(Node->spi_num, buff, 4);
        if(res) {
            res = spi_api_read(Node->spi_num, data,   size);
        }
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_HI);
    }
    return res;
}

//8.2.7 Write Disable (04h)
bool w25m02gv_write_disable(uint8_t num){
    bool res = false;
    W25m02gvHandle_t* Node = W25m02gvGetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_LOW);
        res = spi_write_byte(Node->spi_num, W25_CMD_WRITE_DISABLE);

        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_HI);
    }
    return res;
}

bool w25m02gv_write_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    switch((uint32_t)on_off) {
        case true:  res = w25m02gv_write_enable(num); break;
        case false: res = w25m02gv_write_disable(num); break;
        default: res = false; break;
    }
    return res;
}

//8.2.8 Bad Block Management (A1h)
bool w25m02gv_bad_block_management(uint8_t num,
                                   uint16_t logical_block_address,
                                   uint16_t physical_block_address){
    bool res = false;
    W25m02gvHandle_t* Node = W25m02gvGetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_LOW);
        uint8_t buff[5] = { 0};
        buff[0]= W25_CMD_BB_MANAGEMENT;
        uint16_t logical_block_address_be = reverse_byte_order_uint16(logical_block_address);
        uint16_t physical_block_address_be = reverse_byte_order_uint16(physical_block_address);
        memcpy(&buff[1], &logical_block_address_be, 2);
        memcpy(&buff[3], &physical_block_address_be, 2);
        res = spi_api_write(Node->spi_num, buff, 5);
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_HI);
    }
    return res;
}

//8.2.6 Write Enable (06h)
bool w25m02gv_write_enable(uint8_t num) {
    bool res = false;
    W25m02gvHandle_t* Node = W25m02gvGetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_LOW);
        res = spi_write_byte(Node->spi_num, W25_CMD_WRITE_ENABLE);
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_HI);
    }
    return res;
}

//8.2.11 128KB Block Erase (D8h)
bool w25m02gv_block_erase(uint8_t num, uint16_t page_adddress){
    bool res = false;
    W25m02gvHandle_t* Node = W25m02gvGetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_LOW);
        uint8_t buff[4] = {0};
        buff[0] = W25_CMD_BLOCK_ERASE;
        buff[1] = 0xFF;
        uint16_t page_adddress_be = reverse_byte_order_uint16(page_adddress);
        memcpy(&buff[2], &page_adddress_be, 2);
        res = spi_api_write(Node->spi_num, buff, 4);
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_HI);
    }
    return res;
}

//8.2.5 Write Status Register (1Fh / 01h)
bool w25m02gv_register_write(uint8_t num, W25m02gvRegAddr_t reg_addr, W25m02gvRegUniversal_t Reg){
    bool res = false;
    W25m02gvHandle_t* Node = W25m02gvGetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_LOW);
        uint8_t buff[3] = {W25_CMD_WRITE_STATUS_REGISTER, reg_addr, Reg.byte};
        res = spi_api_write(Node->spi_num, buff, 3);
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_HI);
    }
    return res;
}

//8.2.4 Read Status Register (0Fh / 05h)
bool w25m02gv_register_read(uint8_t num, W25m02gvRegAddr_t reg_addr, W25m02gvRegUniversal_t* const value){
    bool res = false;
    LOG_DEBUG(W25M02GV, "%u,Reg,Addr:0x%x,Read", num,reg_addr);
    W25m02gvHandle_t* Node = W25m02gvGetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->ChipSelect.byte,GPIO_LVL_LOW);
        uint8_t buff[2] = {W25_CMD_READ_STATUS_REGISTER, reg_addr};
        res = spi_api_write(Node->spi_num, buff, 2);
        if(res) {
            res = spi_api_read(Node->spi_num, &value->byte, 1);
            if (res) {

            } else {
                LOG_ERROR(W25M02GV, "SPI,read,Err");
            }
        } else {
            LOG_ERROR(W25M02GV, "SPI,write,Err");
        }
        gpio_logic_level_set(Node->ChipSelect.byte,GPIO_LVL_HI);
    }
    return res;
}

//
bool w25m02gv_jedec_id_read(uint8_t num, JedecInfo_t* const JedecInfo) {
    bool res = false;
    W25m02gvHandle_t* Node = W25m02gvGetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->ChipSelect.byte,GPIO_LVL_LOW);
        uint8_t buff[2]={W25_CMD_JEDEC_ID, 0xFF};
        res = spi_api_write(Node->spi_num, buff, 2);
        if(res) {
        	res = wait_us(100);
            res = spi_api_read(Node->spi_num, JedecInfo->buff, 3);
        }
        gpio_logic_level_set(Node->ChipSelect.byte,GPIO_LVL_HI);
    }
    return res;
}

COMPONENT_INIT_PATTERT(W25M02GV, W25M02GV, w25m02gv)
COMPONENT_PROC_PATTERT(W25M02GV, W25M02GV, w25m02gv)
