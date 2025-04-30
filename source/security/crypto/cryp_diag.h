#ifndef CRYP_DIAG_H
#define CRYP_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "cryp_const.h"

#ifndef HAS_CRYP_DIAG
#error "+HAS_CRYP_DIAG"
#endif

#ifndef HAS_CRYP
#error "+HAS_CRYP"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

const char* CrypAlgo2Str(CrypAlgorithm_t Algo);
const char* AlgoImpl2Str(AlgImpl_t Algo);

bool cryp_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* CRYP_DIAG_H */

