#ifndef DISK_DIAG_H
#define DISK_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "disk_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /**/

#ifndef HAS_DISK
#error "+HAS_DISK"
#endif /**/

#ifndef HAS_DISK_DIAG
#error "+HAS_DISK_DIAG"
#endif /**/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /**/

bool disk_diag(void);
const char* DiskCmdToStr(uint8_t cmd);
const char* DiskIoCtlCmdToStr(uint8_t const ioctl_code);
const char* DiskConfigToStr(const DiskConfig_t* const Config);
const char* DiskNodeToStr(const DiskHandle_t* const Node);
const char* DiskIoCtlCmdToStr(uint8_t const ioctl_code);

#ifdef __cplusplus
}
#endif

#endif /* DISK_DIAG_H  */
