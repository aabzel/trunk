#ifndef FAT_FS_COMMANDS_H
#define FAT_FS_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_FAT_FS
#error "+HAS_FAT_FS"
#endif

#ifndef HAS_FAT_FS_COMMANDS
#error "+HAS_FAT_FS_COMMANDS"
#endif

bool fat_fs_cat_command(int32_t argc, char* argv[]);
bool fat_fs_diag_command(int32_t argc, char* argv[]);
bool fat_fs_root_command(int32_t argc, char* argv[]);
bool fat_fs_scan_command(int32_t argc, char* argv[]);
bool fat_fs_file_write_command(int32_t argc, char* argv[]);
bool fat_fs_format_command(int32_t argc, char* argv[]);
bool fat_fs_mount_command(int32_t argc, char* argv[]);
bool fat_fs_open_command(int32_t argc, char* argv[]);
bool fat_fs_open_dirr_command(int32_t argc, char* argv[]);
bool fat_fs_read_dirr_command(int32_t argc, char* argv[]);
bool fat_fs_write_command(int32_t argc, char* argv[]);
bool fat_fs_read_command(int32_t argc, char* argv[]);
bool fat_fs_close_command(int32_t argc, char* argv[]);
bool fat_fs_seek_command(int32_t argc, char* argv[]);
bool fat_fs_unlink_command(int32_t argc, char* argv[]);
bool fat_fs_init_command(int32_t argc, char* argv[]);
bool fat_fs_write_verify_command(int32_t argc, char* argv[]);
bool fat_fs_delete_command(int32_t argc, char* argv[]);

#define FAT_FS_DIAG_COMMANDS                        \
    SHELL_CMD("fat_fs_scan",  "ffs", fat_fs_scan_command, "FatFsScan"),                     \
    SHELL_CMD("fat_fs_read_dir",  "ffrd", fat_fs_read_dirr_command, "FatFsReadDir"),       \
    SHELL_CMD("fat_fs_read",  "ftfsr", fat_fs_read_command, "FatFsRead"),                    \
    SHELL_CMD("fat_fs_cat",  "cat", fat_fs_cat_command, "FatFsCat"),                         \
    SHELL_CMD("fat_fs_diag",  "ffd", fat_fs_diag_command, "FatFsDiag"),

#define FAT_FS_COMMANDS        FAT_FS_DIAG_COMMANDS                                                \
    SHELL_CMD("fat_fs_write_verify",  "ffwv", fat_fs_write_verify_command, "FatFsWriteRevify"),    \
    SHELL_CMD("fat_fs_root",  "ffr", fat_fs_root_command, "FatFsRoot"),                            \
    SHELL_CMD("fat_fs_del",  "ffdel", fat_fs_delete_command, "FatFsDelete"),                       \
    SHELL_CMD("fat_fs_format",  "fatff", fat_fs_format_command, "FatFsFormat"),              \
    SHELL_CMD("fat_fs_unlink",  "funl", fat_fs_unlink_command, "FatFsUnLink"),               \
    SHELL_CMD("fat_fs_open",  "ftfso", fat_fs_open_command, "FatFsOpen"),                    \
    SHELL_CMD("fat_fs_open_dir",  "ftfsod", fat_fs_open_dirr_command, "FatFsOpenDir"),       \
    SHELL_CMD("fat_fs_write", "ftfsw", fat_fs_write_command, "FatFsWrite"),                  \
    SHELL_CMD("fat_fs_file_write", "ffw", fat_fs_file_write_command, "FatFsFileWrite"),      \
    SHELL_CMD("fat_fs_seek",  "ftfss", fat_fs_seek_command, "FatFsSeek"),                    \
    SHELL_CMD("fat_fs_close", "ftfsc", fat_fs_close_command, "FatFsClose"),                  \
    SHELL_CMD("fat_fs_init", "ftfsi", fat_fs_init_command, "FatFsInit"),                     \
    SHELL_CMD("fat_fs_mount", "ftfsm", fat_fs_mount_command, "FatFsMount"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FAT_FS_COMMANDS_H */
