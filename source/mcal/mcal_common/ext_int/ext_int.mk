$(info EXT_INT_COMMON_MCAL_MK_INC=$(EXT_INT_COMMON_MCAL_MK_INC) )

ifneq ($(EXT_INT_COMMON_MCAL_MK_INC),Y)
    EXT_INT_COMMON_MCAL_MK_INC=Y

    EXT_INT_COMMON_MCAL_DIR = $(MCAL_COMMON_DIR)/ext_int
    # $(error EXT_INT_COMMON_MCAL_DIR=$(EXT_INT_COMMON_MCAL_DIR))

    INCDIR += -I$(EXT_INT_COMMON_MCAL_DIR)

    SOURCES_C += $(EXT_INT_COMMON_MCAL_DIR)/ext_int_general.c
    MCAL_OPT += -DHAS_EXT_INT
    MCAL_OPT += -DHAS_EXT_INT_PROC

    MCAL_OPT += -DHAS_EXT_INT_ISR
    SOURCES_C += $(EXT_INT_COMMON_MCAL_DIR)/ext_int_isr.c
    ifeq ($(EXT_INT_ISR),Y)
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(EXT_INT_DIAG),Y)
            MCAL_OPT += -DHAS_EXT_INT_DIAG
            SOURCES_C += $(EXT_INT_COMMON_MCAL_DIR)/ext_int_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(EXT_INT_COMMANDS),Y)
            MCAL_OPT += -DHAS_EXT_INT_COMMANDS
            SOURCES_C += $(EXT_INT_COMMON_MCAL_DIR)/ext_int_commands.c
        endif
    endif    
endif