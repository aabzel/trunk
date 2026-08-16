#ifndef MATH_COMMANDS_H
#define MATH_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_MATH
#error "+ HAS_MATH"
#endif /*HAS_MATH*/

#ifndef HAS_MATH_COMMANDS
#error "+ HAS_MATH_COMMANDS"
#endif /*HAS_MATH_COMMANDS*/

bool math_sum4_d_command(int32_t argc, char* argv[]);
bool math_sum4_command(int32_t argc, char* argv[]);
bool math_sum3_command(int32_t argc, char* argv[]);
bool math_div_n_m_command(int32_t argc, char* argv[]);
bool math_vector_angle_command(int32_t argc, char* argv[]);

#define MATH_COMMANDS                                                                   \
    SHELL_CMD("math_div_nm", "div_nm", math_div_n_m_command, "MathDivNm"),                 \
    SHELL_CMD("math_sum4_dyn", "ms4d", math_sum4_d_command, "MathSum4Dynamic"),                 \
    SHELL_CMD("math_sum3", "ms3", math_sum3_command, "MathSum3"),                 \
    SHELL_CMD("math_sum4", "ms4", math_sum4_command, "MathSum4"),                 \
    SHELL_CMD("math_vector_angle", "mva", math_vector_angle_command, "MathVectorAngle"),

#ifdef __cplusplus
}
#endif

#endif /* MATH_COMMANDS_H */
