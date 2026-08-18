
message(STATUS "LTR390_CMK_INC=${LTR390_CMK_INC}")

if( NOT (LTR390_CMK_INC STREQUAL Y))
    set(LTR390_CMK_INC Y)

    set(LTR390_DIR ${ASICS_DIR}/ltr390)
    message(STATUS "Add LTR390 Bluetooth Module driver")
    message(STATUS "I2S=[${I2S}]")

    target_include_directories(app PUBLIC ${LTR390_DIR})

    target_compile_definitions(app PUBLIC HAS_LTR390)

    if( NOT (I2S STREQUAL Y))
        message( SEND_ERROR "+ I2S" )
    endif()

    if( NOT (LIMITER STREQUAL Y))
        message( SEND_ERROR "+ LIMITER" )
    endif()

    if( NOT (UART STREQUAL Y))
        message( SEND_ERROR "+ UART" )
    endif()

    target_sources(app PRIVATE ${LTR390_DIR}/ltr390_drv.c)

    if (LTR390_I2S_MASTER STREQUAL Y)
        if (I2S0_MASTER STREQUAL Y)
            message( SEND_ERROR "Double Master on I2S bus")
        endif()

        message(STATUS "Add LTR390 Master")
        target_compile_definitions(app PUBLIC HAS_LTR390_I2S_MASTER)
    endif()

    if (LTR390_I2S_SLAVE STREQUAL Y)
        message(STATUS "Add LTR390 slave")
        target_compile_definitions(app PUBLIC HAS_LTR390_I2S_SLAVE)
    endif()

    if( NOT (LTR390_I2S_SLAVE STREQUAL Y))
        if( NOT (LTR390_I2S_MASTER STREQUAL Y))
            message( SEND_ERROR "LTR390 Role must be spesified")
        endif()
    endif()

    if((LTR390_I2S_SLAVE STREQUAL Y))
        if((LTR390_I2S_MASTER STREQUAL Y))
            message( SEND_ERROR "LTR390 Role must have only one role")
        endif()
    endif()

    if (DIAG STREQUAL Y)
        if (LTR390_DIAG STREQUAL Y)
            message(STATUS "Add LTR390 diag")
            target_compile_definitions(app PUBLIC HAS_LTR390_DIAG)
            target_sources(app PRIVATE ${LTR390_DIR}/ltr390_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (LTR390_COMMANDS STREQUAL Y)
            message(STATUS "Add LTR390 commands")
            target_compile_definitions(app PUBLIC HAS_LTR390_COMMANDS)
            target_compile_definitions(app PUBLIC HAS_MULTIMEDIA_COMMANDS)
            target_sources(app PRIVATE ${LTR390_DIR}/ltr390_commands.c)
        endif()
    endif()
endif()
