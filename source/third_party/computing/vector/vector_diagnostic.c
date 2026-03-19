#include "vector_diagnostic.h"

#include <stdio.h>
#include <string.h>

#define SNPRINTF_AXIS(AXIS)    \
  snprintf(text, sizeof(text), "%sd"#AXIS":%6.2f,", text, Node->d##AXIS);

const char* VECTOR_fToStr(const VECTOR_F* const Node)
{
    static char text[80] = "";
    if(Node)
    {
        strcpy(text, "");
        SNPRINTF_AXIS(x)
        SNPRINTF_AXIS(y)
        snprintf(text, sizeof(text), "%sdz:%6.2f", text, Node->dz);
    }
    return text;
}

