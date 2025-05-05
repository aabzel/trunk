
message(STATUS "CUSTOM_APP_CMAKE_INC=${CUSTOM_APP_CMAKE_INC}")

if( NOT (CUSTOM_APP_CMAKE_INC STREQUAL Y))
    set(CUSTOM_APP_CMAKE_INC Y)
    message(STATUS "+ APPs")
    set(APPLICATIONS_DIR ${WORKSPACE_LOC}/applications)
    message(STATUS "APPLICATIONS_DIR=${APPLICATIONS_DIR}")

    target_compile_definitions(app PUBLIC HAS_APP)
    target_compile_definitions(app PUBLIC HAS_APPLICATIONS)
    target_include_directories(app PUBLIC ${APPLICATIONS_DIR})

    if (AUTO_BRIGHTNESS STREQUAL Y)
        message(STATUS "+ AUTO_BRIGHTNESS")
        include(${APPLICATIONS_DIR}/auto_brightness/auto_brightness.cmake)
    endif()

    if (AUTO_VOLUME STREQUAL Y)
        message(STATUS "+ AUTO_VOLUME")
        include(${APPLICATIONS_DIR}/auto_volume/auto_volume.cmake)
    endif()

    if (BT_BLE_UWB_TAG_CFG STREQUAL Y)
        message(STATUS "+ BT_BLE_UWB_TAG_CFG")
        target_compile_definitions(app PUBLIC HAS_BT_BLE_UWB_TAG_CFG)
    endif()

    if (DASHBOARD STREQUAL Y)
        include(${APPLICATIONS_DIR}/dashboard/dashboard.cmake)
    endif()

    if (LIGHT_NAVIGATOR STREQUAL Y)
        include(${APPLICATIONS_DIR}/light_navigator/light_navigator.cmake)
    endif()

    if (KEYLOG STREQUAL Y)
        include(${APPLICATIONS_DIR}/keylog/keylog.cmake)
    endif()

    if (PASTILDA STREQUAL Y)
        #@echo ${error PASTILDA=${PASTILDA))
        include(${APPLICATIONS_DIR}/pastilda/pastilda.cmake)
    endif()

    target_sources(app PRIVATE ${APPLICATIONS_DIR}/applications_proc.c)

    if (CLI STREQUAL Y)
        if (APPLICATIONS_COMMANDS STREQUAL Y)
            message(STATUS "+ applications commands")
            target_compile_definitions(app PUBLIC HAS_APPLICATIONS_COMMANDS)
            target_sources(app PRIVATE ${APPLICATIONS_DIR}/applications_commands.c)
        endif()
    endif()
endif()
