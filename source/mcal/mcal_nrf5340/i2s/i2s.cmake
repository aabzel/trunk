#message( SEND_ERROR Test compile)

message(STATUS "I2S_NRF5340_MK_INC=${I2S_NRF5340_MK_INC}")
if( NOT (Y STREQUAL I2S_NRF5340_MK_INC))
    set(I2S_NRF5340_MK_INC Y)

    set(I2S_NRF5340_DIR ${MCAL_NRF5340_DIR}/i2s)
    message(STATUS "Add I2S for nrf5340")
    message(STATUS "I2S_NRF5340_DIR=${I2S_NRF5340_DIR}")

    message(STATUS "I2S0_MASTER=${I2S0_MASTER}")
    message(STATUS "I2S0_SLAVE=${I2S0_SLAVE}")
    message(STATUS "I2S0_LOOPBACK=${I2S0_LOOPBACK}")
    message(STATUS "I2S0=${I2S0}")

    add_compile_definitions(HAS_I2S)

    include_directories(${I2S_NRF5340_DIR})
    target_include_directories(app PUBLIC ${I2S_NRF5340_DIR})

    target_sources(app PRIVATE ${I2S_NRF5340_DIR}/i2s_drv.c)

    if(I2S_ISR STREQUAL Y)
        message(STATUS "Add I2S ISR")
        target_compile_definitions(app PUBLIC HAS_I2S_ISR)
        target_sources(app PRIVATE ${I2S_NRF5340_DIR}/i2s_isr.c)
    endif()

    target_compile_definitions(app PUBLIC HAS_NRFX_I2S)
    target_compile_definitions(app PUBLIC HAS_I2S_NRFX)
    target_compile_definitions(app PUBLIC NRFX_I2S_ENABLED)

    set(NRFX_I2S_DIR ${NRF_SDK_DIR}/modules/hal/nordic/nrfx/hal)
    message(STATUS "NRFX_I2S_DIR=${NRFX_I2S_DIR}")
    target_include_directories(app PUBLIC ${NRFX_I2S_DIR})

    if (I2S0_MASTER STREQUAL Y)
        message(STATUS "Add I2S0_MASTER")
        target_compile_definitions(app PUBLIC HAS_I2S0_MASTER)
    endif()

    if (I2S0_SLAVE STREQUAL Y)
        message(STATUS "Add I2S0_SLAVE")
        target_compile_definitions(app PUBLIC HAS_I2S0_SLAVE)
    endif()

    if (I2S0_LOOPBACK STREQUAL Y)
        message(STATUS "Add I2S0_LOOPBACK")
        target_compile_definitions(app PUBLIC HAS_I2S0_LOOPBACK)
    endif()

    if (I2S0 STREQUAL Y)
        message(STATUS "Add I2S0")
        target_compile_definitions(app PUBLIC HAS_I2S0)
    endif()

    if(DIAG STREQUAL Y)
        if(I2S_DIAG STREQUAL Y)
            message(STATUS "Add I2S custon  diag")
            target_compile_definitions(app PUBLIC HAS_I2S_DIAG)
            target_sources(app PRIVATE ${I2S_NRF5340_DIR}/i2s_nrf_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(I2S_COMMANDS STREQUAL Y)
            #message( SEND_ERROR I2S_COMMANDS=${I2S_COMMANDS} )
            message(STATUS "Add I2S custon commands")
            target_compile_definitions(app PUBLIC HAS_I2S_CUSTOM_COMMANDS)
            target_sources(app PRIVATE ${I2S_NRF5340_DIR}/i2s_custom_commands.c)
        endif()
    endif()
endif()
