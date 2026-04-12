#include "rational_num_diag.h"

#include <stdio.h>
#include <string.h>

#include "log.h"

const char* FloatFixToStr(const FloatFixPoint_t* const Node) {
    static char lText[40] = {0};
    if(Node) {
        char format[40] = {0};
        snprintf(format, sizeof(format), "%%d.%%0%uu", Node->accurancy);
        // cli_printf("%s",format);
        snprintf(lText, sizeof(lText), format, Node->integer, Node->fractional);
    }
    return lText;
}
