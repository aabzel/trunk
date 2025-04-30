message(STATUS "UART_ZPHR_CMAKE_INC=${UART_ZPHR_CMAKE_INC}")
if( NOT (UART_ZPHR_CMAKE_INC STREQUAL Y))
    set(UART_ZPHR_CMAKE_INC Y)
    message(STATUS "set UART_ZPHR_CMAKE_INC=${UART_ZPHR_CMAKE_INC}")
    message(STATUS "+ UART for Zephyr")

    set(UART_ZEPHYR_DIR ${MCAL_ZEPHYR_DIR}/uart)
    message(STATUS "UART_ZEPHYR_DIR=${UART_ZEPHYR_DIR}")

    add_compile_definitions(HAS_UART)
    target_compile_definitions(app PUBLIC HAS_UART)

    message(STATUS "UART_ISR=${UART_ISR}")
    message(STATUS "UART_PROC=${UART_PROC}")
    message(STATUS "UART0=${UART0}")
    message(STATUS "UART1=${UART1}")
    message(STATUS "UART2=${UART2}")
    message(STATUS "UART3=${UART3}")

    if (UART_PROC STREQUAL Y)
        message(STATUS "+ UART_PROC")
        target_compile_definitions(app PUBLIC HAS_USART_PROC)
        target_compile_definitions(app PUBLIC HAS_UART_PROC)
    endif()

    include_directories(${UART_ZEPHYR_DIR})
    target_include_directories(app PUBLIC ${UART_ZEPHYR_DIR})

    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/zephyr/include/zephyr/drivers)

    if(UART0 STREQUAL Y)
        message(STATUS "+ UART0")
        target_compile_definitions(app PUBLIC HAS_UART0)
    endif()

    if(UART1 STREQUAL Y)
        message(STATUS "+ UART1")
        target_compile_definitions(app PUBLIC HAS_UART1)
    endif()

    if(UART2 STREQUAL Y)
        message(STATUS "+ UART2")
        target_compile_definitions(app PUBLIC HAS_UART2)
    endif()

    if(UART3 STREQUAL Y)
        message(STATUS "+ UART3")
        target_compile_definitions(app PUBLIC HAS_UART3)
    endif()

    if(UART_ISR STREQUAL Y)
        message(STATUS "+ UART Interrupts")
        target_compile_definitions(app PUBLIC HAS_UART_INTERRUPT)
        target_compile_definitions(app PUBLIC HAS_UART_ISR)
        target_sources(app PRIVATE ${UART_ZEPHYR_DIR}/uart_isr.c)
    endif()

    target_sources(app PRIVATE ${UART_ZEPHYR_DIR}/uart_drv.c)

    if(CLI STREQUAL Y)
        message(STATUS "+ UART custom commands")
        target_sources(app PRIVATE ${UART_ZEPHYR_DIR}/uart_custom_commands.c)
    endif()

endif()



