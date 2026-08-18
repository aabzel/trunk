#ifndef SA51034_TYPES_H
#define SA51034_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "sa51034_registers_types.h"
#include "sa51034_const.h"
#include "audio_types.h"
#include "storage_const.h"

typedef struct {
    Sa51034RegAddr_t addr;
    Sa51034RegUniversal_t Reg; /*register value*/
}Sa51034RegVal_t;

#define POWER_LIMIT_COMMON_VARIABLES \
    Sa51PowerLimit_t code;    \
    double power_limit_v;

typedef struct {
	POWER_LIMIT_COMMON_VARIABLES
}Sa51034PowerLimitInfo_t;

typedef struct {
	POWER_LIMIT_COMMON_VARIABLES
    double diff_v;
}Sa51034PowerLimitItem_t;

typedef struct {
    Sa51034RegAddr_t addr;
    char* name;
    StorageAccess_t access;
    bool valid;
}Sa51034RegInfo_t;


#define SA51034_COMMON_VARIABLE     \
    Gain_t gain;                    \
    Pad_t mute;                     \
    Pad_t shutdown;                 \
    Pad_t fault_z;                  \
    Pad_t power_enable;             \
    GpioLogicLevel_t power_active_level;       \
    uint32_t frequency_hz;          \
    Sa51PowerLimit_t power_limit;   \
    bool valid ;                    \
    uint8_t num ;                   \
    uint8_t chip_addr ;             \
    uint8_t i2c_num;

typedef struct{
    SA51034_COMMON_VARIABLE
    Sa51034RegVal_t* RegVals;
    uint32_t reg_val_cnt;
    char *name;
}Sa51034Config_t;

typedef struct{
    SA51034_COMMON_VARIABLE
    Sa51034RegLatchedFault_t LatchedFault;
    Sa51034RegStatusAndLoadDiagnostic_t StatusAndLoadDiagnostic ;
    Sa51034RegControlRegister_t ControlRegister;
    bool init;
}Sa51034Handle_t;



#endif /* SA51034_TYPES_H */
