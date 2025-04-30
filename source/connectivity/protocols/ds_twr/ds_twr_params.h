#ifndef DS_TWR_PARAMS_H
#define DS_TWR_PARAMS_H

#include "param_types.h"

#define DS_TWR_PARAMS                                                                                 \
    {.facility=DS_TWR, .id=PAR_ID_PHASE1_OFFSET,  .len=8, .type=TYPE_DOUBLE, .name="Phase1Offset"},   \
    {.facility=DS_TWR, .id=PAR_ID_PHASE2_OFFSET,  .len=8, .type=TYPE_DOUBLE, .name="Phase2Offset"},   \
    {.facility=DS_TWR, .id=PAR_ID_FINAL_OFFSET,   .len=8, .type=TYPE_DOUBLE, .name="SinalOffset"},



#endif /* DS_TWR_PARAMS_H */
