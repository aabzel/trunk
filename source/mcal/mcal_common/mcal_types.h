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

/*reference of register*/
typedef struct {
    uint32_t offset; /*memory map register offset*/
    uint8_t num;
    uint8_t size; /*register size in bytes*/
    bool valid;
#ifdef HAS_STORAGE
    StorageAccess_t access;
#endif
    char * name; /*register name*/
}Reg32_t;


#ifdef __cplusplus
}
#endif

#endif /* MCAL_TYPES_H */
