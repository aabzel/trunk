
$(info DELTA_SIGMA_MK_INC=$(DELTA_SIGMA_MK_INC))

ifneq ($(DELTA_SIGMA_MK_INC),Y)
    DELTA_SIGMA_MK_INC=Y

    DELTA_SIGMA_DIR = $(COMPUTING_DIR)/delta_sigma
    #@echo $(error DELTA_SIGMA_DIR = $(DELTA_SIGMA_DIR))

    OPT += -DHAS_DELTA_SIGMA
    OPT += -DHAS_DELTA_SIGMA_PROC

    INCDIR += -I$(DELTA_SIGMA_DIR)

    SOURCES_C += $(DELTA_SIGMA_DIR)/delta_sigma.c


    ifeq ($(DIAG),Y)
        ifeq ($(DELTA_SIGMA_DIAG),Y)
            OPT += -DHAS_DELTA_SIGMA_DIAG
            SOURCES_C += $(DELTA_SIGMA_DIR)/delta_sigma_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DELTA_SIGMA_COMMANDS),Y)
            #@echo $(error DELTA_SIGMA_COMMANDS = $(DELTA_SIGMA_COMMANDS))
            OPT += -DHAS_DELTA_SIGMA_COMMANDS
            SOURCES_C += $(DELTA_SIGMA_DIR)/delta_sigma_commands.c
        endif
    endif
endif
