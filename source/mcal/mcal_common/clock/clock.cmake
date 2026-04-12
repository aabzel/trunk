message(STATUS "CLOCK_GENERAL_MK_INC=${CLOCK_GENERAL_MK_INC}")
if(NOT (CLOCKS_GENERAL_MK_INC STREQUAL Y))
    set(CLOCKS_GENERAL_MK_INC Y)

    set(CLOCK_MCAL_DIR "${MCAL_COMMON_DIR}/clock")
    include_directories( ${CLOCK_MCAL_DIR})

    string(APPEND MCAL_OPT " -DHAS_CLOCK")

    string(APPEND SOURCES_C " ${CLOCK_MCAL_DIR}/clock_general.c")

    if(CLOCK_EXT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_CLOCK_EXT")
    endif()

    if(START_PAUSE STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_START_PAUSE")
    endif()

    if(CLOCK_RUN_TIME_CTRL STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_CLOCK_RUN_TIME_CTRL")
    endif()

    if(DIAG STREQUAL Y)
        if(CLOCK_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_CLOCK_DIAG")
            string(APPEND SOURCES_C " ${CLOCK_MCAL_DIR}/clock_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(CLOCK_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_CLOCK_COMMANDS")
            string(APPEND SOURCES_C " ${CLOCK_MCAL_DIR}/clock_commands.c")
        endif()
    endif()
endif()