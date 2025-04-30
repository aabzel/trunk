
message(STATUS "UART_MK_INC=${UART_MK_INC}")
if( NOT (UART_MK_INC STREQUAL Y))
    set(UART_MK_INC Y)
    message(STATUS "Link UART General")

    set(UART_GENERAL_DIR ${MCAL_COMMON_DIR}/uart)
    message(STATUS "UART_GENERAL_DIR=${UART_GENERAL_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_UART)
    target_compile_definitions(app PUBLIC HAS_UART)

    include_directories(${UART_GENERAL_DIR})
    target_include_directories(app PUBLIC ${UART_GENERAL_DIR})
    
    target_sources(app PRIVATE ${UART_GENERAL_DIR}/uart_bsp.c)

    if(UART0 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_UART0)
    endif()

    if(UART1 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_UART1)
    endif()

    if(UART2 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_UART2)
    endif()

    if(UART3 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_UART3)
    endif()

    if(DIAG STREQUAL Y)
        if(UART_DIAG STREQUAL Y)
            target_sources(app PRIVATE ${UART_GENERAL_DIR}/uart_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(UART_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_UART_COMMANDS)
            target_sources(app PRIVATE ${UART_GENERAL_DIR}/uart_commands.c)
        endif()
    endif()
endif()

