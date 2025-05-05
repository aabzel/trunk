#ifndef FILE_API_TYPES_H
#define FILE_API_TYPES_H

#include "std_includes.h"
#ifdef HAS_FILE_API_CUSTOM
#include "file_api_types_custom.h"
#else
#define FILE_API_CUSTOM_VARIABLES
#endif
#include "file_api_const.h"

typedef struct {
    FILE_API_CUSTOM_VARIABLES
    bool valid;
} FileApiHandle_t;

#endif /* FILE_API_TYPES_H */
