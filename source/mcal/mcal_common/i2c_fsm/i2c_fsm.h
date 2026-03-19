#ifndef I2C_FSM_MCAL_API_H
#define I2C_FSM_MCAL_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "std_includes.h"
#include "i2c_fsm_diag.h"
#include "i2c_fsm_types.h"
#include "i2c_mcal.h"

/*API*/
bool i2c_fsm_enable(I2cHandle_t* const Node) ;
bool i2c_fsm_empty(uint8_t num);
bool i2c_fsm_init_one(uint8_t num);
bool i2c_fsm_init_one_ll(I2cHandle_t* const Node);
bool i2c_fsm_wait_busy(I2cHandle_t* Node);

/*Read*/
bool i2c_fsm_read(uint8_t num, uint8_t chip_addr, uint8_t* const data, uint32_t size);
bool i2c_fsm_read_mem(uint8_t num, uint8_t chip_addr, uint8_t* const addr, size_t addr_size,
                      uint8_t* const data, size_t size);
bool i2c_fsm_read_byte(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint8_t* const value);
bool i2c_fsm_read_word(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint16_t* const word);
bool i2c_fsm_check_addr(uint8_t num, uint8_t chip_addr);
bool i2c_fsm_scan(uint8_t num);

/*Write*/
bool i2c_fsm_write(uint8_t num, uint8_t chip_addr, const uint8_t* const data, size_t size);
bool i2c_fsm_write_word(uint8_t num, uint8_t chip_addr, const uint16_t word);
bool i2c_fsm_write_byte(uint8_t num, uint8_t chip_addr, uint8_t addr, uint8_t reg_val) ;
bool i2c_fsm_write_byte_verify(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint8_t set_value);
bool i2c_fsm_write_mem(uint8_t num, uint8_t chip_addr, uint16_t address, const uint8_t* const data, size_t size);


#ifdef __cplusplus
}
#endif

#endif /* I2C_FSM_MCAL_API_H */
