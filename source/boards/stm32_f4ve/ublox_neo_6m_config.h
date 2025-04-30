#ifndef UBLOX_NEO_6M_CONFIGURATION_H
#define UBLOX_NEO_6M_CONFIGURATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ublox_neo_6m_types.h"

extern const uBloxNeo6mConfig_t uBloxNeo6mConfig[];
extern uBloxNeo6mHandle_t uBloxNeo6mInstance[];

uint32_t ublox_neo_6m_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* UBLOX_NEO_6M_CONFIGURATION_H */
