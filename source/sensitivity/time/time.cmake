message(STATUS "TIME_GENERAL_MK_INC=${TIME_GENERAL_MK_INC}")
if( NOT (TIME_GENERAL_MK_INC STREQUAL Y))
    set(TIME_GENERAL_MK_INC Y)
    message(STATUS "+ Time")

    set(TIME_GENERAL_DIR ${SENSITIVITY_DIR}/time)
    #@echo ${error TIME_GENERAL_DIR= ${TIME_GENERAL_DIR))

    target_include_directories(app PUBLIC ${TIME_GENERAL_DIR})

    target_compile_definitions(app PUBLIC HAS_TIME)
    target_compile_definitions(app PUBLIC HAS_TIME_PROC)

    if(DATE STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_DATE)
    endif()
        
    target_sources(app PRIVATE ${TIME_GENERAL_DIR}/time_mcal.c)

    if(DIAG STREQUAL Y)
        if(TIME_DIAG STREQUAL Y)
            message(STATUS "+ TIME_DIAG")
            target_compile_definitions(app PUBLIC HAS_TIME_DIAG)
            target_sources(app PRIVATE ${TIME_GENERAL_DIR}/time_diag.c)
        endif()
    endif()

    if(TIMER STREQUAL Y)
        target_sources(app PRIVATE ${TIME_GENERAL_DIR}/timer_utils.c)
    endif()

    if(MCU STREQUAL Y)
        target_sources(app PRIVATE ${TIME_GENERAL_DIR}/none_blocking_pause.c)
    endif()

    if(CLI STREQUAL Y)
        if(TIME_COMMANDS STREQUAL Y)
            message(STATUS "+ TIME_COMMANDS")
            target_sources(app PRIVATE ${TIME_GENERAL_DIR}/time_commands.c)
        endif()
    endif()
    
endif()