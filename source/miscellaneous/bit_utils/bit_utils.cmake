if(NOT (BIT_GENERAL_MK_INC STREQUAL Y))
    set(BIT_GENERAL_MK_INC Y)

    set(BIT_MCAL_DIR "${MISCELLANEOUS_DIR}/bit_utils")
    include_directories(${BIT_MCAL_DIR})

    string(APPEND MCAL_OPT " -DHAS_BIT_UTILS")

    string(APPEND SOURCES_C " ${BIT_MCAL_DIR}/bit_utils.c")

    if(DIAG STREQUAL Y)
        if(BIT_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_BIT_DIAG")
            string(APPEND SOURCES_C " ${BIT_MCAL_DIR}/bit_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(BIT_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_BIT_COMMANDS")
            string(APPEND SOURCES_C " ${BIT_MCAL_DIR}/bit_commands.c")
        endif()
    endif()
endif()