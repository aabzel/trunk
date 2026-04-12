#include "little_fs_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "little_fs.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

const char* LittleFsTypeToStr(const uint8_t type) {
    char* name = "?";
    switch(type) {
    case LFS_TYPE_REG:
        name = "Reg";
        break;
    case LFS_TYPE_DIR:
        name = "Dir";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* LittleFsFileInfoToStr(const struct lfs_info* const Info) {
    if(Info) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sName:[%s],", text, Info->name);
        snprintf(text, sizeof(text), "%sSize:%u,", text, Info->size);
        snprintf(text, sizeof(text), "%sType:%u=", text, Info->type);
        snprintf(text, sizeof(text), "%s%s,", text, LittleFsTypeToStr(Info->type));
    }
    return text;
}

const char* LittleFsInfoToStr(const struct lfs_fsinfo* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sDiskVer:%u,", text, Node->disk_version);
        // Size of a logical block in bytes.
        snprintf(text, sizeof(text), "%sBlockSize:%u,", text, Node->block_size);
        snprintf(text, sizeof(text), "%sBlockCnt:%u,", text, Node->block_count);
        snprintf(text, sizeof(text), "%sNameMax:%u,", text, Node->name_max);
        snprintf(text, sizeof(text), "%sFileMax:%u,", text, Node->file_max);
        snprintf(text, sizeof(text), "%sAttrMax:%u,", text, Node->attr_max);
    }
    return text;
}

const char* LittleFsRetToStr(const int err) {
    char* name = "?";
    switch(err) {
    case LFS_ERR_NOMEM:
        name = "NoMoreMemoryAvailable";
        break;
    case LFS_ERR_NOENT: // No directory entry
        name = "NoDirEntry";
        break;
    case LFS_ERR_OK:
        name = "Ok";
        break;
    case LFS_ERR_NOSPC:
        name = "NoSpace";
        break; // No space left on device
    case LFS_ERR_IO:
        name = "Io";
        break;
    case LFS_ERR_CORRUPT:
        name = "Corrupt";
        break;
    case LFS_ERR_EXIST:
        name = "ExisT";
        break;
    case LFS_ERR_NOTDIR:
        name = "NotDir";
        break;
    case LFS_ERR_ISDIR:
        name = "IsDir";
        break;
    case LFS_ERR_NOTEMPTY:
        name = "NoteMPTY";
        break;
    case LFS_ERR_BADF:
        name = "BadF";
        break;
    case LFS_ERR_FBIG:
        name = "Fbig";
        break;
    case LFS_ERR_INVAL:
        name = "INVal";
        break;
    case LFS_ERR_NOATTR:
        name = "NOAttr";
        break;
    case LFS_ERR_NAMETOOLONG:
        name = "NameTooLong";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* LittleFsFlagToStr(const int32_t flags) {
    strcpy(text, "");
    if(LFS_O_CREAT == (LFS_O_CREAT & flags)) {
        snprintf(text, sizeof(text), "%s,Create", text);
    }

    if(LFS_O_RDONLY == (LFS_O_RDONLY & flags)) {
        snprintf(text, sizeof(text), "%s,ReadOnly", text);
    }

    if(LFS_F_ERRED == (LFS_F_ERRED & flags)) {
        snprintf(text, sizeof(text), "%s,ERRED", text);
    }
    if(LFS_F_READING == (LFS_F_READING & flags)) {
        snprintf(text, sizeof(text), "%s,READING", text);
    }
    if(LFS_F_WRITING == (LFS_F_WRITING & flags)) {
        snprintf(text, sizeof(text), "%s,WRITING", text);
    }
    if(LFS_F_DIRTY == (LFS_F_DIRTY & flags)) {
        snprintf(text, sizeof(text), "%s,DIRTY", text);
    }
    if(LFS_O_EXCL == (LFS_O_EXCL & flags)) {
        snprintf(text, sizeof(text), "%s,EXCL", text);
    }
    if(LFS_O_APPEND == (LFS_O_APPEND & flags)) {
        snprintf(text, sizeof(text), "%s,APPEND", text);
    }
    if(LFS_O_CREAT == (LFS_O_CREAT & flags)) {
        snprintf(text, sizeof(text), "%s,CREAT", text);
    }
    if(LFS_O_RDWR == (LFS_O_RDWR & flags)) {
        snprintf(text, sizeof(text), "%s,RDWR", text);
    }
    if(LFS_O_TRUNC == (LFS_O_TRUNC & flags)) {
        snprintf(text, sizeof(text), "%s,TRUNC", text);
    }
    if(LFS_O_WRONLY == (LFS_O_WRONLY & flags)) {
        snprintf(text, sizeof(text), "%s,WRONLY", text);
    }

    if(LFS_F_INLINE == (LFS_F_INLINE & flags)) {
        snprintf(text, sizeof(text), "%s,INLINE", text);
    }

    return text;
}

const char* LittleFsCfgToStr(const struct lfs_config* const cfg) {
    static char lTest[200] = {0};
    if(cfg) {
        strcpy(lTest, "");
        snprintf(lTest, sizeof(lTest), "%sRead:0x%p,", lTest, cfg->read);
        snprintf(lTest, sizeof(lTest), "%sProg:0x%p,", lTest, cfg->prog);
        snprintf(lTest, sizeof(lTest), "%sErase:0x%p,", lTest, cfg->erase);
        snprintf(lTest, sizeof(lTest), "%sSync:0x%p,", lTest, cfg->sync);
        snprintf(lTest, sizeof(lTest), "%sRdSize:%u,", lTest, cfg->read_size);
        snprintf(lTest, sizeof(lTest), "%sWrSize:%u,", lTest, cfg->prog_size);
        snprintf(lTest, sizeof(lTest), "%sBlkSize:%u,", lTest, cfg->block_size);
        snprintf(lTest, sizeof(lTest), "%sBlkCnt:%u,", lTest, cfg->block_count);
        snprintf(lTest, sizeof(lTest), "%sBlkCyc:%u,", lTest, cfg->block_cycles);
        snprintf(lTest, sizeof(lTest), "%sCacSz:%u,", lTest, cfg->cache_size);
        snprintf(lTest, sizeof(lTest), "%sLaSz:%u,", lTest, cfg->lookahead_size);
    }
    return lTest;
}

const char* LittleFsConfigToStr(const LittleFsConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sBaseAddr:0x%08X,", text, Config->base_address);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%s%s,", text, LittleFsCfgToStr(&Config->cfg));
    }
    return text;
}

