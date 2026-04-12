#include "store_fs.h"

#include <stdio.h>

#include "code_generator.h"
#include "compiler_const.h"
#include "convert.h"
#include "log.h"
#include "storage.h"

#ifdef HAS_LITTLE_FS
#include "little_fs.h"
#endif

#ifdef HAS_FAT_FS
#include "fat_fs.h"
#endif

#ifdef HAS_FLASH_FS
#include "flash_fs.h"
#endif

COMPONENT_GET_NODE(StoreFs, store_fs)
COMPONENT_GET_CONFIG(StoreFs, store_fs)

#ifdef HAS_STORE_FS_CUSTOM
static const StoreFsInfo_t StoreFsInfo[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
};

COMPONENT_GET_INFO(StoreFs)
#endif

/*ISO-26262 require verify configuration*/

bool StoreFsIsValidConfig(const StoreFsConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(res) {
            if(Config->name) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(STORE_FS, "%u,NameErr", Config->num);
            }
        }
    }
    return res;
}

bool store_fs_invalidate(const uint8_t num, const StorageId_t id) {
    bool res = false;
    LOG_DEBUG(STORE_FS, "%u,Delete:%s", num, StorageIdToStr(id));
    StoreFsHandle_t* Node = StoreFsGetNode(num);
    if(Node) {
        char file_name[20] = "";
        snprintf(file_name, sizeof(file_name), "ID_%u.nv", id);
        switch(Node->storage_type) {
        case STORAGE_TYPE_LITTLE_FS: {
#ifdef HAS_LITTLE_FS
            res = little_fs_delete(Node->fs_num, file_name);
#endif
        } break;
        case STORAGE_TYPE_FLASH_FS: {
        } break;
        default:
            break;
        }
    }
    return res;
}

bool store_fs_set(uint8_t num, StorageId_t id, const void* const data) {
    bool res = false;
    LOG_WARNING(STORE_FS, "%u,Set:%s", num, StorageIdToStr(id));
    StoreFsHandle_t* Node = StoreFsGetNode(num);
    if(Node) {
        uint32_t size = storage_get_len(id);
        if(size) {
            char file_name[20] = "";
            snprintf(file_name, sizeof(file_name), "ID_%u.nv", id);

            switch(Node->storage_type) {
            case STORAGE_TYPE_LITTLE_FS: {
#ifdef HAS_LITTLE_FS
                res = little_fs_write(Node->fs_num, file_name, (uint8_t*)data, size);
#endif
            } break;

            case STORAGE_TYPE_FLASH_FS: {
#ifdef HAS_FLASH_FS
                res = flash_fs_set((uint16_t) id, (void*)data,(uint16_t) size);
#endif
            } break;



            case STORAGE_TYPE_FAT_FS: {
#ifdef HAS_FAT_FS
                res = fat_fs_write_file(Node->fs_num, file_name, (uint8_t*)data, size);
#endif
            } break;
            default:
                LOG_ERROR(STORE_FS, "%u,UndefFileSystem:%u", num, Node->storage_type);
                res = false;
                break;
            }
        }
    }
    return res;
}

bool store_fs_get(uint8_t num, StorageId_t id, void* const out_data) {
    bool res = false;
    LOG_DEBUG(STORE_FS, "%u,Get:%u=%s", num, id, StorageIdToStr(id));
    StoreFsHandle_t* Node = StoreFsGetNode(num);
    if(Node) {
        if(out_data) {
            char file_name[50] = "";
            uint32_t size = storage_get_len(id);
            snprintf(file_name, sizeof(file_name), "ID_%u.nv", id);
            uint32_t len = 0;

            switch(Node->storage_type) {
            case STORAGE_TYPE_LITTLE_FS: {
#ifdef HAS_LITTLE_FS
                res = little_fs_read(Node->fs_num, file_name, out_data, size, &len);
#endif
            } break;

            case STORAGE_TYPE_FLASH_FS: {
#ifdef HAS_FLASH_FS
                uint16_t value_len = 0;
                res = flash_fs_get((uint16_t) id, (void*)  out_data, (uint16_t) size, &value_len);
#endif
            } break;

            case STORAGE_TYPE_FAT_FS: {
#ifdef HAS_FAT_FS
                res = fat_fs_read_file(Node->fs_num, file_name, out_data, size, &len);
#endif
            } break;
            default: {
                LOG_ERROR(STORE_FS, "%u,UndefFileSystem:%u", num, Node->storage_type);
                res = false;
            } break;
            }

            if(len != size) {
                LOG_DEBUG(STORE_FS, "ID%u,Len:%u,Size:%u", id, len, size);
            }
        }
    }
    return res;
}

bool store_fs_set_lazy(uint8_t num, StorageId_t id, const void* const data_write) {
    bool res = false;
    uint32_t len = storage_get_len(id);
    uint8_t read_data[128] = {0};
    if(len < sizeof(read_data)) {
        res = store_fs_get(num, id, read_data);
        if(res) {
            int ret = memcmp(data_write, read_data, len);
            if(0 == ret) {
                LOG_INFO(STORE_FS, "ID%u,AlreadyTheSame", id);
                res = true;
            } else {
                res = false;
            }
        } else {
            LOG_ERROR(STORE_FS, "GetError");
            res = false;
        }

        if(false == res) {
            res = store_fs_set(num, id, data_write);
        }
    } else {
        LOG_ERROR(STORE_FS, "TooBigParam");
    }

    return res;
}

