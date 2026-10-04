#ifndef W25M02GV_TYPES_H
#define W25M02GV_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "w25m02gv_registers_types.h"
#include "w25m02gv_const.h"
#include "storage_const.h"

typedef struct {
    W25m02gvRegAddr_t addr;
    W25m02gvRegUniversal_t Reg; /*register value*/
}W25m02gvRegVal_t;



typedef struct {
    W25m02gvRegAddr_t addr;
    char* name;
    StorageAccess_t access;
    bool valid;
}W25m02gvRegInfo_t;


#define W25M02GV_COMMON_VARIABLE     \
    bool valid ;                     \
    uint8_t num ;                    \
    uint8_t spi_num;                 \
    Pad_t ChipSelect;                \
    Pad_t Hold;                      \
    Pad_t WriteProtect;

typedef struct {
    W25M02GV_COMMON_VARIABLE
    W25m02gvRegVal_t* RegArray;
    uint32_t reg_cnt;
    char *name;
}W25m02gvConfig_t;

typedef struct{
    W25M02GV_COMMON_VARIABLE
    bool init;
    w25m02gvRegProtection_t RegProtect;
    w25m02gvRegStatus_t RegStatus;
    w25m02gvRegConfiguration_t RegConfig;
}W25m02gvHandle_t;

#endif /* W25M02GV_TYPES_H */
