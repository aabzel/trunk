$(info BQ24079_MK_INC=$(BQ24079_MK_INC) )

ifneq ($(BQ24079_MK_INC),Y)
    BQ24079_MK_INC=Y
    BQ24079_DIR = $(ASICS_DIR)/bq24079
    #@echo $(error BQ24079_DIR=$(BQ24079_DIR))
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info + BQ24079)

    INCDIR += -I$(BQ24079_DIR)
    MCAL_OPT += -DHAS_BQ24079
    MCAL_OPT += -DHAS_BQ24079_PROC

    SOURCES_C += $(BQ24079_DIR)/bq24079_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(BQ24079_DIAG),Y)
            $(info Add BQ24079_DIAG)
            MCAL_OPT += -DHAS_BQ24079_DIAG
            SOURCES_C += $(BQ24079_DIR)/bq24079_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BQ24079_COMMANDS),Y)
            #@echo $(error BQ24079_COMMANDS=$(BQ24079_COMMANDS))
            $(info Add BQ24079_COMMANDS)
            MCAL_OPT += -DHAS_BQ24079_COMMANDS
            SOURCES_C += $(BQ24079_DIR)/bq24079_commands.c
        endif
    endif
endif
