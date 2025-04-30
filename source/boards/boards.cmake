message(STATUS "BOARDS_MK_INC=${BOARDS_MK_INC}")
if( NOT (BOARDS_MK_INC STREQUAL Y))
    set(BOARDS_MK_INC Y)

    set(BOARDS_DIR ${WORKSPACE_LOC}/boards)
    message(STATUS "+ Boards")
    message(STATUS "BOARDS_DIR=${BOARDS_DIR}")

    target_compile_definitions(app PUBLIC HAS_BOARD)

    if(BLE_SPEAKER STREQUAL Y)
        message(STATUS "+ BLE_SPEAKER")
        include(${BOARDS_DIR}/ble_speaker/ble_speaker.cmake)
    endif()

    if(BT_BLE_UWB_TAG STREQUAL Y)
        message(STATUS "+ BT_BLE_UWB_TAG")
        include(${BOARDS_DIR}/bt_ble_uwb_tag/bt_ble_uwb_tag.cmake)
    endif()

    if(NRF5340_ADK STREQUAL Y)
        message(STATUS "+ NRF5340_ADK")
        include(${BOARDS_DIR}/nrf5340_adk/nrf5340_adk.cmake)
    endif()

    if(NRF5340_DK STREQUAL Y)
        message(STATUS "+ NRF5340_DK")
        include(${BOARDS_DIR}/nrf5340_dk/nrf5340_dk.cmake)
    endif()

    if(BLE_AUDIO_EVB_V1 STREQUAL Y)
        message(STATUS "+ BLE-Audio-EVB-v1")
        include(${BOARDS_DIR}/ble_audio_evb_v1/ble_audio_evb_v1.cmake)
    endif()
endif()
