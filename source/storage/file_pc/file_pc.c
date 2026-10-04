#include "file_pc.h"

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "file_mcal.h"
#include "log.h"
#include "macro_utils.h"
#include "str_utils.h"
#include "win_utils.h"

#ifdef HAS_STRING
#include "str_utils_ex.h"
#endif

#ifdef HAS_MCU
#error That code only for desktop builds
#endif

#ifdef HAS_PC
#include <stdlib.h> //_fullpath
char* _fullpath(char*, const char*, size_t);
#define REAL_RATH(N, R) _fullpath((R), (N), 5000)
//#define REAL_RATH(N, R)
#else

char* realpath(const char* restrict path, char* restrict resolved_path);
#endif

int32_t file_pc_line_cnt(const char* const file_name) {
    LOG_DEBUG(FILE_PC, "FileName: [%s]", file_name);
    FILE* fp = NULL;
    int32_t count = 0; // Line counter (result)
    char c = '?';      // To store a character read from file

    // Get file name from user. The file should be
    // either in current folder or complete path should be provided

    // Open the file
    fp = fopen(file_name, "r");
    if(fp) {
        // Extract characters from file and store in character c
        for(c = getc(fp); c != EOF; c = getc(fp)) {
            if('\n' == c) { // Increment count if this character is newline
                count++;
            }
        }
        // Close the file
        fclose(fp);
        LOG_DEBUG(FILE_PC, "The file [%s] has %d lines", file_name, count);
    } else {
        LOG_ERROR(FILE_PC, "CouldNotOpenFile [%s]", file_name);
        count = -1;
    }
    return count;
}

int32_t file_pc_get_size(char* file_name) {
    int32_t fize_size = -1;
    if(file_name) {
        if(0 < strlen(file_name)) {
            FILE *FileNode;
            FileNode = fopen(file_name, "rb");
            if(FileNode) {
                LOG_DEBUG(FILE_PC, "Open file [%s]", file_name);
                fseek(FileNode, 0, SEEK_END); // seek to end of file
                fize_size = ftell(FileNode); // get current file pointer
                fseek(FileNode, 0, SEEK_SET); // seek back to beginning of file
                // read size of firmware
                fclose(FileNode);
            } else {
                LOG_ERROR(FILE_PC, "FileOpenError3:[%s]", file_name);
            }
        } else {
            LOG_ERROR(FILE_PC, "GetSize,FileNameLenError:[%s]", file_name);
        }
    }
    return fize_size;
}

bool file_pc_load_to_array(const char* const file_name, uint8_t* const out_buff, size_t size,
                           uint32_t* const ret_len_ptr) {
    bool res = false;
    if(file_name) {
        if(out_buff) {
            if(size) {
                if(ret_len_ptr) {
                    res = true;
                }
            }
        }
    }
    uint32_t file_size = 0;
    if(res) {
        res = false;
        file_size = file_get_size(1, file_name);
        if(file_size) {
            LOG_NOTICE(FILE_PC, "File Size:%u Byte=%u kByte", file_size, BYTES_2_KBYTES(file_size));
            if(file_size < size) {
                res = true;
            }
        }
    }

    if(res) {
        res = false;
        FILE* FileNode = NULL;
        FileNode = fopen(file_name, "rb");
        if(FileNode) {
            LOG_NOTICE(FILE_PC, "OpenFile[%s]Ok", file_name);

            size_t real_read = fread((void*)out_buff, file_size, 1, FileNode);
            if(1 == real_read) {
                LOG_DEBUG(FILE_PC, " file load OK %s", file_name);
                *ret_len_ptr = file_size;
                res = true;
            } else {
                LOG_ERROR(FILE_PC, " File load error real_read:%u file_size:%u", real_read, file_size);
                res = false;
            }
            fclose(FileNode);
        } else {
            LOG_ERROR(FILE_PC, "FileOpenError2:[%s]", file_name);
        }
    }
    return res;
}

