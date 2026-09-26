#include "file_mcal.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro_utils.h"
#include "std_includes.h"

#ifdef HAS_FAT_FS
#include "fat_fs.h"
#endif

#ifdef HAS_CSV
#include "csv.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_STRING
//#include "str_utils_ex.h"
#endif

#ifdef HAS_FAT_FS
#include "fat_fs.h"
#endif

#ifdef HAS_LITTLE_FS
#include "little_fs.h"
#endif

#ifdef HAS_FILE_PC
#include "file_pc.h"
#endif

COMPONENT_GET_NODE(FileMcal, file_mcal)
COMPONENT_GET_CONFIG(FileMcal, file_mcal)
COMPONENT_IS_VALID(FileMcal, file_mcal)

int32_t file_line_cnt(uint8_t num, const char* const file_name) {
    int32_t line_cnt = -1;

    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        LOG_NOTICE(FILE_MCAL, "LineCnt:{%s}", FileMcalNodeToStr(Node));
        switch(Node->fileSystem.file_system) {
        case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
            line_cnt = fat_fs_file_line_cnt(file_name);
#endif
        } break;

        case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
            line_cnt = file_pc_line_cnt(file_name);
#endif
        } break;

        default: {
            line_cnt = -1;
        } break;
        } // switch
    }     // if(Node)

    if(line_cnt < 0) {
#ifdef HAS_LOG
        LOG_ERROR(FILE_MCAL, "LineCntErr");
#endif
    }
    return line_cnt;
}

int32_t file_get_size(uint8_t num, const char* const file_name) {
    int32_t fize_size = 0;
    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        LOG_NOTICE(FILE_MCAL, "GetSize:{%s}", FileMcalNodeToStr(Node));
        switch(Node->fileSystem.file_system) {
        case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
            fize_size = fat_fs_file_get_size(file_name);
#endif
        } break;

        case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
            fize_size = file_pc_get_size(file_name);
#endif
        } break;

        case FILE_SYS_LITTLE_FS: {
        } break;

        default: {
            fize_size = 0;
        } break;
        }
    }
    return fize_size;
}

/*
  data address to put result
  size - bures to read
  read_size - real read size
  returns actual read size
  */
uint32_t file_mcal_read(uint8_t num, uint8_t* const data, uint32_t size) {
    uint32_t read_size = 0;
    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        LOG_DEBUG(FILE_MCAL, "Read,Size:%u,{%s}", size, FileMcalNodeToStr(Node));
        if(FILE_STATE_OPEN == Node->state) {
            switch(Node->fileSystem.file_system) {

            case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
                if(Node->FilePtr) {
                    uint32_t real_read = fread((void*)data, size, 1, Node->FilePtr);
                    if(real_read) {
                        read_size = size;
                        Node->read_total += size;
                    } else {
                        LOG_DEBUG(FILE_MCAL, "Read:%u,Size:%u", real_read, size);
                        Node->read_error_cnt++;
                    }
                } else {
                    LOG_ERROR(FILE_MCAL, "PtrErr");
                }
#endif
            } break;

            case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
                UINT real_read = 0; /* [OUT] Number of bytes read */
                FRESULT ret = f_read(&Node->FatFsFile, (void*)data, (UINT)size, &real_read);
                if(FR_OK == ret) {
                    read_size = (uint32_t)real_read;
                    if(size == real_read) {

                    } else {
                        LOG_ERROR(FILE_MCAL, "FATFS,Read,Size,Error:%u!=%u", size, real_read);
                    }
                } else {
                    LOG_ERROR(FILE_MCAL, "FATFS,Read,Error:%u=%s", ret, FatFsResToStr(ret));
                }
#endif
            } break;

            case FILE_SYS_LITTLE_FS: {
            } break;

            default: {
            } break;

            } // switch (Node->fileSystem.file_system)
        } else {
            // if(FILE_STATE_OPEN == Node->state)
            LOG_ERROR(FILE_MCAL, "ReadClosed");
        }
    } // if(Node) {
    return read_size;
}

