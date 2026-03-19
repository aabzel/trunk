#ifndef IOMUX_MCAL_API_H
#define IOMUX_MCAL_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "iomux_config.h"
#include "iomux_types.h"
#ifdef HAS_IOMUX_DIAG
#include "iomux_diag.h"
#endif

/*API*/
bool iomux_mcal_init(void);
bool iomux_init_one(const IoMuxConfig_t* const Config);
bool iomux_pin_mux_set(Pad_t Pad, uint8_t mux);
bool iomux_pin_mux_get(Pad_t Pad, uint8_t* const mux);

#ifdef __cplusplus
}
#endif

#endif /* IOMUX_MCAL_API_H  */
