#ifndef MATH_COMMANDS_H
#define MATH_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_MATH
#error "+ HAS_MATH"
#endif /*HAS_MATH*/

#ifndef HAS_MATH_COMMANDS
#error "+ HAS_MATH_COMMANDS"
#endif /*HAS_MATH_COMMANDS*/

bool math_vector_angle_command(int32_t argc, char* argv[]);

#define MATH_COMMANDS                                                                   \
    SHELL_CMD("math_vector_angle", "mva", math_vector_angle_command, "MathVectorAngle"),

#ifdef __cplusplus
}
#endif

#endif /* MATH_COMMANDS_H */
