#include "at24cxx_write_drv.h"

#include <string.h>

#include "at24cxx_config.h"
#include "at24cxx_diag.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "i2c_mcal.h"
#include "log.h"
#include "test_at24cxx.h"
#include "time_mcal.h"

bool at24cxx_write_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    const At24cxxConfig_t* Config = At24cxxGetConfig(num);
    if(Config) {
        res = gpio_is_valid_pad(Config->wp.byte);
        if(res) {
            if(on_off) {
                res = gpio_set_logic_level(Config->wp.byte, GPIO_LVL_LOW);
            } else {
                res = gpio_set_logic_level(Config->wp.byte, GPIO_LVL_HI);
            }
        } else {
            /*Write is allowed by hardware*/
            LOG_WARNING(AT24C, "InvalidGpioPad");
            res = true;
        }
    }
    return res;
}

/*(See page 8) Figure 6: Page Write
 * size*/
bool at24cxx_write(uint8_t num, uint16_t address, const uint8_t* const data, size_t size) {
    bool res = false;
    LOG_DEBUG(AT24C, "AT24C_%u Write Addr:0x%04x size %u", num, address, size);
    At24cxxHandle_t* Node = At24cxxGetNode(num);
    if(Node) {
        if(data) {
            if(size) {
                uint16_t i = 0;
                for(i = 0; i < size; i++) {
                    res = at24cxx_write_byte(num, address + i, data[i]);
                }
            }
        }
    }
    return res;
}

bool at24cxx_write_page(uint8_t num, uint16_t address, const uint8_t* const page) {
    bool res = false;
    LOG_DEBUG(AT24C, "AT24C_%u WritePage Addr:0x%x", num, address);
    At24cxxHandle_t* Node = At24cxxGetNode(num);
    if(Node) {
        if(page) {
            uint8_t byte_train[AT24C02_PAGE_SIZE + 1] = {0};
            // byte_train[0] = WORD_HI_BYTE(address);
            byte_train[0] = WORD_LO_BYTE(address);
            memcpy(&byte_train[1], page, AT24C02_PAGE_SIZE);
            res = i2c_api_write(Node->i2c_num, Node->chip_addr, byte_train, AT24C02_PAGE_SIZE + 1);
            if(res) {
                time_delay_ms(10);
                LOG_DEBUG(AT24C, "WriteOk Addr 0x%04x, %u Byte", address, AT24C02_PAGE_SIZE);
                Node->write_bytes += AT24C02_PAGE_SIZE;
            } else {
                LOG_ERROR(AT24C, "WriteErr");
            }
        }
    }

    return res;
}

/*Figure 8. Byte Write*/
bool at24cxx_write_byte(uint8_t num, uint16_t address, uint8_t byte) {
    bool res = false;
    LOG_DEBUG(AT24C, "AT24C_%u WriteByte Addr:0x%x,Byte 0x%02x", num, address, byte);
    At24cxxHandle_t* Node = At24cxxGetNode(num);
    if(Node) {
        uint8_t data[2] = {WORD_LO_BYTE(address), byte};
        res = i2c_api_write(Node->i2c_num, Node->chip_addr, data, sizeof(data));
        if(res) {
            time_delay_ms(10);
            LOG_DEBUG(AT24C, "WriteByteOk Addr 0x%x, 0x%x", address, byte);
            Node->write_bytes += 1;
        } else {
            LOG_ERROR(AT24C, "WriteByteErr");
        }
    }
    return res;
}

bool at24cxx_write_pattern(uint8_t num, uint8_t pattern) {
    uint8_t data[256 + 1];
    LOG_WARNING(AT24C, "%u, Pattern 0x%x", num, pattern);
    memset(data, pattern, sizeof(data));
    bool res = at24cxx_write(num, 0, data, 256);
    return res;
}

bool at24cxx_erase(uint8_t num, uint16_t address, size_t size) {
    bool res = true;
    LOG_WARNING(AT24C, "Erase Addr:0x%x, Size: %u byte", address, size);
    size_t i = 0;
    size_t ok_cnt = 0;
    for(i = 0; i < size; i++) {

        res = at24cxx_write_byte(num, address + i, 0xFF);

#if 0
        uint8_t data[4]={0};
        memset(data,0xff,sizeof(data));
        res = at24cxx_write(  num, address+i, data, 1);
#endif
        if(res) {
            ok_cnt++;
        } else {
            LOG_ERROR(AT24C, "EraseErr Addr 0x%x", address + i);
        }
    }
    if(ok_cnt == size) {
        res = true;
        LOG_INFO(AT24C, "EraseOk %u Byte", size);
    } else {
        LOG_ERROR(AT24C, "EraseErr Done %u %%", 100 * ok_cnt / size);
        res = false;
    }
    return res;
}

bool at24cxx_erase_chip(uint8_t num) {
    bool res = false;
    LOG_WARNING(AT24C, "EraseChip");
    res = at24cxx_erase(num, 0, 256);
    return res;
}
