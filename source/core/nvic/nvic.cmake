if( NOT (NVIC_MK_INC STREQUAL Y))
    set(NVIC_DRV_MK_INC Y )

    set(NVIC_DIR "${CORE_DIR}/nvic")
    include_directories( ${NVIC_DIR})
    

    string(APPEND MCAL_OPT " -DHAS_NVIC")
    string(APPEND SOURCES_C " ${NVIC_DIR}/nvic_mcal.c")

    if(DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_NVIC_DIAG")
        string(APPEND SOURCES_DIAG_C " ${NVIC_DIR}/nvic_diag.c")
    endif()

    if(CLI STREQUAL Y)
        if(NVIC_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_NVIC_COMMANDS")
            string(APPEND SOURCES_C " ${NVIC_DIR}/nvic_commands.c")
        endif()
    endif()
endif()