
if(NOT (LIMITER_MK_INC STREQUAL Y))
    set(LIMITER_MK_INC Y)

    set(LIMITER_DIR "${COMPUTING_DIR}/limiter")
    include_directories(${LIMITER_DIR})
    

    string(APPEND MCAL_OPT " -DHAS_LIMITER")

    if(LIMITER_EXT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_LIMITER_EXT")
    endif()

    string(APPEND SOURCES_C " ${LIMITER_DIR}/limiter.c")

    if(LIMITER_DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_LIMITER_DIAG")
        string(APPEND SOURCES_C " ${LIMITER_DIR}/limiter_diag.c")
    endif()

    if(CLI STREQUAL Y)
        if(LIMITER_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_LIMITER_COMMANDS")
            string(APPEND SOURCES_C " ${LIMITER_DIR}/limiter_commands.c")
        endif()
    endif()
endif()