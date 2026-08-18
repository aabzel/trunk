ifneq ($(FDA801_MK_INC),Y)
    FDA801_MK_INC=Y


    FDA801_DIR = $(ASICS_DIR)/fda801
    #@echo $(error FDA801_DIR=$(FDA801_DIR))

    INCDIR += -I$(FDA801_DIR)

    MCAL_OPT += -DHAS_FDA801

    SOURCES_C += $(FDA801_DIR)/fda801_drv.c


    ifeq ($(DIAG),Y)
        ifeq ($(FDA801_DIAG),Y)
            MCAL_OPT += -DHAS_FDA801_DIAG
            SOURCES_C += $(FDA801_DIR)/fda801_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(FDA801_COMMANDS),Y)
            MCAL_OPT += -DHAS_FDA801_COMMANDS
            BIN_2_STR=Y
            SOURCES_C += $(FDA801_DIR)/fda801_commands.c
        endif
    endif
endif
