message(STATUS "TEST_LED_MONO_MK_INC=${BSP_MK_INC}")
if( NOT (TEST_LED_MONO_MK_INC STREQUAL Y))
    set(TEST_LED_MONO_MK_INC Y)

    message(STATUS "+ Test LED_MONO")
    set(TEST_LED_MONO_DIR ${TEST_SET_HW_DIR}/test_led_mono)

    target_include_directories(app PUBLIC ${TEST_LED_MONO_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_LED_MONO)

    target_sources(app PRIVATE ${TEST_LED_MONO_DIR}/test_led_mono.c)
endif()