$(info DAC_CHANNEL_DRV_CUSTOM_MK_INC=$(DAC_DRV_CUSTOM_MK_INC) )
ifneq ($(DAC_CHANNEL_DRV_CUSTOM_MK_INC),Y)
    DAC_CHANNEL_DRV_CUSTOM_MK_INC=Y

    DAC_CHANNEL_CUSTOM_DIR = $(MCAL_STM32F4_DIR)/dac_channel
    # $(error DAC_CHANNEL_CUSTOM_DIR=$(DAC_CHANNEL_CUSTOM_DIR))
    MCAL_OPT += -DHAS_DAC_CHANNEL_CUSTOM

    INCDIR += -I$(DAC_CHANNEL_CUSTOM_DIR)

    SOURCES_C += $(DAC_CHANNEL_CUSTOM_DIR)/dac_channel_mcal.c

    ifeq ($(DAC_CHANNEL_INTERRUPT),Y)
        MCAL_OPT += -DHAS_DAC_CHANNEL_INTERRUPT
        SOURCES_C += $(DAC_CHANNEL_CUSTOM_DIR)/dac_channel_custom_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(DAC_CHANNEL_DIAG),Y)
            MCAL_OPT += -DHAS_DAC_CHANNEL_CUSTOM_DIAG
            SOURCES_DIAG_C += $(DAC_CHANNEL_CUSTOM_DIR)/dac_channel_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DAC_CHANNEL_COMMANDS),Y)
            MCAL_OPT += -DHAS_DAC_CHANNEL_CUSTOM_COMMANDS
            SOURCES_C += $(DAC_CHANNEL_CUSTOM_DIR)/dac_channel_custom_commands.c
        endif
    endif
endif