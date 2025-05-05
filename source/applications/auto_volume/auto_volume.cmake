message(STATUS "AUTO_VOLUME_MK_INC=${AUTO_VOLUME_MK_INC}")
if( NOT (AUTO_VOLUME_MK_INC STREQUAL Y))
    set(AUTO_VOLUME_MK_INC Y)
    message(STATUS "+ AUTO_VOLUME")

    set(AUTO_VOLUME_DIR ${APPLICATIONS_DIR}/auto_volume)

    target_include_directories(app PUBLIC ${AUTO_VOLUME_DIR})

    target_compile_definitions(app PUBLIC HAS_AUTO_VOLUME)
    target_compile_definitions(app PUBLIC HAS_AUTO_VOLUME_PROC)

    if(BLE_AUDIO_VOLUME STREQUAL Y)
        message(STATUS "+ BLE_AUDIO_VOLUME")
        target_compile_definitions(app PUBLIC HAS_BLE_AUDIO_VOLUME)
    endif()

    target_sources(app PRIVATE ${AUTO_VOLUME_DIR}/auto_volume.c)
    target_sources(app PRIVATE ${AUTO_VOLUME_DIR}/auto_volume_config.c)

    if(BT_BLE_UWB_TAG_CFG STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_BT_BLE_UWB_TAG_CFG)
    endif()

    if(BLE_SPEAKER_CFG STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_BLE_SPEAKER_CFG)
    endif()

    if(DIAG STREQUAL Y)
        if(AUTO_VOLUME_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_AUTO_VOLUME_DIAG)
            target_sources(app PRIVATE ${AUTO_VOLUME_DIR}/auto_volume_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(AUTO_VOLUME_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_AUTO_VOLUME_COMMANDS)
            target_sources(app PRIVATE ${AUTO_VOLUME_DIR}/auto_volume_commands.c)
        endif()
    endif()
endif()
