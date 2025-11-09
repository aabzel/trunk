#ifndef LIS3DH_I2C_H
#define LIS3DH_I2C_H

#include "std_includes.h"
#include "lis3dh_config.h"
#include "lis3dh_types.h"
#include "asics_types.h"
#include "i2c_mcal.h"
#ifdef HAS_LIS3DH_DIAG
#include "lis3dh_diag.h"
#endif

bool lis3dh_i2c_reg_read_ll(Lis3dhHandle_t *Node, Lis3dhRegAddr_t addr, uint8_t *const byte) ;
bool lis3dh_i2c_reg_write_ll(Lis3dhHandle_t *Node, Lis3dhRegAddr_t addr, uint8_t byte) ;

#endif /* LIS3DH_I2C_H */
