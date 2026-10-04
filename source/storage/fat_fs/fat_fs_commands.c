#include "fat_fs_commands.h"

#include <string.h>

#include "array_diag.h"
#include "convert.h"
#include "debug_info.h"
#include "fat_fs.h"
#include "ff.h"
#include "log.h"
#include "log_utils.h"

#ifdef HAS_FAT_FS_TEST
#include "test_fat_fs.h"
#endif


bool fat_fs_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = fat_fs_diag();
        log_res(FAT_FS, res, "Diag");
    } else {
        LOG_ERROR(FAT_FS, "Usage: fdat");
    }

    return res;
}

bool fat_fs_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = fat_fs_mcal_init();
    log_res(FAT_FS, res, "Init");
    return res;
}

bool fat_fs_mount_command(int32_t argc, char* argv[]) {
    bool res = false;
    char path[100] = "\\";
    uint8_t opt = 1;

    if(1 <= argc) {
        strcpy(path, argv[0]);
        res = true;
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], (uint8_t*)&opt);
    }

    if(res) {
        res = fat_fs_mount(1, opt, path);
    }
    return res;
}

bool fat_fs_read_dirr_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = fat_fs_read_dirr(1);
        log_res(FAT_FS, res, "ReadDir");
    }
    return res;
}
/*
 * ffw log.txt line2 ;  cat log.txt
 * ffw ac_Po.txt line2 ;  cat ac_Po.txt
 * */
bool fat_fs_file_write_command(int32_t argc, char* argv[]) {
    bool res = false;

    char line[150] = {0};
    memset(line, 0, sizeof(line));
    uint32_t len = 0;

    char filename[100] = "";
    if(1 <= argc) {
        strcpy(filename, argv[0]);
        res = true;
    }

    if(2 <= argc) {
        strcpy(line, argv[1]);
        len = strlen(argv[1]);
        res = true;
    }

    if(res) {
        LOG_INFO(FAT_FS, "text[%s],Len:%u",  line, len);
        res = fat_fs_write_line_black_box(1,filename, line);
        log_res(FAT_FS, res, "Write");
    } else {
        LOG_ERROR(FAT_FS, "Usage ffw fileName Line");
    }
    return res;
}

bool fat_fs_open_dirr_command(int32_t argc, char* argv[]) {
    bool res = false;
    char dirr_name[100] = {0};
    if(0 <= argc) {
        strcpy(dirr_name, "/");
    }
    if(1 <= argc) {
        strcpy(dirr_name, argv[0]);
        res = true;
    }

    if(res) {
        res = fat_fs_open_dirr(1, dirr_name);
        log_res(FAT_FS, res, "OpenDir");
    }
    return res;
}

bool fat_fs_unlink_command(int32_t argc, char* argv[]) {
    bool res = false;

    char path[100];
    if(1 <= argc) {
        strcpy(path, argv[0]);
        res = true;
    }

    if(res) {
        res = fat_fs_unlink(1, path);
        log_res(FAT_FS, res, "UnLink");
    } else {
        LOG_ERROR(FAT_FS, "Usage funl path");
    }
    return res;
}

bool fat_fs_open_command(int32_t argc, char* argv[]) {
    bool res = false;
    BYTE mode = FA_READ | FA_OPEN_EXISTING;
    char path[200] = {0};

    if(1 <= argc) {
        strcpy(path, argv[0]);
        res = true;
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &mode);
        log_res(FAT_FS, res, "Mode");
    }

    if(res) {
        res = fat_fs_open(1, path, mode);
        log_res(FAT_FS, res, "Open");
    } else {
        LOG_ERROR(FAT_FS, "Usage ftfso path mode");
    }

    return res;
}

bool fat_fs_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool FatFsRet2Res(FRESULT ret, const char* const prefix);
    uint32_t array_len = 0;
    uint8_t array[500];
    if(1 <= argc) {
        res = try_str2array(argv[0], array, sizeof(array), &array_len);
        if(false == res) {
            LOG_ERROR(FAT_FS, "ParseErr array %s", argv[0]);
            strcpy((char*)array, argv[0]);
            res = true;
        }
    }

    if(res) {
        res = fat_fs_write_bin(1, array, array_len);
        log_res(FAT_FS, res, "WriteBin");
    } else {
        LOG_ERROR(FAT_FS, "Usage ftfsw text");
    }
    return res;
}

