
ifneq ($(FAT_FS_COM_MK_INC),Y)
    FAT_FS_COM_MK_INC=Y


    FAT_FS_COM_DIR = $(STORAGE_DIR)/fat_fs
    #@echo $(error FAT_FS_DIR = $(FAT_FS_DIR))

    OPT += -DHAS_FAT_FS

    INCDIR += -I$(FAT_FS_COM_DIR)
    SOURCES_C += $(FAT_FS_COM_DIR)/fat_fs_drv.c
    SOURCES_C += $(FAT_FS_COM_DIR)/fat_fs_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(FAT_FS_DIAG),Y)
            OPT += -DHAS_FAT_FS_DIAG
            SOURCES_C += $(FAT_FS_COM_DIR)/fat_fs_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        #@echo $(error CLI=$(CLI))
        ifeq ($(FAT_FS_COMMANDS),Y)
            #@echo $(error FAT_FS_COMMANDS = $(FAT_FS_COMMANDS))
            OPT += -DHAS_FAT_FS_COMMANDS
            SOURCES_C += $(FAT_FS_COM_DIR)/fat_fs_commands.c
        endif
    endif
endif
