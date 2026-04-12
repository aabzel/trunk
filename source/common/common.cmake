if(NOT (COMMON_MK_INC STREQUAL Y))
    set(COMMON_MK_INC Y)

    set(COMMON_DIR "${WORKSPACE_LOC}/common")

    string(APPEND MCAL_OPT " -DHAS_COMMON")

    #string(APPEND INCDIR " ${COMMON_DIR}")
    include_directories( ${COMMON_DIR})

    if(DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_COMMON_DIAG")
        string(APPEND SOURCES_C " ${COMMON_DIR}/shared_array.c")
        string(APPEND SOURCES_C " ${COMMON_DIR}/common_diag.c")
    endif()

    if(SUPER_LOOP STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_SUPER_LOOP")
    endif()

    if(CORE_EXT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_CORE_EXT")
    endif()

    if(SYS_INIT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_SYS_INIT")
    endif()

    string(APPEND SOURCES_C " ${COMMON_DIR}/common_functions.c")

    if(CLI STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_COMMON_COMMANDS")
        string(APPEND SOURCES_C " ${COMMON_DIR}/common_commands.c")
    endif()

    include(${COMMON_DIR}/code_generator/code_generator.cmake)

    if(SW_COMPONENT STREQUAL Y)
        include(${COMMON_DIR}/sw_component/sw_component.cmake)
    endif()

    if(MULTIMEDIA STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_MULTIMEDIA")
        string(APPEND INCDIR " ${COMMON_DIR}/multimedia")
        if(MULTIMEDIA_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_MULTIMEDIA_COMMANDS")
            string(APPEND SOURCES_C " ${COMMON_DIR}/multimedia/multimedia_commands.c")
        endif()
        string(APPEND SOURCES_C " ${COMMON_DIR}/multimedia/proc_multimedia.c")
    endif()

endif()
