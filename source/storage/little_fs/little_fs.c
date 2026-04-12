#include "little_fs.h"

#include "array_diag.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "lfs.h"
#include "little_fs_config.h"
#include "log.h"

COMPONENT_GET_NODE(LittleFs, little_fs)
COMPONENT_GET_CONFIG(LittleFs, little_fs)

/*ISO-26262 require verify configuration*/

bool LittleFsIsValidConfig(const LittleFsConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;

        if(Config->name) {
        } else {
            res = false;
            LOG_ERROR(LITTLE_FS, "%u,NameErr", Config->num);
        }

        if(Config->base_address) {
        } else {
            LOG_WARNING(LITTLE_FS, "BaseAddrErr 0x%08x", Config->base_address);
        }

        if(Config->cfg.read) {
        } else {
            res = false;
            LOG_WARNING(LITTLE_FS, "readCallBack,Err");
        }

        if(Config->cfg.prog) {
        } else {
            res = false;
            LOG_WARNING(LITTLE_FS, "progCallBack,Err");
        }

        if(Config->cfg.erase) {
        } else {
            res = false;
            LOG_WARNING(LITTLE_FS, "eraseCallBack,Err");
        }

        if(Config->cfg.block_count) {
        } else {
            res = false;
            LOG_WARNING(LITTLE_FS, "BlockCntCallBack,Err");
        }
    }
    return res;
}

bool little_fs_init_custom(void) {
    bool res = false;
    LOG_INFO(LITTLE_FS, "Version:%s", LITTLE_FS_VERSION);

#ifndef LFS_NO_MALLOC
    LOG_WARNING(LITTLE_FS, "NoMallocDesirable");
#endif

    return res;
}

