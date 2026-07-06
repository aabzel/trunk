message(STATUS "SOUND_RECORDER_MK_INC=${SOUND_RECORDER_MK_INC}")
if( NOT (SOUND_RECORDER_MK_INC  STREQUAL  Y))
    set(SOUND_RECORDER_MK_INC Y)
    message(STATUS "+ SOUND_RECORDER")

    set(SOUND_RECORDER_DIR ${ROOT_DIR}/sound_recorder)
    message(STATUS "SOUND_RECORDER_DIR=${SOUND_RECORDER_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_SOUND_RECORDER)
    target_compile_definitions(app PUBLIC HAS_SOUND_RECORDER)
    target_compile_definitions(app PUBLIC HAS_SOUND_RECORDER_PROC)

    target_include_directories(app PUBLIC ${SOUND_RECORDER_DIR})
    target_sources(app PRIVATE ${SOUND_RECORDER_DIR}/sound_recorder.c)

    if(DIAG  STREQUAL  Y)
        if(SOUND_RECORDER_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SOUND_RECORDER_DIAG)
            target_sources(app PRIVATE ${SOUND_RECORDER_DIR}/sound_recorder_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(SOUND_RECORDER_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SOUND_RECORDER_COMMANDS)
            target_sources(app PRIVATE ${SOUND_RECORDER_DIR}/sound_recorder_commands.c)
        endif()
    endif()
endif()
