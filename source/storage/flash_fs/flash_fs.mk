ifneq ($(FLASH_FS_MK_INC),Y)
    FLASH_FS_MK_INC=Y

    FLASH_FS_DIR = $(STORAGE_DIR)/flash_fs
    #@ echo $(error FLASH_FS_DIR = $(FLASH_FS_DIR))
    #@ echo $(error CFLAGS = $(CFLAGS)) 
    OPT += -DHAS_FLASH_FS
    OPT += -DHAS_FLASH_FS_PROC

    INCDIR += -I$(FLASH_FS_DIR)

    CRC=Y
    CRC8=Y

    SOURCES_C += $(FLASH_FS_DIR)/flash_fs.c
    SOURCES_C += $(FLASH_FS_DIR)/flash_fs_ll.c

    ifeq ($(DIAG),Y)
        ifeq ($(FLASH_FS_DIAG),Y)
            OPT += -DHAS_FLASH_FS_DIAG
            SOURCES_C += $(FLASH_FS_DIR)/flash_fs_diag.c
        endif
    endif

    ifeq ($(FLASH_FS_WRITE),Y)
        #@echo $(error FLASH_FS_WRITE = $(FLASH_FS_WRITE)) 
        OPT += -DHAS_FLASH_FS_WRITE
    endif

    ifeq ($(CLI),Y)
        ifeq ($(FLASH_FS_COMMANDS),Y)
            OPT += -DHAS_FLASH_FS_EXT_COMMANDS
            OPT += -DHAS_FLASH_FS_COMMANDS
            SOURCES_C += $(FLASH_FS_DIR)/flash_fs_commands.c
        endif
    endif
endif


