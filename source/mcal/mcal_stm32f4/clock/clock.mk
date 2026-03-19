ifneq ($(CLOCK_CUSTOM_MK_INC),Y)
    CLOCK_CUSTOM_MK_INC=Y
    # $(error CLOCK=$(CLOCK))
 
    CLOCK_CUSTOM_DIR = $(MCAL_STM32F4_DIR)/clock
    # $(error CLOCK_CUSTOM_DIR=$(CLOCK_CUSTOM_DIR))

    INCDIR += -I$(CLOCK_CUSTOM_DIR)

    MCAL_OPT += -DHAS_CLOCK_CUSTOM

    SOURCES_C += $(CLOCK_CUSTOM_DIR)/clock_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(CLOCK_DIAG),Y)
            MCAL_OPT += -DHAS_CLOCK_DIAG
            SOURCES_C += $(CLOCK_CUSTOM_DIR)/clock_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_COMMANDS),Y)
            MCAL_OPT += -DHAS_CLOCK_CUSTOM_COMMANDS
            SOURCES_C += $(CLOCK_CUSTOM_DIR)/clock_custom_commands.c
        endif
    endif
endif
