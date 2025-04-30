
message(STATUS "PROTOCOL_CMAKE_INC=${PROTOCOL_CMAKE_INC}")
if( NOT (PROTOCOL_CMAKE_INC STREQUAL Y))
    set(PROTOCOL_CMAKE_INC Y)
    message(STATUS "+ General PROTOCOL code")

    set(PROTOCOL Y)

    set(PROTOCOL_DIR ${PROTOCOLS_DIR}/protocol)
    message(STATUS "PROTOCOL_DIR=${PROTOCOL_DIR}")

    #add_compile_definitions(HAS_PROTOCOL)
    target_compile_definitions(app PUBLIC HAS_PROTOCOL)

    #include_directories(${PROTOCOL_DIR})
    target_include_directories(app PUBLIC ${PROTOCOL_DIR})

    target_sources(app PRIVATE ${PROTOCOL_DIR}/protocol.c)

    if (DIAG STREQUAL Y)
        if (PROTOCOL_DIAG STREQUAL Y)
            message(STATUS "+ PROTOCOL_DIAG")
            #target_compile_definitions(app PUBLIC HAS_PROTOCOL_DIAG)
            add_compile_definitions(HAS_PROTOCOL_DIAG)
            target_sources(app PRIVATE ${PROTOCOL_DIR}/protocol_diag.c)
        endif()
    endif()

    if (PROTOCOL STREQUAL Y)
        if (PROTOCOL_COMMANDS STREQUAL Y)
             message(STATUS "+ PROTOCOL_COMMANDS")
             target_compile_definitions(app PUBLIC HAS_PROTOCOL_COMMANDS)
             target_sources(app PRIVATE ${PROTOCOL_DIR}/protocol_commands.c)
        endif()
    endif()
endif()
