$(info DAC_DRV_CUSTOM_MK_INC=$(DAC_DRV_CUSTOM_MK_INC) )
ifneq ($(DAC_DRV_CUSTOM_MK_INC),Y)
    DAC_DRV_CUSTOM_MK_INC=Y

    DAC_CUSTOM_DIR = $(MCAL_CUSTOM_DIR)/dac
    # $(error DAC_CUSTOM_DIR=$(DAC_CUSTOM_DIR))
    MCAL_OPT += -DHAS_DAC_CUSTOM
    MCAL_OPT += -DHAS_DAC

    INCDIR += -I$(DAC_CUSTOM_DIR)

    SOURCES_C += $(DAC_CUSTOM_DIR)/dac_mcal.c

    ifeq ($(DAC1),Y)
        MCAL_OPT += -DHAS_DAC1
    endif

    ifeq ($(DAC2),Y)
        MCAL_OPT += -DHAS_DAC2
    endif

    ifeq ($(DAC_INTERRUPT),Y)
        MCAL_OPT += -DHAS_DAC_INTERRUPT
        SOURCES_C += $(DAC_CUSTOM_DIR)/dac_custom_isr.c
    endif
    
    ifeq ($(DIAG),Y)
        ifeq ($(DAC_DIAG),Y)
            MCAL_OPT += -DHAS_DAC_CUSTOM_DIAG
            SOURCES_DIAG_C += $(DAC_CUSTOM_DIR)/dac_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DAC_COMMANDS),Y)
            MCAL_OPT += -DHAS_DAC_CUSTOM_COMMANDS
            SOURCES_C += $(DAC_CUSTOM_DIR)/dac_custom_commands.c
        endif
    endif
endif