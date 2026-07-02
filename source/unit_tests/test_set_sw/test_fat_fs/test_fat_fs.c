#include "test_fat_fs.h"

#include <string.h>

#include "fat_fs.h"
#include "ff.h"
#include "log.h"
#include "unit_test_check.h"
#include "time_mcal.h"

#ifdef HAS_FAT_FS_DIAG
#include "fat_fs_diag.h"
#endif

bool test_fat_fs_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    ASSERT_EQ(4, sizeof(FatFsTime_t));

    return true;
}

bool test_fat_fs_write_line(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    bool res = false;
    char locText[30] = "";
    strcpy(locText, "Line1");

    res = fat_fs_write_line(TEST_FAT_FS_NUM, "test_log.txt", locText);
    ASSERT_TRUE(res);

    strcpy(locText, "Line2");
    res = fat_fs_write_line(TEST_FAT_FS_NUM, "test_log.txt", locText);
    ASSERT_TRUE(res);

    strcpy(locText, "[]");
    res = fat_fs_write_line(TEST_FAT_FS_NUM, "keylog.txt", locText);
    ASSERT_TRUE(res);

    return true;
}

bool test_fat_fs_write_new(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    char array[500] = {0};
    strncpy((char*)array, "TestWrite", sizeof(array));
    bool res = false;

    char file_name[] = "test_open.txt";

    res = fat_fs_open(TEST_FAT_FS_NUM, file_name, FA_CREATE_ALWAYS | FA_WRITE);
    ASSERT_TRUE(res);

    res = fat_fs_write_bin(TEST_FAT_FS_NUM, (uint8_t*)array, strlen(array));
    ASSERT_TRUE(res);

    res = fat_fs_close(1);
    ASSERT_TRUE(res);

    return true;
}

bool test_fat_fs_open(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    char file_name[] = "test.txt";
    LOG_INFO(TEST, "OpenFile %s", file_name);
    bool res = fat_fs_open(TEST_FAT_FS_NUM, file_name, FA_OPEN_ALWAYS | FA_READ);
    ASSERT_TRUE(res);

    res = fat_fs_close(1);
    ASSERT_TRUE(res);

    return true;
}

#define TEST_FILE_NAME "sin2kHz5s.wav"
#define READ_PART_SIZE 2048
bool test_fat_fs_read(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    FIL File={0};
    uint32_t total_size = 0;
    uint32_t start_ms = time_get_ms32();
    BYTE mode = FA_READ | FA_OPEN_EXISTING;
    FRESULT ret = f_open((FIL*)&File, (const TCHAR*) TEST_FILE_NAME, mode);
    ASSERT_EQ(FR_OK, ret);
    while(1) {
        UINT real_read = 0;
        uint8_t data[READ_PART_SIZE+1]={0};
        ret = f_read(&File, data, (UINT)READ_PART_SIZE, &real_read);
        ASSERT_EQ(FR_OK, ret);
        total_size +=real_read;
        if (0==real_read) {
            break;
        }
        //ASSERT_GR(0, real_read);
    }

    ret = f_close(&File);
    ASSERT_EQ(FR_OK, ret);
    uint32_t stop_ms = time_get_ms32();
    uint32_t diff_ms = stop_ms-start_ms;
    uint32_t data_rate= (1000*total_size)/(diff_ms);
    LOG_INFO(TEST,"totalSize:%u Byte,Duration:%u ms,ReadSpeed:%u Byte/s=%f kByte/s",total_size,diff_ms,data_rate,BYTES_2_KBYTES(data_rate));
    ASSERT_GR((96000*2*2), data_rate);
    return true;
}
