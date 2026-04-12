#ifndef STORAGE_EHAL_DIAGNOSTIC_H
#define STORAGE_EHAL_DIAGNOSTIC_H

#ifdef HAS_EHAL
#include "platform.h"
#endif

#include "storage_type.h"

STORAGE_INFO* STORAGE_GetInfo(STORAGE_TYPE type);

const char* STORAGE_AccessToStr(STORAGE_ACCESS access);

const char* STORAGE_TypeToStr(STORAGE_TYPE type);

const char* STORAGE_DataToStr(const U8*const buff, U32 size, STORAGE_TYPE type );

U8 STORAGE_DataToStrLine(const  U8* const buff, U32 value_len,
                         STORAGE_TYPE type, char* const  outStr, U32 str_size);
#endif /* STORAGE_EHAL_DIAGNOSTIC_H */
