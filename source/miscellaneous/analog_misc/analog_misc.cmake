if(NOT (ANALOG_MISC_GENERAL_MK_INC STREQUAL Y))
    set(ANALOG_MISC_GENERAL_MK_INC Y)

    set(ANALOG_MISC_MCAL_DIR "${MISCELLANEOUS_DIR}/analog_misc")
    include_directories(${ANALOG_MISC_MCAL_DIR})

    string(APPEND MCAL_OPT " -DHAS_ANALOG_MISC")

    string(APPEND SOURCES_C " ${ANALOG_MISC_MCAL_DIR}/analog_misc.c")

    if(DIAG STREQUAL Y)
        if(ANALOG_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_ANALOG_DIAG")
            string(APPEND SOURCES_C " ${ANALOG_MISC_MCAL_DIR}/analog_misc_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(ANALOG_MISC_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_ANALOG_MISC_COMMANDS")
            string(APPEND SOURCES_C " ${ANALOG_MISC_MCAL_DIR}/analog_misc_commands.c")
        endif()
    endif()
endif()