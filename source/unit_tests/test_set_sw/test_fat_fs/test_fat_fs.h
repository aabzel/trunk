#ifndef TEST_FAT_FS_UTILS_H
#define TEST_FAT_FS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define TEST_FAT_FS_NUM 1

#define WAV_WRITE_SPEED  (96000*2*2)
#define WRITE_PART_SIZE 4096UL
#define BIN_WRITE_VERIF_SIZE (1024*512)
#define WAV_WRITE_SIZE (WRITE_PART_SIZE*500UL)

bool test_fat_fs_write_pattern(   char *file_name, uint8_t pattern,   const uint32_t part_size, uint32_t size);
bool test_fat_fs_verify_pattern(   char* file_name, uint8_t pattern,   const uint32_t part_size, uint32_t size) ;
bool test_fat_fs_write_pattern_one(const char *const  file_name , const uint8_t patt,  const uint32_t part_size, const uint32_t size);

bool test_fat_fs_write_1k_verify(void);
bool test_fat_fs_write(void);
bool test_fat_fs_open(void);
bool test_fat_fs_types(void);
bool test_fat_fs_write_verify(void);
bool test_fat_fs_write_line(void);
bool test_fat_fs_write_new(void);
bool test_fat_fs_read(void);

#define TEST_SUIT_FAT_FS                           \
	{"fat_fs_write_1k_verify", test_fat_fs_write_1k_verify},           \
	{"fat_fs_write_verify", test_fat_fs_write_verify},           \
	{"fat_fs_write", test_fat_fs_write},           \
	{"fat_fs_read", test_fat_fs_read},             \
	{"fat_fs_types", test_fat_fs_types},           \
	{"fat_fs_open", test_fat_fs_open},             \
	{"fat_fs_write_new", test_fat_fs_write_new},   \
	{"fat_fs_write_line", test_fat_fs_write_line},

#ifdef __cplusplus
}
#endif

#endif /* TEST_FAT_FS_UTILS_H */
