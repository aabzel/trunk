#ifndef CODE_STYLE_CHECKER_DIAG_H
#define CODE_STYLE_CHECKER_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "code_style_checker_types.h"

bool code_style_checker_diag(void);
bool CodeStyleCheckerDiag(const  CodeStyleCheckerHandle_t* const Node);
const char* CodeStyleCheckerDiag2Str(const CodeStyleCheckerHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* CODE_STYLE_CHECKER_DIAG_H */
