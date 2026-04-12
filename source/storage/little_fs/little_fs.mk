ifneq ($(LITTLE_FS_MCAL_MK_INC),Y)
    LITTLE_FS_MCAL_MK_INC=Y

    LITTLE_FS_DIR = $(STORAGE_DIR)/little_fs
    # $(error LITTLE_FS_DIR=$(LITTLE_FS_DIR))

    INCDIR += -I$(LITTLE_FS_DIR)

    MCAL_OPT += -DHAS_LITTLE_FS

    ifeq ($(LITTLE_FS_PROC),Y)
        MCAL_OPT += -DHAS_LITTLE_FS_PROC
    endif

    SOURCES_C += $(LITTLE_FS_DIR)/little_fs.c

    ifeq ($(DIAG),Y)
        ifeq ($(LITTLE_FS_DIAG),Y)
            MCAL_OPT += -DHAS_LITTLE_FS_DIAG
            SOURCES_C += $(LITTLE_FS_DIR)/little_fs_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LITTLE_FS_COMMANDS),Y)
            MCAL_OPT += -DHAS_LITTLE_FS_COMMANDS
            SOURCES_C += $(LITTLE_FS_DIR)/little_fs_commands.c
        endif
    endif
endif
