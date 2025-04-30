$(info STATISTICS_MK_INC=$(STATISTICS_MK_INC))

ifneq ($(STATISTICS_MK_INC),Y)
    STATISTICS_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    STATISTICS_DIR = $(COMPUTING_DIR)/statistics
    #@echo $(error STATISTICS_DIR = $(STATISTICS_DIR))

    OPT += -DHAS_STATISTICS
    INCDIR += -I$(STATISTICS_DIR)

    SOURCES_C += $(STATISTICS_DIR)/statistics.c

    ifeq ($(DIAG),Y)
        OPT += -DHAS_STATISTICS_DIAG
        SOURCES_C += $(STATISTICS_DIR)/statistics_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(STATISTICS_COMMANDS),Y)
            #@echo $(error STATISTICS_COMMANDS = $(STATISTICS_COMMANDS))
            OPT += -DHAS_STATISTICS_COMMANDS
            SOURCES_C += $(STATISTICS_DIR)/statistics_commands.c
        endif
    endif
endif
