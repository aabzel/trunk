message(STATUS "COMMON_MK_INC=${COMMON_MK_INC}")
if( NOT (COMMON_MK_INC STREQUAL Y))
    set(COMMON_MK_INC Y)

    set(COMMON_DIR ${WORKSPACE_LOC}/common)
    message(STATUS "+ Common")
    message(STATUS "COMMON_DIR=${COMMON_DIR}")

    target_compile_definitions(app PUBLIC HAS_COMMON)

    target_include_directories(app PUBLIC ${COMMON_DIR})
    if(DIAG STREQUAL Y)
        message(STATUS "+DIAG")
        target_sources(app PRIVATE ${COMMON_DIR}/common_diag.c)
    endif()

    target_sources(app PRIVATE ${COMMON_DIR}/common_functions.c)

    if(CORE_EXT STREQUAL Y)
        message(STATUS "+CORE_EXT")
        target_compile_definitions(app PUBLIC HAS_CORE_EXT)
    endif()    
    
    if(SYS_INIT STREQUAL Y)
        message(STATUS "+SYS_INIT")
        target_compile_definitions(app PUBLIC HAS_SYS_INIT)
    endif()

    target_sources(app PRIVATE ${COMMON_DIR}/sw_init.c)
    
    include(${COMMON_DIR}/code_generator/code_generator.cmake)

    if(MULTIMEDIA STREQUAL Y)
        message(STATUS "+ multimedia")
        target_compile_definitions(app PUBLIC HAS_MULTIMEDIA)
        target_include_directories(app PUBLIC ${COMMON_DIR}/multimedia)
        target_sources(app PRIVATE ${COMMON_DIR}/multimedia/proc_multimedia.c)
        if(MULTIMEDIA_COMMANDS STREQUAL Y)
             message(STATUS "+ multimedia commands")
             target_compile_definitions(app PUBLIC HAS_MULTIMEDIA_COMMANDS)
             target_sources(app PRIVATE ${COMMON_DIR}/multimedia/multimedia_commands.c)
        endif()
    endif()

    #if(APPLICATIONS STREQUAL Y)
        #message(STATUS "+ APPLICATIONS")
        #include(${COMMON_DIR}/applications/applications.cmake)
    #endif()

    if (MCU STREQUAL Y)
        message(STATUS "+ MCU")
        target_sources(app PRIVATE ${COMMON_DIR}/hw_init.c)
    endif()
endif()
