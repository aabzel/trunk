#ifndef FILE_API_CUSTOM_H
#define FILE_API_CUSTOM_H

#include <stdio.h>

#ifdef HAS_MCU
#error That code only for desktop PC builds
#endif

#define FILE_API_CUSTOM_VARIABLES \
    FILE *FilePtr;


#endif /* FILE_API_CUSTOM_H */
