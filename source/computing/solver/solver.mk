$(info SOLVER_MK_INC=$(SOLVER_MK_INC))

ifneq ($(SOLVER_MK_INC),Y)
    SOLVER_MK_INC=Y

    SOLVER_DIR = $(COMPUTING_DIR)/solver
    #@echo $(error SOLVER_DIR= $(SOLVER_DIR))

    OPT += -DHAS_SOLVER
    INCDIR += -I$(SOLVER_DIR)

    ifeq ($(SOLVER_COMMANDS),Y)
        OPT += -DHAS_SOLVER_COMMANDS
    endif

    ifeq ($(SOLVER_EXPRESSION),Y)
        #@echo $(error SOLVER_EXPRESSION= $(SOLVER_EXPRESSION))
        include $(SOLVER_DIR)/solver_expression/solver_expression.mk
    endif

    ifeq ($(SOLVER_SLAE),Y)
        #@echo $(error SOLVER_SLAE= $(SOLVER_SLAE))
        include $(SOLVER_DIR)/solver_slae/solver_slae.mk
    endif
endif