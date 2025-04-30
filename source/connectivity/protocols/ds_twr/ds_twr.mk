ifneq ($(DS_TWR_MK_INC),Y)
    DS_TWR_MK_INC=Y

    DS_TWR_DIR = $(PROTOCOLS_DIR)/ds_twr
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build $(mkfile_path))
    $(info + DWM1000 Range)

    INCDIR += -I$(DS_TWR_DIR)

    OPT += -DHAS_DS_TWR
    OPT += -DHAS_DS_TWR_PROC

    SOURCES_C += $(DS_TWR_DIR)/ds_twr.c
    SOURCES_C += $(DS_TWR_DIR)/ds_twr_initiator.c
    SOURCES_C += $(DS_TWR_DIR)/ds_twr_responder.c
    #SOURCES_C += $(DS_TWR_DIR)/ds_twr_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(DS_TWR_DIAG),Y)
            OPT += -DHAS_DS_TWR_DIAG
            SOURCES_C += $(DS_TWR_DIR)/ds_twr_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DS_TWR_COMMANDS),Y)
            $(info +DS_TWR_COMMANDS)
            OPT += -DHAS_DS_TWR_COMMANDS
            SOURCES_C += $(DS_TWR_DIR)/ds_twr_commands.c
        endif
    endif
endif
