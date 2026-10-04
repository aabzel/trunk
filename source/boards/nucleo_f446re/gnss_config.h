#ifndef GNSS_CONFIG_H
#define GNSS_CONFIG_H

#include "std_includes.h"
#include "gnss_types.h"

#ifndef HAS_GNSS
#error "+HAS_GNSS"
#endif

extern const GnssConfig_t GnssConfig[];
extern GnssHandle_t GnssInstance[];

uint32_t gnss_get_cnt(void);

#endif /* GNSS_CONFIG_H */
