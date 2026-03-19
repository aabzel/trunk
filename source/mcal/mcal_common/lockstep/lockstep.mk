$(info LOCKSTEP_COMMON_MCAL_MK_INC=$(LOCKSTEP_COMMON_MCAL_MK_INC) )

ifneq ($(LOCKSTEP_COMMON_MCAL_MK_INC),Y)
    LOCKSTEP_COMMON_MCAL_MK_INC=Y

    LOCKSTEP_COMMON_MCAL_DIR = $(MCAL_COMMON_DIR)/lockstep
    #@echo $(error LOCKSTEP_COMMON_MCAL_DIR=$(LOCKSTEP_COMMON_MCAL_DIR))

    INCDIR += -I$(LOCKSTEP_COMMON_MCAL_DIR)
    MCAL_OPT += -DHAS_LOCKSTEP
    MCAL_OPT += -DHAS_LOCKSTEP_PROC
    
    LOCKSTEP_INTERRUPT=Y
    
    SOURCES_C += $(LOCKSTEP_COMMON_MCAL_DIR)/lockstep_general.c

    ifeq ($(LOCKSTEP_INTERRUPT),Y)
        MCAL_OPT += -DHAS_LOCKSTEP_ISR
        SOURCES_C += $(LOCKSTEP_COMMON_MCAL_DIR)/lockstep_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(LOCKSTEP_DIAG),Y)
            MCAL_OPT += -DHAS_LOCKSTEP_DIAG
            SOURCES_C += $(LOCKSTEP_COMMON_MCAL_DIR)/lockstep_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LOCKSTEP_COMMANDS),Y)
            MCAL_OPT += -DHAS_LOCKSTEP_COMMANDS
            SOURCES_C += $(LOCKSTEP_COMMON_MCAL_DIR)/lockstep_commands.c
        endif
    endif    
endif