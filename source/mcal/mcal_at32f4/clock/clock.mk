ifneq ($(CLOCK_AT32_MK_INC),Y)
    CLOCK_AT32_MK_INC=Y
    #@echo $(error CLOCK=$(CLOCK))
    #mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    #$(info Build  $(mkfile_path) )
    CLOCK_AT32_DIR = $(MCAL_AT32F4_DIR)/clock
    #@echo $(error CLOCK_AT32_DIR=$(CLOCK_AT32_DIR))

    INCDIR += -I$(CLOCK_AT32_DIR)

    OPT += -DHAS_CLOCK_CUSTOM
    #PLL_CALC=Y
    SOURCES_C += $(CLOCK_AT32_DIR)/clock.c

    ifeq ($(DIAG),Y)
        ifeq ($(CLOCK_DIAG),Y)
            OPT += -DHAS_CLOCK_DIAG
            SOURCES_C += $(CLOCK_AT32_DIR)/clock_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_COMMANDS),Y)
            OPT += -DHAS_CLOCK_CUSTOM_COMMANDS
            SOURCES_C += $(CLOCK_AT32_DIR)/clock_custom_commands.c
        endif
    endif
endif
