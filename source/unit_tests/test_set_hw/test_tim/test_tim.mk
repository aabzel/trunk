
$(info TEST_TIM_MK_INC=$(TEST_TIM_MK_INC))
ifneq ($(TEST_TIM_MK_INC),Y)
    TEST_TIM_MK_INC=Y

    #@echo $(error TEST_TIM_DIR=$(TEST_TIM_DIR))
    INCDIR += -I$(TEST_TIM_DIR)

    OPT += -DHAS_TEST_TIM

    SOURCES_C += $(TEST_TIM_DIR)/test_tim.c
endif