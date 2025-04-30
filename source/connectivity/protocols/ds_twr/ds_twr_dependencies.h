#ifndef DS_TWR_DEP_H
#define DS_TWR_DEP_H

#ifndef HAS_ARRAY
#error "+HAS_ARRAY"
#endif

#ifndef HAS_UWB
#warning "+HAS_UWB"
#endif

#include "decawave_dep.h"

#ifndef HAS_DS_TWR
#error "+HAS_DS_TWR"
#endif

#ifndef HAS_PARAM
#warning "+HAS_PARAM"
#endif

#ifndef HAS_TBFP
#error "+HAS_TBFP"
#endif


#endif /* DS_TWR_DEP_H  */
