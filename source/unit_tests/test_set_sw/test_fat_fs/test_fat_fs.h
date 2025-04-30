#ifndef TEST_FAT_FS_UTILS_H
#define TEST_FAT_FS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool test_fat_fs_open(void);
bool test_fat_fs_write_line(void);
bool test_fat_fs_write_new(void);

#define TEST_SUIT_FAT_FS \
	{"fat_fs_open", test_fat_fs_open},\
	{"fat_fs_write_new", test_fat_fs_write_new},\
	{"fat_fs_write_line", test_fat_fs_write_line},

#ifdef __cplusplus
}
#endif

#endif /* TEST_FAT_FS_UTILS_H */
