#ifndef KEYLOG_H
#define KEYLOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "keylog_types.h"
#include "keyboard_types.h"

#ifndef HAS_KEYLOG
#error "+HAS_KEYLOG"
#endif

extern KeyLog_t KeyLog;

bool save_key(const KeyBoard_t* const KeyToSave);
bool keylog_proc(void);
bool keylog_mcal_init(void);

#ifdef __cplusplus
}
#endif

#endif /* KEYLOG_H */
