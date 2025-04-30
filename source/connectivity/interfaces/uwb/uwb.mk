ifneq ($(UWB_MK_INC),Y)
    UWB_MK_INC=Y

    UWB_DIR = $(INTERFACES_DIR)/uwb
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build $(mkfile_path) )
    $(info + UWB)

    INCDIR += -I$(UWB_DIR)
    #OPT += -DHAS_UWB_PROC
    OPT += -DHAS_UWB
    UWB_DIAG=Y
    SOURCES_C += $(UWB_DIR)/uwb_if.c

    ifeq ($(DIAG),Y)
        ifeq ($(UWB_DIAG),Y)
            $(info +UWB_DIAG)
            OPT += -DHAS_UWB_DIAG
             SOURCES_C += $(UWB_DIR)/uwb_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(UWB_COMMANDS),Y)
            #@echo $(error UWB_COMMANDS=$(UWB_COMMANDS))
            $(info +UWB_COMMANDS)
            OPT += -DHAS_UWB_COMMANDS
            #SOURCES_C += $(UWB_DIR)/uwb_commands.c
        endif
    endif
endif
