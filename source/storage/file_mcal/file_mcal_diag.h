#ifndef FILE_MCAL_DIAG_H
#define FILE_MCAL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "file_mcal_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_FILE_MCAL
#error "+HAS_FILE_MCAL"
#endif

#ifndef HAS_FILE_MCAL_DIAG
#error "+HAS_FILE_MCAL_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

const char* FileMcalStateToStr(const FileState_t state);
const char* FileMcalNodeToStr(const FileMcalHandle_t* const Node);
const char* FileSystemTypeToStr(const FileSystemType_t* const Node);
const char* FileMcalConfigToStr(const FileMcalConfig_t* const Config);
const char* FileSystemToStr(FileSystem_t file_system) ;
bool file_mcal_diag(void);
bool file_mcal_diag_one(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* FILE_MCAL_DIAG_H  */
