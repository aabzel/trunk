ifneq ($(FAT_FS_MCAL_MK_INC),Y)
    FAT_FS_MCAL_MK_INC=Y

    FAT_FS_MCAL_DIR = $(STORAGE_DIR)/fat_fs
    # $(error FAT_FS_MCAL_DIR=$(FAT_FS_MCAL_DIR))

    INCDIR += -I$(FAT_FS_MCAL_DIR)

    MCAL_OPT += -DHAS_FAT_FS

    ifeq ($(FAT_FS_PROC),Y)
        MCAL_OPT += -DHAS_FAT_FS_PROC
    endif

    SOURCES_C += $(FAT_FS_MCAL_DIR)/fat_fs.c

    ifeq ($(FAT_FS_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_FAT_FS_INTERRUPTS
        SOURCES_C += $(FAT_FS_MCAL_DIR)/fat_fs_isr.c
    endif

    # must be outside

    ifeq ($(DIAG),Y)
        ifeq ($(FAT_FS_DIAG),Y)
            MCAL_OPT += -DHAS_FAT_FS_DIAG
            SOURCES_C += $(FAT_FS_MCAL_DIR)/fat_fs_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(FAT_FS_COMMANDS),Y)
            MCAL_OPT += -DHAS_FAT_FS_COMMANDS
            SOURCES_C += $(FAT_FS_MCAL_DIR)/fat_fs_commands.c
        endif
    endif
endif
