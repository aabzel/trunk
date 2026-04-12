message(STATUS "TIME_GENERAL_MK_INC=${TIME_GENERAL_MK_INC}")

if(NOT (TIME_GENERAL_MK_INC STREQUAL Y))
    set(TIME_GENERAL_MK_INC Y)

    set(TIME_GENERAL_DIR "${SENSITIVITY_DIR}/time")
    include_directories(${TIME_GENERAL_DIR})

    string(APPEND MCAL_OPT " -DHAS_TIME")

    if(TIME_PROC STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_TIME_PROC")
    endif()

    if(TIME_EXT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_TIME_EXT")
    endif()

    if(DATE STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_DATE")
    endif()

    string(APPEND SOURCES_C " ${TIME_GENERAL_DIR}/time_mcal.c")

    if(DIAG STREQUAL Y)
        if(TIME_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_TIME_DIAG")
            string(APPEND SOURCES_DIAG_C " ${TIME_GENERAL_DIR}/time_diag.c")
        endif()
    endif()

    if(TIMER STREQUAL Y)
        string(APPEND SOURCES_C " ${TIME_GENERAL_DIR}/timer_utils.c")
    endif()

    string(APPEND SOURCES_C " ${TIME_GENERAL_DIR}/none_blocking_pause.c")

    if(CLI STREQUAL Y)
        if(TIME_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_TIME_COMMANDS")
            string(APPEND SOURCES_C " ${TIME_GENERAL_DIR}/time_commands.c")
        endif()
    endif()
endif()
