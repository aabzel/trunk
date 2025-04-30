#ifndef DOT_H
#define DOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifndef HAS_DOT
#error "+ HAS_DOT"
#endif

bool dot_header(FILE *file, char* dir);
bool dot_tail(FILE *file);

#ifdef __cplusplus
}
#endif

#endif /* DOT_H */
