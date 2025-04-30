#ifndef SW_DAC_DIAG_H
#define SW_DAC_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "sw_dac_const.h"

#ifndef HAS_DIAG
#error  "+HAS_DIAG"
#endif /*HAS_DIAG*/

#ifndef HAS_SW_DAC
#error  "+HAS_SW_DAC"
#endif /*HAS_SW_DAC*/


#ifndef HAS_SW_DAC_DIAG
#error  "+HAS_SW_DAC_DIAG"
#endif /*HAS_SW_DAC_DIAG*/

#include "sw_dac_types.h"


const char* SwDacNodeToStr(const SwDac_t* const Node);
const char* FramePattern2Str(FramePattern_t frame_pattern);
const char* SampleSize2Format(uint8_t sample_size);
const char* SwDacMode2Str(SwDacMode_t mode);
bool sw_dac_diag(void) ;
bool sw_dac_print_track(uint8_t dac_num) ;
bool SwDacConfigDiag(const SwDacConfig_t* const Config) ;
bool SwDacNodeDiag(const SwDac_t* const Node) ;

#endif /*DAC_DIAG_H*/
