
ifneq ($(TEST_SOLVER_MK_INC),Y)
    TEST_SOLVER_MK_INC=Y

    TEST_SOLVER_DIR = $(TEST_SET_SW_DIR)/test_solver
    #@echo $(error TEST_SOLVER_DIR= $(TEST_SOLVER_DIR))
    
    INCDIR += -I$(TEST_SOLVER_DIR)
    OPT += -DHAS_TEST_SUIT_SOLVER
    
    SOURCES_C += $(TEST_SOLVER_DIR)/test_solver.c
endif