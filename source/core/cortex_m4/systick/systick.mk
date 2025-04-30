ifneq ($(SYSTICK_CORTEX_M4_MK_INC),Y)
    SYSTICK_CORTEX_M4_MK_INC=Y

    SYSTICK_DIR = $(CORTEX_M4_DIR)/systick
    #@echo $(error SYSTICK_DIR=$(SYSTICK_DIR))

    INCDIR += -I$(SYSTICK_DIR)
    OPT += -DHAS_SYSTICK
    OPT += -DHAS_SYSTICK_INT
    OPT += -DHAS_SYSTICK_ISR

    SOURCES_C += $(SYSTICK_DIR)/systick_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(SYSTICK_DIAG),Y)
            #@echo $(error SYSTICK_DIAG=$(SYSTICK_DIAG))
            OPT += -DHAS_SYSTICK_DIAG
            SOURCES_C += $(SYSTICK_DIR)/systick_general_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        #@echo $(error SYSTICK_COMMANDS=$(SYSTICK_COMMANDS))
        ifeq ($(SYSTICK_COMMANDS),Y)
            OPT += -DHAS_SYSTICK_COMMANDS
            SOURCES_C += $(SYSTICK_DIR)/systick_commands.c
        endif
    endif
endif
