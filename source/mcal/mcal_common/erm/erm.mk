$(info ERM_COMMON_MCAL_MK_INC=$(ERM_COMMON_MCAL_MK_INC) )

ifneq ($(ERM_COMMON_MCAL_MK_INC),Y)
    ERM_COMMON_MCAL_MK_INC=Y

    ERM_COMMON_MCAL_DIR = $(MCAL_COMMON_DIR)/erm
    # $(error ERM_COMMON_MCAL_DIR=$(ERM_COMMON_MCAL_DIR))

    INCDIR += -I$(ERM_COMMON_MCAL_DIR)
    MCAL_OPT += -DHAS_ERM
    MCAL_OPT += -DHAS_ERM_PROC

    SOURCES_C += $(ERM_COMMON_MCAL_DIR)/erm_general.c

    ifeq ($(ERM_INTERRUPT),Y)
        MCAL_OPT += -DHAS_ERM_INTERRUPT
        SOURCES_C += $(ERM_COMMON_MCAL_DIR)/erm_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(ERM_DIAG),Y)
            MCAL_OPT += -DHAS_ERM_DIAG
            SOURCES_C += $(ERM_COMMON_MCAL_DIR)/erm_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ERM_COMMANDS),Y)
            MCAL_OPT += -DHAS_ERM_COMMANDS
            SOURCES_C += $(ERM_COMMON_MCAL_DIR)/erm_commands.c
        endif
    endif    
endif