#ifndef LITTLE_FS_DIAG_H
#define LITTLE_FS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "little_fs_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_LITTLE_FS
#error "+HAS_LITTLE_FS"
#endif /*HAS_LITTLE_FS*/

#ifndef HAS_LITTLE_FS_DIAG
#error "+HAS_LITTLE_FS_DIAG"
#endif /*HAS_DIAG_LITTLE_FS*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool little_fs_diag(uint8_t num);
bool little_fs_cat(uint8_t num, const char* const path);
bool little_fs_list(uint8_t num, const char* const path);
const char* LittleFsTypeToStr(const uint8_t type) ;
const char* LittleFsFileInfoToStr(const struct lfs_info* const  Info) ;
const char* LittleFsCfgToStr(const   struct lfs_config* const cfg );
const char* LittleFsInfoToStr(const struct lfs_fsinfo* const Node);
const char* LittleFsRetToStr(const int err) ;
const char* LittleFsFlagToStr(const int32_t flags) ;
const char* LittleFsConfigToStr(const LittleFsConfig_t* const Config);
const char* LittleFsNodeToStr(const LittleFsHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* LITTLE_FS_DIAG_H  */
