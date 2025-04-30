$(info DAC_COMMON_MCAL_MK_INC=$(DAC_COMMON_MCAL_MK_INC) )

ifneq ($(DAC_COMMON_MCAL_MK_INC),Y)
    DAC_COMMON_MCAL_MK_INC=Y

    DAC_COMMON_MCAL_DIR = $(MCAL_COMMON_DIR)/dac
    #@echo $(error DAC_COMMON_MCAL_DIR=$(DAC_COMMON_MCAL_DIR))

    INCDIR += -I$(DAC_COMMON_MCAL_DIR)

    SOURCES_C += $(DAC_COMMON_MCAL_DIR)/dac_general.c

    ifeq ($(DAC_ISR),Y)
        OPT += -DHAS_DAC_ISR
        SOURCES_C += $(DAC_COMMON_MCAL_DIR)/dac_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(DAC_DIAG),Y)
            OPT += -DHAS_DAC_DIAG
            SOURCES_C += $(DAC_COMMON_MCAL_DIR)/dac_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DAC_COMMANDS),Y)
            OPT += -DHAS_DAC_COMMANDS
            SOURCES_C += $(DAC_COMMON_MCAL_DIR)/dac_commands.c
        endif
    endif    
endif