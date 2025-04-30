#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#include "histogram_config.h"
#include "histogram_types.h"
#include "histogram_diag.h"

#ifndef HAS_HISTOGRAM
#error "+HAS_HISTOGRAM"
#endif

HistogramHandle_t* HistogramGetNode(uint8_t num);
const HistogramConfig_t* HistogramGetConfig(uint8_t num);

bool histogram_get_max(uint8_t num, HistogramItem_t* const Item);
bool histogram_add(uint8_t num, int32_t value);
bool histogram_add_ll(HistogramHandle_t* const Node, int32_t value);
bool histogram_mcal_init(void);
bool histogram_init_one(uint8_t num);
bool histogram_init_custom(void);


#ifdef __cplusplus
}
#endif

#endif /* HISTOGRAM_H */
