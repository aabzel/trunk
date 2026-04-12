#ifndef SENSITIVITY_H
#define SENSITIVITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sensitivity_types.h"

PhysicalQuantityInfo_t* UnitsToPhysicalQuantityInfo(const Units_t units) ;
PhysicalQuantity_t units_to_physical_quantity(const Units_t units);

#ifdef __cplusplus
}
#endif

#endif /* SENSITIVITY_H */







