ifneq ($(MIC2026_MK_INC),Y)
    MIC2026_MK_INC=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    MIC2026_DIR = $(ASICS_DIR)/mic2026
    INCDIR += -I$(MIC2026_DIR)
    #@ echo $(error MIC2026_DIR = $(MIC2026_DIR))
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    SOURCES_C += $(MIC2026_DIR)/mic2026_drv.c
    MCAL_OPT += -DHAS_MIC2026

    ifeq ($(DIAG),Y)
        ifeq ($(MIC2026_DIAG),Y)
            MCAL_OPT += -DHAS_MIC2026_DIAG
            SOURCES_C += $(MIC2026_DIR)/mic2026_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MIC2026_COMMANDS),Y)
            MCAL_OPT += -DHAS_MIC2026_COMMANDS
            SOURCES_C += $(MIC2026_DIR)/mic2026_commands.c
        endif
    endif
endif