#ifndef WM8731_CONFIG_H
#define WM8731_CONFIG_H


#include "std_includes.h"
#include "wm8731_types.h"

extern const Wm8731Config_t Wm8731Config[];
extern Wm8731Handle_t Wm8731Instance[];


uint32_t wm8731_get_cnt(void);
//uint32_t wm8731_get_config_cnt(void);

#endif /* WM8731_CONFIG_H */