bool file_mcal_write_line(uint8_t num, const char* const line, uint32_t len) {
    bool res = false;
    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        LOG_DEBUG(FILE_MCAL, "AddToEndof,Len:%u,text:[%s]", len, line);
        if(FILE_STATE_OPEN == Node->state) {
            LOG_DEBUG(FILE_MCAL, "WriteLine:{%s}", FileMcalNodeToStr(Node));
            switch(Node->fileSystem.file_system) {
            case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
                res = fat_fs_write_line(&Node->FatFsFile, line, len);
#endif
            } break;

            case FILE_SYS_LITTLE_FS: {
#ifdef HAS_LITTLE_FS
                res = little_fs_write_line(Node->fs_num, (uint8_t*)line, len);
#endif
            } break;

            case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
                res = file_pc_write_line(Node->FilePtr, line, len);

#endif
            } break;

            default:
                res = false;
                break;
            } // switch (Node->fileSystem.file_system) {

            if(res) {
                Node->write_total += len;
            }
        } else {
            LOG_ERROR(FILE_MCAL, "WriteInClosedFile");
        }
    } // if(Node) {

    return res;
}

bool FileMcalIsValidConfig(const FileMcalConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(FILE_MCAL, "FILE_MCAL_%u,Name,Err", Config->num);
            res = false;
        }

        ifn(Config->fileSystem.file_system) {
            LOG_ERROR(FILE_MCAL, "FILE_MCAL_%u,file_system,Err", Config->num);
            res = false;
        }
    }
    return res;
}

/*
  data - [IN] Pointer to the data to be written
  size   [IN] Number of bytes to write
 */
bool file_mcal_write(uint8_t num, const uint8_t* const data, const uint32_t size) {
    bool res = false;
    if(size) {
        FileMcalHandle_t* Node = FileMcalGetNode(num);
        if(Node) {
            if(FILE_STATE_OPEN == Node->state) {
                LOG_DEBUG(FILE_MCAL, "Write,Size:%u,{%s}", size, FileMcalNodeToStr(Node));
                switch(Node->fileSystem.file_system) {
                case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
                    // https://metanit.com/c/tutorial/7.9.php
                    size_t write_cnt = fwrite((void*)data, size, 1, Node->FilePtr);
                    if(write_cnt) {
                        res = true;
                        Node->write_total += size;
                    } else {
                        LOG_ERROR(FILE_MCAL, "WriteSizeError,Written:%u,Need:%u", write_cnt, size);
                        res = false;
                    }
#endif
                } break;

                case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
                    res = false;
                    UINT written = 0; /* [OUT] Pointer to the variable to return number of bytes written */
                    FRESULT ret = f_write(&Node->FatFsFile, (void*)data, (UINT)size, &written);
                    if(FR_OK == ret) {
                        Node->write_total += written;
                        if(size == written) {
                            res = true;
                        }
                    }
#endif
                } break;

                default: {
                    LOG_ERROR(FILE_MCAL, "UndefFileSystem");
                    res = false;
                } break;

                } // switch
            } else {
                LOG_ERROR(FILE_MCAL, "WriteClosed");
            }
        } else {
            LOG_ERROR(FILE_MCAL, "NodeError");
        }
    } else {
        LOG_ERROR(FILE_MCAL, "SizeZero");
    }
    return res;
}

/*save to the end of file*/
bool file_save_array(uint8_t num, const char* const file_name, const uint8_t* const data, uint32_t size) {
    bool res = false;
    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        LOG_NOTICE(FILE_MCAL, "Save,Size:%u,{%s}", size, FileMcalNodeToStr(Node));
        switch(Node->fileSystem.file_system) {
        case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
            res = fat_fs_save_array(1, file_name, data, size);
#endif
        } break;

        case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
            res = file_pc_save_array(file_name, data, size);
#endif
        } break;

        case FILE_SYS_LITTLE_FS: {
        } break;

        default: {
            res = false;
        } break;
        }
    }
    return res;
}

bool file_array_to_binary_file(uint8_t num, const char* const file_name, const uint8_t* const data, uint32_t size) {
    bool res = false;
    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        LOG_NOTICE(FILE_MCAL, "ArrayToFile,Size:%u,{%s}", size, FileMcalNodeToStr(Node));
        switch(Node->fileSystem.file_system) {
        case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
            res = fat_fs_save_array(1, file_name, data, size);
#endif
        } break;

        case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
            res = file_pc_array_to_binary_file(file_name, data, size);
#endif
        } break;

        default: {
            res = false;
        } break;
        }
    }

    return res;
}

bool file_mcal_init_custom(void) {
    bool res = false;
    LOG_NOTICE(FILE_MCAL, "Version:%u", FILE_MCAL_VERSION);
    return res;
}

bool file_mcal_rename(uint8_t num, const char* const old_name, const char* const new_name) {
    bool res = false;
    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        LOG_NOTICE(FILE_MCAL, "ReName,%s->%s", old_name, new_name);
        switch(Node->fileSystem.file_system) {
        case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
            res = file_pc_rename(old_name, new_name);
#endif
        } break;

        case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
            res = fat_fs_rename(old_name, new_name);
#endif
        } break;

        case FILE_SYS_LITTLE_FS: {
        } break;

        default: {
        } break;
        }
    }
    return res;
}

