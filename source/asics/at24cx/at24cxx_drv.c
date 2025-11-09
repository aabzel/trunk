#include "at24cxx_drv.h"

#include <string.h>

//#include "array.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "crc8_autosar.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "i2c_mcal.h"
#include "log.h"
#include "time_mcal.h"

static const At24cxxInfo_t At24cxxInfo[] = {
    {
        .valid = true,
        .chip_model = AT24C02,
        .capacity_bytes = 256,
        .pages = 32,
        .page_size = 8,
        .addr_bit = 8,
    },
    {
        .valid = true,
        .chip_model = AT24C04,
        .capacity_bytes = 512,
        .pages = 32,
        .page_size = 16,
        .addr_bit = 9,
    },
    {
        .valid = true,
        .chip_model = AT24C08,
        .capacity_bytes = 1024,
        .pages = 64,
        .page_size = 16,
        .addr_bit = 10,
    },
    {
        .valid = true,
        .chip_model = AT24C16,
        .capacity_bytes = 2048,
        .pages = 126,
        .page_size = 16,
        .addr_bit = 11,
    },
};


const At24cxxInfo_t* At24cxxGetInfo(At24cChipModel_t chip_model) {
    const At24cxxInfo_t* Node = NULL;
    uint16_t i = 0;
    for(i = 0; i < ARRAY_SIZE(At24cxxInfo); i++) {
        if(At24cxxInfo[i].valid) {
            if(chip_model == At24cxxInfo[i].chip_model) {
                Node = &At24cxxInfo[i];
                break;
            }
        }
    }
    return Node;
}

COMPONENT_GET_CONFIG(At24cxx, at24cxx)

COMPONENT_GET_NODE(At24cxx, at24cxx)

uint16_t ChipModel2PageSize(At24cChipModel_t chip_model) {
    uint16_t page_size = 0;
    const At24cxxInfo_t* Info = At24cxxGetInfo(chip_model);
    if(Info) {
        page_size = Info->page_size;
    }
    return page_size;
}

static bool at24cxx_is_connected_ll(At24cxxHandle_t* const Node) {
    bool res = false;
    if(Node) {
        uint16_t address = 0;
        res = at24cxx_read_address_ll(Node, &address);
        if(false == res) {
            LOG_ERROR(AT24C, "I2C%u, Chip 0x%x.LinkErr", Node->i2c_num, Node->chip_addr);
        }
    } else {
        LOG_ERROR(AT24C, "NodeErr");
    }
    return res;
}

bool at24cxx_is_connected(uint8_t num) {
    bool res = false;
    At24cxxHandle_t* Node = At24cxxGetNode(num);
    if(Node) {
        // uint16_t address = 0;
        // res = at24cxx_read_address(num, &address);
        res = at24cxx_is_connected_ll(Node);
        if(res) {
            LOG_DEBUG(AT24C, "LinkOk");
        } else {
            LOG_ERROR(AT24C, "LinkErr");
            // LOG_DEBUG(AT24C, "LinkOk MemAddr:0x%04x", address);
        }
    } else {
        LOG_ERROR(AT24C, "AT%u NodeErr", num);
    }
    return res;
}

bool at24cxx_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(AT24C, "Proc %u", num);
    const At24cxxConfig_t* Config = At24cxxGetConfig(num);
    if(Config) {
        res = at24cxx_is_connected(num);
        if(res) {
            LOG_DEBUG(AT24C, "Connected!");
        } else {
            LOG_ERROR(AT24C, "AT%u Disconnected", num);
        }
    }
    return res;
}

bool at24cxx_init_custom(void){
    bool res = false;
    return res;
}

bool at24cxx_init_one(uint8_t num) {
    bool res = false;
    LOG_INFO(AT24C, "Init");
    set_log_level(AT24C, LOG_LEVEL_DEBUG);
    set_log_level(I2C, LOG_LEVEL_DEBUG);
    set_log_level(GPIO, LOG_LEVEL_DEBUG);

    const At24cxxConfig_t* Config = At24cxxGetConfig(num);
    if(Config) {
        At24cxxDiagConfig(Config);

        const At24cxxInfo_t* Info = At24cxxGetInfo(Config->chip_model);
        if(Info) {
            LOG_INFO(AT24C, "FamiliarChipModel", num);
            At24cxxDiagInfo(Info);
            res = true;
        } else {
            res = false;
            LOG_ERROR(AT24C, "UnfamiliarChipModel", num);
        }
    } else {
        LOG_DEBUG(AT24C, "Conf %u Err", num);
    }

    if(res) {
        At24cxxHandle_t* Node = At24cxxGetNode(num);
        if(Node) {
            Node->i2c_num = Config->i2c_num;
            Node->chip_addr = Config->chip_addr;
            Node->chip_model = Config->chip_model;
            Node->write_enable = Config->write_enable;
            Node->wp = Config->wp;

            res = at24cxx_is_connected_ll(Node);
            if(res) {
                LOG_INFO(AT24C, "I2cLinkOk!");
                uint8_t dump[260];
                res = at24cxx_read(num, 0, dump, 256);
                if(res) {
                    uint8_t crc8 = crc8_autosar_calc(dump, 256);
                    LOG_INFO(AT24C, "crc8 0x%02x", crc8);
                } else {
                    LOG_ERROR(AT24C, "ReadDumpErr");
                }
#ifdef HAS_AT24CXX_WRITE
                res = at24cxx_write_ctrl(num, Config->write_enable);
                if(res) {
                    LOG_INFO(AT24C, "WriteCtrlOk");
                } else {
                    LOG_ERROR(AT24C, "WriteCtrlErr");
                }
#endif
            } else {
                LOG_ERROR(AT24C, "I2cLinkErr");
            }
        } else {
            LOG_ERROR(AT24C, "Node%u Err", num);
        }
    }

    set_log_level(GPIO, LOG_LEVEL_INFO);
    set_log_level(I2C, LOG_LEVEL_INFO);
    set_log_level(AT24C, LOG_LEVEL_INFO);
    return res;
}

COMPONENT_INIT_PATTERT(AT24C, AT24C, at24cxx)

COMPONENT_PROC_PATTERT(AT24C, AT24C, at24cxx)
