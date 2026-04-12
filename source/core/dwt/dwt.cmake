message(STATUS "DWT_MK_INC=${DWT_MK_INC}")
if(NOT (DWT_MK_INC STREQUAL Y))
    set(DWT_MK_INC Y)

    set(DWT_DIR "${CORE_DIR}/dwt")
    include_directories( ${DWT_DIR})

    string(APPEND MCAL_OPT " -DHAS_DWT")
    string(APPEND MCAL_OPT " -DHAS_DWT_PROC")

    string(APPEND SOURCES_C " ${DWT_DIR}/dwt_mcal.c")
    string(APPEND SOURCES_CONFIGURATION_C " ${DWT_DIR}/dwt_config.c")

    if(DIAG STREQUAL Y)
        if(DWT_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_DWT_DIAG")
            string(APPEND SOURCES_DIAG_C " ${DWT_DIR}/dwt_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(DWT_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_DWT_COMMANDS")
            string(APPEND SOURCES_C " ${DWT_DIR}/dwt_commands.c")
        endif()
    endif()
endif()

