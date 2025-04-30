#ifndef MCAL_TYPES_H
#define MCAL_TYPES_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "std_includes.h"
#include "mcal_const.h"
#ifdef HAS_STORAGE
#include "storage_const.h"
#endif

typedef struct {
    uint32_t offset;
    uint8_t num;
    bool valid;
#ifdef HAS_STORAGE
    StorageAccess_t access;
#endif
    char * name;
}Reg32_t;


#ifdef __cplusplus
}
#endif

#endif /* MCAL_TYPES_H */
