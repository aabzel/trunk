ifneq ($(SW_NOR_FLASH_MK_INC),Y)
    SW_NOR_FLASH_MK_INC=Y

    SW_NOR_FLASH_DIR = $(STORAGE_DIR)/sw_nor_flash
    # $(error SW_NOR_FLASH_DIR=$(SW_NOR_FLASH_DIR))

    INCDIR += -I$(SW_NOR_FLASH_DIR)

    MCAL_OPT += -DHAS_SW_NOR_FLASH
    MCAL_OPT += -DHAS_NOR_FLASH_SW

    ifeq ($(SW_NOR_FLASH_PROC),Y)
        MCAL_OPT += -DHAS_SW_NOR_FLASH_PROC
    endif

    SOURCES_C += $(SW_NOR_FLASH_DIR)/sw_nor_flash.c

    ifeq ($(DIAG),Y)
        ifeq ($(SW_NOR_FLASH_DIAG),Y)
            MCAL_OPT += -DHAS_SW_NOR_FLASH_DIAG
            SOURCES_C += $(SW_NOR_FLASH_DIR)/sw_nor_flash_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SW_NOR_FLASH_COMMANDS),Y)
            MCAL_OPT += -DHAS_SW_NOR_FLASH_COMMANDS
            SOURCES_C += $(SW_NOR_FLASH_DIR)/sw_nor_flash_commands.c
        endif
    endif
endif
