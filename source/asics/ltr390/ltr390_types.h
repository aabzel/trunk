#ifndef LTR390_TYPES_H
#define LTR390_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "ltr390_const.h"
#include "ltr390_dep.h"
#include "data_types.h"
#include "gpio_types.h"
#include "ltr390_register_types.h"


typedef struct {
    uint8_t address;
    uint8_t size;
    RegAccess_t access;
    char* name;
    bool valid;
} Ltr390RegisterInfo_t;

typedef struct {
    uint8_t address;
    Ltr390RegGeneral_t value;
} Ltr390Register_t;


typedef struct {
	Ltr390ResolutionCode_t code;
	ResolutionVal_t val;
	double integration_time;
} Ltr390ResolutionInfo_t;

#define LTR390_COMMON_VAR                                  \
    uint8_t num;                                           \
    uint8_t i2c_num;                                       \
    char* name;                                            \
    Pad_t irq;                                             \
    bool valid;


typedef struct {
    LTR390_COMMON_VAR
} Ltr390Config_t;

typedef struct {
    LTR390_COMMON_VAR
    uint32_t err_cnt;
    uint32_t new_data_cnt;
    Ltr390GainVal_t gain;
    ResolutionVal_t resolution;
    double als_lx;
    double uvi; /**/
    double integratin_time_factor;
    DataSource_t cur_source;
    Type32Union_t als_data;
    Type32Union_t uvs_data;

    bool init;
    bool new_data;
} Ltr390Handle_t;

#endif /* LTR390_TYPES_H */
