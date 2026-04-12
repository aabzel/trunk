#ifndef LITTLE_FS_MCAL_H
#define LITTLE_FS_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "little_fs_config.h"
#include "little_fs_types.h"
#ifdef HAS_LITTLE_FS_DIAG
#include "little_fs_diag.h"
#endif

/* API */
LittleFsHandle_t* LittleFsGetNode(uint8_t num);
const LittleFsConfig_t* LittleFsGetConfig(uint8_t num);
bool LittleFsIsValidConfig(const LittleFsConfig_t* const Config);

bool little_fs_mcal_init(void);
bool little_fs_init_custom(void);
bool little_fs_init_one(uint8_t num);
bool little_fs_init_common(const LittleFsConfig_t* const Config,
                              LittleFsHandle_t* const Node);

bool little_fs_proc_one(uint8_t num);
bool little_fs_proc(void);

/* setters */
bool little_fs_delete(uint8_t num, const char *path);
bool little_fs_write_line(uint8_t num, const char *path,  char * const data);
bool little_fs_write(uint8_t num, const char *path, const uint8_t * const data, uint32_t size);
bool little_fs_write_ll(uint8_t num, const uint8_t * const data, uint32_t size) ;
bool little_fs_open(const uint8_t num, const char *const path, const  int32_t flags);
bool little_fs_remove(const uint8_t num, const char* const path);
bool little_fs_close(const uint8_t num);

/*getters*/
bool LittleFsRetToRes(int err);
bool little_fs_read_ll(uint8_t num, uint8_t * const data, uint32_t size, uint32_t* const len);
bool little_fs_read(uint8_t num, const char *const path, uint8_t * const data, uint32_t size, uint32_t* const len);

#ifdef __cplusplus
}
#endif

#endif /* LITTLE_FS_MCAL_H */
