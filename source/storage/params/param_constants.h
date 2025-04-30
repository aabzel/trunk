#ifndef PARAM_CONSTANTS_H
#define PARAM_CONSTANTS_H

#ifdef HAS_FLASH_FS
#include "flash_fs_file_ids.h"
#endif

#include "param_dep.h"

#ifndef HAS_FLASH_FS
#error "Params need FLASH_FS"
#endif


#ifndef HAS_PARAM
#error "+HAS_PARAM"
#endif

#define ID_TYPE_LINK_INFO 0x0A /*4 bit val*/
#define TYPE_UNDEF_LEN 0xFFFF


#endif /* PARAM_CONSTANTS_H  */