const char* LittleFsNodeToStr(const LittleFsHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool little_fs_diag(uint8_t num) {
    bool res = false;
    LittleFsHandle_t* Node = LittleFsGetNode(num);
    if(Node) {
        // Finds the current size of the filesystem
        lfs_ssize_t size = lfs_fs_size(&Node->lfs);
        LOG_INFO(LITTLE_FS, "LITTLE_FS_%u,Size:%u Byte", num, size);

        struct lfs_fsinfo fsinfo = {0};
        int ret = lfs_fs_stat(&Node->lfs, &fsinfo);
        if(ret) {
            LOG_INFO(LITTLE_FS, "LITTLE_FS_%u,%s", num, LittleFsInfoToStr(&fsinfo));
        }
    }
    return res;
}

bool little_fs_cat(uint8_t num, const char* const path) {
    bool res = false;
    int32_t flags = LFS_O_RDONLY;
    LittleFsHandle_t* Node = LittleFsGetNode(num);
    if(Node) {
        res = little_fs_open(num, path, flags);
        if(res) {
            lfs_soff_t size = lfs_file_size(&Node->lfs, &Node->file);
            LOG_INFO(LITTLE_FS, "File:%s,Size:%u Byte", path, size);

            bool loop = true;
            while(loop) {
                char buffer[2] = {0};
                lfs_ssize_t len = lfs_file_read(&Node->lfs, &Node->file, buffer, 1);
                if(1 == len) {
                    cli_printf("%c", buffer[0]);
                } else {
                    loop = false;
                }
            }
            res = little_fs_close(num);
        }
    }
    return res;
}

/*
 https://github.com/littlefs-project/littlefs/issues/2


 */
bool little_fs_list(uint8_t num, const char* const path) {
    bool res = false;
    uint32_t cnt = 0;
    LOG_INFO(LITTLE_FS, "%u,path:[%s]", num, path);

    const table_col_t cols[] = {
        {5, "N"}, {17, "name"}, {9, "size"}, {5, "type"}, {5, "type"},

    };
    LittleFsHandle_t* Node = LittleFsGetNode(num);
    if(Node) {
        lfs_dir_t dir = {0};
        int err = lfs_dir_open(&Node->lfs, &dir, path);
        // res = LittleFsRetToRes(err);
        if(err) {
            LOG_INFO(LITTLE_FS, "Open[%s]Ok", path);
            table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
            struct lfs_info FileInfo = {0};
            bool loop = true;
            while(loop) {
                int ret = lfs_dir_read(&Node->lfs, &dir, &FileInfo);
                if(ret < 0) {
                    LOG_ERROR(LITTLE_FS, "ReadDirErr");
                    loop = false;
                    break;
                } else {
                    LOG_DEBUG(LITTLE_FS, "ReadOk %s", LittleFsFileInfoToStr(&FileInfo));
                    cnt++;
                }

                if(0 == ret) {
                    loop = false;
                    break;
                }

                char temp[150] = {0};
                strcpy(temp, TSEP);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, cnt);
                snprintf(temp, sizeof(temp), "%s %15s " TSEP, temp, FileInfo.name);
                snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, FileInfo.size);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, FileInfo.type);
                snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, LittleFsTypeToStr(FileInfo.type));
                cli_printf("%s" CRLF, temp);
            }

            table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
            err = lfs_dir_close(&Node->lfs, &dir);
            // res = LittleFsRetToRes(err);
            if(err) {
                res = false;
            }
        } else {
            LOG_ERROR(LITTLE_FS, "NotDir:[%s]", path);
        }
    } else {
        LOG_ERROR(LITTLE_FS, "NodeErr");
    }

    if(cnt) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
