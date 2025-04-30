message(STATUS "TEST_GPIO_MK_INC=${BSP_MK_INC}")
if( NOT (TEST_GPIO_MK_INC STREQUAL Y))
    set(TEST_GPIO_MK_INC Y)

    message(STATUS "Link Test GPIO")
    set(TEST_GPIO_DIR ${TEST_SET_HW_DIR}/test_gpio)

    target_include_directories(app PUBLIC ${TEST_GPIO_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_GPIO)

    target_sources(app PRIVATE ${TEST_GPIO_DIR}/test_gpio.c)
endif()