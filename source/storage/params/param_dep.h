#ifndef PARAM_DEP_H
#define PARAM_DEP_H

#ifndef HAS_FLASH
#warning "+HAS_FLASH"
#endif

#ifndef HAS_FLASH_FS
#error "+HAS_FLASH_FS"
#endif

#ifndef HAS_PARAM
#warning "+HAS_PARAM"
#endif

#ifndef HAS_PARAM_SET
#warning "+HAS_PARAM_SET"
#endif

#endif /* PARAM_DEP_H  */
