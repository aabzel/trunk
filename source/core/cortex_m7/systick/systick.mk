ifneq ($(SYSTICK_CORTEX_M7_MK_INC),Y)
    SYSTICK_CORTEX_M7_MK_INC=Y

    SYSTICK_DIR = $(CORTEX_M7_DIR)/systick
    #@echo $(error SYSTICK_DIR=$(SYSTICK_DIR))
    INCDIR += -I$(SYSTICK_DIR)
    MCAL_OPT += -DHAS_SYSTICK
    MCAL_OPT += -DHAS_SYSTICK_INT

    SOURCES_C += $(SYSTICK_DIR)/systick_general.c

    ifeq ($(SYSTICK_DIAG),Y)
        SOURCES_C += $(SYSTICK_DIR)/systick_diag.c
    endif

    ifeq ($(CLI),Y)
        #@echo $(error SYSTICK_COMMANDS=$(SYSTICK_COMMANDS))
        ifeq ($(SYSTICK_COMMANDS),Y)
            MCAL_OPT += -DHAS_SYSTICK_COMMANDS
            SOURCES_C += $(SYSTICK_DIR)/systick_commands.c
        endif
    endif
endif
