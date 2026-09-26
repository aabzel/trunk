ifneq ($(MULTICORE_CUSTOM_MK_INC),Y)
    MULTICORE_CUSTOM_MK_INC=Y

    MULTICORE_CUSTMOM_DIR = $(MCAL_X86_DIR)/multicore
    #@echo $(error MULTICORE_CUSTMOM_DIR=$(MULTICORE_CUSTMOM_DIR))
    INCDIR += -I$(MULTICORE_CUSTMOM_DIR)

    MCAL_OPT += -DHAS_MULTICORE_CUSTOM

    SOURCES_C += $(MULTICORE_CUSTMOM_DIR)/multicore_mcal.c
    SOURCES_C += $(MULTICORE_CUSTMOM_DIR)/multicore_custom_isr.c
    
    ifeq ($(DIAG),Y)
        ifeq ($(MULTICORE_DIAG),Y)
            MCAL_OPT += -DHAS_MULTICORE_CUSTOM_DIAG
            SOURCES_C += $(MULTICORE_CUSTMOM_DIR)/multicore_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MULTICORE_COMMANDS),Y)
            MCAL_OPT += -DHAS_MULTICORE_CUSTOM_COMMANDS
            SOURCES_C += $(MULTICORE_CUSTMOM_DIR)/multicore_custom_commands.c
        endif
    endif
endif