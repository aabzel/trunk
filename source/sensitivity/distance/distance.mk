$(info DISTANCE_MK_INC=$(DISTANCE_MK_INC))

ifneq ($(DISTANCE_MK_INC),Y)
    DISTANCE_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    DISTANCE_DIR = $(SENSITIVITY_DIR)/distance
    #@echo $(error DISTANCE_DIR = $(DISTANCE_DIR))

    OPT += -DHAS_DISTANCE
    OPT += -DHAS_DISTANCE_PROC

    INCDIR += -I$(DISTANCE_DIR)

    SOURCES_C += $(DISTANCE_DIR)/distance_drv.c

    ifeq ($(DISTANCE_DIAG),Y)
        OPT += -DHAS_DISTANCE_DIAG
        SOURCES_C += $(DISTANCE_DIR)/distance_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DISTANCE_COMMANDS),Y)
            #@echo $(error DISTANCE_COMMANDS = $(DISTANCE_COMMANDS))
            OPT += -DHAS_DISTANCE_COMMANDS
            SOURCES_C += $(DISTANCE_DIR)/distance_commands.c
        endif
    endif
endif