bool file_pc_load_to_array_i8_ll(FILE* FileNode, size_t offset, int8_t* const out_buff, size_t size) {
    bool res = false;
    if(FileNode) {
        if(out_buff) {
            if(size) {
                size_t read_bytes = 0;
                fseek(FileNode, offset, SEEK_SET);
                read_bytes = fread(out_buff, 1, size, FileNode);
                if(read_bytes == size) {
                    res = true;
                } else {
                    LOG_ERROR(FILE_PC, "readErr");
                }
            } else {
                LOG_ERROR(FILE_PC, "SizeErr");
            }
        } else {
            LOG_ERROR(FILE_PC, "OutBuffErr");
        }
    } else {
        LOG_ERROR(FILE_PC, "FileNodeErr");
    }
    return res;
}

bool file_pc_load_to_array_i8(char* const file_name, size_t offset, int8_t* const out_buff, size_t size) {
    bool res = false;
    if(file_name) {
        FILE* FilePtr = fopen(file_name, "rb");
        if(FilePtr) {
            res = file_pc_load_to_array_i8_ll(FilePtr, offset, out_buff, size);
            if(res) {
            } else {
                LOG_ERROR(FILE_PC, "FileReadErr");
            }
            fclose(FilePtr);
        } else {
            LOG_ERROR(FILE_PC, "FileOpenErr");
        }
    } else {
        LOG_ERROR(FILE_PC, "FileErr [%s]", file_name);
    }
    return res;
}

bool file_pc_run_through_lines(char* in_file_name,
                               char* pattern,
                               char* rep,
                               char* out_file_name) {
    bool res = false;
    FILE* FileNode;
    FILE* out_file_prt;
    char curFileStr[500];
    out_file_prt = fopen(out_file_name, "w");
    FileNode = fopen(in_file_name, "r");
    if(FileNode) {
        LOG_DEBUG(FILE_PC, "Open in file [%s]", in_file_name);
        if(out_file_prt) {
            LOG_DEBUG(FILE_PC, "Open out file [%s]", out_file_name);
        }
        int line = 0;
        while(NULL != fgets(curFileStr, sizeof(curFileStr), FileNode)) {
            LOG_DEBUG(FILE_PC, "%s", curFileStr);
            res = replace_substring(curFileStr, pattern, rep);
            fprintf(out_file_prt, "%s", curFileStr);
            LOG_DEBUG(FILE_PC, "%s", curFileStr);
            line++;
        }
        fclose(FileNode);
        fclose(out_file_prt);
    } else {
        LOG_ERROR(FILE_PC, "RunThroughLines,FileOpenError[%s]", in_file_name);
    }
    return res;
}

#define CACHE_SIZE (20 * 1024)
static char cache[CACHE_SIZE] = {0};

bool file_pc_print_line_cache(const char* const file_name, const char* const line, size_t size) {
    bool res = false;
    if(file_name) {
        if(line && size) {
            snprintf(cache, sizeof(cache), "%s%s\n", cache, line);
            size_t size_len = strlen(cache);
            LOG_DEBUG(FILE_PC, "size:%u", size);
            if(((uint32_t)((float)CACHE_SIZE) * 0.75) < size) {
                res = file_pc_print_line(file_name, cache, size_len);
                memset(cache, 0, sizeof(cache));
            } else {
                res = true;
            }
        } else {
            LOG_ERROR(FILE_PC, "text[%s]%u,Err", line, size);
        }
    } else {
        LOG_ERROR(FILE_PC, "Ptr[%s]Err", file_name);
    }
    return res;
}

bool file_pc_write_line(const FILE* const pFile, const char* const line, const uint32_t size) {
    bool res = false;
    if(pFile) {
        if(line) {
            if(size) {
                LOG_DEBUG(FILE_PC, "AddToEndof,Len:%u,text:[%s]", size, line);
                // fprintf(pFile, "%s", line);
                // fwrite(pFile, "%s", line);
                size_t cnt = fwrite((const void*)line, size, 1, pFile);
                if(1 == cnt) {
                    res = true;
                }
                // res = true;
            } else {
                LOG_ERROR(FILE_PC, "SizeZero,Err");
            }

        } else {
            LOG_ERROR(FILE_PC, "text[%s]%u,Err", line, size);
        }
    } else {
        LOG_ERROR(FILE_PC, "FilePtrErr,[%p]Err", pFile);
    }
    return res;
}

