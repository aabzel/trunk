
message(STATUS "BH1750_CMK_INC=${BH1750_CMK_INC}")

if( NOT (BH1750_CMK_INC STREQUAL Y))
    set(BH1750_CMK_INC Y)

    set(BH1750_DIR ${ASICS_DIR}/bh1750)
    message(STATUS "Add BH1750 Bluetooth Module driver")
    message(STATUS "I2S=[${I2S}]")

    target_include_directories(app PUBLIC ${BH1750_DIR})

    target_compile_definitions(app PUBLIC HAS_BH1750)

    if( NOT (I2S STREQUAL Y))
        message( SEND_ERROR "+ I2S" )
    endif()

    if( NOT (LIMITER STREQUAL Y))
        message( SEND_ERROR "+ LIMITER" )
    endif()

    if( NOT (UART STREQUAL Y))
        message( SEND_ERROR "+ UART" )
    endif()

    target_sources(app PRIVATE ${BH1750_DIR}/bh1750_drv.c)

    if (BH1750_I2S_MASTER STREQUAL Y)
        if (I2S0_MASTER STREQUAL Y)
            message( SEND_ERROR "Double Master on I2S bus")
        endif()

        message(STATUS "Add BH1750 Master")
        target_compile_definitions(app PUBLIC HAS_BH1750_I2S_MASTER)
    endif()

    if (BH1750_I2S_SLAVE STREQUAL Y)
        message(STATUS "Add BH1750 slave")
        target_compile_definitions(app PUBLIC HAS_BH1750_I2S_SLAVE)
    endif()

    if( NOT (BH1750_I2S_SLAVE STREQUAL Y))
        if( NOT (BH1750_I2S_MASTER STREQUAL Y))
            message( SEND_ERROR "BH1750 Role must be spesified")
        endif()
    endif()

    if((BH1750_I2S_SLAVE STREQUAL Y))
        if((BH1750_I2S_MASTER STREQUAL Y))
            message( SEND_ERROR "BH1750 Role must have only one role")
        endif()
    endif()

    if (DIAG STREQUAL Y)
        if (BH1750_DIAG STREQUAL Y)
            message(STATUS "Add BH1750 diag")
            target_compile_definitions(app PUBLIC HAS_BH1750_DIAG)
            target_sources(app PRIVATE ${BH1750_DIR}/bh1750_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (BH1750_COMMANDS STREQUAL Y)
            message(STATUS "Add BH1750 commands")
            target_compile_definitions(app PUBLIC HAS_BH1750_COMMANDS)
            target_compile_definitions(app PUBLIC HAS_MULTIMEDIA_COMMANDS)
            target_sources(app PRIVATE ${BH1750_DIR}/bh1750_commands.c)
        endif()
    endif()
endif()
