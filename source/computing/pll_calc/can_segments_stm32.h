#ifndef CAN_SEGMENT_CALC_H
#define CAN_SEGMENT_CALC_H

#include "std_includes.h"
#include "can_types.h"

bool bxcan_segment_info_calc(const uint32_t bus_freq_hz,
                             const uint32_t bit_rate_hz,
                             CanSegmentInfo_t* const Segment);


bool bxcan_segment_info_calc_all(const uint32_t bus_freq_hz);


#endif /* CAN_SEGMENT_CALC_H  */