bool store_fs_set_verify(uint8_t num, StorageId_t id, const void* const data_write) {
    bool res = false;
    res = store_fs_set(num, id, data_write);
    if(res) {
        uint8_t read_data[128] = {0};
        res = store_fs_get(num, id, read_data);
        if(res) {
            uint32_t len = storage_get_len(id);
            int ret = memcmp(data_write, read_data, len);
            if(0 == ret) {
                res = true;
            } else {
                LOG_ERROR(STORE_FS, "VerivyError");
                res = false;
            }
        } else {
            LOG_ERROR(STORE_FS, "GetError");
            res = false;
        }
    } else {
        LOG_ERROR(STORE_FS, "SetError");
        res = false;
    }
    return res;
}

bool store_fs_load(uint8_t num, StorageId_t id, void* const out_data) {
    bool res = false;
    StorageItem_t* Node = StorageGetNode(id);
    bool present = store_fs_get(num, id, out_data);
    if(!present) {
        LOG_WARNING(STORE_FS, "NoId:%s", StorageIdToStr(id));
        if(Node) {
            res = true;
        } else {
            LOG_ERROR(STORE_FS, "UnKnownID%u", id);
        }
    }

    if(res) {
        uint8_t defaultData[128] = {0};
        if(Node->default_value) {
            res = try_str2type(Node->default_value, Node->type, defaultData, sizeof(defaultData));
            if(res) {
                LOG_INFO(STORE_FS, "SetDefailt:%s", StorageItemToStr(Node));
                res = store_fs_set(num, id, defaultData);
                if(res) {
                    memcpy(out_data, defaultData, Node->len);
                } else {
                    LOG_ERROR(STORE_FS, "SetErr:%s", StorageItemToStr(Node));
                }
            } else {
                LOG_ERROR(STORE_FS, "ParseErrID%u,Def:[%s]", id, Node->default_value);
            }
        } else {
            LOG_ERROR(STORE_FS, "NoDefVal");
        }
    }
    return res;
}

bool store_fs_init_custom(void) {
    bool res = false;
    LOG_INFO(STORE_FS, "Version:%s", STORE_FS_VERSION);
    log_level_get_set(STORE_FS, LOG_LEVEL_DEBUG);
    return res;
}

bool store_fs_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(STORE_FS, "Proc %u", i);
    StoreFsHandle_t* Node = StoreFsGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool store_fs_init_common(const StoreFsConfig_t* const Config, StoreFsHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

static bool store_fs_is_id_uniq(const StorageId_t id) {
    bool res = false;
    uint32_t match_cnt = 0, i = 0;
    uint32_t cnt = storage_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(id == StorageArray[i].id) {
            match_cnt++;
        }
    }

    if(1 == match_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

static bool store_fs_load_defaults(uint8_t num) {
    bool res = true;
    bool out_res = true;
    uint32_t ok = 0;
    uint32_t cnt = storage_get_cnt();
    LOG_WARNING(STORE_FS, "Init,Cnt:%u", cnt);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        res = store_fs_is_id_uniq(StorageArray[i].id);
        if(res) {
            res = StorageIsValidParam(&StorageArray[i]);
            if(res) {
                uint8_t out_data[512] = {0};
                res = store_fs_load(num, StorageArray[i].id, out_data);
                if(res) {
                    ok++;
                }
            } else {
                LOG_ERROR(STORE_FS, "InValidParam,[%s]", StorageItemToStr(&StorageArray[i]));
                out_res = false;
            }
        } else {
            LOG_ERROR(STORE_FS, "Param:%u,isNotUniq", StorageArray[i].id);
            out_res = false;
        }
    }

    if(ok) {
        LOG_INFO(STORE_FS, "OkCnt:%u/%u", ok, cnt);
        res = true;
    } else {
        res = false;
    }
    return out_res;
}

bool store_fs_init_one(uint8_t num) {
    bool res = false;
    log_level_get_set(STORE_FS, LOG_LEVEL_DEBUG);
    LOG_WARNING(STORE_FS, "STORE_FS%u", num);
    const StoreFsConfig_t* Config = StoreFsGetConfig(num);
    if(Config) {
        res = StoreFsIsValidConfig(Config);
        if(res) {
#ifdef HAS_STORE_FS_DIAG
            LOG_WARNING(STORE_FS, "%s", StoreFsConfigToStr(Config));
#endif
            StoreFsHandle_t* Node = StoreFsGetNode(num);
            if(Node) {
                Node->fs_num = Config->fs_num;
                Node->storage_type = Config->storage_type;
                Node->valid = true;
                Node->init = true;
                res = store_fs_load_defaults(num);
                LOG_INFO(STORE_FS, "InitOk,%u", num);
            } else {
                LOG_ERROR(STORE_FS, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(STORE_FS, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(STORE_FS, "ConfigErr %u", num);
    }
    log_level_get_set(STORE_FS, LOG_LEVEL_INFO);
    return res;
}

COMPONENT_INIT_PATTERT(STORE_FS, STORE_FS, store_fs)
COMPONENT_PROC_PATTERT(STORE_FS, STORE_FS, store_fs)
