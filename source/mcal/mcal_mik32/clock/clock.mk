ifneq ($(CLOCK_MIK32_MK_INC),Y)
    CLOCK_MIK32_MK_INC=Y
    CLOCK_MIK32_DIR = $(MCAL_MIK32_DIR)/clock
    # $(error CLOCK_MIK32_DIR=$(CLOCK_MIK32_DIR))

    INCDIR += -I$(CLOCK_MIK32_DIR)

    OPT += -DHAS_CLOCK_CUSTOM

    SOURCES_C += $(CLOCK_MIK32_DIR)/clock.c

    ifeq ($(DIAG),Y)
        ifeq ($(CLOCK_DIAG),Y)
            OPT += -DHAS_CLOCK_DIAG
            SOURCES_C += $(CLOCK_MIK32_DIR)/clock_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_COMMANDS),Y)
            OPT += -DHAS_CLOCK_CUSTOM_COMMANDS
            SOURCES_C += $(CLOCK_MIK32_DIR)/clock_custom_commands.c
        endif
    endif
endif
