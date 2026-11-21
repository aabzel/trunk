/* vim: set ai et ts=4 sw=4: */
#ifndef __FONTS_RUS_H__
#define __FONTS_RUS_H__

#include "fonts_types.h"


extern FontDef FontRus_7x10;
extern FontDef FontRus_11x18;
extern FontDef FontRus_16x26;

const FontLettetInfo_t* FontLetterToInfo(const char* const letter);

#endif // __FONTS_RUS_H__
