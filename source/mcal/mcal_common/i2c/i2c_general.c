#include "i2c_mcal.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#include "debug_info.h"
#include "sys_config.h"
#include "array_diag.h"
#include "gpio_mcal.h"
#include "time_mcal.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#include "i2c_database.h"
#include "i2c_mcal.h"

#include "code_generator.h"

COMPONENT_GET_NODE(I2c, i2c)

COMPONENT_GET_CONFIG(I2c, i2c)

bool  i2c_is_valid_config(const I2cConfig_t* const Config){
    bool res = false;
    if(Config){
        if(0<Config->clock_speed){
            res=gpio_is_valid_pad(Config->PadScl.byte);
            if(res){
                res=gpio_is_valid_pad(Config->PadSda.byte);
                if(res){
                    res = true;

                }else{
                    res = false;
                }
            }else{
                res = false;
            }
        }else{
            res = false;
        }
    }else{
        res = false;
    }
    return res;
}


bool i2c_init_common(const I2cConfig_t* const Config, I2cHandle_t* const Node){
    bool res = i2c_is_valid_config(Config);
    if(res){
        Node->interrupt_on=Config->interrupt_on;
        Node->num=Config->num;
        Node->interrupt_priority=Config->interrupt_priority;
        Node->PadScl=Config->PadScl;
        Node->PadSda=Config->PadSda;
        Node->own_addr=Config->own_addr;
        Node->clock_speed=Config->clock_speed;
        Node->interrupt_on=Config->interrupt_on;
        Node->valid=true;
    }
    return res;
}




uint32_t i2c_calc_transfer_time_us(uint32_t baudrate, uint32_t bytes) {
    uint32_t tx_time_us = 0;
    float bit_time = 1.0f / (float)baudrate;
    float byte_time = 0.0f;
    byte_time = (9.0) * bit_time;
    float byte_train_duration = byte_time * bytes;
    tx_time_us = (uint32_t)(byte_train_duration * 1000000.0f);
    return tx_time_us;
}

uint32_t i2c_calc_transfer_time_ms(uint32_t baudrate, uint32_t bytes) {
    uint32_t tx_time_us = 0;
    float bit_time = 1.0f / (float)baudrate;
    float byte_time = 0.0f;
    byte_time = (9.0) * bit_time;
    float byte_train_duration = byte_time * bytes;
    tx_time_us = (uint32_t)(byte_train_duration * 1000.0f);
    return tx_time_us;
}

#ifdef HAS_MCU
bool i2c_calc_byte_rate(void) {
    bool res = false;
    uint8_t num = 0;
    for(num = 0; num < i2c_get_cnt(); num++) {
        I2cHandle_t* I2cNode = I2cGetNode(num);
        if(I2cNode) {
            I2cNode->rx_rate.cur = I2cNode->cnt.byte_rx - I2cNode->cnt_prev.byte_rx;
            I2cNode->rx_rate.min = min32u(I2cNode->rx_rate.min, I2cNode->rx_rate.cur);
            I2cNode->rx_rate.max = max32u(I2cNode->rx_rate.max, I2cNode->rx_rate.cur);
            I2cNode->cnt_prev.byte_rx = I2cNode->cnt.byte_rx;

            I2cNode->tx_rate.cur = I2cNode->cnt.byte_tx - I2cNode->cnt_prev.byte_tx;
            I2cNode->tx_rate.min = min32u(I2cNode->tx_rate.min, I2cNode->tx_rate.cur);
            I2cNode->tx_rate.max = max32u(I2cNode->tx_rate.max, I2cNode->tx_rate.cur);
            I2cNode->cnt_prev.byte_tx = I2cNode->cnt.byte_tx;
        }
        res = true;
    }
    return res;
}
#endif

bool i2c_is_init(uint8_t num) {
    bool res = false;
    I2cHandle_t* I2cNode = I2cGetNode(num);
    if(I2cNode) {
        res = I2cNode->init_done;
    }
    return res;
}

bool i2c_is_allowed(uint8_t num) {
    bool res = false;
    bool res1 = false;
    bool res2 = false;
    uint32_t i = 0;
    for(i = 0; i < i2c_get_cnt(); i++) {
        if(num == I2cInstance[i].num) {
            res1 = true;
        }
    }
    for(i = 0; i < i2c_get_cnt(); i++) {
        if(num == I2cConfig[i].num) {
            res2 = true;
        }
    }
    if(res1 && res2) {
        res = true;
    }
    return res;
}

bool i2c_api_write_general(uint8_t num, uint8_t i2c_addr, const uint8_t* const array, size_t array_len) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(I2C, "%u Write chip: 0x%x Len: %u", num, i2c_addr, array_len);
#endif
    res = i2c_write_wait(num, i2c_addr, array, array_len);
