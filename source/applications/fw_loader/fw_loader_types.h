#ifndef FW_LOADER_TYPES_H
#define FW_LOADER_TYPES_H

#include "std_includes.h"
#include "data_types.h"
#include "fw_loader_const.h"

#define FW_LOADER_COMMON_VARIABLES      \
    uint8_t num;                        \
    uint8_t com_num;                    \
    uint8_t tbfp_num;                   \
    uint8_t serial_num;                 \
    uint32_t bit_rate;                  \
    char* hex_file_name;                \
    bool valid;

typedef struct {
    FW_LOADER_COMMON_VARIABLES
} FwLoaderConfig_t;

typedef struct {
    FW_LOADER_COMMON_VARIABLES
    bool init;
} FwLoaderHandle_t;

#endif /* FW_LOADER_TYPES_H */