bool file_mcal_delete(uint8_t num, const char* const file_name) {
    bool res = false;
    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        LOG_WARNING(FILE_MCAL, "Delete,{%s}", FileMcalNodeToStr(Node));
        switch(Node->fileSystem.file_system) {

        case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
            res = file_pc_delete(file_name);
#endif
        } break;

        case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
            res = fat_fs_unlink(1, file_name);
#endif
        } break;

        case FILE_SYS_LITTLE_FS: {
        } break;

        default: {
            res = false;
        } break;
        }
        Node->state = FILE_STATE_CLOSED;
    }
    return res;
}

bool file_mcal_open_append(uint8_t num, const char* const file_name) {
    bool res = false;
    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        if(file_name) {
            LOG_NOTICE(FILE_MCAL, "OpenForWrite,{%s}", FileMcalNodeToStr(Node));
            switch(Node->fileSystem.file_system) {
            case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
                Node->FilePtr = fopen(file_name, "a");
                if(Node->FilePtr) {
                    Node->state = FILE_STATE_OPEN;
                    res = true;
                } else {
                    LOG_ERROR(FILE_MCAL, "Open[%s]Err", file_name);
                }
#endif
            } break;

            case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
                FRESULT ret = FR_INT_ERR;
                ret = f_open(&Node->FatFsFile, (const TCHAR*)file_name, FA_WRITE | FA_OPEN_APPEND);
                res = FatFsRetToRes(ret, "OpenWbin");
#endif
            } break;

            case FILE_SYS_LITTLE_FS: {
            } break;

            default:
                LOG_ERROR(FILE_MCAL, "UndefFileSys,Code:%u,Err", Node->fileSystem.file_system);
                break;
            }

            if(res) {
                strcpy(Node->file_name, file_name);
                Node->read_total = 0;
                Node->write_total = 0;
                Node->state = FILE_STATE_OPEN;
            } else {
#ifdef HAS_LOG
                LOG_ERROR(FILE_MCAL, "Open[%s]Err", file_name);
#endif
            }
        }
    }
    return res;
}

bool file_mcal_open_wb(uint8_t num, const char* const file_name) {
    bool res = false;
    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        Node->read_total = 0;
        Node->write_total = 0;
        strcpy(Node->file_name, file_name);
        LOG_INFO(FILE_MCAL, "OpenForWrite,{%s}", FileMcalNodeToStr(Node));
        switch(Node->fileSystem.file_system) {
        case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
            Node->FilePtr = fopen(file_name, "wb");
            if(Node->FilePtr) {
                Node->state = FILE_STATE_OPEN;
                res = true;
            } else {
                LOG_ERROR(FILE_MCAL, "Open[%s]Err", file_name);
            }
#endif
        } break;

        case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
            FRESULT ret = FR_INT_ERR;
            ret = f_open(&Node->FatFsFile, (const TCHAR*)file_name, FA_WRITE | FA_CREATE_ALWAYS);
            res = FatFsRetToRes(ret, "OpenWbin");
#endif
        } break;

        case FILE_SYS_LITTLE_FS: {
        } break;

        default:
            LOG_ERROR(FILE_MCAL, "UndefFileSys,Code:%u,Err", Node->fileSystem.file_system);
            break;
        }

        if(res) {
            Node->state = FILE_STATE_OPEN;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(FILE_MCAL, "Open[%s]Err", file_name);
#endif
        }
    }
    return res;
}

bool file_mcal_open_re(uint8_t num, const char* const file_name) {
    bool res = false;
    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        Node->read_total = 0;
        Node->write_total = 0;
        strcpy(Node->file_name, file_name);
        LOG_DEBUG(FILE_MCAL, "OpenForRead:{%s}", FileMcalNodeToStr(Node));
        switch(Node->fileSystem.file_system) {

        case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
            Node->FilePtr = fopen(file_name, "rb");
            if(Node->FilePtr) {
                res = true;
            }else{
                LOG_ERROR(FILE_MCAL, "fopen,Error:[%s]", file_name);
            }
#endif
        } break;

        case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
            FRESULT ret = FR_INT_ERR;
            ret = f_open(&Node->FatFsFile, (const TCHAR*)file_name, FA_READ | FA_OPEN_EXISTING);
            res = FatFsRetToRes(ret, "Open");
#endif
        } break;

        case FILE_SYS_LITTLE_FS: {
#ifdef HAS_LITTLE_FS
#endif
        } break;

        default:
            LOG_ERROR(FILE_MCAL, "Undef,fileSystem,Err");
            break;
        }

        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(FILE_MCAL, "Open[%s]Err", file_name);
