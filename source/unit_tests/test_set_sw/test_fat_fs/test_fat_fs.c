#include "test_fat_fs.h"

#include <string.h>

#include "fat_fs.h"
#include "ff.h"
#include "log.h"
#include "unit_test_check.h"
#include "time_mcal.h"
#include "array.h"

#ifdef HAS_FAT_FS_DIAG
#include "fat_fs_diag.h"
#endif

static uint8_t rdData[WRITE_PART_SIZE+1]={0};
static uint8_t wrData[WRITE_PART_SIZE+1]={0};

bool test_fat_fs_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(4, sizeof(FatFsTime_t));

    return res;
}

bool test_fat_fs_write_line(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
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

    return res;
}

bool test_fat_fs_write_new(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    char array[500] = {0};
    strncpy((char*)array, "TestWrite", sizeof(array));

    char file_name[] = "test_open.txt";

    res = fat_fs_open(TEST_FAT_FS_NUM, file_name, FA_CREATE_ALWAYS | FA_WRITE);
    ASSERT_TRUE(res);

    res = fat_fs_write_bin(TEST_FAT_FS_NUM, (uint8_t*)array, strlen(array));
    ASSERT_TRUE(res);

    res = fat_fs_close(1);
    ASSERT_TRUE(res);

    return res;
}

bool test_fat_fs_open(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    char file_name[] = "test.txt";
    LOG_INFO(TEST, "OpenFile %s", file_name);
     res = fat_fs_open(TEST_FAT_FS_NUM, file_name, FA_OPEN_ALWAYS | FA_READ);
    ASSERT_TRUE(res);

    res = fat_fs_close(1);
    ASSERT_TRUE(res);

    return res;
}

#define TEST_FILE_NAME "sin2kHz5s.wav"
#define READ_PART_SIZE 2048
bool test_fat_fs_read(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
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
    return res;
}

/*
  tr fat_fs_write
*/
bool test_fat_fs_write(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    static uint32_t sn=0;
    FRESULT ret;
    sn++;

    memset(wrData, 0xAA, sizeof(wrData));
    FIL File = {0};
    uint32_t i = 0;
    uint32_t total_size = 0;
    uint32_t start_ms = time_get_ms32();
    char file_name[80]="";
    snprintf(file_name,sizeof(file_name),"TWP%u.bin", sn);
    LOG_INFO(TEST,"sizeof:%s ",file_name );
    BYTE mode = FA_WRITE | FA_CREATE_NEW |FA_OPEN_ALWAYS;
    FRESULT reto = f_open((FIL*)&File, (const TCHAR*) file_name, mode);
    LOG_INFO(TEST,"file_name:[%s],ret:%s ",file_name , FatFsResToStr(reto ));
    if(FR_EXIST==reto ) {
        ret = f_unlink(file_name);
        LOG_INFO(TEST,"DeleteFile:[%s],ret:%s ",file_name , FatFsResToStr(ret ));
        reto = f_open((FIL*)&File, (const TCHAR*) file_name, mode);
    }

    while(total_size < WAV_WRITE_SIZE) {
        UINT written = 0;
        ret = f_write(&File, wrData, WRITE_PART_SIZE, &written);
        EXPECT_EQ(FR_OK, ret);
        EXPECT_EQ(WRITE_PART_SIZE, written);
        if( FR_OK != ret ) {
            LOG_ERROR(TEST,"%u,WrError:%s",i, FatFsResToStr(ret ));
            break;
        }
        if(WRITE_PART_SIZE!=written) {
            break;
        }
        total_size += written;
        i++;
    }

    ret = f_close(&File);
    LOG_INFO(TEST,"CloseCode:%s " , FatFsResToStr(ret ));
    ASSERT_EQ(FR_OK, ret);
    uint32_t stop_ms = time_get_ms32();
    uint32_t diff_ms = stop_ms - start_ms;
    uint32_t data_rate= (1000*total_size) / (diff_ms);
    LOG_INFO(TEST,"totalSize:%u Byte,Duration:%u ms,WriteSpeed:%u Byte/s=%f kByte/s",
             total_size,
             diff_ms,
             data_rate,
             BYTES_2_KBYTES(data_rate));

    float ratio =((float) data_rate / (float) WAV_WRITE_SPEED);
    LOG_INFO(TEST,"ratio:%f ",ratio );
    ASSERT_GR(WAV_WRITE_SPEED, data_rate);

    EXPECT_EQ(WAV_WRITE_SIZE, total_size);
    return res;
}



