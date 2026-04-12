if(NOT INTERRUPT_DRV_MK_INC)
    set(INTERRUPT_DRV_MK_INC Y)

    set(INTERRUPT_CUSTOM_DIR ${MCAL_CUSTOM_DIR}/interrupt)

    include_directories(${INTERRUPT_CUSTOM_DIR})
    
    string(APPEND MCAL_OPT " -DHAS_INTERRUPT_CUSTOM")

    string(APPEND SOURCES_C " ${INTERRUPT_CUSTOM_DIR}/interrupt_mcal.c")

    if(INTERRUPT_DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_INTERRUPT_DIAG")
        string(APPEND SOURCES_DIAG_C " ${INTERRUPT_CUSTOM_DIR}/interrupt_custom_diag.c")
    endif()

    if(CLI STREQUAL Y)
        if(INTERRUPT_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_INTERRUPT_COMMANDS")
            string(APPEND SOURCES_C " ${INTERRUPT_CUSTOM_DIR}/interrupt_custom_commands.c")
        endif()
    endif()
endif()