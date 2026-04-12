if(NOT INTERRUPT_GENERAL_DRV_MK_INC STREQUAL Y)
    set(INTERRUPT_GENERAL_DRV_MK_INC Y)

    set(INTERRUPT_MCAL_DIR "${MCAL_COMMON_DIR}/interrupt")

    include_directories(${INTERRUPT_MCAL_DIR})
    string(APPEND MCAL_OPT " -DHAS_INTERRUPT")

    string(APPEND SOURCES_C " ${INTERRUPT_MCAL_DIR}/interrupt_general.c")

    if(INTERRUPT_EXT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_INTERRUPT_EXT")
    endif()

    if(DIAG STREQUAL Y)
        if(INTERRUPT_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_INTERRUPT_DIAG")
            string(APPEND SOURCES_C " ${INTERRUPT_MCAL_DIR}/interrupt_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(INTERRUPT_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_INTERRUPT_COMMANDS")
            string(APPEND SOURCES_C " ${INTERRUPT_MCAL_DIR}/interrupt_commands.c")
        endif()
    endif()
endif()