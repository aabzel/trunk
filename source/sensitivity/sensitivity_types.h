#ifndef SENSITIVITY_TYPES_H
#define SENSITIVITY_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sensitivity_const.h"
#include "std_includes.h"

typedef struct {
    Units_t units;
    PhysicalQuantity_t physical_quantity;
    char* name_physical_quantity;
    char* name_units;
    bool valid;
} PhysicalQuantityInfo_t;


#ifdef __cplusplus
}
#endif

#endif /* SENSITIVITY_TYPES_H */
