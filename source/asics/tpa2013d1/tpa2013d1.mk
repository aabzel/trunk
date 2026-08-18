ifneq ($(TPA2013D1_MK_INC),Y)
    TPA2013D1_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    TPA2013D1_DIR = $(ASICS_DIR)/tpa2013d1
    #@echo $(error TPA2013D1_DIR=$(TPA2013D1_DIR))

    INCDIR += -I$(TPA2013D1_DIR)

    MCAL_OPT += -DHAS_TPA2013D1

    SOURCES_C += $(TPA2013D1_DIR)/tpa2013d1_drv.c


    ifeq ($(DIAG),Y)
        ifeq ($(TPA2013D1_DIAG),Y)
            MCAL_OPT += -DHAS_TPA2013D1_DIAG
            SOURCES_C += $(TPA2013D1_DIR)/tpa2013d1_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(TPA2013D1_COMMANDS),Y)
            MCAL_OPT += -DHAS_TPA2013D1_COMMANDS
            SOURCES_C += $(TPA2013D1_DIR)/tpa2013d1_commands.c
        endif
    endif
endif
