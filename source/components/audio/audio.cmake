message(STATUS "AUDIO_CMK_INC=${AUDIO_CMK_INC}")
if( NOT (Y STREQUAL AUDIO_CMK_INC))
    set(AUDIO_CMK_INC Y)
    message(STATUS "Link Audio")
    set(AUDIO_DIR ${COMPONENTS_DIR}/audio)

    target_compile_definitions(app PUBLIC HAS_AUDIO)

    target_include_directories(app PUBLIC ${AUDIO_DIR})

    if(PCM_16_BIT STREQUAL Y)
        message(STATUS "PCM_16_BIT")
        target_compile_definitions(app PUBLIC PCM_SAMPLE_SIZE=2)
        target_compile_definitions(app PUBLIC HAS_PCM_16_BIT)
    endif()

    if(PCM_32_BIT STREQUAL Y)
        message(STATUS "PCM_32_BIT")
        target_compile_definitions(app PUBLIC PCM_SAMPLE_SIZE=4)
        target_compile_definitions(app PUBLIC HAS_PCM_32_BIT)
    endif()

    #target_sources(app PRIVATE ${AUDIO_DIR}/audio.c)
    #target_sources(app PRIVATE ${AUDIO_DIR}/audio_diag.c)
    #target_sources(app PRIVATE ${AUDIO_DIR}/uicr.c)
    #target_sources(app PRIVATE ${AUDIO_DIR}/channel_assignment.c)
    #target_sources(app PRIVATE ${AUDIO_DIR}/pcm_stream_channel_modifier.c)
endif()
