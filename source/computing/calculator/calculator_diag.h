#ifndef CALCULATOR_DIAG_H
#define CALCULATOR_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "calculator_types.h"

const char* Operation2Str(Operation_t op);
const char* CalcNode2Str(const Calculator_t* const  Node);
const char* OperationNode2Str(const OperationData_t* const Node);


#ifdef __cplusplus
}
#endif

#endif /* CALCULATOR_DIAG_H */
