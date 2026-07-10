message(STATUS "REC_PLAY_MK_INC=${REC_PLAY_MK_INC}")
if( NOT (REC_PLAY_MK_INC  STREQUAL  Y))
    set(REC_PLAY_MK_INC Y)
    message(STATUS "+ REC_PLAY")

    set(REC_PLAY_DIR ${ROOT_DIR}/rec_play)
    message(STATUS "REC_PLAY_DIR=${REC_PLAY_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_REC_PLAY)
    target_compile_definitions(app PUBLIC HAS_REC_PLAY)
    target_compile_definitions(app PUBLIC HAS_REC_PLAY_PROC)

    target_include_directories(app PUBLIC ${REC_PLAY_DIR})
    target_sources(app PRIVATE ${REC_PLAY_DIR}/rec_play.c)

    if(DIAG  STREQUAL  Y)
        if(REC_PLAY_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_REC_PLAY_DIAG)
            target_sources(app PRIVATE ${REC_PLAY_DIR}/rec_play_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(REC_PLAY_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_REC_PLAY_COMMANDS)
            target_sources(app PRIVATE ${REC_PLAY_DIR}/rec_play_commands.c)
        endif()
    endif()
endif()
