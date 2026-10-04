#ifndef DRV8870_CONFIG_H
#define DRV8870_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "drv8870_types.h"
#include "drv8870_dep.h"

extern const Drv8870Config_t Drv8870Config[];
extern Drv8870Handle_t Drv8870Instance[];

uint32_t drv8870_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* DRV8870_CONFIG_H */
