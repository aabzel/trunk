#ifndef I2C_MCAL_API_H
#define I2C_MCAL_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2c_config.h"
#include "i2c_custom_isr.h"
#include "i2c_custom_types.h"
#include "i2c_diag.h"
#include "i2c_types.h"

I2cHandle_t* I2cGetNode(uint8_t num);
const I2cConfig_t* I2cGetConfig(uint8_t num);
const I2cInfo_t* I2cGetInfo(uint8_t num);

/*API*/
bool i2c_is_init(uint8_t num);
bool i2c_init_one(uint8_t num);
bool i2c_init_common(const I2cConfig_t* const Config, I2cHandle_t* const Node);
bool i2c_proc_one(uint8_t num);
bool i2c_mcal_init(void);
bool i2c_proc(void);
bool i2c_init_custom(void);
uint32_t i2c_reg_cnt(void);

bool i2c_wait_tx_done_ll(I2cHandle_t* const Node, uint32_t time_out_ms);
bool i2c_wait_rx_done_ll(I2cHandle_t* const Node, uint32_t time_out_ms);

/*Read*/
bool i2c_api_read(uint8_t num, uint8_t chip_addr, uint8_t* const data, uint32_t size);
bool i2c_api_read_mem(uint8_t num, uint8_t chip_addr, uint8_t* const addr, size_t addr_size, uint8_t* const data,
                      size_t size);
bool i2c_api_read_byte(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint8_t* const value);
bool i2c_api_read_word(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint16_t* const word);
bool i2c_api_read_byte_old(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint8_t* const value);
bool i2c_check_addr(uint8_t num, uint8_t chip_addr);
bool I2cWaitRxDoneTimeOut(const I2cHandle_t* const Node, uint32_t time_out_ms, uint32_t* const real_time);
bool i2c_scan(uint8_t num);

/*Write*/
bool i2c_api_write(uint8_t num, uint8_t chip_addr, const uint8_t* const data, size_t size);
bool i2c_api_write_mem(uint8_t num, uint8_t chip_addr, uint16_t address, const uint8_t* const data, size_t size);
bool i2c_write_wait(uint8_t num, uint8_t i2c_addr, const uint8_t* const data, size_t size);
bool i2c_send_signal(uint8_t num, I2cSignal_t signal);
bool i2c_api_reg_write(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint8_t value);
bool i2c_api_reg_write_verify(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint8_t set_value);
bool i2c_api_write_general(uint8_t num, uint8_t i2c_addr, const uint8_t* const data, size_t size);

uint16_t RegAddr2Word(uint8_t* const addr, size_t addr_size);
/*Do not change That API without negotiation*/
bool i2c_is_allowed(uint8_t num);
bool i2c_calc_byte_rate(void);
uint32_t i2c_calc_transfer_time_ms(uint32_t baudrate, uint32_t bytes);
uint32_t i2c_calc_transfer_time_us(uint32_t baudrate, uint32_t bytes);
uint8_t i2c_compose_read_address(uint8_t base_addr);
uint8_t i2c_compose_write_address(uint8_t base_addr);

#ifdef __cplusplus
}
#endif

#endif /* I2C_MCAL_API_H */
