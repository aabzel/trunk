ifneq ($(W25Q32JV_MK_INC),Y)
    W25Q32JV_MK_INC=Y

    W25Q32JV_DIR = $(ASICS_DIR)/w25q32jv
    #@echo $(error W25Q32JV_DIR=$(W25Q32JV_DIR))

    INCDIR += -I$(W25Q32JV_DIR)

    OPT += -DHAS_W25Q32JV
    OPT += -DHAS_SPI_FLASH
    OPT += -DHAS_FLASH_OFF_CHIP
    OPT += -DHAS_NOR_FLASH
    OPT += -DHAS_W25Q32JV_INIT

    SOURCES_C += $(W25Q32JV_DIR)/w25q32jv_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(W25Q32JV_DIAG),Y)
            OPT += -DHAS_W25Q32JV_DIAG
            SOURCES_C += $(W25Q32JV_DIR)/w25q32jv_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(W25Q32JV_COMMANDS),Y)
            OPT += -DHAS_W25Q32JV_COMMANDS
            SOURCES_C += $(W25Q32JV_DIR)/w25q32jv_commands.c
        endif
    endif
endif
