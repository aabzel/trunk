#include "at24cxx_read_drv.h"

#include <string.h>

//#include "array.h"
#include "at24cxx_drv.h"
#include "byte_utils.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "i2c_mcal.h"
#include "log.h"
#include "time_mcal.h"

bool at24cxx_read(uint8_t num, uint16_t address, void* const data, size_t size) {
    bool res = false;
    LOG_INFO(AT24C, "AT24C_%u Read Addr:0x%04x, size:%u byte", num, address, size);
    At24cxxHandle_t* Node = At24cxxGetNode(num);
    if(Node) {
        if(data) {
            if(size) {
                uint8_t address_u8 = WORD_LO_BYTE(address);
                res = i2c_api_read_mem(Node->i2c_num, Node->chip_addr, (uint8_t*)&address_u8, 1, (uint8_t*)data,
                                       (uint32_t)size);
                if(res) {
                    LOG_INFO(AT24C, "ReadOk");
                    Node->read_bytes += size;
                    res = true;
                } else {
                    LOG_ERROR(AT24C, "AT24C_%u,Read,Addr:0x%x,size:%u byte Err", num, address, size);
                }
            }
        }
    }
    return res;
}

bool at24cxx_read_byte(uint8_t num, uint16_t address, uint8_t* const data) {
    bool res = false;
    LOG_INFO(AT24C, "AT24C_%u,Read,Byte,Addr:0x%04x", num, address);
    At24cxxHandle_t* Node = At24cxxGetNode(num);
    if(Node) {
        if(data) {
            // res=i2c_api_read_byte(Node->i2c_num, Node->chip_addr, address, (uint8_t*)data);
            // address = reverse_byte_order_uint16(address);
            uint8_t address_u8 = WORD_LO_BYTE(address);
            res = i2c_api_read_mem(Node->i2c_num, Node->chip_addr, (uint8_t*)&address_u8, 1, (uint8_t*)data, 1);
            if(false == res) {
                LOG_ERROR(AT24C, "AT24C_%u,Read,Addr:0x%x,size:%u,byte Err", num, address);
            } else {
                LOG_INFO(AT24C, "ReadByte 0x%x", *data);
                Node->read_bytes += 1;
                res = true;
            }
        }
    }
    return res;
}

bool at24cxx_read_address_ll(At24cxxHandle_t* const Node, uint16_t* const address) {
    bool res = false;
    if(Node) {
            res = i2c_api_read(Node->i2c_num, Node->chip_addr, (uint8_t*)address, 2);
            LOG_DEBUG(AT24C, "AT24C_%u,Addr:0x%04x", Node->num, *address);
    }
    return res;
}

bool at24cxx_read_address(uint8_t num, uint16_t* const address) {
    bool res = false;
    At24cxxHandle_t* Node = At24cxxGetNode(num);
    if(Node) {
        res = at24cxx_read_address_ll(Node, address);
    }
    return res;
}

uint8_t at24cxx_read_byte_short(uint8_t num, uint16_t address) {
    uint8_t data = 0x00;
    bool res = at24cxx_read(num, address, &data, 1);
    if(false == res) {
        LOG_ERROR(AT24C, "AT24C_%u,Read,Addr:0x%x byte ", num, address);
    }
    return data;
}

bool at24cxx_scan(uint8_t num, double* usage_pec, uint32_t* spare, uint32_t* busy) {
    bool res = false;
    return res;
}
