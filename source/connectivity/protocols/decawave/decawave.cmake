
message(STATUS "DECAWAVE_CMAKE_INC=${DECAWAVE_CMAKE_INC}")
if( NOT (DECAWAVE_CMAKE_INC STREQUAL Y))
    set(DECAWAVE_CMAKE_INC Y)
    message(STATUS "+ DECAWAVE")

    set(DECAWAVE_PROTOCOL_DIR ${PROTOCOLS_DIR}/decawave)
    message(STATUS "DECAWAVE_PROTOCOL_DIR=${DECAWAVE_PROTOCOL_DIR}")

    target_compile_definitions(app PUBLIC HAS_DECAWAVE)

    include_directories(${DECAWAVE_PROTOCOL_DIR})
    target_include_directories(app PUBLIC ${DECAWAVE_PROTOCOL_DIR})

    target_sources(app PRIVATE ${DECAWAVE_PROTOCOL_DIR}/decawave.c)

    if (DIAG STREQUAL Y)
        if (DECAWAVE_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_DECAWAVE_DIAG)
            target_sources(app PRIVATE ${DECAWAVE_PROTOCOL_DIR}/decawave_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (DECAWAVE_COMMANDS STREQUAL Y)
             message(STATUS "+ DECAWAVE_COMMANDS")
             target_compile_definitions(app PUBLIC HAS_DECAWAVE_COMMANDS)
             target_sources(app PRIVATE ${DECAWAVE_PROTOCOL_DIR}/decawave_commands.c)
        endif()
    endif()
endif()




