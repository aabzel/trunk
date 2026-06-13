#ifndef FILE_API_CONFIG_H
#define FILE_API_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "file_api_types.h"
#include "file_api_dep.h"

extern const FileApiConfig_t FileApiConfig[];
extern FileApiHandle_t FileApiInstance[];

uint32_t file_api_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* FILE_API_CONFIG_H */
