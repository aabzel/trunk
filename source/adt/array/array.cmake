message(STATUS "ARRAY_CMAKE_INC=${ARRAY_CMAKE_INC}")
if( NOT (ARRAY_CMAKE_INC STREQUAL Y))
    set(ARRAY_CMAKE_INC Y)
    message(STATUS "+ Array")

    set(ARRAY_DIR ${ADT_DIR}/array)
    message(STATUS "ARRAY_DIR=${ARRAY_DIR}")
    message(STATUS "ARRAY_DIAG=[${ARRAY_DIAG}]")
    message(STATUS "ARRAY_COMMANDS=[${ARRAY_COMMANDS}]")

    target_compile_definitions(app PUBLIC HAS_ARRAY)
    target_compile_definitions(app PUBLIC HAS_ARRAY_EXT)

    if (ARRAY_VERIFY STREQUAL Y)
        message(STATUS "+ARRAY_VERIFY")
        target_compile_definitions(app PUBLIC HAS_ARRAY_VERIFY)
    endif()

    if(ARRAY_I2S_SLAVE STREQUAL Y)
        message(STATUS "+HAS_ARRAY_I2S_SLAVE")
        target_compile_definitions(app PUBLIC HAS_ARRAY_I2S_SLAVE)
    endif()


    if(ARRAY_I2S_MASTER STREQUAL Y)
        message(STATUS "+HAS_ARRAY_I2S_MASTER")
        target_compile_definitions(app PUBLIC HAS_ARRAY_I2S_MASTER)
    endif()

    #add_compile_definitions(HAS_ARRAY)

    target_include_directories(app PUBLIC ${ARRAY_DIR})
    target_sources(app PRIVATE ${ARRAY_DIR}/array.c)


    if(DIAG STREQUAL Y)
        if(ARRAY_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_ARRAY_DIAG)
            target_sources(app PRIVATE ${ARRAY_DIR}/array_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(ARRAY_COMMANDS STREQUAL Y)
            message(STATUS "+ARRAY_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_ARRAY_COMMANDS)
            target_sources(app PRIVATE ${ARRAY_DIR}/array_commands.c)
        endif()
    endif()
endif()
