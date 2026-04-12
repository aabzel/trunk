
if(NOT (RATIONAL_NUM_MK_INC STREQUAL Y))
    set(RATIONAL_NUM_MK_INC Y)

    set(RATIONAL_NUM_DIR "${COMPUTING_DIR}/rational_num")

    include_directories(${RATIONAL_NUM_DIR})
    string(APPEND MCAL_OPT " -DHAS_RATIONAL_NUM")

    string(APPEND SOURCES_C " ${RATIONAL_NUM_DIR}/rational_num.c")

    if(RATIONAL_NUM_DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_RATIONAL_NUM_DIAG")
        string(APPEND SOURCES_C " ${RATIONAL_NUM_DIR}/rational_num_diag.c")
    endif()

    if(RATIONAL_NUM_COMMANDS STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_RATIONAL_NUM_COMMANDS")
        string(APPEND SOURCES_C " ${RATIONAL_NUM_DIR}/rational_num_commands.c")
    endif()
endif()
