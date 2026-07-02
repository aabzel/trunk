message(STATUS "WAV_PLAYER_MK_INC=${WAV_PLAYER_MK_INC}")
if( NOT (WAV_PLAYER_MK_INC  STREQUAL  Y))
    set(WAV_PLAYER_MK_INC Y)
    message(STATUS "+ WAV_PLAYER")

    set(WAV_PLAYER_DIR ${ROOT_DIR}/wav_player)
    message(STATUS "WAV_PLAYER_DIR=${WAV_PLAYER_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_WAV_PLAYER)
    target_compile_definitions(app PUBLIC HAS_WAV_PLAYER)
    target_compile_definitions(app PUBLIC HAS_WAV_PLAYER_PROC)

    target_include_directories(app PUBLIC ${WAV_PLAYER_DIR})
    target_sources(app PRIVATE ${WAV_PLAYER_DIR}/wav_player.c)

    if(DIAG  STREQUAL  Y)
        if(WAV_PLAYER_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_WAV_PLAYER_DIAG)
            target_sources(app PRIVATE ${WAV_PLAYER_DIR}/wav_player_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(WAV_PLAYER_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_WAV_PLAYER_COMMANDS)
            target_sources(app PRIVATE ${WAV_PLAYER_DIR}/wav_player_commands.c)
        endif()
    endif()
endif()
