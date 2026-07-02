
$(info TEST_PWM_DAC_MK_INC=$(TEST_PWM_DAC_MK_INC))

ifneq ($(TEST_PWM_DAC_MK_INC),Y)
    TEST_PWM_DAC_MK_INC=Y

    TEST_PWM_DAC_DIR = $(TEST_SET_HW_DIR)/test_pwm_dac
    #@echo $(error TEST_PWM_DAC_DIR=$(TEST_PWM_DAC_DIR))
    
    INCDIR += -I$(TEST_PWM_DAC_DIR)
    OPT += -DHAS_TEST_PWM_DAC
    
    SOURCES_C += $(TEST_PWM_DAC_DIR)/test_pwm_dac.c
endif