bool test_fat_fs_verify_pattern(   char *file_name,
                                   uint8_t pattern,
                                   const uint32_t part_size,
                                   uint32_t total_size_to_read) {
    LOG_INFO(TEST, "%s():File:%s Patt:0x%x", __FUNCTION__,file_name,pattern);
    bool res = true;

    uint32_t i = 0;
    uint32_t total_size = 0;
    BYTE mode = FA_READ | FA_OPEN_EXISTING ;
    FIL File = {0};
    FRESULT ret = f_open(&File, (const TCHAR*) file_name, mode);
    LOG_INFO(TEST,"file_name:[%s],ret:%s ",file_name , FatFsResToStr(ret ));
    ASSERT_EQ(FR_OK, ret);

    while(1) {
        UINT read_effective = 0 ;
        memset(rdData, 0x01, sizeof(rdData));
        ret = f_read( &File, (void*) rdData, part_size, &read_effective );
        ASSERT_EQ(FR_OK, ret);
        if (0==read_effective) {
            break;
        }
        ASSERT_EQ(part_size, read_effective);
        uint32_t diff_ind = 0;
        res= is_arr_pat2(rdData, read_effective,   pattern, &diff_ind);
        if(!res){
            uint32_t rest_size =  read_effective - diff_ind;
            uint32_t offset = total_size + diff_ind;
            LOG_ERROR(TEST,"Offset:%u,ReadArray:%s ",offset,  ArrayToStr(&rdData[diff_ind] ,rest_size));
        }
        ASSERT_TRUE(res);
        total_size += read_effective;
        i++;
    }

    ret = f_close(&File);
    LOG_INFO(TEST, "CloseCode:%s " , FatFsResToStr(ret ));
    ASSERT_EQ(FR_OK, ret);
    ASSERT_EQ(total_size_to_read, total_size);

    return res;
}

bool test_fat_fs_write_pattern(   char *file_name, uint8_t pattern,
                                  const uint32_t part_size,
                                  uint32_t total_size_to_wr) {
    LOG_WARNING(TEST, "%s():file_name:%s,", __FUNCTION__,file_name );
    bool res = true;
    FRESULT ret;
    uint32_t i = 0;
    uint32_t total_size = 0;
    BYTE mode = FA_WRITE | FA_CREATE_ALWAYS;
    FIL File = {0};
    FRESULT reto = f_open((FIL*)&File, (const TCHAR*) file_name, mode);
    LOG_INFO(TEST,"file_name:[%s],ret:%s ",file_name , FatFsResToStr(reto ));
    if(FR_EXIST==reto ) {
        ret = f_unlink(file_name);
        LOG_INFO(TEST,"DeleteFile:[%s],ret:%s ",file_name , FatFsResToStr(ret ));
        reto = f_open((FIL*)&File, (const TCHAR*) file_name, mode);
        ASSERT_EQ(FR_OK, reto);
    }
    while(total_size < total_size_to_wr) {
        UINT written = 0;
        memset(wrData, pattern, part_size);
        ret = f_write(&File, wrData, part_size, &written);
        EXPECT_EQ(FR_OK, ret);
        EXPECT_EQ(part_size, written);
        if( FR_OK != ret ) {
            LOG_ERROR(TEST,"%u,WrError:%s",i, FatFsResToStr(ret ));
            break;
        }
        if(part_size!=written) {
            break;
        }
        total_size += written;
        i++;
#if 0
        ret = f_sync(&File);
        EXPECT_EQ(FR_OK, ret);
#endif
    }

    ret = f_close(&File);
    LOG_INFO(TEST,"CloseCode:%s " , FatFsResToStr(ret ));
    ASSERT_EQ(FR_OK, ret);

    LOG_INFO(TEST,"totalSize:%u Byte", total_size );
    EXPECT_EQ(total_size_to_wr, total_size);

    return res;

}

bool test_fat_fs_write_pattern_one(const char * const file_name ,
                                   const uint8_t patt,
                                   const uint32_t part_size,
                                   const uint32_t size) {
    LOG_WARNING(TEST, "%s():%s,0x%x,PartSize:%u,Size:%u", __FUNCTION__,file_name,patt,part_size,size);
    bool res = true ;
    ASSERT_TRUE( test_fat_fs_write_pattern(file_name, patt,part_size, size));
    ASSERT_TRUE(test_fat_fs_verify_pattern(file_name, patt,part_size, size));
    return res;
}


bool test_fat_fs_write_verify(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE( test_fat_fs_write_pattern_one("FilFF.bin", 0xFF,512, BIN_WRITE_VERIF_SIZE ) );
    ASSERT_TRUE( test_fat_fs_write_pattern_one("FilAA.bin", 0xAA,512, BIN_WRITE_VERIF_SIZE ) );
    ASSERT_TRUE( test_fat_fs_write_pattern_one("Fil55.bin", 0x55,512, BIN_WRITE_VERIF_SIZE ) );
    ASSERT_TRUE( test_fat_fs_write_pattern_one("Fil00.bin", 0x00,512, BIN_WRITE_VERIF_SIZE ) );
    return res;
}

bool test_fat_fs_write_1k_verify(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE( test_fat_fs_write_pattern_one("FilA_1k.bin", 0xAA, 1024, BIN_WRITE_VERIF_SIZE ) );
    ASSERT_TRUE( test_fat_fs_write_pattern_one("Fil5_1k.bin", 0x55, 1024, BIN_WRITE_VERIF_SIZE ) );
    return res;
}