bool little_fs_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(LITTLE_FS, "Proc %u", i);
    LittleFsHandle_t* Node = LittleFsGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool little_fs_init_common(const LittleFsConfig_t* const Config, LittleFsHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool LittleFsRetToRes(int err) {
    bool res = false;
    switch(err) {
    case LFS_ERR_OK:
        res = true;
        break;
    case LFS_ERR_IO:
        res = false;
        break;
    case LFS_ERR_CORRUPT:
        res = false;
        break;
    case LFS_ERR_NOENT:
        res = false;
        break;
    case LFS_ERR_EXIST:
        res = false;
        break;
    case LFS_ERR_NOTDIR:
        res = false;
        break;
    case LFS_ERR_ISDIR:
        res = false;
        break;
    case LFS_ERR_NOTEMPTY:
        res = false;
        break;
    case LFS_ERR_BADF:
        res = false;
        break;
    case LFS_ERR_FBIG:
        res = false;
        break;
    case LFS_ERR_INVAL:
        res = false;
        break;
    case LFS_ERR_NOSPC:
        res = false;
        break;
    case LFS_ERR_NOMEM:
        res = false;
        break;
    case LFS_ERR_NOATTR:
        res = false;
        break;
    case LFS_ERR_NAMETOOLONG:
        res = false;
        break;
    default:
        res = false;
        LOG_ERROR(LITTLE_FS, "Err,%d", err);
        break;
    }

#ifdef HAS_LITTLE_FS_DIAG
    if(false == res) {
        LOG_ERROR(LITTLE_FS, "Ret:%d=%s", err, LittleFsRetToStr(err));
    } else {
        LOG_DEBUG(LITTLE_FS, "Ret:%d=%s", err, LittleFsRetToStr(err));
    }
#endif
    return res;
}

bool little_fs_read_ll(uint8_t num, uint8_t* const data, uint32_t size, uint32_t* const len) {
    bool res = false;
    LittleFsHandle_t* Node = LittleFsGetNode(num);
    if(Node) {
        lfs_ssize_t ssize = 0;
        ssize = lfs_file_read(&Node->lfs, &Node->file, data, size);
        if(ssize) {
            *len = ssize;
            res = true;
        }
    } else {
        LOG_ERROR(LITTLE_FS, "NodeError");
    }
    return res;
}

bool little_fs_read(uint8_t num, const char* const path, uint8_t* const data, uint32_t size, uint32_t* const len) {
    bool res;
    LOG_DEBUG(LITTLE_FS, "%u,ReadFile:[%s],ToSize:%u", num, path, size);
    int32_t flags = LFS_O_RDONLY;
    res = little_fs_open(num, path, flags);
    if(res) {
        res = little_fs_read_ll(num, data, size, len);
        res = little_fs_close(num) && res;
    }
    return res;
}

bool little_fs_open(const uint8_t num, const char* path, const int32_t flags) {
    bool res = false;
    if(path) {
#ifdef HAS_LITTLE_FS_DIAG
        LOG_DEBUG(LITTLE_FS, "%u,OpenFile:[%s],flag:0x%08x=%s", num, path, flags, LittleFsFlagToStr(flags));
#endif
        LittleFsHandle_t* Node = LittleFsGetNode(num);
        if(Node) {
            int ret = 0;
#ifdef LFS_NO_MALLOC
            ret = lfs_file_opencfg(&Node->lfs, &Node->file, path, flags, &Node->file_config);
#else
            ret = lfs_file_open(&Node->lfs, &Node->file, path, flags);
#endif
            res = LittleFsRetToRes(ret);
        }
    }
    return res;
}

bool little_fs_remove(const uint8_t num, const char* const path) {
    bool res = false;
    if(path) {
        LOG_WARNING(LITTLE_FS, "%u,ReMoveFile:[%s]", num, path);
        LittleFsHandle_t* Node = LittleFsGetNode(num);
        if(Node) {
            int ret = lfs_remove(&Node->lfs, path);
            res = LittleFsRetToRes(ret);
        }
    }
    return res;
}

bool little_fs_close(const uint8_t num) {
    bool res = false;
    LOG_DEBUG(LITTLE_FS, "Close:%u", num);
    LittleFsHandle_t* Node = LittleFsGetNode(num);
    if(Node) {
        int ret = 0;
        ret = lfs_file_close(&Node->lfs, &Node->file);
        res = LittleFsRetToRes(ret);
    }
    return res;
}

bool little_fs_write_ll(uint8_t num, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(LITTLE_FS, "%u,%s,%s", num, ArrayToStr(data, size), data);
    LittleFsHandle_t* Node = LittleFsGetNode(num);
    if(Node) {
        int ret = 0;
        ret = lfs_file_rewind(&Node->lfs, &Node->file);
        res = LittleFsRetToRes(ret);

        lfs_ssize_t ssize = 0;
        ssize = lfs_file_write(&Node->lfs, &Node->file, data, size);
        if(ssize == size) {
            res = true;
        }
    }
    return res;
}

bool little_fs_write(uint8_t num, const char* path, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(LITTLE_FS, "%u,WriteFile:[%s],WrSize:%u", num, path, size);
    int32_t flags = LFS_O_CREAT | LFS_O_RDWR;
    res = little_fs_open(num, path, flags);
    if(res) {
        res = little_fs_write_ll(num, data, size);
        res = little_fs_close(num);
    }
    return res;
}

bool little_fs_delete(uint8_t num, const char* path) {
    bool res = false;
    LOG_DEBUG(LITTLE_FS, "%u,DeleteFile:[%s]", num, path);
    uint8_t data = 0;
    res = little_fs_write(num, path, &data, 1);
    return res;
}

static bool little_fs_write_end(uint8_t num, const char* path, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(LITTLE_FS, "%u,WriteToEnd,File:[%s],WrSize:%u", num, path, size);
    int32_t flags = LFS_O_CREAT | LFS_O_RDWR | LFS_O_APPEND;
    res = little_fs_open(num, path, flags);
    if(res) {
        res = little_fs_write_ll(num, data, size);
        res = little_fs_close(num);
    }
    return res;
}

/*
 data - must be in RAM
 */
bool little_fs_write_line(uint8_t num, const char* path, char* const data) {
    bool res;
    if(path) {
        if(data) {
            LOG_DEBUG(LITTLE_FS, "%u,WriteToEnd,File:[%s],Text:[%s]", num, path, data);
            uint32_t len = strlen(data);
            data[len] = '\n';
            data[len + 1] = '\r';
            if(len) {
                res = little_fs_write_end(num, path, (uint8_t*)data, len + 2);
            }
        }
    }
    return res;
}

bool little_fs_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(LITTLE_FS, "LITTLE_FS%u", num);
    log_level_get_set(LITTLE_FS, LOG_LEVEL_DEBUG);
    const LittleFsConfig_t* Config = LittleFsGetConfig(num);
    if(Config) {
        res = LittleFsIsValidConfig(Config);
        if(res) {
#ifdef HAS_LITTLE_FS_DIAG
            LOG_WARNING(LITTLE_FS, "%s", LittleFsConfigToStr(Config));
#endif
            LittleFsHandle_t* Node = LittleFsGetNode(num);
            if(Node) {
                Node->cfg = Config->cfg;
                Node->base_address = Config->base_address;
                Node->file_config = Config->file_config;
                Node->name = Config->name;
                Node->num = Config->num;
                Node->valid = true;
                Node->init = true;

                LOG_INFO(LITTLE_FS, "Mount,%u", num);
                int err = lfs_mount(&Node->lfs, &Config->cfg);
                res = LittleFsRetToRes(err);

                // reformat if we can't mount the filesystem
                // this should only happen on the first boot
                if(err < 0) {
                    LOG_WARNING(LITTLE_FS, "Format,%u", num);
                    err = lfs_format(&Node->lfs, &Config->cfg);
                    res = LittleFsRetToRes(err);

                    LOG_INFO(LITTLE_FS, "Mount,%u", num);
                    err = lfs_mount(&Node->lfs, &Config->cfg);
                    res = LittleFsRetToRes(err);
                }
            } else {
                LOG_ERROR(LITTLE_FS, "NodeErr,%u", num);
            }
        } else {
            LOG_ERROR(LITTLE_FS, "ConfigErr,%u", num);
        }
    } else {
        LOG_PARN(LITTLE_FS, "ConfigErr,%u", num);
    }
    log_level_get_set(LITTLE_FS, LOG_LEVEL_INFO);
    return res;
}

COMPONENT_INIT_PATTERT(LITTLE_FS, LITTLE_FS, little_fs)
COMPONENT_PROC_PATTERT(LITTLE_FS, LITTLE_FS, little_fs)
