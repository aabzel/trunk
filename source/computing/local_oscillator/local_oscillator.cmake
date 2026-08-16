message(STATUS "LOCAL_OSCILLATOR_MK_INC=${LOCAL_OSCILLATOR_MK_INC}")
if( NOT (LOCAL_OSCILLATOR_MK_INC  STREQUAL  Y))
    set(LOCAL_OSCILLATOR_MK_INC Y)
    message(STATUS "+ LOCAL_OSCILLATOR")

    set(LOCAL_OSCILLATOR_DIR ${ROOT_DIR}/local_oscillator)
    message(STATUS "LOCAL_OSCILLATOR_DIR=${LOCAL_OSCILLATOR_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_LOCAL_OSCILLATOR)
    target_compile_definitions(app PUBLIC HAS_LOCAL_OSCILLATOR)
    target_compile_definitions(app PUBLIC HAS_LOCAL_OSCILLATOR_PROC)

    target_include_directories(app PUBLIC ${LOCAL_OSCILLATOR_DIR})
    target_sources(app PRIVATE ${LOCAL_OSCILLATOR_DIR}/local_oscillator.c)

    if(DIAG  STREQUAL  Y)
        if(LOCAL_OSCILLATOR_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_LOCAL_OSCILLATOR_DIAG)
            target_sources(app PRIVATE ${LOCAL_OSCILLATOR_DIR}/local_oscillator_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(LOCAL_OSCILLATOR_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_LOCAL_OSCILLATOR_COMMANDS)
            target_sources(app PRIVATE ${LOCAL_OSCILLATOR_DIR}/local_oscillator_commands.c)
        endif()
    endif()
endif()
