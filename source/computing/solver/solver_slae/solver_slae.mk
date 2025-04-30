$(info SOLVER_SLAE_MK_INC=$(SOLVER_SLAE_MK_INC))
ifneq ($(SOLVER_SLAE_MK_INC),Y)
    SOLVER_SLAE_MK_INC=Y

    SOLVER_SLAE_DIR = $(SOLVER_DIR)/solver_slae
    #@echo $(error SOLVER_SLAE_DIR= $(SOLVER_SLAE_DIR))
    INCDIR += -I$(SOLVER_SLAE_DIR)

    OPT += -DHAS_SOLVER_SLAE
    SOURCES_C += $(SOLVER_SLAE_DIR)/solver_slae.c

    ifeq ($(SOLVER_SLAE_DIAG),Y)
        #@echo $(error SOLVER_SLAE_DIAG= $(SOLVER_SLAE_DIAG))
        OPT += -DHAS_SOLVER_SLAE_DIAG
        SOURCES_C += $(SOLVER_SLAE_DIR)/solver_slae_diag.c
    endif

    ifeq ($(SOLVER_SLAE_COMMANDS),Y)
        #@echo $(error SOLVER_SLAE_COMMANDS= $(SOLVER_SLAE_COMMANDS))
        OPT += -DHAS_SOLVER_SLAE_COMMANDS
        SOURCES_C += $(SOLVER_SLAE_DIR)/solver_slae_commands.c
    endif
endif