bool file_pc_print_line(const char* const file_name, const char* const line, size_t size) {
    bool res = false;
    if(file_name) {
        if(line && size) {
            LOG_DEBUG(FILE_PC, "AddToEndof,File:[%s],Len:%u,text:[%s]", file_name, size, line);
            FILE* file = NULL;
            file = fopen(file_name, "a");
            if(file) {
                LOG_DEBUG(FILE_PC, "Open[%s]Ok", file_name);
                fprintf(file, "%s\n", line);
                res = true;
                fclose(file);
            } else {
                LOG_ERROR(FILE_PC, "Open[%s]Err", file_name);
            }
        } else {
            LOG_ERROR(FILE_PC, "text[%s]%u,Err", line, size);
        }
    } else {
        LOG_ERROR(FILE_PC, "Ptr[%s]Err", file_name);
    }
    return res;
}

bool file_pc_print_array(const char* const file_name, const uint8_t* const array, size_t size) {
    bool res = false;
    if(file_name) {
        if(array && size) {
            FILE* file = NULL;
            file = fopen(file_name, "a");
            if(file) {
                LOG_DEBUG(FILE_PC, "Open[%s]Ok", file_name);
                uint32_t i = 0;
                for(i = 0; i < size; i++) {
                    fprintf(file, "%c", array[i]);
                    res = true;
                }
                fclose(file);
            } else {
                LOG_ERROR(FILE_PC, "Open[%s]Err", file_name);
            }
        }
    }
    return res;
}

bool file_pc_save_array_i8(const char* const file_name, const int8_t* const data, size_t size) {
    bool res = false;
    if(file_name) {
        if(data) {
            if(size) {
                res = true;
            }
        }
    }

    if(res) {
        res = false;
        FILE* FileNode = NULL;
        FileNode = fopen(file_name, "a");
        if(FileNode) {
            uint32_t i = 0;
            for(i = 0; i < size; i++) {
                fprintf(FileNode, "%d,", data[i]);
                res = true;
            }

            fclose(FileNode);
        } else {
            LOG_ERROR(FILE_PC, "OpenError:[%s]", file_name);
        }
    }
    return res;
}

/*save to the end of file
 * https://neon1ks.github.io/c/13/fwrite.htm
 * */
bool file_pc_save_array(const char* const file_name, const uint8_t* const data, size_t size) {
    bool res = false;
    if(file_name) {
        if(data) {
            if(size) {
                res = true;
            }
        }
    }

    if(res) {
        res = false;
        FILE* FileNode = NULL;
        FileNode = fopen(file_name, "ab");
        if(FileNode) {
            // fseek(FileNode, 0, SEEK_END); // seek to end of file
            // long fize_size = ftell(FileNode);  // get current file pointer
            //(void) fize_size;
            // fseek(FileNode, 0, SEEK_SET); // seek back to beginning of file
            size_t cnt = fwrite((const void*)data, size, 1, FileNode);
            if(1 == cnt) {
                res = true;
                LOG_DEBUG(FILE_PC, "WriteOk");
            } else {
                LOG_ERROR(FILE_PC, "WriteErr %u", cnt);
                res = false;
            }
            fclose(FileNode);
        }
    }
    return res;
}

