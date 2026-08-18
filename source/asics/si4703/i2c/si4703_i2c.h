#ifndef SI4703_I2C_H
#define SI4703_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "si4703_types.h"

/* API */

/*setters*/
bool si4703_i2c_select_if(uint8_t num);
bool si4703_i2c_write_reg(const uint8_t num,const  Si4703RegAddr_t reg_addr,const  uint16_t reg_val);

/*getters*/
bool si4703_i2c_read_reg(const uint8_t num, const Si4703RegAddr_t reg_addr, uint16_t* const reg_val);






#ifdef __cplusplus
}
#endif

#endif /* SI4703_I2C_H */
