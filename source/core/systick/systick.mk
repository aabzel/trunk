ifneq ($(SYSTICK_CORTEX_M_MK_INC),Y)
    SYSTICK_CORTEX_M_MK_INC=Y

    SYSTICK_DIR = $(CORE_DIR)/systick
    # $(error SYSTICK_DIR=$(SYSTICK_DIR))
    INCDIR += -I$(SYSTICK_DIR)
    
    SYSTICK_INTERRUPT=Y
    MCAL_OPT += -DHAS_SYSTICK

    ifeq ($(SYSTICK_INTERRUPT),Y)
        MCAL_OPT += -DHAS_SYSTICK_INTERRUPT
        SOURCES_C += $(SYSTICK_DIR)/systick_isr.c
    endif

    SOURCES_C += $(SYSTICK_DIR)/systick_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(SYSTICK_DIAG),Y)
            # $(error SYSTICK_DIAG=$(SYSTICK_DIAG))
            MCAL_OPT += -DHAS_SYSTICK_DIAG
            SOURCES_C += $(SYSTICK_DIR)/systick_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        # $(error SYSTICK_COMMANDS=$(SYSTICK_COMMANDS))
        ifeq ($(SYSTICK_COMMANDS),Y)
            MCAL_OPT += -DHAS_SYSTICK_COMMANDS
            SOURCES_C += $(SYSTICK_DIR)/systick_commands.c
        endif
    endif
endif
