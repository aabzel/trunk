ifneq ($(STORE_FS_MK_INC),Y)
    STORE_FS_MK_INC=Y

    STORE_FS_DIR = $(STORAGE_DIR)/store_fs
    # $(error STORE_FS_DIR=$(STORE_FS_DIR))

    INCDIR += -I$(STORE_FS_DIR)

    MCAL_OPT += -DHAS_STORE_FS

    ifeq ($(STORE_FS_PROC),Y)
        MCAL_OPT += -DHAS_STORE_FS_PROC
    endif

    SOURCES_C += $(STORE_FS_DIR)/store_fs.c

    ifeq ($(STORE_FS_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_STORE_FS_INTERRUPTS
        SOURCES_C += $(STORE_FS_DIR)/store_fs_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(STORE_FS_DIAG),Y)
            MCAL_OPT += -DHAS_STORE_FS_DIAG
            SOURCES_C += $(STORE_FS_DIR)/store_fs_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(STORE_FS_COMMANDS),Y)
            MCAL_OPT += -DHAS_STORE_FS_COMMANDS
            SOURCES_C += $(STORE_FS_DIR)/store_fs_commands.c
        endif
    endif
endif
