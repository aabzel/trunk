#ifndef FAT_FS_CONST_H
#define FAT_FS_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_FAT_FS
#error "+HAS_FAT_FS"
#endif

typedef enum{
	MOUNT_DELAYED=0,
	MOUNT_IMMEDIATELY=1,
}MountOpt_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*FAT_FS_CONST_H*/
