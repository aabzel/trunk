message(STATUS "SW_UART_MK_INC=${SW_UART_MK_INC}")
if( NOT (SW_UART_MK_INC  STREQUAL  Y))
    set(SW_UART_MK_INC Y)
    message(STATUS "+ SW_UART")

    set(SW_UART_DIR ${ROOT_DIR}/sw_uart)
    message(STATUS "SW_UART_DIR=${SW_UART_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_SW_UART)
    target_compile_definitions(app PUBLIC HAS_SW_UART)
    target_compile_definitions(app PUBLIC HAS_SW_UART_PROC)

    target_include_directories(app PUBLIC ${SW_UART_DIR})
    target_sources(app PRIVATE ${SW_UART_DIR}/sw_uart.c)

    if(DIAG  STREQUAL  Y)
        if(SW_UART_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SW_UART_DIAG)
            target_sources(app PRIVATE ${SW_UART_DIR}/sw_uart_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(SW_UART_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SW_UART_COMMANDS)
            target_sources(app PRIVATE ${SW_UART_DIR}/sw_uart_commands.c)
        endif()
    endif()
endif()
