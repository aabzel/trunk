#ifndef NVRAM_DIAGNOSTIC_H
#define NVRAM_DIAGNOSTIC_H


#include "nvram_types.h"
#include "general_types.h"
#include "nvram_file_ids.h"

STD_RESULT NVRAM_Default(char* keyWord1, char* keyWord2);
STD_RESULT NVRAM_Diag(char* keyWord1, char* keyWord2);

const char* NVRAM_IdToStr(NVRAM_DATA_ID id);
const char* NVRAM_ValToStr(NVRAM_DATA_ID id, U8* const value, uint32_t size);
const char* NVRAM_VariableInfoToStr(const NVRAM_INFO* const  Info);

#endif /* NVRAM_DIAGNOSTIC_H  */