bool fat_fs_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t RxData[500] = {0};
    uint32_t size = 1;

    if(0 <= argc) {
        res = false;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &size);
    }

    if(res) {
        res = fat_fs_read(1, RxData, size);
    }
    return res;
}

bool fat_fs_cat_command(int32_t argc, char* argv[]) {
    bool res = false;
    char path[100] = "/";
    if(1 <= argc) {
        strcpy(path, argv[0]);
        res = true;
    }

    if(res) {
        res = fat_fs_cat(1, path);
        log_res(FAT_FS, res, "Cat");
    }
    return res;
}

bool fat_fs_close_command(int32_t argc, char* argv[]) {
    bool res = true;
    if(res) {
        res = fat_fs_close(1);
    } else {
        LOG_ERROR(FAT_FS, "Usage ftfsc");
    }
    return res;
}

bool fat_fs_seek_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

/*
 fatff 0 4096
 fatff 1 4096

 FAT16 fatff 1 512
 FAT32 fatff 2 512

EXFAT fatff 4 512
ANY fatff 7 512
fatff 0 1024
*/
bool fat_fs_format_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t format_opt = FM_FAT;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &format_opt);
    }


    if(res) {
        res = fat_fs_format(1, format_opt);
    } else {
        LOG_ERROR(FAT_FS, "Usage fatff FormatOpt");
    }
    return res;
}

bool fat_fs_root_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = fat_fs_root(1);
    log_res(FAT_FS, res, "Root");
    return res;
}

bool fat_fs_scan_command(int32_t argc, char* argv[]) {
    bool res = false;
    char path[20] = "";
    if(0 <= argc) {
        strcpy(path, "");
        res = true;
    }

    if(1 <= argc) {
        strcpy(path, argv[0]);
        res = true;
    }

    if(res) {
        res = fat_fs_scan(path);
        log_res(FAT_FS, res, "Scan");
    } else {
        LOG_ERROR(FAT_FS, "Usage ffs path");
    }
    return res;
}


bool fat_fs_delete_command(int32_t argc, char* argv[]){
    bool res = false;
    char path[30] = "";

    if(0 <= argc) {
        res = true;
    }


    if(1 <= argc) {
        strcpy(path, argv[0]);
        res = true;
    }

    if(res) {
        res = false;

        switch(argc){

        case 0:{
            res = fat_fs_delete_all_files();
        } break;
        case 1:{
#if 0==_FS_MINIMIZE
        FRESULT ret=f_unlink ( (TCHAR*) path );
        res = FatFsRetToRes( ret, "DeleteFile");
        if(res){
            LOG_INFO(FAT_FS, "Del,File:[%s]Ok",path);
        }else {
            LOG_ERROR(FAT_FS, "Del,File:[%s]Err",path);
        }
#endif

        } break;


        default: {

        } break;
        }
    } else {
        LOG_ERROR(FAT_FS, "Usage ffdel path");
    }
    return res;

}


/*
  ffwv Tst.bin 0x55 512 262144 3000
*/
bool fat_fs_write_verify_command(int32_t argc, char* argv[]) {
    bool res = false;
    char file_name[30] = "";
    uint32_t total_size = 128 * 1024;
    uint32_t pause_ms = 3000;
    uint32_t part_size = 512;
    uint8_t pattern = 0x55;

    if(1 <= argc) {
        strcpy(file_name, argv[0]);
        res = true;
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &pattern);
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &part_size);
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &total_size);
    }

    if(5 <= argc) {
        res = try_str2uint32(argv[4], &pause_ms);
    }

    if(res) {
#ifdef HAS_FAT_FS_TEST
        res = test_fat_fs_write_pattern_one(file_name, pattern, part_size, total_size, pause_ms);
#endif
        log_res(FAT_FS, res, "WaritePath");
    } else {
        LOG_ERROR(FAT_FS, "Usage ffwv FileName Pattern PartSz TotSize Pause");
    }
    return res;
}
