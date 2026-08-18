#ifndef SI4703_SPI_MCAL_H
#define SI4703_SPI_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "si4703_const.h"

bool si4703_spi_select_if(uint8_t num) ;
bool si4700_spi_read(uint8_t num, uint8_t* const data , const uint8_t size) ;
bool si4703_spi_read_reg(const uint8_t num,const  Si4703RegAddr_t reg_addr, uint16_t* const  reg_val) ;
bool si4703_spi_write_reg(const uint8_t num, const Si4703RegAddr_t reg_addr, const uint16_t reg_val) ;

#ifdef __cplusplus
}
#endif

#endif /* SI4703_SPI_MCAL_H */
