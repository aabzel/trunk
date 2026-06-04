ifneq ($(MX25R6435F_MK_INC),Y)
    MX25R6435F_MK_INC=Y

    MX25R6435F_DIR = $(ASICS_DIR)/mx25r6435f
     $(error MX25R6435F_DIR=$(MX25R6435F_DIR))

    INCDIR += -I$(MX25R6435F_DIR)

    MCAL_OPT += -DHAS_MX25R6435F
    MCAL_OPT += -DHAS_SPI_FLASH
    MCAL_OPT += -DHAS_FLASH_OFF_CHIP
    MCAL_OPT += -DHAS_NOR_FLASH

    SOURCES_C += $(MX25R6435F_DIR)/mx25r6435f_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(MX25R6435F_DIAG),Y)
            MCAL_OPT += -DHAS_MX25R6435F_DIAG
            SOURCES_C += $(MX25R6435F_DIR)/mx25r6435f_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MX25R6435F_COMMANDS),Y)
            MCAL_OPT += -DHAS_MX25R6435F_COMMANDS
            BIN_2_STR=Y
            SOURCES_C += $(MX25R6435F_DIR)/mx25r6435f_commands.c
        endif
    endif
endif
