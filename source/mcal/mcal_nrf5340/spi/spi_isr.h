#ifndef SPI_ISR_H
#define SPI_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spi_drv.h"

#include <stdbool.h>

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /*HAS_SPI*/

#ifndef HAS_SPI_ISR
#error "+HAS_SPI_ISR"
#endif /*HAS_SPI_ISR*/

bool ProcNrfxSpimEventHandler(SpiHandle_t* SpimNode, nrfx_spim_evt_t const* p_event);

#ifdef NRFX_SPIM0_ENABLED
void nrfx_spim0_event_handler(nrfx_spim_evt_t const* p_event, void* p_context);
#endif

#ifdef NRFX_SPIM1_ENABLED
void nrfx_spim1_event_handler(nrfx_spim_evt_t const* p_event, void* p_context);
#endif

#ifdef NRFX_SPIM2_ENABLED
void nrfx_spim2_event_handler(nrfx_spim_evt_t const* p_event, void* p_context);
#endif

#ifdef NRFX_SPIM3_ENABLED
void nrfx_spim3_event_handler(nrfx_spim_evt_t const* p_event, void* p_context);
#endif

#ifdef NRFX_SPIM4_ENABLED
void nrfx_spim4_event_handler(nrfx_spim_evt_t const* p_event, void* p_context);
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPI_ISR_H */
