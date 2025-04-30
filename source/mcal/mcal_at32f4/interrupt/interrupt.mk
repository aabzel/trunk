ifneq ($(INTERRUPT_DRV_MK_INC),Y)
    INTERRUPT_DRV_MK_INC=Y

    INTERRUPT_DIR = $(MCAL_AT32F4_DIR)/interrupt
    #@echo $(error INTERRUPT_DIR=$(INTERRUPT_DIR))

    INCDIR += -I$(INTERRUPT_DIR)
    OPT += -DHAS_INTERRUPT

    SOURCES_C += $(INTERRUPT_DIR)/interrupt_drv.c

    ifeq ($(INTERRUPT_DIAG),Y)
        #@echo $(error INTERRUPT_DIAG=$(INTERRUPT_DIAG))
        OPT += -DHAS_INTERRUPT_DIAG
        SOURCES_C += $(INTERRUPT_DIR)/interrupt_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(INTERRUPT_COMMANDS),Y)
            OPT += -DHAS_INTERRUPT_COMMANDS
            SOURCES_C += $(INTERRUPT_DIR)/interrupt_custom_commands.c
        endif
    endif
    
endif    