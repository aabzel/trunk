ifneq ($(NOR_FLASH_MK_INC),Y)
    NOR_FLASH_MK_INC=Y


    NOR_FLASH_DIR = $(STORAGE_DIR)/nor_flash
    #@echo $(error NOR_FLASH_DIR=$(NOR_FLASH_DIR))

    INCDIR += -I$(NOR_FLASH_DIR)

    OPT += -DHAS_NOR_FLASH

    SOURCES_C += $(NOR_FLASH_DIR)/nor_flash_drv.c
    SOURCES_C += $(NOR_FLASH_DIR)/nor_flash_api.c

    ifeq ($(DIAG),Y)
        ifeq ($(NOR_FLASH_DIAG),Y)
            OPT += -DHAS_NOR_FLASH_DIAG
            SOURCES_C += $(NOR_FLASH_DIR)/nor_flash_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NOR_FLASH_COMMANDS),Y)
            OPT += -DHAS_NOR_FLASH_COMMANDS
            BIN_2_STR=Y
            SOURCES_C += $(NOR_FLASH_DIR)/nor_flash_commands.c
        endif
    endif
endif
