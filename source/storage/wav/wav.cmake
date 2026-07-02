message(STATUS "WAV_MK_INC=${WAV_MK_INC}")
if( NOT (WAV_MK_INC STREQUAL Y))

    set(WAV_MK_INC Y)
    message(STATUS "+WAV")

    set(WAV_DIR ${STORAGE_DIR}/wav)
    message(STATUS "WAV_DIR=${WAV_DIR}")

    #@ echo ${error WAV_DIR = ${WAV_DIR))

    target_compile_definitions(app PUBLIC HAS_WAV)

    target_include_directories(app PUBLIC ${WAV_DIR})

    target_sources(app PRIVATE ${WAV_DIR}/wav.c)

    if (DIAG STREQUAL Y)
        if (WAV_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_WAV_DIAG)
            target_sources(app PRIVATE ${WAV_DIR}/wav_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (WAV_COMMANDS STREQUAL Y)
             target_compile_definitions(app PUBLIC HAS_WAV_COMMANDS)
            target_sources(app PRIVATE ${WAV_DIR}/wav_commands.c)
        endif()
    endif()
endif()


