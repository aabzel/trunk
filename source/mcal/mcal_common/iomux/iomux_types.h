#ifndef IOMUX_MCAL_TYPES_H
#define IOMUX_MCAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "iomux_const.h"
#include "gpio_types.h"

#ifdef HAS_EXT_INT
#include "ext_int_const.h"
#endif

#ifdef HAS_IOMUX_CUSTOM
#include "iomux_custom_types.h"
#endif /*HAS_IOMUX_CUSTOM*/

typedef struct {
    Pad_t pad;
    uint8_t mux;
    char* function;
} IoMuxConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* IOMUX_MCAL_TYPES_H  */
