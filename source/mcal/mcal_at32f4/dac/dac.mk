ifneq ($(DAC_CUSTOM_MK_INC),Y)
    DAC_CUSTOM_MK_INC=Y

    DAC_CUSTMOM_DIR = $(MCAL_AT32F4_DIR)/dac
    #@echo $(error DAC_CUSTMOM_DIR=$(DAC_CUSTMOM_DIR))
    INCDIR += -I$(DAC_CUSTMOM_DIR)

    MCAL_OPT += -DHAS_DAC
    MCAL_OPT += -DHAS_DAC_TASKS

    SOURCES_C += $(DAC_CUSTMOM_DIR)/dac_mcal.c
    SOURCES_C += $(DAC_CUSTMOM_DIR)/dac_custom_isr.c

    ifeq ($(DAC1),Y)
        MCAL_OPT += -DHAS_DAC1
    endif

    ifeq ($(DAC2),Y)
        MCAL_OPT += -DHAS_DAC2
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(DAC_DIAG),Y)
            MCAL_OPT += -DHAS_DAC_CUSTOM_DIAG
            SOURCES_C += $(DAC_CUSTMOM_DIR)/dac_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DAC_COMMANDS),Y)
            MCAL_OPT += -DHAS_DAC_CUSTOM_COMMANDS
            SOURCES_C += $(DAC_CUSTMOM_DIR)/dac_custom_commands.c
        endif
    endif
endif