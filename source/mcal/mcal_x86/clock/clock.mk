ifneq ($(CLOCK_X86_MK_INC),Y)
    CLOCK_X86_MK_INC=Y
    CLOCK_X86_DIR = $(MCAL_X86_DIR)/clock
    # $(error CLOCK_X86_DIR=$(CLOCK_X86_DIR))

    INCDIR += -I$(CLOCK_X86_DIR)

    MCAL_OPT += -DHAS_CLOCK_CUSTOM

    #PLL_CALC=Y
    SOURCES_C += $(CLOCK_X86_DIR)/clock_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(CLOCK_DIAG),Y)
            MCAL_OPT += -DHAS_CLOCK_DIAG
            SOURCES_C += $(CLOCK_X86_DIR)/clock_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_COMMANDS),Y)
            MCAL_OPT += -DHAS_CLOCK_CUSTOM_COMMANDS
            SOURCES_C += $(CLOCK_X86_DIR)/clock_custom_commands.c
        endif
    endif
endif
