ifneq ($(SYSTICK_GENERAL_MK_INC),Y)
    SYSTICK_GENERAL_MK_INC=Y

    $(info Build  $(mkfile_path) )

    SYSTICK_DIR = $(CORTEX_M33_DIR)/systick
    #@echo $(error SYSTICK_DIR=$(SYSTICK_DIR))
    INCDIR += -I$(SYSTICK_DIR)
    OPT += -DHAS_SYSTICK
    OPT += -DHAS_SYSTIC_INT
    OPT += -DHAS_SYSTICK_ISR

    SOURCES_C += $(SYSTICK_DIR)/systick_config.c
    SOURCES_C += $(SYSTICK_DIR)/systick_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(SYSTICK_DIAG),Y)
            #@echo $(error SYSTICK_DIAG=$(SYSTICK_DIAG))
            OPT += -DHAS_SYSTICK_DIAG
            SOURCES_C += $(SYSTICK_DIR)/systick_general_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        #@echo $(error CLI=$(CLI))
        ifeq ($(SYSTICK_COMMANDS),Y)
            OPT += -DHAS_SYSTICK_COMMANDS
            SOURCES_C += $(SYSTICK_DIR)/systick_commands.c
        endif
    endif
endif