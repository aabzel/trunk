ifneq ($(MAX98357_MK_INC),Y)
    MAX98357_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    MAX98357_DIR = $(ASICS_DIR)/max98357
    #@echo $(error MAX98357_DIR=$(MAX98357_DIR))

    INCDIR += -I$(MAX98357_DIR)

    MCAL_OPT += -DHAS_MAX98357

    SOURCES_C += $(MAX98357_DIR)/max98357_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(MAX98357_DIAG),Y)
            MCAL_OPT += -DHAS_MAX98357_DIAG
            SOURCES_C += $(MAX98357_DIR)/max98357_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MAX98357_COMMANDS),Y)
            MCAL_OPT += -DHAS_MAX98357_COMMANDS
            BIN_2_STR=Y
            SOURCES_C += $(MAX98357_DIR)/max98357_commands.c
        endif
    endif
endif
