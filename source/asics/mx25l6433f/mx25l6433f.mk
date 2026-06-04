ifneq ($(MX25L6433F_MK_INC),Y)
    MX25L6433F_MK_INC=Y

    MX25L6433F_DIR = $(ASICS_DIR)/mx25l6433f
    # $(error MX25L6433F_DIR=$(MX25L6433F_DIR))

    INCDIR += -I$(MX25L6433F_DIR)

    MCAL_OPT += -DHAS_MX25L6433F
    MCAL_OPT += -DHAS_SPI_FLASH
    MCAL_OPT += -DHAS_FLASH_OFF_CHIP
    MCAL_OPT += -DHAS_NOR_FLASH

    ifeq ($(MX25L6433F_PROC),Y)
        MCAL_OPT += -DHAS_MX25L6433F_PROC
    endif

    SOURCES_C += $(MX25L6433F_DIR)/mx25l6433f_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(MX25L6433F_DIAG),Y)
            MCAL_OPT += -DHAS_MX25L6433F_DIAG
            SOURCES_DIAG_C += $(MX25L6433F_DIR)/mx25l6433f_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MX25L6433F_COMMANDS),Y)
            MCAL_OPT += -DHAS_MX25L6433F_COMMANDS
            SOURCES_C += $(MX25L6433F_DIR)/mx25l6433f_commands.c
        endif
    endif
endif
