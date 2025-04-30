ifneq ($(FAT_FS_MK_INC),Y)
    FAT_FS_MK_INC=Y


    FAT_FS_DIR += $(THIRD_PARTY_DIR)/fat_fs
    #@echo $(error FAT_FS_DIR= $(FAT_FS_DIR))
    INCDIR += -I$(FAT_FS_DIR)
    INCDIR += -I$(FAT_FS_DIR)/src
    INCDIR += -I$(FAT_FS_DIR)/src/options

    SOURCES_THIRD_PARTY_C += $(FAT_FS_DIR)/src/diskio.c
    #SOURCES_THIRD_PARTY_C += $(FAT_FS_DIR)/src/option/unicode.c
    SOURCES_THIRD_PARTY_C += $(FAT_FS_DIR)/src/option/ccsbcs.c
    SOURCES_THIRD_PARTY_C += $(FAT_FS_DIR)/src/ff.c
endif