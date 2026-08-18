message(STATUS "MAX98357_MK_INC=${MAX98357_MK_INC}")
if( NOT (MAX98357_MK_INC STREQUAL Y))
    set(MAX98357_MK_INC Y)
    message(STATUS "+ Wm8731")

    set(MAX98357_DIR ${ASICS_DIR}/max98357)
    message(STATUS "MAX98357_DIR=${MAX98357_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_MAX98357)
    target_compile_definitions(app PUBLIC HAS_MAX98357)

    target_include_directories(app PUBLIC ${MAX98357_DIR})
    target_sources(app PRIVATE ${MAX98357_DIR}/max98357_drv.c)

    if(MAX98357_I2S_SLAVE STREQUAL Y)
        message(STATUS "Add HAS_MAX98357_I2S_SLAVE")
        target_compile_definitions(app PUBLIC HAS_MAX98357_I2S_SLAVE)
    endif()

    if(MAX98357_I2S_MASTER STREQUAL Y)
        message(STATUS "Add HAS_MAX98357_I2S_MASTER")
        target_compile_definitions(app PUBLIC HAS_MAX98357_I2S_MASTER)
    endif()

    if(DIAG STREQUAL Y)
        if(MAX98357_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_MAX98357_DIAG)
            target_sources(app PRIVATE ${MAX98357_DIR}/max98357_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(MAX98357_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_MAX98357_COMMANDS)
            target_sources(app PRIVATE ${MAX98357_DIR}/max98357_commands.c)
        endif()
    endif()
endif()
