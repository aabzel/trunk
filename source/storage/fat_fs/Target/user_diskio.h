
/*
 * @brief   This file contains the common defines and functions prototypes for
 *          the user_diskio driver.
 */

#ifndef __USER_DISKIO_H
#define __USER_DISKIO_H

#ifdef __cplusplus
extern "C" {
#endif

extern Diskio_drvTypeDef USER_Driver;
DSTATUS USER_initialize(BYTE pdrv);

#ifdef __cplusplus
}
#endif

#endif /* __USER_DISKIO_H */
