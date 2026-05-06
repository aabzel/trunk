#ifndef SLIDING_INTEGRAL_H
#define SLIDING_INTEGRAL_H

#include "std_includes.h"
#include "sliding_integral_config.h"
#include "sliding_integral_types.h"

#ifdef HAS_SLIDING_INTEGRAL_DIAG
#include "sliding_integral_diag.h"
#endif

// API
SlidingIntegralHandle_t* SlidingIntegralGetNode(uint8_t num);
const SlidingIntegralConfig_t* SlidingIntegralGetConfig(uint8_t num);


bool sliding_integral_pop_ll(SlidingIntegralHandle_t *Node, int32_t x0, int32_t *const out) ;

bool sliding_integral_proc_in_out_ll(SlidingIntegralHandle_t *Node, const int32_t x, int32_t *const y);
bool sliding_integral_proc_in_out(uint8_t num, int32_t x0, int32_t* const y);

bool sliding_integral_proc_in_out_array(uint8_t num,
                                        uint32_t size,
                                        const int32_t* const x,
                                        int32_t* const y);


bool sliding_integral_init_one(uint8_t num);
bool sliding_integral_mcal_init(void);

/* setters */
bool sliding_integral_reset_one(uint8_t num);


/* getters */
int32_t sliding_integral_order_get(uint8_t num);



#endif
