ifneq ($(SA51034_MK_INC),Y)
    SA51034_MK_INC=Y

    SA51034_DIR = $(ASICS_DIR)/sa51034
    #@echo $(error SA51034_DIR=$(SA51034_DIR))

    INCDIR += -I$(SA51034_DIR)

    OPT += -DHAS_SA51034
    OPT += -DHAS_SA51034_PROC

    SOURCES_C += $(SA51034_DIR)/sa51034_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(SA51034_DIAG),Y)
            OPT += -DHAS_SA51034_DIAG
            SOURCES_C += $(SA51034_DIR)/sa51034_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SA51034_COMMANDS),Y)
            OPT += -DHAS_SA51034_COMMANDS
            SOURCES_C += $(SA51034_DIR)/sa51034_commands.c
        endif
    endif
endif
