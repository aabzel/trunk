ifneq ($(DAC_CHANNEL_GENERAL_MK_INC),Y)
    DAC_CHANNEL_GENERAL_MK_INC=Y

    DAC_CHANNEL_MCAL_DIR = $(MCAL_COMMON_DIR)/dac_channel
    # $(error DAC_MCAL_DIR=$(DAC_MCAL_DIR))

    INCDIR += -I$(DAC_CHANNEL_MCAL_DIR)
    MCAL_OPT += -DHAS_DAC_CHANNEL
    MCAL_OPT += -DHAS_DAC_CHANNEL_PROC

    SOURCES_C += $(DAC_CHANNEL_MCAL_DIR)/dac_channel_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(DAC_DIAG),Y)
            MCAL_OPT += -DHAS_DAC_CHANNEL_DIAG
            SOURCES_DIAG_C += $(DAC_MCAL_DIR)/dac_channel_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DAC_CHANNEL_COMMANDS),Y)
            # $(error DAC_COMMANDS=$(DAC_COMMANDS))
            $(info Add DAC commands)
            MCAL_OPT += -DHAS_DAC_CHANNEL_COMMANDS
            SOURCES_C += $(DAC_MCAL_DIR)/dac_channel_commands.c
        endif
    endif
endif