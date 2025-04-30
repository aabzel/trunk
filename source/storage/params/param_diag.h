#ifndef PARAM_DIAG_H
#define PARAM_DIAG_H

#include "std_includes.h"
#include "param_types.h"

bool param_default(char* keyWord1, char* keyWord2);
bool param_diag(char* keyWord1, char* keyWord2);
char* ParamId2Str(Id_t id);
const char* param_val2str(Id_t id, uint8_t* const value, uint32_t size);

#endif /* PARAM_DIAG_H  */
