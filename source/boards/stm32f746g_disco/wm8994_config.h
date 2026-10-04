#ifndef WM8994_CONFIG_H
#define WM8994_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "wm8994_types.h"
#include "wm8994_dep.h"

extern const Wm8994Config_t Wm8994Config[];
extern Wm8994Handle_t Wm8994Instance[];

uint32_t wm8994_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* WM8994_CONFIG_H */
