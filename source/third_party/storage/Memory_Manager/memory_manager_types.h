#ifndef MEMORY_MANAGER_TYPES_H
#define MEMORY_MANAGER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "general_types.h"
#include "memory_manager_const.h"

typedef union{
    U8 byte;
    struct {
        U8 read : 1; // bit 0 READ
        U8 write : 1;// bit 1 WRITE
        U8 erase: 1;// bit 3 ERASE
        U8 reserved: 5;//reserved
    };
}MEMORY_MANAGER_PERMISSIONS;


typedef struct{
    U8 deviceNumber;
    U8 valid;
    U8 permissions    ;
    U32 baseAddress ;
    U32 size          ;
}MEMORY_MANAGER_BANK_INFO;


#ifdef __cplusplus
}
#endif

#endif /* MEMORY_MANAGER_TYPES_H */



