#ifndef DISK_MCAL_H
#define DISK_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "disk_config.h"
#include "disk_types.h"
#ifdef HAS_FAT_FS
#include "integer.h"
#endif
#ifdef HAS_DISK_DIAG
#include "disk_diag.h"
#endif


/* API */
const DiskConfig_t* DiskGetConfig(uint8_t num);
DiskHandle_t* DiskGetNode(uint8_t num);
bool DiskIsValidConfig(const DiskConfig_t* const Config);

#ifdef HAS_DISK_CUSTOM
const DiskInfo_t* DiskGetInfo(uint8_t num);
#endif

DSTATUS disk_initialize(BYTE pdrv);
bool disk_mcal_init(void);
bool disk_init_custom(void);
bool disk_init_one(uint8_t num);
bool disk_init_common(const DiskConfig_t* const Config,
                      DiskHandle_t* const Node);

bool disk_proc_one(uint8_t num);
bool disk_proc(void);

DRESULT disk_res_to_ret(const bool res);
DRESULT disk_ret_to_res(const DRESULT ret);

/*setters*/
DRESULT disk_write(BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void* buff);

/*getters*/
bool disk_raw_reg_diag(uint8_t i) ;
DSTATUS disk_status(BYTE pdrv);
DRESULT disk_read(BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
DWORD get_fattime(void);


#ifdef __cplusplus
}
#endif

#endif /* DISK_MCAL_H */
