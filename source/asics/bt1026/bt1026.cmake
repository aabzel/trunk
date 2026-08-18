
message(STATUS "BT1026_CMK_INC=${BT1026_CMK_INC}")

if( NOT (BT1026_CMK_INC STREQUAL Y))
    set(BT1026_CMK_INC Y)

    set(BT1026_DIR ${ASICS_DIR}/bt1026)
    message(STATUS "Add BT1026 Bluetooth Module driver")
    message(STATUS "I2S=[${I2S}]")

    target_include_directories(app PUBLIC ${BT1026_DIR})

    target_compile_definitions(app PUBLIC HAS_BT1026)
    target_compile_definitions(app PUBLIC HAS_BT1026_PROC)

    if( NOT (I2S STREQUAL Y))
        message( SEND_ERROR "+ I2S" )
    endif()

    if( NOT (LIMITER STREQUAL Y))
        message( SEND_ERROR "+ LIMITER" )
    endif()

    if( NOT (UART STREQUAL Y))
        message( SEND_ERROR "+ UART" )
    endif()

    target_sources(app PRIVATE ${BT1026_DIR}/bt1026_drv.c)

    if (BT1026_I2S_MASTER STREQUAL Y)
        if (I2S0_MASTER STREQUAL Y)
            message( SEND_ERROR "Double Master on I2S bus")
        endif()

        message(STATUS "Add BT1026 Master")
        target_compile_definitions(app PUBLIC HAS_BT1026_I2S_MASTER)
    endif()

    if (BT1026_I2S_SLAVE STREQUAL Y)
        message(STATUS "Add BT1026 slave")
        target_compile_definitions(app PUBLIC HAS_BT1026_I2S_SLAVE)
    endif()

    if( NOT (BT1026_I2S_SLAVE STREQUAL Y))
        if( NOT (BT1026_I2S_MASTER STREQUAL Y))
            message( SEND_ERROR "BT1026 Role must be spesified")
        endif()
    endif()

    if((BT1026_I2S_SLAVE STREQUAL Y))
        if((BT1026_I2S_MASTER STREQUAL Y))
            message( SEND_ERROR "BT1026 Role must have only one role")
        endif()
    endif()

    if (DIAG STREQUAL Y)
        if (BT1026_DIAG STREQUAL Y)
            message(STATUS "Add BT1026 diag")
            target_compile_definitions(app PUBLIC HAS_BT1026_DIAG)
            target_sources(app PRIVATE ${BT1026_DIR}/bt1026_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (BT1026_COMMANDS STREQUAL Y)
            message(STATUS "Add BT1026 commands")
            target_compile_definitions(app PUBLIC HAS_BT1026_COMMANDS)
            target_compile_definitions(app PUBLIC HAS_MULTIMEDIA_COMMANDS)
            target_sources(app PRIVATE ${BT1026_DIR}/bt1026_commands.c)
        endif()
    endif()
endif()
