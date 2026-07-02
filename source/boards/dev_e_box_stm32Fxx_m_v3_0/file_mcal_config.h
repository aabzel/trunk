#ifndef FILE_MCAL_CONFIG_H
#define FILE_MCAL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "file_mcal_types.h"
#include "file_mcal_dep.h"

extern const FileMcalConfig_t FileMcalConfig[];
extern FileMcalHandle_t FileMcalInstance[];

uint32_t file_mcal_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* FILE_MCAL_CONFIG_H */