bool file_pc_array_to_binary_file(const char* const file_name, const uint8_t* const data, size_t size) {
    bool res = false;
    if(file_name) {
        if(data) {
            if(size) {
                LOG_DEBUG(FILE_PC, "Write File:%s,Size:%u byte", file_name, size);
                FILE* file = NULL;
                file = fopen(file_name, "wb");
                if(file) {
                    LOG_DEBUG(FILE_PC, "Open[%s]Ok", file_name);
                    size_t cnt = fwrite((const void*)data, size, 1, file);
                    if(1 == cnt) {
                        res = true;
                        LOG_DEBUG(FILE_PC, "WriteOk");
                    } else {
                        LOG_ERROR(FILE_PC, "WriteErr %u", cnt);
                        res = false;
                    }

                    fclose(file);
                } else {
                    LOG_ERROR(FILE_PC, "OpenErr");
                    res = false;
                }
            } else {
                LOG_ERROR(FILE_PC, "SizeErr");
                res = false;
            }
        } else {
            LOG_ERROR(FILE_PC, "DataErr");
            res = false;
        }
    } else {
        LOG_ERROR(FILE_PC, "FileErr");
        res = false;
    }
    return res;
}

bool file_pc_replace_substr(const char* const file_name, const char* const prev_str, const char* const new_str) {
    bool res = false;
    if(file_name) {
        if(prev_str) {
            if(new_str) {
                LOG_DEBUG(FILE_PC, "PeplaceSubStr File:[%s],Prev:[%s]->New[%s]", file_name, prev_str, new_str);
                char command_line[200] = {0};
                snprintf(command_line, sizeof(command_line), "sed -i -e 's/%s/%s/g' %s", prev_str, new_str, file_name);
                LOG_DEBUG(FILE_PC, "PefrormSed:[%s]", command_line);
                res = win_cmd_run(command_line);
            }
        }
    }
    return res;
}

bool file_pc_rename(const char* const old_name, const char* const new_name) {
    bool res = false;
    int ret = rename(old_name, new_name);
    if(0 == ret) {
        LOG_DEBUG(FILE_PC, "rename Prev:[%s]->New[%s]", old_name, new_name);
        res = true;
    }
    return res;
}

bool file_pc_delete(const char* const file_to_del) {
    bool res = false;
    if(file_to_del) {
        int ret = remove(file_to_del);
        if(0 == ret) {
            LOG_WARNING(FILE_PC, "delete [%s]", file_to_del);
            res = true;
        }
#if 0
        char CmdCommand[500] = {0};
        snprintf(CmdCommand, sizeof(CmdCommand), "rm -f %s", file_name);
        res = win_cmd_run(CmdCommand);
#endif
    }
    return res;
}

/*
 * get relative path
 * C:\job\company\code_base_workspace\code_base_firmware\..\code_base_firmware\source\asics\bc127\bc127_drv.c
 * return absolute Windows path
 * C:/job/company/code_base_workspace/code_base_firmware/source/asics/bc127/bc127_drv.c
 */
bool file_pc_realpath(const char* const in_path, char* const out_file) {
    bool res = false;
    if(in_path) {
        LOG_DEBUG(FILE_PC, "RelativePath:[%s]", in_path);
        if(out_file) {
            char* abs_path = REAL_RATH(in_path, out_file);
            if(abs_path) {
                int ret = replace_char(out_file, '\\', '/');
                LOG_DEBUG(FILE_PC, "AbsolutePath:[%s],%u", out_file, ret);
                ret = replace_char(abs_path, '\\', '/');
                LOG_DEBUG(FILE_PC, "AbsolutePath:[%s],%u", abs_path, ret);
                free(abs_path);
                res = true;
            }
        }
    }
    return res;
}


bool file_pc_get_file_content(const char* filename, char* content, unsigned long* max_content_size) {
    bool res = false;
    if (filename) {
        if (content) {
            if (max_content_size) {
                FILE *pFile = fopen(filename, "r");
                if (pFile ) {
                    LOG_DEBUG(FILE_PC, "Open,Filename:[%s]Ok", filename);
                    *max_content_size = fread(content, sizeof(char), *max_content_size, pFile );
                    fclose(pFile );
                    res = true;
                }else{
                    LOG_ERROR(FILE_PC, "Open,FileName:[%s]", filename);
                }
            }

        }
    }
    return res;
}
