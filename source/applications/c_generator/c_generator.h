#ifndef C_GENERATOR_H
#define C_GENERATOR_H

#include <stdbool.h>

#include "c_generator_config.h"
#include "c_generator_diag.h"
#include "c_generator_types.h"

bool c_generator_eof(void);
bool c_generator_mcal_init(void);
bool c_generator_function_cap(char* const function_name);
bool c_generator_proc(void);

#endif /* C_GENERATOR_H */
