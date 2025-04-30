$(info EXT_INT_CUSTOM_MK_INC=$(EXT_INT_CUSTOM_MK_INC) )

ifneq ($(EXT_INT_CUSTOM_MK_INC),Y)
    EXT_INT_CUSTOM_MK_INC=Y

    EXT_INT_CUSTOM_DIR = $(MCAL_AT32F4_DIR)/ext_int
    #@echo $(error EXT_INT_CUSTOM_DIR=$(EXT_INT_CUSTOM_DIR))

    INCDIR += -I$(EXT_INT_CUSTOM_DIR)

    SOURCES_C += $(EXT_INT_CUSTOM_DIR)/ext_int_mcal.c
    OPT += -DHAS_EXT_INT
    
    EXT_INT_ISR=Y
    
    ifeq ($(EXT_INT_ISR),Y)
        $(info + EXT_INT ISR)
        OPT += -DHAS_EXT_INT_ISR
        SOURCES_C += $(EXT_INT_CUSTOM_DIR)/ext_int_custom_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(EXT_INT_DIAG),Y)
            OPT += -DHAS_EXT_INT_DIAG
            SOURCES_C += $(EXT_INT_CUSTOM_DIR)/ext_int_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(EXT_INT_COMMANDS),Y)
            OPT += -DHAS_EXT_INT_COMMANDS
            SOURCES_C += $(EXT_INT_CUSTOM_DIR)/ext_int_custom_commands.c
        endif
    endif
endif