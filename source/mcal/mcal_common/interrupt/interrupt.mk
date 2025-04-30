$(info INTERRUPT_GENERAL_DRV_MK_INC=$(INTERRUPT_GENERAL_DRV_MK_INC) )
ifneq ($(INTERRUPT_GENERAL_DRV_MK_INC),Y)
    INTERRUPT_GENERAL_DRV_MK_INC=Y


    INTERRUPT_MCAL_DIRR = $(MCAL_COMMON_DIR)/interrupt
    #@echo $(error INTERRUPT_MCAL_DIRR=$(INTERRUPT_MCAL_DIRR))

    INCDIR += -I$(INTERRUPT_MCAL_DIRR)
    OPT += -DHAS_INTERRUPT

    SOURCES_C += $(INTERRUPT_MCAL_DIRR)/interrupt_general.c

    ifeq ($(INTERRUPT_EXT),Y)
        OPT += -DHAS_INTERRUPT_EXT
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(INTERRUPT_DIAG),Y)
            OPT += -DHAS_INTERRUPT_DIAG
            SOURCES_C += $(INTERRUPT_MCAL_DIRR)/interrupt_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(INTERRUPT_COMMANDS),Y)
            OPT += -DHAS_INTERRUPT_COMMANDS
            SOURCES_C += $(INTERRUPT_MCAL_DIRR)/interrupt_commands.c
        endif
    endif
    
endif