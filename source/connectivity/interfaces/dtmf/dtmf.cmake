message(STATUS "DTMF_MK_INC=${DTMF_MK_INC}")
if( NOT (DTMF_MK_INC STREQUAL Y))
    set(DTMF_MK_INC Y)
    set(DTMF_DIR ${INTERFACES_DIR}/dtmf)

    message(STATUS "+ DTMF")

    target_include_directories(app PUBLIC ${DTMF_DIR})
    #target_compile_definitions(app PUBLIC HAS_DTMF_PROC)
    target_compile_definitions(app PUBLIC HAS_DTMF)

    target_sources(app PRIVATE ${DTMF_DIR}/dtmf_if.c)

    if (DIAG STREQUAL Y)
        if (DTMF_DIAG STREQUAL Y)
            message(STATUS "+ DTMF_DIAG")
            target_compile_definitions(app PUBLIC HAS_DTMF_DIAG)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (DTMF_COMMANDS STREQUAL Y)
            message(STATUS "+ DTMF_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_DTMF_COMMANDS)
        endif()
    endif()
endif()
