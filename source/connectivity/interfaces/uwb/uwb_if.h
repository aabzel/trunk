#ifndef UWB_DRV_H
#define UWB_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "uwb_if_types.h"

bool uwb_is_vaild_distance(double distance_m);
bool uwb_send(const uint8_t* const buff, uint32_t size);

#endif /* UWB_DRV_H  */
