$(info GM67_MK_INC=$(GM67_MK_INC) )

ifneq ($(GM67_MK_INC),Y)
    GM67_MK_INC=Y

    GM67_DIR = $(ASICS_DIR)/gm67
    INCDIR += -I$(GM67_DIR)

    GM67=Y
    MCAL_OPT += -DHAS_GM67
    MCAL_OPT += -DHAS_GM67_PROC

    SOURCES_C += $(GM67_DIR)/gm67_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(GM67_DIAG),Y)
            MCAL_OPT += -DHAS_GM67_DIAG
            SOURCES_C += $(GM67_DIR)/gm67_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(GM67_COMMANDS),Y)
            #@echo $(error GM67_COMMANDS=$(GM67_COMMANDS))
            MCAL_OPT += -DHAS_GM67_COMMANDS
            SOURCES_C += $(GM67_DIR)/gm67_commands.c
        endif
    endif
endif
