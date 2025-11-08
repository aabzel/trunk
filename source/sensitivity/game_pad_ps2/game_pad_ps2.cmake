message(STATUS "GAME_PAD_PS2_MK_INC=${GAME_PAD_PS2_MK_INC}")
if( NOT (GAME_PAD_PS2_MK_INC  STREQUAL  Y))
    set(GAME_PAD_PS2_MK_INC Y)
    message(STATUS "+ GAME_PAD_PS2")

    set(GAME_PAD_PS2_DIR ${ROOT_DIR}/game_pad_ps2)
    message(STATUS "GAME_PAD_PS2_DIR=${GAME_PAD_PS2_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_GAME_PAD_PS2)
    target_compile_definitions(app PUBLIC HAS_GAME_PAD_PS2)
    target_compile_definitions(app PUBLIC HAS_GAME_PAD_PS2_PROC)

    target_include_directories(app PUBLIC ${GAME_PAD_PS2_DIR})
    target_sources(app PRIVATE ${GAME_PAD_PS2_DIR}/game_pad_ps2.c)

    if(DIAG  STREQUAL  Y)
        if(GAME_PAD_PS2_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_GAME_PAD_PS2_DIAG)
            target_sources(app PRIVATE ${GAME_PAD_PS2_DIR}/game_pad_ps2_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(GAME_PAD_PS2_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_GAME_PAD_PS2_COMMANDS)
            target_sources(app PRIVATE ${GAME_PAD_PS2_DIR}/game_pad_ps2_commands.c)
        endif()
    endif()
endif()
