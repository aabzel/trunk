#include "storage_config.h"

#include "array.h"
#include "std_includes.h"
#include "storage_diag.h"
#include "storage_types.h"

#ifdef HAS_KEEPASS
#include "keepass_params.h"
#else
#define PARAMS_KEEPASS
#endif

#ifdef HAS_PASTILDA
#include "pastilda_params.h"
#else
#define PARAMS_PASTILDA
#endif

#ifdef HAS_GENERIC
#include "generic_params.h"
#else
#define PARAMS_GENERIC
#endif

#ifdef HAS_TIME
#include "time_params.h"
#else
#define PARAMS_TIME
#endif

/*TODO: Sort by index for bin search in future*/
const StorageItem_t StorageArray[] = {PARAMS_GENERIC PARAMS_KEEPASS PARAMS_PASTILDA PARAMS_TIME};

uint32_t storage_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(StorageArray);
    return cnt;
}
