message(STATUS "SOCKET_MK_INC=${SOCKET_MK_INC}")
if( NOT (SOCKET_MK_INC STREQUAL Y))
    set(SOCKET_MK_INC Y)
    set(SOCKET_DIR ${INTERFACES_DIR}/socket)

    message(STATUS "+ SOCKET")

    target_include_directories(app PUBLIC ${SOCKET_DIR})
    #target_compile_definitions(app PUBLIC HAS_SOCKET_PROC)
    target_compile_definitions(app PUBLIC HAS_SOCKET)

    target_sources(app PRIVATE ${SOCKET_DIR}/socket_if.c)

    if (DIAG STREQUAL Y)
        if (SOCKET_DIAG STREQUAL Y)
            message(STATUS "+ SOCKET_DIAG")
            target_compile_definitions(app PUBLIC HAS_SOCKET_DIAG)
            target_sources(app PRIVATE ${SOCKET_DIR}/socket_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (SOCKET_COMMANDS STREQUAL Y)
            message(STATUS "+ SOCKET_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_SOCKET_COMMANDS)
        endif()
    endif()
endif()
