#include "test_fat_fs.h"

#include <string.h>

#include "fat_fs_config.h"
#include "ff.h"
#include "log.h"
#include "unit_test_check.h"
#ifdef HAS_FAT_FS_DIAG
#include "fat_fs_diag.h"
#endif
#include "fat_fs_drv.h"

bool test_fat_fs_write_line(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(FAT_FS, LOG_LEVEL_DEBUG);
#ifdef HAS_SD_CARD
    set_log_level(SD_CARD, LOG_LEVEL_DEBUG);
#endif
    bool res = false;
    char text[30] = "";
    strcpy(text, "Line1");

    res = fat_fs_write("test_log.txt", text);
    ASSERT_TRUE(res);

    strcpy(text, "Line2");
    res = fat_fs_write("test_log.txt", text);
    ASSERT_TRUE(res);

    strcpy(text, "[]");
    res = fat_fs_write("keylog.txt", text);
    ASSERT_TRUE(res);

    set_log_level(FAT_FS, LOG_LEVEL_INFO);
#ifdef HAS_SD_CARD
    set_log_level(SD_CARD, LOG_LEVEL_INFO);
#endif
    return true;
}

bool test_fat_fs_write_new(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t array[500];
    strncpy((char*)array, "TestWrite", sizeof(array));

#ifdef HAS_SD_CARD
    set_log_level(SD_CARD, LOG_LEVEL_DEBUG);
#endif
    set_log_level(FAT_FS, LOG_LEVEL_DEBUG);

    UINT array_len = 0;
    FRESULT ret;
    char file_name[] = "test_open.txt";
    ret = f_open((FIL*)&FatFsInstance.file, (const TCHAR*)file_name, FA_CREATE_ALWAYS | FA_WRITE);
#ifdef HAS_FAT_FS_DIAG
    LOG_WARNING(FAT_FS, "%u %s", ret, FatFsRes2Str(ret));
#endif
    ASSERT_EQ(FR_OK, ret);
    LOG_INFO(TEST, "Open %s Ok %p", file_name, &FatFsInstance.file);

    ret = f_write((FIL*)&FatFsInstance.file, (const void*)array, (UINT)strlen((char*)array), &array_len);
    ASSERT_EQ(FR_OK, ret);
    ASSERT_GR(0, array_len);
    LOG_INFO(TEST, "WriteOk");

    ret = f_close((FIL*)&FatFsInstance.file);
#ifdef HAS_FAT_FS_DIAG
    LOG_WARNING(FAT_FS, "ret:%u=%s", ret, FatFsRes2Str(ret));
#endif
    ASSERT_EQ(FR_OK, ret);
    LOG_INFO(TEST, "CloseOk");
#ifdef HAS_SD_CARD
    set_log_level(SD_CARD, LOG_LEVEL_INFO);
#endif
    set_log_level(FAT_FS, LOG_LEVEL_INFO);

    return true;
}

bool test_fat_fs_open(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    FRESULT ret;
    char file_name[] = "test.txt";
    LOG_INFO(TEST, "OpenFile %s", file_name);
    ret = f_open((FIL*)&FatFsInstance.file, (const TCHAR*)file_name, FA_OPEN_ALWAYS | FA_READ);
#ifdef HAS_FAT_FS_DIAG
    LOG_INFO(FAT_FS, "%u %s", ret, FatFsRes2Str(ret));
#endif
    ASSERT_EQ(FR_OK, ret);

    ret = f_close((FIL*)&FatFsInstance.file);
#ifdef HAS_FAT_FS_DIAG
    LOG_WARNING(FAT_FS, "%u %s", ret, FatFsRes2Str(ret));
#endif
    ASSERT_EQ(FR_OK, ret);
    return true;
}
