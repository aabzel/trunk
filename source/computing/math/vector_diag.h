#ifndef VECTOR_DIAG_H
#define VECTOR_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "vector_types.h"

bool math_vector_angle_diag(char* key_word1, char* key_word2);
const char* VectorToStr(const Vector_t* const Node);
const char* VectorFtoStr(const VectorF_t* const Node);
void print_line(Line_t line, char* text);
void print_dot(Dot_t d, char* text);
void print_vector(Vector_t v, char* text);

#ifdef __cplusplus
}
#endif

#endif /*VECTOR_DIAG_H*/