#if 0
    res= i2c_wait_write(num, i2c_addr,  array, array_len);
#endif
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(I2C, "%u WriteChipErr: 0x%02x Len: %u", num, i2c_addr, array_len);
#ifdef HAS_STREAM
        print_mem(array, (uint32_t)array_len, true, false, true, true);
#endif
#endif
    }
    return res;
}

bool i2c_scan(uint8_t num) {
    bool res = false;
    uint32_t chip_addr = 0;
    uint32_t cnt = 0;
    for(chip_addr = 0; chip_addr <= 0xFF; chip_addr++) {
        res = i2c_check_addr(num, (uint8_t)chip_addr);
        if(res) {
            cnt++;
#ifdef HAS_I2C_DIAG
            LOG_WARNING(I2C, "%u SpotChipAddr 0x%02x=[%s]", num, chip_addr, I2cGetChipName(chip_addr));
#endif
        }
    }
    if(0 < cnt) {
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(I2C, "%u NoChip", num);
#endif
        res = false;
    }
    return res;
}

uint8_t i2c_compose_read_address(uint8_t base_addr) {
    uint8_t read_address = (base_addr << 1) | 1;
    return read_address;
}

uint8_t i2c_compose_write_address(uint8_t base_addr) {
    uint8_t write_address = base_addr << 1;
    return write_address;
}

bool I2cWaitRxDoneTimeOut(const I2cHandle_t* const Node, uint32_t time_out_ms, uint32_t* const real_time) {
    bool res = false;
    uint32_t diff = 0;
    uint32_t start = time_get_ms32();
    while(1) {
        uint32_t cur = time_get_ms32();
        diff = cur - start;
        if(time_out_ms < diff) {
            res = false;
            break;
        }

        if(Node->rx_int) {
            res = true;
            break;
        }
    }
    *real_time = diff;

    return res;
}
__attribute__((weak))

bool i2c_api_read_word(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint16_t* const word){
    bool res = false ;
    return res;
}

__attribute__((weak))
bool i2c_init_custom(void) {
    bool res = false ;
    return res;
}

__attribute__((weak)) bool i2c_api_reg_write(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint8_t value) {
    bool res = false;
    uint8_t buff[3] = {reg_addr, value};
    LOG_DEBUG(I2C, "I2C%u,RegW,Chip:0x%02x,Addr:0x%02x,Value:0x%02x", num, chip_addr, reg_addr, value);
    res = i2c_api_write(num, chip_addr, buff, 2);
    if(res) {
        LOG_DEBUG(I2C, "I2C%u WriteOk", num);
    } else {
        LOG_ERROR(I2C, "I2C%u WriteErr", num);
    }
    return res;
}

bool i2c_api_reg_write_verify(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint8_t set_value) {
    bool res = false;
    LOG_DEBUG(I2C, "I2C%u RegWv,Chip:0x%02x,Addr:0x%02x,Value:0x%02x", num, chip_addr, reg_addr, set_value);
    res = i2c_api_reg_write(num, chip_addr, reg_addr, set_value);
    if(res) {
        uint8_t get_value = 0;
        res = i2c_api_read_byte(num, chip_addr, reg_addr, &get_value);
        if(get_value == set_value) {
            res = true;
        } else {
            LOG_ERROR(I2C, "I2C%u,RegWriteSetGetErr,0x%x!=0x%x", num, set_value, get_value);
            res = false;
        }
    }

    return res;
}

bool i2c_wait_tx_done_ll(I2cHandle_t* const Node, uint32_t time_out_ms) {
    bool res = false;
    if(Node) {
        uint32_t start = time_get_ms32();
        res = true;
        while(false == Node->tx_done) {
            uint32_t cur = time_get_ms32();
            uint32_t diff = 0;
            diff = cur - start;
            if(time_out_ms < diff) {
                res = false;
                LOG_ERROR(I2C, "I2C%u,TimeOut:%u ms", Node->num,time_out_ms);
                break;
            }
        }
    }
    return res;
}

bool i2c_wait_rx_done_ll(I2cHandle_t* const Node, uint32_t time_out_ms) {
    bool res = false;
    if(Node) {
        res = true;
        uint32_t diff = 0;
        uint32_t start = time_get_ms32();
        while(false == Node->rx_done) {
            uint32_t cur = time_get_ms32();
            diff = cur - start;
            if(time_out_ms < diff) {
                res = false;
                break;
            }
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT_CNT(I2C, I2C, i2c, I2C_COUNT)
COMPONENT_PROC_PATTERT_CNT(I2C, I2C, i2c, I2C_COUNT)
