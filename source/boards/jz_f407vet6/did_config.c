#include "did_config.h"

#include "data_utils.h"
#include "storage_const.h"

#define DID_CONGID_READ_WRITE

#define DID_CONGID_READ_ONLY              \
    {.num=(__COUNTER__+1),  .did=UDS_DID_TIME_STAMP, .name="UpTimeMs",   .nvram=false, .access=ACCESS_READ_ONLY,  .type=TYPE_UINT32, .size=4, .default_value="-",.valid= true,},


#define DID_CONGID_ALL       \
    DID_CONGID_READ_ONLY     \
    DID_CONGID_READ_WRITE

const DidConfig_t DidConfig[] = {
    DID_CONGID_ALL
};

DidHandle_t DidInstance[] = {
    {.num=1, .valid= true,},
    {.num=2, .valid= true,},
    {.num=3, .valid= true,},
};

COMPONENT_GET_CNT(Did, did)

