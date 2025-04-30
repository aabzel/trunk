$(info AT24CXX_MK_INC=$(AT24CXX_MK_INC) )

ifneq ($(AT24CXX_MK_INC),Y)
    AT24CXX_MK_INC=Y

    AT24CXX_DIR = $(ASICS_DIR)/at24cxx
    #@echo $(error AT24CXX_DIR=$(AT24CXX_DIR))
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    INCDIR += -I$(AT24CXX_DIR)
    OPT += -DHAS_AT24C02

    AT24CXX=Y
    I2C=Y
    OPT += -DHAS_AT24CXX
    OPT += -DHAS_AT24CXX_PROC

    SOURCES_C += $(AT24CXX_DIR)/at24cxx_drv.c
    SOURCES_C += $(AT24CXX_DIR)/at24cxx_read_drv.c

    ifeq ($(AT24CXX_WRITE),Y)
        #@echo $(error AT24CXX_WRITE=$(AT24CXX_WRITE))
        OPT += -DHAS_AT24CXX_WRITE
        SOURCES_C += $(AT24CXX_DIR)/at24cxx_write_drv.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(AT24CXX_DIAG),Y)
            OPT += -DHAS_AT24CXX_DIAG
            SOURCES_C += $(AT24CXX_DIR)/at24cxx_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(AT24CXX_COMMANDS),Y)
            #@echo $(error AT24CXX_COMMANDS=$(AT24CXX_COMMANDS))
            OPT += -DHAS_AT24CXX_COMMANDS
            SOURCES_C += $(AT24CXX_DIR)/at24cxx_commands.c
        endif
    endif
endif
