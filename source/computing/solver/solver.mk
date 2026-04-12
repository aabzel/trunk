$(info SOLVER_MK_INC=$(SOLVER_MK_INC))

ifneq ($(SOLVER_MK_INC),Y)
    SOLVER_MK_INC=Y

    SOLVER_DIR = $(COMPUTING_DIR)/solver
    # $(error SOLVER_DIR= $(SOLVER_DIR))

    MCAL_OPT += -DHAS_SOLVER
    INCDIR += -I$(SOLVER_DIR)

    ifeq ($(SOLVER_COMMANDS),Y)
        MCAL_OPT += -DHAS_SOLVER_COMMANDS
    endif

    ifeq ($(SOLVER_EXPRESSION),Y)
        # $(error SOLVER_EXPRESSION= $(SOLVER_EXPRESSION))
        include $(SOLVER_DIR)/solver_expression/solver_expression.mk
    endif

    ifeq ($(SOLVER_SLAE),Y)
        # $(error SOLVER_SLAE= $(SOLVER_SLAE))
        include $(SOLVER_DIR)/solver_slae/solver_slae.mk
    endif
endif