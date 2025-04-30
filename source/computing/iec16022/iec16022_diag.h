#ifndef IEC16022_DIAG_H
#define IEC16022_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool iec16022_print_cli(unsigned char *ret ,int w , int h);
bool iec16022_print_graphviz(unsigned char *ret ,int w , int h, char* name);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*IEC16022_DIAG_H*/
