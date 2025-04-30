
message(STATUS "STACK_FRAME_CMAKE_INC=${STACK_FRAME_CMAKE_INC}")
if( NOT (STACK_FRAME_CMAKE_INC STREQUAL Y))
    set(STACK_FRAME_CMAKE_INC Y)
    message(STATUS "+ STACK_FRAME")

    set(STACK_FRAME_PROTOCOL_DIR ${PROTOCOLS_DIR}/stack_frame)
    message(STATUS "STACK_FRAME_PROTOCOL_DIR=${STACK_FRAME_PROTOCOL_DIR}")

    target_compile_definitions(app PUBLIC HAS_STACK_FRAME)

    include_directories(${STACK_FRAME_PROTOCOL_DIR})
    target_include_directories(app PUBLIC ${STACK_FRAME_PROTOCOL_DIR})

    target_sources(app PRIVATE ${STACK_FRAME_PROTOCOL_DIR}/stack_frame.c)

    if (DIAG STREQUAL Y)
        if (STACK_FRAME_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_STACK_FRAME_DIAG)
            target_sources(app PRIVATE ${STACK_FRAME_PROTOCOL_DIR}/stack_frame_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (STACK_FRAME_COMMANDS STREQUAL Y)
             message(STATUS "+ STACK_FRAME_COMMANDS")
             target_compile_definitions(app PUBLIC HAS_STACK_FRAME_COMMANDS)
             target_sources(app PRIVATE ${STACK_FRAME_PROTOCOL_DIR}/stack_frame_commands.c)
        endif()
    endif()
endif()




