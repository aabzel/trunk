ifneq ($(CLOCK_STM32_MK_INC),Y)
    CLOCK_STM32_MK_INC=Y
    #@echo $(error CLOCK=$(CLOCK))
    #mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    #$(info Build  $(mkfile_path) )
    CLOCK_STM32_DIR = $(MCAL_STM32F4_DIR)/clocks
    #@echo $(error CLOCK_STM32_DIR=$(CLOCK_STM32_DIR))

    INCDIR += -I$(CLOCK_STM32_DIR)

    OPT += -DHAS_CLOCK_CUSTOM

    SOURCES_C += $(CLOCK_STM32_DIR)/clocks.c

    ifeq ($(DIAG),Y)
        ifeq ($(CLOCK_DIAG),Y)
            OPT += -DHAS_CLOCK_DIAG
            SOURCES_C += $(CLOCK_STM32_DIR)/clock_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_COMMANDS),Y)
            OPT += -DHAS_CLOCK_CUSTOM_COMMANDS
            SOURCES_C += $(CLOCK_STM32_DIR)/clock_custom_commands.c
        endif
    endif
endif
