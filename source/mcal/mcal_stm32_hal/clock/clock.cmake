if(NOT CLOCK_CUSTOM_MK_INC)
    set(CLOCK_CUSTOM_MK_INC Y)

    set(CLOCK_CUSTOM_DIR ${MCAL_CUSTOM_DIR}/clock)

    include_directories(${CLOCK_CUSTOM_DIR})
    string(APPEND MCAL_OPT " -DHAS_CLOCK_CUSTOM")
    string(APPEND SOURCES_C " ${CLOCK_CUSTOM_DIR}/clock_mcal.c")

    if(DIAG STREQUAL Y)
        if(CLOCK_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_CLOCK_DIAG")
            string(APPEND SOURCES_DIAG_C " ${CLOCK_CUSTOM_DIR}/clock_custom_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(CLOCK_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_CLOCK_CUSTOM_COMMANDS")
            string(APPEND SOURCES_C " ${CLOCK_CUSTOM_DIR}/clock_custom_commands.c")
        endif()
    endif()
endif()