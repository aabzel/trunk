#ifndef COMPILER_CONST_H
#define COMPILER_CONST_H


#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_CLANG
#include "clang_const.h"
#endif

#ifdef HAS_ARM_GCC
#include "gcc_const.h"
#endif

#ifdef HAS_MINGW
#include "mingw_const.h"
#endif

#ifdef HAS_IAR
#include "iar_const.h"
#endif

#ifdef HAS_KEIL
#include "keil_const.h"
#endif

#ifdef HAS_TCC
#include "tcc_const.h"
#endif


#ifdef __cplusplus
}
#endif

#endif /* COMPILER_CONST_H */





