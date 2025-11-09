#ifndef LIS3DH_DRV_H
#define LIS3DH_DRV_H

#include "std_includes.h"
#include "lis3dh_config.h"
#include "lis3dh_types.h"
#include "asics_types.h"
#ifdef HAS_LIS3DH_DIAG
#include "lis3dh_diag.h"
#endif

extern const Lis3dhOperationModeInfo_t OperationModeInfo[];

/*API*/
bool lis3dh_mcal_init(void);
bool lis3dh_proc(void);
bool lis3dh_link_proc(void);
bool lis3dh_init_one(uint8_t num);
bool lis3dh_proc_one(uint8_t num);
bool lis3dh_check(uint8_t num);
bool lis3dh_init_custom(void);
const Lis3dhConfig_t* Lis3dhGetConfig(uint8_t num);
Lis3dhHandle_t* Lis3dhGetNode(uint8_t num);

// computing

bool lis3dh_accel_read(uint32_t num, VectorF_t* const AccelReal);

bool lis3dh_is_valid_addr(uint8_t reg_addr);
bool lis3dh_adc_to_real_ll(Lis3dhHandle_t* const Node );
bool lis3dh_adc_to_real(Lis3dhAcceleration_t* const Acceleration, int8_t mg_per_digit,int8_t bit_depth);
uint32_t lis3dh_operation_mode_cnt(void);
const Lis3dhOperationModeInfo_t* Lis3dhOpModeInfoGetByOpMode(Lis3dhOperationMode_t operation_mode);
const AsicReg8bitInfo_t* Lis3dhRegAddrToInfo(Lis3dhRegAddr_t addr);
uint32_t lis3dh_static_reg_cnt(void);

/*getters*/
bool lis3dh_acceleration_slow_get_ll(Lis3dhHandle_t* Node, Lis3dhAcceleration_t* const Acceleration);
bool lis3dh_acceleration_fast_get_ll(Lis3dhHandle_t* Node, Lis3dhAcceleration_t* const Acceleration);
int8_t lis3dh_sensitivity_get(uint8_t num);
bool lis3dh_operation_mode_get_ll(Lis3dhHandle_t* const Node,
                                  Lis3dhOperationMode_t* const operation_mode) ;
bool lis3dh_is_connected(uint8_t num);
bool lis3dh_acceleration_get(uint8_t num,Lis3dhAcceleration_t* const Acceleration);
bool lis3dh_bit_depth_get(uint8_t num,Lis3dhBitDepth_t* const bit_depth);
bool lis3dh_operation_mode_get(uint8_t num, Lis3dhOperationMode_t* const operation_mode);
bool lis3dh_reg_read(uint8_t num, Lis3dhRegAddr_t reg_addr, uint8_t* const reg_val);
bool lis3dh_reg_read_ll(Lis3dhHandle_t* Node, Lis3dhRegAddr_t addr, uint8_t* const reg_val);
bool lis3dh_reg_read_all(uint8_t num);
uint32_t lis3dh_reg_cnt(void);

/*setters*/
bool lis3dh_power_limit_set(uint8_t num, double power_limit);
bool lis3dh_reg_write_ll(Lis3dhHandle_t* Node, Lis3dhRegAddr_t addr, uint8_t value);
bool lis3dh_reg_write(uint8_t num, Lis3dhRegAddr_t reg_addr, uint8_t reg_val);
bool lis3dh_reg_write_verify(uint8_t num, Lis3dhRegAddr_t reg_addr, uint8_t value);
bool lis3dh_reg_write_lazy(uint8_t num, Lis3dhRegAddr_t reg_addr, uint8_t value);
bool lis3dh_reg_write_by_bitmask(uint8_t num, Lis3dhRegAddr_t reg_addr, char* bit_mask);
bool lis3dh_reset(uint8_t num);

#endif /* LIS3DH_DRV_H */
