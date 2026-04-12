#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include "std_includes.h"

typedef struct{
    uint32_t start;
    uint32_t end;
    char* name ;
    bool valid ;
}ProccessSectorInfo_t;

#endif /* COMMON_TYPES_H */
