#ifndef KEYBOARD_DIAG_H
#define KEYBOARD_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "keyboard_types.h"

#ifndef HAS_KEYBOARD
#error "+HAS_KEYBOARD"
#endif

#ifndef HAS_KEYBOARD_DIAG
#error "+HAS_KEYBOARD_DIAG"
#endif

const char* KeyBoard2Str(const KeyBoard_t* const key_code);

#ifdef __cplusplus
}
#endif

#endif /* KEYBOARD_DIAG_H */
