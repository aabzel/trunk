#ifndef QUAD_MIX_4FS_ISR_H
#define QUAD_MIX_4FS_ISR_H

#include <stdbool.h>
#include <stdint.h>

#include "quad_mix_4fs_types.h"

bool quad_mix_4fs_pop_ll(QuadMix4fsHandle_t *Node, QuadMix4fsSample_t x0, QuadMix4fsSample_t *const out) ;

bool quad_mix_4fs_proc_in_out_ll(QuadMix4fsHandle_t *Node, QuadMix4fsSample_t x, QuadMix4fsSample_t *const y);
bool quad_mix_4fs_proc_in_out(uint8_t num, QuadMix4fsSample_t x0, QuadMix4fsSample_t* const y);

bool quad_mix_4fs_proc_in_out_array(uint8_t num,
                           uint32_t size,
                           const QuadMix4fsSample_t* const x,
                           QuadMix4fsSample_t* const y);

#endif
