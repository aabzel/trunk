message(STATUS "LOOPBACK_AUDIO_MK_INC=${LOOPBACK_AUDIO_MK_INC}")
if( NOT (LOOPBACK_AUDIO_MK_INC  STREQUAL  Y))
    set(LOOPBACK_AUDIO_MK_INC Y)
    message(STATUS "+ LOOPBACK_AUDIO")

    set(LOOPBACK_AUDIO_DIR ${ROOT_DIR}/loopback_audio)
    message(STATUS "LOOPBACK_AUDIO_DIR=${LOOPBACK_AUDIO_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_LOOPBACK_AUDIO)
    target_compile_definitions(app PUBLIC HAS_LOOPBACK_AUDIO)
    target_compile_definitions(app PUBLIC HAS_LOOPBACK_AUDIO_PROC)

    target_include_directories(app PUBLIC ${LOOPBACK_AUDIO_DIR})
    target_sources(app PRIVATE ${LOOPBACK_AUDIO_DIR}/loopback_audio.c)

    if(DIAG  STREQUAL  Y)
        if(LOOPBACK_AUDIO_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_LOOPBACK_AUDIO_DIAG)
            target_sources(app PRIVATE ${LOOPBACK_AUDIO_DIR}/loopback_audio_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(LOOPBACK_AUDIO_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_LOOPBACK_AUDIO_COMMANDS)
            target_sources(app PRIVATE ${LOOPBACK_AUDIO_DIR}/loopback_audio_commands.c)
        endif()
    endif()
endif()
