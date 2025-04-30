#ifndef CLOCKS_CUSTOM_DRV_H
#define CLOCKS_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "clock_custom_types.h"

nrf_clock_domain_t ClockDomainToNrfxDomain(ClockDomain_t domain) ;
nrf_clock_hfclk_div_t  ClockDividerToNrfDivider(uint8_t divider);
extern const ClockInfo_t ClockInfo[4];
uint32_t clock_freq_get(nrf_clock_domain_t domain_nrf) ;
bool clock_nrfx_sleep(void);
ClockSource_t   clock_nrf_src_get(nrf_clock_domain_t domain_nrf);
ClockDomain_t ClockNrfDomain2Domain(nrf_clock_domain_t nrf_clock_domain);

#ifdef __cplusplus
}
#endif

#endif // CLOCKS_CUSTOM_DRV_H
