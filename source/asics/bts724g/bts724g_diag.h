#ifndef BTS724G_DIAG_H
#define BTS724G_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bts724g_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_BTS724G
#error "+HAS_BTS724G"
#endif

#ifndef HAS_BTS724G_DIAG
#error "+HAS_BTS724G_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool bts724g_diag(char* key_word1, char* key_word2);
bool bts724g_diag_one(uint8_t num);
const char* Bts724gNumToStr(uint8_t num);
const char* Bts724gConfigToStr(const Bts724gConfig_t* const Config);
const char* Bts724gNodeToStr(const Bts724gHandle_t* const Node);
const char* Bts724gNodeToStrShort(const Bts724gHandle_t* const Node);
const char* Bts724gModeToStr(Bts724gPinMode_t mode);

#ifdef __cplusplus
}
#endif

#endif /* BTS724G_DIAG_H  */
