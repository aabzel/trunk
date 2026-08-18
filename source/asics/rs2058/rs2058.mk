ifneq ($(RS2058_MK_INC),Y)
    RS2058_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    RS2058_DIR = $(ASICS_DIR)/rs2058
    #@echo $(error RS2058_DIR=$(RS2058_DIR))

    INCDIR += -I$(RS2058_DIR)

    MCAL_OPT += -DHAS_RS2058

    SOURCES_C += $(RS2058_DIR)/rs2058_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(RS2058_DIAG),Y)
            MCAL_OPT += -DHAS_RS2058_DIAG
            SOURCES_C += $(RS2058_DIR)/rs2058_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(RS2058_COMMANDS),Y)
            MCAL_OPT += -DHAS_RS2058_COMMANDS
            SOURCES_C += $(RS2058_DIR)/rs2058_commands.c
        endif
    endif
endif
