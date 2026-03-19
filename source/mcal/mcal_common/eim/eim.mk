$(info EIM_MCAL_MK_INC=  $(EIM_MCAL_MK_INC) )

ifneq ($(EIM_MCAL_MK_INC),Y)
    EIM_MCAL_MK_INC=Y

    EIM_MCAL_DIR = $(MCAL_COMMON_DIR)/eim
    # $(error EIM_MCAL_DIR=$(EIM_MCAL_DIR))

    INCDIR += -I$(EIM_MCAL_DIR)
    MCAL_OPT += -DHAS_EIM
    MCAL_OPT += -DHAS_EIM_PROC

    ifeq ($(EIM_ISR),Y)
        MCAL_OPT += -DHAS_EIM_ISR
        SOURCES_C += $(EIM_MCAL_DIR)/eim_isr.c
    endif

    SOURCES_C += $(EIM_MCAL_DIR)/eim_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(EIM_DIAG),Y)
            MCAL_OPT += -DHAS_EIM_DIAG
            SOURCES_C += $(EIM_MCAL_DIR)/eim_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(EIM_COMMANDS),Y)
            MCAL_OPT += -DHAS_EIM_COMMANDS
            SOURCES_C += $(EIM_MCAL_DIR)/eim_commands.c
        endif
    endif
endif