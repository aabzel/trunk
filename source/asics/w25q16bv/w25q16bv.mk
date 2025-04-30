ifneq ($(W25Q16BV_MK_INC),Y)
    W25Q16BV_MK_INC=Y

    W25Q16BV_DIR = $(ASICS_DIR)/w25q16bv
    # $(error W25Q16BV_DIR=$(W25Q16BV_DIR))

    INCDIR += -I$(W25Q16BV_DIR)

    OPT += -DHAS_W25Q16BV

    SOURCES_C += $(W25Q16BV_DIR)/w25q16bv_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(W25Q16BV_DIAG),Y)
            OPT += -DHAS_W25Q16BV_DIAG
            SOURCES_C += $(W25Q16BV_DIR)/w25q16bv_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(W25Q16BV_COMMANDS),Y)
            OPT += -DHAS_W25Q16BV_COMMANDS
            BIN_2_STR=Y
            SOURCES_C += $(W25Q16BV_DIR)/w25q16bv_commands.c
        endif
    endif
endif
