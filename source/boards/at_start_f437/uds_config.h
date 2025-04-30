#ifndef UDS_CONFIG_H
#define UDS_CONFIG_H

#include "uds_types.h"


extern const RoutineIdentifierConfig_t RoutineIdentifierConfig[] ;

extern const DidConfig_t DidConfig[] ;
extern DidHandle_t DidInstance[] ;

extern const UdsConfig_t UdsConfig[];
extern UdsHandle_t UdsInstance[];

uint32_t uds_get_cnt(void);
uint32_t did_get_cnt(void);
uint32_t routine_identifier_get_cnt(void);

#endif /*UDS_CONFIG_H*/
