#ifndef CODE_STYLE_CHECKER_H
#define CODE_STYLE_CHECKER_H

#include <stdbool.h>

#include "code_style_checker_config.h"
#include "code_style_checker_diag.h"
#include "code_style_checker_types.h"

bool code_style_checker_mcal_init(void);

/*[REQ_CODE_0412] The order of function declarations must match the order of function definitions*/
bool code_style_checker_proto(const char* const file_name_c, const char *const file_name_h);
bool code_style_checker_global_proto(const char *const file_name_c, const char *const h_file_name);
bool code_style_checker_static_proto(const char *const file_name_c);

#endif /* CODE_STYLE_CHECKER_H */