#endif
        } else {
            Node->state = FILE_STATE_OPEN;
        }
    }
    return res;
}

bool file_mcal_close(uint8_t num) {
    bool res = false;
    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        LOG_NOTICE(FILE_MCAL, "Close:{%s}", FileMcalNodeToStr(Node));
        switch(Node->fileSystem.file_system) {
        case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
            FRESULT ret = FR_INT_ERR;
            ret = f_close(&Node->FatFsFile);
            res = FatFsRetToRes(ret, "Close");
#endif
        } break;

        case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
            int ret = fclose(Node->FilePtr);
            if(0 == ret) {
                Node->FilePtr = NULL;
                res = true;
            }
#endif
        } break;

        case FILE_SYS_LITTLE_FS: {
            res = false;
#ifdef HAS_LITTLE_FS
#endif
        } break;

        default: {
            res = false;
        } break;

        } // end of switch(Node->fileSystem.file_system)

        if(res) {
            strcpy(Node->file_name, "");
            Node->state = FILE_STATE_CLOSED;
            Node->write_total = 0;
            Node->read_total = 0;
        }
    }
    return res;
}

bool file_mcal_gets(FileMcalHandle_t* const Node, char* const line, uint32_t size, uint32_t* const read_len_prt) {
    bool res = false;
    if(Node) {
        LOG_NOTICE(FILE_MCAL, "Get:{%s}", FileMcalNodeToStr(Node));
        if(FILE_STATE_OPEN == Node->state) {
            if(line) {
                if(size) {
                    if(read_len_prt) {
                        res = true;
                    }
                }
            }
        }
    }

    if(res) {
        res = false;
        switch(Node->fileSystem.file_system) {
        case FILE_SYS_FAT_FS: {
#ifdef HAS_FAT_FS
            TCHAR* buff = f_gets((TCHAR*)line, (int)size, &Node->FatFsFile);
            if(buff) {
                *read_len_prt = strlen(line);
                res = true;
            }
#endif
        } break;

        case FILE_SYS_POSIX_API: {
#ifdef HAS_FILE_PC
            // http://all-ht.ru/inf/prog/c/func/fgets.html
            if(Node->FilePtr) {
                char* estr = fgets(line, (int)size, Node->FilePtr);
                if(estr) {
                    *read_len_prt = strlen(line);
                    res = true;
                } else {
                    res = false;
                }
            } else {
                LOG_ERROR(FILE_MCAL, "NotOpened");
                res = false;
            }
#endif
        } break;

        case FILE_SYS_LITTLE_FS: {
        } break;

        default: {
            res = false;
        } break;
        }
    }
    return res;
}

bool file_mcal_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(FILE_MCAL, "FILE_MCAL_%u,Proc", num);
    FileMcalHandle_t* Node = FileMcalGetNode(num);
    if(Node) {
        Node->spin++;
    }
    return res;
}

/*
 */
char* file_path_to_file_name(const char* const file_path) {
    bool res = false;
    static char file_name[100] = {0};
#ifdef HAS_CSV
    res = csv_parse_last_text(file_path, '/', file_name, sizeof(file_name));
#endif
    if(!res) {
        strcpy(file_name, "?");
    }
    return file_name;
}

bool file_mcal_init_common(const FileMcalConfig_t* const Config, FileMcalHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->fileSystem = Config->fileSystem;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool file_mcal_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(FILE_MCAL, "FILE_MCAL_%u", num);
    const FileMcalConfig_t* Config = FileMcalGetConfig(num);
    res = FileMcalIsValidConfig(Config);
    if(res) {
#ifdef HAS_FILE_MCAL_DIAG
        LOG_WARNING(FILE_MCAL, "%s", FileMcalConfigToStr(Config));
#endif
        FileMcalHandle_t* Node = FileMcalGetNode(num);
        if(Node) {
            res = file_mcal_init_common(Config, Node);
            Node->state = FILE_STATE_CLOSED;
            Node->valid = true;
            Node->init = true;
        } else {
            LOG_ERROR(FILE_MCAL, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(FILE_MCAL, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(FILE_MCAL, FILE_MCAL, file_mcal)
COMPONENT_PROC_PATTERT(FILE_MCAL, FILE_MCAL, file_mcal)
