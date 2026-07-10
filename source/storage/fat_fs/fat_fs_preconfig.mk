ifneq ($(FAT_FS_PRECONFIG_INC),Y)
    FAT_FS_PRECONFIG_INC=Y
    
    DISK=Y
    DISKIO=Y
    FAT_FS=Y
endif
