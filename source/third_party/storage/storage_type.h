#ifndef STORAGE_EHAL_TYPES_H
#define STORAGE_EHAL_TYPES_H

#include "storage_constants.h"

typedef struct{
    STORAGE_TYPE type;
    U16 typeSize;
    char* typeName;
    U8 valid;
}STORAGE_INFO;

#endif /* STORAGE_EHAL_TYPES_H */
