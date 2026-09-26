#include "little_fs_commands.h"

#include "array_diag.h"
#include "convert.h"
#include "little_fs.h"
#include "log.h"

bool little_fs_cat_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    char path[300] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LITTLE_FS, res, "Num");
    }

    if(2 <= argc) {
        res = strncpy(path, argv[1], sizeof(path));
    }

    if(res) {
        res = little_fs_cat(num, path);
        log_info_res(LITTLE_FS, res, "Cat");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfc Num FileName");
    }

    return res;
}



bool little_fs_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    char path[300] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LITTLE_FS, res, "Num");
    }

    if(2 <= argc) {
        res = strncpy(path, argv[1], sizeof(path));
    }

    if(res) {
        uint8_t data[200] = {0};
        uint32_t len = 0;
        res = little_fs_read(num, path, data, sizeof(data), &len);
        log_info_res(LITTLE_FS, res, "Read");
        if(res) {
            print_hex(data, len);
        }
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfrl Num FileName");
    }

    return res;
}

bool little_fs_read_ll_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LITTLE_FS, res, "Num");
    }

    if(res) {
        uint8_t data[200] = {0};
        uint32_t len = 0;
        res = little_fs_read_ll(num, data, sizeof(data), &len);
        log_info_res(LITTLE_FS, res, "Read");
        if(res) {
            print_hex(data, len);
        }
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfrl Num");
    }

    return res;
}

bool little_fs_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t size = 0;
    uint8_t data[100] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LITTLE_FS, res, "Num");
    }

    char path[300] = {0};
    if(2 <= argc) {
        res = strncpy(path, argv[1], sizeof(path));
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], data, sizeof(data), &size);
        log_info_res(LITTLE_FS, res, "Data");
        if(!res) {
            strcpy((char*)data, argv[2]);
            size = strlen(argv[2]);
            res = true;
        }
    }

    if(res) {
        res = little_fs_write(num, path, data, size);
        log_info_res(LITTLE_FS, res, "Write");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfw Num Path Data");
    }
    return res;
}

bool little_fs_write_ll_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t size = 0;
    uint8_t data[100] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LITTLE_FS, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        log_info_res(LITTLE_FS, res, "Data");
        if(!res) {
            strcpy((char*)data, argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = little_fs_write_ll(num, data, size);
        log_info_res(LITTLE_FS, res, "Write");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfw Num Data");
    }
    return res;
}

bool little_fs_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = little_fs_diag(1);
        log_info_res(LITTLE_FS, res, "Diag");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage: fdat");
    }

    return res;
}

bool little_fs_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = little_fs_mcal_init();
        log_info_res(LITTLE_FS, res, "Init");
    }
    return res;
}

bool little_fs_open_command(int32_t argc, char* argv[]) {
    bool res = false;
    int32_t mode = LFS_O_RDWR | LFS_O_CREAT;

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    char path[300] = {0};
    if(2 <= argc) {
        res = strncpy(path, argv[1], sizeof(path));
    }

    if(3 <= argc) {
        res = try_str2int32(argv[2], &mode);
    }

    if(res) {
        res = little_fs_open(num, path, mode);
        log_info_res(LITTLE_FS, res, "Open");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfo path mode");
    }
    return res;
}

bool little_fs_remove_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    char path[300] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = strncpy(path, argv[1], sizeof(path));
    }

    if(res) {
        res = little_fs_remove(num, path);
        log_info_res(LITTLE_FS, res, "ReMove");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfrm path");
    }
    return res;
}

bool little_fs_format_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = little_fs_format(num);
        log_info_res(LITTLE_FS, res, "Format");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfrm N");
    }

    return res;
}

bool little_fs_write_end_command(int32_t argc, char* argv[]){
    bool res = false;
    char path[20] = "log.txt";
    char logTest[200] = {0};

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        strcpy(path, argv[1]);
        res = true;
    }

    if(3 <= argc) {
        strcpy(logTest, argv[2]);
        res = true;
    }

    if(res) {
        res = little_fs_write_line(num, path, logTest);
        log_info_res(LITTLE_FS, res, "LogEnd");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfwe Num path Test");
    }
    return res;
}

bool little_fs_file_info_command(int32_t argc, char* argv[]) {
    bool res = false;
    char path[20] = "\\"; //
    if(1 <= argc) {
        strcpy(path, argv[0]);
        res = true;
    }

    LittleFsHandle_t* Node = LittleFsGetNode(1);
    if(Node) {
        struct lfs_info info = {0};
        int ret = lfs_stat(&Node->lfs, path, &info);
        res = LittleFsRetToRes(ret);
    }
    return res;
}

/*
little_fs_ls ..
little_fs_ls .
 * */
bool little_fs_list_command(int32_t argc, char* argv[]) {
    bool res = false;
    char path[40] = "\\"; //    .      backslash

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        strcpy(path, argv[0]);
        res = true;
    }

    if(res) {
        res = little_fs_list(1, path);
        log_info_res(LITTLE_FS, res, "List");
    }
    return res;
}
