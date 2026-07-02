
message(STATUS "TEST_PWM_DAC_MK_INC=${TEST_PWM_DAC_MK_INC}")

if( NOT (TEST_PWM_DAC_MK_INC STREQUAL Y))
    set(TEST_PWM_DAC_MK_INC Y)
    message(STATUS "Add PWM_DAC Test")

    set(TEST_PWM_DAC_DIR ${TEST_SET_HW_DIR}/test_pwm_dac)

    target_include_directories(app PUBLIC ${TEST_PWM_DAC_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_PWM_DAC)

    target_sources(app PRIVATE ${TEST_PWM_DAC_DIR}/test_pwm_dac.c)
endif()