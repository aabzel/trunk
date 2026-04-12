if(NOT DATA_MISC_MK_INC STREQUAL Y)
    set(DATA_MISC_MK_INC Y)

    set(DATA_MCAL_DIR "${MISCELLANEOUS_DIR}/data_misc")

    include_directories(${DATA_MCAL_DIR})
    string(APPEND MCAL_OPT " -DHAS_DATA_UTILS")
    string(APPEND MCAL_OPT " -DHAS_DATA_MISC")

    string(APPEND SOURCES_C " ${DATA_MCAL_DIR}/data_utils.c")

    if(DIAG STREQUAL Y)
        if(DATA_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_DATA_DIAG")
            string(APPEND SOURCES_C " ${DATA_MCAL_DIR}/data_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(DATA_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_DATA_COMMANDS")
            string(APPEND SOURCES_C " ${DATA_MCAL_DIR}/data_commands.c")
        endif()
    endif()
endif()