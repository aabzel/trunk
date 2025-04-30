message(STATUS "TEST_UART_MK_INC=${BSP_MK_INC}")
if( NOT (TEST_UART_MK_INC STREQUAL Y))
    set(TEST_UART_MK_INC Y)
    message(STATUS "Add Test UART")

    set(TEST_UART_DIR ${TEST_SET_HW_DIR}/test_uart)

    target_include_directories(app PUBLIC ${TEST_UART_DIR})

    target_compile_definitions(app PUBLIC HAS_TEST_UART)

    target_sources(app PRIVATE ${TEST_UART_DIR}/test_uart.c)
endif()