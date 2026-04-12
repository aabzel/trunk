if(NOT (FLOAT_GENERAL_MK_INC STREQUAL Y))
    set(FLOAT_GENERAL_MK_INC Y)

    #message(FATAL_ERROR "text")

    set(FLOAT_MCAL_DIR "${MISCELLANEOUS_DIR}/float_utils")

    include_directories(${FLOAT_MCAL_DIR})
    string(APPEND MCAL_OPT " -DHAS_FLOAT_UTILS")
    string(APPEND MCAL_OPT " -DHAS_FLOAT_EXT")
    string(APPEND MCAL_OPT " -DHAS_FLOAT")

    string(APPEND SOURCES_C " ${FLOAT_MCAL_DIR}/float_utils.c")

    if(DIAG STREQUAL Y)
        if(FLOAT_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_FLOAT_DIAG")
            string(APPEND SOURCES_C " ${FLOAT_MCAL_DIR}/float_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(FLOAT_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_FLOAT_COMMANDS")
            string(APPEND SOURCES_C " ${FLOAT_MCAL_DIR}/float_commands.c")
        endif()
    endif()
endif()