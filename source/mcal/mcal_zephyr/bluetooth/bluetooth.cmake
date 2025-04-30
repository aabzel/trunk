message(STATUS "BLUETOOTH_CMAKE_INC=${BLUETOOTH_CMAKE_INC}")
if( NOT (BLUETOOTH_CMAKE_INC STREQUAL Y))
    set(BLUETOOTH_CMAKE_INC Y)
    message(STATUS "set BLUETOOTH_CMAKE_INC=${BLUETOOTH_CMAKE_INC}")
    message(STATUS "+ BLUETOOTH for Zephyr")

    set(BLUETOOTH_ZEPHYR_DIR ${MCAL_ZEPHYR_DIR}/bluetooth)
    message(STATUS "BLUETOOTH_ZEPHYR_DIR=${BLUETOOTH_ZEPHYR_DIR}")

    add_compile_definitions(HAS_BLUETOOTH)
    target_compile_definitions(app PUBLIC HAS_BLUETOOTH)
    target_compile_definitions(app PUBLIC HAS_BLE)
    target_compile_definitions(app PUBLIC HAS_BLE_AUDIO)

    target_include_directories(app PUBLIC ${BLUETOOTH_ZEPHYR_DIR})

    target_sources(app PRIVATE ${BLUETOOTH_ZEPHYR_DIR}/ble_core.c)
    target_sources(app PRIVATE ${BLUETOOTH_ZEPHYR_DIR}/ble_audio_services.c)
    target_sources(app PRIVATE ${BLUETOOTH_ZEPHYR_DIR}/ble_hci_vsc.c)

    if (CONFIG_TRANSPORT_CIS)
        target_compile_definitions(app PUBLIC HAS_BLE_CIS)
        # HEADSET
        if (CONFIG_AUDIO_DEV EQUAL 1)
            target_sources(app PRIVATE
                ${BLUETOOTH_ZEPHYR_DIR}/le_audio_cis_headset.c)
        # GATEWAY
        elseif (CONFIG_AUDIO_DEV EQUAL 2)
            target_sources(app PRIVATE
                ${BLUETOOTH_ZEPHYR_DIR}/le_audio_cis_gateway.c)
        else()
            message(FATAL_ERROR "GATEWAY or HEADSET device must be chosen")
        endif()
    elseif (CONFIG_TRANSPORT_BIS)
        target_compile_definitions(app PUBLIC HAS_BLE_BIS)
        # HEADSET
        if (CONFIG_AUDIO_DEV EQUAL 1)
            target_sources(app PRIVATE
                ${BLUETOOTH_ZEPHYR_DIR}/le_audio_bis_headset.c)
        # GATEWAY
        elseif (CONFIG_AUDIO_DEV EQUAL 2)
            target_sources(app PRIVATE
                ${BLUETOOTH_ZEPHYR_DIR}/le_audio_bis_gateway.c)
        else()
            message(FATAL_ERROR "GATEWAY or HEADSET device must be chosen")
        endif()
    else()
        message(FATAL_ERROR "CIS or BIS mode must be chosen")
    endif()

    set(BLE_AUDIO_COMMANDS Y)
    if (CLI STREQUAL Y)
        if (BLE_AUDIO_COMMANDS STREQUAL Y)
            message(STATUS "+ BLE_AUDIO_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_BLE_AUDIO_COMMANDS)
            target_sources(app PRIVATE ${BLUETOOTH_ZEPHYR_DIR}/ble_audio_commands.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (BLUETOOTH_COMMANDS STREQUAL Y)
            message(STATUS "+ BLUETOOTH_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_BLUETOOTH_COMMANDS)
            target_sources(app PRIVATE ${BLUETOOTH_ZEPHYR_DIR}/bluetooth_commands.c)
        endif()
    endif()
endif()