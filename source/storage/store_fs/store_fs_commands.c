#include "store_fs_commands.h"

#include "convert.h"
#include "log.h"
#include "storage.h"
#include "store_fs.h"

bool store_fs_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    char keyWord1[11] = "";
    char keyWord2[11] = "";

    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        res = false;
    }

    if(res) {
        res = store_fs_diag(1, keyWord1, keyWord2);
    } else {
        LOG_ERROR(STORE_FS, "Usage: sd  keyWord1 keyWord2");
    }
    return res;
}

bool store_fs_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t id = 0;
    uint8_t wrData[100] = {0};
    memset(wrData, 0x00, sizeof(wrData));
    if(2 == argc) {
        res = try_str2uint16(argv[0], &id);
        res = log_res(STORE_FS, res, "Id");

        StorageType_t par_type = storage_get_type((StorageId_t)id);
        if(TYPE_UNDEF != par_type) {
            res = try_str2type(argv[1], par_type, wrData, sizeof(wrData));
            res = log_res(STORE_FS, res, "GetType");
        } else {
            LOG_ERROR(STORE_FS, "Undef id %u", id);
            res = false;
        }
    }

    if(res) {
        res = store_fs_set(1, id, wrData);
        res = log_info_res(STORE_FS, res, "Set");
    } else {
        LOG_ERROR(STORE_FS, "Usage: sfs id data");
    }
    return res;
}

bool store_fs_delete_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t id = 0;
    if(1 == argc) {
        res = try_str2uint16(argv[0], &id);
        if(false == res) {
            LOG_ERROR(STORE_FS, "Unable to extract id %s", argv[0]);
        }
    }

    if(res) {
        res = store_fs_invalidate(1, id);
        res = log_res(STORE_FS, res, "Invalidate");
    } else {
        LOG_ERROR(STORE_FS, "Usage: se Id");
    }
    return res;
}

bool store_fs_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = store_fs_mcal_init();
        log_res(STORE_FS, res, "Init");
    }
    return res;
}

bool store_fs_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t id = 0;
    res = try_str2uint16(argv[0], &id);
    log_res(STORE_FS, res, "Id");

    if(res) {
        uint8_t data[128] = {0};
        res = store_fs_get(1, (StorageId_t)id, data);
        log_res(STORE_FS, res, "Get");
        if(res) {
            LOG_INFO(STORE_FS, "%s", StoreFsDataToStr(id, data));
        }
    } else {
        LOG_ERROR(STORE_FS, "Usage: sg Id");
    }
    return res;
}
